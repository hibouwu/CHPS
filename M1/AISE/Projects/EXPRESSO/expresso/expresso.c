#define _POSIX_C_SOURCE 200112L
#include "expresso.h"
#include <stdio.h>
#include <stdlib.h>
#include <pthread.h>
#include <unistd.h>
#include <string.h>
#include <time.h>
#include <errno.h>

/* --- Structures Internes --- */
// Structure de nœud de tâche
typedef struct task_node {
    void (*func)(void *);            // Pointeur de fonction de tâche
    void *arg;                       // Argument de tâche
    unsigned int weight;             // Poids de la tâche
    long target_worker;              // ID du travailleur cible (-1 si non spécifié)
    struct task_node *next;          // Pointeur vers la tâche suivante
} task_node_t;

// Structure de file d'attente de tâches
typedef struct {
    task_node_t *head;               // Tête de file
    task_node_t *tail;               // Queue de file
} task_queue_t;

// Structure de l'état global du système
typedef struct {
    pthread_t *threads;              // Tableau de threads (worker_count - 1 par défaut)
    size_t worker_count;             // Nombre total de travailleurs (y compris le thread principal)
    size_t *tasks_executed;          // Statistiques des tâches exécutées par chaque travailleur
    
    task_queue_t queue;              // File d'attente des tâches
    pthread_mutex_t mutex;           // Mutex
    
    // Comme je veux synchroniser le début et la fin des tâches pour expresso_wait()
    pthread_barrier_t barrier_start; // Barrière de départ
    pthread_barrier_t barrier_end;   // Barrière de fin
    
    int shutdown;                    // flag d'arrêt
    struct timespec start_time;      // Temps de début de référence
    
    schedule_t mode;                 // Mode d'ordonnancement actuel
    long *worker_loads;              // Charge des travailleurs (estimée) pour le mode équilibré
    size_t total_tasks_submitted;    // Nombre total de tâches soumises (pour le round-robin statique)
} expresso_system_t;

static expresso_system_t sys;
static int is_initialized = 0;

/* --- Obtenir le temps actuel (en secondes) --- */
static double get_time_sec() {
    struct timespec ts;
    clock_gettime(CLOCK_MONOTONIC, &ts);
    return (double)ts.tv_sec + (double)ts.tv_nsec / 1e9;
}

/* --- Logique générique pour récupérer et exécuter des tâches --- */
static void execute_tasks_until_empty(long id) {
    while (1) {
        task_node_t *task = NULL;
        task_node_t *prev = NULL;
        
        pthread_mutex_lock(&sys.mutex);
        
        task_node_t *curr = sys.queue.head;
        
        // Logique d'ordonnancement : trouver une tâche adaptée au travailleur actuel
        while (curr != NULL) {
            // Si la tâche n'a pas de travailleur cible (-1) ou est destinée à ce travailleur
            if (curr->target_worker == -1 || curr->target_worker == id) {
                // Supprimer le noeud de tâche dans la file d'attente
                task = curr;
                if (prev) {
                    prev->next = curr->next;
                    if (sys.queue.tail == curr) {
                        sys.queue.tail = prev;
                    }
                } else {
                    sys.queue.head = curr->next;
                    if (sys.queue.tail == curr) {
                        sys.queue.tail = NULL;
                    }
                }
                break;
            }
            prev = curr;
            curr = curr->next;
        }
        
        pthread_mutex_unlock(&sys.mutex);
        
        if (task == NULL) {
            break; 
        }
        
        // Exécuter la tâche
        task->func(task->arg);
        free(task);
        
        // Statistiques (utilisation des opérations atomiques intégrées GCC)
        __atomic_fetch_add(&sys.tasks_executed[id], 1, __ATOMIC_RELAXED);
    }
}

/* --- Fonction du thread travailleur --- */
static void *worker_func(void *arg) {
    long id = (long)arg;
    
    while (1) {
        // 1. Attendre le signal de départ
        // Attendre que tous les travailleurs soient prêts (incluant le thread principal)
        int rc = pthread_barrier_wait(&sys.barrier_start);
        if (rc != 0 && rc != PTHREAD_BARRIER_SERIAL_THREAD) { }
        
        if (sys.shutdown) {
            break; 
        }
        
        // 2. Prendre des tâches
        execute_tasks_until_empty(id);
        
        // 3. Attendre la fin
        // Attendre que tous les travailleurs aient terminé (incluant le thread principal)
        pthread_barrier_wait(&sys.barrier_end);
    }
    
    return NULL;
}

/* --- Implémentation de l'API --- */
int expresso_initialize() {
    if (is_initialized) return 0;
    
    char *env = getenv("EXPRESSO_WORKER_COUNT");    // Regler le nombre de travailleurs via une variable d'environnement
    if (env) {
        sys.worker_count = atoi(env);
        if (sys.worker_count < 1) sys.worker_count = 1;
    } else {
        sys.worker_count = sysconf(_SC_NPROCESSORS_ONLN); // Par défaut, utiliser le nombre de cœurs disponibles
    }
    
    sys.threads = malloc(sizeof(pthread_t) * (sys.worker_count - 1));   // Le thread principal n'est pas inclus
    sys.tasks_executed = calloc(sys.worker_count, sizeof(size_t));
    sys.worker_loads = calloc(sys.worker_count, sizeof(long));
    
    sys.mutex = (pthread_mutex_t)PTHREAD_MUTEX_INITIALIZER;     // Initialisation du mutex
    
    pthread_barrier_init(&sys.barrier_start, NULL, sys.worker_count);
    pthread_barrier_init(&sys.barrier_end, NULL, sys.worker_count);
    
    sys.queue.head = NULL;
    sys.queue.tail = NULL;
    sys.shutdown = 0;
    
    sys.mode = SCHEDULE_DYNAMIC;    // Politique par défaut
    char *mode_env = getenv("EXPRESSO_SCHEDULE");
    if (mode_env) {
        if (strcmp(mode_env, "static") == 0) sys.mode = SCHEDULE_STATIC;
        else if (strcmp(mode_env, "balanced") == 0) sys.mode = SCHEDULE_BALANCED;
    }
    
    sys.total_tasks_submitted = 0;
    
    clock_gettime(CLOCK_MONOTONIC, &sys.start_time);
    
    for (long i = 1; i < sys.worker_count; i++) {
        pthread_create(&sys.threads[i-1], NULL, worker_func, (void *)i);
    }
    
    is_initialized = 1;
    return 0;
}

size_t expresso_worker_count() {
    return sys.worker_count;
}

schedule_t expresso_schedule_get() {
    return sys.mode; 
}

void expresso_schedule_set(schedule_t mode) {
    sys.mode = mode;
}

int expresso_task(void (*func)(void *), void *arg) {
    return expresso_weighted_task(func, arg, 1);
}

int expresso_weighted_task(void (*func)(void *), void *arg, unsigned int weight) {
    if (!func) return -1;
    if (weight == 0) return -1; // Conformément au sujet : strictement positif
    
    task_node_t *node = malloc(sizeof(task_node_t));
    node->func = func;
    node->arg = arg;
    node->weight = weight;
    node->next = NULL;
    node->target_worker = -1; // Par défaut : Dynamique
    
    // Attribution selon la politique
    if (sys.mode == SCHEDULE_STATIC) {
        // Round-robin
        node->target_worker = sys.total_tasks_submitted % sys.worker_count;
    } else if (sys.mode == SCHEDULE_BALANCED) {
        // Algorithme de glouton
        // Trouver le travailleur avec la charge minimale actuelle
        long min_load = sys.worker_loads[0];
        long target = 0;
        for (long i = 1; i < sys.worker_count; i++) {
            if (sys.worker_loads[i] < min_load) {
                min_load = sys.worker_loads[i];
                target = i;
            }
        }
        node->target_worker = target;
        sys.worker_loads[target] += weight;
    }
    
    sys.total_tasks_submitted++;
    
    // Ajout de la tâche dans la file
    pthread_mutex_lock(&sys.mutex);
    if (sys.queue.tail) {
        sys.queue.tail->next = node;
        sys.queue.tail = node;
    } else {
        sys.queue.head = node;
        sys.queue.tail = node;
    }
    pthread_mutex_unlock(&sys.mutex);
    return 0;
}

int expresso_wait() {
    // le thread principal attend que tous les travailleurs soient prêts
    pthread_barrier_wait(&sys.barrier_start);
    execute_tasks_until_empty(0);
    // le thread principal attend que tous les travailleurs aient terminé
    pthread_barrier_wait(&sys.barrier_end);

    for(size_t i=0; i<sys.worker_count; i++) sys.worker_loads[i] = 0;
    sys.total_tasks_submitted = 0;
    
    return 0;
}

void expresso_stats() {
    size_t total = 0;
    for (size_t i = 0; i < sys.worker_count; i++) {
        total += __atomic_load_n(&sys.tasks_executed[i], __ATOMIC_RELAXED);
    }
    
    printf("Expresso stats:\n");
    printf("\tTotal tasks executed: %lu\n", total);
    printf("\tAverage tasks per worker: %.2f\n", (double)total / sys.worker_count);
    for (size_t i = 0; i < sys.worker_count; i++) {
        printf("\tWorker %lu: %lu tasks\n", i, __atomic_load_n(&sys.tasks_executed[i], __ATOMIC_RELAXED));
    }
}

double expresso_wall_time() {
    return get_time_sec() - ((double)sys.start_time.tv_sec + (double)sys.start_time.tv_nsec / 1e9);
}

int expresso_finalize() {
    if (!is_initialized) return 0;
    
    sys.shutdown = 1;
    pthread_barrier_wait(&sys.barrier_start);
    
    for (size_t i = 1; i < sys.worker_count; i++) {
        pthread_join(sys.threads[i-1], NULL);
    }
    
    pthread_barrier_destroy(&sys.barrier_start);
    pthread_barrier_destroy(&sys.barrier_end);
    pthread_mutex_destroy(&sys.mutex);
    
    free(sys.threads);
    free(sys.tasks_executed);
    free(sys.worker_loads);
    
    while (sys.queue.head) {
        task_node_t *tmp = sys.queue.head;
        sys.queue.head = tmp->next;
        free(tmp);
    }
    
    is_initialized = 0;
    return 0;
}

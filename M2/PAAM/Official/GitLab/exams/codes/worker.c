
struct task_t {
  void (*func)(void*);
  void* arg;
  struct task_t* next;
};

struct queue_t {
  struct task_t* head;
  struct task_t* queue;
};

int nb_stealers = 0;
int nb_terminate = 0;

void* worker(void* queue) {
  struct task* task;

 normal:
  task = dequeue(queue);

  if(task) {
    task->func(task->arg);
    goto normal;
  }

  atomic_add(&nb_stealers, 1);

 stealer:
  for(size_t i=0; i<nb_threads; i++) {
    task = dequeueue(&queues[i]);
    
    if(task) {
      atomic_add(&nb_stealers, -1); // last question only
      task->func(task->arg);
      goto normal;
    }
  }

  // goto stealer in question

  atomic_add(&nb_terminate, 1);

  // termination
 termination:
  if(nb_stealers < nb_threads) {
    atomic_add(&nb_terminate, -1);
    goto stealers;
  }

  if(nb_termination < nb_threads)
    goto termination;
}

Exo 1 : 13 points

a: 2.5
b: 3,5
c: 2
d: 3
e: 2

I.a -- 2,5 => 0,5 perdu par erreur
struct barrier b;

void* f(void* buf) {
  barrier_wait(&b);
  return 0;
}

int main(int argc, char** argv) {
  int n = atoi(argv[1]);
  pthread_t tid[n];

  barrier_init(&b, n);

  for(int i=0; i<n; i++)
    pthread_create(&tid[i], 0, f, 0);

  for(int i=0; i<n; i++) {
    void* retval;
    pthread_join(&tid[i], &retval);
  }

  return 0;
}

I.b -- 3,5 => 0,5 perdu par erreur
struct barrier {
  int n;
  pthread_cond_t cond;
  pthread_mutex_t mutex;
};

void barrier_init(struct barrier* b, int n) {
  b->n = n;
  pthread_mutex_init(&b->mutex, 0);
  pthread_cond_init(&b->cond, 0);
}

void barrier_wait(struct barrier* b) {
  pthread_mutex_lock(&b->lock);
  if(--b->n)
    pthread_cond_wait(&b->cond, &b->lock);
  else
    pthread_cond_broadcast(&b->cond);
  pthread_mutex_unlock(&b->lock);
}

I.c -- 2 points - 0,5 perdu par erreur
struct barrier {
  _Atomic int n;
};

void barrier_init(struct barrier* b, int n) {
  atomic_store(&b->n, n);
}

void barrier_wait(struct barrier* b) {
  if(atomic_fetch_add(b->n, -1) > 1)
    while(atomic_load(&b->n)) { }
}

I.d -- 3 points
struct barrier {
  int max;
  _Atomic int n;
};

void barrier_init(struct barrier* b, int n) {
  b->max = max;
  atomic_store(&b->n, n);
}

void barrier_wait(struct barrier* b) {
  int val = atomic_fetch_add(b->n, -1);

  if(val > 1) {
    while(val > 1) {
      futex_wait(&b->n, val);
      val = atomic_load(b->n);
    }
  } else
    futex_wake(&b->n, b->max);
}

I.e -- 2 points
struct barrier {
  int n;
};

void barrier_init(struct barrier* b, int n) {
  b->n = n;
}

void barrier_wait(struct barrier* b) {
  atomic {
    b->n --;
  }

  atomic {
    if(b->n)
      retry;
  }
}

Exo 2 : 2 points

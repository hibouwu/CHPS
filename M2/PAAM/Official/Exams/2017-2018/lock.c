/* 
 *   On vous rappelle que __sync_fetch_and_add(int* ptr, int n) 
 *   permet d'ajouter n à *ptr de façon atomique.
 */
struct ticket_lock {
	int ticket;
	int guichet;
};

void init(struct ticket_lock* lock) {
	lock->ticket = 0;
	lock->guichet = 0;
}

/* prend un verrou */
void lock(struct ticket_lock* lock) {
	int ticket = __sync_fetch_and_add(&lock->ticket, 1);
	while(lock->guichet < ticket);
}

/* lâche le verrou */
void unlock(struct ticket_lock* lock) {
	__sync_fetch_and_add(&lock->guichet, 1);
}

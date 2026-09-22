struct node {
	struct node* next;
	int          val;
};

struct node*    first;
struct node*    last;
pthread_mutex_t mutex;

/* initialise le FIFO */
void init() {
	first = last = malloc(sizeof(struct node)); /* faux n&oelig;ud initial */
	first->next = 0;
}

/* ajoute un élément au début du FIFO */
void addFirst(int val) {
	struct node* node = malloc(sizeof(struct node));
	node->next = 0;
	node->val = val;

	pthread_mutex_lock(&mutex);
	last->next = node;
	last = node;
	pthread_mutex_unlock(&mutex);
}

/* retire l'élément se trouvant à la fin du FIFO */
/* attend que la file contienne au moins un élément avant de le renvoyer */
int removeLast() {
	pthread_mutex_lock(&mutex);

	while(!first->next) {
		pthread_mutex_unlock(&mutex);
		/* dans la vrai vie, on utiliserait une variable condition ici */
		pthread_mutex_lock(&mutex);
	}

	int res = first->next->val;
	first = first->next;

	pthread_mutex_unlock(&mutex);

	return res;
}

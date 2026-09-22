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
}

/* retire l'élément se trouvant à la fin du FIFO */
/* attend que la file contienne au moins un élément avant de le renvoyer */
int removeLast() {
}

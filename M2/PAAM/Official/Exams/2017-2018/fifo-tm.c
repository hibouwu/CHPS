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

	atomic {
		last->next = node;
		last = node;
	}
}

/* retire l'élément se trouvant à la fin du FIFO */
/* attend que la file contienne au moins un élément avant de le renvoyer */
int removeLast() {
	int res;

	atomic {
		if(!first->next)
			retry;
		res = first->next->val;
		first = first->next;
	}

	return res;
}

int removeAsync() {
	int res = -1;

	atomic {
		res = removeLast();
	} orElse { } /* exécute le orElse si file vide (ce qui répond à la question), mais aussi si conflit dans removeLast */

	return res;
}


struct node {
  _Atomic void* value:
  _Atomic struct node* nexts[256];
};

_Atomic struct node* root = NULL;

struct node* get_leaf(struct node** p) {
  if(!atomic_load(p)) {
    struct node* tmp = calloc(1, sizeof(*tmp));
    if(!atomic_cas(p, NULL, tmp))
      free(tmp);
  }
  
  return atomic_load(p);
}

void* insert(char* str, void* value) {
  struct node** cur = &root;
  
  for(int i=0; str[i]; i++) {
    struct node* node = get_leaf(cur);
    cur = &node->nexts[str[i]];
  }

  struct node* leaf = get_leaf(cur);

  return atomic_swap(&lead->value, value);
}

void* get(char* str) {
  struct node** cur = &root;
  
  for(int i=0; str[i]; i++) {
    if(!*cur)
      return NULL;
    cur = &cur->nexts[str[i]];
  }

  struct node* leaf = atomic_load(cur);
  
  return leaf ? atomic_load(&leaf->value) : NULL;
}


struct free_chunk {
  size_t size;
  struct free_chunk* next;
};

struct free_chunk* free_list;

void push(struct free_chunk* head, struct free_chunk* tail) {
restart:
  tail->next = free_list;
  if(!cas(&free_list, &tail->next, head))
    goto restart;
}

struct free_chunk* pop() {
  struct free_chunk* res;
  struct free_chunk* expected;

 restart:
  res = free_list;

  if(res == NULL)
    return NULL;

  expected = res->next;

  if(!cas(&free_list, &res, expected))
    goto restart;

  return res;
}

void free(void* ptr) {
  struct free_chunk* node = (struct node*)((char*)ptr - sizeof(size_t));
  push(node, node);
}

void allocate_large_chunk() {
  struct free_chunk* new_node = malloc(4096*4096);
  new_node->size = 4096*4096;
}

void* allocate(size_t size) {
  size = round_up(size + sizeof(size_t));
  struct free_chunk* head;
  struct free_chunk* tail;

  tail = pop();

  if(tail == NULL)
    tail = allocate_large_chunk();

  head = tail;

  while(head->size < size) {
    struct free_chunk* node = pop();
    if(node == NULL)
      node = allocate_large_chunk();
    node->next = head;
    head = node;
  }

  if((size + sizeof(struct free_chunk)) < head->size) {
    struct free_chunk* new_head = (struct free_chunk*)((char*)head + size);
    new_head->size = head->size - size;
    head->size = size;
    push(new_head, tail == head ? new_head : tail);
  } else if(head != tail)
    push(head->next, tail);

  return (char*)node + sizeof(size_t);
}

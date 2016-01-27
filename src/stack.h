#ifndef STACK_H_
#define STACK_H_

typedef struct _stack stack;

stack * init_stack(const uint32_t size);
void free_stack(stack *s);
void push(stack *s, int32_t x);
int32_t pop(stack *);

#endif // STACK_H_

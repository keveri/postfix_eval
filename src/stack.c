#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>

struct _stack {
    int32_t        *data;
    uint32_t       size;
    const uint32_t limit;
};
typedef struct _stack stack;

static void exit_with_error(char *msg) {
    fprintf(stderr, "%s\n", msg);
    exit(1);
}

/* Exit with failure msg if memory allocation failed. */
static void ensure_data_alloc(int32_t *d) {
    if (d == NULL) {
        free(d);
        exit_with_error("Allocation failure!");
    }
}

/* Exit with failure msg if memory allocation failed. */
static void ensure_stack_alloc(stack *s) {
    if (s == NULL) {
        free(s);
        exit_with_error("Allocation failure!");
    }
}

/* Initialize a stack to heap and return a pointer for it. */
stack * init_stack(const uint32_t limit) {
    int32_t *data = calloc(limit, sizeof(uint32_t));
    ensure_data_alloc(data);

    /* put our struct to heap so we can just pass a pointer around */
    stack *s = malloc(sizeof(stack));
    ensure_stack_alloc(s);

    /* this way we can use a constant in the struct */
    stack initial = { data, 0, limit };
    memcpy(s, &initial, sizeof(stack));

    return s;
}

/* Free all allocated memory in struct. */
void free_stack(stack *s) {
    free(s->data);
    free(s);
}

/* Push a value into the stack. */
void push(stack *s, const int32_t x) {
    if (s->size >= s->limit) {
        exit_with_error("Stack full!");
    }
    s->data[s->size++] = x;
}

/* Pop a value from the stack. */
int32_t pop(stack *s) {
    if (s->size == 0) {
        exit_with_error("Stack empty!");
    }
    int32_t x = s->data[s->size - 1];
    s->size--;
    return x;
}

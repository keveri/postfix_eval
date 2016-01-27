#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <string.h>

#include "stack.c"

/* Exit with failure msg if memory allocation failed. */
static void ensure_alloc(char *str) {
    if (str == NULL) {
        free(str);
        perror("Allocation failure!");
        exit(1);
    }
}

/* Read one line from input stream. */
static char * read(FILE *input) {
    uint32_t buff_size = 4096;
    char *line_buff    = calloc(buff_size, sizeof(char));
    ensure_alloc(line_buff);

    fgets(line_buff, buff_size, input);

    /* resize the result string to input length */
    char *result = realloc(line_buff, strlen(line_buff) * sizeof(char));
    ensure_alloc(line_buff);

    return result;
}

/* Apply operator to values from stack. */
static int32_t apply(stack *s, const char op) {
    int32_t x = pop(s);
    int32_t y = pop(s);

    switch(op) {
        case '+' : return x + y;
        case '-' : return x - y;
        case '*' : return x * y;
        case '/' : return x / y;
        default  :
            fprintf(stderr, "Invalid operator '%c'\n", op);
            exit(1);
    }
}

/* Evaluate the statement. */
static int32_t eval(const char *stmnt) {
    stack *s       = init_stack(5);
    int32_t limit  = strlen(stmnt) - 1;
    int32_t offset = 0;
    int32_t n      = 0;
    char op;
    int32_t x,y;

    /* parse and apply operations */
    while (offset < limit) {
      if (sscanf(stmnt + offset, " %d %d %c%n", &x, &y, &op, &n) == 3) {
          push(s, x);
          push(s, y);
      }
      else if (sscanf(stmnt + offset, " %d %c%n", &x, &op, &n) == 2) {
          push(s, x);
      }
      else {
          perror("Parse error!");
          exit(1);
      }
      push(s, apply(s, op));
      offset += n;
    }

    int32_t result = pop(s);
    free_stack(s);

    return result;
}

int main() {
    FILE *input     = stdin;
    char *statement = read(input);
    int32_t result  = eval(statement);

    printf("Result: %d\n", result);

    free(statement);
    return 0;
}

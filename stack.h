#include <stdint.h>

typedef struct stack {
	uint16_t value;
	struct stack *next;
} stack;

void push(stack **top, uint16_t value);
uint16_t pop(stack **top);
void show(stack *top);

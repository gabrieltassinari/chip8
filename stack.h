typedef struct stack {
	int value;
	struct stack *next;
} stack;

void push(stack **top, int value);
void pop(stack **top);
void show(stack *top);

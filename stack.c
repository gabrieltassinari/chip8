#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void push(stack **top, uint16_t value)
{
	stack *tmp;

	tmp = malloc(sizeof (stack));

	tmp->next = NULL;
	tmp->value = value;

	if (*top != NULL)
		tmp->next = *top;
	*top = tmp;
}

uint16_t pop(stack **top)
{
	uint16_t value;
	stack *tmp;

	if (*top == NULL) {
		printf("ERROR: The stack is empty.\n");
		return 0;
	}

	tmp = *top;
	value = tmp->value;

	*top = (*top)->next;

	free(tmp);

	return value;
}

void show(stack *top)
{
	for (; top != NULL; top = top->next)
		printf("%d\n", top->value);
}

#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

void push(stack **top, int value)
{
	stack *tmp;

	tmp = malloc(sizeof (stack));

	tmp->next = NULL;
	tmp->value = value;

	if (*top != NULL)
		tmp->next = *top;
	*top = tmp;
}

void pop(stack **top)
{
	if (*top == NULL) {
		printf("ERROR: Empty stack.\n");
		return;
	}

	stack *tmp;

	tmp = *top;
	*top = (*top)->next;

	free(tmp);
}

void show(stack *top)
{
	for (; top != NULL; top = top->next)
		printf("%d\n", top->value);
}


struct stacked
{
    int *stackPointer;
    int *stackBase;
} stacks;

void push(int, struct stacked *);
int pop(struct stacked *);

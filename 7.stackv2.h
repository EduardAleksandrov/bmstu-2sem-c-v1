
struct stacked
{
    int *stackPointer;
    int *stackBase;
};

void push(int, struct stacked *);
int pop(struct stacked *);

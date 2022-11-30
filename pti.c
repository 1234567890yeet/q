#include <stdio.h>
#include <math.h>
#define N 100
typedef struct Stack
{
    int array[N];
    int top;
} Stack;
Stack stack;

void push(int c)
{
    stack.array[++stack.top] = c;
}
int peek()
{
    return stack.array[stack.top];
}
int pop()
{
    return stack.array[stack.top--];
}
void postfixToInfix(char *expression)
{
    int i = 0;
    int b, a;
    while (expression[i] != '\0')
    {
        char ch = expression[i];
        if ((ch >= 48 && ch <= 57))
        {
            push((int)ch - 48);
        }
        else
        {
            b = pop();
            a = pop();
            switch (ch)
            {
            case '+':
                push(a + b);
                break;
            case '-':
                push(b - a);
                break;
            case '*':
                push(b * a);
                break;
            case '/':
                push(b / a);
                break;
            case '^':
                push(pow(b, a));
                break;
            }
        }
        i++;
    }
    printf("%d", pop());
}
int main()
{
    stack.top = -1;
    printf("Enter postfix expression: ");
    char expression[N];
    gets(expression);
    postfixToInfix(expression);
}

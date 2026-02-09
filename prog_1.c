#include <stdio.h>
#include <stdbool.h>
#include <string.h>

#define MAX 1000

typedef struct {
    char data[MAX];
    int top;
} Stack;

void initStack(Stack *s) {
    s->top = -1;
}

bool isEmpty(Stack *s) {
    return s->top == -1;
}

bool isFull(Stack *s) {
    return s->top == MAX - 1;
}

bool push(Stack *s, char ch) {
    if (isFull(s)) {
        return false; // overflow
    }
    s->data[++(s->top)] = ch;
    return true;
}

bool pop(Stack *s, char *ch) {
    if (isEmpty(s)) {
        return false; // underflow
    }
    *ch = s->data[(s->top)--];
    return true;
}
bool isMatchingPair(char open, char close) {
    return (open == '(' && close == ')') ||
           (open == '[' && close == ']') ||
           (open == '{' && close == '}');
}
ool isBalanced(const char *expr) {
    Stack s;
    initStack(&s);

    for (int i = 0; expr[i] != '\0'; i++) {
        char ch = expr[i];

        
        if (ch == '(' || ch == '[' || ch == '{') {
            if (!push(&s, ch)) {
                return false;
            }
        }
        
        else if (ch == ')' || ch == ']' || ch == '}') {
            char topChar;
            if (!pop(&s, &topChar)) {
                
                return false;
            }
            if (!isMatchingPair(topChar, ch)) {
                
                return false;
            }
        }
    }


    return isEmpty(&s);
}
#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>
#include <math.h>

#define MAX 100

typedef struct {
    int top;
    char items[MAX];
} CharStack;

typedef struct {
    int top;
    double items[MAX];
} DoubleStack;
void pushChar(CharStack *s, char c) {
    s->items[++(s->top)] = c;
}

char popChar(CharStack *s) {
    return s->items[(s->top)--];
}

char peekChar(CharStack *s) {
    return s->items[s->top];
}

void pushDouble(DoubleStack *s, double d) {
    s->items[++(s->top)] = d;
}

double popDouble(DoubleStack *s) {
    return s->items[(s->top)--];
}
int getPrecedence(char op) {
    switch (op) {
        case '+': case '-': return 1;
        case '*': case '/': return 2;
        case '^': return 3;
        default: return 0;
    }
}
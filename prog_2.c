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
void infixToPostfix(char* infix, char* postfix) {
    CharStack s;
    s.top = -1;
    int i = 0, j = 0;

    while (infix[i] != '\0') {
        char token = infix[i];

        // If operand, add to output (handles multi-digit by adding spaces)
        if (isdigit(token)) {
            while (isdigit(infix[i])) {
                postfix[j++] = infix[i++];
            }
            postfix[j++] = ' '; // Space separator for evaluation
            i--; 
        } 
        else if (token == '(') {
            pushChar(&s, '(');
        } 
        else if (token == ')') {
            while (s.top != -1 && peekChar(&s) != '(') {
                postfix[j++] = popChar(&s);
                postfix[j++] = ' ';
            }
            popChar(&s); // Pop '('
        } 
        else if (strchr("+-*/^", token)) { // Operator
            while (s.top != -1 && getPrecedence(peekChar(&s)) >= getPrecedence(token)) {
                postfix[j++] = popChar(&s);
                postfix[j++] = ' ';
            }
            pushChar(&s, token);
        }
        i++;
    }

    while (s.top != -1) {
        postfix[j++] = popChar(&s);
        postfix[j++] = ' ';
    }
    postfix[j - 1] = '\0'; // Null terminate
}double evaluatePostfix(char* postfix) {
    DoubleStack s;
    s.top = -1;
    char* token = strtok(postfix, " ");

    while (token != NULL) {
        if (isdigit(token[0])) {
            pushDouble(&s, atof(token));
        } else {
            double val2 = popDouble(&s);
            double val1 = popDouble(&s);
            switch (token[0]) {
                case '+': pushDouble(&s, val1 + val2); break;
                case '-': pushDouble(&s, val1 - val2); break;
                case '*': pushDouble(&s, val1 * val2); break;
                case '/': pushDouble(&s, val1 / val2); break;
                case '^': pushDouble(&s, pow(val1, val2)); break;
            }
        }
        token = strtok(NULL, " ");
    }
    return popDouble(&s);
}
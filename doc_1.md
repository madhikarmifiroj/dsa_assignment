## Program 1 – Balanced Parentheses Checker (Using Stack)

This program reads a mathematical expression from the user and checks whether the parentheses (round `()`, square `[]`, and curly `{}`) are **balanced** or not using a **stack** data structure.

---

### (a) Data Structure Definition

The program uses a stack implemented as a structure:

```c
typedef struct {
    char data[MAX];
    int top;
} Stack;
```

- **`data[MAX]`**: An array of characters that stores the opening brackets encountered in the expression.
- **`top`**: An integer index that points to the current top of the stack.  
  - When `top == -1`, the stack is empty.
  - On each `push`, `top` is incremented.
  - On each `pop`, `top` is decremented.

The constant **`MAX`** defines the maximum size of the stack:

```c
#define MAX 1000
```

---

### (b) Functions and Their Purpose

1. **`void initStack(Stack *s)`**
   - Initializes the stack by setting `top = -1`.
   - Must be called before using the stack.

2. **`bool isEmpty(Stack *s)`**
   - Returns `true` if the stack is empty (`top == -1`), otherwise `false`.
   - Used to check if there are no elements to pop.

3. **`bool isFull(Stack *s)`**
   - Returns `true` if the stack is full (`top == MAX - 1`), otherwise `false`.
   - Prevents stack overflow on `push`.

4. **`bool push(Stack *s, char ch)`**
   - Pushes a character `ch` (an opening bracket) onto the stack.
   - If the stack is full, it returns `false` and does not modify the stack.

5. **`bool pop(Stack *s, char *ch)`**
   - Pops the top character from the stack and stores it in `*ch`.
   - If the stack is empty, it returns `false` (underflow), which means there is no matching opening bracket.

6. **`bool isMatchingPair(char open, char close)`**
   - Checks whether an opening bracket `open` correctly matches a closing bracket `close`.
   - Returns `true` for valid pairs: `()`, `[]`, `{}`; otherwise `false`.

7. **`bool isBalanced(const char *expr)`**
   - Core logic to check if the expression `expr` has balanced brackets.
   - Algorithm:
     - Initialize an empty stack.
     - Scan the expression character by character.
     - If the character is an **opening bracket** `(`, `[`, `{` → **push** it onto the stack.
     - If the character is a **closing bracket** `)`, `]`, `}`:
       - If the stack is empty → expression is **not balanced**.
       - Otherwise, **pop** the top element and check if it forms a matching pair using `isMatchingPair`.
       - If not a matching pair → **not balanced**.
     - After the entire expression is scanned:
       - If the stack is **empty** → all brackets matched → **balanced**.
       - If the stack is **not empty** → some opening brackets had no closing partners → **not balanced**.

8. **`void testExpression(const char *expr)`**
   - Helper function that:
     - Prints the expression.
     - Calls `isBalanced(expr)` and prints `"Balanced"` or `"Not balanced"` accordingly.

---

### (c) Organization of `main()` Function

```c
int main(void) {
    char input[MAX];
    printf("Enter your own expression to test: ");
    if (fgets(input, sizeof(input), stdin) != NULL) {
        input[strcspn(input, "\n")] = '\0';
        testExpression(input);
    }

    return 0;
}
```

- Defines a character array `input` to store the user’s expression.
- Prompts the user: `"Enter your own expression to test:"`.
- Uses `fgets` to safely read a full line of input (including spaces and operators).
- Removes the trailing newline character from the input.
- Calls `testExpression(input)` to:
  - Check if the expression’s brackets are balanced.
  - Print the corresponding result.
- Returns `0` to indicate successful program termination.

The `main()` function is therefore responsible only for:
- Taking input from the user.
- Delegating the checking logic to `testExpression` / `isBalanced`.

---

### (d) Sample Output of a Complete Run

Below is an example of a complete run of the program:

```text
Enter your own expression to test: a + (b - c) * (d
Expression: a + (b - c) * (d
Result: Not balanced
```

Another example:

```text
Enter your own expression to test: a + (b - c)
Expression: a + (b - c)
Result: Balanced
```

And with mixed types of brackets:

```text
Enter your own expression to test: m + [a - b * (c + d * {m)]
Expression: m + [a - b * (c + d * {m)]
Result: Not balanced
```

These examples show how the stack-based algorithm correctly detects whether the brackets in a mathematical expression are balanced.

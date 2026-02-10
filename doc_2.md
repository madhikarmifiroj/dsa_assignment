## Program 2 – Infix to Postfix Conversion and Evaluation (Using Stack)

This program converts an **infix** mathematical expression (e.g. `(3+4)*2^3`) into its equivalent **postfix** (Reverse Polish) form, and then **evaluates** the postfix expression using stacks.

---

### (a) Explanation of Data Structures

The program uses two separate stack structures:

```c
typedef struct {
    int top;
    char items[MAX];
} CharStack;

typedef struct {
    int top;
    double items[MAX];
} DoubleStack;
```

- **`CharStack`**
  - Stores characters (operators and parentheses) during the **infix → postfix** conversion.
  - `items[MAX]` holds stack elements (`+`, `-`, `*`, `/`, `^`, `(`, `)`).
  - `top` is the index of the current top element (`-1` means the stack is empty).

- **`DoubleStack`**
  - Stores numeric values during **postfix evaluation**.
  - `items[MAX]` holds `double` values that are operands or intermediate results.
  - `top` works the same way as in `CharStack`.

Both stacks are array-based with a fixed maximum size defined by:

```c
#define MAX 100
```

---

### (b) Description of Functions

1. **`void pushChar(CharStack *s, char c)`**
   - Pushes a character `c` onto the `CharStack`.
   - Increments `top` and stores `c` at `items[top]`.
   - Used for operators and parentheses in the infix expression.

2. **`char popChar(CharStack *s)`**
   - Pops and returns the top character from the `CharStack`.
   - Decrements `top`.
   - Used when moving operators from the stack to the postfix expression or when discarding `'('`.

3. **`char peekChar(CharStack *s)`**
   - Returns the top character without removing it from the `CharStack`.
   - Used to compare operator precedence.

4. **`void pushDouble(DoubleStack *s, double d)`**
   - Pushes a `double` value `d` onto the `DoubleStack`.
   - Used during postfix evaluation to store operands and intermediate results.

5. **`double popDouble(DoubleStack *s)`**
   - Pops and returns the top `double` value from the `DoubleStack`.
   - Used to get operands for arithmetic operations during postfix evaluation.

6. **`int getPrecedence(char op)`**
   - Returns the precedence level of an operator:
     - `+` or `-` → `1`
     - `*` or `/` → `2`
     - `^`       → `3`
   - Used in infix-to-postfix conversion to decide when to pop operators from the stack.

7. **`void infixToPostfix(char* infix, char* postfix)`**
   - Converts an infix expression string into postfix form using a `CharStack`.
   - Main logic:
     - Scan the `infix` string character by character.
     - If the character is a **digit**:
       - Append it to `postfix`.
       - Handles multi-digit numbers by reading consecutive digits.
       - Adds a **space** after each number as a separator.
     - If the character is `'('`:
       - Push it onto the operator stack.
     - If the character is `')'`:
       - Pop operators from the stack and append to `postfix` until `'('` is found.
       - Pop and discard `'('`.
     - If the character is an operator (`+`, `-`, `*`, `/`, `^`):
       - While the operator stack is not empty and the operator on top has **greater or equal precedence**, pop it and append to `postfix`.
       - Then push the current operator.
     - After scanning the whole infix string:
       - Pop any remaining operators from the stack into `postfix`.
     - Finally, terminate the `postfix` string with `'\0'`.

8. **`double evaluatePostfix(char* postfix)`**
   - Evaluates a postfix expression and returns the result as a `double`.
   - Uses `strtok` with space `" "` as a delimiter to read tokens:
     - If a token starts with a **digit**, it is converted to a number using `atof` and pushed onto the `DoubleStack`.
     - If a token is an **operator**:
       - Pop the top two numbers: `val2` (right operand), then `val1` (left operand).
       - Apply the operator:
         - `+` → `val1 + val2`
         - `-` → `val1 - val2`
         - `*` → `val1 * val2`
         - `/` → `val1 / val2`
         - `^` → `pow(val1, val2)`
       - Push the result back onto the stack.
   - After all tokens are processed, the final result remains at the top of the `DoubleStack` and is returned.

---

### (c) Organization of `main()` Function

```c
int main() {
    char infix[MAX] = "(3+4)*2^3";
    char postfix[MAX];

    printf("Infix:   %s\n", infix);
    
    infixToPostfix(infix, postfix);
    printf("Postfix: %s\n", postfix);

    double result = evaluatePostfix(postfix);
    printf("Result:  %.2f\n", result);

    return 0;
}
```

- Declares an infix expression: `"(3+4)*2^3"`.
- Declares a `postfix` character array to store the converted expression.
- Prints the original **infix** expression.
- Calls `infixToPostfix(infix, postfix)` to perform the conversion.
- Prints the resulting **postfix** expression.
- Calls `evaluatePostfix(postfix)` to compute the numeric result.
- Prints the final **result** with two decimal places.
- Returns `0` to indicate successful program termination.

`main()` thus demonstrates the complete flow:
1. Start from an infix expression.
2. Convert it to postfix.
3. Evaluate the postfix expression.

---

### (d) Sample Output of a Complete Run

For the hardcoded infix expression `(3+4)*2^3`, a sample run looks like this:

```text
Infix:   (3+4)*2^3
Postfix: 3 4 + 2 3 ^ *
Result:  56.00
```

Explanation:
- `3 4 +` evaluates to `7`.
- `2 3 ^` evaluates to \(2^3 = 8\).
- `7 * 8` evaluates to `56`.

This confirms that the program correctly converts the infix expression to postfix form and evaluates the result using stack-based processing.

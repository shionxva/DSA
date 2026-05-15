# Large Integer Arithmetic System

## Summary

This project implements a large integer arithmetic system in C++ supporting up to 100 digits, without relying on any built-in big integer library. The system handles large integers, negative numbers, and complex expressions with correct operator precedence and parentheses. Numbers are stored as digit arrays, and a recursive descent parser evaluates multi-operation expressions.

---

## BigNum

### Number Storage

Numbers are stored as a reversed integer array of up to 100 elements inside a `BigNum` struct, which tracks:

- `digit[]` — the digit array (least significant digit at index 0)
- `digitCount` — number of active digits
- `negative` — sign flag
- `decimalPlaces` — number of digits after the decimal point

**Example:** `123` is stored as `[3, 2, 1, 0, 0, ..., 0]` with `digitCount = 3` and `negative = false`.

---

### Helper / Utility Functions

| Function | Description |
|---|---|
| `print()` | Outputs the number with correct sign and digit order to stdout and/or a file |
| `op()` | Dispatches to the correct arithmetic function given an operator character |
| `compareABS()` | Compares two numbers by absolute value — length first, then most significant digit |
| `compare()` | Full signed comparison, accounting for both signs |
| `subABS()` | Subtracts two numbers by absolute value, without sign handling |
| `align()` | Pads the operand with fewer decimal places so both share the same `decimalPlaces` before addition or subtraction |
| `round2()` | Rounds the result to 2 decimal places before printing |

---

### Arithmetic

#### Addition — `add()`

Digits are summed from least to most significant, carrying any overflow forward. Sign handling adds complexity:

- **Same sign:** sum the absolute values; result inherits that sign.
- **Different signs:** reduce to a subtraction; the result takes the sign of the larger absolute value.

#### Subtraction — `sub()`

Flips the sign of the second operand and delegates to `add()`, reusing its sign logic:

```
A - B  →  A + (-B)
-A - B  →  -A + (-B)
```

#### Multiplication — `mul()`

Uses the standard long multiplication algorithm:

```cpp
for (int i = 0; i < digitCount; i++) {
    int carry = 0;
    for (int j = 0; j < other.digitCount; j++) {
        int r = mul.digit[i + j] + digit[i] * other.digit[j] + carry;
        mul.digit[i + j] = r % 10;
        carry = r / 10;
    }
    mul.digit[i + other.digitCount] += carry;
}
```

The result sign is determined from the signs of the two operands.

#### Division — `div()`

Signs are stripped first; the result sign is assigned at the end. The algorithm performs long division digit by digit:

1. Bring down digits from the dividend one at a time into a running `current` value.
2. Count how many times `current` fits the divisor (`qdigit`), subtract accordingly.
3. Store `qdigit` in the quotient and continue.
4. Extend the dividend by a fixed precision (10 digits) of trailing zeros to produce decimal output.

**Example — `100 / 5`:**
- Bring down `1` → less than `5`, bring down `0` → `10 ≥ 5`
- Subtract `5` twice → `qdigit = 2`, remainder `0`
- Continue for remaining digits → result `20`

---

### Decimal Support

`decimalPlaces` tracks the implied decimal position without changing how digits are stored internally.

**Example:** `3.14` is stored as `[4, 1, 3, 0, ..., 0]` with `digitCount = 3` and `decimalPlaces = 2`.

Each operation propagates `decimalPlaces` differently:

| Operation | Decimal places in result |
|---|---|
| `add` / `sub` | Operands are aligned first; result inherits `max(d1, d2)` |
| `mul` | `d1 + d2` (e.g. `1.5 × 1.5 = 2.25` → 2 places) |
| `div` | Decimal places cancel; dividend is extended by 10 digits of precision |

Trailing decimal zeros are stripped in `print()` by skipping zero-valued low-index digits before output.

---

## Parser

The parser implements a standard operator-precedence grammar using recursive descent:

```
expression = term | expression "+" term | expression "-" term
term       = factor | term "*" factor | term "/" factor
factor     = number | "(" expression ")" | "-" factor
```

The four parsing functions — `parseExpression()`, `parseTerm()`, `parseFactor()`, and `parseNumber()` — call each other recursively to enforce precedence naturally. When `parseFactor()` encounters `(`, it calls `parseExpression()` recursively and expects a closing `)` on return.

### Unary Minus

A leading `-` is treated as a factor rather than a binary operator. The parser skips the `-`, recursively parses the following factor, then negates the result.

**Example:** `-5 + 3`
1. `pos[0] = '-'` → skip, call `parseFactor()` recursively
2. Returns `5` → negate → `-5`
3. Continue with `+ 3` → result `−2`

---

## Error Handling

The system catches and reports the following errors:

- Division by zero
- Multiplication overflow (result exceeds 100 digits)
- Parser errors (mismatched parentheses, invalid tokens)
- File I/O errors (missing or unreadable input file)

Errors are written to both stdout and the output file in the format:

```
Error: <message> from: <expression>
```

---

## Results

The system passed all test cases with integers up to 100 digits and produced accurate results across addition, subtraction, multiplication, and division — including negative numbers, nested expressions, and decimal outputs rounded to 2 decimal places.

---

## References
Big Integer struct and how to add them together. [BigInteger](https://www.youtube.com/watch?v=FwIBLSnz6A8)

Parse logic. [StackOverflow](https://stackoverflow.com/questions/2969561/how-to-parse-mathematical-expressions-involving-parentheses)

and a little help from my Ai friend :3
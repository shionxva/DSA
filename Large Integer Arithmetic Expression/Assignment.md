# Assignment 1: Large Integer Arithmetic Expression

## Objective

In this lab, you will implement a program that evaluates large integer arithmetic expressions with multiple operands and parentheses. You will work with large integers (up to 100 digits) and ensure the proper handling of basic arithmetic operations, respecting the precedence of operations, including the use of parentheses.

## Problem Statement

Given a mathematical infix expression containing large integers (up to 100 digits) and multiple arithmetic operators \((+,- ,*,\%)\), your task is to evaluate the expression and return the result. The expression may also include parentheses to group operations. Your program should handle expressions with multiple operands, correctly respecting the order of operations (PMDAS: Parentheses, Multiplication/Division, Addition/Subtraction).

## Requirements

### 1. Input

A string representing the arithmetic expression. The expression may contain:

- Large integers (up to 100 digits)
- The four basic arithmetic operators \((+,- ,*,\%)\)
- Parentheses to denote precedence in operations

**Example Input:**  
`(12345678901234567890 + (98765432109876543210 - 12345678901234567890)) * 100`

### 2. Output

The result of evaluating the arithmetic expression, taking into account the proper order of operations, including the handling of parentheses.

**Example Output:**  
`1111111111111111111000000000000000000000`

### 3. Tasks

- Replace `StudentID` with your student ID.
- Take input from the file named `tests.txt`.
- Output results to the file named `output_StudentID.txt`.
- Each line in `tests.txt` is an arithmetic expression.
- Your program must be a **C++** program.
- The `.cpp` file containing the `main` function must be named with your student ID: `StudentID.cpp`.
- The program takes two command-line arguments:
  - `x` = `tests.txt`
  - `y` = `output_StudentID.txt`
- It prints the results of each expression in `tests.txt` to both the terminal and the output file.

**Example:**

In `tests.txt` contains:

- (12345678901234567890 + (98765432109876543210 - 12345678901234567890)) * 100
- 1 + 2 * 4

Running:

```bash
g++ StudentID.cpp -o StudentID
./StudentID tests.txt output_StudentID.txt
```

The terminal and output_StudentID.txt should show:
- 1111111111111111111110000000000000000000000
- 9

### 4. Evaluation Criteria
You are NOT ALLOWED to use any built-in data structure or library capable of handling large integers or expressions (e.g., BigInteger in C++ is prohibited).

- Your solution should handle errors gracefully, such as division by zero or malformed expressions, and output appropriate error messages.
- Correctness of results for various test cases, including those with parentheses and multiple operations.
- Proper handling of large integers and negative numbers.
- Correct implementation of operator precedence and parentheses handling.
- Efficient parsing and evaluation of expressions with multiple nested operations.

### 6.Report Guidelines
Submit your source code and report. All source codes must be placed in a folder named StudentID, then zipped to StudentID.zip. The report must be in PDF format and named StudentID.pdf.

A table that describes which part of your source code is written by you and which part is referenced. For referenced parts, you must explicitly write the reference source.

Any violation of these guidelines or the tasks will result in a score of zero.
# postfix_eval
Evaluate arithmetic expressions using postfix notation (also known as Reverse Polish Notation or RPN).

## Setup

Build:
```
$ make
```

Clean:
```
$ make clean
```

## Usage

Program reads input from `stdin`.

Example:
```
$ echo "1 2 + 3 *" | postfix_eval
Result: 9
```

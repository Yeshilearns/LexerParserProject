# LexerParserProject
# Lexical Analyzer in C++

## Overview
This project is a **Lexical Analyzer** written in **C++**. It reads an input file character by character, groups them into lexemes, and assigns each lexeme a corresponding token code.

The goal of this project is to simulate the **first phase of a compiler**, where raw source code is broken into tokens that can later be used for parsing.


## Features

The lexer recognizes the following:

### Keywords
- int, short, long, signed, unsigned  
- float, double, const  
- do, else, for, if, switch, while  

### Identifiers
- Variable names like `x`, `sum`, `value_1`
- Supports underscores `_`

### Array Identifiers
- Recognizes patterns like `arr[10]`

### Literals
- Integer literals → `25`, `100`
- Floating-point literals → `3.14`, `2.5e10`

### Operators
- Arithmetic: `+`, `-`, `*`, `/`, `%`, `^`
- Assignment: `=`
- Increment / Decrement: `++`, `--`
- Compound operators:
  - `+=`, `-=`, `*=`, `/=`, `%=`, `^=`
- Unary minus (represented as `~`)

### Separators / Delimiters
- `(` `)`  
- `{` `}`  
- `[` `]`  
- `,` `;`

---

## Token Codes

### Literals & Identifiers
| Token | Code |
|------|------|
| Integer Literal | 10 |
| Identifier | 11 |
| Array Identifier | 12 |
| Float Literal | 14 |
| Keyword | 15 |

### Delimiters
| Token | Code |
|------|------|
| ( | 25 |
| ) | 26 |
| { | 125 |
| } | 126 |
| , | 127 |
| ; | 128 |
| [ | 129 |
| ] | 130 |

### Operators
| Token | Code |
|------|------|
| = | 220 |
| + | 221 |
| - | 222 |
| * | 223 |
| / | 224 |
| ^ | 227 |
| ~ (Unary minus) | 328 |
| % | 329 |
| ++ | 330 |
| -- | 331 |
| += | 341 |
| -= | 342 |
| *= | 343 |
| /= | 344 |
| ^= | 347 |
| %= | 349 |

---

## How It Works

1. The program opens an input file (`TESTCASE_1.in`).
2. It reads one character at a time.
3. Each character is classified as:
   - LETTER
   - DIGIT
   - UNKNOWN
   - END OF FILE
4. Based on the classification:
   - Letters → identifiers or keywords
   - Digits → integers or floats
   - Unknown → operators or delimiters
5. The lexer prints the token code and lexeme.
6. This continues until the end of file is reached.

---

## Key Functions

- **addChar()** → Adds character to current lexeme  
- **getChar()** → Reads next character from file  
- **getNonBlank()** → Skips whitespace  
- **isKeyword()** → Checks if lexeme is a keyword  
- **lookup()** → Handles operators and separators  
- **lex()** → Core function that identifies tokens  

---

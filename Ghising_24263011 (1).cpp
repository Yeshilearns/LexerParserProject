//Hisey_Dolma Ghising 24263011
#include <iostream>
#include <fstream>
#include <cctype>
#include <cstring>
#include <vector>
#include <algorithm>

using namespace std;
//character classes to categorize input characters
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99
#define END_OF_FILE -1
//Tokesn provided in instructions for constants, identifiers, keywords, operators and so on where I introduced helper operators '[',']'
#define INT_LIT 10
#define IDENT 11
#define ARRAY_IDENT 12
#define FLOAT_LIT 14
#define KEYWORD 15

#define LEFT_PAREN 25
#define RIGHT_PAREN 26
#define L_CURLY 125
#define R_CURLY 126
#define COMMA 127
#define SEMICOLON 128
#define LEFT_BRACKET 129
#define RIGHT_BRACKET 130

#define ASSIGN_OP 220
#define ADD_OP 221
#define SUB_OP 222
#define MULT_OP 223
#define DIV_OP 224
#define POWER_OP 227

#define UNARY_MINUS 328
#define MODULO_OP 329

#define INC_OP 330
#define DEC_OP 331
#define ADD_ASSIGN 341
#define SUB_ASSIGN 342
#define MULT_ASSIGN 343
#define DIV_ASSIGN 344
#define POWER_ASSIGN 347
#define MODULO_ASSIGN 349
//Global declaration variables 
int charClass;
char lexeme[100];
char nextChar;
int lexLen = 0;
int token;
int nextToken;
ifstream in_fp;
//function declarations
void addChar();
void getChar();
void getNonBlank();
int lex();
int lookup(char ch);
bool isKeyword(const string& word);
//these are keywords that are recognized by the lexer
const vector<string> keywords = {
    "int", "short", "long", "signed", "unsigned",
    "float", "double", "const", "do", "else",
    "for", "if", "switch", "while"
};

//Main function->opens input file, scans the character and characterizes them based on our tokens
int main() {
    in_fp.open("TESTCASE_1.in");
    //in_fp.open("TESTCASE_2.in");
    if (!in_fp) {
        cout << "ERROR - cannot open file" << endl;
        return 1;
    }
  
//here it gets the next character and then tokenizes each characters and repeats over all until the End OF File is reached
    getChar();
    do {
        lex();
    } while (nextToken != END_OF_FILE);

    return 0;
}
//AddChar()-> adds nextCHar to lexeme
void addChar() {
    if (lexLen <= 98) {
        lexeme[lexLen++] = nextChar;
        lexeme[lexLen] = '\0';
    }else {
        cout << "Error - lexeme is too long" << endl;
    }
}
//getChar->function to get the next character of input and determine its character class
void getChar() {
    if (in_fp.get(nextChar)) {
        if (isalpha(nextChar) || nextChar == '_') charClass = LETTER;
        else if (isdigit(nextChar)) charClass = DIGIT;
        else charClass = UNKNOWN;
    }else {
        charClass = END_OF_FILE;
    }
}
//getnonBlank->to call getchar until it return a non white space character
void getNonBlank() {
    while (isspace(nextChar)) getChar();
}
//iskeyword->checks if a string matches any known keyword
bool isKeyword(const string& word) {
    return find(keywords.begin(), keywords.end(), word) != keywords.end();
}
//this looks up and returns the token code for operators and separators based on each condition and handles them accordingly 
int lookup(char ch) {
    lexLen = 0;  // Reset lexeme length here for operators
    lexeme[lexLen++] = ch;
    lexeme[1] = '\0';
    
    switch (ch) {
    case '[': nextToken = LEFT_BRACKET; break;
    case ']': nextToken = RIGHT_BRACKET; break;
    case '(': nextToken = LEFT_PAREN; break;
    case ')': nextToken = RIGHT_PAREN; break;
    case '{': nextToken = L_CURLY; break;
    case '}': nextToken = R_CURLY; break;
    case ',': nextToken = COMMA; break;
    case ';': nextToken = SEMICOLON; break;
        //handles all the'+' related operators as uniary +, += and soon
    case '+':
        getChar();
        if (nextChar == '+') {
            lexeme[lexLen++] = nextChar;
            lexeme[lexLen] = '\0';
            nextToken = INC_OP;
        }else if (nextChar == '=') {
            lexeme[lexLen++] = nextChar;
            lexeme[lexLen] = '\0';
            nextToken = ADD_ASSIGN;
        }else {
            in_fp.unget();
            lexeme[1] = '\0';
            nextToken = ADD_OP;
        }
        break;
    case '-':
        getChar();
        if (nextChar == '-') {
            lexeme[lexLen++] = nextChar;
            lexeme[lexLen] = '\0';
            nextToken = DEC_OP;
        }else if (nextChar == '=') {
            lexeme[lexLen++] = nextChar;
            lexeme[lexLen] = '\0';
            nextToken = SUB_ASSIGN;
        }else {
            in_fp.unget();
            lexeme[1] = '\0';
            nextToken = SUB_OP;
        }
        break;
    case '*':
        getChar();
        if (nextChar == '=') {
            lexeme[lexLen++] = nextChar;
            lexeme[lexLen] = '\0'; 
            nextToken = MULT_ASSIGN;
        }
        else {
            in_fp.unget();
            lexeme[1] = '\0';
            nextToken = MULT_OP;
        }
        break;
    case '/':
        getChar();
        if (nextChar == '=') {
            lexeme[lexLen++] = nextChar;
            lexeme[lexLen] = '\0';
            nextToken = DIV_ASSIGN;
        }
        else {
            in_fp.unget();
            lexeme[1] = '\0';
            nextToken = DIV_OP;
        }
        break;
    case '=': nextToken = ASSIGN_OP; break;
    case '^':
        getChar();
        if (nextChar == '=') {
            lexeme[lexLen++] = nextChar;
            lexeme[lexLen] = '\0';
            nextToken = POWER_ASSIGN;
        }
        else {
            in_fp.unget();
            lexeme[1] = '\0';
            nextToken = POWER_OP;
        }
        break;
    case '%':
        getChar();
        if (nextChar == '=') {
            lexeme[lexLen++] = nextChar;
            lexeme[lexLen] = '\0';
            nextToken = MODULO_ASSIGN;
        }
        else {
            in_fp.unget();
            lexeme[1] = '\0';
            nextToken = MODULO_OP;
        }
        break;
    case '~': nextToken = UNARY_MINUS; break;
    default: nextToken = END_OF_FILE; break;
    }
    return nextToken;
}
/*lexical analyzer functions that indentifes the tokens.Based on the character class we process accordingly like
if its a letter then it process either identifier or keyword and if its digit then it process either interger or float
similarly for any unknown symbol it looksup it its an operator and eventually END of file after which it stops processing
 */
int lex() {
    lexLen = 0;
    getNonBlank();

    switch (charClass) {
    case LETTER:
        addChar();
        getChar();
        while (isalnum(nextChar) || nextChar == '_') {
            addChar();
            getChar();
        }
        nextToken = IDENT;

        if (nextChar == '[') {
            addChar();
            getChar();

            while (charClass == DIGIT) {
                addChar();
                getChar();
            }

            addChar();
            getChar();

            nextToken = ARRAY_IDENT;
        }

        for (int i = 0; i < keywords.size(); i++) {
            if (strcmp(lexeme, keywords[i].c_str()) == 0) {
                nextToken = KEYWORD;
                break;
            }
        }
        break;

    case DIGIT:
        addChar();
        getChar();

        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;

        if (nextChar == '.') {
            addChar();
            getChar();

            while (charClass == DIGIT) {
                addChar();
                getChar();
            }

            if (nextChar == 'e' || nextChar == 'E') {
                addChar();
                getChar();

                if (nextChar == '+' || nextChar == '-') {
                    addChar();
                    getChar();
                }

                while (charClass == DIGIT) {
                    addChar();
                    getChar();
                }
            }

            nextToken = FLOAT_LIT;
        }
        break;
        //this looks for unknown character beside explained above
    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;

    case END_OF_FILE:
        nextToken = END_OF_FILE;
        strcpy(lexeme, "EOF");
        //strcpy_s(lexeme, sizeof(lexeme), "EOF");


        break;
    }
    //outputs the result of lexical analysis
    cout << "Token Num Code =" << '\t' << nextToken << '\t' << "Lexeme =" << '\t' << lexeme << endl;
    return nextToken;
}


#include <iostream>
#include <cctype>
#include <string>
#include <sstream>

using namespace std;

/* Global declarations */
/* Variables */
int charClass;
string lexeme;
char nextChar;
int lexLen;
int token;
int nextToken;
stringstream input_stream; // For using `cin` input

/* Function declarations */
void addChar();
void getChar();
void getNonBlank();
int lex();

/* Character classes */
#define LETTER 0
#define DIGIT 1
#define UNKNOWN 99

/* Token codes */
#define INT_LIT 10
#define IDENT 11
#define ASSIGN_OP 30 // Add this for '='
#define ADD_OP 21
#define SUB_OP 22
#define MULT_OP 23
#define DIV_OP 24
#define LEFT_PAREN 25
#define RIGHT_PAREN 26

/******************/
/* main driver */
int main() {
    // Read the entire line of input into a string stream
    string input;
    cout << "Enter an expression: ";
    getline(cin, input);
    input_stream.str(input); // Set the input stream to the user input

    getChar();
    do {
        lex();
    } while (nextToken != EOF);
    return 0;
}

/*******************/
/* lookup - a function to lookup operators and parentheses
and return the token */
int lookup(char ch) {
    switch (ch) {
    case '(':
        addChar();
        nextToken = LEFT_PAREN;
        break;
    case ')':
        addChar();
        nextToken = RIGHT_PAREN;
        break;
    case '+':
        addChar();
        nextToken = ADD_OP;
        break;
    case '-':
        addChar();
        nextToken = SUB_OP;
        break;
    case '*':
        addChar();
        nextToken = MULT_OP;
        break;
    case '/':
        addChar();
        nextToken = DIV_OP;
        break;
    case '=':
        addChar();
        nextToken = ASSIGN_OP; // Handle '=' as an assignment operator
        break;
    default:
        addChar();
        nextToken = EOF;
        break;
    }
    return nextToken;
}

/*******************/
/* addChar - a function to add nextChar to lexeme */
void addChar() {
    if (lexLen <= 98) {
        lexeme += nextChar;
        lexLen++;
    }
    else {
        cout << "Error - lexeme is too long" << endl;
    }
}

/*******************/
/* getChar - a function to get the next character of
input and determine its character class */
void getChar() {
    nextChar = input_stream.get();
    if (!input_stream.eof()) {
        if (isalpha(nextChar)) {
            charClass = LETTER;
        }
        else if (isdigit(nextChar)) {
            charClass = DIGIT;
        }
        else {
            charClass = UNKNOWN;
        }
    }
    else {
        charClass = EOF;
    }
}

/*******************/
/* getNonBlank - a function to call getChar until it
returns a non-whitespace character */
void getNonBlank() {
    while (isspace(nextChar)) {
        getChar();
    }
}

/*******************/
/* lex - a simple lexical analyzer for arithmetic
expressions */
int lex() {
    lexLen = 0;
    lexeme.clear();
    getNonBlank();
    switch (charClass) {
        /* Parse identifiers */
    case LETTER:
        addChar();
        getChar();
        while (charClass == LETTER || charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = IDENT;
        break;

        /* Parse integer literals */
    case DIGIT:
        addChar();
        getChar();
        while (charClass == DIGIT) {
            addChar();
            getChar();
        }
        nextToken = INT_LIT;
        break;

        /* Parentheses and operators */
    case UNKNOWN:
        lookup(nextChar);
        getChar();
        break;

        /* EOF */
    case EOF:
        nextToken = EOF;
        lexeme = "EOF";
        break;
    }

    cout << "Next token is: " << nextToken << ", Next lexeme is " << lexeme << endl;
    return nextToken;
}

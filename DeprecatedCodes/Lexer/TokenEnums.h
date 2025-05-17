
enum TokenType{
    NUL = 0x00,             // NULL character, end of something
    TAB = 0x0B,             // Tabbed whitespaces
    LF = 0x0A,              // New Line
    CR = 0x0D,              // Carret Return
    SPACE = 0x20,           // Space 
    EXCLM = 0x21,           // Exclamation Mark, used for User defined data types declaration
    QOUTE = 0x22,           // Double Quotes for String
    PRCNT = 0x25,           // % for modulo operations
    AMP = 0x26,             // Ampersand for conditional and bitwise operations
    APOS = 0x27,            // Single Quotes for character
    LPARN = 0x28,           // Left Parenthesis for used various declarations
    RPAREN = 0x29,          // Right Parenthesis for used various declarations
    AST = 0x2A,             // Asterisk for multiplication, Comments
    PLUS = 0x2B,            // Plus for addition
    COMMA = 0x2C,           // Comma used for various declarations
    MINUS = 0x2D,           // Minus for subtraction and loop iteration
    PERIOD = 0x2E,          // Dot used for for User defined data types usage 
    DIVIDE = 0x2F,          // Divide for Division, Comments
    COLON = 0x3A,           // Colon for If-Case, Labels
    SEMI = 0x3B,            // Semicolon for ending of a statement and seperation for map
    LTHAN = 0x3C,           // Less than for conditional operations
    EQUAL = 0x3D,           // Equals for equating values and testing equalness
    GTHAN = 0x3E,           // Greater than for conditional operations
    LBRAK = 0x5B,           // Left Bracket for used Simple Data Structures
    RBRAK = 0x5D,           // Right Bracket for used Simple Data Structures
    CARET = 0x5E,           // Caret - circumflex used for equating to the power operations
    LBRAC = 0x7B,           // Left Brace for various opening declarations
    VBAR = 0x7C,            // Vertical Bar for conditional and bitwise operations
    RBRAC = 0x7D,           // Right Brace for closing opened declarations

    SYMTKN_END,             // End of one character symbol token

    // Expressions
    PLUS_PLUS,              // ++ increment expression
    MINUS_MINUS,            // -- decrement expression
    PLUS_EQUAL,             // += assignment expression
    MINUS_EQUAL,            // -= assignment expression
    EQUAL_EQUAL,            // == conditional expression
    LESS_EQUAL,             // <= conditional expression
    GREAT_EQUAL,            // >= conditional expression
    NOT_EQUAL,              // != conditional expression

    EXPTKN_END,             // End of Expression Token

    // Declarations
    USE,                   // include a file to access its contents in the current file
    MAIN,                  // main entry point
    LET,                   // Mutable variable and Simple Data Structures. Function with return value and User defined data types
    CONST,                 // Immutable variable and data structure declaration
    PB,                    // Declare variable or function as public
    STRUCT,                // Declared s!
    ENUM,                  // Declared e!
    UNION,                 // Declared u!
    PROTO,                 // Declared p!
    ARRAY,                 // Declared a[
    SET,                   // Declared s[
    MAP,                   // Declared m[
    TUPLE,                 // Declared t[
    IDENTIFIER,            // Name given to variable, functions or any simple or user defined data types
    CH_LITERAL,            // Fixed character value
    STR_LITERAL,           // Fixed string value
    NUM_LITERAL,           // Fixed number value
    FLT_LITERAL,           // Fixed float value
        
    DECLTKN_END,           // End of Declaration Tokens
    
    // Control Flows   
    IF,                   // If else, if-case
    ELIF,                 // else if
    ELSE,                 // else and default for if-case
    LOOP,                 // for loop, while loop, foreach
    IN,                   // loop directive 
    SPAN,                 // loop range
    CONT,                 // continue statement
    RET,                  // return statement
    BRK,                  // break statement
    GOTO,                 // goto label statement
    
    CTLFTKN_END,           // End of Control Flow Tokens

    // Special Tokens
    EOL,                   // End of Line token
    EOF,                   // End of File Token

    SPCTKN_END             // End of Special Token
};

bool isUpperAlpha(char c){
    return (c > 0x40 && c < 0x5B) ? true : false;
}

bool isLowerAlpha(char c){
    return (c > 0x60 && c < 0x7B) ? true : false;
}

bool isAlphabet(char c){
    return isUpperAlpha(c) | isLowerAlpha(c);
}

bool isNumber(char c){
    return (c > 0x2F && c < 0x3A) ? true : false;
}


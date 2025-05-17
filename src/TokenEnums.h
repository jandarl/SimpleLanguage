
enum TokenType{
    NUL,             // NULL character, end of something
    TAB,             // Tabbed whitespaces
    LF,              // New Line
    CR,              // Carret Return
    SPACE,           // Space 
    EXCLM,           // Exclamation Mark, used for User defined data types declaration
    QOUTE,           // Double Quotes for String
    PRCNT,           // % for modulo operations
    AMP,             // Ampersand for conditional and bitwise operations
    APOS,            // Single Quotes for character
    LPARN,           // Left Parenthesis for used various declarations
    RPAREN,          // Right Parenthesis for used various declarations
    AST,             // Asterisk for multiplication, Comments
    PLUS,            // Plus for addition
    COMMA,           // Comma used for various declarations
    MINUS,           // Minus for subtraction and loop iteration
    PERIOD,          // Dot used for for User defined data types usage 
    DIVIDE,          // Divide for Division, Comments
    COLON,           // Colon for If-Case, Labels
    SEMI,            // Semicolon for ending of a statement and seperation for map
    LTHAN,           // Less than for conditional operations
    EQUAL,           // Equals for equating values and testing equalness
    GTHAN,           // Greater than for conditional operations
    LBRAK,           // Left Bracket for used Simple Data Structures
    RBRAK,           // Right Bracket for used Simple Data Structures
    CARET,           // Caret - circumflex used for equating to the power operations
    LBRAC,           // Left Brace for various opening declarations
    VBAR,            // Vertical Bar for conditional and bitwise operations
    RBRAC,           // Right Brace for closing opened declarations

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
    COMMENT_BEG,           // Beginning of a Comment
    COMMENT_END,           // End of a Comment
    EOL,                   // End of Line token
    ENDF,                  // End of File Token

    SPCTKN_END             // End of Special Token
};



// TokenType String Equivalent
static const char *TokenTypeString[] = {
	"NUL",             // NULL character, end of something
    "TAB",             // Tabbed whitespaces
    "LF",              // New Line
    "CR",              // Carret Return
    "SPACE",           // Space 
    "EXCLM",           // Exclamation Mark, used for User defined data types declaration
    "QOUTE",           // Double Quotes for String
    "PRCNT",           // % for modulo operations
    "AMP",             // Ampersand for conditional and bitwise operations
    "APOS",            // Single Quotes for character
    "LPARN",           // Left Parenthesis for used various declarations
    "RPAREN",          // Right Parenthesis for used various declarations
    "AST",             // Asterisk for multiplication, Comments
    "PLUS",            // Plus for addition
    "COMMA",           // Comma used for various declarations
    "MINUS",           // Minus for subtraction and loop iteration
    "PERIOD",          // Dot used for for User defined data types usage 
    "DIVIDE",          // Divide for Division, Comments
    "COLON",           // Colon for If-Case, Labels
    "SEMI",            // Semicolon for ending of a statement and seperation for map
    "LTHAN",           // Less than for conditional operations
    "EQUAL",           // Equals for equating values and testing equalness
    "GTHAN",           // Greater than for conditional operations
    "LBRAK",           // Left Bracket for used Simple Data Structures
    "RBRAK",           // Right Bracket for used Simple Data Structures
    "CARET",           // Caret - circumflex used for equating to the power operations
    "LBRAC",           // Left Brace for various opening declarations
    "VBAR",            // Vertical Bar for conditional and bitwise operations
    "RBRAC",           // Right Brace for closing opened declarations
	
    "SYMTKN_END",             // End of one character symbol token
	
    // Expressions
    "PLUS_PLUS",              // ++ increment expression
    "MINUS_MINUS",            // -- decrement expression
    "PLUS_EQUAL",             // += assignment expression
    "MINUS_EQUAL",            // -= assignment expression
    "EQUAL_EQUAL",            // == conditional expression
    "LESS_EQUAL",             // <= conditional expression
    "GREAT_EQUAL",            // >= conditional expression
    "NOT_EQUAL",              // != conditional expression
	
    "EXPTKN_END",             // End of Expression Token
	
    // Declarations
    "USE",                   // include a file to access its contents in the current file
    "MAIN",                  // main entry point
    "LET",                   // Mutable variable and Simple Data Structures. Function with return value and User defined data types
    "CONST",                 // Immutable variable and data structure declaration
    "PB",                    // Declare variable or function as public
    "STRUCT",                // Declared s!
    "ENUM",                  // Declared e!
    "UNION",                 // Declared u!
    "PROTO",                 // Declared p!
    "ARRAY",                 // Declared a[
    "SET",                   // Declared s[
    "MAP",                   // Declared m[
    "TUPLE",                 // Declared t[
    "IDENTIFIER",            // Name given to variable, functions or any simple or user defined data types
    "CH_LITERAL",            // Fixed character value
    "STR_LITERAL",           // Fixed string value
    "NUM_LITERAL",           // Fixed number value
    "FLT_LITERAL",           // Fixed float value
       
    "DECLTKN_END",           // End of Declaration Tokens
    
    // Control Flows   
    "IF",                   // If else, if-case
    "ELIF",                 // else if
    "ELSE",                 // else and default for if-case
    "LOOP",                 // for loop, while loop, foreach
    "IN",                   // loop directive 
    "SPAN",                 // loop range
    "CONT",                 // continue statement
    "RET",                  // return statement
    "BRK",                  // break statement
    "GOTO",                 // goto label statement
    
    "CTLFTKN_END",           // End of Control Flow Tokens
	
    // Special Tokens
    "EOL",                   // End of Line token
    "EOF",                   // End of File Token
	
    "SPCTKN_END"             // End of Special Token
};


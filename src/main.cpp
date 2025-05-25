#include <iostream>
#include <cstdio>
#include <fstream>
#include <string>
#include <mutex>
#include <vector>
#include <cstring>

#include "TokenEnums.h"

/* Jandarl[01051625]: 

    For this first trial of creating a compiler, I will first try the simple
    Tree-Walk Interpreter approach and only compile 1 file at a time.

    This is more of a draft and might become a big file with a lot of lines for the time being 
    as I will put all the codes in just this cpp. I will slowly migrate it to other files as 
    I go on and understand how to make it better.

    A couple of Tags created for easer debugging:

    CTAG: Crash Tag, can potentially crash in runtime
    MTAG: Memory Leak Tag, can cause memory leaks in runtime
    DTAG: Data Tag, can cause data loss / corruption in runtime 
*/

/*----------------------ERROR HANDLING SECTION----------------------------------------*/

// This class will be the only sole responsible for any Error Handling.
// It will not have any other responsibility but handling on how errors should be processed.

// List of possible Error types
static const char *ErrorTypeString[] = {

    // All File releated errors are grouped here
    "FILE_OPEN",
    "FILE_READ",

    // Parsing releated error are grouped here
    "END_OF_FILE"

    // End of File releated errors
};

class ErrorHandling{
    
    // handle the error report
    static void report(int type, int line, std::string error){
        
        // create the buffer for the error output
        char *buffer = new char[sizeof(error) + sizeof(type) + sizeof(line) + 30];

        // format the error to print, check if line number is needed or not
        if(line > -1){
            sprintf(buffer, "ERROR ON [%s]: %s in line %i", ErrorTypeString[type], error, line);
        }
        else{
            sprintf(buffer, "ERROR ON [%s]: %s", ErrorTypeString[type], error);
        }
        
        // print the error
        printf("%s\n", buffer);
        delete[] buffer;
    }

public:

    ErrorHandling(){}
    ~ErrorHandling(){}

    // Report the error using this function
    static void reportError(int type, int line, std::string error){
        report(type, line, error);
    }
};


/*----------------------END OF ERROR HANDLING SECTION---------------------------------*/



/*----------------------FILE HANDLING SECTION-----------------------------------------*/

// This class will be the only sole responsible for any File Handling.
// It will not have any other responsibility but opening, reading, writing, closing files.

class FileHandler{

    // private both Constructor and Destructor for Singleton Instance
    FileHandler(){
        clear();
    }           

    ~FileHandler(){
        clear();
    }

    // Singleton Instance
    static FileHandler *m_psingleton;    
    
    // implement mutex for thread safety
    static std::mutex m_mutex;      
    
    // read data in byte 
    char *m_byteRead = nullptr;
    int m_readLength;

    // Clear all Data
    void clear(){
        clearBuffer();

        // CTAG: Potential Crash tag for future debugging, I may need to find another place to delete this pointer.
        delete m_psingleton;
    }
    
    // Clear Byte Buffer
    void clearBuffer(){
        if(m_byteRead != nullptr){
            delete m_byteRead;
            m_byteRead = nullptr;
        }

        m_readLength = 0;
    }

public:
    // not cloneable
    FileHandler(FileHandler &other) = delete;
    
    // not assiagnable
    void operator=(const FileHandler &) = delete;    

    // Singleton get instance
    static FileHandler* GetInstance(){
        std::lock_guard<std::mutex> lock(m_mutex);

        if(m_psingleton == nullptr){
            m_psingleton = new FileHandler();
        }
    
        return m_psingleton;
    }           

    // File Open Function
    bool openFile(const char* argv){
        bool retval = false;

        // Open the file in binary mode
        std::ifstream readFile(argv, std::ios_base::binary);

        if(readFile.is_open()){

            // Get File Length
            readFile.seekg(0, std::ios::end);
            size_t length = readFile.tellg();
            readFile.seekg(0, std::ios::beg);

            if(length > 0){
                // Set the buffer size
                clearBuffer();
                m_byteRead = new char[length];

                // Read the file and store in a character buffer
                readFile.read(m_byteRead, length);
                retval = true;
            }
            else{
                ErrorHandling::reportError(1, -1, "Failed to read the opened File, file may be empty or is corrupted");
            }

            // Close the File
            readFile.close();
        }
        else{
            ErrorHandling::reportError(0, -1, "Failed to open the File, please check if file exists or is not being used by other process");
        }

        return retval;
    }

    // Return the Read Bytes and its length from the file
    char *getReadBytes(){
        return m_byteRead;
    }

    int getBufferLength(){
        return m_readLength;
    }
};


// Instatiate singleton and mutex
FileHandler* FileHandler::m_psingleton{nullptr};
std::mutex FileHandler::m_mutex;

/*----------------------END OF FILE HANDLING SECTION-------------------------------------*/

/*---------------------------TOKEN CLASS-------------------------------------------------*/

// This class will store a token and all of its identifications / properties
class Token{
    TokenType m_type;
    std::string m_lexeme;
    int m_line;

    void clear(){
        m_type = TokenType::NUL;
        m_lexeme.clear();
        m_line = -1;
    }

public:

    Token(TokenType type, std::string lexeme, int line){
        clear();
        m_type = type;
        m_lexeme = lexeme;
        m_line = line;
    }

    ~Token(){
        clear();
    }

    std::string toString(){
         char *buffer = new char[sizeof(TokenTypeString[m_type]) + sizeof(m_lexeme) + sizeof(m_line) + 30];
         sprintf(buffer, "%s %s at line %i", TokenTypeString[m_type], m_lexeme, m_line);
         std::string retval(buffer);
         delete[] buffer;
         return retval;
    }
};


/*---------------------------END OF TOKEN CLASS------------------------------------------*/

/*---------------------------SCANNER CLASS-------------------------------------------------*/

// The scanner will work its way through the source code adding tokens until it runs out of 
// characters.

class Scanner{
    char *m_source = nullptr;
    int m_length;
    int m_start;
    int m_current;
    int m_line;
    std::vector<Token> m_tokens;

    void clearBuffer(){
        // We should not need to delete the buffer here because FileHandler will do that, just de-reference it
        // MTAG: Memory Leak tag for future debugging, I am not sure if I should still delete the pointer after nulling it, I will see later.
        m_source = nullptr;     
        m_length = 0;
    }
    

    void clear(){
        clearBuffer();

        m_tokens.clear();
        m_start = 0;
        m_current = 0;
        m_line = 1;
    }

    // Check if we have run out of characters to scan
    bool atEOF(){
        return (m_current >= m_length) ? true : false;
    }

    // Add Token to token list
    void addToken(TokenType type, char* lexeme){
        // Add the Lexeme into the tokens
        m_tokens.push_back(Token(type, lexeme, m_line));
        
        // DTAG: Data Tag, deleting this here may delete also the data pushed into the m_tokens, will check when debugging
        delete[] lexeme;
    }

    // Add the Token By Type
    void addTokenByType(TokenType type){
        // We get a the lexeme by getting the portion of the source from the current versus where it started
        int size = m_current - m_start + 1;
        char *lexeme = new char[size]; 
        memcpy(lexeme, m_source + m_start, sizeof(char) * size);

        // Add the Lexeme to the Tokens
        addToken(type, lexeme);
    }

    // Eat the next character
    char advance(){
        return m_source[m_current++];
    }

    // Peek at the next character
    char peek(){
        return m_source[m_current];
    }

    // Peek at character following the next character
    char peekNext(){
        // CTAG: I may crash here if the source is at EOF, currently return NUL is at EOF
        if(m_current + 1 >= m_length) return 0x00; 

        return m_source[m_current + 1];
    }

    // Check if Symbol Tokens are valid
    TokenType getSymbolTokenType(char c){
        TokenType retval = TokenType::SYMTKN_END;

        switch(c){
			case 0x00: retval = TokenType::NUL; break;          
			case 0x09: retval = TokenType::TAB; break;
			case 0x0A: retval = TokenType::LF; break;           
			case 0x0D: retval = TokenType::CR; break;           
			case 0x20: retval = TokenType::SPACE; break;       
			case 0x21: retval = TokenType::EXCLM; break;       
			case 0x22: retval = TokenType::QOUTE; break;       
			case 0x25: retval = TokenType::PRCNT; break;  
			case 0x26: retval = TokenType::AMP; break;         
			case 0x27: retval = TokenType::APOS; break; 
			case 0x28: retval = TokenType::LPARN; break;       
			case 0x29: retval = TokenType::RPAREN; break;            
			case 0x2A: retval = TokenType::AST; break;         
			case 0x2B: retval = TokenType::PLUS; break;        
			case 0x2C: retval = TokenType::COMMA; break;       
			case 0x2D: retval = TokenType::MINUS; break;       
			case 0x2E: retval = TokenType::PERIOD; break;    
			case 0x2F: retval = TokenType::DIVIDE; break;	
			case 0x3A: retval = TokenType::COLON; break;       
			case 0x3B: retval = TokenType::SEMI; break;        
			case 0x3C: retval = TokenType::LTHAN; break;       
			case 0x3D: retval = TokenType::EQUAL; break;       
			case 0x3E: retval = TokenType::GTHAN; break;       
			case 0x5B: retval = TokenType::LBRAK; break;       
			case 0x5D: retval = TokenType::RBRAK; break;       
			case 0x5E: retval = TokenType::CARET; break;       
			case 0x7B: retval = TokenType::LBRAC; break;       
			case 0x7C: retval = TokenType::VBAR; break;        
			case 0x7D: retval = TokenType::RBRAC; break;
			default: retval = TokenType::SYMTKN_END; break;                
		}

		return retval;
	}

    // Check if Tokens are valid expressions or a comment

    TokenType getExpressionTokenType(TokenType type){
        TokenType retval = type;

        // Check for a match of the expression
        auto match = [&](char expected){
            // Check if at end of file
            if(atEOF()) return false;

            // check if expected is the next token
            if(m_source[m_current] != expected) return false;

            m_current++;
            return true;
        };

        switch(type){
            case TokenType::EXCLM: match(0x3D) ? retval = TokenType::NOT_EQUAL : retval = type; break; 

            case TokenType::PLUS: match(0x2B) ? retval = TokenType::PLUS_PLUS : 
                                  match(0x3D) ? retval = TokenType::PLUS_EQUAL : retval = type; 
                                  break; 

            case TokenType::MINUS: match(0x2D) ? retval = TokenType::MINUS_MINUS : 
                                   match(0x3D) ? retval = TokenType::MINUS_EQUAL : retval = type; 
                                   break; 

		    case TokenType::LTHAN: match(0x3D) ? retval = TokenType::LESS_EQUAL : retval = type; break;

		    case TokenType::EQUAL: match(0x3D) ? retval = TokenType::EQUAL_EQUAL : retval = type; break;

		    case TokenType::GTHAN: match(0x3D) ? retval = TokenType::GREAT_EQUAL : retval = type; break;

            case TokenType::DIVIDE: match(0x2A) ? retval = TokenType::COMMENT_BEG : retval = type; break;

            case TokenType::AST: match(0x2F) ? retval = TokenType::COMMENT_END : retval = type; break;

            default: retval = type; break;
        }

        return retval;
    }

    // Discard the comment block, since comments do not matter in compilation
    void discardCommentBlock(){
        TokenType tkn = TokenType::COMMENT_BEG;

        while(tkn != TokenType::COMMENT_END && !atEOF()){
            tkn = getSymbolTokenType(advance());

            // If the symbol is an *, let's check if it is the end of the comment
            if(tkn == TokenType::AST){
                tkn = getExpressionTokenType(tkn);

                // Break when we find the end of comment
                if(tkn == TokenType::COMMENT_END){
                    break;
                }
            }
        } 
    }

    // If its a string literal, eat the rest of the part of the string
    void eatString(){
        TokenType tkn = TokenType::QOUTE;

        // Lets get the first character in the string and check it       
        tkn = getSymbolTokenType(advance());

        // Let's eat the tokens until we find the end of the string
        while (tkn != TokenType::QOUTE && !atEOF){
            if(getSymbolTokenType(peek()) == TokenType::LF) m_line++;
          
            // Let's eat the token
           advance();

           // Let's peek the next token
           tkn = getSymbolTokenType(peek());
        }

        if(atEOF()) {
            ErrorHandling::reportError(2, m_line, "String literal was unterminated!");
            return;
        }

        // Let's eat the ending quote
        advance();

        // We get a the string literal by getting the portion of the source from the current versus where it started
        int size = (m_current - 1) - (m_start + 1);  // This is to discard the quotations
        char *lexeme = new char[size]; 
        memcpy(lexeme, m_source + m_start + 1, sizeof(char) * size); // +1 to discard the opening quotation

        // Add the Lexeme to the Tokens
        addToken(TokenType::STR_LITERAL, lexeme);
    }

    // If its a Number Literal eat the rest of the number
    void eatNumber(){
        // If the token is a digit or a period with a digit next to it, eat the tokens
        while(isDigit(peek()) && (peek() == 0x2E && isDigit(peekNext()))) advance();

        // We get a the lexeme by getting the portion of the source from the current versus where it started
        int size = m_current - m_start + 1;
        char *lexeme = new char[size]; 
        memcpy(lexeme, m_source + m_start, sizeof(char) * size);

        // Add the Lexeme to the Tokens
        addToken(TokenType::NUM_LITERAL, lexeme);
    }

    // Scan the token
    void scanToken(){     
        // Check if Token is valid and get it
        TokenType tkn = getSymbolTokenType(advance());

        // Check if Token is an expression or comment
        tkn = getExpressionTokenType(tkn);

        switch(tkn){
            // If the Token is a commen begining block, discard it
            case TokenType::COMMENT_BEG: discardCommentBlock(); break;

            // Ignore all whitespace Tokens
            case TokenType::SPACE:
            case TokenType::CR:
            case TokenType::TAB:
                            break;

            // New line we increase line count
            case TokenType::LF: m_line++; break;

            // String Literal
            case TokenType::STR_LITERAL: eatString(); break;

            // Number Literal
            case TokenType::NUM_LITERAL: eatNumber(); break;

        }  
    }

public:
    Scanner(char *source, int length){
        m_source = source;
        m_length = length;
    }
};

/*---------------------------END OF SCANNER CLASS------------------------------------------*/

int main(int argc, const char* argv[]){
  
    if(sizeof(argc) > 1){
        FileHandler::GetInstance()->openFile(argv[1]);
    }

    return 0;
}
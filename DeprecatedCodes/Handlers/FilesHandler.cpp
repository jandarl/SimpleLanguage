#include "FilesHandler.h"

FilesHandler* FilesHandler::m_psingleton{nullptr};
mutex FilesHandler::m_mutex;

FilesHandler::FilesHandler(){
    clear();
}

FilesHandler::~FilesHandler(){
    clear();
}

void FilesHandler::clear(){
    m_file_stack = {};
    m_file_compiled = {};
    m_source.clear();
    m_destination.clear();
}

FilesHandler* FilesHandler::GetInstance(){
    lock_guard<mutex> lock(m_mutex);

    if(m_psingleton == nullptr){
        m_psingleton = new FilesHandler();
    }

    return m_psingleton;
}

void FilesHandler::SetDestination(string destination){
    m_destination = destination;
}   

bool FilesHandler::FileOpen(string file_path, string file_name){
    m_source = file_path;

    /*
        This section will be revisted later as this will need a recursive lexer for the "use" token
        Current Idea:

        1) The current file will be openned and will be parsed and lexed
        2) If a file has "use" token, the file will be saved into the stack and then the file directed by the token "use" will be opened
        3) This will emulate a pseudo depth first search, where we will jump deeper into the file until we reach the deepest file with no "use" token
        4) When the GetNextFileFromStack is called, it will return the one in the top of the stack meaning the deepest file found 
        5) When the compile success is called, we save the file to the compiled file sets, the we pop the stack to remove the file
        6) We then peek on the next file and check if it has any other "use" token that is not yet compiled
        7) If we find another "use" token inside the peeked next file, we will update the stack and jump deeper until we find the last file
            just like how we did it on the previous search
        8) This way, we will not proceed and compile a higher layer of file until everything underneath is done  
    */
}   

string FilesHandler::GetNextFileFromStack(){
    return m_file_stack.top();
}   

string FilesHandler::GetDestination(){
    return m_destination;
}                                          

void FilesHandler::CompileFailed(){
    clear();
}   

void FilesHandler::CompileSuccess(){
    m_file_compiled.insert(m_file_stack.top());                   // Get the file and add it to the compiled files
    m_file_stack.pop();                                           // Remove file from stack

    string _peek_next = m_file_stack.top();                       // Peek Next file

    /*
      - Additional functions will also be added here when the lexer has been done refer to FileOpen function for details
      - We will open the peeked file to check for any other "use" token that contains a file that has not yet been compiled
      - Do recurssion again and update stack if another "use" token is found
    */
}    
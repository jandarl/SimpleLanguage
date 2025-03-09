#include <string>
#include <stack>
#include <set>

#include <mutex>
using namespace std;

class FilesHandler{
    stack<string> m_file_stack;                 // This is where we store the stack of files we will compile
                                                // LIFO because we need to compile the file under "use" first before compiling the main file

    set<string> m_file_compiled;                // This is where we store the compiled files to avoid compiling a file twice if it was 
                                                // "use" in multiple files

    string m_source;                            // The source folder of the main entry point (main.spl)
    string m_destination;                       // The destination folder of the compiled files

    FilesHandler();                             // private both Constructor and Destructor for Singleton Instance
    ~FilesHandler();

    static FilesHandler *m_psingleton;          // Singleton Instance
    static mutex m_mutex;                       // implement mutex for thread safety

    void clear();                               // Clear all Data

public:
    FilesHandler(FilesHandler &other) = delete;       // not cloneable
    void operator=(const FilesHandler &) = delete;    // not assiagnable

    static FilesHandler* GetInstance();               // Singleton get instance

    // Setters
    void SetDestination(string destination);          // Set the destination folder for the compiled files
    bool FileOpen(string file_path, string file_name = "main.spl");     // open the file to be compiled, default is the main entry file

    // Getters
    string GetNextFileFromStack();                                      // Retrieve the next file to be compiled from the stack
    string GetDestination();                                            // Get the Destination Folder

    // Command the File Handle to do its routine
    void CompileFailed();                                               // Compile Failed, do routine if compile has failed
    void CompileSuccess();                                              // Compile Succeeded, do routine if compile has succeed

};
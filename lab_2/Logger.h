#include <fstream>
#include <string>

using namespace std;

class Logger {
private:
    ofstream logFile;
    
public:
    Logger();
    ~Logger();
    void log(const string& text);
};

extern Logger logger;
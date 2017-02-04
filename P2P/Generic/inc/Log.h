#ifndef LOG_MODULE
#define LOG_MODULE

#include <fstream>

class Logger
{
	private:
		int logLevel;
		std::ofstream outfile;
	    static Logger *single;
	    Logger(int);
	public:
	    static Logger* getInstance(int outLevel);
	    void Log(std::string& , int lvl);
	    void Log(const char * , int lvl);
	    ~Logger();
};
#endif
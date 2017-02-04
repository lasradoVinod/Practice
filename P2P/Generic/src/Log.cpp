#include <iostream>
#include <fstream>
#include <sys/stat.h>
#include "Log.h" 
#include <cerrno>
#include <cstdlib>

Logger:: Logger(int outLevel)
{
	this->logLevel = outLevel;
	const int dir_err = mkdir("Log", S_IRWXU | S_IRWXG | S_IROTH | S_IXOTH);
	if (-1 == dir_err && errno != EEXIST)
	{
    	std::cout << "Cannot create directory for log. Terminating application\n";
	}

	outfile.open("./Log/log.txt");
}

Logger:: ~Logger()
{
	outfile.close();
}

Logger* Logger:: getInstance(int outLevel)
{
	return new Logger(outLevel);
}


void Logger:: Log(std::string& p, int lvl)
{
	if(lvl < 0)
	{
		std::cerr << p << std::endl;
		outfile << "ERROR:" << p << std::endl;
		std::exit(1);
	}
	else 
	{
		outfile << "LOG:" << p << std::endl;		
	}

	if(lvl <logLevel)
	{
		std::cout << p << std::endl;
	}
}

void Logger:: Log(const char* p, int lvl)
{
	if(lvl < 0)
	{
		std::cerr << p << std::endl;
		outfile << "ERROR:" << p << std::endl;
		std::exit(1);
	}
	else 
	{
		outfile << "LOG:" << p << std::endl;		
	}

	if(lvl > logLevel)
	{
		std::cout << p << std::endl;
	}
}
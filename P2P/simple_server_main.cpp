#include "ServerSocket.h"
#include "Exception.h"
#include <string>
#include <iostream>
#include "Log.h"

int main ( void )
{
  std::cout << "running....\n";

  Logger* p = Logger:: getInstance(0);

  std::string str;
  try
    {
      // Create the socket
      ServerSocket server ( 30000 );

      p->Log("Server Created",10);

      while ( true )
	{

	  ServerSocket new_sock;
	  server.accept ( new_sock );

	  try
	    {
	      while ( true )
		{
		  std::string data;
		  new_sock >> data;
		  new_sock << data;
		}
	    }
	  catch ( Exception& ) {}

	}
    }
  catch ( Exception& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\nExiting.\n";
    }

  return 0;
}


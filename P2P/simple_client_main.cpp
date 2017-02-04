#include "ClientSocket.h"
#include "Exception.h"
#include <iostream>
#include <string>

int main (void)
{
  try
    {

      ClientSocket client_socket ( "localhost", 30000 );

      std::string reply;

      try
	{
	  client_socket << "Test message.";
	  client_socket >> reply;
	}
      catch ( Exception& ) {}

      std::cout << "We received this response from the server:\n\"" << reply << "\"\n";;

    }
  catch ( Exception& e )
    {
      std::cout << "Exception was caught:" << e.description() << "\n";
    }

  return 0;
}


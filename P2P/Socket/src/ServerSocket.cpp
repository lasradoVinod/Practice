// Implementation of the ServerSocket class

#include "ServerSocket.h"
#include "Exception.h"


ServerSocket::ServerSocket ( int port )
{
  if ( ! Socket::create() )
    {
      throw Exception ( "Could not create server socket.",-1 );
    }

  if ( ! Socket::bind ( port ) )
    {
      throw Exception ( "Could not bind to port.",1 );
    }

  if ( ! Socket::listen() )
    {
      throw Exception ( "Could not listen to socket.",-1 );
    }

}

ServerSocket::~ServerSocket()
{
}


const ServerSocket& ServerSocket::operator << ( const std::string& s ) const
{
  if ( ! Socket::send ( s ) )
    {
      throw Exception ( "Could not write to socket.", -1);
    }

  return *this;

}


const ServerSocket& ServerSocket::operator >> ( std::string& s ) const
{
  if ( ! Socket::recv ( s ) )
    {
      throw Exception ( "Could not read from socket.",-1 );
    }

  return *this;
}

void ServerSocket::accept ( ServerSocket& sock )
{
  if ( ! Socket::accept ( sock ) )
    {
      throw Exception ( "Could not accept socket.",-1 );
    }
}


// Implementation of the ClientSocket class

#include "ClientSocket.h"
#include "Exception.h"


ClientSocket::ClientSocket ( std::string host, int port )
{
  if ( ! Socket::create() )
    {
      throw Exception ( "Could not create client socket.",-1 );
    }

  if ( ! Socket::connect ( host, port ) )
    {
      throw Exception ( "Could not bind to port.",-1 );
    }

}


const ClientSocket& ClientSocket::operator << ( const std::string& s ) const
{
  if ( ! Socket::send ( s ) )
    {
      throw Exception ( "Could not write to socket.",-1 );
    }

  return *this;

}


const ClientSocket& ClientSocket::operator >> ( std::string& s ) const
{
  if ( ! Socket::recv ( s ) )
    {
      throw Exception ( "Could not read from socket.",-1 );
    }

  return *this;
}

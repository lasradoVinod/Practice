#ifndef FILE_SERVER
#define FILE_SERVER

#define REGISTER_REQUEST			1u
#define REGISTER_REPLY				2u
#define FILE_LIST_REQUEST			3u
#define FILE_LIST_REPLY				4u
#define FILE_LOCATION_REQUEST			5u
#define FILE_LOCATION_REPLY			6u
#define LEAVE_REQUEST				7u
#define LEAVE_REPLY				8u

class FileServer
{
	private:
	struct infoFile
	{
		int size;
		std::String address;
		int port;
	};
	map <String,struct infoFile> fileList;

	int registerRequest(String&);
	int fileListRequest(String&);
	int fileLocationRequest(String&);
	int leaveRequest(String&);

	public:
	static String process (String&);
};
#endif

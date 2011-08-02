#include <iostream>
#include <string>
#include <sstream>

#define WIN32_MEAN_AND_LEAN
#include <winsock2.h>
#include <windows.h>

#include "SocketServer.h"

using namespace std;


const int  REQ_WINSOCK_VER   = 2;	// Minimum winsock version required
const int  DEFAULT_PORT      = 6666;	
const int  TEMP_BUFFER_SIZE  = 128;

//-------globals
SOCKET 		hSocket = INVALID_SOCKET;
SOCKET		hClientSocket = INVALID_SOCKET;
bool		bSuccess = true;
sockaddr_in	sockAddr = {0};





class ROTException
{
public:
    ROTException() :
         m_pMessage("") {}
    virtual ~ROTException() {}
    ROTException(const char *pMessage) :
         m_pMessage(pMessage) {}
    const char * what() { return m_pMessage; }
private:
    const char *m_pMessage;
};


string gethostdescription(const sockaddr_in &sockaddr)
{
	ostringstream stream;
	stream << inet_ntoa(sockaddr.sin_addr) << ":" << ntohs(sockaddr.sin_port);
	return stream.str();
}

void SetServerSockAddr(sockaddr_in *pSockAddr, int portNumber)
{
	// Set family, port and find IP
	pSockAddr->sin_family = AF_INET;
	pSockAddr->sin_port = htons(portNumber);
	pSockAddr->sin_addr.S_un.S_addr = INADDR_ANY;
}

////void rot13(char *pBuffer, int size)
////{
////	for(int i=0;i<size;i++)
////	{
////		char c = pBuffer[i];
////		if ((c >= 'a' && c < 'n') || (c >= 'A' && c < 'N') )
////			c += 13;
////		else if ((c>='n' && c <= 'z') || (c>='N' && c <= 'Z'))
////			c -= 13;
////		else
////			continue;
////		pBuffer[i] = c;
////	}
////}
//
//void HandleConnection(SOCKET hClientSocket, const sockaddr_in &sockAddr, char* frameData)
//{
//	// Print description (IP:port) of connected client
//	cout << "Connected with " << GetHostDescription(sockAddr) << ".\n";
//
//	char tempBuffer[TEMP_BUFFER_SIZE];
//
//	// Read data
//	while(true)
//	{
//		int retval;
//		retval = recv(hClientSocket, tempBuffer, sizeof(tempBuffer), 0);
//		if (retval==0)
//		{ 
//			break; // Connection has been closed
//		}
//		else if (retval==SOCKET_ERROR)
//		{
//			throw ROTException("socket error while receiving.");
//		}
//		else
//		{
//			/* retval is the number of bytes received.
//			   rot13 the data and send it back to the client */
//			/*rot13(tempBuffer, retval);
//			if (send(hClientSocket, tempBuffer, retval, 0)==SOCKET_ERROR)
//				throw ROTException("socket error while sending.");*/
//			if (send(hClientSocket, frameData, sizeof(frameData), 0) == SOCKET_ERROR)
//				throw ROTException("socket error while sending.");
//		}
//	}
//	cout << "Connection closed.\n";
//}
//
////------------ run socket server --------------
//
//bool RunServer(int portNumber)
//{
//	//SOCKET 		hSocket = INVALID_SOCKET,
//	//			hClientSocket = INVALID_SOCKET;
//	//bool		bSuccess = true;
//	//sockaddr_in	sockAddr = {0};
//	
//	try
//	{
//		// Create socket
//		cout << "Creating socket... ";
//		if ((hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
//			throw ROTException("could not create socket.");
//		cout << "created.\n";
//		
//		// Bind socket
//		cout << "Binding socket... ";
//		SetServerSockAddr(&sockAddr, portNumber);
//		if (bind(hSocket, reinterpret_cast<sockaddr*>(&sockAddr), sizeof(sockAddr))!=0)
//			throw ROTException("could not bind socket.");
//		cout << "bound to port: " << portNumber << endl;
//
//		// Put socket in listening mode
//		cout << "Putting socket in listening mode... ";
//		if (listen(hSocket, SOMAXCONN)!=0)
//			throw ROTException("could not put socket in listening mode.");
//		cout << "done.\n";
//
//		//// Wait for connection
//		//cout << "Waiting for incoming connection... ";
//		//
//		//sockaddr_in clientSockAddr;
//		//int			clientSockSize = sizeof(clientSockAddr);
//		//
//		//// Accept connection:
//		//hClientSocket = accept(hSocket,
//		//				 reinterpret_cast<sockaddr*>(&clientSockAddr),
//		//				 &clientSockSize);
//	
//		//// Check if accept succeeded
//		//if (hClientSocket==INVALID_SOCKET)
//		//	throw ROTException("accept function failed.");
//		//cout << "accepted.\n";
//	
//		//// Wait for and accept a connection:
//		//HandleConnection(hClientSocket, clientSockAddr);
//
//	}
//	catch(ROTException e)
//	{
//		cerr << "\nError: " << e.what() << endl;
//		bSuccess = false; 
//	}
//
//	//if (hSocket!=INVALID_SOCKET)
//	//	closesocket(hSocket);
//	//
//	//if (hClientSocket!=INVALID_SOCKET)
//	//	closesocket(hClientSocket);
//		
//	return bSuccess;
//}	

//-------------- interface ----------------

int initSocket() {

	int iRet = 1;
	WSADATA wsaData;

	cout << "Initializing winsock... ";

	if (WSAStartup(MAKEWORD(REQ_WINSOCK_VER,0), &wsaData)==0)
	{
		// Check if major version is at least REQ_WINSOCK_VER
		if (LOBYTE(wsaData.wVersion) >= REQ_WINSOCK_VER)
		{
			cout << "initialized.\n";
			iRet = 0;
			int portNumber = DEFAULT_PORT;
			//---------------------
			//iRet = !RunServer(port);
			//SOCKET 		hSocket = INVALID_SOCKET,
			//			hClientSocket = INVALID_SOCKET;
			//bool		bSuccess = true;
			//sockaddr_in	sockAddr = {0};

			try
			{
				// Create socket
				cout << "Creating socket... ";
				if ((hSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP)) == INVALID_SOCKET)
					throw ROTException("could not create socket.");
				cout << "created.\n";

				// Bind socket
				cout << "Binding socket... ";
				SetServerSockAddr(&sockAddr, portNumber);
				if (bind(hSocket, reinterpret_cast<sockaddr*>(&sockAddr), sizeof(sockAddr))!=0)
					throw ROTException("could not bind socket.");
				cout << "bound to port: " << portNumber << endl;

				// Put socket in listening mode
				cout << "Putting socket in listening mode... ";
				if (listen(hSocket, SOMAXCONN)!=0)
					throw ROTException("could not put socket in listening mode.");
				cout << "done.\n";

				// Wait for connection
				std::cout << "Waiting for incoming connection... \n";

				// Accept connection:
				std::cout << hSocket << std::endl;
				hClientSocket = accept(hSocket, NULL, NULL);

				// Check if accept succeeded
				if (hClientSocket==INVALID_SOCKET) 
					throw ROTException("accept function failed.");
				std::cout << "accepted.\n";

				//// Wait for connection
				//cout << "Waiting for incoming connection... ";
				//
				//sockaddr_in clientSockAddr;
				//int			clientSockSize = sizeof(clientSockAddr);
				//
				//// Accept connection:
				//hClientSocket = accept(hSocket,
				//				 reinterpret_cast<sockaddr*>(&clientSockAddr),
				//				 &clientSockSize);

				//// Check if accept succeeded
				//if (hClientSocket==INVALID_SOCKET)
				//	throw ROTException("accept function failed.");
				//cout << "accepted.\n";

				//// Wait for and accept a connection:
				//HandleConnection(hClientSocket, clientSockAddr);

			} catch(ROTException e)	{
				cerr << "\nError: " << e.what() << endl;
				bSuccess = false; 
			}

			//if (hSocket!=INVALID_SOCKET)
			//	closesocket(hSocket);
			//
			//if (hClientSocket!=INVALID_SOCKET)
			//	closesocket(hClientSocket);

		} else {
			cerr << "required version not supported!";
		}

		//cout << "Cleaning up winsock... ";

		//// Cleanup winsock
		//if (WSACleanup()!=0)
		//{
		//	cerr << "cleanup failed!\n";
		//	iRet = 1;
		//}   
		//cout << "done.\n";
	} else {
		cerr << "startup failed!\n";
	}
	return iRet;

}
//
//
//
//int closeSocket() {
//
//	int iRet = 0;
//	cout << "Cleaning up winsock... ";
//
//	if (WSACleanup()!=0)
//	{
//		cerr << "cleanup failed!\n";
//		iRet = 1;
//	}   
//	cout << "done.\n";
//	
//	return iRet;
//
//}


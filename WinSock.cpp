#include "stdafx.h"
#include <iostream>
#include <winsock2.h>
#include <string>
#include <fstream>
using namespace std;
HINSTANCE steam;
void Check_Status(string);
string Get_End(string);

string get_source(string insert)
{
	WSADATA WSAData;
	WSAStartup(MAKEWORD(2, 0), &WSAData);

	SOCKET sock;
	SOCKADDR_IN sin;

	char buffer[1024];

	////////////////This is portion that is confusing me//////////////////////////////////////////////////
	string srequete = "GET ";
	srequete += insert;
	srequete += " HTTP/1.1\r\n";
	srequete += "Host: steamcommunity.com\r\n";
	srequete += "Connection: close\r\n";
//	srequete += "Accept: text/xml,application/xml,application/xhtml+xml,text/html;q=0.9,text/plain;q=0.8,image/png,*/*;q=0.5\r\n";
//	srequete += "Accept-Language: fr,fr-fr;q=0.8,en-us;q=0.5,en;q=0.3\r\n";
//	srequete += "Accept-Charset: ISO-8859-1,utf-8;q=0.7,*;q=0.7\r\n";
//	srequete += "User-Agent: Mozilla/5.0 (Windows; U; Windows NT 5.1; fr; rv:1.8.1.3) Gecko/20070309 Firefox/2.0.0.3\r\n";
//	srequete += "Referer: http://pozzyx.net/\r\n";
	srequete += "\r\n\r\n";
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	size_t requete_taille = srequete.size() + 1;

	char crequete[80000];
	strncpy(crequete, srequete.c_str(), requete_taille);

	int i = 0;
	string source = "";

	sock = socket(AF_INET, SOCK_STREAM, 0);

	sin.sin_addr.s_addr = inet_addr("63.228.223.103"); // epguides.com //why wont it work for 72.233.89.200 (whatismyip.com)
	sin.sin_family = AF_INET;
	sin.sin_port = htons(80); // port HTTP.

	connect(sock, (SOCKADDR *)&sin, sizeof(sin)); // on se connecte sur le site web.
	send(sock, crequete, strlen(crequete), 0); // why do we send the string??


	do
	{
		i = recv(sock, buffer, sizeof(buffer), 0); // le buffer récupère les données reçues.
		source += buffer;
	} while (i != 0);


	closesocket(sock); // on ferme le socket.
	WSACleanup();

	return source;
}

void main()
{
	string contents;
	string line;

	ifstream myfile("profiles.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << Get_End(line) << "  --->> ";

			contents = get_source(line);
			Check_Status(contents);
			cout << endl;

		}
		myfile.close();
	}
	

	ofstream fout;
	fout.open("Buffer.txt");
	fout << get_source(line); // the string url doesnt matter
	fout.close();
	system("PAUSE");
}

void Check_Status(string contents)
{
	size_t found,position;
	string ip;
	
	string status[3] = { "Currently Online", "Currently In-Game", "Offline" };
	for (int i = 0; i < 3; i++)
	{
		found = contents.find(status[i]);
		if (found != std::string::npos){    //until end of string
			cout << status[i] << endl;

			found = contents.find("Join Game");                      //if Join Game is displayed
			if (i == 1 && found != std::string::npos)
			{

				cout << "YAYA!" << endl;
				found = contents.find("steam://connect/");         //finds position of this text
				cout << found << endl;
				ip = contents.substr(found, contents.length() - 1);        //ip is set to contain text "steam" to end of file
				position = ip.find(" ");                                 //sets position to end of IP address
				ip = contents.substr(found, position);                    // sets "ip" to whole line
				cout << ip << endl;

				 char *path = strdup(ip.c_str());         //convert to LPCSTR

				steam = ShellExecuteA(0, "open", path, "", NULL, SW_SHOW);                        // hwnd

			}

		}
	}
}

string Get_End(string line)
{
	size_t found = line.find(".com");
	if (found != string::npos)
		line = line.substr(found+4, line.length() - 1);


		return line;
}
























//#include <windows.h>
//#include <wininet.h>
//#include <iostream>
//#include <string>
//#include <stdio.h>
//#include <stdlib.h>
//using namespace std;
//
//#pragma comment ( lib, "Wininet.lib" )
//
//int main()
//{
//	HINTERNET hInternet = InternetOpenA("InetURL/1.0", INTERNET_OPEN_TYPE_PRECONFIG, NULL, NULL, 0);
//
//	HINTERNET hConnection = InternetConnectA(hInternet, "google.com", 80, " ", " ", INTERNET_SERVICE_HTTP, 0, 0);
//
//	HINTERNET hData = HttpOpenRequestA(hConnection, "GET", "/", NULL, NULL, NULL, INTERNET_FLAG_KEEP_CONNECTION, 0);
//
//	char buf[2048];
//	string lol;
//	HttpSendRequestA(hData, NULL, 0, NULL, 0);
//
//	DWORD bytesRead = 0;
//	DWORD totalBytesRead = 0;
//	// http://msdn.microsoft.com/en-us/library/aa385103(VS.85).aspx
//	// To ensure all data is retrieved, an application must continue to call the
//	// InternetReadFile function until the function returns TRUE and the
//	// lpdwNumberOfBytesRead parameter equals zero. 
//	while (InternetReadFile(hData, buf, 2000, &bytesRead) && bytesRead != 0)
//	{
//		buf[bytesRead] = 0; // insert the null terminator.
//
//		puts(buf);          // print it to the screen.
//		lol = lol + buf;
//
//		printf("%d bytes read\n", bytesRead);
//
//		totalBytesRead += bytesRead;
//	}
//
//	printf("\n\n END -- %d bytes read\n", bytesRead);
//	printf("\n\n END -- %d TOTAL bytes read\n", totalBytesRead);
//
//	InternetCloseHandle(hData);
//	InternetCloseHandle(hConnection);
//	InternetCloseHandle(hInternet);
//
//	cout << "\nThe beginning." << endl << endl << endl;
//
//	cout << lol << endl;
//
//
//	system("PAUSE");
//}

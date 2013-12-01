//Add winsock2.h & fstream.h to beginning of file


class SteamLogger
{
private:
	HINSTANCE steam;
public:
        
    #pragma warning (disable : 4996)     //Add to beginning of file
	string SteamLogger::get_source(string insert)
	{
		{
			WSADATA WSAData;
			WSAStartup(MAKEWORD(2, 0), &WSAData);

			SOCKET sock;
			SOCKADDR_IN sin;

			char buffer[1024];

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
	}

	void SteamLogger::Check_Status(string contents)
	{

		size_t found, position;
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

	string SteamLogger::Get_End(string line)
	{
		size_t found = line.find(".com");
		if (found != string::npos)
			line = line.substr(found + 4, line.length() - 1);


		return line;
	}

	void SteamLogger::Output()
	{
		string contents;
		string line;

		ofstream fout;
		fout.open("Buffer.txt"); // the string url doesnt matter


		ifstream myfile("profiles.txt");
		if (myfile.is_open())
		{
			while (getline(myfile, line))
			{
				cout << Get_End(line) << "  --->> ";

				contents = get_source(line);
				fout << contents << endl;
				Check_Status(contents);
				cout << endl;

			}
			myfile.close();
		}
		fout.close();


	}


};

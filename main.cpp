// 
// curltest.cpp 
//


#pragma warning (disable : 4996)



#include <iostream>
#include <string>
#include <curl/curl.h>
#include <fstream>

using namespace std;
void function(string);
void Start_Steam();
HINSTANCE steam;



static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}



int main(void)
{

	string line;
	char* troll;
	ifstream myfile("profiles.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{
			cout << line << endl;
			function(line);
		}
		myfile.close();
	}


	system("PAUSE");

	return 0;
}

void function(string line)
{

	CURL *curl;
	CURLcode res;
	size_t found;
	std::string contents;
	size_t position, space;
	string ip;

	curl = curl_easy_init();
	if (curl) {

		char *result = strdup(line.c_str());


		curl_easy_setopt(curl, CURLOPT_URL, result);
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
		curl_easy_setopt(curl, CURLOPT_WRITEDATA, &contents);  // sets user arguments
		res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);



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

					steam = ShellExecute( // WinExec is obsolete.
						0,    // hwnd
						"open",          // operation/verb.
						path,  // path to steam (external protocol request)
						"",        // parameters.
						NULL,            // directory
						SW_SHOW);       // how to be displayed 


					ofstream batch;
					batch.open("Launch.bat");
					batch << "@echo\n" << "\"C:\\Program Files (x86)\\Steam\\steam.exe\" -applaunch 440 +connect " << ip << endl;
					batch.close();
				//	system("Launch.bat");
				}

			}
		}
	}


}


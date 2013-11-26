// 
// curltest.cpp 
//


#pragma warning (disable : 4996)



#include <iostream>
#include <string>
#include <curl/curl.h>
#include <vector>
#include <fstream>

using namespace std;


static size_t WriteCallback(void *contents, size_t size, size_t nmemb, void *userp)
{
	((std::string*)userp)->append((char*)contents, size * nmemb);
	return size * nmemb;
}

void function(string);

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

curl = curl_easy_init();
if (curl) {

	char *result = strdup(line.c_str());


	curl_easy_setopt(curl, CURLOPT_URL, result);
	curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, WriteCallback);
	curl_easy_setopt(curl, CURLOPT_WRITEDATA, &contents);
	res = curl_easy_perform(curl);
	curl_easy_cleanup(curl);



	string status[3] = { "Currently Online", "Currently In-Game", "Offline" };
	for (int i = 0; i < 3; i++)
	{
		found = contents.find(status[i]);
		if (found != std::string::npos){
			cout << status[i] << endl;
		}
	}
	/**
	found = contents.find("Currently Online");
	if (found != std::string::npos){
		cout << "Currently Online!" << endl;
	}
	found = contents.find("Currently In-Game");
	if (found != std::string::npos){
		cout << "Currently In-Game!" << endl;
	}
	found = contents.find("Offline");
	if (found != std::string::npos){
		cout << "Currently Offline!" << endl;
	}
	else
		cout << "NAH!!!" << endl;
	**/


}
}


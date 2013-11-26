#include <iostream>
#include <string>
#include <fsttream>
using namespace std;




int main(int argc, char *argv[])
{
	string line;
	ifstream myfile("profiles.txt");
	if (myfile.is_open())
	{
		while (getline(myfile, line))
		{ 
			Get_Html(line);
		}
		myfile.close();
	}
	
	system("PAUSE");
	return 0;

}

void Get_Html(string link)
{
	size_t found;
	CURL* curl = curl_easy_init();
	if (curl)
	{
		// Tell libcurl the URL 
		curl_easy_setopt(curl, CURLOPT_URL, link);
		// Tell libcurl what function to call when it has data 
		curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION,);
		// Do it! 
		CURLcode res = curl_easy_perform(curl);
		curl_easy_cleanup(curl);

		if (res == 0)
		{
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
		}

		else
			cerr << "Error: " << res << endl;
	}

}

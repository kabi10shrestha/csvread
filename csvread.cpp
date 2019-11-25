#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

int main(int argc, char* argv[]) {
	string filedata;
	int pos = 0;
	vector<string> headers;
	vector<string> dbdata;
	vector<string> temp_data;
	
	ifstream inFile("example.csv");
	if (argc != 2) {
		cout << "Required parameter missing.\n"; return 1;
	}
	if (!inFile) { cout << "Error in opening file.\n"; return 1; }
	getline(inFile, filedata);
	size_t found = filedata.find(",");
	while (found != string::npos) {
		headers.push_back(filedata.substr(pos, (found-pos)));
		pos = (found + 1);
		found = filedata.find(",", pos+1);
	}
	headers.push_back(filedata.substr(pos));

	while (!inFile.eof()) {
		getline(inFile, filedata);
		dbdata.push_back(filedata);
	}
	inFile.close();

	/*for (int i = 0; i < headers.size(); i++)
		cout << headers.at(i) << " ";
	for (int i = 0; i < dbdata.size(); i++)
		cout << dbdata.at(i) << endl;
	*/
	
	string header_search;
	string find_header = argv[1];
	size_t foundeq = find_header.find("=");
	string header_match = find_header.substr(0, foundeq);
	string para_match = find_header.substr(foundeq + 1);
	if (foundeq != string::npos)
		header_search = header_match;
	else
		header_search = find_header;
	   
	for (int i = 0; i < headers.size(); i++) {
		if (headers[i] == header_search) {
			cout << "Found Header: " << headers.at(i) << endl;
			for (int j = 0; j < dbdata.size(); j++) {
				size_t found = dbdata[j].find(",");
				int pos1 = 0;
				while (found != string::npos) {
					temp_data.push_back(dbdata[j].substr(pos1, (found - pos1)));
					pos1 = (found + 1);
					found = dbdata[j].find(",", pos1 + 1);
				}
				temp_data.push_back(dbdata[j].substr(pos1));
				if (temp_data[i] == para_match) {
					for (int k = 0; k < temp_data.size(); k++)
						cout << temp_data.at(k) << ", ";
					cout << endl;
				}
				if (foundeq == string::npos)
					cout << temp_data[i] << endl;
				temp_data.clear();
			}
		}
	}
			
	system("pause");
	return 0;
}


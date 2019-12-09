// Copyright 2019 <Kabi Shrestha>
#include <iostream>
#include <string>
#include <vector>
#include <fstream>

using namespace std;

/** brief csvtovector - input of csv string split into vector
 *
 * param string n csv string with '"' included
 * "1,101,Alan Smith,\"Austin, Texas\",77,hello"
 * return vector<string>
 */
vector<string> csvtovector(string n) {
    int pos = 0;
    vector<string> csv_vector;
    if (n[pos] == '\"') {  // special case where first element starts with '"'
        pos = (n.find("\"", pos + 1) + 1);
        csv_vector.push_back(n.substr(0, pos));
        pos += 1;
    }
    size_t found = n.find(",", pos);
    while (found != string::npos) {
        // cout << n.substr(pos, (found - pos)) << endl;
        csv_vector.push_back(n.substr(pos, (found - pos)));
        pos = (found + 1);
        if (n[pos] == '\"') {
            found = n.find("\"", pos + 1);
            csv_vector.push_back(n.substr(pos, ((found + 1) - pos)));
            pos = found + 2;
        }
        found = n.find(",", pos + 1);
    }
    csv_vector.push_back(n.substr(pos));
    return csv_vector;
}
/** brief print_matching_column - uses input header name and prints specific column from csv data
 *
 * param column_name header column to be printed from each csv data
 * param headers contains header names
 * param dbdata contains database data lines
 * if header name does not match then nothing is printed
 *
 */
void print_matching_column(string column_name,
                           vector<string> headers, vector<string> dbdata) {
    for (int i = 0; i < headers.size(); i++) {
        if (headers[i] == column_name) {
            cout << "Found Header: " << headers.at(i) << endl;
            for (int j = 0; j < dbdata.size(); j++) {
                vector<string> dbline = csvtovector(dbdata[j]);
                cout << dbline[i] << endl;
            }
        }
    }
}

/** brief print_matching_row - uses input header name and value to print matching csv data rows
 *
 * param column_name header column to be matched from each csv data
 * param column_value value to be matched in data line
 * param headers contains header names
 * param dbdata contains database data lines
 * if header name does not match then nothing is printed
 *
 */
void print_matching_row(string column_name, string column_value,
	                    vector<string> headers, vector<string> dbdata) {
    for (int i = 0; i < headers.size(); i++) {
        if (headers[i] == column_name) {
            cout << "Found Header: " << headers.at(i) << endl;
            for (int j = 0; j < dbdata.size(); j++) {
                vector<string> dbline = csvtovector(dbdata[j]);
                if (column_value == dbline[i]) {
                    cout << dbdata[j] << endl;
                }
            }
        }
    }
}

/** brief main - command line argument searching csv file by headers and matching parameter
 *
 * param int argc contains the number of command-line arguments passed by user
 * param char* argv[] contains the strings matching the header names or matching the header name and parameter
 * csvtovector sex
 * prints all elements of column sex
 * csvtovector sex=F
 * prints all lines where sex column = F
 * return 0
 */
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


    headers = csvtovector(filedata);

    while (!inFile.eof()) {
        getline(inFile, filedata);
        dbdata.push_back(filedata);
    }
    inFile.close();

    string find_header = argv[1];
    size_t foundeq = find_header.find("=");

    string header_match = find_header.substr(0, foundeq);
    string para_match = find_header.substr(foundeq + 1);

    if (foundeq != string::npos) {
        print_matching_row(header_match, para_match, headers, dbdata);
    } else {
        print_matching_column(find_header, headers, dbdata);
    }

    // system("pause");
    return 0;
}


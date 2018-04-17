#include <iostream>
#include <stdlib.h>
#include <vector>
#include <fstream>
#include "hashtable.hpp"
using namespace std;

hashtable parser(string file_in);

int main() {
	// creating the table
	string file_in = "words.txt";
	hashtable table = parser(file_in);

	// user interface
	string input;
	cout << "Type a word to get a definition(type 'exit' to finish):";
	while (cin >> input) {
		if(input == "exit") break;
		string def = table.search(input);
		if(def != "False")
			cout << def << endl;

		cout << "Type a word to get a definition(type 'exit' to finish):";
	}
	cout << "Program terminated.";
	return 0;
}

hashtable parser(string file_in) {
	hashtable table;
	ifstream fread(file_in.c_str());
	if(!fread.is_open()) {
		cout << "Failed to open the file!" << endl;
	} else {
		string word, definition, raw;
		while(getline(fread, raw)) {
			size_t delimiter = raw.find(";");
			word = raw.substr(0, delimiter);
			table.insert(word, raw); // insert definition and row
		}
	}
	fread.close();
	return table;
}



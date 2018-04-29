#include <string>
#include <iostream>
#include <fstream>
#include <cctype>
#include <stdexcept>

#include "hash_table/hash_table.hpp"

#define INIT_LENGTH 200

using namespace std;

// prototypes
HashTable<string, string> parseDict(const char*);
void process(const HashTable<string, string>&);

// implementation
int main(int argc, char* argv[]) {
  try {
    if (argc != 2) throw runtime_error("Invalid application arguments passed.");

    const char* dictFile = argv[1];
    HashTable<string, string> dict = parseDict(dictFile);
    process(dict);

    return 0;
  } catch (const exception& e) {
    cout << e.what() << endl;
    return 1;
  }
}

HashTable<string, string> parseDict(const char* file) {
  ifstream fin(file);

  if (!fin) throw runtime_error("Error opening file '"s + file + "'.");

  HashTable<string, string> dict(INIT_LENGTH);

  for (string def; getline(fin, def).good(); ) {
    string word = def.substr(0, def.find(';'));
    dict.put(word, def);
  }

  fin.close();
  return dict;
}

void process(const HashTable<string, string>& dict) {
  cout << "Type '^' to exit." << endl << endl;

  while (cin.good()) {
    string word, def;
    cout << "Type a word to get the definition: ";
    cin >> word;

    if (word == "^") break;

    def = "Word '" + word + "' wasn't found in the dictionary";
    for (char& c : word) c = toupper(c);
    dict.get(word, def);
    cout << def << endl << endl;
  }
}

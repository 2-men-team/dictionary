#include <string>
#include <iostream>
#include <fstream>
#include <cctype>

#include "hash_table/hash_table.hpp"

#define DICT "dict_processed.txt"
#define INIT_LENGTH 200

using namespace std;

// prototypes
HashTable<string, string> parseDict(const char*);
void process(const HashTable<string, string>&);

// implementation
int main() {
  HashTable<string, string> dict = parseDict(DICT);
  process(dict);
  return 0;
}

HashTable<string, string> parseDict(const char* file) {
  HashTable<string, string> dict(INIT_LENGTH);

  ifstream fin(file);

  for (string def; getline(fin, def).good(); ) {
    string word = def.substr(0, def.find(';'));
    dict.put(word, def);
  }

  fin.close();
  return dict;
}

void process(const HashTable<string, string>& dict) {
  cout << "Type '^' to exit." << endl << endl;

  while (true) {
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

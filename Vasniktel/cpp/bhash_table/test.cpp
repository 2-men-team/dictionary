#include <iostream>
#include <string>

#include "bhash_table.hpp"

#define INIT_SIZE 10
#define EXIT_SIGN "^"
#define NOT_FOUND "such an element doesn't exist in the table."

using namespace std;

int main() {
  BHashTable<string, string> table(INIT_SIZE);

  cout << "Start inputing key-value pairs." << endl
       << "Input '" EXIT_SIGN "' to proceed testing." << endl;
  while (cin.good()) {
    string key, value;
    cin >> key >> value;

    if (key == EXIT_SIGN || value == EXIT_SIGN) break;

    table.put(key, value);
  }

  cout << "Start inputing key or value to see the element in the table." << endl
       << "Make input in a form: 'key|value <input>'." << endl
       << "Input '" EXIT_SIGN "' to exit." << endl;
  while (cin.good()) {
    string entity, in;
    cin >> entity >> in;

    if (entity == EXIT_SIGN || in == EXIT_SIGN) break;

    string out = NOT_FOUND;
    if (entity == "key") table.getByKey(in, out);
    else if (entity == "value") table.getByValue(in, out);

    cout << "Result: " << out << endl << endl;
  }

  return 0;
}

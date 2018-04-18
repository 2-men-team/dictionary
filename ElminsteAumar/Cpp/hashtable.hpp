#include <stdlib.h>
#include <string>
#include "single.hpp"
#include <vector>
using namespace std;

class hashtable {
	private:
		vector<slist> hash;
		int m = 0;
	public:
		hashtable() {
			for(int i = 0; i < 10; i++) {
				slist temp;
				hash.push_back(temp);
			}
		}
		bool check_overload();
		void resize();
		int load_factor();
		int get_len();
		void insert(string word, string definition);
		void delete_word(string word);
		string search(string word);
		int hash_func(string word);
		void clear();
		void display();
};

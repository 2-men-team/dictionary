#include <vector>
#include <iostream>
#include <stdlib.h>
#include <cctype>
#include "hashtable.hpp"
using namespace std;

string upper(string word);

int hashtable::get_len() {
	return hash.size();
}

void hashtable::resize() {
	hashtable table;
	for(unsigned int i = 0; i < 2*hash.size(); i++) {
		slist list;
		table.hash.push_back(list);
	}

	for(unsigned int i = 0; i<hash.size(); i++) {
		node* temp = new node;
		temp = hash[i].get_head();
		while (temp != NULL) {
			table.insert(temp->word, temp->definition);
			temp = temp->next;
		}
		hash[i].erase();
	}
	hash = table.hash;
}

bool hashtable::check_overload() {
	return (load_factor() > 0.8) ? true:false;
}

int hashtable::load_factor() {
	return m/hash.size();
}

int hashtable::hash_func(string word) {
	int sum = 0;
	for(unsigned int i = 0; i < word.length(); i++)
		sum += int(word[i]);
	return sum % hash.size();
}

void hashtable::insert(string word, string definition) {
	m += 1;
	int key = hash_func(word);
	hash[key].insert_start(word, definition);
	if(check_overload()) {
		resize();
	}
}

void hashtable::delete_word(string word) {
	int key = hash_func(word);
	hash[key].delete_element(word);
}

string hashtable::search(string word) {
	word = upper(word);
	int key = hash_func(word);
	string definition = hash[key].search(word);
	if(definition != "False") {
		return definition;
	} else {
		cout << "Element not found!" << endl;
		return "False";
	}
}

void hashtable::clear() {
	for(unsigned int i = 0; i < hash.size(); i++) {
		hash[i].erase();
	}
}

void hashtable::display() {
	for(unsigned int i = 0;i < hash.size(); i++) {
		hash[i].display();
	}
}

string upper(string word) {
	for(unsigned int i = 0; i < word.length(); i++) {
		word[i] = toupper(word[i]);
	}
	return word;
}

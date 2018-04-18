#include <stdlib.h>
#include <string>
using namespace std;

struct node {
	string word;
	string definition;
	node *next;
};

class slist // single list
{
	private:
		node *tail, *head;
	public:
	  slist() {
		  head=NULL;
		  tail=NULL;
	  }
	  node* get_head(); // returns the head of the list
	  node* get_tail(); // return the tail of the list
	  void insert_start(string word, string definition);// add an element to the end of the list
	  void display(); // display the elements of the list
	  void delete_last();// delete last element of the list
	  void delete_element(string word);
	  string search(string word);
	  void erase();// delete all the elements of list
};


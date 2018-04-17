#include "single.hpp"
#include <iostream>

node* slist::get_head() {
	return head;
}

node* slist::get_tail() {
	return tail;
}

void slist::insert_start(string word, string definition) {
	node *temp = new node;
	temp->word = word;
	temp->definition = definition;
	temp->next = head;
	head=temp;
}

void slist::display() {
  node *temp=new node;
  temp=head;
  while(temp!=NULL) {
    cout<< temp->word <<"\t";
    temp=temp->next;
  }
}

void slist::delete_last() {
	node *current=new node;
	node *previous=new node;
	current=head;
	while(current->next!=NULL) {
	  previous=current;
	  current=current->next;
	}
	tail=previous;
	previous->next=NULL;
	delete current;
}

void slist::delete_element(string word) {
	node *temp = new node;
	node *previous = new node;
	temp = head;
	while(temp != NULL && temp->word != word) {
		previous = temp;
		temp = temp->next;
	}
	if(temp->word == word) {
		if(temp->next == NULL)
			delete_last();
		previous->next = temp->next;
		temp->next = NULL;
		delete temp;
		cout << "Element deleted";
	} else {
		cout << "No such element";
	}
}

string slist::search(string word) {
	node *temp = new node;
	temp = head;
	while(temp != NULL && temp->word != word) {
		temp = temp->next;
	}
	if(temp == NULL) {
		return "False";
	} else {
		return temp->definition;
	}
}

void slist::erase() {
	node *current = head;
	node *next;
	while (current != NULL) {
	   next = current->next;
	   delete current;
	   current = next;
	}
	head = NULL;
}


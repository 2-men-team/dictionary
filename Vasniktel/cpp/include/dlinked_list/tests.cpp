#include <iostream>
#include <cstdlib>
#include <ctime>
#include "dlinked_list.hpp"

using namespace std;

int main() {
  srand(time(NULL));
  DLinkedList<int, true> list1;

  for (int i = 0; i < 200; i++) {
    list1.insert(rand() % 601, rand() % (i + 1));
  }
  cout << list1.sort([](const int& a, const int& b) { return a > b; }).dup() << endl;

  DLinkedList<int, true> list2 = list1;

  cout << "list1 and list2 are " << boolalpha << (list1 == list2 ? "equal" : "not equal") << endl;

  list2[0] = list2[list2.size() - 1] = -1000;

  cout << list2.map([](const int& el, size_t) {
    return el - 600;
  }).filter([](const int& el, size_t) {
    return el % 2 == 0 && el != 0;
  }).insertBack(0).insertFront(0) << endl;

  list2.each([](const int& el, size_t index) {
    cout << el << " at " << index << endl;
    return true;
  });

  return 0;
}

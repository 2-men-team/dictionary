#ifndef _DLINKED_LIST_HPP_
#define _DLINKED_LIST_HPP_

#include <cstddef>
#include <ostream>
#include <stdexcept>
#include <vector>
#include <algorithm>
#include <functional>
#include <utility>

template <typename ValType, bool looped = false>
class DLinkedList;

template <typename ValType, bool looped>
std::ostream& operator<<(std::ostream&, const DLinkedList<ValType, looped>&);

template <typename ValType, bool looped>
class DLinkedList {
private:

  struct Node {
    ValType data;
    Node* next;
    Node* prev;

    Node(const ValType&, Node* = nullptr, Node* = nullptr);
    bool operator==(const Node&) const;
    bool operator==(const ValType&) const;
    bool operator!=(const Node&) const;
    bool operator!=(const ValType&) const;
  };

  Node* _first = nullptr;
  Node* _last = nullptr;
  std::size_t _size = 0;

public:
  DLinkedList();
  DLinkedList(const DLinkedList&);
  DLinkedList(DLinkedList&&);
  DLinkedList& operator=(const DLinkedList&);
  DLinkedList& operator=(DLinkedList&&);
  ~DLinkedList();
  DLinkedList& clear();
  long indexOf(const ValType&) const;
  ValType remove(std::size_t);
  DLinkedList& insert(const ValType&, std::size_t);
  DLinkedList& insertFront(const ValType&);
  DLinkedList& insertBack(const ValType&);
  DLinkedList& append(const DLinkedList&);
  bool has(const ValType&) const;
  std::size_t size() const;
  bool empty() const;
  friend std::ostream& operator<< <ValType, looped> (std::ostream&, const DLinkedList&);
  DLinkedList& sort(const std::function<bool(const ValType&, const ValType&)>& = [](const ValType& a, const ValType& b) {
    return a < b;
  });
  bool each(const std::function<bool(const ValType&, std::size_t)>&) const;
  DLinkedList map(const std::function<ValType(const ValType&, std::size_t)>&) const;
  DLinkedList filter(const std::function<bool(const ValType&, std::size_t)>&) const;
  ValType& operator[](std::size_t);
  ValType operator[](std::size_t) const;
  bool operator==(const DLinkedList&) const;
  bool operator!=(const DLinkedList&) const;
  std::size_t count(const ValType&) const;
};

#include "node.tpp"
#include "dlinked_list.tpp"

#endif

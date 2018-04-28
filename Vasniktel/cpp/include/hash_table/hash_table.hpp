#ifndef _HASH_TABLE_HPP_
#define _HASH_TABLE_HPP_

#include <functional>
#include <utility>
#include <stdexcept>

#include "dlinked_list/dlinked_list.hpp"

template <typename KeyType, typename ValType, typename Hash = std::hash<KeyType>>
class HashTable {
private:

  using entry_type = std::pair<KeyType, ValType>;

  DLinkedList<entry_type>* _table = nullptr;
  std::size_t _fullSize;
  std::size_t _usedSize;
  float _loadFactor;
  std::size_t _increaseFactor;

  void _rehash(std::size_t);
  std::size_t _index(const KeyType&) const;
  entry_type _makeEntry(const KeyType&, const ValType&) const;

public:

  HashTable() = delete;
  HashTable(std::size_t, float = 0.8, std::size_t = 2);
  HashTable(const HashTable&);
  HashTable(HashTable&&);
  HashTable& operator=(const HashTable&);
  HashTable& operator=(HashTable&&);
  ~HashTable();
  HashTable& clear();
  HashTable& put(const KeyType&, const ValType&);
  bool get(const KeyType&, ValType&) const;
  bool remove(const KeyType&);
  std::size_t size() const;
  bool empty() const;
  bool has(const KeyType&) const;

};

#include "hash_table.tpp"

#endif

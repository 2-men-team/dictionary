#ifndef _BHASH_TABLE_HPP_
#define _BHASH_TABLE_HPP_

#include <functional>

#include "hash_table/hash_table.hpp"

template <
  typename KeyType,
  typename ValType,
  typename KeyHash = std::hash<KeyType>,
  typename ValHash = std::hash<ValType>
>
class BHashTable {
private:

  HashTable<KeyType, ValType, KeyHash> _keyTable;
  HashTable<ValType, KeyType, ValHash> _valTable;

public:

  BHashTable() = delete;
  BHashTable(std::size_t, float = 0.8, std::size_t = 2);
  BHashTable& clear();
  BHashTable& put(const KeyType&, const ValType&);
  bool getByKey(const KeyType&, ValType&) const;
  bool getByValue(const ValType&, KeyType&) const;
  bool removeByKey(const KeyType&);
  bool removeByValue(const ValType&);
  std::size_t size() const;
  bool empty() const;
  bool hasKey(const KeyType&) const;
  bool hasValue(const ValType&) const;

};

#include "bhash_table.tpp"

#endif

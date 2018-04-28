template <typename KeyType, typename ValType, typename KeyHash, typename ValHash>
BHashTable<KeyType, ValType, KeyHash, ValHash>::BHashTable(std::size_t size, float loadFactor, std::size_t increaseFactor)
  : _keyTable(size, loadFactor, increaseFactor), _valTable(size, loadFactor, increaseFactor)
{ }

template <typename KeyType, typename ValType, typename KeyHash, typename ValHash>
BHashTable<KeyType, ValType, KeyHash, ValHash>& BHashTable<KeyType, ValType, KeyHash, ValHash>::clear() {
  this->_keyTable.clear();
  this->_valTable.clear();
  return *this;
}

template <typename KeyType, typename ValType, typename KeyHash, typename ValHash>
BHashTable<KeyType, ValType, KeyHash, ValHash>& BHashTable<KeyType, ValType, KeyHash, ValHash>::put(const KeyType& key, const ValType& value) {
  this->_keyTable.put(key, value);
  this->_valTable.put(value, key);
  return *this;
}

template <typename KeyType, typename ValType, typename KeyHash, typename ValHash>
bool BHashTable<KeyType, ValType, KeyHash, ValHash>::getByKey(const KeyType& key, ValType& value) const
{ return this->_keyTable.get(key, value); }

template <typename KeyType, typename ValType, typename KeyHash, typename ValHash>
bool BHashTable<KeyType, ValType, KeyHash, ValHash>::getByValue(const ValType& value, KeyType& key) const
{ return this->_valTable.get(value, key); }

template <typename KeyType, typename ValType, typename KeyHash, typename ValHash>
bool BHashTable<KeyType, ValType, KeyHash, ValHash>::removeByKey(const KeyType& key)
{ return this->_keyTable.remove(key); }

template <typename KeyType, typename ValType, typename KeyHash, typename ValHash>
bool BHashTable<KeyType, ValType, KeyHash, ValHash>::removeByValue(const ValType& value)
{ return this->_valTable.remove(value); }

template <typename KeyType, typename ValType, typename KeyHash, typename ValHash>
std::size_t BHashTable<KeyType, ValType, KeyHash, ValHash>::size() const
{ return this->_keyTable.size(); }

template <typename KeyType, typename ValType, typename KeyHash, typename ValHash>
bool BHashTable<KeyType, ValType, KeyHash, ValHash>::empty() const
{ return this->_keyTable.empty(); }

template <typename KeyType, typename ValType, typename KeyHash, typename ValHash>
bool BHashTable<KeyType, ValType, KeyHash, ValHash>::hasKey(const KeyType& key) const
{ return this->_keyTable.has(key); }

template <typename KeyType, typename ValType, typename KeyHash, typename ValHash>
bool BHashTable<KeyType, ValType, KeyHash, ValHash>::hasValue(const ValType& value) const
{ return this->_valTable.has(value); }

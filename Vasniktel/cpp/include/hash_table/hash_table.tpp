template <typename KeyType, typename ValType, typename Hash>
HashTable<KeyType, ValType, Hash>::HashTable(std::size_t size, float loadFactor, std::size_t increaseFactor) {
  if (loadFactor <= 0) throw std::invalid_argument("'loadFactor' must be greater than zero.");
  if (increaseFactor <= 0) throw std::invalid_argument("'increaseFactor' must be greater than zero.");
  if (size == 0) throw std::invalid_argument("'size' must be greater than zero.");

  this->_table = new DLinkedList<entry_type>[size];
  this->_fullSize = size;
  this->_usedSize = 0;
  this->_loadFactor = loadFactor;
  this->_increaseFactor = increaseFactor;
}

template <typename KeyType, typename ValType, typename Hash>
HashTable<KeyType, ValType, Hash>::HashTable(const HashTable<KeyType, ValType, Hash>& other)
{ *this = other.dup(); }

template <typename KeyType, typename ValType, typename Hash>
HashTable<KeyType, ValType, Hash>::~HashTable()
{ delete[] this->_table; }

template <typename KeyType, typename ValType, typename Hash>
HashTable<KeyType, ValType, Hash>& HashTable<KeyType, ValType, Hash>::clear() {
  for (std::size_t i = 0; i < this->_fullSize; i++) this->_table[i].clear();
  this->_usedSize = 0;
  return *this;
}

template <typename KeyType, typename ValType, typename Hash>
std::size_t HashTable<KeyType, ValType, Hash>::_index(const KeyType& key) const
{ return Hash()(key) % this->_fullSize; }

template <typename KeyType, typename ValType, typename Hash>
typename HashTable<KeyType, ValType, Hash>::entry_type HashTable<KeyType, ValType, Hash>::_makeEntry(
  const KeyType& key,
  const ValType& value
) const
{ return std::make_pair(key, value); }

template <typename KeyType, typename ValType, typename Hash>
HashTable<KeyType, ValType, Hash>& HashTable<KeyType, ValType, Hash>::put(const KeyType& key, const ValType& value) {
  this->_table[this->_index(key)].insertFront(this->_makeEntry(key, value));
  this->_usedSize++;

  if (float(this->_usedSize) / this->_fullSize > this->_loadFactor)
    this->_rehash(this->_fullSize * this->_increaseFactor);

  return *this;
}

template <typename KeyType, typename ValType, typename Hash>
bool HashTable<KeyType, ValType, Hash>::get(const KeyType& key, ValType& found) const {
  return !this->_table[this->_index(key)].each(
    [&found, &key](const entry_type& entry, std::size_t) {
      if (entry.first == key) {
        found = entry.second;
        return false;
      }
      return true;
    }
  );
}

template <typename KeyType, typename ValType, typename Hash>
bool HashTable<KeyType, ValType, Hash>::remove(const KeyType& key, ValType& removed) {
  std::size_t position;
  auto& section = this->_table[this->_index(key)];

  bool present = !section.each(
    [&key, &removed, &position](const entry_type& entry, std::size_t i) {
      if (entry.first == key) {
        removed = entry.second;
        position = i;
        return false;
      }
      return true;
    }
  );

  if (present) {
    section.remove(position);
    this->_usedSize--;
  }

  return present;
}

template <typename KeyType, typename ValType, typename Hash>
std::size_t HashTable<KeyType, ValType, Hash>::size() const
{ return this->_usedSize; }

template <typename KeyType, typename ValType, typename Hash>
bool HashTable<KeyType, ValType, Hash>::empty() const
{ return this->size() == 0; }

template <typename KeyType, typename ValType, typename Hash>
bool HashTable<KeyType, ValType, Hash>::has(const KeyType& key) const {
  return !this->_table[this->_index(key)].each(
    [&key](const entry_type& entry, std::size_t) {
      if (entry.first == key) return false;
      return true;
    }
  );
}

template <typename KeyType, typename ValType, typename Hash>
void HashTable<KeyType, ValType, Hash>::_rehash(std::size_t newSize) {
  auto oldTable = this->_table;
  std::size_t oldSize = this->_fullSize;

  this->_table = new DLinkedList<entry_type>[newSize];
  this->_fullSize = newSize;
  this->_usedSize = 0;

  for (std::size_t i = 0; i < oldSize; i++) {
    oldTable[i].each(
      [this](const entry_type& entry, std::size_t) {
        this->put(entry.first, entry.second);
        return true;
      }
    );
  }

  delete[] oldTable;
}

template <typename KeyType, typename ValType, typename Hash>
HashTable<KeyType, ValType, Hash> HashTable<KeyType, ValType, Hash>::dup() const {
  HashTable copied(this->_fullSize, this->_loadFactor, this->_increaseFactor);

  for (std::size_t i = 0; i < this->_fullSize; i++) {
    copied._table[i] = this->_table[i].dup();
  }

  copied._usedSize = this->_usedSize;
  return copied;
}

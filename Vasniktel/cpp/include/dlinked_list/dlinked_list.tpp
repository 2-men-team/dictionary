template <typename ValType, bool looped>
DLinkedList<ValType, looped>::DLinkedList() :
  _first(nullptr), _last(nullptr), _size(0)
{ }

template <typename ValType, bool looped>
DLinkedList<ValType, looped>::DLinkedList(const DLinkedList<ValType, looped>& other) :
  DLinkedList()
{ this->append(other); }

template <typename ValType, bool looped>
DLinkedList<ValType, looped>::~DLinkedList()
{ this->clear(); }

template <typename ValType, bool looped>
DLinkedList<ValType, looped>& DLinkedList<ValType, looped>::clear() {
  for (std::size_t i = 0, size = this->_size; i < size; i++) this->remove(0);
  return *this;
}

template <typename ValType, bool looped>
long DLinkedList<ValType, looped>::indexOf(const ValType& val) const {
  Node* elem = this->_first;

  for (std::size_t i = 0; i < this->_size; i++) {
    if (*elem == val) return i;
    elem = elem->next;
  }

  return -1;
}

template <typename ValType, bool looped>
ValType DLinkedList<ValType, looped>::remove(std::size_t index) {
  if (index >= this->_size)
    throw std::out_of_range("Invalid index value at 'remove' method");

  ValType data;
  Node* elem;

  if (this->_size == 1) {
    elem = this->_first;
    data = elem->data;
    this->_first = this->_last = nullptr;
  } else {
    if (index == 0) {
      data = this->_first->data;
      elem = this->_first;
      this->_first->next->prev = looped ? this->_last : nullptr;
      if (looped) this->_last->next = this->_first->next;
      this->_first = this->_first->next;
    } else if (index == this->_size - 1) {
      data = this->_last->data;
      elem = this->_last;
      this->_last->prev->next = looped ? this->_first : nullptr;
      if (looped) this->_first->prev = this->_last->prev;
      this->_last = this->_last->prev;
    } else {
      elem = this->_first;
      for (std::size_t i = 0; i < index; i++) elem = elem->next;
      data = elem->data;
      elem->next->prev = elem->prev;
      elem->prev->next = elem->next;
    }
  }

  delete elem;
  this->_size--;

  return data;
}

template <typename ValType, bool looped>
DLinkedList<ValType, looped>& DLinkedList<ValType, looped>::insert(const ValType& val, std::size_t index) {
  if (index > this->_size)
    throw std::out_of_range("Invalid index value at 'insert' method");

  Node* elem = new Node(val);

  if (this->_size == 0) {
    if (looped) elem->next = elem->prev = elem;
    this->_first = this->_last = elem;
  } else {
    if (index == 0) {
      elem->next = this->_first;
      this->_first->prev = elem;
      if (looped) {
        elem->prev = this->_last;
        this->_last->next = elem;
      }
      this->_first = elem;
    } else if (index == this->_size) {
      elem->prev = this->_last;
      this->_last->next = elem;
      if (looped) {
        elem->next = this->_first;
        this->_first->prev = elem;
      }
      this->_last = elem;
    } else {
      Node* ptr = this->_first;
      for (std::size_t i = 0; i < index; i++) ptr = ptr->next;
      elem->next = ptr;
      elem->prev = ptr->prev;
      ptr->prev->next = elem;
      ptr->prev = elem;
    }
  }

  this->_size++;

  return *this;
}

template <typename ValType, bool looped>
DLinkedList<ValType, looped>& DLinkedList<ValType, looped>::insertFront(const ValType& val)
{ return this->insert(val, 0); }

template <typename ValType, bool looped>
DLinkedList<ValType, looped>& DLinkedList<ValType, looped>::insertBack(const ValType& val)
{ return this->insert(val, this->_size); }

template <typename ValType, bool looped>
DLinkedList<ValType, looped> DLinkedList<ValType, looped>::dup() const
{ return DLinkedList<ValType, looped>(*this); }

template <typename ValType, bool looped>
DLinkedList<ValType, looped>& DLinkedList<ValType, looped>::append(const DLinkedList<ValType, looped>& other) {
  Node* otherPtr = other._first;

  for (std::size_t i = 0; i < other._size; i++) {
    this->insertBack(otherPtr->data);
    otherPtr = otherPtr->next;
  }

  return *this;
}

template <typename ValType, bool looped>
bool DLinkedList<ValType, looped>::has(const ValType& val) const
{ return this->indexOf(val) != -1; }

template <typename ValType, bool looped>
std::size_t DLinkedList<ValType, looped>::size() const
{ return this->_size; }

template <typename ValType, bool looped>
bool DLinkedList<ValType, looped>::empty() const
{ return this->_size == 0; }

template <typename ValType, bool looped>
std::ostream& operator<<(std::ostream& out, const DLinkedList<ValType, looped>& list) {
  if (list._size == 0) return out << "DLinkedList { }";

  typename DLinkedList<ValType, looped>::Node* ptr = list._first->next;

  out << "DLinkedList { " << list._first->data;
  for (std::size_t i = 1; i < list._size; i++) {
    out << ", " << ptr->data;
    ptr = ptr->next;
  }
  out << " }";

  return out;
}

template <typename ValType, bool looped>
DLinkedList<ValType, looped>& DLinkedList<ValType, looped>::sort(const std::function<bool(const ValType&, const ValType&)>& comp) {
  std::vector<ValType> list(this->_size);
  Node* ptr = this->_first;

  for (auto& elem : list) {
    elem = ptr->data;
    ptr = ptr->next;
  }

  std::sort(list.begin(), list.end(), comp);

  ptr = this->_first;
  for (const auto& elem : list) {
    ptr->data = elem;
    ptr = ptr->next;
  }

  return *this;
}

template <typename ValType, bool looped>
bool DLinkedList<ValType, looped>::each(const std::function<bool(const ValType&, std::size_t)>& fn) const {
  Node* ptr = this->_first;

  for (std::size_t i = 0; i < this->_size; i++) {
    if (!fn(ptr->data, i)) return false;
    ptr = ptr->next;
  }

  return true;
}

template <typename ValType, bool looped>
DLinkedList<ValType, looped> DLinkedList<ValType, looped>::map(const std::function<ValType(const ValType&, std::size_t)>& fn) const {
  DLinkedList<ValType, looped> result(*this);
  Node* ptr = result._first;

  for (std::size_t i = 0; i < result._size; i++) {
    ptr->data = fn(ptr->data, i);
    ptr = ptr->next;
  }

  return result;
}

template <typename ValType, bool looped>
DLinkedList<ValType, looped> DLinkedList<ValType, looped>::filter(const std::function<bool(const ValType&, std::size_t)>& fn) const {
  DLinkedList<ValType, looped> result;
  Node* ptr = this->_first;

  for (std::size_t i = 0; i < this->_size; i++) {
    if (fn(ptr->data, i)) result.insertBack(ptr->data);
    ptr = ptr->next;
  }

  return result;
}

template <typename ValType, bool looped>
ValType& DLinkedList<ValType, looped>::operator[](std::size_t index) {
  if (index >= this->_size)
    throw std::out_of_range("Invalid index value at 'operator[]'");

  if (index == this->_size - 1) return this->_last->data;

  Node* ptr = this->_first;
  for (std::size_t i = 0; i < index; i++) ptr = ptr->next;

  return ptr->data;
}

template <typename ValType, bool looped>
ValType DLinkedList<ValType, looped>::operator[](std::size_t index) const {
  if (index >= this->_size)
    throw std::out_of_range("Invalid index value at 'operator[]'");

  if (index == this->_size - 1) return this->_last->data;

  Node* ptr = this->_first;
  for (std::size_t i = 0; i < index; i++) ptr = ptr->next;

  return ptr->data;
}

template <typename ValType, bool looped>
bool DLinkedList<ValType, looped>::operator==(const DLinkedList<ValType, looped>& list) const {
  if (this->_size != list._size) return false;

  Node* thisPtr = this->_first;
  Node* listPtr = list._first;

  for (std::size_t i = 0; i < this->_size; i++) {
    if (*thisPtr != *listPtr) return false;
    thisPtr = thisPtr->next;
    listPtr = listPtr->next;
  }

  return true;
}

template <typename ValType, bool looped>
bool DLinkedList<ValType, looped>::operator!=(const DLinkedList<ValType, looped>& list) const
{ return !(*this == list); }

template <typename ValType, bool looped>
std::size_t DLinkedList<ValType, looped>::count(const ValType& val) const {
  Node* ptr = this->_first;
  std::size_t counter = 0;

  for (std::size_t i = 0; i < this->_size; i++) {
    if (*ptr == val) counter++;
    ptr = ptr->next;
  }

  return counter;
}

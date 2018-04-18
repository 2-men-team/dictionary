template <typename ValType, bool looped>
DLinkedList<ValType, looped>::Node::Node(
  const ValType& val,
  typename DLinkedList<ValType, looped>::Node* next,
  typename DLinkedList<ValType, looped>::Node* prev
) : data(val), next(next), prev(prev)
{ }

template <typename ValType, bool looped>
bool DLinkedList<ValType, looped>::Node::operator==(const typename DLinkedList<ValType, looped>::Node& node) const
{ return *this == node.data; }

template <typename ValType, bool looped>
bool DLinkedList<ValType, looped>::Node::operator==(const ValType& val) const
{ return this->data == val; }

template <typename ValType, bool looped>
bool DLinkedList<ValType, looped>::Node::operator!=(const typename DLinkedList<ValType, looped>::Node& node) const
{ return !(*this == node); }

template <typename ValType, bool looped>
bool DLinkedList<ValType, looped>::Node::operator!=(const ValType& val) const
{ return !(*this == val); }

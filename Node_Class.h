

template<typename C>
class Node
{
private:
    C data;
    Node<C> *next = nullptr;
    Node<C> *prev = nullptr;
public:
    Node(C input) ;
    Node(C input, Node<C> *prev);
    Node(C input, Node<C> *prev, Node<C> *next);
    Node(Node<C> &other);
    Node(Node<C> &&other);
    ~Node();
    bool operator >(const Node &second) const;
    bool operator <(const Node &second) const;
    bool operator <(const C &second) const;
    bool operator >=(const Node &second) const;
    bool operator <=(const Node &second) const;
    bool operator ==(const Node &second) const;
    bool operator ==(const C second) const;
    bool operator !=(const Node &second) const;
    Node &operator =(C input);
    Node &operator =(Node &&second);
    Node &operator =(Node& second) ;
    Node &operator +=(Node &second);
    Node &operator +=(C input);
    Node *get_next();
    Node *get_previous();
    void set_next(Node<C> *input);
    void set_previous(Node<C> *input);
    const C &get_data() const;
    Node *operator*() {return this;};
};



template<typename C>
Node<C>::Node(C input)
{
    data = input;
}

template<typename C>
Node<C>::Node(C input, Node *prev)
{
    data = input;
    this->prev = prev;
}

template<typename C>
Node<C>::Node(C input, Node *prev, Node *next)
{
    data = input;
    this->prev = prev;
    this->next = next;
}

template<typename C>
Node<C>::Node(Node<C> &other)
{
    data = other.get_data();
}

template<typename C>
Node<C>::Node(Node<C> &&other)
{
    data = other.get_data();
    delete *other;
}

template<typename C>
Node<C>::~Node() = default ;

template<typename C>
const C &Node<C>::get_data() const
{
    return data;
}


template<typename C>
void Node<C>::set_next(Node<C> *input)
{
    next = input;
}

template<typename C>
void Node<C>::set_previous(Node<C> *input)
{
    prev = input;
}

template<typename C>
Node<C> *Node<C>::get_next()
{
    return next;
}

template<typename C>
Node<C> *Node<C>::get_previous()
{
    return prev;
}

template<typename C>
bool Node<C>::operator>(const Node<C> &second) const
{
    return data > second.get_data();
}

template<typename C>
bool Node<C>::operator<(const Node<C> &second) const
{
    return *this < second.get_data();
}

template<typename C>
bool Node<C>::operator<(const C &second) const
{
    return data < second;
}

template<typename C>
bool Node<C>::operator==(const Node<C> &second) const
{
    return this->operator==(second.get_data());
}

template<typename C>
bool Node<C>::operator==(const C second) const
{
    return data == second;
}

template<typename C>
bool Node<C>::operator>=(const Node<C> &second) const
{
    return (*this > second) || (*this == second);
}

template<typename C>
bool Node<C>::operator<=(const Node<C> &second) const
{
    return (*this < second) || (*this == second);
}

template<typename C>
bool Node<C>::operator!=(const Node<C> &second) const
{
    return !(*this == second);
}

template<typename C>
Node<C> &Node<C>::operator=(Node<C> &second)
{
    if(this != &second)
        data = second.get_data();
    return *this;
}

template<typename C>
Node<C> &Node<C>::operator=(C input)
{
    if(input != data)
        data = input;
    return *this;
}

template<typename C>
Node<C> &Node<C>::operator =(Node<C> &&second)
{
    if(this != &second)
    {
        data = second.get_data();
        prev = second.get_previous();
        next = second.get_next();
        second.set_previous(nullptr);
        second.set_next(nullptr);
    }
    return *this;
}

template<typename C>
Node<C> &Node<C>::operator+=(Node<C> &second)
{
    data = data + second.get_data();
    return *this;
}

template<typename C>
Node<C> &Node<C>::operator+=(C input)
{
    data = data + input;
    return *this;
}

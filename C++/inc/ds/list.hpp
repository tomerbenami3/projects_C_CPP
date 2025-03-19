#ifndef DS_LIST_HPP
#define DS_LIST_HPP

#include <cstddef>
#include <cassert>
#include <iostream>

namespace ds
{
template <typename T>
struct Node {
    T data;
    Node* next;
    Node* prev;


    Node(T data = T())
    : data{data}
    , next{nullptr}
    , prev{nullptr}
    {
    }

};

template <typename T>
class List {
public:
	List();
	~List();
	List(List const& other);
	List& operator=(List const& other);

	Node<T>* get_head();
	Node<T>* get_tail();

	void push_head(T item);
	void push_tail(T item);
	T pop_head();
	T pop_tail();

	size_t size();
	bool empty();
	void clear();

	void swap(List<T>& other);
private:
	void insert_after(Node<T>& where, T const& item);

private:
	Node<T>* m_head;
	Node<T>* m_tail;
	size_t m_size;
};



template <typename T>
List<T>::List()
: m_head{new Node<T>()}
, m_tail{new Node<T>()}
, m_size{0}
{
    m_head->next = m_tail;
    m_head->prev = m_head;

    m_tail->next = m_tail;
    m_tail->prev = m_head;
}

template <typename T>
List<T>::~List()
{
    Node<T>* current = m_head->next;

    while(current != m_tail) {
        Node<T>* temp = current;
        current = current->next;
        delete temp;
    }

    delete m_head;
    delete m_tail;
}

template <typename T>
List<T>::List(List const& other)
: m_head{new Node<T>()}
, m_tail{new Node<T>()}
, m_size{other.m_size}
{
    Node<T>* current = m_head;
    current->prev = m_head;

    Node<T>* other_node = other.m_head->next;

    while(other_node != other.m_tail) {
        Node<T>* new_node = new Node<T>(other_node->data);
        current->next = new_node;
        new_node->prev = current;
        current = new_node;
        other_node = other_node->next;
    }

    current->next = m_tail;
    m_tail->prev = current;
    m_tail->next = m_tail;
}

template <typename T>
Node<T>* List<T>::get_head()
{
    return m_head;
}

template <typename T>
Node<T>* List<T>::get_tail()
{
    return m_tail;
}

template <typename T>
void List<T>::swap(List<T>& other)
{
    std::swap(this->m_head, other.m_head);
    std::swap(this->m_tail, other.m_tail);
    std::swap(this->m_size, other.m_size);
}

template <typename T>
List<T>& List<T>::operator=(List const& other)
{
    if (this!= &other) {
        List temp(other);
        swap(temp);
        }

    return *this;
}

template <typename T>
void List<T>::push_head(T item)
{

    Node<T>* new_node = new Node(item);
    Node<T>* first_node = m_head->next;

    new_node->next = first_node;
    first_node->prev = new_node;

    m_head->next = new_node;
    new_node->prev = m_head;

    ++m_size;
}

template <typename T>
void List<T>::push_tail(T item)
{
    Node<T>* new_node = new Node(item);
    Node<T>* prev_node = m_tail->prev;

    prev_node->next = new_node;
    new_node->next = m_tail;
    new_node->prev = prev_node;
    m_tail->prev = new_node;

    ++m_size;
}

template <typename T>
T List<T>::pop_head()
{
    assert(!empty());

    if (m_head->next == m_tail) {
            std::cout << "List is empty." << std::endl;
            return -1;
    }

    Node<T>* temp = m_head->next;
    T data = temp->data;

    m_head->next = temp->next;
    m_head->next->prev = m_head;

    delete temp;
    --m_size;

    return data;
}

template <typename T>
T List<T>::pop_tail()
{
    assert(!empty());

    if (m_head->next == m_tail) {
            std::cout << "List is empty." << std::endl;
            return -2;
    }

    Node<T>* to_remove = m_tail->prev;
    T data = to_remove->data;

    m_tail->prev = to_remove->prev;
    m_tail->prev->next = m_tail;

    --m_size;

    delete to_remove;

    return data;
}

template <typename T>
size_t List<T>::size()
{
    return m_size;
}

template <typename T>
bool List<T>::empty()
{
    return m_size == 0;
}

template <typename T>
void List<T>::clear()
{
    while(!empty()) {
        pop_tail();
    }
}

template <typename T, typename Action, typename Context>
size_t for_each(List<T>& list, Action action, Context context)
{
    size_t index = 0;
    Node<T>* current = list.get_head()->next;

    while(current != list.get_tail()) {
        if(action(current->data, context) == 0) {
            break;
        }
        current =  current->next;
        ++index;
    }
    return index;
}

}


#endif // DS_LIST_HPP

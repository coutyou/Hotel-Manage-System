#ifndef NODE_H
#define NODE_H

template<class T>
class Node
{
public:
    Node(const T &data, Node<T> * next = 0);
    void insertAfter(Node<T> * p);
    Node<T>*deleteAfter();
    Node<T>*nextNode();
    const Node<T>*nextNode() const;
    Node<T> * next;
    T data;
private:
};


#endif // NODE_H

#ifndef SLIST_H_INCLUDED
#define SLIST_H_INCLUDED
//#include <iostream>

using std::cout;
using std::endl;


//------- Class Node -------//
template <typename Key,typename Info>
class Node
{
    Key key; //key data unique
    Info info; //data
    Node<Key, Info> *next; // link to next node

public:
    // constructors
    Node (): next(nullptr) {}
    Node(const Key &newKey,const Info &newInfo): key(newKey),info(newInfo),next(nullptr) {}
    Node(const Node<Key, Info> &scdNode): key(scdNode.key),info(scdNode.info),next(scdNode.next) {}

    //destructor
    ~Node() { next=nullptr; }

    //access
    Info getInfo()
        { return info;}
    Key getKey()
        { return key; }
    Node<Key, Info>*& refNext() //returns reference to the next
        { return next; }

    //operators
    Node<Key, Info> operator=(const Node rhs);

    //output
    void printNode()const
    {
        if(this)
        {
            cout<<"Key: "<<key<<"  ";
            cout<<"Info: "<<info<<endl;

        }
    }

    //for testing
    bool isValid() const
        { return this; }
    void addNext(Node rhs)
        { next=&rhs; }
    void setKey(const Key &newKey)
        { key=newKey; }
    void setInfo(const Info &newInfo)
        { info=newInfo; }

};
template <typename Key,typename Info>
Node<Key, Info> Node<Key, Info>::operator=(const Node rhs)
{
    info=rhs.info;
    key=rhs.key;
    next=rhs.next;
    return *this;
}


//------- Class List-------//
template <typename Key,typename Info>
class List
{
    int length;// number of nodes in th list
    Node<Key, Info> *head; // pointer to the first node
    Node<Key, Info> *tail; // pointer to the last element
public:

    //constructors
    List() : head(nullptr), tail(nullptr) , length(0){ }
    List(const List<Key, Info> &scdList);

    //destructor
    ~List() { clear(); }

    bool isListEmpty() const
        {return head;}

    //output
    void printList()const;

    //access
    int refLength()const
        { return length;}

    bool doesNodeExist(const Key &key,const Info &info);
    //returns true if exists Node with this item

    void insertElement(const Info &info, const Key &key);
    // add new node at the end of the list
    // length is incremented by 1

    void deleteNode(Node<Info, Key> *n);
    //Function to delete element from the list
    // length is decremented by 1

    void clear();
    // delete all nodes from the list
    // change length to 0


    //inserting
    void insert(const Key& newKey,const Info& newInfo)
    {
        Node<Key,Info> *current;//pointer to traverse the list
        Node<Key,Info> *trailCurrent; //pointer just before current
        Node<Key,Info> *newNode; //pointer to create a node
        bool found;
        Node<Key,Info> *newNode = new Node<Key,Info>(newKey,newInfo); //create the node
        if (!head) //Case 1
        {
            head = newNode;
            tail = newNode;
            length++;
        }
        else
        {
            current = head;
            found = false;
            while (current && !found) //search the list
                if (current->refKey() >= newKey)
                    found = true;
                else
                {
                    trailCurrent = current;
                    current = current->refNext();
                }
            if (current == head) //Case 2
            {
                newNode->refNext() = head;
                head = newNode;
                length++;
            }

            else //Case 3
            {
                trailCurrent->refNext() = newNode;
                newNode->refNext() = current;
                if (!current)
                    tail = newNode;
                length++;
            }
        }//end else
    }//end insert




    void join(const List<Key, Info>& fst, const List<Key, Info>& snd);
    // select <Key, Info> pair from fst or snd
    // where Key value is lower and add this to the result

};

template <typename Key,typename Info>
List<Key, Info>::List(const List<Key, Info> &scdList)
{
    head=nullptr;
    tail=nullptr;
    length=0;

    if(scdList.head)
    {
        Node<Key, Info> *temp=scdList.head; // traversal node
        length=scdList.length; //copy length

        Node<Key, Info> *newHead=new Node<Info, Key>(temp->refInfo(),temp->refKey()); //creation of a new node which head and tail
        head=newHead;
        tail=newHead;
        temp=temp->refNext();
        while(temp) // duplication of the remainings nodes
        {
            Node<Info, Key> *newNode=new Node<Info, Key>(temp->refInfo(),temp->refKey());
            tail->refNext()=newNode;
            tail=newNode;
            temp=temp->refNext();
        }
    }
}

template <typename Key,typename Info>
void List<Key, Info>::printList() const
{
    if(!head)
        cout<<"List is empty."<<endl;
    else
    {
        Node<Info, Key> *temp=head;
        while (temp)
        {
            temp->printNode();
            temp=temp->refNext();
        }
    }
}

template <typename Key,typename Info>
void List<Key, Info>::deleteNode(Node<Info, Key> *n)
{
    Node<Key, Info> *temp;
    if(!head) // list is empty
        return;
    else if(head==tail ) // list has only one element
    {
        delete n;
        head=nullptr;
        tail=nullptr;
        length=0;
    }
    else if(n==head)
    {
        n=head->refNext();
        delete head;
        head=n;
        --length;
    }
    else if( n==tail)
    {
        temp=head;
        while(temp->refNext()!=tail)
            temp=temp->refNext();
        delete tail;
        tail=temp;
        --length;
    }
    else //n is in the middle of the list
    {
        Node<Info, Key> *nNext=n->refNext();
        temp=head;
        while(temp->refNext()!=n)
            temp=temp->refNext();
        delete n;
        temp->refNext()=nNext;
        --length;
    }
}

template <typename Key,typename Info>
void List<Key, Info>::clear()
{
    Node<Info, Key> *temp=head;
    while(head)
    {
        temp=head;
        head=head->refNext();
        delete temp;
    }
    tail=nullptr;
    length=0;
}

template <typename Key,typename Info>
void List<Key, Info>::insertElement(const Info &info, const Key &key)
{
    Node<Key, Info> *newNode=new Node<Key, Info>(info,key);

    if(!head)  // list is empty
    {
        head=newNode;
        tail=newNode;
        ++length;
    }
    else // new node is added after the tail
    {
        tail->refNext()=newNode;
        tail=newNode;
        ++length;
    }
}

template <typename Key,typename Info>
bool List<Key, Info>::doesNodeExist(const Key& key, const Info& info)
{
    Node<Key, Info> *temp=head;
    while(temp)
    {
        if(temp->refInfo()==info && temp->refKey()==key)
            return true;
        temp=temp->refNext();
    }
    return false;
}

template <typename Key,typename Info>
void List<Key, Info>::join(const List<Key, Info>& fst,const List<Key, Info>& snd)
{
    if(isListEmpty()==false)
        clear();

    Node<Key, Info> *fstptr=fst.refHead();
    Node<Key, Info> *sndptr=snd.refHead();

    while(fstptr!=nullptr && sndptr!=nullptr )
    {
        if(fstptr->refKey()<sndptr->refKey()) // node from fst is added
        {
            insertElement(fstptr->refInfo(),fstptr->refKey());
            fstptr=fstptr->refNext();


        }
        else if (fstptr->refKey()==sndptr->refKey()) // since I decide that key is not uniqe both elements are added
        {

            insertElement(fstptr->refInfo(),fstptr->refKey());
            insertElement(sndptr->refInfo(),sndptr->refKey());
            fstptr=fstptr->refNext();
            sndptr=sndptr->refNext();

        }
        else if(fstptr->refKey()>sndptr->refKey()) // node from snd is added
        {
            insertElement(sndptr->refInfo(),sndptr->refKey());
            sndptr=sndptr->refNext();

        }
        else
            break;
    }

    if(fstptr!=nullptr && sndptr==nullptr) // the remaining nodes from fst are added
    {
        while(fstptr!=nullptr)
        {
            insertElement(fstptr->refInfo(),fstptr->refKey());
            fstptr=fstptr->refNext();
        }
    }

    if(fstptr==nullptr && sndptr!=nullptr) // the remaining nodes from snd are added
    {
        while(sndptr!=nullptr)
        {
            insertElement(sndptr->refInfo(),sndptr->refKey());
            sndptr=sndptr->refNext();
        }
    }

}

#endif // SLIST_H_INCLUDED

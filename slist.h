#ifndef SLIST_H_INCLUDED
#define SLIST_H_INCLUDED
//#include <iostream>

using std::cout;
using std::endl;

//------- Class List-------//
template <typename Key,typename Info>
class List
{
    struct Node
    {
        Key key;
        Info info;
        Node* previous;
        Node* next;

        Node(Key& newkey, Info& newinfo)
        {
            key = newkey;
            info = newinfo;
            previous = next = nullptr;
        }
    };
    int length;// number of nodes in th list
    Node *head; // pointer to the first node
    Node *tail; // pointer to the last element
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

    void deleteNode(Node *n);
    //Function to delete element from the list
    // length is decremented by 1

    void clear();
    // delete all nodes from the list
    // change length to 0


    //inserting
    void insert(const Key& newKey,const Info& newInfo)
    {
        Node *current;//pointer to traverse the list
        Node *trailCurrent; //pointer just before current
        Node *newNode; //pointer to create a node
        bool found;
        Node *newNode = new Node(newKey, newInfo); //create the node
        if (!head) //Case 1 - list is empty
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
                if (current->key() >= newKey)
                    found = true;
                else
                {
                    trailCurrent = current;
                    current = current->next();
                }
            if (current == head) //Case 2
            {
                newNode->next() = head;
                head = newNode;
                length++;
            }

            else //Case 3
            {
                trailCurrent->next() = newNode;
                newNode->next() = current;
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
        Node *temp=scdList.head; // traversal node
        length=scdList.length; //copy length
  
        Node *newHead=new Node(temp->info,temp->info); //creation of a new node which head and tail
        head=newHead;
        tail=newHead;
        temp=temp->next;
        while(temp) // duplication of the remainings nodes
        {
            Node *newNode=new Node(temp->info,temp->key);
            tail->next()=newNode;
            tail=newNode;
            temp=temp->next;
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
        Node *temp=head;
        while (temp)
        {
            //temp->printNode();
            temp=temp->next;
        }
    }
}

template <typename Key,typename Info>
void List<Key, Info>::deleteNode(Node *n)
{
    Node *temp;
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
        n=head->next;
        delete head;
        head=n;
        --length;
    }
    else if( n==tail)
    {
        temp=head;
        while(temp->next!=tail)
            temp=temp->next();
        delete tail;
        tail=temp;
        --length;
    }
    else //n is in the middle of the list
    {
        Node *nNext=n->next();
        temp=head;
        while(temp->next!=n)
            temp=temp->next;
        delete n;
        temp->next=nNext;
        --length;
    }
}

template <typename Key,typename Info>
void List<Key, Info>::clear()
{
    Node *temp=head;
    while(head)
    {
        temp=head;
        head=head->next;
        delete temp;
    }
    tail=nullptr;
    length=0;
}

template <typename Key,typename Info>
void List<Key, Info>::insertElement(const Info &info, const Key &key)
{
    Node *newNode=new Node(key, info);

    if(!head)  // list is empty
    {
        head=newNode;
        tail=newNode;
        ++length;
    }
    else // new node is added after the tail
    {
        tail->next=newNode;
        tail=newNode;
        ++length;
    }
}

template <typename Key,typename Info>
bool List<Key, Info>::doesNodeExist(const Key& key, const Info& info)
{
    Node *temp=head;
    while(temp)
    {
        if(temp->info==info && temp->key==key)
            return true;
        temp=temp->next;
    }
    return false;
}

template <typename Key,typename Info>
void List<Key, Info>::join(const List<Key, Info>& fst,const List<Key, Info>& snd)
{
    if(isListEmpty()==false)
        clear();

    Node *fstptr=fst.refHead();
    Node *sndptr=snd.refHead();

    while(fstptr!=nullptr && sndptr!=nullptr )
    {
        if (fstptr->key < sndptr->key()) // node from fst is added
        {
            insertElement(fstptr->info, fstptr->key);
            fstptr = fstptr->next;


        }
        else if (fstptr->key==sndptr->key) // since I decide that key is not uniqe both elements are added
        {

            insertElement(fstptr->info(),fstptr->key);
            insertElement(sndptr->info(),sndptr->key);
            fstptr = fstptr->next;
            sndptr = sndptr->next;
        }
        else if(fstptr->key>sndptr->key) // node from snd is added
        {
            insertElement(sndptr->info,sndptr->key);
            sndptr=sndptr->next;

        }
        else
            break;
    }

    if(fstptr!=nullptr && sndptr==nullptr) // the remaining nodes from fst are added
    {
        while(fstptr!=nullptr)
        {
            insertElement(fstptr->info,fstptr->key);
            fstptr=fstptr->next;
        }
    }

    if(fstptr==nullptr && sndptr!=nullptr) // the remaining nodes from snd are added
    {
        while(sndptr!=nullptr)
        {
            insertElement(sndptr->info, sndptr->key);
            sndptr=sndptr->next;
        }
    }

}

#endif // SLIST_H_INCLUDED

#ifndef SLIST_H_INCLUDED
#define SLIST_H_INCLUDED
#include <iostream>


using std::cout;
using std::endl;

//------- Class List-------//
template <typename Key,typename Info>
class List
{
    struct Node
    {
        Key key; //TO DO: unique data 
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

    void deleteNode(const Key& key); //USED BY: erase(const Key& key)
                                     //Function to delete element from the list
                                     //length is decremented by 1
    
    Node* findNode(const Key& key);  //USED BY: erase(const Key& key)
                                    //Return pointer to Node with given Key or if it does not exists nullptr
    

public:
    List() : head(nullptr), tail(nullptr) , length(0){ } //constructor
    List(const List<Key, Info> &scdList);     //copy constructor
 
    ~List()   //destructor
    { clear(); }

    bool isListEmpty() const //returns true if list is nonempty otherwise false
    {   return head;  }

    bool doesNodeExist(const Key& key) //returns true if node exists otherwise false
    {   return findNode(key);   }      // USES: findNode(const Key& key)

    void erase(const Key& key) //delete node with given key 
    {   deleteNode(key); }     //USES: findNode(const Key& key), deleteNode(Node* n)

    int length() const //access length
    {   return length;}
    

    void clear();  // delete all nodes from the list
                   // change length to 0
   
    void printList() const;  //output the list 

    
         
    //inserting
    void insert(const Key& newKey, const Info& newInfo);
    




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
        Node *current=scdList.head; // traversal node
        length=scdList.length; //copy length
  
        Node *newHead=new Node(current->key,current->info); //creation of a new node which head and tail
        head=newHead;
        tail=newHead;
        current=current->next;
        while(current) // duplication of the remainings nodes
        {
            Node *newNode=new Node(current->key,current->info);
            tail->next()=newNode;
            tail=newNode;
            current=current->next;
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
            cout << "Key: " << temp->key << " Info: " << temp->info << endl;
            temp=temp->next;
        }
    }
}

template <typename Key, typename Info>
List<Key, Info>::Node* List<Key, Info>::findNode(const Key& key)
{
    Node* current = head;
    while (current)
    {
        if (current->key == key)
            return current;
        current = current->next;
    }
    return nullptr;
}

template <typename Key, typename Info>
void List<Key, Info>::deleteNode(const Key& key)
{
    Node* current = findNode(key);

    if (current)
    {
        if(head == tail) //Case 1 - one element list
        {
            delete current;
            head = nullptr;
            tail = nullptr;
            length = 0;
        }
        else //Case 2 
        {
            current->previous->next = current->next;
            current->next->previous = current->previous;
            
            if (current == head)
                head = current->next
            else if(current == tail)
                tail = current->previous;
            delete current;
            length--;   
        }
    }
}

template <typename Key,typename Info>
void List<Key, Info>::clear()
{
    Node *current=head;
    while(head)
    {
        current=head;
        head=head->next;
        delete current;
    }
    tail=nullptr;
    length=0;
}

template <typename Key,typename Info>
void List<Key, Info>::insert(const Key& key, const Info& info)
{
    if (doesNodeExist(key)) //no duplicates
        return;

    Node* current;//pointer to traverse the list
    Node* prevCurrent; //pointer just before current
    bool found;
    Node* newNode = new Node(newKey, newInfo); //create new node
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
        while (current && !found)           //search the list 
        {                                   //newNode will be inserted before current
            if (current->key > newKey)
                found = true;
            else
            {
                prevCurrent = current;
                current = current->next();
            }
        }


        if (current == head) //Case 2
        {
            newNode->next = head;
            newNode->previous = tail;
            head = newNode;
            length++;
        }
        else //Case 3
        {
            prevCurrent->next = newNode;
            newNode->previous = prevCurrent;
            newNode->next = current;
            length++;

            if (newNode->key > tail->key)
            {
                tail = newNode;
                return;
            }
            current->previous = newNode;

        }
    }
}//end insert

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

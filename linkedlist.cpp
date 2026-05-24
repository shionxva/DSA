#include <iostream>
using namespace std;

struct NODE{
  int data;
  NODE* next;
};

struct LIST{
    NODE* head;
    NODE* tail;
};

//create empty list
void Init(LIST &l){
    l.head = l.tail = nullptr;
}

bool isEmpty(LIST &l){
    return l.head == nullptr;
}

//create an element
NODE* GetNode(int x) {
    NODE* p = new NODE;
    
    p->data = x;
    p->next = nullptr;
    return p;
}

//add to the beginning of the LIST
void AddFirst(LIST &l, NODE* new_e) {
    if (l.head == nullptr) // Empty list
        l.head = l.tail = new_e;
    else {
        new_e->next = l.head;
        l.head = new_e;
    }
}


NODE* InsertHead(LIST &l, int x){
    NODE* new_e = GetNode(x);
    if (new_e == nullptr)
        return nullptr;
    AddFirst(l, new_e);
    return new_e;
}

//add to the end of the LIST
void AddTail(LIST &l, NODE* new_e) {
    if (l.head == nullptr) // Empty list
        l.head = l.tail = new_e;
    else {
        l.tail->next = new_e;
        l.tail = new_e;
    }
}

NODE* InsertTail(LIST &l, int x){
    NODE* new_e = GetNode(x);
    if (new_e == nullptr)
        return nullptr;
    AddTail(l, new_e);
    return new_e;
}

//insert after a NODE
void AddAfter(LIST &l,NODE *q, NODE* new_e){
    if (q!=nullptr) {
        new_e->next = q->next;
        q->next = new_e;
        if(q == l.tail)
            l.tail = new_e;
    }
    else{ // Add at the beginning of the list
        AddFirst(l, new_e);
    }
}

NODE* InsertAfter(LIST &l, NODE* q, int x){
    NODE* new_e = GetNode(x);
    if (new_e == nullptr)
        return nullptr;
    AddAfter(l, q, new_e);
    return new_e;
}

//insert before a NODE
NODE* findBefore(LIST &l, NODE* q){
    NODE* p = l.head;
    while(p != nullptr && p->next != q) //traverse the whole list
        p = p->next;

    return p;
}

void AddBefore(LIST &l, NODE* q, NODE* new_e){
    if(q != NULL){
        NODE* p = findBefore(l, q);
        AddAfter(l, p, new_e);
    }
    else{
        AddFirst(l, new_e);
    }
}

NODE* InsertBefore(LIST &l, NODE* q, int x){
    NODE* new_e = GetNode(x);
    if (new_e == NULL)
        return NULL;
    else{
        AddBefore(l, q, new_e);
    }
    return new_e;
}


//extracting head (and remove)
NODE* PickHead(LIST &l) {
    NODE *p = nullptr;
    if (l.head != nullptr) {
        p = l.head; // p is the node to be extracted
        l.head = l.head->next; // Detach p from the list
        p->next = nullptr;
        
        if(l.head == nullptr)
            l.tail = nullptr; // The list is now empty
    }
    return p;
}

int RemoveHead(LIST &l){
    if (l.head == nullptr)
        return -1;
    NODE* p = PickHead(l);
    int x = p->data;
    delete p;
    return x;
}

//print
void PrintList(LIST l){
    NODE* p = l.head;
    while(p != NULL){
        cout << p->data << " ";
        p = p->next;
    }
}


int main(){
    LIST l;
    Init(l);

    NODE* A = InsertHead(l, 10);
    NODE* B = InsertTail(l, 20);
    NODE* C = InsertTail(l, 30);
    cout<<"Initial list: ";
    PrintList(l);
    //A -> B -> C
    
    cout<<"\nInsert new elements: ";
    NODE* D = InsertBefore(l, B, 15); //then A -> D -> B -> C
    NODE* E = InsertAfter(l, B, 25); //and A -> D -> B -> E -> C
    PrintList(l);
    
    cout<<"\n\nExtracted elements: ";
    NODE* p = PickHead(l);
    cout<< "\nHead's" <<"\n-Address: "<< p <<"\n-Value: "<< p->data << endl;
    RemoveHead(l);
    cout<<"\nRemoved head -> new list: ";
    PrintList(l);
    
    return 0;
}
#include <iostream>
using namespace std;

//===========Linked List===========
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

//while pick only extract the node, remove delete them from the list
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

//extract after a NODE (and delete)
NODE* PickAfter(LIST &l, NODE* q){
    NODE* p;
    if(q!= nullptr){
        p = q->next;
        if(p!= nullptr){
            if(p == l.tail){
                l.tail = q;
            }
            q->next = p->next;
            p->next = nullptr;
        }
    }
    else
        p = PickHead(l);
    return p;
}

int RemoveAfter(LIST &l, NODE *q) {
    NODE *p = PickAfter(l, q);
    if (p == nullptr)
        return -1;
    int x = p->data;
    delete p;
    return x;
}

//extract NODE with data k (and delete)
NODE* PickNode(LIST &l, int K) {
    NODE *p = l.head, *q = nullptr;
    // Find node p with key K and the node q before it.
    while ((p != nullptr) && (p->data != K)) {
        q = p;
        p = p->next;
    }
    if (p == nullptr) // Report that key K is not found.
    return nullptr;
    return PickAfter(l, q); // Key K is found
}

int RemoveNode(LIST &l, int K) {
    NODE *p = PickNode(l, K);
    if (p == nullptr)
        return -1;
    int x = p->data;
    delete p;
    return x;
}

//print
void PrintList(LIST l){
    NODE* p = l.head;
    while(p != nullptr){
        cout << p->data << " ";
        p = p->next;
    }
}

//============SORT==============
//selection sort -> choose smallest element
NODE* FindMinprev(LIST l) {
    NODE *min, *minprev, *p, *q;
    minprev = q = nullptr;
    min = p = l.head;
    while(p != nullptr) {
        if (p->data < min->data) {
        min = p;
        minprev = q;
        }
    q = p;
    p = p->next;
    }
    return minprev;
}

void ListSelectionSort(LIST &l) {
    LIST lResult;
    NODE *min, *minprev;
    lResult.head = lResult.tail = nullptr;
    while(l.head != nullptr) {
        minprev = FindMinprev(l);
        min = PickAfter(l, minprev);
        AddTail(lResult, min);
    }
    l = lResult;
}

//quick sort
void LISTAppend (LIST &list, LIST &list2){
    if (list2.head == nullptr) return;
    if(list.head == nullptr)
        list = list2;
    else{
        list.tail->next = list2.head;
        list.tail = list2.tail;
    }
    Init(list2);
}

void ListQuickSort (LIST &list) {
    NODE *X, *p;
    LIST list1, list2;
    if(list.head == list.tail) return;
    Init(list1);
    Init(list2);
    
    X = PickHead(list);
    while(list.head != nullptr) {
        p = PickHead(list);
        if (p->data <= X->data)
            AddTail(list1, p);
        else
            AddTail(list2, p);
    }
    ListQuickSort(list1);
    ListQuickSort(list2);
    LISTAppend(list, list1);
    AddTail(list, X);
    LISTAppend(list, list2);
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
    InsertTail(l, 40);
    InsertTail(l, 50);
    PrintList(l);
    
    cout<<"\n\nExtracted elements: ";
    NODE* p = PickHead(l);
    cout<< "\nHead's" <<"\n-Address: "<< p <<"\n-Value: "<< p->data << endl;
    PrintList(l);
    
    NODE* p2 = PickAfter(l, C);
    cout<< "\n\nAfter 30's" <<"\n-Address: "<< p2 <<"\n-Value: "<< p2->data << endl;
    PrintList(l);
    
    NODE* p3 = PickNode(l, 25);
    cout<<"\n\nK = 25";
    cout<< "\nK's" <<"\n-Address: "<< p3 <<"\n-Value: "<< p3->data << endl;
    PrintList(l);    
    
    LIST l2;
    Init(l2);
    InsertHead(l2, 7);InsertHead(l2, 2);InsertHead(l2, 1);InsertHead(l2, 5);InsertHead(l2, 3);InsertHead(l2, 6);InsertHead(l2, 19);InsertHead(l2, 9);
    cout<< "\n\nLL Before sorting: ";
    PrintList(l2);
    
    ListSelectionSort(l2);
    cout<< "\nLL After selection sort: ";
    PrintList(l2);
    
    LIST l3;
    Init(l3);;
    InsertHead(l3, 7);InsertHead(l3, 2);InsertHead(l3, 1);InsertHead(l3, 5);InsertHead(l3, 3);InsertHead(l3, 6);InsertHead(l3, 19);InsertHead(l3, 9);
    ListSelectionSort(l3);
    cout<< "\nLL After quick sort: ";
    PrintList(l3);
    
    return 0;
}
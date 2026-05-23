#include <iostream>
using namespace std;

#define MAX 100

class ArrayQueue {
private:
    int arr[MAX];
    int front;
    int rear;

public:
    ArrayQueue() {
        front = -1;
        rear = -1;
    }

    bool isEmpty() const {
        return front == -1 || front > rear;
    }

    bool isFull() const {
        return rear == MAX - 1;
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue Overflow\n";
            return;
        }
        if (isEmpty()) front = 0;
        arr[++rear] = value;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow\n";
            return;
        }
        front++;
    }

    int peek() const {
        if (isEmpty()) { cout << "Queue is empty\n"; return -1;
        }
        return arr[front];
    }

    int getRear() const {
        if (isEmpty()) { cout << "Queue is empty\n"; return -1;
        }
        return arr[rear];
    }

    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        cout << "Array Queue elements: ";
        for (int i = front; i <= rear; i++) {
            cout << arr[i] << " ";
        }
        cout << "\n";
    }

    void clear() {
        front = 0;
        rear = -1;
    }
};


class LinkedListQueue{
private:
    struct Node{
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr) {}
    };
    
    Node* front = nullptr;
    Node* rear = nullptr;
    
public:
    ~LinkedListQueue() { while (front) dequeue(); }
    
    bool isEmpty() const { return front == nullptr; }
    
    void enqueue(int val) {
        Node* node = new Node(val);
        if (rear) rear->next = node;
        else front = node;
        rear = node;
    }
    
    void dequeue() {
        if (isEmpty()) { cout << "Underflow\n"; return; }
        Node* temp = front;
        front = front->next;
        if (!front)
            rear = nullptr;
        delete temp;
    }
    
    int peek() const {
        if(isEmpty()) { cout << "Empty queue\n"; return -1; }
        return front->data;
    }
    int getRear() const {
        if(isEmpty()) { cout << "Empty queue\n"; return -1; }
        return rear->data;
    }
    
    void display() {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        cout<<"Linked List Queue elements: ";
        for(Node* cur = front; cur; cur = cur->next)
            cout<< cur->data << " ";
        cout<<"\n";
    }
    
};


int main() {
    cout<<"Queue - Array implementation\n";
    ArrayQueue q;
    
    q.enqueue(10);
    q.enqueue(20);
    q.enqueue(30);
    q.display();
    cout << "Front element: " << q.peek() << endl;
    
    q.dequeue();
    q.display();
    q.enqueue(40);
    q.enqueue(50);
    q.display();
    
    cout<<"\n\nQueue - Linked List implementation\n";
    LinkedListQueue q2;
    
    q2.enqueue(10);
    q2.enqueue(20);
    q2.enqueue(30);
    q2.display();
    cout << "Front element: " << q2.peek() << endl;
    
    q2.dequeue();
    q2.display();
    q2.enqueue(40);
    q2.enqueue(50);
    q2.display();

    return 0;
}
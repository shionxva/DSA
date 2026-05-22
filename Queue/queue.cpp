#include <iostream>
using namespace std;

#define MAX 100

class Queue {
private:
    int arr[MAX];
    int front;
    int back;
    int currentSize;

public:
    Queue() {
        front = 0;
        back = -1;
        currentSize = 0;
    }

    bool isEmpty() const {
        return currentSize == 0;
    }

    bool isFull() const {
        return currentSize == MAX;
    }

    void enqueue(int value) {
        if (isFull()) {
            cout << "Queue Overflow\n";
            return;
        }
        back = (back + 1) % MAX;
        arr[back] = value;
        currentSize++;
    }

    void dequeue() {
        if (isEmpty()) {
            cout << "Queue Underflow\n";
            return;
        }
        front = (front + 1) % MAX;
        currentSize--;
    }

    int peek() const {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return -1;
        }
        return arr[front];
    }

    int getRear() const {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return -1;
        }
        return arr[back];
    }

    void display() const {
        if (isEmpty()) {
            cout << "Queue is empty\n";
            return;
        }
        cout << "Queue elements: ";
        for (int i = 0; i < currentSize; i++) {
            int index = (front + i) % MAX;
            cout << arr[index] << " ";
        }
        cout << "\n";
    }

    int size() const {
        return currentSize;
    }

    void clear() {
        front = 0;
        back = -1;
        currentSize = 0;
    }
};

int main() {
    Queue q;
    
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
    
    return 0;
}
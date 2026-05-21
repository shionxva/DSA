#include <iostream>
using namespace std;

#define MAX 10

class Stack {
public:
    virtual bool isEmpty() const = 0;
    virtual bool isFull() const = 0;

    virtual void push(int item) = 0;
    virtual void pop() = 0;
    virtual int peek() const = 0;

    virtual void display() const = 0;

    virtual ~Stack() {}
};

class ArrayStack : public Stack {
private:
    int arr[MAX];
    int top;

public:
    ArrayStack() {
        top = -1;
    }

    bool isEmpty() const override {
        return top == -1;
    }

    bool isFull() const override {
        return top == MAX - 1;
    }

    void push(int item) override {
        if (isFull()) {
            cout << "Array Stack Overflow\n";
            return;
        }
        arr[++top] = item;
    }

    void pop() override {
        if (isEmpty()) {
            cout << "Array Stack Underflow\n";
            return;
        }
        top--;
    }

    int peek() const override {
        if (isEmpty()) {
            cout << "Array Stack Empty\n";
            return -1;
        }
        return arr[top];
    }

    void display() const override {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return;
        }

        for (int i = 0; i < top+1; i++) {
            cout << arr[i] << " ";
        }
        
        cout << "<- Current top is here";
        cout << endl;
    }
};

class LinkedListStack : public Stack {
private:
    struct Node {
        int data;
        Node* next;

        Node(int value) {
            data = value;
            next = nullptr;
        }
    };

    Node* top;

public:
    LinkedListStack() {
        top = nullptr;
    }

    ~LinkedListStack() {
        while (!isEmpty()) {
            pop();
        }
    }

    bool isEmpty() const override {
        return top == nullptr;
    }

    bool isFull() const override {
        return false;
    }

    void push(int item) override {
        Node* newNode = new Node(item);

        newNode->next = top;
        top = newNode;
    }

    void pop() override {
        if (isEmpty()) {
            cout << "Linked Stack Underflow\n";
            return;
        }

        Node* temp = top;
        top = top->next;
        delete temp;
    }

    int peek() const override {
        if (isEmpty()) {
            cout << "Linked Stack Empty\n";
            return -1;
        }

        return top->data;
    }

    void display() const override {
        if (isEmpty()) {
            cout << "Stack is empty\n";
            return;
        }

        cout << "Top is here -> ";

        Node* current = top;

        while (current != nullptr) {
            cout << current->data << " ";
            current = current->next;
        }

        cout << endl;
    }
};


int main() {

    cout << "ArrayStack test\n\n";

    ArrayStack s1;

    s1.push(10);
    s1.push(20);
    s1.push(30);
    s1.display();

    cout << "peek(): " << s1.peek() << endl;
    s1.pop();
    s1.display();

    cout << "\nLLStack test\n";

    LinkedListStack s2;

    s2.push(100);
    s2.push(200);
    s2.push(300);

    cout<< "\nKeep in mind this array is being printed in reversed order..\n";
    s2.display();

    cout << "peek(): " << s2.peek() << endl;
    s2.pop();
    s2.display();

    return 0;
}

/* Or use stack lib

stack<T> st; T: datatype; st: stackname

#include <stack>

    stack<int> st;
    //Push
    st.push(10);
    st.push(20);
    
    //Pop top
    st.pop();

    //Check empty
    st.empty()

    //Check size
    st.size()

*/

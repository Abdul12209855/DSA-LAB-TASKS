#include <iostream>
using namespace std;


struct Node {
    int data;
    Node* next;
    Node(int d) : data(d), next(nullptr) {}
};


class BrtQueue {
private:
    Node* head;
public:
    BrtQueue() : head(nullptr) {}	
    ~BrtQueue();

    void addPassenger(int value);
    void addEmergencyPassenger(int value);
    void addSpecialPassenger(int value, int pos);
    bool boardPassenger(int* removedValue = nullptr);
    void display() const;
};


BrtQueue::~BrtQueue() {
    while (head) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}


void BrtQueue::addPassenger(int value) {
    Node* newNode = new Node(value);
    if (!head) {
        head = newNode;
        return;
    }
    Node* temp = head;
    while (temp->next) temp = temp->next; 
    temp->next = newNode;
}


void BrtQueue::addEmergencyPassenger(int value) {
    Node* newNode = new Node(value); 
    newNode->next = head; 
    head = newNode; 
}


void BrtQueue::addSpecialPassenger(int value, int pos) {
    if (pos <= 1 || !head) { 
        addEmergencyPassenger(value);
        return;
    }
    Node* newNode = new Node(value);
    Node* temp = head;
    for (int i = 1; temp->next && i < pos - 1; i++) {
        temp = temp->next;
    }
    newNode->next = temp->next;
    temp->next = newNode;
}


bool BrtQueue::boardPassenger(int* removedValue) {
    if (!head) return false; 
    Node* temp = head;
    if (removedValue) *removedValue = temp->data; 
    head = head->next;
    delete temp; 
    return true;
}


void BrtQueue::display() const {
    Node* temp = head;
    if (!temp) {
        cout << "Queue is empty.\n";
        return;
    }
    cout << "Current Queue: ";
    while (temp) {
        cout << temp->data << " -> ";
        temp = temp->next;
    }
    cout << "NULL\n";
}


int main() {
    BrtQueue brt;

   
    brt.addPassenger(101);
    brt.addPassenger(102);
    brt.addPassenger(103);
    cout << "Initial Queue after adding passengers:\n";
    brt.display();

    
    brt.addEmergencyPassenger(999);
    cout << "After adding an emergency passenger at beginning:\n";
    brt.display();

    
    brt.addSpecialPassenger(555, 2);
    cout << "After inserting special booking passenger at position 2:\n";
    brt.display();

    
    int removed;
    brt.boardPassenger(&removed);
    cout << "Passenger " << removed << " boarded.\n";
    brt.display();

    return 0;
}


#include <iostream>
#include <string>
using namespace std;



struct Node{
    int ID;
    string title;
    string course;
    string dueDate;
    bool completed;
    Node* next;
    

};

Node* head = nullptr;

void displayID(Node* head){
    Node* curr = head;
    while(curr != nullptr){
        cout << curr->ID << " ";
        curr = curr->next;
    }

}

void displayTitle(Node* head){
    Node* curr = head;
    while(curr != nullptr){
        cout << curr->title << " ";
        curr = curr->next;
    }
  
}

void InsertFront(Node*& head, int ID, string title, string course, string dueDate){
    Node* newNode = new Node{ID, title, course, dueDate, false, nulltr};

    newNode->next = head;
    head = newNode;
}

void InsertEnd(Node*& head, int ID, string title, string course, string dueDate){
    Node* newNode = new Node{ID, title, course, dueDate, false, nulltr};
    if (head == nullptr){
        head = newNode;
        return;
    }
    Node* curr = head;
    while(curr->next != nullptr){
        curr = curr->next;
    }
    curr->next = newNode;

}
void Insert(Node*& head, int ID, string title, string course, string dueDate) {

    Node* curr = head;

    while (curr != nullptr) {
        if (curr->ID == ID) {
            cout << "Assignment ID already exists." << endl;
            return;
        }

        curr = curr->next;
    }

    InsertEnd(head, ID, title, course, dueDate);
}
    
    
    
        
    }

void displayAssignments(Node* head) {
    Node* curr = head;

    while (curr != nullptr) {
        cout << "ID: "<< curr ->ID << endl;
        cout << "Title: "<< curr ->title << endl;
        cout << "Course: "<< curr ->course << endl;
        cout << "Due Date: "<< curr ->dueDate << endl;

        if (curr->completed) {
            cour << "Status: Completed" << endl;
        }
        else    {
                cout << "Status: Incomplete" << endl;
        }

        cout << "-------------------" << endl;

        curr = curr->next;
    }
}

bool contains(Node* head, int targetID) {

    Node* curr = head;

    while (curr != nullptr) {

        if (curr->ID == targetID) {
            return true;
        }

        curr = curr->next;
    }

    return false;
}

bool containsTitle(Node* head, string targetTitle) {

    Node* curr = head;

    while (curr != nullptr) {

        if (curr->title == TargetTitle) {
            return true;
        }

        curr = curr->next;
    }
return false;
}

void Delete(Node*& head, int targetID) {

    if (head == nullptr) {
        cout << "Assignment list is empty." << endl;
        return;
    }

    if (head->ID == targetID) {
        Node* temp = head;
        head = head->next;
        delete temp;
        cout << "Assignment deleted." << endl;
        return;
    }

    Node* curr = head;

    while (curr->next != nullptr) {

        if (curr->next->ID == targetID) {
            Node* temp = curr->next;
            curr->next = temp->next;
            delete temp;

            cout << "Assignment deleted." << endl;
            return;
        }

        curr = curr->next;
    }

    cout << "Assignment not found." << endl;
}

void MarkCompleted(Node* head, int targetID) {
        Node* curr = head;

        while (curr != nullptr) {

            if (curr->ID == targetID) {
                curr->completed = true;
                cout << "Assignment marked as completed." << endl;
                return;
            }
    curr = curr->next;
        }
    cout << "Assignment not found." << endl;
}

int main() {
           Node* head = nullptr;
            InsertFront(head, 140, "Final Project", "CSCI 325", "12-01-2026");
            InsertEnd(head,141, "Research Paper", "ENGL 112" , "11-25-2026);
            InsertEnd(head, 142, "Security Report", "CYBR 322" , "11-30-2026);
            displayAssignments(head);
            return 0;
}

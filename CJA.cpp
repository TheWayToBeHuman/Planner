
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

void InsertFront(Node*& head, int ID, string title){
    Node* newNode = new Node{ID, title, nullptr};
    newNode->next = head;
    head = newNode;
}

void InsertEnd(Node*& head, int ID, string title){
    Node* newNode = new Node{ID, title, nullptr};
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



int main(){
    
int one_piece;
InsertFront(head, 140, "Math");
    displayID(head);
    cout << endl;
    displayTitle(head);
int fax;
   fax = contains(head, 140, "Math") ;

   cout << endl << fax;

Insert(head, 325, "CSCI");

displayID(head);

    return 0;
}


#include <iostream>
#include <string>
using namespace std;



struct Node{
    int ID;
     string title;
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
    return;

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
void Insert(Node*head, int ID, string title){
    Node* newNode = new Node{ID, title, nullptr};
    if (head == nullptr){
        head = newNode;
        return;
    }

    Node* curr = head;
    while(curr->next != nullptr){
        if(curr->ID == ID && curr->title == title){
            newNode->next = curr->next;
            curr->next = newNode;
            return;
        }
    }
    
    
    
        
    }




bool contains(Node* head, int targetID, string targetStr){
    Node* curr = head;
    
    
    while (curr != nullptr){
        if(curr->ID == targetID && curr->title == targetStr){
            return true;
            cout << targetStr << " is here.";
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
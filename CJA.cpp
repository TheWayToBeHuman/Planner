
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

void InsertTitlefront(Node*& head, int ID, string title){
    Node* newNode = new Node{ID, title};
    newNode->next = head;
    head = newNode;
    return;

}
int main(){
    
int one_piece;
InsertTitlefront(head, 140, "Math");
    displayID(head);
    cout << endl;
    displayTitle(head);







    return 0;
}
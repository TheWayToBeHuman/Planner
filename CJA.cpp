
#include <iostream>
#include <limits>
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
    Node* newNode = new Node{ID, title, course, dueDate, false, nullptr};

    newNode->next = head;
    head = newNode;
}

void InsertEnd(Node*& head, int ID, string title, string course, string dueDate){
    Node* newNode = new Node{ID, title, course, dueDate, false, nullptr};
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
    
    
    
        
    

void displayAssignments(Node* head) {
    Node* curr = head;

    if (curr == nullptr) {
        cout << "No assignments found." << endl;
        return;
    }

    while (curr != nullptr) {
        cout << "ID: "<< curr ->ID << endl;
        cout << "Title: "<< curr ->title << endl;
        cout << "Course: "<< curr ->course << endl;
        cout << "Due Date: "<< curr ->dueDate << endl;

        if (curr->completed) {
            cout << "Status: Completed" << endl;
        }
        else    {
                cout << "Status: Incomplete" << endl;
        }

        cout << "-------------------" << endl;

        curr = curr->next;
    }
}

void searchAssignments(Node* head, const string& searchTerm) {
    Node* curr = head;
    bool found = false;

    while (curr != nullptr) {
        if (to_string(curr->ID) == searchTerm || curr->title == searchTerm) {
            cout << "ID: " << curr->ID << endl;
            cout << "Title: " << curr->title << endl;
            cout << "Course: " << curr->course << endl;
            cout << "Due Date: " << curr->dueDate << endl;
            cout << "Status: "
                 << (curr->completed ? "Completed" : "Incomplete") << endl;
            cout << "-------------------" << endl;
            found = true;
        }
        curr = curr->next;
    }

    if (!found) {
        cout << "No assignment found matching \"" << searchTerm << "\"." << endl;
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

        if (curr->title == targetTitle) {
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

struct TreeNode {
    int dateKey;
    Node* assignment;
    TreeNode* left;
    TreeNode* right;
};

int DateToKey(string date) {
    int year, month, day;
    if (date[4] == '-') {
        year  = stoi(date.substr(0, 4));
        month = stoi(date.substr(5, 2));
        day   = stoi(date.substr(8, 2));
    }
    else {
        month = stoi(date.substr(0, 2));
        day   = stoi(date.substr(3, 2));
        year  = stoi(date.substr(6, 4));
    }
    return year * 10000 + month * 100 + day;
}

bool ComesBefore(int dateA, int idA, int dateB, int idB) {
    if (dateA != dateB) {
        return dateA < dateB;
    }
    return idA < idB;
}

void BSTInsert(TreeNode*& root, Node* assignment) {
    int key = DateToKey(assignment->dueDate);
    if (root == nullptr) {
        root = new TreeNode{key, assignment, nullptr, nullptr};
        return;
    }
    if (ComesBefore(key, assignment->ID, root->dateKey, root->assignment->ID)) {
        BSTInsert(root->left, assignment);
    }
    else {
        BSTInsert(root->right, assignment);
    }
}

void BSTBuildFromList(TreeNode*& root, Node* head) {
    Node* curr = head;
    while (curr != nullptr) {
        BSTInsert(root, curr);
        curr = curr->next;
    }
}

TreeNode* BSTFindMin(TreeNode* root) {
    while (root != nullptr && root->left != nullptr) {
        root = root->left;
    }
    return root;
}

bool BSTDelete(TreeNode*& root, int dateKey, int ID) {
    if (root == nullptr) {
        return false;
    }
    if (dateKey == root->dateKey && ID == root->assignment->ID) {
        if (root->left == nullptr) {
            TreeNode* temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == nullptr) {
            TreeNode* temp = root;
            root = root->left;
            delete temp;
        }
        else {
            TreeNode* successor = BSTFindMin(root->right);
            root->dateKey = successor->dateKey;
            root->assignment = successor->assignment;
            BSTDelete(root->right, successor->dateKey, successor->assignment->ID);
        }
        return true;
    }
    if (ComesBefore(dateKey, ID, root->dateKey, root->assignment->ID)) {
        return BSTDelete(root->left, dateKey, ID);
    }
    return BSTDelete(root->right, dateKey, ID);
}

void BSTDisplayByDueDate(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    BSTDisplayByDueDate(root->left);
    Node* a = root->assignment;
    cout << a->dueDate << "  [" << a->ID << "] " << a->title
         << " (" << a->course << ") - "
         << (a->completed ? "Completed" : "Incomplete") << endl;
    BSTDisplayByDueDate(root->right);
}

int BSTSearchByDate(TreeNode* root, int dateKey) {
    if (root == nullptr) {
        return 0;
    }
    int found = 0;
    if (dateKey <= root->dateKey) {
        found += BSTSearchByDate(root->left, dateKey);
    }
    if (dateKey == root->dateKey) {
        cout << "  [" << root->assignment->ID << "] " << root->assignment->title
             << " (" << root->assignment->course << ")" << endl;
        found++;
    }
    if (dateKey >= root->dateKey) {
        found += BSTSearchByDate(root->right, dateKey);
    }
    return found;
}

void BSTDueBetween(TreeNode* root, int startKey, int endKey) {
    if (root == nullptr) {
        return;
    }
    if (startKey <= root->dateKey) {
        BSTDueBetween(root->left, startKey, endKey);
    }
    if (root->dateKey >= startKey && root->dateKey <= endKey) {
        cout << "  " << root->assignment->dueDate << "  [" << root->assignment->ID
             << "] " << root->assignment->title << endl;
    }
    if (endKey >= root->dateKey) {
        BSTDueBetween(root->right, startKey, endKey);
    }
}

Node* BSTNextDue(TreeNode* root) {
    if (root == nullptr) {
        return nullptr;
    }
    Node* leftResult = BSTNextDue(root->left);
    if (leftResult != nullptr) {
        return leftResult;
    }
    if (!root->assignment->completed) {
        return root->assignment;
    }
    return BSTNextDue(root->right);
}

void BSTPreorder(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    cout << root->assignment->ID << " ";
    BSTPreorder(root->left);
    BSTPreorder(root->right);
}

int BSTHeight(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = BSTHeight(root->left);
    int rightHeight = BSTHeight(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

void BSTClear(TreeNode*& root) {
    if (root == nullptr) {
        return;
    }
    BSTClear(root->left);
    BSTClear(root->right);
    delete root;
    root = nullptr;
}

bool AddAssignment(Node*& head, TreeNode*& root, int ID, string title,
                   string course, string dueDate) {
    if (contains(head, ID)) {
        cout << "Assignment ID " << ID << " already exists." << endl;
        return false;
    }
    InsertEnd(head, ID, title, course, dueDate);
    Node* curr = head;
    while (curr->next != nullptr) {
        curr = curr->next;
    }
    BSTInsert(root, curr);
    return true;
}

void DeleteAssignment(Node*& head, TreeNode*& root, int ID) {
    Node* curr = head;
    while (curr != nullptr && curr->ID != ID) {
        curr = curr->next;
    }
    if (curr == nullptr) {
        cout << "Assignment not found." << endl;
        return;
    }
    BSTDelete(root, DateToKey(curr->dueDate), ID);
    Delete(head, ID);
}
TreeNode* insertBST(TreeNode* root, Node* assignment) {
    BSTInsert(root, assignment);
    return root;
}

void displayByDueDate(TreeNode* root) {
    BSTDisplayByDueDate(root);
}
int main() {
    Node* head = nullptr;
    TreeNode* dueDateTree = nullptr;

    InsertEnd(head, 140, "Final Project", "CSCI 325", "2026-12-01");
    InsertEnd(head, 141, "Research Paper", "ENGL 112", "2026-11-25");
    InsertEnd(head, 142, "Security Report", "CYBR 322", "2026-11-30");

    Node* current = head;
    while (current != nullptr) {
        dueDateTree = insertBST(dueDateTree, current);
        current = current->next;
    }

    int choice = 0;
    while (choice != 7) {
        cout << "\nPlanner\n"
             << "1. Add assignment\n"
             << "2. View all assignments\n"
             << "3. Search for an assignment\n"
             << "4. Display assignments by due date\n"
             << "5. Mark assignment as complete\n"
             << "6. Delete assignment\n"
             << "7. Exit\n"
             << "Choose an option: ";

        if (!(cin >> choice)) {
            cout << "Please enter a number from 1 to 7." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n');

        if (choice == 1) {
            int ID;
            string title;
            string course;
            string dueDate;

            cout << "Assignment ID: ";
            if (!(cin >> ID)) {
                cout << "Assignment ID must be a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            cout << "Title: ";
            getline(cin, title);
            cout << "Course: ";
            getline(cin, course);
            cout << "Due date (YYYY-MM-DD): ";
            getline(cin, dueDate);

            if (AddAssignment(head, dueDateTree, ID, title, course, dueDate)) {
                cout << "Assignment added." << endl;
            }
        }
        else if (choice == 2) {
            displayAssignments(head);
        }
        else if (choice == 3) {
            string searchTerm;
            cout << "Enter assignment ID or exact title: ";
            getline(cin, searchTerm);
            searchAssignments(head, searchTerm);
        }
        else if (choice == 4) {
            displayByDueDate(dueDateTree);
        }
        else if (choice == 5 || choice == 6) {
            int ID;
            cout << "Assignment ID: ";
            if (!(cin >> ID)) {
                cout << "Assignment ID must be a number." << endl;
                cin.clear();
                cin.ignore(numeric_limits<streamsize>::max(), '\n');
                continue;
            }
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            if (choice == 5) {
                MarkCompleted(head, ID);
            }
            else {
                DeleteAssignment(head, dueDateTree, ID);
            }
        }
        else if (choice != 7) {
            cout << "Please choose a number from 1 to 7." << endl;
        }
    }

    BSTClear(dueDateTree);
    while (head != nullptr) {
        Node* next = head->next;
        delete head;
        head = next;
    }
}

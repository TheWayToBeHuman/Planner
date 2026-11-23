
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

// ===================== BINARY SEARCH TREE =====================
// The BST organizes assignments by DUE DATE.
//   - every assignment in a node's LEFT subtree is due EARLIER
//   - every assignment in a node's RIGHT subtree is due LATER
// If two assignments share a due date, the smaller ID goes first.
//
// The linked list still OWNS the assignment records. Each tree node just
// points to the assignment's Node in the linked list, so there is only one
// copy of each assignment. (Marking one completed in the list shows up in
// the tree too.)
//
// In-order traversal (left, node, right) visits assignments in
// chronological order, which is the "display by due date" feature.

struct TreeNode {
    int dateKey;          // due date as YYYYMMDD so it compares correctly
    Node* assignment;     // the record stored in the linked list
    TreeNode* left;
    TreeNode* right;
};

// Turn a due date into a number YYYYMMDD so dates compare correctly.
// Accepts "YYYY-MM-DD" (e.g. "2026-12-01") or "MM-DD-YYYY" (e.g. "12-01-2026").
int DateToKey(string date) {
    int year, month, day;
    if (date[4] == '-') {                 // YYYY-MM-DD
        year  = stoi(date.substr(0, 4));
        month = stoi(date.substr(5, 2));
        day   = stoi(date.substr(8, 2));
    }
    else {                                // MM-DD-YYYY
        month = stoi(date.substr(0, 2));
        day   = stoi(date.substr(3, 2));
        year  = stoi(date.substr(6, 4));
    }
    return year * 10000 + month * 100 + day;
}

// Ordering rule for the tree: earlier date first, then smaller ID.
bool ComesBefore(int dateA, int idA, int dateB, int idB) {
    if (dateA != dateB) {
        return dateA < dateB;
    }
    return idA < idB;
}

// INSERT: walk left if the assignment is due earlier, right if later,
// and attach the new node where we reach nullptr. O(log n) on average.
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

// Build the tree from every assignment currently in the linked list.
void BSTBuildFromList(TreeNode*& root, Node* head) {
    Node* curr = head;
    while (curr != nullptr) {
        BSTInsert(root, curr);
        curr = curr->next;
    }
}

// Smallest node in a subtree = keep going left.
TreeNode* BSTFindMin(TreeNode* root) {
    while (root != nullptr && root->left != nullptr) {
        root = root->left;
    }
    return root;
}

// DELETE the node for (dateKey, ID). Returns true if it was found.
// Three cases:
//   1. Leaf (no children): just remove it.
//   2. One child: replace the node with its child.
//   3. Two children: copy the in-order successor (smallest node in the
//      right subtree) into this node, then delete the successor instead.
// This only removes the TREE node; the linked list deletes the record.
bool BSTDelete(TreeNode*& root, int dateKey, int ID) {
    if (root == nullptr) {
        return false;                                     // not found
    }
    if (dateKey == root->dateKey && ID == root->assignment->ID) {
        if (root->left == nullptr) {                      // case 1 or 2
            TreeNode* temp = root;
            root = root->right;
            delete temp;
        }
        else if (root->right == nullptr) {                // case 2
            TreeNode* temp = root;
            root = root->left;
            delete temp;
        }
        else {                                            // case 3
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

// IN-ORDER traversal = assignments in due-date order.
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

// SEARCH: print every assignment due on one date.
// Skips any subtree that can't contain that date. Returns how many matched.
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

// RANGE: print assignments due between two dates (inclusive), in order.
// Useful for "what's due this week?"
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

// NEXT DUE: the earliest INCOMPLETE assignment (in-order, stop at first match).
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

// PRE-ORDER traversal (node, left, right) = shows the shape of the tree.
void BSTPreorder(TreeNode* root) {
    if (root == nullptr) {
        return;
    }
    cout << root->assignment->ID << " ";
    BSTPreorder(root->left);
    BSTPreorder(root->right);
}

// HEIGHT = number of levels in the tree.
int BSTHeight(TreeNode* root) {
    if (root == nullptr) {
        return 0;
    }
    int leftHeight = BSTHeight(root->left);
    int rightHeight = BSTHeight(root->right);
    return 1 + (leftHeight > rightHeight ? leftHeight : rightHeight);
}

// Free every tree node (post-order: children before parent).
// Does NOT delete the assignments - the linked list owns those.
void BSTClear(TreeNode*& root) {
    if (root == nullptr) {
        return;
    }
    BSTClear(root->left);
    BSTClear(root->right);
    delete root;
    root = nullptr;
}

// ---------- helpers that keep the list and the tree in sync ----------

// Add to both structures (rejects duplicate IDs).
void AddAssignment(Node*& head, TreeNode*& root, int ID, string title,
                   string course, string dueDate) {
    if (contains(head, ID)) {
        cout << "Assignment ID " << ID << " already exists." << endl;
        return;
    }
    InsertEnd(head, ID, title, course, dueDate);
    Node* curr = head;
    while (curr->next != nullptr) {      // the new node is the last one
        curr = curr->next;
    }
    BSTInsert(root, curr);
}

// Delete from both: remove the tree node first (it points at the record),
// then let the linked list delete the record itself.
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
// ---------- names used by the group's main() ----------
TreeNode* insertBST(TreeNode* root, Node* assignment) {
    BSTInsert(root, assignment);
    return root;
}

void displayByDueDate(TreeNode* root) {
    BSTDisplayByDueDate(root);
}
// =================== END BINARY SEARCH TREE ===================

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

    displayByDueDate(dueDateTree);
}

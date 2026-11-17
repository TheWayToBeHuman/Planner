// Free every node so the program does not leak memory.
void ClearList(Node*& head) {
    while (head != nullptr) {
        Node* temp = head;
        head = head->next;
        delete temp;
    }
}

void section(string title) {
    cout << "\n========== " << title << " ==========" << endl;
}

int main() {
    Node* head = nullptr;

    section("1. INSERT (front, end, and duplicate check)");
    InsertFront(head, 140, "Final Project", "CSCI 325", "12-01-2026");
    InsertEnd(head, 141, "Research Paper", "ENGL 112", "11-25-2026");
    InsertEnd(head, 142, "Security Report", "CYBR 322", "11-30-2026");
    Insert(head, 143, "Lab 7", "CSCI 325", "11-20-2026");
    InsertFront(head, 139, "Quiz Review", "MATH 201", "11-18-2026");
    cout << "Trying to insert duplicate ID 141: ";
    Insert(head, 141, "Duplicate", "TEST 000", "01-01-2027");

    section("2. TRAVERSAL - all assignments");
    displayAssignments(head);
    cout << "IDs in list order: ";
    displayID(head);
    cout << endl << "Titles: ";
    displayTitle(head);
    cout << endl;

    section("3. SEARCH");
    cout << "Contains ID 142? "   << (contains(head, 142) ? "Yes" : "No") << endl;
    cout << "Contains ID 999? "   << (contains(head, 999) ? "Yes" : "No") << endl;
    cout << "Contains \"Lab 7\"? " << (containsTitle(head, "Lab 7") ? "Yes" : "No") << endl;
    cout << "Contains \"Essay\"? " << (containsTitle(head, "Essay") ? "Yes" : "No") << endl;

    section("4. UPDATE - mark completed");
    MarkCompleted(head, 141);
    MarkCompleted(head, 139);
    cout << "Mark ID 500: ";
    MarkCompleted(head, 500);

    section("5. DELETE (head, middle, missing)");
    cout << "Delete 139 (head): ";    Delete(head, 139);
    cout << "Delete 142 (middle): ";  Delete(head, 142);
    cout << "Delete 777 (missing): "; Delete(head, 777);

    section("6. FINAL LIST");
    displayAssignments(head);

    ClearList(head);
    return 0;
}

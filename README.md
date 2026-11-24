# Planner

## How it works

The planner stores assignments in a singly linked list. Each assignment has
an ID, title, course, due date, and completion status. The list is the owner of
the assignment records and supports adding, displaying, searching, completing,
and deleting assignments.

A binary search tree (BST) provides due-date ordering. Each tree node points to
an assignment in the linked list rather than making a second copy of it. This
keeps the assignment data in one place, so changes such as marking an assignment
complete are reflected wherever that assignment is displayed.

### Due-date ordering

Due dates are converted to an integer in `YYYYMMDD` form before they are stored
as tree keys. The date conversion helper accepts `YYYY-MM-DD` and `MM-DD-YYYY`.
The tree places earlier dates on the left and later dates on the right; when
two assignments have the same due date, the one with the smaller ID comes
first.

Displaying the tree uses an in-order traversal (left, node, right), so
assignments appear in chronological order. The tree also includes helpers to
search for assignments on a date, list assignments within a date range, find
the earliest incomplete assignment, print the tree in preorder, calculate its
height, and free its nodes.

### Keeping the structures in sync

Adding an assignment first checks for a duplicate ID, then adds the record to
the linked list and inserts a pointer to it into the tree. Deleting an
assignment removes its tree node before deleting the linked-list record that
the tree node points to. The tree deletion handles nodes with no children, one
child, or two children; in the two-child case it replaces the node with its
in-order successor.

### Running the planner

The program starts with three sample assignments and displays a menu that lets
you add an assignment, view all assignments, search by ID or exact title,
display assignments by due date, mark an assignment complete, delete an
assignment, or exit. New assignments are entered with a title, course, ID, and
due date.

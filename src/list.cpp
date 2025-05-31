#include "list.h"
#include <stdexcept>

// === LinkedList core ===
LinkedList::LinkedList() = default;

/* TODO: deep-copy constructor 
 * Implement a copy constructor that creates a deep copy of the linked list.
 * This means:
 * 1. Create a new empty list
 * 2. Use the deepCopy helper function to copy the chain
 * 3. Set the head pointer to the result of deepCopy
 * 
 * Example:
 * If other is [1 → 2 → 3]
 * Create a new list with nodes containing 1, 2, and 3
 * Do not just copy the head pointer (that would be a shallow copy)
 * 
 * Hint: Use the deepCopy helper function to do the actual copying
*/
LinkedList::LinkedList(const LinkedList& other) {
    head = deepCopy(other.head);
}

/* TODO: assignment operator using copy-and-swap
 * Implement the assignment operator using the copy-and-swap idiom.
 * This means:
 * 1. Take the parameter by value (this creates a copy)
 * 2. Swap the contents of this list with the copy
 * 3. Return *this
 * 
 * The copy-and-swap idiom provides strong exception safety
 * and automatically handles self-assignment.
 * 
 * Example:
 * LinkedList a, b;
 * a = b;  // This should copy b's contents to a
*/
LinkedList& LinkedList::operator=(LinkedList rhs) {
     std::swap(head, rhs.head);
    return *this;
}

LinkedList::~LinkedList() { freeChain(head); }

void LinkedList::prepend(int value) {
    head = new Node{value, head};
}

/* TODO: append implementation
 * Add a new node with the given value at the end of the list.
 * Steps:
 * 1. Create a new node with the given value
 * 2. If the list is empty, set head to the new node
 * 3. Otherwise, traverse to the last node
 * 4. Set the last node's next pointer to the new node
 * 
 * Example:
 * If list is [1 → 2] and we append(3)
 * Result should be [1 → 2 → 3]
*/
void LinkedList::append(int value) {
    Node* newNode = new Node{value, nullptr};
    if (isEmpty()) {
        head = newNode;
    } else {
        Node* current = head;
        while (current->next) {
            current = current->next;
        }
        current->next = newNode;
    }
}

/* TODO: removeFront implementation
 * Remove and return the first element from the list.
 * Steps:
 * 1. Check if list is empty (use isEmpty())
 * 2. Save the data from the first node
 * 3. Update head to point to the second node
 * 4. Delete the first node
 * 5. Return the saved data
 * 
 * Example:
 * If list is [1 → 2 → 3]
 * removeFront() should return 1 and leave [2 → 3]
*/
   int LinkedList::removeFront() {
    if (isEmpty()) throw runtime_error("removeFront on empty list");
    Node* temp = head;
    int value = head->data;
    head = head->next;
    delete temp;
    return value;
}


bool LinkedList::isEmpty() const { return head == nullptr; }

void LinkedList::print(ostream& out) const {
    out << '[';
    for (Node* cur = head; cur; cur = cur->next) {
        out << cur->data;
        if (cur->next) out << " → ";
    }
    out << ']';
}

// === private helpers ===
/* TODO: deepCopy implementation
 * Create a deep copy of a linked list starting from the given node.
 * Steps:
 * 1. If the source node is null, return null
 * 2. Create a new node with the same data as the source
 * 3. Recursively copy the rest of the list
 * 4. Return the new node
 * 
 * Example:
 * If src points to [1 → 2 → 3]
 * Return a new list [1 → 2 → 3] with new nodes
*/
LinkedList::Node* LinkedList::deepCopy(Node* src) {
   if (!src) return nullptr;
Node* newNode = new Node{src->data, deepCopy(src->next)};
return newNode;
}

void LinkedList::freeChain(Node* n) {
    while (n) {
        Node* next = n->next;
        delete n;
        n = next;
    }
}

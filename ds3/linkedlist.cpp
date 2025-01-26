#include <algorithm>
#include <iostream>
#include <vector>

// Node structure for Linked List
struct Node {
  int data;
  Node *next;
  Node(int value) : data(value), next(nullptr) {}
};

// Linked List class
class LinkedList {
private:
  Node *head;

public:
  LinkedList() : head(nullptr) {}

  // Insert at the end of the list
  void insert(int value) {
    Node *newNode = new Node(value);
    if (!head) {
      head = newNode;
      return;
    }
    Node *temp = head;
    while (temp->next) {
      temp = temp->next;
    }
    temp->next = newNode;
  }

  // Insert at the beginning of the list
  void insertAtBeginning(int value) {
    Node *newNode = new Node(value);
    newNode->next = head;
    head = newNode;
  }

  // Delete a node by value
  void deleteValue(int value) {
    if (!head) {
      std::cout << "List is empty." << std::endl;
      return;
    }
    if (head->data == value) {
      Node *temp = head;
      head = head->next;
      delete temp;
      return;
    }
    Node *temp = head;
    while (temp->next && temp->next->data != value) {
      temp = temp->next;
    }
    if (temp->next) {
      Node *toDelete = temp->next;
      temp->next = temp->next->next;
      delete toDelete;
    } else {
      std::cout << "Value not found in the list." << std::endl;
    }
  }

  // Search for a value in the list
  bool search(int value) {
    Node *temp = head;
    while (temp) {
      if (temp->data == value) {
        return true;
      }
      temp = temp->next;
    }
    return false;
  }

  // Display the list
  void display() {
    Node *temp = head;
    while (temp) {
      std::cout << temp->data << " ";
      temp = temp->next;
    }
    std::cout << std::endl;
  }

  // Reverse the list
  void reverse() {
    Node *prev = nullptr;
    Node *current = head;
    Node *next = nullptr;
    while (current) {
      next = current->next;
      current->next = prev;
      prev = current;
      current = next;
    }
    head = prev;
  }

  // Concatenate another list
  void concatenate(LinkedList &other) {
    if (!head) {
      head = other.head;
      return;
    }
    Node *temp = head;
    while (temp->next) {
      temp = temp->next;
    }
    temp->next = other.head;
    other.head = nullptr; // Optional: Clear the other list's head
  }
};

int main() {
  LinkedList list1, list2;

  int n1, n2, value;

  std::cout << "Enter the number of elements in the first list: ";
  std::cin >> n1;
  std::cout << "Enter elements of the first list: ";
  for (int i = 0; i < n1; ++i) {
    std::cin >> value;
    list1.insert(value);
  }

  std::cout << "Enter the number of elements in the second list: ";
  std::cin >> n2;
  std::cout << "Enter elements of the second list: ";
  for (int i = 0; i < n2; ++i) {
    std::cin >> value;
    list2.insert(value);
  }

  std::cout << "First List: ";
  list1.display();

  std::cout << "Second List: ";
  list2.display();

  std::cout << "Reversing the first list...\n";
  list1.reverse();
  std::cout << "First List after reversal: ";
  list1.display();

  std::cout << "Concatenating the second list to the first list...\n";
  list1.concatenate(list2);
  std::cout << "First List after concatenation: ";
  list1.display();

  return 0;
}

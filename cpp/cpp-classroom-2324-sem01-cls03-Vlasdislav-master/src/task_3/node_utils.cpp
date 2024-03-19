#include "node_utils.hpp"

void revert(Node** head) {
    Node* prev = nullptr;
    Node* current = *head;
    Node* next = nullptr;
    while (current != nullptr) {
        next = current->next;
        current->next = prev;
        prev = current;
        current = next;
    }
    *head = prev;
}

void cleanup(Node* &head) {
    Node* current = nullptr;
    while (head != nullptr) {
        current = head;
        head = head->next;
        delete current;
    }   
}
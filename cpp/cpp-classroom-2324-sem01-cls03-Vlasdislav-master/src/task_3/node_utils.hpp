#pragma once

struct Node {
    int value = 0;
    Node* next = nullptr;
};

void revert(Node** head);
void cleanup(Node* &head);

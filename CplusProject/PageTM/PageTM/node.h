#pragma once
#ifndef NODE_H
#define NODE_H
#include "Page.h"
class Node {
public:
    int data;
    Node* prev;
    Node* next;
    Node(int value) : data(value), prev(nullptr), next(nullptr) {}
};


#endif
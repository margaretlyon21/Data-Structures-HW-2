#ifndef DECK_H
#define DECK_H

#include "Node.h"

class Deck {
private:
    Node* front;
    Node* rear;
    int size;
public:
    Deck();
    bool isEmpty();
    void enqueue(int card);
    int dequeue();
    int getSize();
};

#endif


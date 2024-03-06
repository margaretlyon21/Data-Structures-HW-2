#ifndef SIDE_H
#define SIDE_H

class Side {
public:
    int size;
    int data[5];
    int index;

    Side();
    void Push(int input);
    int Pop();
    bool isFull();
    bool isEmpty();
    int top();
    int length();
    void empty();
};

#endif

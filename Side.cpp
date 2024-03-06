#include "Side.h"
#include "Exception.h"

Side::Side() : size(5), index(0) {}

void Side::Push(int input) {
    if (isFull()) {
        throw stackOverflow();
    }
    data[index++] = input;
}

int Side::Pop() {
    if (isEmpty()) {
        throw stackUnderflow();
    }
    return data[--index];
}

bool Side::isFull() {
    return index >= size;
}

bool Side::isEmpty() {
    return index <= 0;
}

int Side::top() {
    if (isEmpty()) {
        throw stackUnderflow();
    }
    return data[index - 1];
}

int Side::length() {
    return index;
}

void Side::empty() {
    while (!isEmpty()) {
        Pop();
    }
}

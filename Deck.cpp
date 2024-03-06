#include "Deck.h"
#include "Exception.h"
#include <chrono>
#include <random>

Deck::Deck() : front(nullptr), rear(nullptr), size(0) {
    unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
    std::default_random_engine generator(seed);
    std::uniform_int_distribution<int> distribution(1, 13);

    for (int i = 0; i < 33; i++) {
        int random = distribution(generator);
        enqueue(random);
    }
}

bool Deck::isEmpty() {
    return front == nullptr;
}

void Deck::enqueue(int card) {
    Node* temp = new Node(card);
    if (isEmpty()) {
        front = rear = temp;
        return;
    }
    rear->next = temp;
    rear = temp;
    size++;
}

int Deck::dequeue() {
    if (isEmpty()) {
        throw queueUnderflow();
    }
    int data = front->data;
    Node* temp = front;
    front = front->next;
    size -= 1;
    if (isEmpty()) {
        rear = nullptr;
    }
    delete (temp);
    return data;
}

int Deck::getSize() {
    return size;
}

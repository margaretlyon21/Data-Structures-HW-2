#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>

#include "Exception.h"

using namespace std;

class Node
{
    public:
        int data;
        Node* next;
        Node(int val) : data(val), next(nullptr){}
};

class Deck
{
    private:
    Node* front;
    Node* rear;
    int size;
    public:
    Deck() : front(nullptr), rear(nullptr), size(0) {
        unsigned seed = std::chrono::system_clock::now().time_since_epoch().count();
        std::default_random_engine generator(seed);
        std::uniform_int_distribution<int> distribution(1, 13);

        for (int i = 0; i < 32; i++) {
            int random = distribution(generator);
            enqueue(random);
        }
    }

    bool isEmpty(){
        return front == nullptr;
    }

    void enqueue(int card){
        Node* temp =  new Node(card);
        if (isEmpty()){
            front = rear = temp;
            return;
        }
        rear->next = temp;
        rear = temp;
        size++;
        cout << card << " succefully added, current size now" << size << "\n";
    }

    int dequeue(){
        if (isEmpty()){
            throw queueUnderflow();
        }
        int data = front->data;
        Node* temp = front;
        front = front->next;
        size -= 1;
        if (isEmpty()){
            rear = nullptr;
        }
        delete (temp);
        cout << data << " succesfully removed\n";
        return data;
    }
    int getSize(){
        return size;
    }
};

class Side
{
    public:
    int size;
    int data[5];
    int index;

    Side() : size(5), index(0) {}

  //Pushes an element to the top of the stack
  void Push(int input){
    if(isFull()){
      throw stackOverflow();
    }
    data[index++] = input;
  }

  //Pops an element from the top of the stack
  int Pop(){
    if (isEmpty()){
      throw stackUnderflow();
    }
    return data[--index];
    
    }

  //Checks if stack is full
  bool isFull(){
    return index >= size;
  }
  //Checks if stack is empty
  bool isEmpty(){
    return index <= 0;
  }

  //Returns element at top of stack
  int top(){
    if (isEmpty()){
      throw stackUnderflow();
    }
    return data[index - 1];
  }

  //Returns size of stack
  int length(){
    return index;
  }

  //Empties the stack
  void empty(){
    while (!isEmpty()){
      Pop();
    }
  }
};

string faceValues(int card)
{
    if (card == 1){
        return "ace";
    }
    if (card == 2){
        return "two";
    }
    if (card == 3){
        return "three";
    }
    if (card == 4){
        return "four";
    }
    if (card == 5){
        return "five";
    }
    if (card == 6){
        return "six";
    }
    if (card == 7){
        return "seven";
    }
   if (card == 8){
        return "eight";
    }
    if (card == 9){
        return "nine";
    }
    if (card == 10){
        return "ten";
    }
    if (card == 11){
        return "jack";
    }
    if (card == 12){
        return "queen";
    }
    if (card == 13){
        return "king";
    }
    return "";
}

void turn(Deck* playersDeck, Side* playersSide, Deck* computersDeck, Side* computersSide)
{

    // Drawing the card
    int draw = playersDeck->dequeue();
    int compDraw = computersDeck->dequeue();
    cout << draw << " successfully dequeued from your deck\n";
    cout << compDraw << " successfully dequeed from computer deck\n";
    int draw2 = 0;
    int total = 0;
    cout << "You drew a " << faceValues(draw) << "!" << endl;
    cout << "Do you want to....\n"
        << "Play just this card (1)\n"
        << "Place this card on your side pile and play a new card (2)\n"
        << "Play this card and the card on top of your side pile (3)" << endl;

    int choice;
    cin >> choice;
    while (choice != 1 && choice != 2 && choice != 3)
    {
        cout << "Invalid choice! Please try again." << endl;
        cin >> choice;
    }

    if (choice == 1)
    {
        //play just this card 
        cout << "You played a " << faceValues(draw) << "!" << endl;
        cout << "Its the computers turn! The computer played a " << faceValues(compDraw) << endl;
        if (compDraw > draw)
        {
            cout << "Computer wins this round! taking both cards..." << endl;
            computersDeck->enqueue(compDraw);
            cout << compDraw << " successfully enqueued to computer deck\n";
            computersDeck->enqueue(draw);
            cout << draw << " successfully enqueued to computer deck\n";
        }
        else
        {
            cout << "You win this round! adding both cards to your deck... " << endl;
            playersDeck->enqueue(compDraw);
            cout << compDraw << " successfully enqueued to your deck " << endl;
            playersDeck->enqueue(draw);
            cout << draw << " successfully enqueued to your deck\n";

        }
    }

    if (choice == 2)
    {
        //add this card to your side pile and play another
        cout << "Adding " << draw << " to the side pile.....\n";
        playersSide->Push(draw);
        draw2 = playersDeck->dequeue();
        cout << "You drew a " << faceValues(draw2) << "!" << endl;
        cout << "You played the " << faceValues(draw2) << "!" << endl;
        if (compDraw > draw2)
        {
            cout << "Computer wins this round! taking both cards..." << endl;
            computersDeck->enqueue(draw2);
            computersDeck->enqueue(compDraw);
        }
        else
        {
            cout << "You win this round! adding both cards to your deck... " << endl;
            playersDeck->enqueue(compDraw);
            playersDeck->enqueue(draw2);
        }
    }

    if (choice == 3)
    {
        //play this card and one from the side
        int sideDraw = playersSide->Pop();
        cout << "You picked up a " << sideDraw << "from your side pile. " << endl;
        total = sideDraw + draw;
        cout << "You played the "<< faceValues(draw) << " and the " << faceValues(sideDraw) << " for a total of " << total << endl;
        if (compDraw > total)
        {
            cout << "Computer wins this round! taking all 3 cards..." << endl;
            computersDeck->enqueue(draw);
            computersDeck->enqueue(sideDraw);
            computersDeck->enqueue(compDraw);
        }
        else
        {
            cout << "You win this round! adding all 3 cards to your deck... " << endl;
            playersDeck->enqueue(compDraw);
            playersDeck->enqueue(sideDraw);
            playersDeck->enqueue(draw);
        }
    }
    return;
}

int main()
{
    Deck playerDeck;
    Side playerSide;
    Deck computerDeck;
    Side computerSide;
    cout << "Welcome to War! \nEnter 1 if you would like to play until someone rins out of cards.\nEnter 2 if you would like to play a set number of rounds!" << endl;
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        cout << "************** Starting Game... **************" << endl;
        while(!playerDeck.isEmpty() && !computerDeck.isEmpty())
        {
            cout << "-------Turn Start-------" << endl;
            turn(&playerDeck, &playerSide, &computerDeck, &computerSide);
            cout << "You have " << playerDeck.getSize() << " cards" << endl;
            cout << "The computer has " << computerDeck.getSize() << " cards" << endl;
        }
    }
    else if (choice == 2) 
    {
        cout << "How many rounds would you like to play?" << endl;
        int rounds;
        cin >> rounds;
        cout << "************** Starting Game... **************" << endl;
        for (int i = 0; i < rounds; i++){
            cout << "-------Turn Start-------" << endl;
            turn(&playerDeck, &playerSide, &computerDeck, &computerSide);
            cout << "You have " << playerDeck.getSize() << " cards" << endl;
            cout << "The computer has " << computerDeck.getSize() << " cards" << endl;
        }
    }
}
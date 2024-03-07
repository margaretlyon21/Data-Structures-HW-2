#include <iostream>
#include <string>
#include <fstream>
#include <sstream>
#include <random>
#include <chrono>

#include "Exception.h"
#include "Node.h"
#include "Deck.h"
#include "Side.h"

using namespace std;

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

void turn(Deck* playersDeck, Side* playersSide, Deck* computersDeck, Side* computersSide, int &rounds)
{

    // Drawing the card
    int draw = playersDeck->dequeue();
    int compDraw = computersDeck->dequeue();
    int draw2 = 0;
    int total = 0;
    cout << "You drew a " << faceValues(draw) << "!" << endl;
    cout << "Do you want to....\n"
        << "Play just this card (1)\n"
        << "Place this card on your side pile and play a new card (2)\n"
        << "Play this card and the card on top of your side pile (3)" << endl;

    int choice;
    cin >> choice;
    while (choice != 1 && choice != 2 && (choice != 3 || playersSide->isEmpty()))
    {
        if (choice == 3)
        {
            cout << "Player's Side Deck is empty!" << endl;
        }
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
            computersDeck->enqueue(draw);
        }
        else
        {
            cout << "You win this round! adding both cards to your deck... " << endl;
            playersDeck->enqueue(compDraw);
            playersDeck->enqueue(draw);
        }
    }

    if (choice == 2)
    {
        //add this card to your side pile and play another
        cout << "Adding " << faceValues(draw) << " to the side pile.....\n";
        playersSide->Push(draw);
        draw2 = playersDeck->dequeue();
        cout << "You drew a " << faceValues(draw2) << "!" << endl;
        cout << "You played the " << faceValues(draw2) << "!" << endl;
        cout << "The computer played a " << faceValues(compDraw) << endl;
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
        if (playersSide->length() != 0) {
            int sideDraw = playersSide->Pop();
            cout << "You picked up a " << sideDraw << " from your side pile. " << endl;
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
        else {
            cout << "You have no cards in your side pile! Try again!" << endl;
            computersDeck->enqueue(compDraw);
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
    cout << "Welcome to War! \nEnter 1 if you would like to play until someone runs out of cards.\nEnter 2 if you would like to play a set number of rounds!" << endl;
    int choice;
    cin >> choice;
    if (choice == 1)
    {
        int rounds = 0;
        cout << "************** Starting Game... **************" << endl;
        while(!playerDeck.isEmpty() && !computerDeck.isEmpty())
        { 

            turn(&playerDeck, &playerSide, &computerDeck, &computerSide, rounds);
            cout << "You have " << playerDeck.getSize() << " cards in your deck and " << playerSide.length() << " cards in your side pile." << endl;
            cout << "The computer has " << computerDeck.getSize() << " cards" << endl;
            cout << "**************Next Turn**************" << endl;
            if (playerDeck.isEmpty()){
                while (!playerSide.isEmpty()){
                    turn(&playerDeck, &playerSide, &computerDeck, &computerSide, rounds);
                    cout << "You have " << playerDeck.getSize() << " cards in your deck and " << playerSide.length() << " cards in your side pile." << endl;
                    cout << "The computer has " << computerDeck.getSize() << " cards in its deck." << endl;
                }
            }
        }

        if (computerDeck.isEmpty())
        {
            cout << "You win!\n" 
                << "Round count: " << rounds << "\n";
        }
        else
        {
            cout << "You lose :<"
                << "Round count: " << rounds << "\n";
        }
    }
    else if (choice == 2) 
    {
        cout << "How many rounds would you like to play?" << endl;
        int rounds;
        cin >> rounds;
        cout << "************** Starting Game... **************" << endl;
        for (int i = 0; i < rounds; i++){
            turn(&playerDeck, &playerSide, &computerDeck, &computerSide, rounds);
            cout << "You have " << playerDeck.getSize() << " cards in your deck and " << playerSide.length() << " cards in your side pile." << endl;
            cout << "The computer has " << computerDeck.getSize() << " cards in its deck." << endl;
            cout << "There are " << (rounds - 1) - i << " rounds left!" << endl;
            if ((rounds - 1) - i != 0){
                cout << "**************Next Turn**************" << endl;
            }
        }
      cout << "**************Game over**************" << endl;
      if (computerDeck.getSize() > playerDeck.getSize()){
        cout << "You lose :<" << endl;
      }
      else{
        cout << "You win!" << endl;
      }
        }
}


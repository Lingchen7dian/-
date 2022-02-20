// ==================================================================================
// Implement all functions that you listed by prototype in deck.h
// You may include additional helper functions as necessary
// All of your code must be in deck.h and deck.cpp
//
// NOTE: These are standalone functions, not part of a class.
// ==================================================================================

#include <iostream>
#include <cassert>
#include "playing_card.h"
#include "node.h"
#include "deck.h"
#include <cstdlib>
#include <ctime>

// ==================================================================================

//find out the size of a deck list
int DeckSize(Node* deck1){
    if(deck1 == NULL){
        return 0;
    }
    int count = 1;
    while(deck1->after != NULL){
        deck1 = deck1->after;
        count++;
    }
    return count;
}

//Helper function to output the cards in the sorted order
void PrintDeckSorted(string description, Node* deck){
    cout << description;
    //pass the pointer to the first order of the deck in sorted order
    while(deck->sorted_prev != NULL){
        deck = deck->sorted_prev;
    }

    while (deck != NULL) {
        cout << " " << deck->getCard().getString();
        deck = deck->sorted_next;
    }
    cout << endl;
}

//to judge whether the two decks are in the same order(in primary order)
bool SamePrimaryOrder(Node* deck1, Node* deck2){
    bool judge = false;
    Node* a = deck1;
    Node* b = deck2;
    while(a->getCard().getCard() == b->getCard().getCard()
    &&a->getCard().getSuit() == b->getCard().getSuit()){
        if(a->after == NULL && b->after == NULL){
            judge = true;
            break;
        }
        a = a->after;
        b = b->after;
    }
    return judge;
}

//to judge whether the two decks are in the same order(in reverse primary order)
bool ReversePrimaryOrder(Node* deck1, Node* deck2){
    Node* a = deck1;
    Node* b = deck2;
    while(b->after != NULL){
        b = b->after;
    }
    bool judge = false;
    while(a->getCard() == b->getCard()){
        if(a->after == NULL && b->before == NULL){
            judge = true;
            break;
        }
        a = a->after;
        b = b->before;
    }
    return judge;
}


//used to copy a deck
Node* CopyDeck(Node* deck1){
    Node* copy_deck = NULL;
    while(deck1 != NULL){
        DeckPushBackCard(copy_deck, deck1->getCard().getSuit()
                , deck1->getCard().getCard());
        deck1 = deck1->after;
    }
    return copy_deck;
}

//delete the memory of a deck
void DeleteAllCards(Node* &deck2){
    int times = DeckSize(deck2);
    for(int i = 0; i < times - 1; i++){
        Node* temp = deck2;
        deck2 = deck2->after;
        deck2->before = NULL;
        temp->after = NULL;
        delete temp;
    }
    delete deck2;
}

//cut a deck from the middle and store the top and the bottom
void CutDeck(Node* &deck, Node* &top, Node* &bottom, string P_or_not){
    int size = DeckSize(deck);
    //avoid cutting empty decks or decks with only one card
    if(size == 0){
        cerr<<"The deck is empty";
        exit(0);

    }else if(size == 1){
        cerr<<"We cannot cut one card into two pieces!!!";
        exit(1);
    }

    if(P_or_not == "perfect") {
    //cutting the deck into half and half
        int position = size / 2;
        Node *temp = deck;
        top = deck;
        for (int i = 0; i < position; i++) {
            temp = temp->after;
        }
        temp->before->after = NULL;
        temp->before = NULL;
        bottom = temp;

    } else if (P_or_not == "random"){
    //cutting the deck randomly
        srand((unsigned)time(0));
        int x;
        x = rand() % 5 + 1;
        int position = size / 2 - x;

        Node *temp = deck;
        top = deck;
        for (int i = 0; i < position; i++) {
            temp = temp->after;
        }
        temp->before->after = NULL;
        temp->before = NULL;
        bottom = temp;
    }
}

//shuffle the card
Node* Shuffle(Node* &top, Node* &bottom, string P_or_not2){
    Node* Shuffle =NULL;
    if(P_or_not2 == "perfect"){
    // takes those two smaller pieces and interleaves the cards
    // one at a time to form a single deck again
        Node* T_temp = top;
        Node* B_temp = bottom;
        Shuffle = T_temp;
        while(1){
            B_temp->before = T_temp;
            T_temp = T_temp->after;
            B_temp->before->after = B_temp;
            if(T_temp == NULL){break;}
            T_temp->before = B_temp;
            B_temp = B_temp->after;
            T_temp->before->after = T_temp;
            if(B_temp == NULL){break;}
        }

    } else if (P_or_not2 == "random"){
    //mimic the randomness that naturally occurs in physical shuffling
        int top_cards;
        int bottom_cards;
        Node* T_temp = top;
        Node* B_temp = bottom;
        Shuffle = T_temp;

        while(1) {
            //in each turn of shuffling, shuffle a random number of cards from the top
            srand((unsigned) time(0));
            top_cards = rand() % 3 + 1;
            for(int i = 0; i < top_cards - 1; i++){
                if(T_temp->after == NULL){
                    break;
                }
                T_temp = T_temp->after;
            }
            B_temp->before = T_temp;
            T_temp = T_temp->after;
            B_temp->before->after = B_temp;
            if(T_temp == NULL){break;}

            //in each turn of shuffling, shuffle a random number of cards from the bottom
            srand((unsigned) time(0));
            bottom_cards = rand() % 3 + 1;
            for(int j = 0; j < bottom_cards - 1; j++){
                if(B_temp->after == NULL){
                    break;
                }
                B_temp = B_temp->after;
            }
            T_temp->before = B_temp;
            B_temp = B_temp->after;
            T_temp->before->after = T_temp;
            if(B_temp == NULL){break;}
        }
    }
    return Shuffle;
}

//Deal all or some of the deck to a specified number of players
void Deal(Node* &deck, Node* hands[], int num1, string T, int num2){
    //avoid dealing empty decks
    if(DeckSize(deck) == 0) {
        cerr << "The deck is empty";
        exit(0);
    }

    if(T == "one-at-a-time") {
        //create numbers of players and initializing them
        // with the first card they get
        Node *player[num1];
        for (int k = 0; k < num1; k++) {
            hands[k] = deck;
            player[k] = hands[k];
            deck = deck->after;

            deck->before->after = NULL;
            deck->before = NULL;
        }
        //deal the rest of cards one by one
        for (int i = 0; i < num2 - 1; i++) {
            for (int j = 0; j < num1; j++) {
                player[j]->after = deck;
                player[j]->after->before = player[j];

                player[j] = player[j]->after;
                deck = deck->after;
                if (deck) {
                    deck->before = NULL;
                }
                player[j]->after = NULL;
            }
        }
    }
}

//sort cards in each person's hands
Node* SortHand(Node* deck){
    //create a pointer of the deck in primary order
    Node* primary_temp = deck;
    //record the head of the deck list in sorted order
    Node* sort = deck;
    sort->sorted_prev = NULL;
    sort->sorted_next = NULL;
    //create a pointer of the deck in sorted order
    Node* sort_temp = sort;

    //record the size of the deck list in sorted order
    int sort_size = 1;
    //calculate the size of the deck list in primary order
    int primary_size = DeckSize(deck);

    //go through the deck list in primary order
    for(int i = 0; i < primary_size - 1; i++){
        primary_temp = primary_temp->after;

        //go through the deck list in sorted order
        for(int j = 0; j < sort_size; j++){
            //case 1: the card is the biggest one
            //then we put it at the beginning of the list in sorted order
            if(primary_temp->getCard() < sort->getCard()){
                sort->sorted_prev = primary_temp;
                sort->sorted_prev->sorted_next = sort;
                sort = sort->sorted_prev;
                sort->sorted_prev = NULL;
                break;

            //case 2: the card is the smaller then the head of the list in sorted order
            //then we move to the (sorted_)next and compare again
            } else if(primary_temp->getCard() > sort_temp->getCard()) {
                //if the card is the smallest one
                //then put it at the end of the list in sorted order
                if(sort_temp->sorted_next == NULL){
                    sort_temp->sorted_next = primary_temp;
                    sort_temp->sorted_next->sorted_prev = sort_temp;
                    primary_temp->sorted_next = NULL;
                    break;
                }
                sort_temp = sort_temp->sorted_next;
                continue;

            //case 3: normal case(the card is neither the biggest nor the smallest)
            //which means we should insert it in the middle
            }else if(primary_temp->getCard() < sort_temp->getCard()
                 || primary_temp->getCard() == sort_temp->getCard()){
                sort_temp->sorted_prev->sorted_next = primary_temp;
                primary_temp->sorted_prev = sort_temp->sorted_prev;
                sort_temp->sorted_prev = primary_temp;
                primary_temp->sorted_next = sort_temp;
                break;
            }
        }
        sort_size += 1;
        sort_temp = sort;
    }
    return sort;
}
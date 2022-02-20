#include "playing_card.h"
#include "node.h"
using namespace std;
// ==================================================================================
// prototypes for provided functions (implemented in main.cpp)
// ==================================================================================
//read-only functions
int DeckSize(Node* deck1);
void PrintDeckSorted(string description, Node* deck);
bool SamePrimaryOrder(Node* deck1, Node* deck2);
bool ReversePrimaryOrder(Node* deck1, Node* deck2);

//allocate and deallocate
Node* CopyDeck(Node* deck1);
void DeleteAllCards(Node* &deck2);

//other functions
void CutDeck(Node* &deck, Node* &top, Node* &bottom, string P_or_not);
Node* Shuffle(Node* &top, Node* &bottom, string P_or_not2);
void Deal(Node* &deck, Node* hands[], int num1, string T, int num2);
Node* SortHand(Node* deck);



bool SanityCheckPrimary(Node* top);
bool SanityCheckSorted(Node* first);
Node* CreateDeck(int numCards);
void DeckPushBackCard(Node* &deck, const std::string& suit, int num);
void PrintDeckPrimary(const std::string &description, Node* deck);


// ==================================================================================
//
// Write all the prototypes for the your functions here
// (they will be implemented in deck.cpp)
//
// NOTE: These are standalone functions, not part of a class.
//
// You may include additional helper functions as necessary
// All of your code must be in deck.h and deck.cpp
//
// ==================================================================================



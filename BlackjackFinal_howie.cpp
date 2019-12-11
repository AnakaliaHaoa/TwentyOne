
#include <iostream>
#include <time.h>
#include <stdlib.h>
using namespace std;

void Rules();
int getCards();
int convertAce(int value);
int dealerHand();
void playerCards();
void aceHL1();
void aceHL2();
void checkWin();
void hitStick();
void keepPlaying();

// Variables accessed by multiple functions
int card, playCard1, playCard2, dealCardTotal, bet; 
// Initializing counts
int playCardTotal = 0;
int coins = 100;

// Function to take in player's name; display a list of rules explaining the logic
// the game plays by, including dealer's limitations
void rules() {
	string playerName;

	cout << "Welcome to 21!" << endl;
	cout << "Please enter your name!" << endl;
	cin >> playerName;
	cout << "Let's go, " << playerName << "!" << endl;

	cout << "  ***************************************************" << endl;
	cout << "  *1. The goal is to reach or be closest to 21      *" << endl;
	cout << "  *   without going over.                           *" << endl;
	cout << "  *2. You will then be dealt two cards and prompted *" << endl;
	cout << "  *   to bet.                                       *" << endl;
	cout << "  *3. Once you've bet you'll be asked if you want   *" << endl;
	cout << "  *   another card via Hit/Stick.                   *" << endl;
	cout << "  *4. If you Hit you will receive another card.     *" << endl;
	cout << "  *   You can hit until you go over 21.             *" << endl;
	cout << "  *5. If you Stick the dealer will receive cards    *" << endl;
	cout << "  *   until he reaches 16 and Sticks, busts,        *" << endl;
	cout << "  *   or hits blackjack.                            *" << endl;
	cout << "  *6. If neither of you bust or reach 21 your       *" << endl;
	cout << "  *   cards will be compared. The closer to 21 wins.*" << endl;
	cout << "  ***************************************************" << endl;
	return;
}



int getCards()
{
	int card; // Holder for random #

	card = rand() % 14 + 1; // Generates random value for the card

	if (card >= 12) // Clarifies that Jack, Queen and King all have value 10
		return 10;
	else
		return card; // returns a random card to be added to currentCardTotal

}

//int convertAce(int value)
//{
//	return 0;
//}

void playerCards()
{
	int ace1, ace2; // Holds ace values 

	playCardTotal = 0;
	ace1 = 0;
	ace2 = 0;
	playCard1 = getCards(); 
	playCard2 = getCards();

	cout << "You have " << coins << "." << endl << endl; // Print bet apparatus

	// Accounts for no coins to bet
	if (coins <= 0) {
		cout << "*************************" << endl;
		cout << "... Oh no, you lost the game!" << endl;
		cout << "You went bankrupt, but you can reinitalize the game to play again!" << endl;
		coins = 100;
		cout << "There you go, 100 more coins if you keep playing!" << endl;
		keepPlaying(); // Calling the keep playing option
		playerCards(); // Calling player's hand
	}

	// Force end to game if X profits are reached
	if (coins >= 200) {
		cout << "**********************" << endl;
		cout << "YOU WON!" << endl;
		cout << "You doubled your coins  /n and won the game!" << endl;
		cout << "Bank is being reset..." << endl;
		coins = 100; // resets bet
		keepPlaying();
		playerCards();
	}

	// Takes in bet
	cout << "Place your bet: " << endl;
	cin >> bet;

	// Bounds checking bet availability
	if (bet > coins) {
		cout << endl;
		cout << "You cannot bet more than you have!" << endl;
		keepPlaying();
		playerCards();
	}

	// Triggers decision tree for player's first card equaling an ace
	if (playCard1 == 11) {
		cout << "Your first card is: " << "Ace High or Low, you pick!"; // Allows for player to pick high/low value for ace
		ace1 = 1;
	}
	else if (playCard1 == 1) {
		cout << "Your first card is: " << "Ace High or Low, you pick!"; // Allows for player to pick high/low value for ace
		ace1 = 1;
	}
	else {
		cout << "CARD ONE" << endl;
		cout << "********" << endl;
		cout << "  " << playCard1 << "  " << endl;
	}
	
	// Triggers decision tree for player's second card equaling an ace
	if (playCard2 == 11) {
		cout << "Your second card is: " << "Ace High or Low, you pick!" << endl; // Allows for player to pick high/low value for 2nd ace
		ace2 = 1;
	}
	else if (playCard2 == 1) {
		cout << "Your second card is: " << "Ace High or Low, you pick!" << endl; // Allows for player to pick high/low value for 2nd ace
		ace2 = 1;
	}
	else {
		cout << "CARD TWO" << endl;
		cout << "********" << endl;
		cout << "  " << playCard2 << "  " << endl;
	}

	cout << endl;

	// Moves decision tree to aceHL1 function in order to maintain clarity of code
	if (ace1 == 1) {
		cout << "Press u: Ace is Low (1) | Press d: Ace is High (11)" << endl;
		aceHL1();
	}
	// Moves decision tree to aceHL2 function in order to maintain clarity of code
	if (ace2 == 1) {
		cout << "Press u: Ace is Low (1) | Press d: Ace is High (11)" << endl;
		aceHL2();
	}

	playCardTotal = playCard1 + playCard2;

	cout << "TOTAL HAND" << endl;
	cout << "**********" << endl;
	cout << "   " << playCardTotal << "   " << endl;

	if (playCardTotal == 21) {
		cout << "*********" << endl;
		cout << "   21!   " << endl;
		cout << "You win double your bet!" << endl;
		coins = coins + bet * 2;
		cout << "You have " << coins << " coins available." << endl;
		keepPlaying();
		playerCards();
	}

	cout << endl;

	hitStick();

}

void aceHL1()
{

	char choice;
	cout << endl;

	cin >> choice;

	// Determines if first card is high or low
	switch (choice) {
	case 'd':
		playCard1 = 1;
		break;
	case 'u':
		playCard1 = 11;
		break;
	}

}

void aceHL2()
{

	char choice;
	cout << endl;

	cin >> choice;
	
	// Determines if second card is high or low
	switch (choice) {
	case 'd':
		playCard2 = 1;
		break;
	case 'u':
		playCard2 = 11;
		break;
	}

}

// Accepts player's input to either add a card or stay with the hand they have now
// Then returns to playingCards() function with player's card total for the hand
void hitStick()
{
	char hitOrStick;

	cout << "(H)it || (S)tick" << endl;

	cout << endl;
	cin >> hitOrStick;

	switch (hitOrStick) 
	{
	case 'h':
		playCardTotal = playCardTotal + getCards();
		if (playCardTotal > 21) {
			cout << "TOTAL HAND " << endl;
			cout << "***********" << endl;
			cout << "    " << playCardTotal << "     " << endl <<  endl;
			system("CLS");
			cout << "        " << endl;
			cout << "********" << endl;
			cout << playCardTotal << endl << endl;
			cout << "You went bust!" << endl << endl;
			cout << "You lost " << bet << " coins." << endl;
			coins = coins - bet;
			cout << "You have " << coins << " coins available." << endl;
			keepPlaying();
			playerCards();
		}
		cout << "TOTAL HAND" << endl;
		cout << "**********" << endl;
		cout << "   " << playCardTotal << "   " << endl;
		hitStick();
		break;
	case 's':
		system("CLS");
		checkWin();
		break;
	case 'H':
		playCardTotal = playCardTotal + getCards();
		if (playCardTotal > 21) {
			cout << "TOTAL HAND " << endl;
			cout << "***********" << endl;
			cout << "    " << playCardTotal << "     " << endl << endl;
			system("CLS");
			cout << "        " << endl;
			cout << "********" << endl;
			cout << playCardTotal << endl << endl;
			cout << "You went bust!" << endl << endl;
			cout << "You lost " << bet << " coins." << endl;
			cout << "You have " << coins << " coins available." << endl;
			coins = coins - bet;
			keepPlaying();
			playerCards();
		}
		cout << "TOTAL HAND" << endl;
		cout << "**********" << endl;
		cout << "   " << playCardTotal << "   " << endl;
		hitStick();
		break;
	case 'S':
		system("CLS");
		checkWin();
		break;
	}

}

void checkWin()
{
	dealCardTotal = dealerHand();

	cout << "TOTAL CARDS" << endl;
	cout << "***********" << endl;
	cout << "     " << playCardTotal << "    " << endl;
	if (playCardTotal > 21) {
		cout << "You bust" << endl;
		coins = coins - bet;
		keepPlaying();
		playerCards();
	}
	else
		cout << "DEALERS HAND" << endl;
	cout << "************" << endl;
	cout << "     " << dealCardTotal << "      " << endl << endl;

	if (dealCardTotal == 21)
	{
		cout << "DEALER WINS" << endl;
		cout << "You lost " << bet << " coins!" << endl;
		cout << "*** Better luck next time! *** " << endl;
		coins = coins - bet;
		cout << "You have " << coins << " coins available." << endl;
		keepPlaying();
		playerCards();
	}
	else if (dealCardTotal > 21)
	{
		cout << "DEALER BUSTS!" << endl;
		cout << "You win " << bet << " coins!" << endl;
		coins = coins + bet;
		cout << "You have " << coins << " coins available." << endl;
		keepPlaying();
		playerCards();
	}
	else
	{
		if (playCardTotal > dealCardTotal) 
		{
			cout << "YOU WON!" << endl;
			cout << "You win " << bet << " coins!" << endl;
			coins = coins + bet;
			cout << "You have " << coins << " coins available." << endl;
		}
		if (playCardTotal == dealCardTotal) 
		{
			cout << "DRAW" << endl;
			cout << "Bet of " << bet << " coins goes back in the pool." << endl;
			coins = coins;
		}
		if (playCardTotal < dealCardTotal) 
		{
			cout << "YOU LOST!" << endl;
			cout << "You lost " << bet << " coins!" << endl;
			cout << "*** Better luck next time! *** " << endl;
			coins = coins - bet;
			cout << "You have " << coins << " coins available." << endl;
		}
		keepPlaying();
		playerCards();
	}
}

int dealerHand()
{
	int dealCard1, dealCard2, dealCard3, dealCard4, dealCard5, dealCardTotal, dealAce1, dealAce2;

	dealCard1 = getCards();
	dealCard2 = getCards();
	dealCard3 = getCards();
	dealCard4 = getCards();
	dealCard5 = getCards();

	card = dealCard1;
	card = dealCard2;

	dealCardTotal = dealCard1 + dealCard2;

	if (dealCardTotal > 16)
		return dealCardTotal;
	else if (dealCardTotal == 21) {
		cout << "DEALER WON!" << endl;
		cout << "21! 21! 21!" << endl;
		cout << "You lost " << bet << " coins." << endl;
		coins = coins - bet;
		cout << "You have " << coins << " coins available." << endl;
		keepPlaying();
		playerCards();
		return dealCardTotal;
	}
	else if (dealCardTotal < 16)
	{
		getCards();
		card = dealCard3;
		dealCardTotal = dealCardTotal + dealCard3;
		// Evaluation tree that counts whether Dealer's Hand ever:
		// Reaches 17, in which case the dealer sticks
		// Reaches 21, in which case the value is checked against 

		if (dealCardTotal > 16) {
			return dealCardTotal;
		}
		else if (dealCardTotal == 21)
			return dealCardTotal;
		else if (dealCardTotal < 16) {
			getCards();
			card = dealCard4;
			dealCardTotal = dealCardTotal + dealCard4;
			if (dealCardTotal > 16) {
				return dealCardTotal;
			}
			else if (dealCardTotal == 21)
				return dealCardTotal;
			else if (dealCardTotal < 16) {
				getCards();
				card = dealCard5;
				dealCardTotal = dealCardTotal + dealCard5;
				if (dealCardTotal > 16) {
					return dealCardTotal;
				}
				else if (dealCardTotal == 21)
					return dealCardTotal;
				else if (dealCardTotal < 21) {
					return dealCardTotal;
				}
			 
			}
		}
	}



	return dealCardTotal;

}

void keepPlaying()
{
	int key;
	cout << endl;
	cout << "Press 1 to keep playing. Press 2 to end game." << endl;
	cin >> key;
	if (key == 1) {
		system("CLS");
	}
	else if (key == 2) {
		cout << "We're sad to see you go." << endl;
		cout << "You have " << coins << " coins." << endl;
		exit(0);
	}
	else if (key != 1 || key != 2) {
		cout << "That's not a valid option!" << endl;
		cout << "Press 1 to keep playing. Press 2 to end game." << endl;
		cin >> key;
	}
}

int main()
{
	rules();
	srand(time(NULL));
	playerCards();
}
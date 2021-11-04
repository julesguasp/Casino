#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "casino.h"

/* global constants
#define SLOTS 1
#define SCRATCH 2
#define BLACKJACK 3

// black jack constants
#define FACES 13
#define SUITS 4
#define CLUBS 0
#define DIAMONDS 1
#define HEARTS 2
#define SPADES 3
#define BUST 21

// scratch off constants
#define ONE 1
#define TWO 2
#define FIVE 5
#define BONUS 20

struct OneDollar
{
    int winNumber;
    int numbers[5];
    float prizes[5];
    char bonus[2];
};

struct TwoDollar
{
    int winNumbers[2];
    int numbers[10];
    float prizes[10];
    char bonus[2];
};

struct FiveDollar
{
    int winNumbers[4];
    int numbers[12];
    float prizes[12];
    char bonus[4];
};

// function prototypes
void welcomeScreen();
void clearScreen();
int displayMenu();

// game Slots
int playSlots(int);
char randomSymbol();

// game Black Jack
int playBlackJack(int);
void initializeUsed(char used[SUITS][FACES]);
void printDeck(char deck[SUITS][FACES]);
void initializeDeck(char deck[SUITS][FACES]);
int deal(char deck[SUITS][FACES], char used[SUITS][FACES]);
int results(int playScore, int dealScore);

// game scratch offs
int playScratchOffs(int);
struct OneDollar createScratchOffOne(struct OneDollar oneSO);
void displayScratchOffOne(struct OneDollar oneSO);
struct TwoDollar createScratchOffTwo(struct TwoDollar twoSO);
void displayScratchOffTwo(struct TwoDollar twoSO);
struct FiveDollar createScratchOffFive(struct FiveDollar fiveSO);
void displayScratchOffFive(struct FiveDollar fiveSO);
int cashOneDollar(struct OneDollar one);
int cashTwoDollar(struct TwoDollar two);
int cashFiveDollar(struct FiveDollar five);
char getBonus(int type);*/


// main function
int main()
{
  int play = 1;
    // seed the random function to generate true random numbers
    srand(time(0));
    int game;
    int cash = 1000;

    welcomeScreen();
    while(play == 1) {
      clearScreen();
      game = displayMenu();
      switch(game)
    {
        case SLOTS:
            cash = playSlots(cash);
            break;
        case SCRATCH:
            cash = playScratchOffs(cash);
            break;
        case BLACKJACK:
            cash = playBlackJack(cash);
            break;
        case EXIT:
            game = 0;
            return(0);
            break;
    }
    printf("\nYour cash is %d\n", cash);
    printf("Would you like to play another game? (1= Yes, 0 = No)\n");
    scanf("%d", &play);
    }
    clearScreen();
    game = displayMenu();
    clearScreen();

    switch(game)
    {
        case SLOTS:
            cash = playSlots(cash);
            break;
        case SCRATCH:
            cash = playScratchOffs(cash);
            break;
        case BLACKJACK:
            cash = playBlackJack(cash);
            break;
    }

    return 0;
}

// welcome screen
void welcomeScreen()
{
    printf("\t\t##########################################################\n");
    printf("\t\t##########################################################\n");
    printf("\t\t############                                  ############\n");
    printf("\t\t############          Knights Casino          ############\n");
    printf("\t\t############                                  ############\n");
    printf("\t\t##########################################################\n");
    printf("\t\t##########################################################\n");
}

// clear the screen
void clearScreen()
{
    char enter;

    printf("\n\t\t\t\t <Hit Enter to continue>\n\n");

    scanf("%c", &enter);

    // windows
    system("cls");

    // linux and mac
//    system("clear");
}

// casino game menu
int displayMenu()
{
    int game;

    do
    {
        printf("Select a game to play by entering the number next to the game\n");
        printf("%d. Slots\n", SLOTS);
        printf("%d. Scratch Offs\n", SCRATCH);
        printf("%d. Black Jack\n", BLACKJACK);
        printf("%d. Quit\n\n", EXIT);

        scanf("%d", &game);

    } while(game < SLOTS || game > EXIT);


    return game;
}

// ------------------------------ SLOTS SOURCE CODE ------------------------------ //

int playSlots(int cash)
{
    // bet amount
    const int BET = 5;

    // payouts
    const int MATCH_TWO = 5;
    const int MATCH_THREE = 50;

    // loop control
    int play = 1;

    // random symbols
    char symOne;
    char symTwo;
    char symThree;

    printf("Let's play the slot machines!\n\n");
    printf("Your cash balance is $%d. The bet is $%d.\n", cash, BET);
    printf("Match two symbols to win $%d.\n", MATCH_TWO);
    printf("Match all three symbols to win $%d.\n\n", MATCH_THREE);

    if(cash < BET)
    {
        printf("You are out of cash, you cannot play\n\n");
        play = 0;
    }

    // continue playing until user chooses to stop
    while(play)
    {
        // place the bet of $5
        cash -= BET;

        // generate the three symbols
        printf("Spinning...\n\n");
        symOne = randomSymbol();
        symTwo = randomSymbol();
        symThree = randomSymbol();

        printf("%c  %c  %c\n\n", symOne, symTwo, symThree);

        // three symbols matched
        if(symOne == symTwo && symOne == symThree)
        {
            printf("Three symbols matched, you won $50!\n\n");
            cash += MATCH_THREE;
        }
        // two symbols matched
        else if(symOne == symTwo || symOne == symThree || symTwo == symThree)
        {
            printf("Two symbols matched, you won $5!\n\n");
            cash += MATCH_TWO;
        }
        else
        {
            printf("No symbols matched\n\n");
        }

        printf("CASH = $%d\n\n", cash);

        // only continue looping if the player has cash
        if(cash >= BET)
        {
            printf("Would you like to spin again (Yes = 1, No = 0)? ");
            scanf("%d", &play);
        }
        else
        {
            break;
        }
    }

    printf("Thank you for playing slots at Knights Casino! Your cash out is $%d\n\n", cash);

    return cash;
}

char randomSymbol()
{
    // symbols for slots game
    const int SYMBOLS = 6;
    const char symbols[] = {'$', '%', '&', '#', '@', '!'};
    char symbol;
    int num;

    // get a random number between 0 - 5
    num = rand() % SYMBOLS;

    // set the symbol based on the random value
    switch(num)
    {
        case 0:
            symbol = symbols[0];
            break;
        case 1:
            symbol = symbols[1];
            break;
        case 2:
            symbol = symbols[2];
            break;
        case 3:
            symbol = symbols[3];
            break;
        case 4:
            symbol = symbols[4];
            break;
        case 5:
            symbol = symbols[5];
            break;
    }

    return symbol;
}

// ------------------------------ BLACK JACK SOURCE CODE ------------------------------ //
int playBlackJack(int cash)
{
    // bet amount
    const int BET = 10;

    // Black Jack constants
    const int MIN_HIT = 16;
    const int HIT = 1;
    const int STAND = 0;

    // loop control variables
    int play = 1;   // continue playing
    int choice = 0; // player wants to HIT or STAND
    int bust = 0;   // flag for player busting and play again

    // keep track of score of cards
    int player = 0;
    int dealer = 0;

    // the deck of cards
    char deck[SUITS][FACES];

    // which cards have been dealt
    char dealt[SUITS][FACES];

    printf("Let's play Black Jack!\n\n");
    printf("Your cash balance is $%d\nThe bet is $%d\n", cash, BET);
    printf("Dealer must HIT if their score is 16 or less\n");
    printf("Dealer must STAND if their score is 17 or higher\n");
    printf("If the player wins the hand, they receive $20\n");
    printf("If the dealer wins the hand, the $10 bet is lost\n");
    printf("If it is a PUSH, the player keeps their $%d bet\n", BET);

    clearScreen();

    if(cash < BET)
    {
        printf("Player does not have enough money to play!\n");
        return cash;
    }

    initializeUsed(dealt);

    printf("Shuffling the cards...\n");
    initializeDeck(deck);

    printf("Here's the deck...\n");
    printDeck(deck);

    clearScreen();

    printf("\nDealing...\n");

    while(play)
    {
        printf("\nPlayer's cash $%d\n\n", cash);

        if(cash < BET)
        {
            printf("Player does not have enough money to play!\n");
            play = 0;
            continue;
        }

        // place the player's bet
        cash -= BET;

        // for each hand, reset the scores to 0 and the bust flag
        player = 0;
        dealer = 0;
        bust = 0;

        // deal two cards to player and dealer
        player += deal(deck, dealt);
        player += deal(deck, dealt);

        printf("\nPlayer's score %d\n", player);

        dealer += deal(deck, dealt);
        dealer += deal(deck, dealt);

        // determine if the player wants to HIT or STAND first
        printf("\nPlayer, another card? (0 = STAND, 1 = HIT)\n");
        scanf("%d", &choice);

        // continue looping until the player busts or stands
        while(choice == HIT && player < BUST)
        {
            player += deal(deck, dealt);

            printf("\nPlayer's score %d\n", player);

            // if the player busts 21, dealer automatically wins the hand
            if(player > BUST)
            {
                // set the bust flag
                bust = 1;
                printf("\nPlayer BUSTED! Dealer wins the hand!\n");
                // break out of the inner loop
                break;
            }
            else
            {
                printf("\nPlayer, another card? (0 = STAND, 1 = HIT)\n");
                scanf("%d", &choice);
            }
        } // end while loop for player to HIT or STAND


        // if the player busted and the player wants another hand, skip the remaining code
        if(bust)
        {
            printf("\nPlayer, play another hand? (0 = No, 1 = Yes)\n");
            scanf("%d", &play);

            // clear the screen after each hand
            clearScreen();
            continue;
        }
        else
        {
            // determine if the dealer has to HIT or STAND
            if(dealer <= MIN_HIT)
            {
                choice = HIT;
            }
            else
            {
                choice = STAND;
            }

            // keep dealing until the dealer is required to HIT, STAND or busts
            while(choice == HIT)
            {
                dealer += deal(deck, dealt);

                if(dealer <= MIN_HIT)
                {
                    choice = HIT;
                }
                else
                {
                    choice = STAND;
                }
            }
        }

        printf("\nDealers's score %d\n", dealer);

        cash += results(player, dealer);

        printf("\nPlayer, play another hand? (0 = No, 1 = Yes)\n");
        scanf("%d", &play);

        // clear the screen after each hand
        clearScreen();
    }

    printf("Thank you for playing Black Jack at Knights Casino! Your cash out is $%d\n\n", cash);

    return cash;
}

// compare the scores for player and dealer to determine player's cash after initial bet
int results(int playScore, int dealScore)
{
    // payouts
    const int WIN = 20;
    const int PUSH = 10;
    const int LOSE = 0;

    // if the dealer BUSTS, player receives their bet
    if(dealScore > BUST)
    {
        printf("Dealer BUSTED!\n");
        return PUSH;
    }
    // if it is PUSH, player receives their bet
    else if(playScore == dealScore)
    {
        printf("It was a PUSH!\n");
        return PUSH;
    }
    // if the player WINS, they double their bet
    else if(playScore > dealScore)
    {
        printf("Player WINS the hand!\n");
        return WIN;
    }
    // if the player LOSSES, they lose their bet
    else
    {
        printf("Dealer WINS the hand!\n");
        return LOSE;
    }
}


int deal(char deck[SUITS][FACES], char dealt[SUITS][FACES])
{
    // maximum number of cards in a deck
    // will need to add logic
    const int MAX = 52;

    /* static counter to keep track of the number of cards used
    static int cards = 0;*/

    // flag to determine if a card has been dealt
    int used = 0;

    // card value
    int score = 0;

    // randoms
    int face;
    int suit;

    // keep trying to deal a new card until one that hasn't been used if found
    if(cards == MAX) {
      cards = 0;
      initializeUsed(dealt);
    }
    while(!used)
    {
        suit = rand() % SUITS;
        face = rand() % FACES;

        // the card has not been dealt
        if(dealt[suit][face] == 0)
        {
            // ends the loop checking for an unused card
            used = 1;
            // mark the card as dealt
            dealt[suit][face] = 1;
            cards++;
        }
    }

    switch(face)
    {
        case 0:
        case 1:
        case 2:
        case 3:
        case 4:
        case 5:
        case 6:
        case 7:
            score = face + 2;
            break;
        case 8:
        case 9:
        case 10:
        case 11:
            score = 10;
            break;
        case 12:
            score = 11;
            break;
    }

    return score;
}

void initializeUsed(char used[SUITS][FACES])
{
    int f;
    int s;

    // set the used array elements to false for all elements
    for(s = 0; s < SUITS; s++)
    {
        for(f = 0; f < FACES; f++)
        {
            used[s][f] = 0;
        }
    }
}

void initializeDeck(char deck[SUITS][FACES])
{
    // face values
    const char face[] = {'2', '3', '4', '5', '6', '7', '8', '9', 'T', 'J', 'Q', 'K', 'A'};

    // looping variables for face and suit
    int f;
    int s;

    // create the deck of cards

    for(s = 0; s < SUITS; s++)
    {
        for(f = 0; f < FACES; f++)
        {
            deck[s][f] = face[f];
        }
    }
}

void printDeck(char deck[SUITS][FACES])
{
    int s;
    int f;

    for(s = 0; s < SUITS; s++)
    {
        for(f = 0; f < FACES; f++)
        {
            switch(s)
            {
                case CLUBS:
                    printf("%c of Clubs\n", deck[s][f]);
                    break;
                case DIAMONDS:
                    printf("%c of Diamonds\n", deck[s][f]);
                    break;
                case HEARTS:
                    printf("%c of Hearts\n", deck[s][f]);
                    break;
                case SPADES:
                    printf("%c of Spades\n", deck[s][f]);
                    break;
            }
        }
    }
}

// ------------------------------ SCRACH OFF SOURCE CODE ------------------------------ //

int playScratchOffs(int cash)
{
    int type;
    int count;
    int c;
    int play = 1;
    struct OneDollar oneSO;
    struct TwoDollar twoSO;
    struct FiveDollar fiveSO;

    printf("Let's play scratch off tickets!\n");
    printf("Players can select from One Dollar, Two Dollar and Five Dollars tickets\n");
    printf("Prizes are based on the ticket selected\n\n");

    printf("Which type of scratch off would you like \n(1 = One Dollar, 2 = Two Dollar, 5 = Five Dollar)?\n");
    scanf("%d", &type);

    printf("How many scratch offs would you like?\n");
    scanf("%d", &count);

    printf("Getting your scratch offs...\n");
    while(play == 1) {
    for(c = 0; c < count; c++)
    {
        switch(type)
        {
            case ONE:
                if(cash > ONE) {
                  cash -= ONE;
                oneSO = createScratchOffOne(oneSO);
                displayScratchOffOne(oneSO);
                cash = cashOneDollar(oneSO);
                }
                else
                c = count;
                break;
            case TWO:
                if(cash > TWO) {
                  cash -= TWO;
                twoSO = createScratchOffTwo(twoSO);
                displayScratchOffTwo(twoSO);
                cash = cashTwoDollar(twoSO);
                }
                else
                c = count;
                break;
            case FIVE:
                if(cash > FIVE) {
                  cash -= FIVE;
                fiveSO = createScratchOffFive(fiveSO);
                displayScratchOffFive(fiveSO);
                cash = cashFiveDollar(fiveSO);
                }
                else
                c = count;
                break;
        }
    }
  }
    return cash;

}

struct OneDollar createScratchOffOne(struct OneDollar oneSO)
{
    const char SYMBOLS[] = {'$', '%', '&', '#', '@', '!'};
    const int SYMS = 2;
    const int NUMS = 5;
    const int BASE = 20;
    int usedSyms [] = {0, 0, 0, 0, 0, 0};
    int used = 0;
    int sym;
    int n;

    // randomly generate the winning number 1 - 20
    oneSO.winNumber = (rand() % BASE) + 1;

    // randomly generate the player's numbers 1 - 20
    for(n = 0; n < NUMS; n++)
    {
        oneSO.numbers[n] = (rand() % BASE) + 1;
    }

    // randomly generate the prizes numbers 1 - 20
    for(n = 0; n < NUMS; n++)
    {
        oneSO.prizes[n] = (float)(((rand() % BASE) + 1) * 5);
    }

    // randomly select two bonus symbols
    for(n = 0; n < SYMS; n++)
    {
      int used = 0;
      while(used == 0) {
        sym = rand() % (sizeof(SYMBOLS)/sizeof(SYMBOLS[0]));
        if(usedSyms[sym] == 0){
          usedSyms[sym] = 1;
          used = 1;
          break;
        }

      }
        switch(sym)
        {
            case 0:
                oneSO.bonus[n] = SYMBOLS[0];
                break;
            case 1:
                oneSO.bonus[n] = SYMBOLS[1];
                break;
            case 2:
                oneSO.bonus[n] = SYMBOLS[2];
                break;
            case 3:
                oneSO.bonus[n] = SYMBOLS[3];
                break;
            case 4:
                oneSO.bonus[n] = SYMBOLS[4];
                break;
            case 5:
                oneSO.bonus[n] = SYMBOLS[5];
                break;
        }
    }

    return oneSO;
}

void displayScratchOffOne(struct OneDollar oneSO)
{
    int n;
    const int NUMS = 5;
    const int SYMS = 2;

    printf("+------------------------------------------+\n");
    printf("| WINNING NUMBER        %2d%17s|\n", oneSO.winNumber, " ");
    printf("|%42s|\n", " ");
    printf("| YOUR NUMBERS%29s|\n|", " ");

    for(n = 0; n < NUMS; n++)
    {
        printf("%8d", oneSO.numbers[n]);
    }

    printf("  |\n");
    printf("|%42s|\n", " ");
    printf("| PRIZES%35s|\n", " ");
    printf("|%42s|\n|", " ");

    for(n = 0; n < NUMS; n++)
    {
        printf("%8.2f", oneSO.prizes[n]);
    }

    printf("  |\n|%42s|\n", " ");
    printf("| SYMBOLS%34s|\n", " ");
    printf("|%42s|\n|", " ");

    for(n = 0; n < SYMS; n++)
    {
        printf("%8c", oneSO.bonus[n]);
    }

    printf("%26s|\n+------------------------------------------+\n", " ");

}


struct TwoDollar createScratchOffTwo(struct TwoDollar twoSO)
{
    const char SYMBOLS[] = {'$', '%', '&', '#', '@', '!'};
    const int SYMS = 2;
    const int NUMS = 10;
    const int BASE = 30;
    int usedSyms[] = {0, 0, 0, 0, 0, 0};
    int usedNums [10] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int num;
    int used = 0;
    int sym;
    int n;

    // randomly generate the winning number 1 - 30
    for(n = 0; n < SYMS; n++)
    {
      used = 0;
      while (used == 0) {
        twoSO.winNumbers[n] = (rand() % BASE) + 1;
        if(usedNums[n] == 0){
        usedNums[n] = 1;
        twoSO.winNumbers[n] = num;
        used = 1;
        break;
        }
      }
    }

    // randomly generate the player's numbers 1 - 30
    for(n = 0; n < NUMS; n++)
    {
        twoSO.numbers[n] = (rand() % BASE) + 1;
    }

    // randomly generate the prizes numbers 1 - 30
    for(n = 0; n < NUMS; n++)
    {
        twoSO.prizes[n] = (float)(((rand() % BASE) + 1) * 5);
    }

    // randomly select two bonus symbols
    for(n = 0; n < SYMS; n++)
    {
      used = 0;
        while(used == 0) {
        sym = rand() % (sizeof(SYMBOLS)/sizeof(SYMBOLS[0]));
        if(usedSyms[sym] == 0){
          usedSyms[sym] = 1;
          used = 1;
          break;
        }
        }
        switch(sym)
        {
            case 0:
                twoSO.bonus[n] = SYMBOLS[0];
                break;
            case 1:
                twoSO.bonus[n] = SYMBOLS[1];
                break;
            case 2:
                twoSO.bonus[n] = SYMBOLS[2];
                break;
            case 3:
                twoSO.bonus[n] = SYMBOLS[3];
                break;
            case 4:
                twoSO.bonus[n] = SYMBOLS[4];
                break;
            case 5:
                twoSO.bonus[n] = SYMBOLS[5];
                break;
        }
    }

    return twoSO;
}

void displayScratchOffTwo(struct TwoDollar twoSO)
{
    int n;
    const int NUMS = 10;
    const int SYMS = 2;
    const int BREAK = 4;

    printf("+------------------------------------------+\n");
    printf("| WINNING NUMBERS%6s", " ");

    for(n = 0; n < SYMS; n++)
    {
        printf("%6d", twoSO.winNumbers[n]);
    }
    printf("%8s|\n|%42s|\n", " ", " ");

    printf("| YOUR NUMBERS%29s|\n|", " ");

    for(n = 0; n < NUMS; n++)
    {
        printf("%8d", twoSO.numbers[n]);

        if(n == BREAK)
            printf("  |\n|");
    }

    printf("  |\n");
    printf("|%42s|\n", " ");
    printf("| PRIZES%35s|\n", " ");
    printf("|%42s|\n|", " ");

    for(n = 0; n < NUMS; n++)
    {
        printf("%8.2f", twoSO.prizes[n]);

        if(n == BREAK)
            printf("  |\n|");
    }

    printf("  |\n|%42s|\n", " ");
    printf("| SYMBOLS%34s|\n", " ");
    printf("|%42s|\n|", " ");

    for(n = 0; n < SYMS; n++)
    {
        printf("%8c", twoSO.bonus[n]);
    }

    printf("%26s|\n+------------------------------------------+\n", " ");

}

struct FiveDollar createScratchOffFive(struct FiveDollar fiveSO)
{
    const char SYMBOLS[] = {'$', '%', '&', '#', '@', '!', '^', '*'};
    const int SYMS = 4;
    const int NUMS = 12;
    const int BASE = 50;
    int usedSyms[] = {0, 0, 0, 0, 0, 0, 0, 0};
    int usedNums[] = {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0};
    int num;
    int used = 0;
    int sym;
    int n;

    // randomly generate the winning number 1 - 50
    for(n = 0; n < SYMS; n++)
    {
      used = 0;
      while( used == 0) {
        /*fiveSO.winNumbers[n]*/ num = (rand() % BASE) + 1;
        if(usedNums[num] == 0) {
          usedNums[num] = 1;
          fiveSO.winNumbers[n] = num;
          used = 1;
          break;
        }
      }
    }

    // randomly generate the player's numbers 1 - 50
    for(n = 0; n < NUMS; n++)
    {
        fiveSO.numbers[n] = (rand() % BASE) + 1;
    }

    // randomly generate the prizes numbers 1 - 50
    for(n = 0; n < NUMS; n++)
    {
        fiveSO.prizes[n] = (float)(((rand() % BASE) + 1) * 5);
    }

    // randomly select two bonus symbols
    for(n = 0; n < SYMS; n++)
    {
      used = 0;
      while (used ==  0) {
        sym = rand() % (sizeof(SYMBOLS)/sizeof(SYMBOLS[0]));
        if(usedSyms[sym] == 0) {
          usedSyms[sym] = 1;
          used = 1;
          break;
        }
      }

        switch(sym)
        {
            case 0:
                fiveSO.bonus[n] = SYMBOLS[0];
                break;
            case 1:
                fiveSO.bonus[n] = SYMBOLS[1];
                break;
            case 2:
                fiveSO.bonus[n] = SYMBOLS[2];
                break;
            case 3:
                fiveSO.bonus[n] = SYMBOLS[3];
                break;
            case 4:
                fiveSO.bonus[n] = SYMBOLS[4];
                break;
            case 5:
                fiveSO.bonus[n] = SYMBOLS[5];
                break;
            case 6:
                fiveSO.bonus[n] = SYMBOLS[6];
                break;
            case 7:
                fiveSO.bonus[n] = SYMBOLS[7];
                break;
        }
    }

    return fiveSO;
}

void displayScratchOffFive(struct FiveDollar fiveSO)
{
    int n;
    const int SYMS = 4;
    const int NUMS = 12;
    const int BREAK = 4;

    printf("+------------------------------------------+\n");
    printf("| WINNING NUMBERS%6s", " ");

    for(n = 0; n < SYMS; n++)
    {
        printf("%4d", fiveSO.winNumbers[n]);
    }
    printf("%4s|\n|%42s|\n", " ", " ");

    printf("| YOUR NUMBERS%29s|\n|", " ");

    for(n = 0; n < NUMS; n++)
    {
        printf("%8d", fiveSO.numbers[n]);

        if(n == BREAK)
            printf("  |\n|");
        else if(n == BREAK * 2)
            printf("%10s|\n|", " ");
    }

    printf("%18s|\n", " ");
    printf("|%42s|\n", " ");
    printf("| PRIZES%35s|\n", " ");
    printf("|%42s|\n|", " ");

    for(n = 0; n < NUMS; n++)
    {
        printf("%8.2f", fiveSO.prizes[n]);

        if(n == BREAK)
            printf("  |\n|");
        else if(n == BREAK * 2)
            printf("%10s|\n|", " ");
    }

    printf("%18s|\n", " ");
    printf("|%42s|\n", " ");
    printf("| SYMBOLS%34s|\n", " ");
    printf("|%42s|\n|", " ");

    for(n = 0; n < SYMS; n++)
    {
        printf("%8c", fiveSO.bonus[n]);
    }

    printf("%10s|\n+------------------------------------------+\n", " ");
}

int cashOneDollar(struct OneDollar one)
{
    float cash = 0;
    int n;
    const int NUMS = 5;
    const int SYMS = 2;

    char bonus = getBonus(ONE);

    printf("\nBonus symbol is %c\n\n", bonus);

    for(n = 0; n < NUMS; n++)
    {
        if(one.numbers[n] == one.winNumber)
        {
            cash += one.prizes[n];
        }
    }

    for(n = 0; n < SYMS; n++)
    {
        if(one.bonus[n] == bonus)
        {
            cash += BONUS;
        }
    }

    printf("\nYour One Dollar Scratch Off won you $%.2f\n\n", cash);

    return (int)cash;
}

int cashTwoDollar(struct TwoDollar two)
{
    float cash = 0;
    int w;
    int n;
    const int NUMS = 10;
    const int WINS = 2;
    const int SYMS = 2;


    char bonus = getBonus(TWO);

    printf("\nBonus symbol is %c\n\n", bonus);

    for(w = 0; w < WINS; w++)
    {
        for(n = 0; n < NUMS; n++)
        {
            if(two.numbers[n] == two.winNumbers[w])
            {
                cash += two.prizes[n];
            }
        }
    }

    for(n = 0; n < SYMS; n++)
    {
        if(two.bonus[n] == bonus)
        {
            cash += BONUS;
        }
    }

    printf("\nYour Two Dollar Scratch Off won you $%.2f\n\n", cash);

    return (int)cash;
}

int cashFiveDollar(struct FiveDollar five)
{
    float cash = 0;
    int w;
    int n;
    const int NUMS = 12;
    const int WINS = 4;
    const int SYMS = 4;

    char bonus = getBonus(FIVE);

    printf("\nBonus symbol is %c\n\n", bonus);

    for(w = 0; w < WINS; w++)
    {
        for(n = 0; n < NUMS; n++)
        {
            if(five.numbers[n] == five.winNumbers[w])
            {
                cash += five.prizes[n];
            }
        }
    }

    for(n = 0; n < SYMS; n++)
    {
        if(five.bonus[n] == bonus)
        {
            cash += BONUS;
        }
    }

    printf("\nYour Five Dollar Scratch Off won you $%.2f\n\n", cash);

    return (int)cash;
}

char getBonus(int type)
{
    const char SYMBOLS[] = {'$', '%', '&', '#', '@', '!', '^', '*'};
    char bonus;
    int sym;
    const int ONE_TWO = 6;
    const int FIVE_RAND = 8;

    if(type == ONE || type == TWO)
    {
        sym = rand() % ONE_TWO;

        switch(sym)
        {
            case 0:
                bonus = SYMBOLS[0];
                break;
            case 1:
                bonus = SYMBOLS[1];
                break;
            case 2:
                bonus = SYMBOLS[2];
                break;
            case 3:
                bonus = SYMBOLS[3];
                break;
            case 4:
                bonus = SYMBOLS[4];
                break;
            case 5:
                bonus = SYMBOLS[5];
                break;
        }
    }
    else if(type == FIVE)
    {
        sym = rand() % FIVE_RAND;

        switch(sym)
        {
            case 0:
                bonus = SYMBOLS[0];
                break;
            case 1:
                bonus = SYMBOLS[1];
                break;
            case 2:
                bonus = SYMBOLS[2];
                break;
            case 3:
                bonus = SYMBOLS[3];
                break;
            case 4:
                bonus = SYMBOLS[4];
                break;
            case 5:
                bonus = SYMBOLS[5];
                break;
            case 6:
                bonus = SYMBOLS[6];
                break;
            case 7:
                bonus = SYMBOLS[7];
                break;
        }
    }

    return bonus;
}

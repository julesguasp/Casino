// global constants
#define SLOTS 1
#define SCRATCH 2
#define BLACKJACK 3
#define EXIT 4
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
char getBonus(int type);

//global variable
int cards;

#include <conio.h>
#include <iostream>
#include <windows.h>
using namespace std;

//specifying and declaring specific global game variables.


//height and width of the boundary.
const int width = 80;
const int height = 20;

//snake head coordinates of snake (x and y axis).
int x,y;
//Food coordinates.
int fruitCordX, fruitCordY;
//stores player score. 
int playerScore;
//Array that stores the cooridnates of snake tail.
int snakeTailX[100], snakeTailY[100];
//stores the length of the snake's tail. 
int snakeTailLen;
//stores the moving for the snakeDirection variable
enum snakesDirection { STOP = 0, LEFT, RIGHT, UP, DOWN };
//snakeDirection variable.
snakesDirection sDir;
//boolean that checks if game is over or not.
bool isGameOver;


//void funtion that initiates the game variables.
void GameInit()
{
    isGameOver = false;
    sDir = STOP;
    x = width / 2;
    y = height / 2;
    fruitCordX = rand() % width;
    fruitCordY = rand() % height;
    playerScore = 0;
}

//Function that creates the game board and redering.
void GameRender(string playerName)
{
    system("cls"); //Clears the console.

    //Creates the top walls with "-"
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    for (int i = 0; i < height; i++) {
        for (int j = 0; j <= width; j++){
            //Creating side walls with "|"
            if (j == 0 || j == width)
                cout << "|";
            //Creates the snake's head with "O"
            if (i == y && j == x)
                cout << "O";
            //Creates the snake's food with "#'s"
            else if (i == fruitCordY && j == fruitCordX)
                cout << "#";
            //Creating the snake's head with "O" again.
            else {
                bool prTail = false;
                for (int k = 0; k < snakeTailLen; k++) {
                    if (snakeTailX[k] == j && snakeTailY[k] == i) {
                        cout << "o";
                        prTail = true;
                    }
                }
                if (!prTail)
                    cout << " ";
            }
        }
        cout << endl;
    }

    //Creates bottom walls with "-"
    for (int i = 0; i < width + 2; i++)
        cout << "-";
    cout << endl;

    //Displays the player's score
    cout << playerName << "'s Score: " << playerScore << endl;
}

//Function that updates the game after every move. 

void UpdateGame()
{
    int prevX = snakeTailX[0];
    int prevY = snakeTailY[0];
    int prev2X, prev2Y;
    snakeTailX[0] = x;
    snakeTailY[0] = y;

    for (int i = 1; i < snakeTailLen; i++) {
        prev2X = snakeTailX[i];
        prev2Y = snakeTailY[i];
        snakeTailX[i] = prevX;
        snakeTailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }

    switch (sDir) {
    case LEFT:
        x--;
        break;
    case RIGHT:
        x++;
        break;
    case UP:
        y--;
        break;
    case DOWN:
        y++;
        break;
    }

    //Checks if the snake collides with the wall ("|")
    if (x >= width || x < 0 || y >= height || y < 0)
        isGameOver = true;

    //Checks for the collison with the snake's tail ("o")
    for (int i = 0; i < snakeTailLen; i++) {
        if (snakeTailX[i] == x && snakeTailY[i] == y)
            isGameOver = true;
    }

    //Checks for the snake's collision with the food. (#)
    if (x == fruitCordX && y == fruitCordY) {
        playerScore += 10;
        fruitCordX = rand() % width;
        fruitCordY = rand() % height;
        snakeTailLen++;
    }
}

//This function sets the game difficulty. 
int SetDifficulty()
{
    int dfc, choice;
    cout << "\nSET DIFFICULTY\n1: Easy\n2: Medium\n3: Hard "
            "\nNOTE: if not chosen or pessed any other "
            "key, the difficulty will be automatically set "
            "to medium\nChoose difficulty level: ";
    cin >> choice;
    switch (choice) {
    case '1':
        dfc = 50;
        break;
    case '2':
        dfc = 100;
        break;
    case '3':
        dfc = 150;
        break;
    default:
        dfc = 100;
    }
    return dfc;
}

//Function that handles the UserInput
void UserInput()
{
    //Checks if a key is pressed or not
    if (_kbhit()) {
        //Retrieves the pressed key
        switch (_getch()) {
        case 'a':
            sDir = LEFT;
            break;
        case 'd':
            sDir = RIGHT;
            break;
        case 'w':
            sDir = UP;
            break;
        case 's':
            sDir = DOWN;
            break;
        case 'x':
            isGameOver = true;
            break;
        }
    }
}

//Main function that runs and loops game
int main()
{
    string playerName;
    cout << "Enter your name: ";
    cin >> playerName;
    int dfc = SetDifficulty();

    GameInit();
    while (!isGameOver) {
        GameRender(playerName);
        UserInput();
        UpdateGame();
        //creates a delay for according to chosen difficulty
        Sleep(dfc);
    }

    return 0;
}



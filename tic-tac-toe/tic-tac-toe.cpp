#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <conio.h>
#include <ctype.h>

// Globalne varijable
char board[3][3];
char PLAYER;
char COMPUTER;

// Deklaracije funkcija
void resetboard();
void printboard();
int checkfreespaces(); // Provjera slobodnih mjesta
void playermove();
void computermove();
char checkwinner();
void printwinner(char winner);
void choosesymbol();

int main()
{
    char winner = ' '; // Nema pobjednika na početku
    char response;

    choosesymbol();

    do {
        winner = ' ';
        response = ' ';

        resetboard(); // Resetiranje ploče
        while (winner == ' ' && checkfreespaces() != 0) // Provjera ima li pobjednika ili slobodnih mjesta
        {
            printboard();
            playermove();
            winner = checkwinner();
            if (winner != ' ' || checkfreespaces() == 0)
            {
                break;
            }

            computermove();
            winner = checkwinner();
            if (winner != ' ' || checkfreespaces() == 0)
            {
                break;
            }
        }

        printboard();
        printwinner(winner);

        printf("Would you like to play again? (Y/N): ");
        scanf(" %c", &response); // Čitanje odgovora
        response = toupper(response); // Pretvaranje u veliko slovo
    } while (response == 'Y');

    printf("Thanks for playing!\n");

    return 0;
}

void choosesymbol()
{
    char choice;
    do
    {
        printf("Choose your symbol (X or O): ");
        scanf(" %c", &choice);
        choice = toupper(choice);
        if (choice == 'X') {
            PLAYER = 'X';
            COMPUTER = 'O';
        }
        else if (choice == 'O') {
            PLAYER = 'O';
            COMPUTER = 'X';
        }
        else {
            printf("Invalid choice. Please choose either X or O.\n");
        }
    } while (choice != 'X' && choice != 'O');
}

void resetboard()
{
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            board[i][j] = ' '; // Prazna polja
        }
    }
}

void printboard()
{
    printf("\n");
    printf(" %c | %c | %c \n", board[0][0], board[0][1], board[0][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n", board[1][0], board[1][1], board[1][2]);
    printf("---|---|---\n");
    printf(" %c | %c | %c \n\n", board[2][0], board[2][1], board[2][2]);
}

int checkfreespaces()
{
    int freespaces = 9;
    for (int i = 0; i < 3; i++)
    {
        for (int j = 0; j < 3; j++)
        {
            if (board[i][j] != ' ')
            {
                freespaces--;
            }
        }
    }
    return freespaces;
}

void playermove()
{
    int x, y;
    do
    {
        printf("Enter row number (1-3): ");
        scanf("%d", &x);
        x--; // Pretvaranje u indeks (0-2)

        printf("Enter column number (1-3): ");
        scanf("%d", &y);
        y--; // Pretvaranje u indeks (0-2)

        if (x < 0 || x > 2 || y < 0 || y > 2 || board[x][y] != ' ')
        {
            printf("Invalid move. Try again.\n");
        }
        else
        {
            board[x][y] = PLAYER;
            break;
        }
    } while (1);
}

void computermove()
{
    srand(time(0));
    int x, y;

    if (checkfreespaces() > 0)
    {
        do {
            x = rand() % 3;
            y = rand() % 3;
        } while (board[x][y] != ' ');

        board[x][y] = COMPUTER;
    }
}

char checkwinner()
{
    // Provjera redova
    for (int i = 0; i < 3; i++)
    {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != ' ')
        {
            return board[i][0];
        }
    }

    // Provjera stupaca
    for (int i = 0; i < 3; i++)
    {
        if (board[0][i] == board[1][i] && board[1][i] == board[2][i] && board[0][i] != ' ')
        {
            return board[0][i];
        }
    }

    // Provjera dijagonala
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != ' ')
    {
        return board[0][0];
    }
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != ' ')
    {
        return board[0][2];
    }

    return ' '; // Nema pobjednika
}

void printwinner(char winner)
{
    if (winner == PLAYER)
    {
        printf("Congratulations! You have won!\n");
    }
    else if (winner == COMPUTER)
    {
        printf("You lost! Better luck next time.\n");
    }
    else
    {
        printf("It's a tie!\n");
    }
}

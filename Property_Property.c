/*
    Description: This is a turn-based two-player board game.
    Programmed by: John Kovie L. Niño S15B
    Last modified: December 24, 2021
    Version: 1.0
    Acknowledgements: Borrowed the Standard Library (stdlib.h)
*/

#include <stdio.h>
#include <stdlib.h>

/*
    This functions return a random number ranging from 1 to 9.
    Precondition: <precondition / assumption>
    @return: random number ranging from 1 to 9
*/
int diceRoll() {
    return rand() % 9 + 1;
}

/*
    Outputs introductory message as program runs
*/
void introMsg() {
    printf("%s\n%s\n%s\n\n%s\n\n%s\n",
        "=====================================",
        "   Welcome to Property...Property!",
        "=====================================",
        "This is a turn-based two-player board game.\nPlayers compete to acquire wealth by buying or renting properties.\nThe game ends when a player goes bankrupt, i.e. he does not have enough money to pay rent.",
        "Press any key to get started!" );

        getchar();
        system("cls");
}


int main() {
    int nPlayer1, nPlayer2;
    int nPlayertAmt1 = 200;
    int nPlayertAmt2 = 200;

    introMsg();

}
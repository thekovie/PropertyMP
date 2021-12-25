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

int main() {
    int nPlayer1, nPlayer2;
    int nPlayertAmt1 = 200;
    int nPlayertAmt2 = 200;

}
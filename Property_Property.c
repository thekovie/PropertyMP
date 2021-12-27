/*
    Description:       This is a turn-based two-player board game.
    Programmed by:     John Kovie L. Niño S15B
    Last modified:     December 27, 2021
    Version:           1.0-alpha
    Acknowledgements:  Used the Standard Library (stdlib.h), Math Library (math.h)
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#define COLLECT_GO 200;
#define BUY_ELECTRIC 150;
#define BUY_RAILROAD 100;
#define PAY_RAILROAD_RENT 35;

/*
    Description: This function generates a random number ranging from 1 to 9.
    Precondition: <precondition / assumption>
    @return: random number ranging from 1 to 9
*/

int getRandom(int min, int max) {
       return min + rand() % (max + 1 - min);
}

int getLocation(int nLocation, int nDiceRoll, int * passedGo){
    if (nLocation + nDiceRoll > 9) {
        nLocation -= 10;
        *passedGo = 1;
    }
    return nLocation += nDiceRoll;
}

/*
    Description:        This functions check if the number given is Prime or not
    Precondition:       <precondition / assumption>
    @param  diceRoll =  the value needed to identify if Prime or not.
    @return 1        =  returns a TRUE boolean
    @return 0        =  returns a FALSE boolean
*/

int isPrime (int diceRoll) {
    int i, nDivisors;
    for (i = 2; i <= diceRoll; i++) {
        if (diceRoll % i == 0)
            nDivisors++;
    }
    if (nDivisors == 2)
        return 1;

    return 0; 
}

int getDigit(int current, int location) {
    int nDivisor = pow(10, location - 1);
    int nSplit = current / nDivisor;
    int nFinal = nSplit % 10;
    return nFinal;
}

int isOwned (int opponent, int current, int location) {
    int nLoc1 = getDigit(current, location); // Current player
    int nLoc2 = getDigit(opponent, location); // Opponent player

    if (nLoc2 == 1) // Opponent owns it
        return 1;
    if (nLoc1 == 1) // Current player owns it
        return 0;
    if (nLoc1 == 0 && nLoc2 == 0) { // Unowned
        return 0;
    }
}

int isRenovated (int opponent, int current, int location) {
    int nLoc1 = getDigit(current, location); // Current player
    int nLoc2 = getDigit(opponent, location); // Opponent player

    if (nLoc2 == 2) // Opponent renovated it
        return 1;
    if (nLoc1 == 2) // Current player renovated it
        return 0;
}

int promptBuy(int current, int location) {
    int decide;
    printf("%s\n%s\n\n%s\n%s\n%s",
            "This property is currently UNOWNED.",
            "Please select the following:",
            "[1]\tBuy Property from the bank",
            "[2]\tSkip to the next player",
            ">> ");
    
    scanf("%d", &decide);

    if (decide == 1) {
        if (location == 2) {
            return BUY_ELECTRIC;
        }
            
        else if (location == 7) {
            return BUY_RAILROAD;
        }

        else 
            return location % 7 * 20;
    } else; //skip


}
/*
    Description: Outputs introductory message as program runs
*/
void introMsg() {
    printf("%s\n%s\n%s\n\n%s\n\n%s\n",
        "=====================================",
        "|| Welcome to Property...Property! ||",
        "=====================================",
        "This is a turn-based two-player board game.\nPlayers compete to acquire wealth by buying or renting properties.\nThe game ends when a player goes bankrupt, i.e. he does not have enough money to pay rent.",
        "Press ENTER to get started!" );

        getchar();
        system("cls");
}

void printMenu() {
    printf("%s\n%s\n%s\n%s\n%s\n",
        "=====================================",
        "||   PLEASE SELECT THE FOLLOWING   ||",
        "=====================================",
        "[1]\tBuy Property",
        "[2]\tSell Property");
    
}


void playerSwitch(int * current, int * opponent, int * playerno, int player1, int player2, int amt1, int amt2, int * camt1, int * camt2) {
    if (*current == player1) {
        *current = player2;
        *opponent = player1;
        *playerno = 2;
        *camt1 = amt2;
    }
    else {
        *current = player1;
        *opponent = player2;
        *playerno = 1;
        *camt2 = amt1;
    }

}

void getPropertyName(int location) {
    switch (location) {
        case 0: printf("GO! COLLECT $200!\n"); break;
        case 1: printf("TREEHOUSE.\n"); break;
        case 2: printf("ELECTRIC COMPANY.\n"); break;
        case 3: printf("BEACH HOUSE.\n"); break;
        case 4: printf("JAIL TIME.\n"); break;
        case 5: printf("CASTLE.\n"); break;
        case 6: printf("FEELIN' LUCKY.\n"); break;
        case 7: printf("RAILROAD.\n"); break;
        case 8: printf("IGLOO.\n"); break;
        case 9: printf("FARM HOUSE.\n"); break;
    }
}

int getRentAmount(int opponent, int current, int location, int roll) {
    int nTotalAmt = location * 0.2;

    if (!isRenovated(opponent, current, location)) {
            switch (location) {
                case 2: return roll * 8; // ELECTRIC RENT
                case 7: return PAY_RAILROAD_RENT;
            }
        }
    else 
        nTotalAmt = nTotalAmt * 2 + 1;

    return nTotalAmt;
}

int isSpecial(int location) {
    if (location == 0 || location == 4 || location == 6)
        return 1;
    return 0;
}

void payAmount (int * current, int * opponent, int payment) {
    current -= payment;
    opponent += payment;
}


int main() {
    int nPlayer1, nPlayer2, nRoll, nStatus1, nStatus2, nLocation;
    int nLoc1 = 0;
    int nLoc2 = 0;
    int nPlayertAmt1 = 200;
    int nPlayertAmt2 = 200;

    introMsg();

    int nCurrent = nPlayer1;
    int nOpponent = nPlayer2;
    int nPlayerNo = 1;
    int nCurrentAmt, nOpponentAmt;
    int nPassedGo = 0;
    

    while(){ // NO CONDITION YET
        printf("Rolling Dice...\n");
        nRoll = getRandom(1,9);
        printf("Player %d has rolled [%d].\n", nPlayerNo, nRoll);

        if (nCurrent == nPlayer1) {
            nLoc1 = getLocation(nLoc1, nRoll, &nPassedGo);
            nLocation = nLoc1;
        }
        else {
            nLoc2 = getLocation(nLoc2, nRoll, &nPassedGo);
            nLocation = nLoc2;
        }

        printf("Player %d have landed on ", nPlayerNo);
        getPropertyName(nLocation);
        printf("\n");

           
        if (isSpecial(nLocation)) {
            if (nPassedGo == 1 || nLocation == 0) {
                nCurrentAmt += 200;
                printf("Player %d collect $200!\n", nPlayerNo);
            }
            else if (nLocation == 4)
            {
                printf("Player %d have lost your next turn.\n", nPlayerNo);
                // code line to put user to jail.
            }
            else if (nLocation == 6)
            {
                printf("Rolling dice to determine your luck...\n");
                nRoll = getRandom(1,9);
                if (isPrime(nRoll)) 
                    nCurrentAmt += getRandom(100,200);
                else if (nRoll == 1)
                {
                    nLocation = 4;
                }
                else
                    nCurrentAmt -= getRandom(50,150);
            }
        }
        else if (isOwned(nOpponent, nCurrent, nLocation)) {
            int nOwe = getRentAmount(nOpponent, nCurrent, nLocation, nRoll);
            printf("Player %d owes $%d", nPlayerNo, nOwe);
            nCurrentAmt -= nOwe;
        }
        else promptBuy(nCurrent, nLocation);


        playerSwitch(&nCurrent, &nOpponent, &nPlayerNo, nPlayer1, nPlayer2, nPlayertAmt1, nPlayertAmt2, &nCurrentAmt, &nOpponentAmt);
    }
    


    return 0;
}
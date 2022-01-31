/*
    Description:       This is a turn-based two-player board game.
    Programmed by:     John Kovie L. Niño S15B
    Last modified:     January 16, 2022
    Version:           1.0-alpha
    Acknowledgements:  Used the Standard Library (stdlib.h) and the Math Library (math.h) for making the program possible.
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
//#include <conio.h>
//#include <windows.h>
#include <unistd.h>

#define COLLECT_GO 200;
#define BUY_ELECTRIC 150;
#define BUY_RAILROAD 100;
#define PAY_RAILROAD_RENT 35;
#define PAY_RENOVATION 50;

/*
    Description: This function generates a random number ranging from the minimum to maximum.
    Precondition: The parameters given are integers.
    @param min: The minimum number.
    @param max: The maximum number.
    @return: random number ranging from its given minimum to maximum value
*/

int getRandom(int min, int max) {
       return min + rand() % (max + 1 - min);
}

/*
    Description: This function determines what location / property the player landed on.
    Precondition: The parameters given are integers.
    @param nLocation: The location of the player.
    @param nDiceRoll: The dice roll of the player.
    @param passedGo: The variable that determines if the player passed Go.
    @return returns the location of player
*/

int getLocation(int nLocation, int nDiceRoll, int * passedGo){
    if (nLocation + nDiceRoll > 9) {
        nLocation -= 10;
        *passedGo = 1;
    }
    return nLocation += nDiceRoll;
}

/*
    Description: This function prints the property's name that the player has landed on.
    Precondition: The parameter given are integers.
    @param location: The location of the player.
    @return returns the name of the property.
*/

void getPropertyName(int location) {
    switch (location) {
        case 0: printf("GO! COLLECT $200"); break;
        case 1: printf("TREEHOUSE"); break;
        case 2: printf("ELECTRIC COMPANY"); break;
        case 3: printf("BEACH HOUSE"); break;
        case 4: printf("JAIL TIME"); break;
        case 5: printf("CASTLE"); break;
        case 6: printf("FEELIN' LUCKY"); break;
        case 7: printf("RAILROAD COMPANY"); break;
        case 8: printf("IGLOO"); break;
        case 9: printf("FARM HOUSE"); break;
    }
}

/*
    Description: This function returns the specific digit of the given number.
    Precondition: The parameters given is an integer.
    @param current: The current player's owned properties.
    @param location: The location of the player.
    @return returns the specific digit of the given number.
*/

int getDigit(int current, int location) {
    int nDivisor = pow(10, location - 1);
    int nSplit = current / nDivisor;
    int nFinal = nSplit % 10;
    return nFinal;
}

/*
    Description: This function prints the player's owned properties.
    Precondition: The parameter given are integers.
    @param current: The current player's owned properties.
*/

void listAllProperties(int current) {
    int i;

    if (current == 0)
        printf("You don't own any properties!\n");

    if (current > 0) {
        for (i = 1; i < 10; i++) {
            if (getDigit(current, i) == 1 || getDigit(current, i) == 2) {
                printf("[%d]\t ", i);
                getPropertyName(i);
                if (getDigit(current, i) == 2)
                    printf(" (RENOVATED)");
                printf("\n");
            }
        }
    }
}

/*
    Description:        This functions check if the number given is Prime or not
    Precondition:       The parameter given is an integer
    @param  diceRoll =  the value needed to identify if Prime or not.
    @return 1        =  returns a TRUE boolean
    @return 0        =  returns a FALSE boolean
*/

int isPrime (int diceRoll) {
    int i; 
    int nDivisors = 0;
    for (i = 2; i <= diceRoll; i++) {
        if (diceRoll % i == 0)
            nDivisors++;
    }
    if (nDivisors == 2 || diceRoll == 2)
        return 1;

    return 0; 
}

/*
    Description: This function checks if the current or opponent owns the property
    Precondition: The parameters given are integers.
    @param current: The current player's owned properties.
    @param opponent: The opponent's owned properties.
    @param location: The location of the player landed on.
    @return returns a boolean value.
*/

int isOwned (int opponent, int current, int location) {
    int nLoc1 = getDigit(current, location); // Current player
    int nLoc2 = getDigit(opponent, location); // Opponent player

    if (nLoc2 == 1 || nLoc2 == 2) // Opponent owns it
        return 1;
    if (nLoc1 == 1 || nLoc1 == 2) // Current player owns it
        return 0;

    return 0; // Unowned
}

/*
    Description: This function checks if the property landed on is renovated or not.
    Precondition: The parameters given are integers.
    @param current: The current player's owned properties.
    @param location: The location of the player landed on.
    @return returns a boolean value.
*/

int isRenovated (int opponent, int current, int location) {
    int nLoc1 = getDigit(current, location); // Current player
    int nLoc2 = getDigit(opponent, location); // Opponent player

    if (nLoc2 == 2) // Opponent renovated it
        return 1;
    if (nLoc1 == 2) // Current player renovated it
        return 0;
    return 0;
}

/*
    Description: This function returns the buy price of the property.
    Precondition: The parameter is an integer.
    @param location: The location of the player landed on.
    return returns the buy price of the property.
*/

int getBuyPrice (int location) {
    switch (location)
    {
        case 2: return BUY_ELECTRIC; break;
        case 7: return BUY_RAILROAD; break;
        default: return location % 7 * 20; break;
    }
}

/*
    Description: This function returns a boolean value if the player can buy the property or pay rent.
    Precondition: The parameters given are integers.
    @param money: The current player's money.
    @param price: The price of the property.
    @return returns a boolean value.
*/

int hasMoney (int money, int price) {
    if (money >= price)
        return 1;
    return 0;
}

/*
    Description: This function prompts if the player wants to buy the property or not.
    Precondition: The parameters given are integers.
    @param current: The current player's owned properties.
    @param location: The location of the player landed on.
    @param money: The current player's money.
    return: returns the price of the property or 0 if the player doesn't want to buy it, also updates current if the player bought the property.
*/

int promptBuy(int * current, int location, int money) {
    char decide;
    int nPrice = getBuyPrice(location);
    sleep(1);
    getPropertyName(location);
    printf(" costs $%d.\n\n", nPrice);
    sleep(1);
    if (hasMoney(money, nPrice))
    {
        do {
            printf("%s\n%s\n\n%s\n%s\n%s",
            "This property is for sale!",
            "Please select the following:",
            "[1]\tPurchase Property from the bank",
            "[2]\tNot interested",
            ">> ");
    
            scanf("%c", &decide);
            if (!(decide == '1' || decide == '2'))
                printf("\nERROR: Invalid input. Please try again.\n\n");
        } while(!(decide == '1' || decide == '2'));

        sleep(1);
        if (decide == '1') {
            if (location == 2) {
                *current += pow(10, location-1);
                printf("You have purchased ");
                getPropertyName(location);
            }
                
            else if (location == 7) {
                *current += pow(10, location-1);
                printf("You have purchased ");
                getPropertyName(location);
            }

            else  {
                *current += pow(10, location-1);
                printf("You have purchased ");
                getPropertyName(location);
            }
            printf("!\n");
            sleep(1);
            return nPrice;
        } 

        if (decide == '2')
            return 0;
    }
    sleep(1);
    printf("This property is for sale!\n");
    sleep(1);
    printf("You have insufficient funds to buy this property!\n\n");
    return 0;
}

/*
    Description: This function prompts if the player wants to renovate or not.
    Precondition: The parameters given are integers.
    @param current: The current player's owned properties.
    @param location: The location of the player landed on.
    return: returns the renovation price of the property or 0 if the player doesn't want to renovate it, also updates current if the player renovated the property.
*/

int promptRenovate(int * current, int location) {
    char decide;
    do {
        sleep(1);
        printf("Your house property is not yet renovated.\nIf you're interested, it costs $50!\n\n");
        sleep(1);
        printf("%s\n\n%s\n%s\n%s",
        "Please select the following:",
        "[1]\tRenovate Property",
        "[2]\tNot interested",
        ">> ");
    
        scanf("%c", &decide);

        if (!(decide == '1' || decide == '2'))
            printf("\nERROR:Invalid input. Please try again.\n\n");
    } while(!(decide == '1' || decide == '2'));

    if (decide == '1') {
        *current += pow(10, location-1);
        return PAY_RENOVATION;
    }
    return 0;
}

/*
    Description: This function prompts to resell properties.
    Precondition: The parameters given are integers.
    @param current: The current player's owned properties.
    @param opponent: The opponent's owned properties.
    @param owe: The amount of money the player owes.
    @param money: The current player's money.
    return: Updates current properties and money of the player.
*/

void promptResellProperty(int * current, int * opponent, int owe, int * money) {
    int decide;
    while (*money < owe && *current != 0) {
        do {
            sleep(1);
            printf("%s\n", "Please resell one of your properties:");
            listAllProperties(*current);
            printf("\n>> ");
            scanf("%d", &decide);
            sleep(1);
            if (!isOwned(*current, *opponent, decide))
                printf("\nERROR: You don't own this property!\n\n");
        } while(!isOwned(*current, *opponent, decide));
        
        sleep(1);
        if (decide == 2) {
            printf("You have sold the ");
            getPropertyName(decide);
            *current -= pow(10, decide-1);
            *money += 150 / 2;
            printf(" for $%d!\n", 150 / 2);
        }
        else if (decide == 7) {
            printf("You have sold the ");
            getPropertyName(decide);
            *current -= pow(10, decide-1);
            *money += 100 / 2;  
            printf(" for $%d!\n", 100 / 2);
        }
        else {
            printf("You have sold ");
            getPropertyName(decide);
            if (getDigit(*current, decide) == 2)
                *current -= pow(10, decide-1) * 2;
            else
                *current -= pow(10, decide-1);
            *money += decide % 7 * 20;
            printf(" for $%d!\n", decide % 7 * 20);
        }
        sleep(1);
        printf("You no longer own this property.\n\n");

        if (*money < owe) {
            sleep(1);
            printf("You still need $%d to pay the rent! You still have to sell more properties!\n\n", owe - *money);
        }
    }
    sleep(1);
    if (*current == 0 && *money < owe){
        printf("You have no properties to sell!\n");
        sleep(1);
        printf("You have insufficient funds to pay $%d to the opponent! You are not able to pay rent!\n", owe);
    }
    
    sleep(1);
    if (*money >= owe) {
        printf("\nYou now have enough funds to pay the rent!\n");
        sleep(1);
        printf("\n====================================\n");
        printf("NEW Current Balance: $%d\n", *money);
        printf("====================================\n");
    }
}

/*
    Description: Outputs introductory message as program runs
*/
void introMsg() {
    char enter;
    printf("%s\n%s\n%s\n\n%s\n\n%s\n",
        "=====================================",
        "|| Welcome to Property...Property! ||",
        "=====================================",
        "This is a turn-based two-player board game.\nPlayers compete to acquire wealth by buying or renting properties.\nThe game ends when a player goes bankrupt, i.e. he does not have enough money to pay rent.",
        "Press ENTER to get started!" );

        scanf("%c", &enter);
        //system("cls");
        system("clear");
}

/*
    Description: This function switches the turn of the players.
    Precondition: The parameters given are integers.
    @param current: The current player's owned properties.
    @param opponent: The opponent's owned properties.
    @param playerno: The current player's number.
    @param player1: The first player's money balance.
    @param player2: The second player's money balance.
    @param amtcurrent: The amount of money the current player has.
    @param amtopponent: The amount of money the opponent has.
    return: transfers the data of the current player to the opponent and vice versa.
*/

void playerSwitch(int * current, int * opponent, int * playerno, 
                  int * player1, int * player2, int * amtcurrent, 
                  int * amtopponent) {
    int temp;

    if (*playerno == 1) {
        *player1 = *current;
        *current = *player2;
        *opponent = *player1;
        *playerno = 2;
    }
    else {
        *player2 = *current;
        *current = *player1;
        *opponent = *player2;
        *playerno = 1;
    }

    temp = *amtcurrent;
    *amtcurrent = *amtopponent;
    *amtopponent = temp;
}

/*
    Description: This function gets the rent amount of the property.
    Precondition: The parameters given are integers.
    @param opponent: The opponent's owned properties.
    @param current: The current player's owned properties.
    @param location: Player's current location.
    @param roll: Current dice roll the player has.
    return: The rent amount of the property.
*/

int getRentAmount(int opponent, int current, int location, int roll) {
    int nTotalAmt = getBuyPrice(location) * 2; // getBuyPrice(location) * 0.2

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

/*
    Description: Checks if the property landed on Property 1, 4, or 6.
    Precondition: The parameters given are integers.
    @param location: Player's current location.
    return: Returns true if the player landed on Property 1, 4, or 6.
*/

int isSpecial(int location) {
    if (location == 0 || location == 4 || location == 6)
        return 1;
    return 0;
}

/*
    Description: Pays amount to the opponent.
    Precondition: The parameters given are integers.
    @param current: The current player's money.
    @param opponent: The opponent's money.
    @param payment: The amount to pay.
    return: Deducts the amount from the current player's money and adds it to the opponent's money.
*/

void payAmount (int * current, int * opponent, int payment) {
    *current -= payment;
    *opponent += payment;
}

/*
    Description: Checks if the player can still play the game.
    Precondition: The parameters given are integers.
    @param money: The current player's money.
    @param current: The current player's owned properties.
    @param owe: The amount of money the player owes.
    return: Returns true if the player can still play the game.
*/

int isValidToPlay (int money, int current, int owe) {
    // Check if no properties and money left and cannot pay rent anymore.
    if (current == 0 && money < owe)
        return 0;
    return 1;
}

/*
    Description: prints end game summary and announces winner.
    Precondition: The parameters given are integers.
    @param player1: The first player's properties.
    @param player2: The second player's properties.
    @param money1: The first player's money.
    @param money2: The second player's money.
*/

void getGameSummary(int player1, int player2, int money1, int money2) {
    char enter;

    if (player1 == 0)
        printf("%s\n%s\n\n", "Player 2 wins!", "Congratulations!");
    else
        printf("%s\n%s\n\n", "Player 1 wins!", "Congratulations!");
    
    printf("=====================================\n");
    printf("            Game Summary\n");
    printf("=====================================\n\n");
    printf("=============[PLAYER %d]==============\n", 1);
    listAllProperties(player1);
    printf("\nRemaining Balance: $%d\n", money1);
    printf("\n=============[PLAYER %d]=============\n", 2);
    listAllProperties(player2);
    printf("\nRemaining Balance: $%d\n", money2);
    printf("\n=====================================\n\n");
    printf("The game ends.\n");
    printf("\nPress ENTER to EXIT.\n");
    scanf("%c", &enter);
}

int main() {
    srand(time(NULL));
    int nRoll, nLocation, nTempAmt;
    int nLoc1 = 0;
    int nLoc2 = 0;
    int nPlayer1 = 0;
    int nPlayer2 = 0;

    introMsg();

    int nCurrent = nPlayer1;
    int nOpponent = nPlayer2;
    int nPlayerNo = 1;
    int nCurrentAmt = 200;
    int nOpponentAmt = 200;
    int nPassedGo = 0;
    int nPlayer1Turns = 1;
    int nPlayer2Turns = 1;
    int nOwe = 0;
    
    while(isValidToPlay(nOpponentAmt, nOpponent, nOwe)) {
        printf("===============[PLAYER %d]==================\n", nPlayerNo);
        printf("Current Balance: $%d\n", nCurrentAmt);
        printf("Current Location: ");
        if (nPlayerNo == 1)
            getPropertyName(nLoc1);
        else
            getPropertyName(nLoc2);
        printf("\n===========================================\n");
        sleep(1);
        printf("Properties Owned:\n");
        listAllProperties(nCurrent);
        printf("===========================================\n\n");
        sleep(1);

        printf("Rolling Dice...\n");
        nRoll = getRandom(1,6);
        sleep(1);
        printf("Player %d has rolled [ %d ].\n", nPlayerNo, nRoll);
        

        // Assigning Location to the current player
        if (nPlayerNo == 1) {
            nLoc1 = getLocation(nLoc1, nRoll, &nPassedGo);
            nLocation = nLoc1;
        }
        else {
            nLoc2 = getLocation(nLoc2, nRoll, &nPassedGo);
            nLocation = nLoc2;
        }

        // Output where the Player has landed
        sleep(1);
        printf("Player %d has landed on ", nPlayerNo);
        getPropertyName(nLocation);
        printf(".\n");
        sleep(1);


        // Check if user has passed thru GO or Location 0
        if (nPassedGo == 1 && nLocation != 0) {
            nCurrentAmt += 200;
            printf("Player %d passed through GO! Collect $200.\n", nPlayerNo);
            sleep(1);
            printf("===========================================\n");
            printf("Player %d's NEW Balance: $%d\n", nPlayerNo, nCurrentAmt);
            printf("===========================================\n");
        }

        // Check if location lands on the special locations
        if (isSpecial(nLocation)) {
            if (nLocation == 0) {  // nLocation lands on 0.
                nCurrentAmt += 200;
                printf("Player %d collects $200!\n", nPlayerNo);
            }
            else if (nLocation == 4) // Lands on jail
            {
                printf("Player %d has lost its next turn.\n", nPlayerNo);
            }
            else if (nLocation == 6) // Feelin' Lucky
            {
                printf("Rolling dice to determine your luck...\n");
                nRoll = getRandom(1,6);
                sleep(1);
                printf("Player %d has has rolled [ %d ].\n", nPlayerNo, nRoll);
                sleep(1);

                if (isPrime(nRoll)) { // If the roll is a prime number
                    nTempAmt = getRandom(100,200);
                    nCurrentAmt += nTempAmt;
                    printf("Player %d has earned $%d!\n", nPlayerNo, nTempAmt);
                } 
                
                else if (nRoll == 1) { // If Roll lands on 1
                    nLocation = 4;
                    printf("Player %d has landed on ", nPlayerNo);
                    getPropertyName(nLocation);
                    printf("\nPlayer %d have lost its turn!\n", nPlayerNo);

                }
                else {
                    nTempAmt = getRandom(50,150);
                    nCurrentAmt -= nTempAmt;
                    printf("Player %d lost $%d.\n", nPlayerNo, nTempAmt);
                }
            }
        }
        else if (isOwned(nOpponent, nCurrent, nLocation)) { // If opponent owns it
            nOwe = getRentAmount(nOpponent, nCurrent, nLocation, nRoll);
            sleep(1);
            printf("Player %d owes $%d to the opponent.\n", nPlayerNo, nOwe);
            sleep(1);

            if (nCurrentAmt < nOwe) {
                printf("Player %d has insufficent funds!\n", nPlayerNo);
                sleep(1);
                printf("You're $%d short!\n\n", nOwe - nCurrentAmt);
                promptResellProperty(&nCurrent, &nOpponent, nOwe, &nCurrentAmt);
                payAmount(&nCurrentAmt, &nOpponentAmt, nOwe);
                sleep(1);
                if (nOwe == 0) {
                    printf("Player %d has now paid $%d to the opponent.\n\n", nPlayerNo, nOwe);
                }
            }
            else {
                payAmount(&nCurrentAmt, &nOpponentAmt, nOwe);
                sleep(1);
                printf("Player %d has now paid $%d to the opponent.\n\n", nPlayerNo, nOwe);
            }
        }
        else if (isOwned(nCurrent, nOpponent, nLocation)) { // If current player owns it
            printf("Player %d currently own this property!\n\n", nPlayerNo);
            if (!(isRenovated(nCurrent, nOpponent, nLocation) || nLocation == 2 || nLocation == 7)) {
                nCurrentAmt -= promptRenovate(&nCurrent, nLocation);
            }
        }
        else 
            nCurrentAmt -= promptBuy(&nCurrent, nLocation, nCurrentAmt);


        // Deduct Player Turns
        if (nPlayerNo == 1)
            nPlayer1Turns--;
        else
            nPlayer2Turns--;

        // Reset values when both have no more turns
        if(nPlayer1Turns == 0 && nPlayer2Turns == 0)
        {
            nPlayer1Turns = 1;
            nPlayer2Turns = 1;
        }

        // Check if user landed on Jail, add/reduce turns
        if (nLocation == 4) {
            if (nPlayerNo == 1) {
                nPlayer1Turns = 0;
                if (nLoc1 == 4 && nLoc2 == 4)
                    nPlayer2Turns = 1;
                else
                    nPlayer2Turns = 2;
            }
                
            else {
                nPlayer2Turns = 0;
                if (nLoc1 == 4 && nLoc2 == 4)
                    nPlayer1Turns = 1;
                else
                    nPlayer1Turns = 2;
            }
        }

        if (nCurrentAmt >= 0) {
            printf("===========================================\n");
            printf("Player %d's NEW Balance: $%d\n", nPlayerNo, nCurrentAmt);
            printf("===========================================\n");
            printf("\n\nPress ENTER to continue.\n");
        }

        // If opponent has 1 turn, next player
        if (nPlayerNo == 1) {
            if (nPlayer2Turns > 0)
                playerSwitch(&nCurrent, &nOpponent, &nPlayerNo, &nPlayer1, &nPlayer2, &nCurrentAmt, &nOpponentAmt);
        }
        else {
            if (nPlayer1Turns > 0)
                playerSwitch(&nCurrent, &nOpponent, &nPlayerNo, &nPlayer1, &nPlayer2, &nCurrentAmt, &nOpponentAmt);
        }
        nPassedGo = 0;
        char enter;
        scanf("%c", &enter);
        //system("cls");
        //system("clear");
    }
    getGameSummary(nCurrent, nOpponent, nCurrentAmt, nOpponentAmt);

    return 0;
}

/*
    This is to certify that this project is my own work, based on my personal efforts in studying and applying the concepts
    learned. I have constructed the functions and their respective algorithms and corresponding code all by myself. The
    program was run, tested, and debugged by my own efforts. I further certify that I have not copied in part or whole
    or otherwise plagiarized the work of other students and/or persons.
    
    John Kovie L. Niño
    DLSU ID 12109975
*/
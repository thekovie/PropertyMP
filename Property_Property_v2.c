/**
 * Description:       This is a turn-based two-player board game.
 * Programmed by:     John Kovie L. Niño S15B
 * Last modified:     February 4, 2022
 * Version:           2.0
 * Acknowledgements:  I thank https://unix.stackexchange.com/questions/293940/how-can-i-make-press-any-key-to-continue
 *                    and https://stackoverflow.com/questions/5725296/difference-between-sh-and-bash
 *                    for the help in implementing the pause code in some operating systems and other libraries for making
 *                    this project possible.            
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <unistd.h>
#if defined(_WIN32)
    #include <conio.h>
#endif

void displayKey() {
    printf("\n\nPress any key to continue...\n");
    #if defined(_WIN32) && !defined(UNIX)
        getch();
    #else
        system("sh -c \"read -n 1 -sr\"");
    #endif
}

/*
    Description: This function is to configure the game's values.
    Pre-condition: The parameters given are integers.
    @param nCash: Starting cash of each player.
    @param rentRailroad: Rent cost of the railroad.
    @param activateCond: To activate the end-game condition.
    @param cashCond: Modify the end-game condition.
    @param multiplierElectric: Rent multiplier of the electric company.
    @param minPrimeAmt: Minimum cash amount of prime numbers under Feelin' Lucky.
    @param maxPrimeAmt: Maximum cash amount of prime numbers under Feelin' Lucky.
    @param minAmt: Minimum cash amount of non-prime numbers under Feelin' Lucky.
    @param maxAmt: Maximum cash amount of non-prime numbers under Feelin' Lucky.
    @param costRenovation: Cost of the renovation of the property.
    @return: Multiple return values that will be used in the main function.
*/
void gameConfiguration(int * nCash, int * rentRailroad, int * activateCond,
                      int * cashCond, int * multiplierElectric, int * minPrimeAmt,
                      int * maxPrimeAmt, int * minAmt, int * maxAmt, int * costRenovation) {
        
        char choice;
        while (choice != '0') {
            system("cls || clear");
            printf("----------------------[ GAME CONFIGURATION ]--------------------------\n");
            printf("            Select the following you want to configure:\n\n");
            printf("1 - Starting Cash: \t\t\t\t$%d\n", *nCash);
            printf("2 - [RENT] Electric Company Multiplier: \tx%d\n", *multiplierElectric);
            printf("3 - [RENT] Railroad: \t\t\t\t$%d \n", *rentRailroad);
            printf("4 - [FEELIN' LUCKY] Minimum Prime Amount: \t$%d\n", *minPrimeAmt);
            printf("5 - [FEELIN' LUCKY] Maximum Prime Amount: \t$%d\n", *maxPrimeAmt);
            printf("6 - [FEELIN' LUCKY] Minimum Non-Prime Amount: \t$%d\n", *minAmt);
            printf("7 - [FEELIN' LUCKY] Maximum Non-Prime Amount: \t$%d\n", *maxAmt);
            printf("8 - RENOVATION Cost: \t\t\t\t$%d\n", *costRenovation);
            if (!*activateCond)
                printf("9 - [END-GAME CONDITION] Lowest Cash: \t\tDISABLED");
            else
                printf("9 - [END-GAME CONDITION] Lowest Cash: \t\t$%d\n", *cashCond);
            printf("\n---------------------------------------------------------------------\n");
            printf("0 - Exit Game Configuration and Start Game!\n\n");
            printf(">> ");
            scanf(" %c", &choice);

            sleep(1);
            switch (choice) {
                case '1':
                    printf("\nEnter the new starting cash: ");
                    scanf("%d", nCash);
                    break;
                case '2':
                    printf("\nEnter the new rent multiplier for Electric Company: ");
                    scanf("%d", multiplierElectric);
                    break;
                case '3':
                    printf("\nEnter the new rent cost of Raiload: ");
                    scanf("%d", rentRailroad);
                    break;
                case '4':
                    printf("\nEnter the new minimum prime amount: ");
                    scanf("%d", minPrimeAmt);
                    break;
                case '5':
                    printf("\nEnter the new maximum prime amount: ");
                    scanf("%d", maxPrimeAmt);
                    break;
                case '6':
                    printf("\nEnter the new minimum non-prime amount: ");
                    scanf("%d", minAmt);
                    break;
                case '7':
                    printf("\nEnter the new maximum non-prime amount: ");
                    scanf("%d", maxAmt);
                    break;
                case '8':
                    printf("\nEnter the new Renovation Cost: ");
                    scanf("%d", costRenovation);
                    break;
                case '9':
                    printf("\nEnter the lowest cash-on-hand condition (Input 0 to disable): ");
                    scanf("%d", cashCond);
                    if (*cashCond == 0)
                        *activateCond = 0;
                    else
                     *activateCond = 1;
                    break;
                case '0':
                    break;
                default:
                    printf("\nERROR: Invalid choice. Try Again!\n");
                    break;
            }
            sleep(1);
        }
        system("cls || clear");
}

/*
    Description: This function generates and returns a random number ranging from the minimum to maximum.
    Precondition: The parameters given are integers.
    @param min: The minimum number.
    @param max: The maximum number.
    @return: random number ranging from its given minimum to maximum value
*/

int getRandom(int min, int max) {
       return min + rand() % (max + 1 - min);
}

/*
    Description: This function determines what location / property number the player landed on.
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
    @param renovated: The variable that determines if the property is renovated.
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
    Description: This function returns the specific digit of the given 9-digit number.
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
        printf("No properties owned.\n");

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
    Description:        This function checks if the number given is Prime or not
    Precondition:       The parameter given is an integer
    @param  diceRoll =  the value needed to identify if Prime or not.
    @return 1        =  returns a TRUE boolean
    @return 0        =  returns a FALSE boolean
*/

int isPrime (int diceRoll) {
    int i; 
    int nDivisors = 1;
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
    int nLoc1 = getDigit(current, location);
    int nLoc2 = getDigit(opponent, location);

    if (nLoc2 == 1 || nLoc2 == 2) // Current user owns it
        return 1;
    if (nLoc1 == 1 || nLoc1 == 2) // Another player owns it
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

    if (nLoc2 == 2) // Current user renovated it
        return 1;
    if (nLoc1 == 2) // Another player renovated it
        return 0;
    return 0; // Unrenovated
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
        case 2: return 150; break; // Electric Company
        case 7: return 100; break; // Railroad Company
        default: return location % 7 * 20; break; // Other properties
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
    
            scanf(" %c", &decide);
            if (!(decide == '1' || decide == '2'))
                printf("\nERROR: Invalid input. Please try again.\n\n");
        } while(!(decide == '1' || decide == '2'));

        sleep(1);
        if (decide == '1') {
            *current += pow(10, location-1);
            printf("You have purchased ");
            getPropertyName(location);
            printf("!\n");
            return nPrice;
        } 
        if (decide == '2')
            return 0;
    }
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
    @param renPrice: The renovation cost of the property.
    return: returns the renovation price of the property or 0 if the player doesn't want to renovate it, also updates current if the player renovated the property.
*/

int promptRenovate(int * current, int location, int renPrice) {
    char decide;
    do {
        sleep(1);
        printf("Your house property is not yet renovated.\nIf you're interested, it costs $%d!\n\n", renPrice);
        sleep(1);
        printf("%s\n\n%s\n%s\n%s",
        "Please select the following:",
        "[1]\tRenovate Property",
        "[2]\tNot interested",
        ">> ");
    
        scanf(" %c", &decide);

        if (!(decide == '1' || decide == '2'))
            printf("\nERROR:Invalid input. Please try again.\n\n");
    } while(!(decide == '1' || decide == '2'));

    if (decide == '1') {
        *current += pow(10, location-1);
        printf("You have renovated this property!\n");
        return renPrice;
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
        printf("You have sold the ");
        getPropertyName(decide);

        // Update sold property
        if (getDigit(*current, decide) == 2)
                *current -= pow(10, decide-1) * 2;
            else
                *current -= pow(10, decide-1);

        *money += getBuyPrice(decide) / 2; // Update money from sold property

        printf(" for $%d!\n", getBuyPrice(decide) / 2);
        
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
        printf("====================================\n\n");
    }
}

/*
    Description: Outputs introductory message as program runs
*/
void introMsg() {
    printf("%s\n%s\n%s\n\n%s\n\n",
        "=====================================",
        "|| Welcome to Property...Property! ||",
        "=====================================",
        "This is a turn-based two-player board game.\nPlayers compete to acquire wealth by buying or renting properties.\nThe game ends when a player goes bankrupt, i.e. he does not have enough money to pay rent (unless the player modifies its condition).");
        
        sleep(2);
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
    int temp; // temporary variable to store the current player's money

    if (*playerno == 1) {
        *player1 = *current; // store the current player's properties
        *current = *player2; // transfer the player 2's properties to the current player
        *opponent = *player1; // transfer the current player 1's properties to the opponent
        *playerno = 2; // switch the current player to player 2
    }
    else {
        *player2 = *current; // store the current player's properties
        *current = *player1; // transfer the player 1's properties to the current player
        *opponent = *player2; // transfer the current player 2's properties to the opponent
        *playerno = 1; // switch the current player to player 1
    }

    temp = *amtcurrent; // store the current player's money
    *amtcurrent = *amtopponent; // transfer the opponent's money to the current player
    *amtopponent = temp; // transfer the current player's money to the opponent
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

int getRentAmount(int opponent, int current, int location, int roll, int multiplier, int railroad) {
    int nTotalAmt = getBuyPrice(location) * 0.2; // Original rent amount

    if (!isRenovated(opponent, current, location)) { // If not renovated property
            switch (location) {
                case 2: return roll * multiplier; // ELECTRIC RENT
                case 7: return railroad; // RAILROAD RENT
            }
        }
    else { // Rent amount with renovation
        printf("This property is renovated by the opponent. There will be additional rent charges.\n");
        nTotalAmt = nTotalAmt * 2 + 1;
    }
    return nTotalAmt;
}

/*
    Description: Checks if the property landed on Property 0, 4, or 6.
    Precondition: The parameters given are integers.
    @param location: Player's current location.
    return: Returns true if the player landed on Property 0, 4, or 6.
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
    // Pay amount to opponent
    *current -= payment;
    *opponent += payment;
}

/*
    Description: Checks if the player can still play the game.
    Precondition: The parameters given are integers.
    @param money: The current player's money.
    @param current: The current player's owned properties.
    @param owe: The amount of money the player owes.
    @param cashcondition: The amount of money set by the player to end the game.
    @param activatecondition: A boolean value that determines if the player has enabled the cash condition.
    return: Returns true if the player can still play the game.
*/

int isValidToPlay (int money, int current, int owe, int cashcondition, int activatecondition) {
    // If the player has enabled the cash condition and the player has enough money to end the game
    if (activatecondition == 1 && (money <= cashcondition)) 
        return 0;
    // If the player has not enough money to pay the rent and has run out of properties to sell
    if (current == 0 && money < owe)
        return 0;
    return 1;
}

/*
    Description: Prompts the game menu and returns the user's choice
    Precondition: None
    @return: Returns the user's choice.
*/

int printMenu () {

    int choice;
    do {
        printf("\n------------------------------------------------------\n");
        printf("Please select the following:\n\n");
        printf("1. Configure Game\n2. Start Game\n3. Exit Game\n");
        printf("\n------------------------------------------------------\n");
        printf(">> ");
        scanf("%d", &choice);

        if (choice == 1)
            return 1;
        
        else if (choice == 2)
            return 2;

        if (!(choice >= 1 && choice <= 3))
            printf("\nInvalid input. Please try again.\n");

    } while (!(choice >= 1 && choice <= 3));
    system("cls || clear");
            
    return 0;
}

/*
    Description: Prints end game summary and announces winner.
    Precondition: The parameters given are integers.
    @param player1: The first player's properties.
    @param player2: The second player's properties.
    @param money1: The first player's money.
    @param money2: The second player's money.
    @param playerno: The current player's number.
*/

void getGameSummary(int player1, int player2, int money1, int money2, int playerno) {

    // If both has the same amount of money, it is a draw
    if (money1 == money2) {
            printf("\n====================================\n");
            printf("It's a draw! Congratulations!\n");
            printf("====================================\n");
    }
    // Player 1 winner
    else if (playerno == 1) {
            printf("\n====================================\n");
            printf("Player 2 has gone bankrupt!\n");
            printf("Player 1 has won the game! Congratulations\n");
            printf("====================================\n");
    }
    // Player 2 winner
    else {
            printf("\n====================================\n");
            printf("Player 1 has gone bankrupt!\n");
            printf("Player 2 has won the game! Congratulations\n");
            printf("====================================\n");
    }
    // Show game summary
    sleep(1);
    printf("=====================================\n");
    printf("            Game Summary\n");
    printf("=====================================\n\n");
    sleep(1);
    printf("=============[PLAYER %d]==============\n", 1);
    listAllProperties(player1);
    printf("\nRemaining Balance: $%d\n", money1);
    sleep(1);
    printf("\n=============[PLAYER %d]==============\n", 2);
    listAllProperties(player2);
    printf("\nRemaining Balance: $%d\n", money2);
    printf("\n=====================================\n\n");
    sleep(1);
    printf("The game ends.\n\n");
    sleep(1);
    displayKey();
}

int main() {
    srand(time(NULL));
    int nDecide;

    // Intro Message
    introMsg();

    do {
        // Player 1 and 2 Current Stats
        int nLoc1 = 0, nLoc2 = 0;
        int nPlayer1 = 0, nPlayer2 = 0;

        // Configurable variables
        int nInitialMoney = 200;
        int nActivateCondition = 0;
        int nCashCondition = 0;
        int nMultiplierElectric = 8;
        int nRentRailroad = 35;
        int nMinPrimeAmt = 100;
        int nMaxPrimeAmt = 200;
        int nMinNonAmt = 50;
        int nMaxNonAmt = 150;
        int nRenovationCost = 50;

        // Menu
        nDecide = printMenu();

        if (nDecide == 1)
            gameConfiguration(&nInitialMoney, &nRentRailroad, &nActivateCondition, &nCashCondition, &nMultiplierElectric, &nMinPrimeAmt, &nMaxPrimeAmt, &nMinNonAmt, &nMaxNonAmt, &nRenovationCost);
        
        // Initialize the game
        int nRoll, nLocation, nTempAmt;
        int nCurrent = nPlayer1;
        int nOpponent = nPlayer2;
        int nPlayerNo = 1;
        int nCurrentAmt = nInitialMoney;
        int nOpponentAmt = nInitialMoney;
        int nPassedGo = 0;
        int nPlayer1Turns = 1;
        int nPlayer2Turns = 1;
        int nOwe = 0;

        while(isValidToPlay(nOpponentAmt, nOpponent, nOwe, nCashCondition, nActivateCondition) && (nDecide == 2 || nDecide == 1)) {
            system("clear || cls");

            /* PLAYER STATS */
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

            /* ROLL DICE */
            printf("Rolling Dice...\n");
            nRoll = getRandom(1,6);
            sleep(1);
            printf("Player %d has rolled [ %d ].\n", nPlayerNo, nRoll);
            

            /* Assigning Location to the current player */
            if (nPlayerNo == 1) {
                nLoc1 = getLocation(nLoc1, nRoll, &nPassedGo);
                nLocation = nLoc1;
            }
            else {
                nLoc2 = getLocation(nLoc2, nRoll, &nPassedGo);
                nLocation = nLoc2;
            }

            /* Output where the Player has landed */
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
                        nTempAmt = getRandom(nMinPrimeAmt, nMaxPrimeAmt);
                        nCurrentAmt += nTempAmt;
                        printf("Player %d has earned $%d!\n", nPlayerNo, nTempAmt);
                    } 
                    
                    else if (nRoll == 1) { // If Roll lands on 1
                        nLocation = 4;
                        printf("Player %d has landed on ", nPlayerNo);
                        getPropertyName(nLocation);
                        printf("\nPlayer %d have lost its turn!\n", nPlayerNo);

                    }
                    else { // If the roll is a non-prime number
                        nTempAmt = getRandom(nMinNonAmt, nMaxNonAmt);
                        nCurrentAmt -= nTempAmt;
                        printf("Player %d lost $%d.\n", nPlayerNo, nTempAmt);
                    }
                }
            }
            // If opponent owns it
            else if (isOwned(nOpponent, nCurrent, nLocation)) { 
                nOwe = getRentAmount(nOpponent, nCurrent, nLocation, nRoll, nMultiplierElectric, nRentRailroad);
                sleep(1);
                printf("Player %d owes $%d to the opponent.\n", nPlayerNo, nOwe);
                sleep(1);

                if (nCurrentAmt < nOwe) {
                    printf("Player %d has insufficent funds!\n", nPlayerNo);
                    sleep(1);
                    printf("You're $%d short!\n\n", nOwe - nCurrentAmt);
                    promptResellProperty(&nCurrent, &nOpponent, nOwe, &nCurrentAmt);
                    if (nOwe < nCurrentAmt)
                        printf("Player %d has now paid $%d to the opponent.\n\n", nPlayerNo, nOwe);
                    payAmount(&nCurrentAmt, &nOpponentAmt, nOwe);
                    sleep(1);
                }
                else {
                    payAmount(&nCurrentAmt, &nOpponentAmt, nOwe);
                    sleep(1);
                    printf("Player %d has now paid $%d to the opponent.\n\n", nPlayerNo, nOwe);
                }
            }
            // If current player owns it
            else if (isOwned(nCurrent, nOpponent, nLocation)) { 
                printf("Player %d currently own this property!\n\n", nPlayerNo);

                // Check property if it is renovated
                if (!(isRenovated(nCurrent, nOpponent, nLocation) || nLocation == 2 || nLocation == 7)) {
                    if (hasMoney(nCurrentAmt, nRenovationCost))
                        nCurrentAmt -= promptRenovate(&nCurrent, nLocation, nRenovationCost);
                    else
                        printf("Player %d has insufficent funds to renovate this property!\n", nPlayerNo);
                }
            }
            // Property for sale
            else 
                nCurrentAmt -= promptBuy(&nCurrent, nLocation, nCurrentAmt);


            // Deduct Player Turns
            if (nPlayerNo == 1)
                nPlayer1Turns--;
            else
                nPlayer2Turns--;

            // Reset values when both have no more turns
            if (nPlayer1Turns == 0 && nPlayer2Turns == 0)
            {
                nPlayer1Turns = 1;
                nPlayer2Turns = 1;
            }

            // Check if user landed on Jail, add and reduce turns
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

            // Outputs the current player's balance if amount is above or equal to 0
            if (nCurrentAmt >= 0) {
                sleep(1);
                printf("\n===========================================\n");
                printf("Player %d's NEW Balance: $%d\n", nPlayerNo, nCurrentAmt);
                printf("===========================================\n");
            }

            // Switching of turns
            if (nPlayerNo == 1) {
                if (nPlayer2Turns > 0)
                    playerSwitch(&nCurrent, &nOpponent, &nPlayerNo, &nPlayer1, &nPlayer2, &nCurrentAmt, &nOpponentAmt);
            }
            else {
                if (nPlayer1Turns > 0)
                    playerSwitch(&nCurrent, &nOpponent, &nPlayerNo, &nPlayer1, &nPlayer2, &nCurrentAmt, &nOpponentAmt);
            }
            // Resetting for next player
            nPassedGo = 0;

            // Prompt to continue
             displayKey();
        }
        system("clear || cls");
        if (nDecide != 0)
            getGameSummary(nCurrent, nOpponent, nCurrentAmt, nOpponentAmt, nPlayerNo);

    } while(nDecide == 1 || nDecide == 2);
    
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
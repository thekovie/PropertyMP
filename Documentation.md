# Documentation

This repository started at December 23, 2021.

## <u>Formulas or Algorithms</u>

### Variables
```c
# Monitor 9-digit integer
int nPlayer1; 
int nPlayer2;
```

```c
# Monitor amount left
int nPlayertAmt1 = 200;
int nPlayertAmt2 = 200;
```

### Buying Properties
```c
nElectric = 150;

nRailroad = 100;

nHouses = position % 7 * 20;
```
### Paying Rent
```c
nElectric = diceRoll * 8;

nRailroad = 35;
```


House Properties (Paying rent)
```c
# The rent of an unrenovated
property is one-fifth of its cost.

nUnrenovated = nHouses / 0.2;
```

```c
# The rent of a renovated property is one plus twice the rent (unrenovated).

nRenovated = nUnrenovated * 2 + 1;
```

### Dice Roll
```c
# Generates 10 numbers

diceRoll = rand() % 9 + 1
```

### Feelin' Lucky
```c
# Checking Prime Number

int isPrime (int diceRoll) {
    int i, nDivisors;
    for (i = 2, i < = diceRoll; i++) {
        if (diceRoll % i == 0)
            nDivisors++
    }
    if (nDivisors == 2)
        return 1;

    return 0; 
}
```
```c
# Check if diceRoll is equal to 0, player goes to jail.
```

### Not enough cash!
```c
# Resell value of the property is half the cost of the property

property / 2;
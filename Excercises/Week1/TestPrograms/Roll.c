#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>
#include <time.h>

int main(){
    int Sides, Dice, FinalRoll = 0;
    char inputSides[20];
    char inputDice[20];
    srand (time(NULL)); //seeds the Random number to the time to generate a more random number
    while (Sides < 1){
        printf("Enter the amount of dice\n");
        scanf("%s", inputDice);
        printf("Enter the amount of dice sides\n");
        scanf("%s", inputSides);
        int lengthSides = strlen(inputSides);
        int lengthDice = strlen(inputDice);
        int failedCondition = 1;
        for (int i = 0; i < lengthSides; i++){
            if (!isdigit(inputSides[i])){   
                failedCondition--;
            }
        }
        for (int j = 0; j < lengthDice; j++){
            if (!isdigit(inputDice[j])){   
                failedCondition--;
            }
        }
        if (failedCondition == 1){
            Sides = atoi(inputSides);
            Dice = atoi(inputDice);
        }
          
    }
    int min = 1; //Lowest number for the randomizer
    for (int i = 0; i < Dice; i++){
        int diceRoll = rand() % (Sides) + min;
        FinalRoll += diceRoll;
    }
    printf("You have rolled the number: %d\n", FinalRoll);
    return 0;
}
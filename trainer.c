//
// Created by samuel on 05.01.21.
//

#include "library.h"
#include <time.h>

void exercise (struct word *start) {
    char input[WORD_LENGTH];
    //loop for learning vocabulary, breaks with input of "exit"
    printf("Willkommen beim Vokabeltrainer!\n"
           "Um aufzuhoeren einfach \"exit\" eingeben.\n\n");
    do {
        struct word currWord = randomWord(start);
        printf("Das gegebene Wort ist: %s\n", currWord.engWord);

        getWord(input, start);

        if (strncmp(input, "exit", 4) == 0){
            printf("Vokabeltrainer wurde beendet.\n");
            break;
        }

        if (strncmp(currWord.gerWord, input, strlen(input)) == 0){
            printf("Die Eingabe war korrekt!\n");
        } else {
            printf("Die Antwort \"%s\" war leider falsch. ", input);
            printf("Richtig gewesen waere: \"%s\"\n", currWord.gerWord);
        }
    } while (&free);
}

struct word randomWord (struct word *start) {
    struct word *temp = start->next;
    int number = getRandomInt(start);
    //picks random element from wordlist
    for (int i = 0; temp->next != NULL && i <= number; i++) {
        temp = temp->next;
    }
    return *temp;
}

void printEverything (struct word *start) {
    struct word *temp = start->next;
    printf("\nEnglish\t\t\tDeutsch\n\n");

    //prints content of wordlist
    while (temp != NULL) {
        printf("%-20s\t%s\n", temp->engWord, temp->gerWord);
        temp = temp->next;
    }
    printf("\n\n");
}

int getRandomInt (struct word *start) {
    //seed for rand()
    srand((time(NULL) * time(NULL)));
    return rand() % getCountWords(start);
}

int getCountWords (struct word *start) {
    int i;
    struct word *temp = start->next;

    //loop counts elements in wordlist
    for (i = 0; temp != NULL; i++) {
        temp = temp->next;
    }
    return i;
}
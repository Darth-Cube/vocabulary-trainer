//
// Created by samuel on 05.01.21.
//

#include "library.h"
#include <time.h>

void exercise(struct word *start) {
    char input[WORD_LENGTH];
    //Schleife, die durch nutzereingabe von 'naechstes' aufrechterhalten wird, funktion randomWord wird immer aufgerufen
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

struct word randomWord(struct word *start) {
    struct word *temp = start->next;
    int i = 0;
    int number = getRandomInt(start);
    //Liste wird "number" Elemente durchlaufen, zufallselement wird ausgesucht und zurückgegeben
    for (; temp->next != NULL && i <= number; i++) {
        temp = temp->next;
    }
    return *temp;
}

void printEverything(struct word *start) {
    struct word *temp = start->next;
    printf("\nEnglish\t\t\tDeutsch\n\n");

    //gibt gesamte Liste Zeile fuer Zeile aus
    while (temp != NULL) {
        printf("%-20s\t%s\n", temp->engWord, temp->gerWord);
        temp = temp->next;
    }
    printf("\n\n");
}

int getRandomInt(struct word *start) {
    srand((time(NULL) * time(NULL)));
    //Zufallszahl mit time(NULL) zum quadrat als seed begrenzt durch modulo anzahl an woertern
    int random = rand() % getCountWords(start);
    return random;
}

int getCountWords(struct word *start) {
    int i;
    struct word *temp = start->next;

    //schleife zaehlt vom Anfang bis zum Ende der Liste
    for (i = 0; temp != NULL; i++) {
        temp = temp->next;
    }
    return i;
}
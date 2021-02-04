//
// Created by samuel on 05.01.21.
//

#include "library.h"

int main() {
    struct word *start = addWord("0", "0", NULL);

    if (start == NULL) {
        fprintf(stderr, "Speicher konnte nicht initialisiert werden!\n");
        return EXIT_FAILURE;
    }

    if (initiate(start)) {
        return EXIT_FAILURE;
    }

    selector(start);

    return EXIT_SUCCESS;
}

void selector(struct word *start) {
    printf("\nBitte Namen der Funktion eingeben, "
           "fuer mehr \"hilfe\" eingeben.\n");
    char input[WORD_LENGTH];
    fgets(input, WORD_LENGTH, stdin);

    //loop adds case-sensitivity
    for (int i = 0; input[i] != '\0'; i++) {
        input[i] = tolower(input[i]);
    }
    int function = 0;

    unsigned int len = strlen(input)-1;

    if (strncmp(input, "hilfe", len) == 0) {
        function = 1;
    } else if (strncmp(input, "neu", len) == 0) {
        function = 2;
    } else if (strncmp(input, "loeschen", len) == 0) {
        function = 3;
    } else if (strncmp(input, "ausgeben", len) == 0) {
        function = 4;
    } else if (strncmp(input, "speichern", len) == 0) {
        function = 5;
    } else if (strncmp(input, "ueben", len) == 0) {
        function = 6;
    } else if (strncmp(input, "beenden", len) == 0) {
        function = 7;
    } else if (strncmp(input, "fehler", len) == 0) {
        function = 8;
    } else if (strncmp(input, "oeffnen", len) == 0) {
        function = 9;
    }else if (strncmp(input, "fehler loeschen", len) == 0) {
        function = 10;
    }
    switch (function) {
        case 1:
            printf("\n");
            printf("hilfe\t\t gibt die Hilfe-Uebersicht aus.\n");
            printf("neu\t\t erstellt eine neue Vokabel.\n");
            printf("loeschen\t entfernt eine Vokabel.\n");
            printf("ausgeben\t gibt alle Vokabeln aus.\n");
            printf("speichern\t speichert die Vokabeln ab.\n");
            printf("ueben\t\t ruft den Vokabeltrainer auf.\n");
            printf("fehler\t\t gibt die Fehler-Datei aus.\n");
            printf("fehler loeschen  loescht den Inhalt der Fehler-Datei.\n");
            printf("oeffnen\t\t oeffnet den Vokabel-Speicher erneut.\n "
                   "\t\t Achtung: aktueller Stand wird nicht erneut abgespeichert!\n");
            printf("beenden\t\t beendet das Programm.\n");
            printf("\n\n");
            selector(start);
            break;
        case 2:
            newWord(start);
            selector(start);
            break;
        case 3:
            delete(start);
            selector(start);
            break;
        case 4:
            printEverything(start);
            selector(start);
            break;
        case 5:
            saveData(start);
            selector(start);
            break;
        case 6:
            exercise(start);
            selector(start);
            break;
        case 7:
            stop(start);
            return;
        case 8:
            viewErrors();
            selector(start);
            break;
        case 9:
            close(start);
            struct word *ptr = addWord("0", "0", NULL);
            reopen(ptr);
            selector(ptr);
            break;
        case 10:
            remErrors();
            selector(start);
        default:
            selector(start);
            break;
    }
}

void delete(struct word *start) {
    char word[WORD_LENGTH];
    printf("Bitte zu loeschendes Wort eingeben:\n");
    if (getWord(word, start) == 0){
        fprintf(stderr,"Das Wort existiert nicht.\n");
        return;
    }
    //asks if word really should get deleted
    printf("Geben Sie 1 ein, wenn Sie \"%s\" wirklich loeschen wollen, ansonsten 2:\n", word);
    int number[1];
    scanf("%d", number);
    if (number[0] == 1) {
        if (delWord(word, start) == 0) {
            printf("Vokabel wurde geloescht!\n\n\n");
        }
    } else {
        printf("Vokabel wurde nicht geloescht.\n\n\n");
    }
}

void newWord(struct word *start) {
    printf("Bitte das Englische Wort eingeben:\n");
    char engWord[WORD_LENGTH], gerWord[WORD_LENGTH];
    //tests if word is in list
    if(getWord(engWord, start) == 2){
        printf("Das Wort ist bereits vorhanden.\n");
        return;
    }
    printf("Nun das Deutsche Wort:\n");
    if(getWord(gerWord, start) == 2){
        printf("Das Wort ist bereits vorhanden.\n");
        return;
    }

    struct word *temp = start;
    //goes to last element of wordlist
    while (temp->next != NULL) {
        temp = temp->next;
    }
    if ((temp->next = addWord(engWord, gerWord, temp)) == NULL) {
        fprintf(stderr, "Vokabel konnte nicht hinzugefuegt werden!");
        return;
    }
    printf("Vokabel wurde hinzugefuegt.\n");
}

int getWord(char *word, struct word *start) {
    fgets(word, WORD_LENGTH, stdin);
    //formats user input (removes ascii '\n')
    for (int i = 0; word[i] != '\0'; i++) {
        if (word[i] == '\n') {
            word[i] = '\0';
            break;
        }
    }
    int buf = proofRead(word, start);

    if (buf == 1) {
        fprintf(stderr, "Das Wort scheint Fehlerhaft zu sein, bitte geben Sie es erneut ein:\n");
        getWord(word, start);
    } else if (buf == 2){
        return 2;
    }
    return EXIT_SUCCESS;
}

void reopen(struct word *start){
    if (start == NULL) {
        fprintf(stderr, "Speicher konnte nicht initialisiert werden!\n"
                        "Das Programm wird nun beendet.\n");
        return ;
    }
    if (initiate(start)) {
        fprintf(stderr, "Beim oeffnen der Dateien ist ein Fehler aufgetreten.\n"
                        "Das Programm wird nun beendet.\n");
        return;
    }
    printf("Die Vokabel-Datei wurde erneut geoeffnet.\n");
}

void stop(struct word *start){
    if (saveData(start)) {
        fprintf(stderr, "Durch einen Fehler, konnten die Vokabeln nicht gespeichert werden.\n "
                        "Das Programm wird daher noch nicht beendet.\n");
        return;
    }
    close(start);
    printf("Das Programm wurde beendet.\n");
}

int initiate(struct word *start) {
    //opens stream from 'errors.dat'
    FILE *errors = fopen("errors.dat", "a");
    if (errors == NULL) {
        fprintf(stderr, "Kritischer Fehler!\n Programm wird nun geschlossen.\n");
        fflush(stderr);
        return 1;
    }

    //opens stream from 'words.dat'
    FILE *words = fopen("vocabulary.dat", "r");

    if (words == NULL) {
        fprintf(errors, "Vokabel-Datei konnte nicht geöffnet werden.\n");

        words = fopen("vocabulary.dat", "w");
        if (words == NULL) {
            fprintf(stderr, "Speicherort Fehlerhaft!\n");
            fflush(stderr);
            fclose(errors);
            return 1;
        } else {
            fprintf(stdout, "Es wurde eine neue Datei angelegt, da vorher keine existierte.\n");
            return 0;
        }
    }

    if (readData(words, errors, start)) {
        fprintf(stderr, "Dateien konnten nicht gelesen werden.\n");
    }
    fclose(words);
    fclose(errors);
    return 0;
}
//
// Created by samuel on 05.01.21.
//

#include "library.h"

int readData(FILE *words, FILE *errors, struct word *start) {
    struct word *ptr = start;
    char line[LINE_MAX], *engWord, *gerWord;
    int error = 0;

    //einlesen jeder Zeile aus dem Stream words
    while (fgets(line, LINE_MAX, words)) {
        if (line[0] == '\0' || line[1] == '\0' || line[0] == ';') {
            error++;
        }
        if (error == 0) {
            engWord = strtok(line, ";");
            gerWord = strtok(NULL, "\n");
            if(engWord == NULL || gerWord == NULL || strncmp(engWord, " ", 1) == 0 || strncmp(gerWord, " ", 1) == 0) {
                error++;
            }
        }
        //wenn Fehlerhaft, wird der Fehler in errors geschrieben um Verlust von Vokabeln zu vermeiden
        if (error == 0) {
            if (proofRead(engWord, start) || proofRead(gerWord, start)) {
                error++;
            }
        }
        if (error == 0) {
            if ((ptr->next = addWord(engWord, gerWord, ptr)) == NULL) {
                return 1;
            }
            ptr = ptr->next;
        }else{
            fputs(line, errors);
        }
        error = 0;
    }
    return 0;
}

int saveData(struct word *start) {
    FILE *words = fopen("vocabulary.dat", "w");
    if (words == NULL) {
        fprintf(stderr, "Vokabel-Datei konnte nicht geöffnet werden.\n");
        return 1;
    } else {
        //Vokabeln werden Zeile fuer Zeile in den stream "words" geschrieben
        struct word *ptr = start->next;
        while (ptr != NULL) {
            fprintf(words, "%s;%s\n", ptr->engWord, ptr->gerWord);
            ptr = ptr->next;
        }
    }
    fclose(words);
    printf("Speichern erfolgreich\n");
    return 0;
}

int proofRead(char *word, struct word *ptr) {
    int counter = 0;

    for (int i = 0; i <= strlen(word) - 1; i++) {

        //alphabets pruefung
        if (!(isalpha(word[i]) || word[i] == '\n')) {
            //zaehlt die leerstellen
            if (word[i] == ' ') {
                counter++;
            } else {
                return EXIT_FAILURE;
            }
        }
    }
    if (counter > 1) {
        return EXIT_FAILURE;
    } else {
        while (ptr != NULL) {
            if ((strncmp(word, ptr->engWord, strlen(ptr->engWord)) == 0 ||
                 strncmp(word, ptr->gerWord, strlen(ptr->gerWord)) == 0)) {
                return 2;
            }
            ptr = ptr->next;
        }
        return EXIT_SUCCESS;
    }
}

void viewErrors() {
    FILE *errors = fopen("errors.dat", "r");
    if (errors == NULL) {
        fprintf(stderr, "Fehler-Datei konnte nicht geöffnet werden!\n");
        return;
    }
    char line[LINE_MAX];
    //jede Zeile von errors wird ausgelesen
    while (fgets(line, LINE_MAX, errors)) {
        fputs(line, stderr);
        fflush(stderr);
    }
    printf("\n\n");
    fflush(stdout);
    fclose(errors);
}

void remErrors() {
    FILE *errors = fopen("errors.dat", "w");
    if (errors == NULL) {
        fprintf(stderr, "Fehler-Datei konnte nicht geloescht werden!\n");
        return;
    }
    fclose(errors);
}

void close(struct word *start) {
    struct word *temp = start, *remove;

    //heap speicher wird mit free() freigegeben
    while (temp != NULL) {
        remove = temp;
        temp = temp->next;
        free(remove);
    }
}
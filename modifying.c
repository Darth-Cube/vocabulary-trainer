//
// Created by samuel on 05.01.21.
//

#include "library.h"

struct word *addWord (char *pEngWord, char *pGerWord, struct word *ptr) {
    struct word *newWord = malloc(sizeof(struct word));
    if (newWord == NULL) {
        fprintf(stderr, "Kritischer Fehler!\n");
        return NULL;
    }
    strncpy(newWord->engWord, pEngWord, WORD_LENGTH);
    strncpy(newWord->gerWord, pGerWord, WORD_LENGTH);
    newWord->previous = ptr;
    newWord->next = NULL;
    return newWord;
}

int delWord (char *word, struct word *ptr) {
    while (ptr != NULL) {
        /* die Liste wird nach dem word durchsucht
           falls dieses gefunden wurde, wird der Speicher freigegeben
           und die Pointer der anderen Elemente werden entsprechend veraendert */

        if (strncmp(word, ptr->engWord, strlen(ptr->engWord)) == 0 ||
            strncmp(word, ptr->gerWord, strlen(ptr->gerWord)) == 0){
            //next-Pointer des Elements mit der Adresse "ptr" wird mit dem next-Pointer des vorherigen Elements getauscht
            ptr->previous->next = ptr->next;
            if(ptr->next != NULL) {
                //wenn das Ende nicht bereits erreicht wurde, wird der previous-Pointer vom naechsten Element auch noch getauscht
                ptr->next->previous = ptr->previous;
            }
            free(ptr);

            return 0;
        }else {
            ptr = ptr->next;
        }
    }
    fprintf(stderr, "Wort konnte nicht geloescht oder gefunden werden.\n");
    return 1;
}
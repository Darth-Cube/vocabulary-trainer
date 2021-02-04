//
// Created by samuel on 05.01.21.
//

#ifndef PRAKTIKUM_5_VOKABELTRAINER_LIBRARY_H
#define PRAKTIKUM_5_VOKABELTRAINER_LIBRARY_H

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <ctype.h>

#define LINE_MAX 42
#define WORD_LENGTH 20

struct word {
    char gerWord[WORD_LENGTH];
    char engWord[WORD_LENGTH];
    struct word *next;
    struct word *previous;
};

/**
 * @function initiate ruft die Dateien auf gibt die Streams an readData weiter
 * @return 1 ist ein Fehlercode und sorgt fuer das beenden des Programms
 * @return 0 meldet, dass alles wie vorgesehen funktioniert
 */
int initiate();

/**
 * @function selector ist zur Auswahl der Programmfunktionen
 * @param start ist ein Pointer auf das Erste Element der Liste
 */
void selector(struct word *start);

int getFunction(char *input);

/**
 * @function newWord uebergibt der Funktion addWord eine Nutzereingabe und erstellt damit eine neue Vokabel
 * @param start ist ein Pointer auf das Erste Element der Liste
 */
void newWord(struct word *start);

/**
 * @function delete gibt eine Nutzereingabe an die Funktion delWord und ueberprueft den rueckgabewert von dieser
 * @param start ist ein Pointer auf das Erste Element der Liste
 */
void delete(struct word *start);

/**
 * @function getWord fragt ein Wort als Nutzereingabe ab und speichert dieses beim Pointer 'word' ab
 * @param word ist die Speicheradresse wo die Eingabe hinterlegt wird
 */
int getWord(char *word, struct word *start);

/**
 * @function readData ließt den Inhalt von 'vocabulary.dat' in eine Liste ein und speichert Form-Fehler in 'errors.dat'
 * @param words ist der Dateistream der Vokabel-Datei 'vocabulary.dat'
 * @param errors ist der Dateistream der Fehler-Datei 'errors.dat'
 * @param ptr ist zunaechst ein Pointer auf das Erste Element der Liste
 * @return zeigt einen Fehler beim Objekt in Liste einfuegen an und fuehrt zum beenden des Programms
 */
int readData(FILE *words, FILE *errors, struct word *start);

/**
 * @function saveData speichert die Liste in 'vocabulary.dat'
 * @param start ist ein Pointer auf das Erste Element der Liste
 * @return zeigt an ob das Speichern funktionierte
 */
int saveData(struct word *start);

/**
 * @function proofRead ueberprueft den Parameter auf Fehler wie Zahlen
 * @param word ist das zu ueberpruefende Wort
 * @return zeigt an ob das Wort fehlerfrei war oder nicht
 */
int proofRead(char *word, struct word *ptr);

/**
 * @function viewErrors gibt die Datei 'errors.dat' in der Konsole aus
 */
void viewErrors();

/**
 * @function stop leert den belegten Heap-Speicher
 * @param start ist ein Pointer auf das Erste Element der Liste
 */
void close(struct word *start);

/**
 * @function exercise beinhaltet eine Schleife, die ueberprueft ob der Nutzer weiter hin "ueben" moechte
 * @param start ist ein Pointer auf das Erste Element der Liste
 */
void exercise(struct word *start);

/**
 * @function randomWord sucht ein zufaelliges Element der Liste und vergleicht mit der Benutzereingabe
 * @param start ist ein Pointer auf das Erste Element der Liste
 */
struct word randomWord(struct word *start);

/**
 * @function printEverything gibt die gesamte Liste in der Konsole aus
 * @param start ist ein Pointer auf das Erste Element der Liste
 */
void printEverything(struct word *start);

/**
 * @function getRandomInt gibt eine Zufallszahl in abhaengigkeit von der Anzahl an Elementen in der Liste zurueck
 * @param start ist ein Pointer auf das Erste Element der Liste
 * @return Zufallszahl
 */
int getRandomInt(struct word *start);

int getCountWords(struct word *start);

/**
 * @function addWord fuegt einer Liste eine Vokabel an
 * @param pEngWord Englisches Wort
 * @param pGerWord Deutsches Wort
 * @param ptr Pointer auf letztes Element der Liste
 * @return gibt zurueck ob erstellen Erfolgreich war
 */
struct word *addWord(char *pEngWord, char *pGerWord, struct word *ptr);

/**
 * @function delWord entfernt eine Vokabel anhand eines Wortes
 * @param word Teil der zu loeschenden Vokabel
 * @param ptr Pointer auf das Erste Element der Liste
 * @return gibt zurueck ob das Loeschen erfolgreich war
 */
int delWord(char *word, struct word *ptr);

void remErrors();

void stop(struct word *start);


void reopen(struct word *start);

#endif //PRAKTIKUM_5_VOKABELTRAINER_LIBRARY_H
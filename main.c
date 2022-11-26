#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include <ctype.h>

int checkPasswort(char* passwort){

    int counter = 0;
    for (int j = 0; j < sizeof(passwort); ++j) {
        if(passwort[j]>=97&&passwort[j]<=122){
            counter++;
        }
        else{
            return 0;
        }
    }

    if(counter < 4){
        return 0;
    }

    return 1;
}

int main(int i, char* a[]) {

    //zuerst pfad dann passwort
    char* pfad = a[1];
    char  *passwort= a[2];
    //printf("%s %s",pfad, passwort);

    //Datei finden
    FILE* datei = fopen(pfad, "r");

    //Variablen
    char buffer[1024];
    int iFileSize = ftell(datei);
    char* DateiPuffer = malloc(iFileSize+1);
    char* verschluesseltDatei = malloc(iFileSize+1);
    char c = 0;
    char* pTemp = DateiPuffer;
    int icounter = 0;

    fseek(datei, 0, SEEK_SET);

    //Datei in Variable
    while(c = fgetc(datei)){

        if(97<=c && c<=122){
            *pTemp = c;
            pTemp++;
            icounter++;
        }
        else if(65<=c && c<=90){
            c = tolower(c);
            *pTemp = c;
            pTemp++;
            icounter++;
        }
        else if(c != 32){
            if(c != '\0'){
                break;
            }
            printf("error in datei");
            return 0;
        }
    }

    //Datei schließen
    fclose(datei);

    //check passwort validität
    if(checkPasswort(passwort)==0){
        printf("error passwort");
        return 0;
    }

    //baue Quadrat
    char quadrat[26][26];
    for (int j = 0; j < 26; ++j) {
        for (int k = 0; k < 26; ++k) {
            int temp = 97 + j + k;
            if(temp > 122){
                temp = 97 + (temp - 123);
            }
            quadrat[j][k] = temp;
        }
    }

    //verschlüsselten Text erstellen
    for (int j = 0; j < icounter; ++j) {
        int counter = 0;
        if(counter>sizeof(passwort)){
            counter = 0;
        }
        int tempPasswortAlphabetNr = passwort[counter]-97;
        int tempVerschluesselAlphabetNr = DateiPuffer[j] - 97 ;

        verschluesseltDatei[j] = quadrat[tempPasswortAlphabetNr][tempVerschluesselAlphabetNr];
        counter++;

    }

    //pfad erstellen
    char *newPfad = pfad;
    newPfad[strlen(newPfad)-3]='v';
    newPfad[strlen(newPfad)-2]='i';
    newPfad[strlen(newPfad)-1]='n';

    //neue Datei beschreiben (geht nicht)
    FILE * datei1 = fopen(newPfad,"w");
    fseek(datei1, 0, SEEK_SET);
    for (int j = 0; j < icounter; ++j) {
        //Die Datei wird nicht beschrieben ich weiß nicht warum.
        fputc(verschluesseltDatei[j],datei1);
        printf("%c",verschluesseltDatei[j]);
    }

    //Speicher freigeben , Dateien schließen
    fflush(datei1);
    fclose(datei1);
    free(DateiPuffer);
    free(verschluesseltDatei);





}

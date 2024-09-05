#ifndef SOUNDEX_H
#define SOUNDEX_H

#include "Soundex.h"
#include <ctype.h>
#include <string.h>

char getSoundexCode(char c) {
    c = toupper(c);
    switch (c) {
        case 'B': case 'F': case 'P': case 'V': return '1';
        case 'C': case 'G': case 'J': case 'K': case 'Q': case 'S': case 'X': case 'Z': return '2';
        case 'D': case 'T': return '3';
        case 'L': return '4';
        case 'M': case 'N': return '5';
        case 'R': return '6';
        default: return '0'; // For A, E, I, O, U, H, W, Y
    }
}

void generateSoundex_ReplaceCharacters(const char *name, char *soundex) {
    int len = strlen(name);
    soundex[0] = toupper(name[0]);
    for (int i = 1; i < len; i++) {
        soundex[i] = getSoundexCode(name[i]);
    }
}

void generateSoundex_RemoveVowels(char *soundex) {
    for (int i = 1; i < strlen(soundex); i++) {
     if(soundex[i] == '0') {
        soundex[i] = soundex[i-1];
     }   
    }
}

void generateSoundex_SimplifyAdjacentCharacters(char *soundex) {
    char *tempSoundex = soundex;
    int sIndex = 1;
    // printf("\n%s", soundex);
    for (int i = 1; i < strlen(tempSoundex); i++) {
     if(tempSoundex[i] != tempSoundex[i-1]) {
        soundex[sIndex++] = tempSoundex[i];
        // printf("\n%s", soundex);
     }   
    }
    
    while (sIndex < 4) {
        soundex[sIndex++] = '0';
    }
}

void generateSoundex_AddZeroPadding(char *soundex) {
    int len = strlen(soundex);
    
    while(len < 4) {
        soundex[len] = 0;
        len++;
    }
}

void generateSoundex(const char *name, char *soundex) {
    generateSoundex_ReplaceCharacters(name, soundex);
    // printf(soundex);
    generateSoundex_RemoveVowels(soundex);
    // printf(soundex);
    generateSoundex_SimplifyAdjacentCharacters(soundex);
    // printf(soundex);
    // generateSoundex_AddZeroPadding(soundex);
    // printf(soundex);
    soundex[4] = '\0';
    printf(soundex);
    
}

#endif // SOUNDEX_H

#ifndef SOUNDEX_H
#define SOUNDEX_H

#include "Soundex.h"
#include <ctype.h>
#include <string.h>

void deleteCharFromStringByIndex(char *inputString, int charIndex) {
    int len = strlen(inputString);
    int i;
    for(i = charIndex; i < len-1; ++i) {
        inputString[i] = inputString[i+1];
    }
    inputString[i] = '\0';
}

void generateSoundex_ReplaceCharacters(const char *name, char *soundex) {
    char soundexCode[26] = {'0','1','2','3','0','1','2','*','0','2','2','4','5','5','0','1','2','6','2','3','0','1','*','2','0','2'};
    int len = strlen(name);
    
    for(int i = 0; i < len; ++i) {
        soundex[i] = soundexCode[(toupper(name[i]) - 65)];
    }
    soundex[len] = '\0';
}


void generateSoundex_SimplifyAdjacentCharacters_CheckForHW(char *soundex) {
    int len  = strlen(soundex);
    for (int i = 2; i < len; ++i) {
        if((soundex[i-1] == '*') && (soundex[i] == soundex[i-2])) {
            deleteCharFromStringByIndex(soundex,i);
        }
    }
}

void generateSoundex_SimplifyAdjacentCharacters_CheckForRepeatedCharacters(char *soundex) {
    int len = strlen(soundex);
    
    for (int i = 1; i < len; ++i) {
        if(soundex[i] == soundex[i-1]) {
            deleteCharFromStringByIndex(soundex,i);
        }
    }
}

void generateSoundex_RemoveVowels(char *soundex) {
    int len = strlen(soundex);
    for (int i = 1; i < len; ++i) {
        if((strchr("0*", soundex[i]))) {
            deleteCharFromStringByIndex(soundex,i);
        }
    }
}

void generateSoundex_AddZeroPadding(char *soundex) {
    int len = strlen(soundex);
    while(len < 4) {
        soundex[len++] = '0';
    }
}

void generateSoundex(const char *name, char *soundex) {
    generateSoundex_ReplaceCharacters(name, soundex);
    generateSoundex_SimplifyAdjacentCharacters_CheckForHW(soundex);
    generateSoundex_SimplifyAdjacentCharacters_CheckForRepeatedCharacters(soundex);
    generateSoundex_RemoveVowels(soundex);
    generateSoundex_AddZeroPadding(soundex);
    soundex[0] = toupper(name[0]);
    soundex[4] = '\0';
    
}

#endif // SOUNDEX_H

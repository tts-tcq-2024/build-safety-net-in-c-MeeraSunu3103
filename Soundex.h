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


int compareSubstringForHW(char *soundex, int index) {
    char substr1[4], substr2[4] = "***";
    
    strncpy(substr1,soundex+(index-2),3);
    substr1[3] = '\0';
    
    substr2[0] = soundex[index];
    // substr2[1] = '*';
    substr2[2] = soundex[index];
    // substr2[3] = '\0'
    
    return (!strcmp(substr1, substr2));
}

void generateSoundex_SimplifyAdjacentCharactersSeparatedByHW(char *soundex) {
    int len  = strlen(soundex);
    for (int i = 2; i < len; ++i) {
        if(compareSubstringForHW(soundex,i)) {
            deleteCharFromStringByIndex(soundex,i);
        }
    }
}

void generateSoundex_SimplifyRepeatedAdjacentCharacters(char *soundex) {
    int len = strlen(soundex);
    int i = 1;
    
    while(i < len) {
        if(soundex[i] == soundex[i-1]) {
            deleteCharFromStringByIndex(soundex,i);
            --i;
            --len;
        }
            // printf("\n\t%d : %c : %s",i,soundex[i],soundex);
        ++i;
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
    printf(soundex);
    printf(" - ReplaceCharacters, len: %d\n", strlen(soundex));
    generateSoundex_SimplifyAdjacentCharactersSeparatedByHW(soundex);
    printf(soundex);
    printf(" - SimplifyAdjacentCharactersSeparatedByHW, len: %d\n", strlen(soundex));
    generateSoundex_SimplifyRepeatedAdjacentCharacters(soundex);
    printf(soundex);
    printf(" - SimplifyRepeatedAdjacentCharacters, len: %d\n", strlen(soundex));
    generateSoundex_RemoveVowels(soundex);
    printf(soundex);
    printf(" - RemoveVowels, len: %d\n", strlen(soundex));
    generateSoundex_AddZeroPadding(soundex);
    printf(soundex);
    printf(" - AddZeroPadding, len: %d\n", strlen(soundex));
    soundex[0] = toupper(name[0]);
    soundex[4] = '\0';
    
}

#endif // SOUNDEX_H

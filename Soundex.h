#ifndef SOUNDEX_H
#define SOUNDEX_H

#include "Soundex.h"
#include <ctype.h>
#include <string.h>

/* Function Description: delete the character at the given index from the given string */
void deleteCharFromStringByIndex(char *inputString,    /* string from which a character is to be deleted */
                                    int charIndex) {   /* index of the character which is to be deleted */         
    int len = strlen(inputString); /* len - length of the input string */
    int i;
    for(i = charIndex; i < len-1; ++i) {
        inputString[i] = inputString[i+1];
    }
    inputString[i] = '\0';
}

/* Function Description: replace characters of the input string with their corresponding soundex encoding */
void generateSoundex_ReplaceCharacters(const char *inputString,    /* inputString - input string whose characters are to be replaced */
                                                char *soundex) {   /* soundex - string with soundex code (intermediate) */
    char soundexCode[26] = {'0','1','2','3','0','1','2','*','0','2','2','4','5','5','0','1','2','6','2','3','0','1','*','2','0','2'}; /* soundexCode - soundex encoding of each alphabet, accordin to alphabetical position */
    int len = strlen(inputString); /* len - length of the input string */
    
    for(int i = 0; i < len; ++i) {
        soundex[i] = soundexCode[(toupper(inputString[i]) - 65)];
    }
    soundex[len] = '\0';
}


/* Function Description: checks if the 3-character substring is a string with the same character separated by '*' (which is the encoding for h and w) */
int compareSubstringForHW(char *soundex,    /* soundex - string with soundex code (intermediate) */
                            int index) {    /* index - index of the soundex code to checked for separation by h or w */
    char substr1[4];         /* substr1 - substring from the soundex code */
    char substr2[4] = "***"; /* substr2 - substring in the format [character_at_index][*][character_at_index] */
    
    strncpy(substr1,soundex+(index-2),3);
    substr1[3] = '\0';
    
    substr2[0] = soundex[index];
    substr2[2] = soundex[index];
    
    return (!strcmp(substr1, substr2));
}

/* Function Description: removes adjacent characters that are separated by either 'h' or 'w', if they encode to the same value */
void generateSoundex_SimplifyAdjacentCharactersSeparatedByHW(char *soundex) { /* soundex - string with soundex code (intermediate) */
    int len  = strlen(soundex); /* len - current length of the soundex code */
    for (int i = 2; i < len; ++i) {
        if(compareSubstringForHW(soundex,i)) {
            deleteCharFromStringByIndex(soundex,i);
        }
    }
}

/* Function Description: removes adjacent characters that encode the same value */
void generateSoundex_SimplifyRepeatedAdjacentCharacters(char *soundex) { /* soundex - string with soundex code (intermediate) */
    int len = strlen(soundex); /* len - current length of the soundex code */
    int i = 1;
    
    while(i < len) {
        if(soundex[i] == soundex[i-1]) {
            deleteCharFromStringByIndex(soundex,i);
            --i;
            --len;
        }
        ++i;
    }
}

/* Function Description: removes a,e,i,o,u,y,h,w from the soundex code */
void generateSoundex_RemoveVowels(char *soundex) { /* soundex - string with soundex code (intermediate) */
    int len = strlen(soundex); /* len - current length of the soundex code */
    for (int i = 1; i < len; ++i) {
        if((strchr("0*", soundex[i]))) {
            deleteCharFromStringByIndex(soundex,i);
        }
    }
}

/* Function Description: pads the soundex code with zeros, if it is less than 4 characters */
void generateSoundex_AddZeroPadding(char *soundex) { /* soundex - string with soundex code (intermediate) */
    int len = strlen(soundex); /* len - current length of the soundex code */
    while(len < 4) {
        soundex[len++] = '0';
    }
}

/* Function Description: generates the soundex code for the given input string */
void generateSoundex(const char *inputString,   /* inputString - input string whose soundex code is to be generated */
                            char *soundex) {    /* soundex - string with soundex code */
    generateSoundex_ReplaceCharacters(inputString, soundex);
    generateSoundex_SimplifyAdjacentCharactersSeparatedByHW(soundex);
    generateSoundex_SimplifyRepeatedAdjacentCharacters(soundex);
    generateSoundex_RemoveVowels(soundex);
    generateSoundex_AddZeroPadding(soundex);
    soundex[0] = toupper(inputString[0]);
    soundex[4] = '\0';    
}

#endif // SOUNDEX_H

#ifndef SOUNDEX_H
#define SOUNDEX_H

#include "Soundex.h"
#include <ctype.h>
#include <string.h>

/* Function Prototypes */
void deleteCharFromStringByIndex(char *inputString, int charIndex);
void generateSoundex_ReplaceCharacters(const char *inputString, char *soundex);
int compareSubstringForHW(char *soundex, int index);
void generateSoundex_SimplifyAdjacentCharactersSeparatedByHW(char *soundex);
void generateSoundex_SimplifyRepeatedAdjacentCharacters(char *soundex);
void generateSoundex_RemoveVowels(char *soundex);
void generateSoundex_AddZeroPadding(char *soundex);
void generateSoundex(const char *inputString, char *soundex);


/* Function Description: delete the character at the given index from the given string */
/* Parameters:
      inputString - string from which a character is to be deleted
      charIndex - index of the character which is to be deleted
*/
void deleteCharFromStringByIndex(char *inputString, int charIndex) {        
    int len = strlen(inputString); /* len - length of the input string */
    int i;
    for(i = charIndex; i < len-1; ++i) {
        inputString[i] = inputString[i+1];
    }
    inputString[i] = '\0';
}

/* Function Description: replaces all alphabet characters of the input string with their corresponding soundex encoding and ignores all non-alphabetic characters */
/* Parameters:
      inputString - input string whose characters are to be replaced
      soundex - string with soundex code (intermediate)
*/
void generateSoundex_ReplaceCharacters(const char *inputString, char *soundex) { 
    char soundexCode[26] = {'0','1','2','3','0','1','2','*','0','2','2','4','5','5','0','1','2','6','2','3','0','1','*','2','0','2'}; /* soundexCode - soundex encoding of each alphabet, accordin to alphabetical position */
    int len = strlen(inputString); /* len - length of the input string */
    int sIndex = 0; /* sIndex - index of soundex at which the next code is to be inserted */
    
    for(int i = 0; i < len; ++i) {
        if(isalpha(inputString[i])) {
            soundex[sIndex++] = soundexCode[(toupper(inputString[i]) - 65)];
        }
    }
    soundex[sIndex] = '\0';
}


/* Function Description: checks if the 3-character substring is a string with the same character separated by '*' (which is the encoding for h and w) */
/* Parameters:
      soundex - string with soundex code (intermediate)
      index - index of the soundex code to checked for separation by h or w
*/
int compareSubstringForHW(char *soundex, int index) {
    char substr1[4] = {soundex[index-2],soundex[index-1],soundex[index],'\0'}; /* substr1 - substring from the soundex code */
    char substr2[4] = {soundex[index],'*',soundex[index],'\0'}; /* substr2 - substring in the format [character_at_index][*][character_at_index] */
    return (!strcmp(substr1, substr2));
}

/* Function Description: removes adjacent characters that are separated by either 'h' or 'w', if they encode to the same value */
/* Parameters:
      soundex - string with soundex code (intermediate)
*/
void generateSoundex_SimplifyAdjacentCharactersSeparatedByHW(char *soundex) {
    int len  = strlen(soundex); /* len - current length of the soundex code */
    for (int i = 2; i < len; ++i) {
        if(compareSubstringForHW(soundex,i)) {
            deleteCharFromStringByIndex(soundex,i);
        }
    }
}

/* Function Description: removes adjacent characters that encode the same value */
/* Parameters:
      soundex - string with soundex code (intermediate)
*/
void generateSoundex_SimplifyRepeatedAdjacentCharacters(char *soundex) {
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
/* Parameters:
      soundex - string with soundex code (intermediate)
*/
void generateSoundex_RemoveVowels(char *soundex) {
    int len = strlen(soundex); /* len - current length of the soundex code */
    for (int i = 1; i < len; ++i) {
        if((strchr("0*", soundex[i]))) {
            deleteCharFromStringByIndex(soundex,i);
        }
    }
}

/* Function Description: pads the soundex code with zeros, if it is less than 4 characters */
/* Parameters:
      soundex - string with soundex code (intermediate)
*/
void generateSoundex_AddZeroPadding(char *soundex) {
    int len = strlen(soundex); /* len - current length of the soundex code */
    while(len < 4) {
        soundex[len++] = '0';
    }
}

/* Function Description: generates the soundex code for the given input string */
/* Parameters:
      inputString - input string whose soundex code is to be generated
      soundex - string with soundex code (intermediate)
*/
void generateSoundex(const char *inputString, char *soundex) {
    generateSoundex_ReplaceCharacters(inputString, soundex);
    generateSoundex_SimplifyAdjacentCharactersSeparatedByHW(soundex);
    generateSoundex_SimplifyRepeatedAdjacentCharacters(soundex);
    generateSoundex_RemoveVowels(soundex);
    generateSoundex_AddZeroPadding(soundex);
    soundex[0] = toupper(inputString[0]);
    soundex[4] = '\0';    
}

#endif // SOUNDEX_H

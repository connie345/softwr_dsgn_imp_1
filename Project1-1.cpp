/*
 * Project1.cpp
 *
 * Name: Ima Student
 * EE312 Summer 2020
 * SuperStrings
 */

// SuperStrings <Project1.cpp>
// EE 312 Project <n> submission by
// Connie Wang
// cw39276
// Slip days used: <0>
// Spring 2021// Copy-paste contents of this file at the top of every .c or .h file that you write or modi

#include <stdio.h> // provides declarations for printf and putchar
#include <stdint.h> // provides declarations for int32_t uint32_t and the other (new) standard C types

#define ONE_MB (1 << 20)
#define BUFFER_SIZE ONE_MB
/*
All of your code must be in this file. Please no #includes other than standard system headers (ie.., stdio.h, stdint.h)

You must write this function (printSuperStrings). Do not change the way the function is declared (i.e., it has
exactly two parameters, each parameter is a standard (mundane) C string (see Instruction).
*/

/*
 * check if char is a letter
 * input: char
 * output: 1 if char is letter; 0 if not
 */
int isLetter(char c){
    if((c >= 'a' && c <= 'z')|| (c >= 'A' && c <= 'Z')){    //if c is a letter
        return 1;                                           //return 1
    }
    else {return 0;}                                        //else return 0
}
/*
 * print out the superstring when found
 * input: char array
 */
void matchfound(char print[]){
    int i = 0;

    while(print[i] != '\0'){                                //if yet to hit null
        printf("%c", print[i]);                             //print characters
        ++i;
    }
    printf("\n");
}
/*
 * find matches between string and superstring
 * input: char array of singular word from target strings, char array of superstring candidates
 */
void match(char toPrint[], char candidates[]){
    int c = 0, t =0, p =0;
    char print[BUFFER_SIZE];                             //to save a match

    while (candidates[c] != '\0'){                       //until end of candidates array
        if(isLetter(candidates[c]) == 1){                //if the candidate is a letter
            if(candidates[c] == toPrint[t]){             //test if the letter is a match to target
                ++t;                                     //if so then move up the target array
            }
            print[p] = candidates[c];                    //regardless save the letter from candidates to print
            ++p;
        }
        else{                                             //if not a letter
            if (toPrint[t] == '\0'){                      //check if target array has moved to null meaning that a match was found
                print[p] = '\0';                          //if match was found then save a null to signal end
                matchfound(print);                        //then print

            }
            p = 0;                                         //regardless of match found set p and t to 0 to restart
            t = 0;
        }
        ++c;                                                //always increment candidates array
    }
}

/*
 * find and print superstrings
 */
void printSuperStrings(char target [], char candidates []){
    int p = 0, t =0;
    char toPrint[BUFFER_SIZE];                          //to save a word

    while(target[t] != '\0'){                           //until end of target array
        if(isLetter(target[t]) == 1){                   //if target is a letter
            toPrint[p] = target[t];                     //save the letter
            ++p;
        }
        else{
            toPrint[p] = '\0';                          //if not a letter means that word was found and save a null to signify that
            match(toPrint, candidates);                 //send the word to be matched with candidates
            p = 0;
        }
        ++t;
    }
    // edge case
    if(toPrint[p-1] != '\0') {                          //test for edge case
        toPrint[p] = '\0';                               //if found run edgecase
        match(toPrint, candidates);
    }
}

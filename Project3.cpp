// String ADT <Project3.cpp>
// EE 312 Project 3 submission by
// Connie Wang
// cw39276
// Slip days used: <1>
// Spring 2021
// Copy and paste this file at the top of all your submitted source code files.  Do not turn this in by itself.

#include <stdio.h>
#include <assert.h>
#include <stdbool.h>
#include <stdlib.h>
#include <stdint.h>
#include <string.h>
#include "UTString.h"

/*
 * Helper macro to find the signature of a UTString
 * Treat this like a function that takes a UTString*
 * Accesses a uint32_t from where the signature should be located
 */
#define CHECK(s) (*(uint32_t*) ((s)->string + (s)->length + 1))

/*
 * Checks if a UTString is valid or not.
 */
int isOurs(const UTString* s) {
    if (CHECK(s) == SIGNATURE) { return 1; }
    else { return 0; }
}

void checkValid(UTString* s){
    (isOurs(s));   
   ///////////////////////////                           //Creates redundancy by checking in two different ways
}

/*
 * Allocate a utstring on the heap.
 * Initialize the string correctly by copying src.
 * Return a pointer to the UTString.
 */
UTString* utstrdup(const char* src) {

    UTString* str = (UTString*)malloc(sizeof(UTString) + strlen(src) + 2);
    str->length = strlen(src);
    str->capacity = strlen(src);
    str->string= (char*) malloc(strlen(src));
    for(int i = 0; i<strlen(src); i++){
        str->string[i] = src[i];
    }

    str->string[strlen(src)] = 0 ;
    return str;
}

/*
 * Returns the length of s.
 *  s must be a valid UTString.
 */
uint32_t utstrlen(const UTString* s) {
    uint32_t length;
    isOurs( s);      //Make sure 0xdeadbeef check is in string ptr
    UTString* str =(UTString*)s;
    length = str->length;
    return length ;
}

/*
 * Append the string suffix to the UTString s.
 *  s must be a valid UTString.
 * Do not allocate any additional storage: only append as many characters
 *  as will actually fit in s.
 * Update the length of s.
 * Return s with the above changes. */
UTString* utstrcat(UTString* s, const char* suffix) {
    checkValid(s);
    UTString* str = s;
    uint32_t length = strlen(suffix);		            //src length
    uint32_t dlength = str->length;		                //dst length
    assert(dlength == str->length);	                    //assure s length actually correct

    if (length > (str->capacity - dlength)) {
        int x = 0;
        for (int i = dlength; i < str->capacity ; i++) {
            str->string[i] = suffix[x];	                //add suffix data in utstring
            x++;
        }
        str->length = str->capacity;		            //fix s length
        str->string[str->capacity] = 0;		            //null term.
    }
    else {
        int j = 0;
        for (int i = dlength; i <= dlength + length; i++) {
            str->string[i] = suffix[j];		            //add suffix data in utstring
            j++;
        }
        str->length = dlength + length;		        //update length of dest
    }
    return s;
    return s;
}

/*
 * Copy src into dst.
 *  dst must be a valid UTString.
 *  src is an ordinary string.
 * Do not allocate any additional storage: only copy as many characters
 *  as will actually fit in dst.
 * Update the length of dst.
 * Return dst with the above changes.
 */
UTString* utstrcpy(UTString* dst, const char* src) {
    checkValid(dst);
    UTString* str = dst;
    uint32_t length;
    uint32_t dlength;
    length = strlen(src);		                        //src string length
    dlength = str->length;	                            //dst string length
    assert(dlength == dst->length);		                //check dst length, same as above
    if (length > str->capacity) {
        for (int i = 0; i < str->capacity; i++) {
            str->string[i] = src[i];
        }
        str->string[str->capacity] = 0;		    //null term.
        str->length = str->capacity;		    //fix dlength
    }
    else {
        for (int i = 0; i <= length; i++) {
            str->string[i] = src[i];
        }
        str->length = length;
    }
    return dst;
}

/*
 * Free all memory associated with the given UTString.
 */
void utstrfree(UTString* self) {
    checkValid(self);
    free(self->string);
    free(self) ;	
   // free(self);	
}

/*
 * Make s have at least as much capacity as new_capacity.
 *  s must be a valid UTString.
 * If s has enough capacity already, do nothing.
 * If s does not have enough capacity, then allocate enough capacity,
 *  copy the old string and the null terminator, free the old string,
 *  and update all relevant metadata.
 * Return s with the above changes.
 */
UTString* utstrrealloc(UTString* s, uint32_t new_capacity) {
    checkValid(s);
    UTString* str = s;
    char* retStr;
    if (str->capacity >= new_capacity) {
        return s;
    }
    else {
        UTString* newStr = (UTString*)malloc(sizeof(UTString) + new_capacity + 1);		//alloc space
        newStr->capacity = new_capacity;		        //chang length and capacity for string
     newStr->string= (char*) malloc(s->length);   
     newStr->length = s->length;

        for (int i = 0; i < newStr->length; i++) {
            newStr->string[i] = s->string[i];		                //copying chars from s to new str_data
//         printf("in loop\n");
        }
        newStr->string[newStr->length] = 0;	            //add null term
        retStr = newStr->string;		                    //return new str
        utstrfree(s);		                            //free up start str
        return newStr;
    }
}

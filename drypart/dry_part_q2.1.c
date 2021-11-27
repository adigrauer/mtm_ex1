//q2.1
//q2.1.1

#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include <stdio.h>

/*char *stringduplicator(char *s, int times){  //convention1   //convention2
    assert(!s);    //coding1
    assert(times > 0);
    int LEN = strlen(*s);   //coding2   //convention3  
    char *out = malloc(LEN * times);    //coding3
    assert(out);    //coding4
    for (int i = 0; i < times; i++) {  
    out = out + LEN;    //convention4
    strcpy(out, s);
    }
    return out;   //coding5
}*/

//conventions errors-
//convention1- function name should start with upper lettter from the second word and on.
//convention2- wording function names as verbs, not action names.
//convention3- variables names in lower case and not upper case.
//convention4- no indentation is used in if block. 

//coding erroes-
//coding1- if the string s isn't NULL we sholud continue the program running and not collapse the program. 
//coding2- strlen function input is pointer. using dereferance to a pointer sends to strlen valuse instead of pointer.
//coding3- no memory allocation was made for '/0' at the end of the new srting, and need to duplicate sizeof(len) because the allocation is of bits.
//coding4- assert check if out is NULL. if the string out is NULL we sholud return NULL and not collapse the program. 
//coding5- out is not a pointer for the start of the string beacuse we promoted out pointer in the loop instead of promoting coopy of the pointer. 

//q2.1.2
//Fixed version of the above code
char *duplicateTheString(char *s, int times)
{    
    if(s == NULL)
        return NULL;   
    assert(times > 0);
    int len = strlen(s);  
    char *out = malloc(sizeof(len) * times + 1 );    
    if (out == NULL)
        return NULL;    
    char *out_copy = out; 
    for (int i = 0; i < times; i++) 
    {
        strcpy(out_copy, s);
        out_copy = out_copy + len;  
    }
    return out;   
}

int main()
{
    char* string= "h";
    int times= 2;
    char* duplication = duplicateTheString(string, times);
    printf("%s", duplication);
    return 0;
}

//need to check if string=NULL case is working correctly

#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include "amount_set_str_tests.h"
#include "amount_set_str.h"

bool test1() // this test is to check return values in NULL cases
{
    printf("Test_1");
    bool check=true;
    if (asCopy(NULL) != NULL) {
        printf("Test 1 Failed at check_point 1\n");
        check=false;
    }
    if (asGetSize(NULL) != -1) {
        printf("Test 1 Failed at check_point 2\n");
        check=false;
    }
    if (asContains(NULL, "test") != false) {
        printf("Test 1 Failed at check_point 3\n");
        check=false;
    }
    double x = 0;
    if (asGetAmount(NULL, "test", &x) != AS_NULL_ARGUMENT) {
        printf("Test 1 Failed at check_point 4\n");
        check=false;
    }
    if (asRegister(NULL, "test") != AS_NULL_ARGUMENT){
        printf("Test 1 Failed at check_point 5\n");
        check=false;
    }
    if (asChangeAmount(NULL, "test", 10) != AS_NULL_ARGUMENT) {
        printf("Test 1 Failed at check_point 6\n");
        check=false;
    }
    if (asDelete(NULL, "test")!=AS_NULL_ARGUMENT) {
        printf("Test 1 Failed at check_point 7\n");
        check=false;
    }
    if (asClear(NULL) != AS_NULL_ARGUMENT) {
        printf("Test 1 Failed at check_point 8\n");
        check=false;
    }
    if (asGetFirst(NULL) != NULL){
        printf("Test 1 Failed at check_point 9\n");
        check=false;
    }
    if (asGetNext(NULL) != NULL){
        printf("Test 1 Failed at check_point 10\n");
        check=false;
    }
    if(check==false){
        return false;
    }
    return true;
}

bool test2()
{
    printf("Test_2");
    AmountSet Set2 = asCreate();
    bool check=true;
    const char* name = NULL;
    if(asRegister(Set2,name) != AS_NULL_ARGUMENT){
        printf("Test 2 Failed at check_point 1\n");
        check=false;
    }
    if(asRegister(Set2, "adi") != AS_SUCCESS){
        printf("Test 2 Failed at check_point 2\n");
        check=false;
    }
    if(asRegister(Set2, "gili") != AS_SUCCESS){
        printf("Test 2 Failed at check_point 3\n");
        check=false;
    }
    if(asRegister(Set2,"lior") != AS_SUCCESS){
        printf("Test 2 Failed at check_point 4\n");
        check=false;
    }
    if(strcmp(asGetFirst(Set2),"adi")!=0){
        printf("Test 2 Failed at check_point 5\n");
        check=false;
    }
    if(strcmp(asGetNext(Set2),"gili")!=0){
        printf("Test 2 Failed at check_point 6\n");
        check=false;
    }
    if(strcmp(asGetNext(Set2),"lior")!=0){
        printf("Test 2 Failed at check_point 7\n");
        check=false;
    }
    if(asGetNext(Set2)!=NULL){
        printf("Test 2 Failed at check_point 8\n");
        check=false;
    }
    if(asDelete(Set2, "adi") != AS_SUCCESS){
        printf("Test 2 Failed at check_point 9\n");
        check=false;
    }
    if(asDelete(Set2, "adi") != AS_ITEM_DOES_NOT_EXIST){
        printf("Test 2 Failed at check_point 10\n");
        check=false;
    }
    if(strcmp(asGetFirst(Set2),"gili")!=0){
        printf("Test 2 Failed at check_point 11\n");
        check=false;
    }
    if(asRegister(Set2, "einat") !=AS_SUCCESS){
        printf("Test 2 Failed at check_point 12\n");
        check=false;
    }
    if(asGetSize(Set2)!=3)
    {
        printf("Test 2 Failed at check_point 13\n");
        check=false;
    }
    if(asChangeAmount(Set2,"einat",5)!=AS_SUCCESS)
    {
        printf("Test 2 Failed at check_point 14\n");
        check=false;
    }
    if(asChangeAmount(Set2,"gili",10)!=AS_SUCCESS)
    {
        printf("Test 2 Failed at check_point 15\n");
        check=false;
    }
    double x=0;
    if(asGetAmount(Set2,"einat",&x)!=AS_SUCCESS)
    {
        printf("Test 2 Failed at check_point 16\n");
        check=false;
    }
    if(x!=5)
    {
        printf("Test 2 Failed at check_point 17\n");
        check=false;
    }
    if(asGetAmount(Set2,"gili",&x)!=AS_SUCCESS)
    {
        printf("Test 2 Failed at check_point 18\n");
        check=false;
    }
    if(x!=10)
    {
        printf("Test 2 Failed at check_point 19\n");
        check=false;
    }
    if(asChangeAmount(Set2,"einat",-7)!=AS_INSUFFICIENT_AMOUNT)
    {
        printf("Test 2 Failed at check_point 20\n");
        check=false;
    }
    if(asChangeAmount(Set2,"ofer",-7)!=AS_ITEM_DOES_NOT_EXIST)
    {
        printf("Test 2 Failed at check_point 21\n");
        check=false;
    }
    if(asRegister(Set2,"nadav") !=AS_SUCCESS){
        printf("Test 2 Failed at check_point 22\n");
        check=false;
    }
    if(asGetSize(Set2)!=4)
    {
        printf("Test 2 Failed at check_point 23\n");
        check=false;
    }
    AmountSet CopySet2 = asCopy(Set2); 
    if(CopySet2==NULL)
    {
        asDestroy(Set2);
        printf("Test 2 Failed at check_point 24\n");
        check=false;
    }  
    if(asRegister(CopySet2, "amit") !=AS_SUCCESS){
        printf("Test 2 Failed at check_point 25\n");
        check=false;
    }
    if(strcmp(asGetFirst(CopySet2),"amit")!=0){
        printf("Test 2 Failed at check_point 26\n");
        check=false;
    }
    if(strcmp(asGetNext(CopySet2),"einat")!=0){
        printf("Test 2 Failed at check_point 27\n");
        check=false;
    }
    if(asChangeAmount(CopySet2,"gili",-11)!=AS_INSUFFICIENT_AMOUNT)
    {
        printf("Test 2 Failed at check_point 28\n");
        check=false;
    }
    if(asChangeAmount(CopySet2,"gili",-5)!=AS_SUCCESS)
    {
        printf("Test 2 Failed at check_point 29\n");
        check=false;
    }
    if(asGetAmount(CopySet2,"gili",&x)!=AS_SUCCESS)
    {
        printf("Test 2 Failed at check_point 30\n");
        check=false;
    }
    if(x!=5)
    {
        printf("Test 2 Failed at check_point 31\n");
        check=false;
    }
    if(asDelete(CopySet2, "einat") != AS_SUCCESS){
        printf("Test 2 Failed at check_point 30\n");
        check=false;
    }
    if(asDelete(CopySet2, "einat") != AS_ITEM_DOES_NOT_EXIST){
        printf("Test 2 Failed at check_point 32\n");
        check=false;
    }
    if(asGetSize(CopySet2)!=4)
    {
        printf("Test 2 Failed at check_point 33\n");
        check=false;
    }
    asDestroy(Set2);
    asDestroy(CopySet2);
    if(check==false){
        return false;
    }
    return true;
}


bool test3()
{
    printf("Test_3");
    AmountSet set3 = asCreate();
    bool check=true;
    if(asRegister(set3, "banana")!=AS_SUCCESS)
    {
        printf("Test 3 Failed at check_point 1\n");
        check=false;
    }
    if(asRegister(set3, "banana")!=AS_ITEM_ALREADY_EXISTS)
    {
        printf("Test 3 Failed at check_point 2\n");
        check=false;
    }
    if(asRegister(set3, "apple")!=AS_SUCCESS)
    {
        printf("Test 3 Failed at check_point 3\n");
        check=false;
    }
    if (asGetSize(set3) != 2)
    {
        printf("Test 3 Failed at check_point 4\n");
        check=false;
    }
    if (asDelete(set3, "carrot") != AS_ITEM_DOES_NOT_EXIST){
        printf("Test 3 Failed at check_point 5\n");
        check=false;
    }
    if (asDelete(set3, "apple") != AS_SUCCESS){
        printf("Test 3 Failed at check_point 6\n");
        check=false;
    }
    AmountSet set3_copy = asCopy(set3);
    if(asGetSize(set3) != 1 || asGetSize(set3_copy) != 1)
    {
        printf("Test 3 Failed at check_point 7\n");
        check=false;
    }
    double x= 200.92;
    if(asChangeAmount(set3_copy, "banana", x) != AS_SUCCESS) 
    {
        printf("Test 3 Failed at check_point 8\n");
        check=false;  
    } 
    if (asGetAmount(set3_copy, "banana", &x) != AS_SUCCESS) 
    {
        printf("Test 3 Failed at check_point 9\n");
        check=false;
    }
    if (x != 200.92) 
    {
        printf("Test 3 Failed at check_point 10\n");
        check=false;
    }
    if (asClear(set3) != AS_SUCCESS)
    {
        printf("Test 3 Failed at check_point 11\n");
        check=false;
    }
    if (asRegister (set3, "carrot") != AS_SUCCESS) 
    {
        printf("Test 3 Failed at check_point 12\n");
        check=false;
    }
    if (asRegister (set3, "banana") != AS_SUCCESS) 
    {
        printf("Test 3 Failed at check_point 13\n");
        check=false;
    }
    if (strcmp((asGetFirst(set3)),(asGetFirst(set3_copy))) !=0)
    {
        printf("Test 3 Failed at check_point 14\n");
        check=false;
    }
    asDestroy(set3);
    asDestroy(set3_copy);
    if(check==false){
        return false;
    }
    return true;
    
}

bool test4()
{
    printf("Test_4");
    AmountSet set4 = asCreate();
    AmountSet set4_copy = NULL;
    bool check=true;
    if(asRegister(set4, "A")!=AS_SUCCESS)
    {
        printf("Test 4 Failed at check_point 1\n");
        check=false;
    }
    if(asRegister(set4, "A")!=AS_ITEM_ALREADY_EXISTS) 
    {
        printf("Test 4 Failed at check_point 2\n");
        check=false;
    }
    if(asRegister(set4, "C")!=AS_SUCCESS)
    {
        printf("Test 4 Failed at check_point 3\n");
        check=false;
    }
    if (asGetSize(set4_copy) != -1)
    {
        printf("Test 4 Failed at check_point 4\n");
        check=false;
    }
    if (asGetAmount(set4, "A", NULL) != AS_NULL_ARGUMENT) {
        printf("Test 4 Failed at check_point 5\n");
        check=false;
    }
    double x = 0;
    if (asGetAmount(set4, "test", &x) != AS_ITEM_DOES_NOT_EXIST) {
        printf("Test 4 Failed at check_point 5\n");
        check=false;
    }
    asDestroy(set4);
    asDestroy(set4_copy);
    if(check==false){
        return false;
    }
    return true;
}


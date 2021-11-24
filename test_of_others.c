#include <stdio.h>
#include <stdbool.h>
#include "amount_set_str.h"

void test1()
{
    printf("***************Test_1***************\n");
    AmountSet Set1 = asCreate();
    bool check=true;
    if(asRegister(Set1,"Madrid") != AS_SUCCESS){
        printf("Test 1 Failed at check_point 1\n");
        check=false;
    }
    if(strcmp(asGetFirst(Set1),"Madrid")!=0){
        printf("Test 1 Failed at check_point 2\n");
        check=false;
    }
    if(asRegister(Set1, "Madrid") != AS_ITEM_ALREADY_EXISTS){
        printf("Test 1 Failed at check_point 3\n");
        check=false;
    }
    if(asRegister(Set1, "yones") != AS_SUCCESS){
        printf("Test 1 Failed at check_point 4\n");
        check=false;
    }
    if(strcmp(asGetNext(Set1),"yones")!=0){
        printf("Test 1 Failed at check_point 5\n");
        check=false;
    }

    if(asRegister(Set1, "omran") != AS_SUCCESS){
        printf("Test 1 Failed at check_point 6\n");
        check=false;
    }
    if(asDelete(Set1, "omran") != AS_SUCCESS){
        printf("Test 1 Failed at check_point 7 \n");
    }
    if(asRegister(Set1, "omran") !=AS_SUCCESS){
        printf("Test 1 Failed at check_point 8\n");
        check=false;
    }
    if(asChangeAmount(Set1,"omran",18.57)!=AS_SUCCESS)
    {
        printf("Test 1 Failed at check_point 9\n");
        check=false;
    }
    double x=0;
    if(asGetAmount(Set1,"omran",&x)!=AS_SUCCESS)
    {
        printf("Test 1 Failed at check_point 10\n");
        check=false;
    }
    if(x!=18.57)
    {
        printf("Test 1 Failed at check_point 11\n");
        check=false;
    }
    if(asRegister(Set1, "N") !=AS_SUCCESS){
        printf("Test 1 Failed at check_point 12\n");
        check=false;
    }

    if(asGetSize(Set1)!=4)
    {
        printf("Test 1 Failed at check_point 13\n");
        check=false;
    }
    

    AmountSet CopySet = asCopy(Set1); //leak memory
    if(CopySet==NULL)
    {
        asDestroy(Set1);
        printf("Test 1 Failed at check_point 14\n");
        check=false;
    }
    
    if(asRegister(CopySet, "yones") !=AS_ITEM_ALREADY_EXISTS){
        printf("Test 1 Failed at check_point 15\n");
        check=false;
    }
    if(asDelete(CopySet, "yones") !=AS_SUCCESS){
        printf("Test 1 Failed at check_point 16\n");
        check=false;
    }
    if(asDelete(CopySet, "yones") !=AS_ITEM_DOES_NOT_EXIST){
        printf("Test 1 Failed at check_point 17\n");
        check=false;
    }
    if(asRegister(CopySet, "Yuval") !=AS_SUCCESS){
        printf("Test 1 Failed at check_point 18\n");
        check=false;
    }
    if(asRegister(CopySet, "Kane") !=AS_SUCCESS){
        printf("Test 1 Failed at check_point 19\n");
        check=false;
    }

    if(asGetSize(CopySet)!=5)
    {
        printf("Test 1 Failed at check_point 20\n");
        check=false;
    }


    asDestroy(Set1);
    asDestroy(CopySet);

    if(check==false){
        printf("\n**************Test 1 failed************\n");
        //return false;
    }
    if(check==true){
        printf("\n**************Test 1 passed************\n");
        //return true;
    }
}

void test2()
{
    printf("***************Test_2***************\n");
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
 
    AmountSet CopySet2 = asCopy(Set2); //leak memory here!
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
    if(asDelete(CopySet2, "einat") !=AS_SUCCESS){
        printf("Test 2 Failed at check_point 30\n");
        check=false;
    }
    if(asDelete(CopySet2, "einat") !=AS_ITEM_DOES_NOT_EXIST){
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
        printf("\n**************Test 2 failed************\n");
        //return false;
    }
    if(check==true){
        printf("\n**************Test 2 passed************\n");
        //return true;
    }
}

int main()
{
    test2();
    test1();
    return 0;
}

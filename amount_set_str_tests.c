#include "amount_set_str.h"
#include "amount_set_str_tests.h"
#include <stdbool.h>
#include <stdlib.h>
/*
//tests for asCreate
bool test_asCreate_1()
{
    AmountSet new_set = asCreate();
    if (asGetFirst(new_set) == NULL || getNextNodeOfSetAmount(new_set) == NULL){
        asDestroy(new_set);
        return true;
    }
}

//tests for strcmp
bool test_strcmp_1()
{
    char* str1= "adi";
    char* str2= "adii";
    if(strcmp(str1, str2) >= 0)
        return false; 
}

bool test_strcmp_2()
{
    char* str1= "";
    char* str2= "adi";
    if(strcmp(str1, str2) >= 0)
        return false; 
}

bool test_strcmp_3()
{
    char* str1= "adz";
    char* str2= "adi";
    if(strcmp(str1, str2) <= 0)
        return false; 
}

//test for strLen
bool test_strlen_1()
{
    const char* str = "adi"; 
    if(strLength(str) == 3)
        return true;
}

bool test_strlen_2()
{
    const char* str = ""; 
    if(strLength(str) == 0)
        return true;
}

//tests for copyString
bool test_copyString_1()
{
    char* str = "adi"; 
    char* str_tmp = copyString(str);
    if (strcmp(str, str_tmp) == 0){
        free(str_tmp);
        return true;
    }
    
}

bool test_copyString_2()
{
    char* str = NULL; 
    char* str_tmp = copyString(str);
    if (str_tmp == NULL){
        free(str_tmp);
        return true;
    }
}

bool test_copyString_3()
{
    char* str = NULL; 
    char* str_tmp = copyString(str);
    if (str_tmp == NULL){
        free(str_tmp);
        return true;
    }
}

//test for createNode
bool test_createNode_1()
{
    char* name = "adi";
    Node node= createNode(name);
    const char* description = getNodeDescriptionPointer(node);
    if (strcmp(description, name) == 0){
        return true;
    }
}

bool test_createNode_2()
{
    char* name = "";
    Node node= createNode(name);
    if (node == NULL){
        return true;
    }
}

bool test_createNode_3()
{
    char* name = '\0';
    Node node= createNode(name);
    if (node == NULL){
        return true;
    }
}

bool test_createNode_4()
{
    char* name = "nodeeeee";
    Node node= createNode(name);
    const char* description = getNodeDescriptionPointer(node);
    if (strcmp(description, name) == 0){
        return true;
    }
}

bool test_cheackForIndexRegister_1()
{
    const char* element = "";
    AmountSet set = asCreate();
    if (cheackForIndexRegister(set, element) == getNextNodeOfSetAmount(set)){
        asDestroy(set);
        return true;
    }
}

need to check cases when set contain nodes after checking add node function 
bool test_cheackForIndexRegister_2()
{
}

//tests for asRegister
bool test_asRegister_1()
{
    const char* element = NULL;
    AmountSet set = asCreate();
    if (asRegister(set, element) == AS_NULL_ARGUMENT){
        asDestroy(set);
        return true;
    }
}


bool test_asRegister_2()
{
    const char* element = "adi";
    AmountSet set = asCreate();
    if (asRegister(set, element) == AS_SUCCESS){
        asDestroy(set);
        return true;
    }
}

bool test_asRegister_3()
{
    const char* element = "adi";
    AmountSet set = asCreate();
    if (asRegister(set, element) == AS_SUCCESS){
        if (strcmp(element, asGetFirst(set)) == 0){
            asDestroy(set);
            return true;
        }
    }
}

bool test_asRegister_4()
{
    const char* element1 = "adi";
    const char* element2 = "grauer";
    AmountSet set = asCreate();
    if (asRegister(set, element1) == AS_SUCCESS){
        if (asRegister(set, element2) == AS_SUCCESS){
            asDestroy(set);
            return true;
        }
    }
}

bool test_asRegister_5()
{
    const char* element1 = "adi";
    const char* element2 = "grauer";
    AmountSet set = asCreate();
    if (asRegister(set, element1) == AS_SUCCESS && asRegister(set, element2) == AS_SUCCESS){
        const char* element3 = "adi";
        const char* element4 = "grauer";
        if (asRegister(set, element3) == AS_ITEM_ALREADY_EXISTS && asRegister(set,element4) == AS_ITEM_ALREADY_EXISTS){
            asDestroy(set);
            return true;
        }
    }
}

bool test_asRegister_6()
{
    const char* element1 = "adi";
    const char* element2 = "grauer";
    AmountSet set = asCreate();
    if (asRegister(set, element1) == AS_SUCCESS && asRegister(set, element2) == AS_SUCCESS){
        const char* element3 = '\0';
        const char* element4 = "bar";
        Node node = getNextNodeOfSetAmount(set);
        node = getNextNodeOfNode(node);
        if (asRegister(set, element3) == AS_NULL_ARGUMENT && asRegister(set, element4) == AS_SUCCESS && strcmp(element4, getNodeDescriptionPointer(node)) == 0){
            asDestroy(set);
            return true;
        }
    }
}

//tests for changeAmount
bool test_changeAmount_1()
{
    const char* element1 = "adi";
    double amount = 3;
    AmountSet set = asCreate();
    if(asRegister(set, element1) == AS_SUCCESS){
        Node node = getNextNodeOfSetAmount(set);
        if(asChangeAmount(set, element1, amount) != AS_NULL_ARGUMENT && getNodeItemAmountPointer(node) == 3){
            asDestroy(set);
            return true;
        }
    }
}

bool test_changeAmount_2()
{
    const char* element1 = "adi";
    const char* element2 = "grauer";
    double amount = 3;
    AmountSet set = asCreate();
    if(asRegister(set, element1) == AS_SUCCESS){
        Node node = getNextNodeOfSetAmount(set);
        if(asChangeAmount(set, element2, amount) == AS_ITEM_DOES_NOT_EXIST){
            asDestroy(set);
            return true;
        }
    }
}

bool test_changeAmount_3()
{
    const char* element1 = "adi";
    const char* element2 = "grauer";
    double amount = 3;
    AmountSet set = asCreate();
    if(asRegister(set, element1) == AS_SUCCESS){
        Node node = getNextNodeOfSetAmount(set);
        if(asChangeAmount(set, element1, amount) == AS_ITEM_DOES_NOT_EXIST){
            amount = -3;
            if(asChangeAmount(set, element2, amount) == AS_SUCCESS){
                amount = -1;
                if(asChangeAmount(set, element2, amount) == AS_INSUFFICIENT_AMOUNT){
                    asDestroy(set);
                    return true;
                }
            }
        }
    }
}
//tests for asClear
bool test_asClear_1()
{
    const char* element1 = "adi";
    const char* element2 = "grauer";
    AmountSet set = asCreate();
    if(asRegister(set, element1) == AS_SUCCESS && asRegister(set, element1) == AS_SUCCESS){
        if(asClear(set) == AS_SUCCESS && strcmp(asGetFirst(set),NULL)==0 && strcmp(asGetNext(set),NULL)==0){
            asDestroy(set);
            return true;
        }
    }
}


//tests for asDelete
bool test_asDelete_1()
{
    const char* element1 = "adi";
    const char* element2 = "grauer";
    double amount = 3;
    AmountSet set = asCreate();
    if(asRegister(set, element1) == AS_SUCCESS){
        Node node = getNextNodeOfSetAmount(set);
        const char* element3 = "home";
        if(asDelete(set, element3) == AS_ITEM_DOES_NOT_EXIST){
            if(asDelete(set, element1) == AS_SUCCESS && strcmp(getNodeDescriptionPointer(node), element2) == 0){
                if(asRegister(set, element3) == AS_SUCCESS){
                    if(asDelete(set, element3) == AS_SUCCESS){
                        asDestroy(set);
                        return true;
                    }
                }
            }
        }
    }
}

//tests for asGetFirst
bool test_asGetFirst_1(){
    const char* element1 = "adi";
    const char* element2 = "grauer";
    AmountSet set = asCreate();
    if(asRegister(set, element1) == AS_SUCCESS && asRegister(set, element2) == AS_SUCCESS){
        if(strcmp(asGetFirst(set), element1) == 0){
            if(asDelete(set, element1) == AS_SUCCESS && strcmp(asGetFirst(set), element2) == 0){
                if(asDelete(set, element1) == AS_SUCCESS && asGetFirst(set) == NULL){
                    asDestroy(set);
                    return true;
                }
            }
        }
    }
}

//tests for asGetNext
bool test_asGetNext_1()
{
    const char* element1 = "adi";
    const char* element2 = "grauer";
    AmountSet set = asCreate();
    if(asGetNext(set) == NULL){
        if(asRegister(set, element1) == AS_SUCCESS && asRegister(set, element2) == AS_SUCCESS){
            if(strcmp(asGetNext(set), element1) == 0){
                if(strcmp(asGetNext(set), element2) == 0){
                    if(asGetNext(set) == NULL){
                        asDestroy(set);
                        return true;
                    }
                }
            }
        }
    }
}


int main()
{
    RUN_TEST(test_asCreate_1);
    RUN_TEST( test_strcmp_1);
    RUN_TEST( test_strcmp_2);
    RUN_TEST( test_strcmp_3);
    RUN_TEST(test_strlen_1);
    RUN_TEST(test_strlen_2);
    RUN_TEST(test_copyString_1);
    RUN_TEST(test_copyString_2);
    RUN_TEST(test_copyString_3);
    RUN_TEST(test_createNode_1);
    RUN_TEST(test_createNode_2);
    RUN_TEST(test_createNode_3);
    RUN_TEST(test_createNode_4);
    RUN_TEST(test_cheackForIndexRegister_1);
    RUN_TEST(test_asRegister_1);
    RUN_TEST(test_asRegister_2);
    RUN_TEST(test_asRegister_3);
    RUN_TEST(test_asRegister_4);
    RUN_TEST(test_asRegister_5);
    RUN_TEST(test_asRegister_6);
    RUN_TEST(test_changeAmount_1);
    RUN_TEST(test_changeAmount_2);
    RUN_TEST(test_changeAmount_3);
    RUN_TEST(test_asClear_1);
    RUN_TEST(test_asDelete_1);
    RUN_TEST(test_asGetFirst_1);
    RUN_TEST(test_asGetNext_1);
    return 0;
}
*/
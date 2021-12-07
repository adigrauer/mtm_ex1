#include "amount_set_str.h"
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>
#include <string.h>

/* struct declaration */
////////////////////////////////////////////
struct Node_t {
    char* description;
    double item_amount;
    struct Node_t* next;
};

struct AmountSet_t {
    struct Node_t* current_element;
    struct Node_t* next;
};
////////////////////////////////////////////

/* static functions declaration */
////////////////////////////////////////////
//int strcmp(const char *str1, const char *str2);
//static int strLength(const char* element);
//static char* copyString(const char* element);
static Node createNode(char* element);
static Node cheackForIndexRegister(AmountSet set, const char* element);
////////////////////////////////////////////

/* static functions implementation */
////////////////////////////////////////////
static Node createNode(char* element)
{
    if (element == NULL){
        return NULL;
    }
    Node new_node = (Node)malloc(sizeof(*new_node));  
    if (new_node == NULL)
    {
         return NULL;
    }
    new_node->next = NULL;
    new_node->description = element;
    new_node->item_amount = 0;
    return new_node;
}

static Node cheackForIndexRegister(AmountSet set, const char* element)
{
    assert(element != NULL && set != NULL && set->next != NULL); //the function add node only if not emty or has one node
    Node ptr = set->next;
    while(strcmp(ptr->description, element) < 0 && ptr->next != NULL && strcmp( ptr->next->description, element) < 0){
        ptr = ptr->next;
    }
    return ptr;
}
////////////////////////////////////////////

/* header functions implementation */
////////////////////////////////////////////
AmountSet asCreate() 
{
    AmountSet set = (AmountSet)malloc(sizeof(*set));  
    if (set == NULL){
        return NULL;
    }
    set->next = NULL;
    set->current_element = NULL;
    return set;
}

void asDestroy(AmountSet set)
{
    if(set == NULL){
        return;
    }
    asClear(set); 
    free(set); 
}

AmountSet asCopy(AmountSet set)
{ 
    if (set == NULL) {
        return NULL;
    }
    int size = asGetSize(set);
    AmountSet new_set = asCreate();
    if (new_set == NULL) {
        return NULL;
    }
    if(size == 0){
        return new_set;
    }
    Node temp_old_ptr = set->next;
    double temp_amount = 0; 
    while(temp_old_ptr != NULL){
        if(asRegister(new_set, temp_old_ptr->description) != AS_SUCCESS){
            asDestroy(new_set);
            return NULL;
        }
        if(asGetAmount(set, temp_old_ptr->description ,&temp_amount) != AS_SUCCESS){
            asDestroy(new_set);
            return NULL;
        }
        if(asChangeAmount(new_set, temp_old_ptr->description, temp_amount) != AS_SUCCESS){
            asDestroy(new_set);
            return NULL;
        }
        temp_old_ptr = temp_old_ptr->next;
    }
    return new_set;
}

int asGetSize(AmountSet set)
{ 
    if (set == NULL){
        return -1;
    }
    int size = 0;
    if (set->next == NULL){
        return size;
    }
    Node ptr = set->next;
    assert(ptr != NULL);
    size++;
    while (ptr->next != NULL){ 
        size++;
        ptr = ptr->next;
    }
    return size;
}

bool asContains(AmountSet set, const char* element)
{ 
    if (set == NULL || element == NULL || set->next == NULL) {
        return false;
    }
    Node ptr = set->next;
    assert(ptr != NULL);
    while (ptr != NULL) {
        if((strcmp(element, ptr->description)) == 0){
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

AmountSetResult asGetAmount(AmountSet set, const char* element, double* outAmount)
{
    if(set == NULL || element == NULL || outAmount == NULL){
        return AS_NULL_ARGUMENT;
    }
    if(asContains(set,element) == false || set->next == NULL){
        return AS_ITEM_DOES_NOT_EXIST;
    }
    Node ptr = set->next;
    while(ptr != NULL && strcmp(ptr->description, element) != 0 ){
        ptr = ptr->next;
    }
    assert(ptr != NULL);
    *outAmount = ptr->item_amount;
    return AS_SUCCESS;
}

AmountSetResult asRegister(AmountSet set, const char* element)
{
    if(element == NULL || set == NULL){
        return AS_NULL_ARGUMENT;
    }
    if(asContains(set, element) == true){
        return AS_ITEM_ALREADY_EXISTS;
    }
    char* new_element = malloc(strlen(element)+1);
    if(new_element == NULL){
        return AS_OUT_OF_MEMORY;
    }
    strcpy(new_element, element);
    Node new_node = createNode(new_element);
    if(new_node == NULL){
        free(new_element);
        return AS_OUT_OF_MEMORY;
    }
    if((asGetSize(set) == 0 || strcmp(set->next->description, element) > 0)){ //set is empty or new node is the smallest one so shoud be add to the start of the list
        Node temp_next_original_pointer = set->next; 
        set->next= new_node;
        new_node->next= temp_next_original_pointer;
        return AS_SUCCESS;
    }
    Node index = cheackForIndexRegister(set, element);
    Node temp_next_original_pointer = index->next; //covers the case of adding new node to the end of the list
    index->next= new_node;
    new_node->next= temp_next_original_pointer;
    return AS_SUCCESS;
}

AmountSetResult asChangeAmount(AmountSet set, const char* element, double amount)
{
    if(set == NULL || element == NULL){
        return AS_NULL_ARGUMENT;
    }
    if(asContains(set, element) == false){
        return AS_ITEM_DOES_NOT_EXIST;
    }
    if(asGetSize(set) == 1 || strcmp(set->next->description, element) == 0){
        if (set->next->item_amount + amount < 0){
            return AS_INSUFFICIENT_AMOUNT;
        }
        set->next->item_amount = set->next->item_amount + amount;
        return AS_SUCCESS;
    }
    Node index_before_the_element = cheackForIndexRegister(set, element);
    Node index_of_the_element = index_before_the_element->next;
    if(index_of_the_element->item_amount + amount < 0)
        return AS_INSUFFICIENT_AMOUNT;
    index_of_the_element->item_amount = index_of_the_element->item_amount + amount;
    return AS_SUCCESS;
}

AmountSetResult asDelete(AmountSet set, const char* element)
{
    if(set == NULL || element == NULL){
        return AS_NULL_ARGUMENT;
    }
    if(asContains(set, element) == false){
        return AS_ITEM_DOES_NOT_EXIST;
    }
    Node next_index = NULL;
    if(strcmp(set->next->description, element) == 0){ //the first node contains the element
       free(set->next->description);
       next_index = set->next->next;
       free(set->next);
       set->next = next_index;
       return AS_SUCCESS;
    }
    Node index_before_the_element = cheackForIndexRegister(set, element);
    assert(index_before_the_element != NULL);
    Node index_of_the_element = index_before_the_element->next;
    assert(index_of_the_element != NULL);
    free(index_of_the_element->description);
    next_index = index_of_the_element->next;
    free(index_of_the_element);
    index_before_the_element->next = next_index;
    return AS_SUCCESS;
}

AmountSetResult asClear(AmountSet set)
{
    if(set == NULL){
        return AS_NULL_ARGUMENT;
    }
    Node ptr = set->next;
    Node ptr_tmp = ptr;
    if(ptr == NULL)
        return AS_SUCCESS;
    while(ptr != NULL){
        free(ptr->description); /////?
        ptr_tmp= ptr;
        ptr = ptr->next;
        free(ptr_tmp);
    }
    set->next= NULL;
    return AS_SUCCESS;
}

char* asGetFirst(AmountSet set)
{
    if(set == NULL || set->next == NULL){
        return NULL;
    }
    set->current_element = set->next;
    return set->current_element->description;
}

char* asGetNext(AmountSet set)
{
    if(set == NULL || set->next == NULL){
        return NULL;
    }
    set->current_element = set->current_element->next;
    if(set->current_element != NULL){
        return set->current_element->description;
    }
    return NULL;
}


    



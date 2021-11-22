#include "amount_set_str.h"
#include "amount_set_str_tests.h"
#include <stdlib.h>
#include <stdlib.h>
#include <stdbool.h>
#include <assert.h>

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
static int strcmp(const char *str1, const char *str2);
static int strLength(const char* element);
static char* copyString(const char* element);
static Node createNode(const char* element);
static Node cheackForIndexRegister(AmountSet set, const char* element);
////////////////////////////////////////////

/* static functions implementation */
////////////////////////////////////////////
static int strcmp(const char *str1, const char *str2)
{
     while (*str1 && (*str1 == *str2)){
        str1++;
        str2++;
    }
    return *(const unsigned char*)str1 - *(const unsigned char*)str2;
}

static int strLength(const char* element)
{
    assert(element != NULL);
    int count = 0;
    const char* ptr = element;
    while(*ptr != '\0'){
        count++;
        ptr++;
    }
    return count;
}

static char* copyString(const char* element)
{
    if (element == NULL){
        return NULL;
    }
    char* new_string = (char*)malloc(strLength(element)+1);
    if (new_string == NULL){
        return NULL;
    }
    assert(new_string != NULL && element != NULL);
    char *temp = new_string;
    while(*element != '\0'){
        *new_string++ = *element++;
    } 
    return temp;
}

static Node createNode(const char* element)
{
    Node new_node = (Node)malloc(sizeof(*new_node));  
    if (new_node == NULL)
    {
         return NULL;
    }
    return new_node;
}

static Node cheackForIndexRegister(AmountSet set, const char* element)
{
    assert(element != NULL && set != NULL);
    Node ptr = set->next;
    while(strcmp(ptr->description, element) < 0 && strcmp( ptr->next->description, element) < 0 && ptr->next != NULL)
    {
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
    if (set == NULL)
    {
        return NULL;
    }
    set->next = NULL;
    set->current_element = NULL;
    return set;
}

void asDestroy(AmountSet set){
    if(set == NULL) {
        return;
    }
    asClear(set);
    free(set);
}

AmountSet asCopy(AmountSet set){ 
    if (set == NULL) {
        return NULL;
    }
    int size = asGetSize(set);
    AmountSet new_set = asCreate();
    if (new_set == NULL) {
        return NULL;
    }
    new_set->next= set->next;
    new_set->current_element = set->current_element;
    if (size == 0)
        return new_set;
    assert(set->next != NULL);
    Node temp_old_ptr = set->next;
    Node temp_new_ptr = new_set->next;
    for (int i = 0; i < size; i++){
        char* temp_description = copyString(temp_old_ptr->description);
        temp_new_ptr->description = temp_description;
        temp_new_ptr->item_amount = temp_old_ptr->item_amount;
        temp_new_ptr->next = temp_old_ptr->next;
        temp_new_ptr = temp_new_ptr->next;
        temp_old_ptr = temp_old_ptr->next;
    }
    return new_set;
}

int asGetSize(AmountSet set) { 
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
    while (ptr->next != NULL) {
        size++;
        ptr = ptr->next;
    }
    return size;
}

bool asContains(AmountSet set, const char* element){ 
    if (set == NULL || element == NULL) {
        return false;
    }
    if (set->next == NULL){
        return false;
    }
    Node ptr = set->next;
    assert(ptr != NULL);
    while (ptr->next != NULL) {
        if ((strcmp (element, ptr->description)) == 0){
            return true;
        }
        ptr = ptr->next;
    }
    return false;
}

AmountSetResult asGetAmount(AmountSet set, const char* element, double* outAmount){
    if (set == NULL || outAmount == NULL || element == NULL){
        return AS_NULL_ARGUMENT;
    }
    if (asContains(set,element) == false){
        return AS_ITEM_DOES_NOT_EXIST;
    }
    Node ptr = set->next;
    while ((strcmp(ptr->description, element) != 0 )){
        ptr = ptr->next;
    }
    assert(ptr != NULL);
    *outAmount = ptr->item_amount;
    return AS_SUCCESS;
}

AmountSetResult asRegister(AmountSet set, const char* element)
{
    if(set == NULL || element == NULL) 
        return AS_NULL_ARGUMENT;
    if(asContains(set, element) == false) //do i need to change parameters?
        return AS_ITEM_ALREADY_EXISTS;
    Node index = cheackForIndexRegister (set, element);
    assert(index != NULL);
    const char* new_element = copyString(element);
    if(new_element == NULL){
        return AS_OUT_OF_MEMORY;
    }
    Node new_node = createNode(new_element);
    if(new_node == NULL){
        return AS_OUT_OF_MEMORY;
    }
    if((asGetSize(set) == 0 || strcmp(set->next->description, element) > 0)){ //set is empty or new node is the smallest one so shoud be add to the start of the list
        Node temp_next_original_pointer = set->next; 
        set->next= new_node;
        new_node->next= temp_next_original_pointer;
        return AS_SUCCESS;
    }
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
    Node index_before_the_element = cheackForIndexRegister(set, element);
    if(index_before_the_element == NULL){
        return AS_OUT_OF_MEMORY;
    }
    Node index_of_the_element = index_before_the_element->next;
    assert(index_of_the_element != NULL);
    if (index_of_the_element->item_amount - amount < 0)
        return AS_INSUFFICIENT_AMOUNT;
    index_of_the_element->item_amount= index_of_the_element->item_amount - amount;
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

}

char* asGetFirst(AmountSet set)
{
    if(set == NULL || set->next == NULL){
        return NULL;
    }
    set->current_element = set->next;
    return set->current_element->description;
}

//should return to that function
char* asGetNext(AmountSet set)
{
    if(set == NULL || set->next == NULL){
        return NULL;
    }
    set->current_element = set->current_element->next;
    return set->current_element->description;
}




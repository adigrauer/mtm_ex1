#include "set.h"
#include "amount_set.h"
//#include "matamikya.h"
#include "orders.h"
#include <stdlib.h>
#include <string.h>

//structs implementation 
/////////////////////////////////////////////////
//set orders element
struct order_information_t {
    unsigned int order_id;
    AmountSet list_items_in_order; //its elements will be int*- the id product
};
/////////////////////////////////////////////////


//functions for SingleItemInOrder
/////////////////////////////////////////////////
ASElement copySingleItemInOrder(ASElement item_id)
{
    if(item_id == NULL){
        return NULL;
    }
    int* new_id = malloc(sizeof(int));  //malloc!!!! need to free 1
    if(new_id == NULL){
        return NULL;
    }
    *new_id = *(int*)item_id;
    return (ASElement)new_id;
}

ASElement freeSingleleItemInOrder(ASElement item_id)
{
    if(item_id == NULL){
        return NULL;
    }
    free(item_id);  //free 1
}

int compareItemInOrder(ASElement item_id_1, ASElement item_id_2) //can be written withour malloc
{
    return (*(int*)item_id_1) - (*(int*)item_id_2);
}
/////////////////////////////////////////////////


//functions for OrdersInformation
/////////////////////////////////////////////////
SetElement copyOrder(SetElement order)
{
    if(order == NULL){
        return NULL;
    }
    OrderInformation new_order = malloc(sizeof(*new_order));   //malloc!!!! need to free 2
    if (new_order == NULL){
        return NULL;
    }
    new_order->order_id = ((OrderInformation)order)->order_id;
    new_order->list_items_in_order = asCopy(((OrderInformation)order)->list_items_in_order); //how copy know the functions of the element int* of items? //the list can be null
    return (SetElement)new_order;
}

SetElement freeOrder(SetElement order)
{
    if(order == NULL){
        return NULL;
    }
    asDestroy(((OrderInformation)order)->list_items_in_order);  //free 1
    free(order);    //free 2
}

int compareOrder(SetElement order_1, SetElement order_2)
{
    return ((OrderInformation)order_1)->order_id - ((OrderInformation)order_1)->order_id;
}
/////////////////////////////////////////////////


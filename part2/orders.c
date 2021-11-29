#include "set.h"
#include "amount_set.h"
#include "orders.h"
#include "util.h"
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

//structs implementation 
/////////////////////////////////////////////////
//set orders element
struct order_information_t {
    unsigned int order_id;
    AmountSet list_items_in_order; //its elements will be int*- the id product
};
/////////////////////////////////////////////////

//functions for amountset SingleItemInOrder
/////////////////////////////////////////////////
ASElement copySingleItemInOrder(ASElement item_id)
{
    RETURN_VALUE_IF_TRUE(item_id, NULL); 
    unsigned int* copy_id = malloc(sizeof(int));    //nalloc!!! need to free 1
    RETURN_VALUE_IF_TRUE(copy_id, NULL); 
    *copy_id = *(unsigned int*)item_id;
    return (ASElement)copy_id;
}

void freeSingleleItemInOrder(ASElement item_id)
{
    if(item_id == NULL){
        return;
    }
    free(item_id);  //free 1
}

int compareSingleItemInOrder(ASElement item_id_1, ASElement item_id_2) //can be written withour malloc
{
    return (*(unsigned int*)item_id_1) - (*(unsigned int*)item_id_2);
}
/////////////////////////////////////////////////


//functions for set OrdersInformation
/////////////////////////////////////////////////
SetElement copyOrder(SetElement order)
{
    RETURN_VALUE_IF_TRUE(order, NULL);
    OrderInformation new_order = malloc(sizeof(*new_order));   //malloc!!!! need to free 2
    RETURN_VALUE_IF_TRUE(new_order, NULL);
    new_order->order_id = ((OrderInformation)order)->order_id;
    new_order->list_items_in_order = asCopy(((OrderInformation)order)->list_items_in_order); //how copy know the functions of the element int* of items? //the list can be null
    if(new_order->list_items_in_order == NULL){
        free(new_order);
        return NULL;
    }
    return (SetElement)new_order;
}

void freeOrder(SetElement order)
{
    if(order == NULL){
        return;
    }
    asDestroy(((OrderInformation)order)->list_items_in_order);  //free 1
    free(order);    //free 2
}

int compareOrder(SetElement order_1, SetElement order_2)
{
    return ((OrderInformation)order_1)->order_id - ((OrderInformation)order_1)->order_id;
}
/////////////////////////////////////////////////


//functions for orders set
/////////////////////////////////////////////////
OrderInformation createNewEmptyOrder(const unsigned int order_id) 
{
    OrderInformation new_order = malloc(sizeof(*new_order));   //malloc!!!! need to free 3, will be free by function freeOrder
    RETURN_VALUE_IF_TRUE(new_order, NULL);
    new_order->order_id = order_id;
    new_order->list_items_in_order = asCreate(copySingleItemInOrder, freeSingleleItemInOrder, compareSingleItemInOrder);
    if(new_order->list_items_in_order == NULL){
        free(new_order); //free 3 in case of error
        return NULL;
    }
    return new_order;
}

bool checkIfOrderExistById(Set orders, const unsigned int order_id)
{
    if(orders == NULL){
        return false;
    }
    OrderInformation temp_order = createNewEmptyOrder(order_id);    //malloc!!!! need to free 6
    if(setIsIn(orders, (SetElement)temp_order) == false){
        freeOrder(temp_order);   //free 6
        return false;
    }
    freeOrder(temp_order); 
    return true;
}

AmountSet findSpecificOrderInOrders(Set orders, const unsigned int order_id)
{
    OrderInformation temp_order = createNewEmptyOrder(order_id);   //malloc!!!! need to free 8
    RETURN_VALUE_IF_TRUE(temp_order, NULL);
    OrderInformation ptr = setGetFirst(orders);
    while (ptr != NULL){
        if(compareOrder((SetElement)ptr, (SetElement)temp_order) == 0){
            freeOrder(temp_order); 
            return ptr->list_items_in_order;
        }
        ptr = setGetNext(orders);
    }
    freeOrder(temp_order); 
    return NULL;
}
/////////////////////////////////////////////////

//functions for items in order amount set
/////////////////////////////////////////////////
AmountSetResult changeAmountOfItemInOrder(AmountSet list_item_in_order, const unsigned int product_id, const double amount) //use this function only if can change the amount according to the instructions
{
    unsigned int* temp_item_id = createNewIdForItemInOrder(product_id);  //malloc!!!! need to free 5
    AmountSetResult result = asChangeAmount(list_item_in_order, (ASElement)temp_item_id, amount);
    free(temp_item_id);
    return result;
}

unsigned int* createNewIdForItemInOrder(const unsigned int product_id)
{
    unsigned int* new_product_id = malloc(sizeof(int));
    RETURN_VALUE_IF_TRUE(new_product_id, NULL);
    *new_product_id = product_id;
    return new_product_id;
}

bool checkIfItemExistInOrderById(AmountSet list_items_in_order, const unsigned int product_id)
{
    if(list_items_in_order == NULL){
        return false;
    }
    unsigned int* temp_item_id = createNewIdForItemInOrder(product_id);
    if(asContains(list_items_in_order, (SetElement)temp_item_id) == false){
        free(temp_item_id);
        return false;
    }
    free(temp_item_id);
    return true;
}

////////////////////////////////////////////////

//max free right now is 7!!!!!!!!!!


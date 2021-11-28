#include "set.h"
#include "amount_set.h"
//#include "matamikya.h"
#include "orders.h"
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

void freeSingleleItemInOrder(ASElement item_id)
{
    if(item_id == NULL){
        return;
    }
    free(item_id);  //free 1
}

int compareSingleItemInOrder(ASElement item_id_1, ASElement item_id_2) //can be written withour malloc
{
    return (*(int*)item_id_1) - (*(int*)item_id_2);
}
/////////////////////////////////////////////////


//functions for set OrdersInformation
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
unsigned int selectIdForNewOrder(Set orders) //does the set is classified???????
{
    OrderInformation ptr = setGetFirst(orders);
    if (ptr == NULL){
        return 1;   //orders is empty that the next order will be the first
    }
    while(ptr != NULL){
        ptr = setGetNext(orders);
    }
    return ptr->order_id + 1;
}

OrderInformation createNewEmptyOrder(const unsigned int order_id) //the id will be from the function selectIdForNewOrder(Set orders)
{
    OrderInformation new_order = malloc(sizeof(*new_order));   //malloc!!!! need to free 3, will be free by function freeOrder
    if (new_order == NULL){
        return NULL;
    }
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
    if(setIsIn(orders, temp_order) == false){
        setDestroy(temp_order->list_items_in_order);
        free(temp_order);   //free 6
        return false;
    }
    setDestroy(temp_order->list_items_in_order);
    free(temp_order);
    return true;
}

AmountSet findSpecificOrderInOrders (Set orders, const unsigned int order_id)
{
    OrderInformation temp_order = malloc(sizeof(*temp_order));   //malloc!!!! need to free 8
    if (temp_order == NULL){
        return NULL;
    }
    temp_order->order_id = order_id;
    temp_order->list_items_in_order = NULL;
    OrderInformation ptr = setGetFirst(orders);
    while (ptr != NULL){
        if(compareOrder(ptr, temp_order) == 0){
            free(temp_order);
            return ptr->list_items_in_order;
        }
        ptr = setGetNext(orders);
    }
    free(temp_order);
    return NULL;
}
/////////////////////////////////////////////////

//functions for items in order amount set
/////////////////////////////////////////////////
AmountSetResult changeAmountOfItemInOrder(AmountSet list_item_in_order, const unsigned int product_id, const double amount) //use this function only if can change the amount according to the instructions
{
    int* item_id = malloc(sizeof(int));  //malloc!!!! need to free 5
    if(item_id == NULL){
        return AS_OUT_OF_MEMORY;
    }
    *item_id = product_id;
    AmountSetResult result = asChangeAmount(list_item_in_order, item_id, amount);
    free(item_id);
    return result;
}

int* createNewIdForItemInOrder(const unsigned int product_id)
{
    int* new_product_id = malloc(sizeof(int));  //malloc!!!! need to free 4, will be free by function freeSingleleItemInOrder
    if(new_product_id == NULL){
        return NULL;
    }
    *new_product_id = product_id;
    return new_product_id;
}

bool checkIfItemExistInOrderById(AmountSet list_items_in_order, const unsigned int product_id)
{
    if(list_items_in_order == NULL){
        return false;
    }
    int* temp_item_id = createNewIdForItemInOrder(product_id);  //malloc!!!! need to free 7
    if(asContains(list_items_in_order, temp_item_id) == false){
        free(temp_item_id);
        return false;
    }
    free(temp_item_id); //free 7
    return true;
}

////////////////////////////////////////////////

//max free right now is 7!!!!!!!!!!


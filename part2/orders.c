#include "set.h"
#include "amount_set.h"
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
    double total_price;
};
/////////////////////////////////////////////////

//functions for amountset SingleItemInOrder
/////////////////////////////////////////////////
ASElement copySingleItemInOrder (ASElement item_id)
{
    if(item_id == NULL){
        return NULL;
    }
    unsigned int* copy_id = (unsigned int*)malloc(sizeof(int));    //nalloc!!! need to free 1
    if(copy_id == NULL){
        return NULL;
    }
    *copy_id = *(unsigned int*)item_id;
    return (ASElement)copy_id;
}

void freeSingleleItemInOrder (ASElement item_id)
{
    if(item_id == NULL){
        return;
    }
    free(item_id);  //free 1
}

int compareSingleItemInOrder (ASElement item_id_1, ASElement item_id_2) //can be written withour malloc
{
    return (*(unsigned int*)item_id_1) - (*(unsigned int*)item_id_2);
}
/////////////////////////////////////////////////


//functions for set OrdersInformation
/////////////////////////////////////////////////
SetElement copyOrder (SetElement order)
{
    if(order == NULL){
        return NULL;
    }
    OrderInformation new_order = (OrderInformation)malloc(sizeof(*new_order));   //malloc!!!! need to free 2
    if(new_order == NULL){
        return NULL;
    }
    new_order->order_id = ((OrderInformation)order)->order_id;
    new_order->total_price = ((OrderInformation)order)->total_price;
    new_order->list_items_in_order = asCopy(((OrderInformation)order)->list_items_in_order); //how copy know the functions of the element int* of items? //the list can be null
    if(new_order->list_items_in_order == NULL){
        free(new_order);
        return NULL;
    }
    return (SetElement)new_order;
}

void freeOrder (SetElement order)
{
    if(order == NULL){
        return;
    }
    asDestroy(((OrderInformation)order)->list_items_in_order);  //free 1
    free(order);    //free 2
}

int compareOrder (SetElement order_1, SetElement order_2)
{
    return (((OrderInformation)order_1)->order_id) - (((OrderInformation)order_2)->order_id);
}
/////////////////////////////////////////////////


//functions for orders set
/////////////////////////////////////////////////
OrderInformation createNewEmptyOrder (const unsigned int order_id) 
{
    OrderInformation new_order = (OrderInformation)malloc(sizeof(*new_order));   //malloc!!!! need to free 3, will be free by function freeOrder
    if(new_order == NULL){
        return NULL;
    }
    new_order->order_id = order_id;
    new_order->total_price = 0;
    new_order->list_items_in_order = asCreate(copySingleItemInOrder, freeSingleleItemInOrder, compareSingleItemInOrder);
    if(new_order->list_items_in_order == NULL){
        free(new_order); //free 3 in case of error
        return NULL;
    }
    return new_order;
}

bool checkIfOrderExistById (Set orders, const unsigned int order_id)
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

AmountSet GetListOfItemsInSpecificOrder (Set orders, const unsigned int order_id)
{
    OrderInformation temp_order = createNewEmptyOrder(order_id);   //malloc!!!! need to free 8
    if(temp_order == NULL){
        return NULL;
    }
    OrderInformation ptr = (OrderInformation)setGetFirst(orders);
    while (ptr != NULL){
        if(compareOrder((SetElement)ptr, (SetElement)temp_order) == 0){
            freeOrder(temp_order); 
            return ptr->list_items_in_order;
        }
        ptr = (OrderInformation)setGetNext(orders);
    }
    freeOrder(temp_order); 
    return NULL;
}

OrderInformation findSpecificOrderInOrders (Set orders, const unsigned int order_id)
{
    OrderInformation temp_order = createNewEmptyOrder(order_id);   //malloc!!!! need to free 8
    if(temp_order == NULL){
        return NULL;
    }
    OrderInformation ptr = (OrderInformation)setGetFirst(orders);
    while (ptr != NULL){
        if(compareOrder((SetElement)ptr, (SetElement)temp_order) == 0){
            freeOrder(temp_order); 
            return ptr;
        }
        ptr = (OrderInformation)setGetNext(orders);
    }
    freeOrder(temp_order); 
    return NULL;
}

void clearProductFromAllOrders (Set orders, const unsigned id) 
{
    OrderInformation ptr_order = (OrderInformation)setGetFirst(orders);
    if (ptr_order == NULL) {
        return;
    }
    unsigned int* ptr_item;
    while (ptr_order != NULL) {
        if(checkIfItemExistInOrderById(ptr_order->list_items_in_order, id) == true){
            ptr_item = findSpecificItemInOrders(ptr_order->list_items_in_order, id);
            asDelete(ptr_order->list_items_in_order, (ASElement)ptr_item);
            //do we need to delete an empty order???
        }
        ptr_order = (OrderInformation)setGetNext(orders);
    }
}

int getOrderId (OrderInformation order)
{
    return order->order_id;
}

void changeTotalPriceInOrder (OrderInformation order, double price_to_add)
{
    order->total_price += price_to_add;
}

double getTotalPriceForOrder (OrderInformation order)
{
    return order->total_price;
}
/////////////////////////////////////////////////

//functions for items in order amount set
/////////////////////////////////////////////////
unsigned int* createNewIdForItemInOrder (const unsigned int product_id)
{
    unsigned int* new_product_id = (unsigned int*)malloc(sizeof(int));
    if(new_product_id == NULL){
        return NULL;
    }
    *new_product_id = product_id;
    return new_product_id;
}

bool checkIfItemExistInOrderById (AmountSet list_items_in_order, const unsigned int product_id)
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

unsigned int* findSpecificItemInOrders (AmountSet order, const unsigned int product_id)
{
    unsigned int* temp_item = createNewIdForItemInOrder(product_id);   //malloc!!!! need to free 8
    if(temp_item == NULL){
        return NULL;
    }
    unsigned int* ptr = (unsigned int*)asGetFirst(order);
    while (ptr != NULL){
        if(compareSingleItemInOrder((ASElement)ptr, (ASElement)temp_item) == 0){
            freeSingleleItemInOrder(temp_item); 
            return ptr;
        }
        ptr = (unsigned int*)asGetNext(order);
    }
    freeSingleleItemInOrder(temp_item); 
    return NULL;
}

unsigned int* getMinIdItemInOrder (AmountSet order)
{
    unsigned int* ptr = (unsigned int*)asGetFirst(order); //ptr != NULL, useing this function only in case the order isnt empty
    unsigned int* ptr_current_min = ptr;
    unsigned int current_min_id_item = *ptr;
    while (ptr != NULL) {
        if(*ptr < current_min_id_item){
            current_min_id_item = *ptr;
            ptr_current_min = ptr;
        }
        ptr = (unsigned int*)asGetNext(order);
    }
    return ptr_current_min;
}

unsigned int* getNextMinimalItemInOrderById (AmountSet order, Product last_printed_product) 

/*
Product getNextMinimalProductById (AmountSet storage, Product last_printed_product) 
{
    Product ptr = (Product)asGetFirst(storage);
    int current_min_id = 0;
    Product current_min_id_product = NULL;
    while (ptr != NULL){
        if (ptr->product_id <= last_printed_product->product_id){
            ptr = (Product)asGetNext(storage);
            continue;
        }
        if (current_min_id != 0) {
            if (ptr->product_id < current_min_id){
                current_min_id = ptr->product_id;
                current_min_id_product = ptr;
                ptr = (Product)asGetNext(storage);
                continue;
            }
        }
        else {
            current_min_id = ptr->product_id;
                current_min_id_product = ptr;
        } 
        ptr = (Product)asGetNext(storage);
    }
    if (current_min_id == last_printed_product-> product_id) {
        return NULL;
    }
    return current_min_id_product;
}
*/
////////////////////////////////////////////////




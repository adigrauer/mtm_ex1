#ifndef ORDERS_H
#define ORDERS_H
#include "amount_set.h"
#include "set.h"
#include "amount_set.h"

//typedef for structs
typedef struct order_information_t *OrderInformation;
typedef struct single_item_in_order *SingleItemInOrder;

//functions for using generic ADT set for restoring oreders
SetElement copyOrder(SetElement order);
void freeOrder(SetElement order);
int compareOrder(SetElement order_1, SetElement order_2);

//functions for using generic ADT amount set for restoring items in oreder
ASElement copySingleItemInOrder (ASElement item_id);
void freeSingleleItemInOrder (ASElement item_id);
int compareItemInOrder (ASElement item_id_1, ASElement item_id_2);

////////////////////////functions for orders set

/* chose unsigned int for the next id of new order.
return values- if set orders is empty the function will return 1 for the first order in set orders,
otherwise the function will return the maxmial id order+1 */
unsigned int selectIdForNewOrder(Set orders);

/* create new order element for set orders.
return value- if allocation was failed return NULL,
otherwise return new OrderInformation */
OrderInformation createNewEmptyOrder(const unsigned int order_id);

/* get order id and cheack if the order id exit in the set of orders
return value- false if the order id do not exit and true if the order id alreay exitd */
bool checkIfOrderExistById(Set orders, const unsigned int order_id);

/* return pointer to OrderInformation of an order in set orders 
return value- if allocate was faild or order id does not exist in orders
otherewise return pointer to OrderInformation */
AmountSet findSpecificOrderInOrders (Set orders, const unsigned int order_id);
void clearProductFromAllOrders (Set orders, const unsigned id);
int getOrderId (OrderInformation order);
///////////////////////functions for item set amount in an order

/* change the amount of item in specific order.
return value- AS_OUT_OF_MEMORY if allocation failed.
otherewise and the AmountSetResult of asChangeAmount  */
//AmountSetResult changeAmountOfItemInOrder(AmountSet list_item_in_order, const unsigned int product_id, const double amount);

/* get product id and cheack if the product id exit in specific order
return value- false if the product id do not exit and true if the product id alreay exitd */
bool checkIfItemExistInOrderById(AmountSet list_items_in_order, const unsigned int product_id);

/* create new unsigned int* for id
returns value- NULL if allocated was faild, otherwise unsigned int* ewith the id */
unsigned int* createNewIdForItemInOrder(const unsigned int product_id);

unsigned int* findSpecificItemInOrders(AmountSet order, const unsigned int product_id);

#endif /*ORDERS_H*/
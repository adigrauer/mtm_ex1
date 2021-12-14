#ifndef ORDERS_H
#define ORDERS_H
#include "amount_set.h"
#include "set.h"
#include "amount_set.h"

//typedef for structs
typedef struct order_information_t *OrderInformation;
typedef struct single_item_in_order *SingleItemInOrder;

//functions for using generic ADT set for restoring oreders
SetElement copyOrder (SetElement order);
void freeOrder (SetElement order);
int compareOrder (SetElement order_1, SetElement order_2);

//functions for using generic ADT amount set for restoring items in oreder
ASElement copySingleItemInOrder (ASElement item_id);
void freeSingleleItemInOrder (ASElement item_id);
int compareItemInOrder (ASElement item_id_1, ASElement item_id_2);

////////////////////////functions for orders set

/* chose unsigned int for the next id of new order.
return values- if set orders is empty the function will return 1 for the first order in set orders,
otherwise the function will return the maxmial id order+1 */
unsigned int selectIdForNewOrder (Set orders);

/* create new order element for set orders.
return value- if allocation was failed return NULL,
otherwise return new OrderInformation */
OrderInformation createNewEmptyOrder (const unsigned int order_id);

/* get order id and cheack if the order id exit in the set of orders
return value- false if the order id do not exit and true if the order id alreay exitd */
bool checkIfOrderExistById (Set orders, const unsigned int order_id);

/* return pointer to OrderInformation of an order in set orders 
return value- if allocate was faild or order id does not exist in orders
otherewise return pointer to OrderInformation */

/* return Amountset of list items in order for specific order by id
return value- NULL if allocation was failed,
otherwise return an Amounset pointer to the list of item in specific order in the orders set */
AmountSet GetListOfItemsInSpecificOrder (Set orders, const unsigned int order_id);

///////////need to change the name to -findSpecificOrderInOrders///////////////////////
/* return Orderinformation of specific order by id
return value- NULL if allocation was failed,
otherwise return an OrderInformation pointer to specific order in the orders set */
OrderInformation findSpecificOrderInOrders (Set orders, const unsigned int order_id);

/* delete product by id from all orders in the set of orders
return value- void function, delete the product by asDelete of amount set if exist,
otherwise does not do nothing */
void clearProductFromAllOrders (Set orders, const unsigned id);

/* return order id for specific order by access to the field of order id in the struct */
int getOrderId (OrderInformation order);

/* need to clear total price before calculate each new printing */ 
void clearOrderTotalAmount (OrderInformation order);

/* add to the field of total price in specific order amount that given after calculating the profits of the order */
void changeTotalPriceInOrder (OrderInformation order, double price_to_add);

/* return order total price for specific order by access to the field of order in the struct */ 
double getTotalPriceForOrder (OrderInformation order);

///////////////////////functions for item set amount in an order

/* get product id and cheack if the product id exit in specific order
return value- false if the product id do not exit and true if the product id alreay exitd */
bool checkIfItemExistInOrderById (AmountSet list_items_in_order, const unsigned int product_id);

/* create new unsigned int* for id
returns value- NULL if allocated was faild, otherwise unsigned int* ewith the id */
unsigned int* createNewIdForItemInOrder (const unsigned int product_id);

/* find a specifi item in all existing orders
return value- NULL if allocation was failed,
otherwise return an unsigned int pointer to item in given order in the set of orders by product id */
unsigned int* findSpecificItemInOrders(AmountSet order, const unsigned int product_id);

/* return pointer to the item with the minimal id in given order */
unsigned int* getMinIdItemInOrder (AmountSet order);

/* return pointer to the item with the minimal id in given order ater the last printed item דorted in ascending order
return value- pointer the the next mininal item in rder, NULL if all items were printed */
unsigned int* getNextMinimalItemInOrderById (AmountSet order, unsigned int* last_printed_item);

#endif /*ORDERS_H*/
#ifndef ORDERS_H
#define ORDERS_H
#include "amount_set.h"
#include "set.h"

//typedef for structs
typedef struct orders_information_t *OrdersInformation;
typedef struct single_item_in_order *SingleItemInOrder;

//functions for using generic ADT set for restoring oreders
SetElement copyOrder(SetElement order);
SetElement freeOrder(SetElement order);
SetElement compareOrder(SetElement order_exist, SetElement order_to_add);

//functions for using generic ADT amount set for restoring items in oreder
ASElement copyItemInOrder (ASElement item);
ASElement freeItemInOrder (ASElement item);
ASElement compareItemInOrder (ASElement item_exist, ASElement item_to_add);

#endif /*ORDERS_H*/
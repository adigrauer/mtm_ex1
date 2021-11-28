#ifndef ORDERS_H
#define ORDERS_H
#include "amount_set.h"
#include "set.h"

//typedef for structs
typedef struct order_information_t *OrderInformation;
typedef struct single_item_in_order *SingleItemInOrder;

//functions for using generic ADT set for restoring oreders
SetElement copyOrder(SetElement order);
SetElement freeOrder(SetElement order);
int compareOrder(SetElement order_1, SetElement order_2);

//functions for using generic ADT amount set for restoring items in oreder
ASElement copySingleItemInOrder (ASElement item_id);
ASElement freeSingleleItemInOrder (ASElement item_id);
int compareItemInOrder (ASElement item_id_1, ASElement item_id_2);

#endif /*ORDERS_H*/
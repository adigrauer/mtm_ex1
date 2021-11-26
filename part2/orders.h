#ifndef ORDERS_H
#define ORDERS_H
#include "amount_set.h"
#include "set.h"
#include "matamikya.h"

typedef struct orders_t *Orders;
typedef struct single_item_in_order *SingleItemInOrder;
copySetElements copyOrder (Orders orders);
freeSetElements freeOrder (Orders orders);
compareSetElements compareOrders (Orders order_exist, Orders order_to_add);

////single item in each order
typedef SingleItemInOrder (*copySingleItem)(SingleItemInOrder);
typedef SingleItemInOrder (*freeSingleItem)(SingleItemInOrder);
typedef SingleItemInOrder (*compareSingleItem)(SingleItemInOrder, SingleItemInOrder);

copySingleItem copyItemInOrder (SingleItemInOrder item);
freeSingleItem freeItemInOrder (SingleItemInOrder item);
compareSingleItem compareItemInOrder (SingleItemInOrder item_exist, SingleItemInOrder item_to_add);
#endif /*ORDERS_H*/
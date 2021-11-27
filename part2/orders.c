#include "set.h"
#include "amount_set.h"
#include "matamikya.h"

//orders node
struct orders_information_t {
    unsigned int order_id;
    AmountSet items_in_order;
    orders_information_t* next;
};

//items_in_order node
struct single_item_in_order {
    unsigned int item_id;
    char* item_description;
    single_item_in_order* next_item_in_order;
    /* double amount; no need to include in the struct single_item_in_order cause the items in the orders organized in amount set ADT,
    therefore exit build in a field for amount */
};
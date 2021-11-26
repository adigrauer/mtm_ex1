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
    unsigned int product_id;
    char* product_name;
    double amount;
    single_item_in_order* next_item_in_order;

};
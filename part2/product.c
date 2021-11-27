#include "amount_set.h"
#include "matamikya.h"

struct product_t {
    char* product_description;
    unsigned int product_id;
    MtmProductData custom_data;
    //need to implement
    MatamikyaAmountType amount_type;
    double profit;
    product_t* next_product;
    /* double amount; no need to include in the struct single_item_in_order cause the items in the orders organized in amount set ADT,
    therefore exit build in a field for amount */
};


struct mtmProductData_t {
    double price_for_quantity; 
}; 
 
MtmProductData copyProductData (MtmProductData product_data)
{

}

MtmProductData freeProductData (MtmProductData product_data)
{

}

MtmProductData compareProductData (MtmProductData product_data, const double amount)
{
    
}
#ifndef PRODUCT_H
#define PRODUCT_H
#include "amount_set.h"
#include "matamikya.h"
#include <stdlib.h>
#include <string.h>

struct product_t {
    char* product_description;
    unsigned int product_id;
    MtmProductData custom_data;
    //need to implement
    MatamikyaAmountType amount_type;
    double profit;
    /* double amount; no need to include in the struct single_item_in_order cause the items in the orders organized in amount set ADT,
    therefore exit build in a field for amount */
};

struct mtmProductData_t {
    double price_for_quantity; 
}; 

//typedef for structs
typedef struct product_t *Product;
typedef struct mtmProductData_t *ProductData;

//functions for using generic ADT amount set for restoring items in storage
ASElement createProduct ();
ASElement copyProduct (ASElement product);
void freeProduct (ASElement product);
int compareProduct (ASElement product_exist, ASElement product_to_add);

//functions for using MtmProductData for restoring more information about the product
MtmProductData createProductData ();
MtmProductData copyProductData (MtmProductData product_data);
void freeProductData (MtmProductData product_data);
double getProductPrice (MtmProductData product_data, const double amount);

#endif /*PRODUCT_H*/
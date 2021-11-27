#ifndef PRODUCT_H
#define PRODUCT_H
#include "amount_set.h"
#include "matamikya.h"

//typedef for structs
typedef struct product_t *Product;

//functions for using generic ADT amount set for restoring items in storage
ASElement copyProduct (ASElement product);
ASElement freeProduct (ASElement product);
ASElement compareProduct (ASElement product_exist, ASElement product_to_add);

//functions for using MtmProductData for restoring more information about the product
MtmProductData copyProductData (MtmProductData product_data);
MtmProductData freeProductData (MtmProductData product_data);
MtmProductData compareProductData (MtmProductData product_data, const double amount);

#endif /*PRODUCT_H*/
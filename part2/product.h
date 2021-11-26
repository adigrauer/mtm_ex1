#ifndef PRODUCT_H
#define PRODUCT_H
#include "amount_set.h"
#include "matamikya.h"
typedef struct product_t *Product;
CopyASElement copyProduct (Product product);
FreeASElement freeProduct (Product product);
CompareASElements compareProduct (Product product_exist, Product product_to_add);

////product data
MtmCopyData copyProductData (MtmProductData product_data);
MtmFreeData freeProductData (MtmProductData product_data);
MtmGetProductPrice compareProductData (MtmProductData product_data, const double amount);


#endif /*PRODUCT_H*/
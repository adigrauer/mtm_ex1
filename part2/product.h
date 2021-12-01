#ifndef PRODUCT_H
#define PRODUCT_H
#include "amount_set.h"
#include "matamikya.h"
#include <stdlib.h>
#include <string.h>


//typedef for structs
typedef struct product_t *Product;


//functions for using generic ADT amount set for restoring items in storage
Product createProduct ();
ASElement copyProduct (ASElement product);
void freeProduct (ASElement product);
int compareProduct (ASElement product_exist, ASElement product_to_add);
bool productExist (AmountSet products_set, const unsigned int id);
bool registerProduct (Product new_product, const unsigned int id, const char *name,
                              const double amount, const MatamikyaAmountType amountType,
                              const MtmProductData customData, MtmCopyData copyData,
                              MtmFreeData freeData, MtmGetProductPrice prodPrice);
Product getProductInStorage (AmountSet storage, const unsigned int id);
MatamikyaAmountType getAmountType (Product product);
Product getBestSelling (AmountSet storage);
Product getNextMinimalProductById (AmountSet storage, Product last_printed_product);
Product getMinIdProduct (AmountSet storage);


////get information for matamikya
char* getProductName (Product product);
char* getProductNameById (AmountSet storage, unsigned int id);
unsigned int getProductId (Product product);
double getProductIncome (Product product);
double getProductPrice (Product product);
double getProductAmount (AmountSet storage,Product product);
double calculatePriceForAmount (Product product, double amount);
void updateProfitForProduct (Product product, double amount);
#endif /*PRODUCT_H*/


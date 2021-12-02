#ifndef PRODUCT_H
#define PRODUCT_H
#include "amount_set.h"
#include "matamikya.h"
#include <stdlib.h>
#include <string.h>


//typedef for structs
typedef struct product_t *Product;


//functions for using generic ADT amount set for restoring items in storage

/*allocates new memory for product, product values are null or empty after this*/
Product createProduct ();
ASElement copyProduct (ASElement product);
void freeProduct (ASElement product);

/*compare product by id*/
int compareProduct (ASElement product_exist, ASElement product_to_add);

/*checks if product exists in storage by id*/
bool productExist (AmountSet products_set, const unsigned int id);

/*takes the new product freates by create function and updates it to given values*/
bool registerProduct (Product new_product, const unsigned int id, const char *name,
                              const double amount, const MatamikyaAmountType amountType,
                              const MtmProductData customData, MtmCopyData copyData,
                              MtmFreeData freeData, MtmGetProductPrice prodPrice);

/*finds pointer to Product using an id*/
Product getProductInStorage (AmountSet storage, const unsigned int id);

/* print only one best selling
Product getBestSelling (AmountSet storage); */

Product getBestSellingOfMinimalIdProduct (AmountSet storage);
Product getNextBestSelling (AmountSet storage, Product last_best_selling_printed);

/*gets a product with higer id then the product given, but lower then others*/
Product getNextMinimalProductById (AmountSet storage, Product last_printed_product);

/*gets the total minimal id product*/
Product getMinIdProduct (AmountSet storage);

/*for an amount and a product, return s the total price*/
double calculatePriceForAmount (Product product, double amount);

/*after an order is shipped, the function updates the profit made per product*/
void updateProfitForProduct (Product product, double amount);

////get information for matamikya
MatamikyaAmountType getAmountType (Product product);
char* getProductName (Product product);
char* getProductNameById (AmountSet storage, unsigned int id);
unsigned int getProductId (Product product);
double getProductIncome (Product product);
double getProductPrice (Product product);
double getProductAmount (AmountSet storage,Product product);

#endif /*PRODUCT_H*/


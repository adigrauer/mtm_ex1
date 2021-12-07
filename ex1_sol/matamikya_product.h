#ifndef PRODUCT_H
#define PRODUCT_H
#include "amount_set.h"
#include "matamikya.h"
#include <stdlib.h>
#include <string.h>


//typedef for structs
typedef struct product_t *Product;

//functions for using generic ADT amount set for restoring items in storage

/*allocates new memory for product,
Return values:
NULL if aloocation failed
ptr to new empty product*/
Product createProduct ();

/*creates copy of Product,
Return values:
NULL if Product is NULL,or one of the product arguments NULL or allocation failed
otherwisr, ptr to copy of product*/
ASElement copyProduct (ASElement product);
/*free allocated memory*/
void freeProduct (ASElement product);

/*compare product by id
return the difference between two product ids*/
int compareProduct (ASElement product_exist, ASElement product_to_add);

/*checks if product exists in storage by id
return true if exist
false if not*/
bool productExist (AmountSet products_set, const unsigned int id);

/*takes the new product created by create function and updates it to given values
false if allocation for product name failed otherwise true*/
bool registerProduct (Product new_product, const unsigned int id, const char *name,
                              const double amount, const MatamikyaAmountType amountType,
                              const MtmProductData customData, MtmCopyData copyData,
                              MtmFreeData freeData, MtmGetProductPrice prodPrice);

/*finds pointer to Product using an id
return:
NULL if memory allocatin failed
ptr of the Product in storage*/
Product getProductInStorage (AmountSet storage, const unsigned int id);

/*finds pointer to BestSellingProduct using an id
return: ptr to the best seller*/
Product getBestSelling (AmountSet storage); 

/*gets a product with higer id then the product given, but lower then others
return values:
    NULL if last printed id is the last
    ptr of the next minimal product id*/
Product getNextMinimalProductById (AmountSet storage, Product last_printed_product);

/*gets the total minimal id product
return values:
    NULL if storage empty
    ptr of the minimal product id*/
Product getMinIdProduct (AmountSet storage);

/*for an amount and a product, return the total price*/
double calculatePriceForAmount (Product product, double amount);

/*after an order is shipped, the function updates the profit made per product*/
void updateProfitForProduct (Product product, double amount);

////get information for matamikya
/*return ProductAmount type*/
MatamikyaAmountType getAmountType (Product product);
/*return ProductName*/
char* getProductName (Product product);
/*return ProductName by id*/
char* getProductNameById (AmountSet storage, unsigned int id);
/*return Product id*/
unsigned int getProductId (Product product);
/*return Product profit*/
double getProductIncome (Product product);
/*return Product price*/
double getProductPrice (Product product);
/*return Product amount*/
double getProductAmount (AmountSet storage,Product product);

#endif /*PRODUCT_H*/


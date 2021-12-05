#include "matamikya_print.h"
#include "set.h"
#include "amount_set.h"
#include "matamikya.h"
#include "orders.h"
#include "product.h"
#include <stdlib.h>
#include <stdio.h>

///define
#define INT_VALUE 0.001

//structs implementation 
////////////////////////////////////////////////
struct Matamikya_t{
   AmountSet storage;
   Set orders; 
   unsigned int last_orders_id;
};
/////////////////////////////////////////////////

//static declerations
/////////////////////////////////////////////////
/*used before adding new product to the storage to check if product is valid
*return values: MATAMIKYA_NULL_ARGUMENT - if matamikya/name/customData/copyData/freeData/prodPrice are NULL.
    MATAMIKYA_INVALID_NAME - if name is empty, or doesn't start with a letter (a -z, A -Z) or a digit (0 -9).
    MATAMIKYA_INVALID_AMOUNT - if amount < 0, or is not consistent with amountType (@see MatamikyaAmountType documentation above)
    MATAMIKYA_PRODUCT_ALREADY_EXIST - if a product with the given id already exist.
    MATAMIKYA_SUCCESS - if product was added successfully. */
static MatamikyaResult checkProductValid (Matamikya matamikya, const unsigned int id, const char *name,
                              const double amount, const MatamikyaAmountType amountType,
                              const MtmProductData customData, MtmCopyData copyData,
                              MtmFreeData freeData, MtmGetProductPrice prodPrice);

/* check if given amount type match to the product amount type
return value- MATAMIKYA_INVALID_AMOUNT if amount doesnt match otherwise MATAMIKYA_SUCCESS */
static MatamikyaResult checkProductAmountValid (const double amount, const MatamikyaAmountType amountType);

/* check if product name valid- not empty, or doesn't start with aletter (a -z, A -Z) or a digit (0 -9). 
return value- MATAMIKYA_INVALID_NAME if not valid, otherwise MATAMIKYA_SUCCESS */
static MatamikyaResult checkProductNameValid (const char *name);

/*check if there is enough of a product to reduce amount from the storage, adding is always allowed */
static MatamikyaResult checkProductAmountSufficient (AmountSet storage, const double amount, Product product);

/* check if matamikya or storage NULL
return value- MATAMIKYA_NULL_ARGUMENT one of the struct NULL, otherwise MATAMIKYA_SUCCESS */
static MatamikyaResult checkIfStorageNull (Matamikya matamikya);

/* check if matamikya or orders NULL
return value- MATAMIKYA_NULL_ARGUMENT one of the struct NULL, otherwise MATAMIKYA_SUCCESS */
static MatamikyaResult checkIfOrdersNull(Matamikya matamikya);

/*changes amounts and updates profits in the storage according to the legal shipped order*/
static void updateShippedOrder(AmountSet storage, AmountSet order);

/*checks if order is legal by checking if the amount in the storage is sufficient*/ 
static bool checkIfOrderIsValidForShipping (AmountSet storage, AmountSet order);

static void calculateTotalPriceOfOrder(Matamikya matamikya, const unsigned int order_id);
/////////////////////////////////////////////////

////////MATAMIKYA FUNCTIONS IMPLEMENTATION///////
/////////////////////////////////////////////////
Matamikya matamikyaCreate()
{
    Matamikya new_warehouse = (Matamikya)malloc(sizeof(*new_warehouse));   //malloc!!! need to free 1
    if(new_warehouse == NULL){
        return NULL;
    }
    new_warehouse->storage = asCreate(copyProduct, freeProduct, compareProduct); //malloc!!! need to free 2
    if(new_warehouse->storage == NULL){
        matamikyaDestroy(new_warehouse);  //free 1 in case of error
        return NULL;
    }
    new_warehouse->orders = setCreate(copyOrder, freeOrder, compareOrder);  //malloc!!! need to free 3
    if(new_warehouse->orders == NULL){
        matamikyaDestroy(new_warehouse);
        return NULL;
    }
    new_warehouse->last_orders_id = 1;
    return new_warehouse;
}

void matamikyaDestroy(Matamikya matamikya)
{
   if(matamikya == NULL){
      return;
   }
   asDestroy(matamikya->storage);    //free 2 at the end of program
   setDestroy(matamikya->orders);   //free 3 at the end of program
   free(matamikya);   //free 1 at the end of program
}

MatamikyaResult mtmNewProduct(Matamikya matamikya, const unsigned int id, const char *name,
                              const double amount, const MatamikyaAmountType amountType,
                              const MtmProductData customData, MtmCopyData copyData,
                              MtmFreeData freeData, MtmGetProductPrice prodPrice)
 {
    MatamikyaResult result = checkProductValid(matamikya, id, name, amount, amountType, customData, copyData, freeData, prodPrice);
    if ( result != MATAMIKYA_SUCCESS) {
        return result;
    }
    Product new_product = createProduct();
    if (new_product == NULL){
        return MATAMIKYA_OUT_OF_MEMORY;
    }
    if (registerProduct(new_product, id, name, amount, amountType, customData, copyData, freeData, prodPrice) == false){
        freeProduct(new_product);
        return MATAMIKYA_OUT_OF_MEMORY;
    }
    asRegister(matamikya->storage, (ASElement)new_product);
    asChangeAmount(matamikya->storage, (ASElement)new_product, amount);
    freeProduct(new_product); //this is what we added
    return MATAMIKYA_SUCCESS;
 }

MatamikyaResult mtmChangeProductAmount(Matamikya matamikya, const unsigned int id, const double amount)
{   
    if (checkIfStorageNull(matamikya) == MATAMIKYA_NULL_ARGUMENT){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    if (productExist(matamikya->storage, id) == false){
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    Product ptr = getProductInStorage(matamikya->storage, id);
    if (ptr == NULL){
        return MATAMIKYA_OUT_OF_MEMORY;
    }
    MatamikyaAmountType amount_type = getAmountType(ptr);
    if (checkProductAmountValid(amount, amount_type) != MATAMIKYA_SUCCESS) {
        return MATAMIKYA_INVALID_AMOUNT;
    }
    if (checkProductAmountSufficient(matamikya->storage, amount, ptr) != MATAMIKYA_SUCCESS)
    {
        return MATAMIKYA_INSUFFICIENT_AMOUNT;
    }
    asChangeAmount(matamikya->storage, (ASElement)ptr, amount);
    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmClearProduct(Matamikya matamikya, const unsigned int id)
{
    if (checkIfStorageNull(matamikya) == MATAMIKYA_NULL_ARGUMENT){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    if (productExist(matamikya->storage, id) == false) {
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    clearProductFromAllOrders(matamikya->orders, id);
    Product ptr = getProductInStorage(matamikya->storage, id);
    if (ptr == NULL){
        return MATAMIKYA_OUT_OF_MEMORY;
    }
    asDelete(matamikya->storage, (ASElement)ptr);
    return MATAMIKYA_SUCCESS;
}

unsigned int mtmCreateNewOrder(Matamikya matamikya)
{
    if(checkIfOrdersNull(matamikya) == MATAMIKYA_NULL_ARGUMENT){
        return 0;
    }
    unsigned int new_order_id = matamikya->last_orders_id + 1;
    OrderInformation new_order = createNewEmptyOrder(new_order_id);
    if(new_order == NULL){
        return 0;
    }
    if(setAdd(matamikya->orders, (SetElement)new_order) == SET_SUCCESS){
        matamikya->last_orders_id = new_order_id;
        freeOrder(new_order);
        return new_order_id;
    }
    freeOrder(new_order);
    return 0;
}

MatamikyaResult mtmChangeProductAmountInOrder(Matamikya matamikya, const unsigned int orderId,
                  const unsigned int productId, const double amount)
{
    if(checkIfStorageNull(matamikya) == MATAMIKYA_NULL_ARGUMENT || checkIfOrdersNull(matamikya) == MATAMIKYA_NULL_ARGUMENT){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    if(productExist(matamikya->storage, productId) == false){
        return MATAMIKYA_PRODUCT_NOT_EXIST;
    }
    if(checkIfOrderExistById(matamikya->orders, orderId) == false){
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    AmountSet ptr_order = GetListOfItemsInSpecificOrder(matamikya->orders, orderId);
    if(ptr_order == NULL){
        return MATAMIKYA_OUT_OF_MEMORY; //findSpecificOrderInOrders wont return NULL cause order doesnt exist
    }
    Product product = getProductInStorage(matamikya->storage, productId);
    if(product == NULL){
        return MATAMIKYA_OUT_OF_MEMORY;
    }
    MatamikyaAmountType product_amount_type = getAmountType(product);
    if(checkProductAmountValid(amount,product_amount_type) == MATAMIKYA_INVALID_AMOUNT){
        return MATAMIKYA_INVALID_AMOUNT;
    }
    if(checkIfItemExistInOrderById(ptr_order, productId) == false){
        if(amount <= 0){
            return MATAMIKYA_SUCCESS; 
        }
        unsigned int* new_product_id = createNewIdForItemInOrder(productId);
        asRegister(ptr_order, (ASElement)new_product_id);
        freeSingleleItemInOrder(new_product_id); //this is what we added
    }
    //need to check how getamount works, doest it use the compare function????
    unsigned int* ptr_product_id = findSpecificItemInOrders(ptr_order, productId);
    double current_amount = 0;
    //AmountSetResult change_amount_result = changeAmountOfItemInOrder(ptr_order, product_id, amount);
    AmountSetResult change_amount_result = asChangeAmount(ptr_order,(ASElement)ptr_product_id, amount);
    if(change_amount_result == AS_INSUFFICIENT_AMOUNT){
        asDelete(ptr_order, (ASElement)ptr_product_id);
        return MATAMIKYA_SUCCESS;
    }
    asGetAmount(ptr_order, (ASElement)ptr_product_id, &current_amount);
    if(current_amount == 0){
        asDelete(ptr_order, (ASElement)ptr_product_id);
        return MATAMIKYA_SUCCESS;
    }
    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmShipOrder(Matamikya matamikya, const unsigned int orderId)
{
    if(checkIfStorageNull(matamikya) == MATAMIKYA_NULL_ARGUMENT || checkIfOrdersNull(matamikya) == MATAMIKYA_NULL_ARGUMENT){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    if(checkIfOrderExistById(matamikya->orders, orderId) == false){
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    AmountSet items_in_order = GetListOfItemsInSpecificOrder(matamikya->orders, orderId);
    if(items_in_order == NULL){
        return MATAMIKYA_OUT_OF_MEMORY;
    }
    if(checkIfOrderIsValidForShipping(matamikya->storage, items_in_order) == false){
        return MATAMIKYA_INSUFFICIENT_AMOUNT;
    }
    updateShippedOrder(matamikya->storage, items_in_order);
    mtmCancelOrder(matamikya, orderId);
    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmCancelOrder(Matamikya matamikya, const unsigned int orderId)
{
    if(checkIfOrdersNull(matamikya) == MATAMIKYA_NULL_ARGUMENT){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    if(checkIfOrderExistById(matamikya->orders, orderId) == false){
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    OrderInformation temp_order = createNewEmptyOrder(orderId);
    if(temp_order == NULL){
        return MATAMIKYA_OUT_OF_MEMORY;
    }  
    setRemove(matamikya->orders, (SetElement)temp_order);
    //does set use coopy or original order in the function setRemove????
    freeOrder(temp_order);
    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmPrintInventory(Matamikya matamikya, FILE *output)
{
    if (checkIfStorageNull(matamikya) == MATAMIKYA_NULL_ARGUMENT || output == NULL) {
        return MATAMIKYA_NULL_ARGUMENT;
    }
    Product ptr_current_min = getMinIdProduct(matamikya->storage);
    fprintf (output, "Inventory Status:\n");
    if (ptr_current_min == NULL) {
        return MATAMIKYA_SUCCESS;
    }
    while (ptr_current_min != NULL) {
        mtmPrintProductDetails(getProductName(ptr_current_min), getProductId(ptr_current_min),
             getProductAmount(matamikya->storage, ptr_current_min), getProductPrice(ptr_current_min), output);
        ptr_current_min = getNextMinimalProductById(matamikya->storage, ptr_current_min);
    }
    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmPrintOrder(Matamikya matamikya, const unsigned int orderId, FILE *output)
{
    if(checkIfOrdersNull(matamikya) == MATAMIKYA_NULL_ARGUMENT  || checkIfStorageNull(matamikya) == MATAMIKYA_NULL_ARGUMENT || output == NULL){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    if(checkIfOrderExistById(matamikya->orders, orderId) == false){
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    OrderInformation order = findSpecificOrderInOrders(matamikya->orders, orderId);
    AmountSet list_items_in_specific_order = GetListOfItemsInSpecificOrder (matamikya->orders, orderId);
    calculateTotalPriceOfOrder(matamikya, orderId);
    int order_size = asGetSize(list_items_in_specific_order);
    if(order_size == 0){
        mtmPrintOrderHeading(orderId, output);
        mtmPrintOrderSummary(getTotalPriceForOrder(order), output);
        return MATAMIKYA_SUCCESS;
    } 
    mtmPrintOrderHeading(orderId, output);
    unsigned int* ptr_current_min = getMinIdItemInOrder(list_items_in_specific_order);
    Product temp_product = NULL;
    double amount = 0;
    while(ptr_current_min != NULL){
        temp_product = getProductInStorage(matamikya->storage, *ptr_current_min);
        asGetAmount(list_items_in_specific_order, (ASElement)ptr_current_min, &amount);
        mtmPrintProductDetails(getProductNameById(matamikya->storage, *ptr_current_min), *ptr_current_min,
            amount, calculatePriceForAmount(temp_product, amount), output);
        ptr_current_min = getNextMinimalItemInOrderById(list_items_in_specific_order, ptr_current_min); 
    }
    mtmPrintOrderSummary(getTotalPriceForOrder(order), output);
    return MATAMIKYA_SUCCESS;
}

MatamikyaResult mtmPrintBestSelling(Matamikya matamikya, FILE *output) 
{
    if (checkIfStorageNull(matamikya) == MATAMIKYA_NULL_ARGUMENT || output == NULL){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    Product best_selling_product = getBestSelling(matamikya->storage);
    double max_profit = getProductIncome(best_selling_product);
    if(max_profit == 0) {
        fprintf (output, "Best Selling Product:\nnone\n");
        return MATAMIKYA_SUCCESS;
    }
    fprintf (output, "Best Selling Product:\n");
    mtmPrintIncomeLine(getProductName(best_selling_product), getProductId(best_selling_product), max_profit, output);
    return MATAMIKYA_SUCCESS;
}

/////////////////////////////////////////////////

///////////static functions/////////
/////////////////////////////////////////////////
static MatamikyaResult checkProductValid (Matamikya matamikya, const unsigned int id, const char *name,
                              const double amount, const MatamikyaAmountType amountType,
                              const MtmProductData customData, MtmCopyData copyData,
                              MtmFreeData freeData, MtmGetProductPrice prodPrice)
{
    if (checkIfStorageNull(matamikya) == MATAMIKYA_NULL_ARGUMENT || name == NULL || customData == NULL ||copyData == NULL || freeData == NULL
        || prodPrice == NULL) {
            return MATAMIKYA_NULL_ARGUMENT;
        }
    if (amount < 0) {
        return MATAMIKYA_INVALID_AMOUNT;
    }
    if (checkProductAmountValid(amount, amountType) == MATAMIKYA_INVALID_AMOUNT) {
        return MATAMIKYA_INVALID_AMOUNT;
    }
    if (checkProductNameValid(name) == MATAMIKYA_INVALID_NAME) {
        return MATAMIKYA_INVALID_NAME;
    }
    if(productExist(matamikya->storage, id) == true) {
        return MATAMIKYA_PRODUCT_ALREADY_EXIST;
    }
    return MATAMIKYA_SUCCESS;
}

static MatamikyaResult checkProductAmountValid (const double amount, const MatamikyaAmountType amountType) 
{
    double difference = amount - (int)amount;
    if (difference < 0) {
        difference *= -1;
    } 
    if ((amountType == MATAMIKYA_INTEGER_AMOUNT) &&  (difference < (1-INT_VALUE)) && (difference > INT_VALUE)) {
        return MATAMIKYA_INVALID_AMOUNT;
    }
    if (amountType == MATAMIKYA_HALF_INTEGER_AMOUNT){
        if(((difference < (1-INT_VALUE-0.5)) && (difference > INT_VALUE))
            || ((difference > (0.5 + INT_VALUE)) && (difference < (1-INT_VALUE)))) {
            return MATAMIKYA_INVALID_AMOUNT;
        }
    }
    return MATAMIKYA_SUCCESS;
}

static MatamikyaResult checkProductNameValid (const char *name) 
{
    if (strcmp("", name) == 0)
    {
        return MATAMIKYA_INVALID_NAME;
    }
    if ( (*name >= 'A' && *name <= 'Z') || (*name >= 'a' && *name <= 'z') || (*name >= '0' && *name <= '9')){
        return MATAMIKYA_SUCCESS;
    }
    return MATAMIKYA_INVALID_NAME;
}


static MatamikyaResult checkProductAmountSufficient (AmountSet storage, const double amount, Product product)
{
    if(amount >= 0) {
        return MATAMIKYA_SUCCESS;
    }
    double real_amount = 0;
    asGetAmount(storage,(ASElement)product, &real_amount);
    if (real_amount + amount < 0 ) {
        return MATAMIKYA_INSUFFICIENT_AMOUNT;
    }
    return MATAMIKYA_SUCCESS;
}

static MatamikyaResult checkIfStorageNull(Matamikya matamikya)
{
    if(matamikya == NULL || matamikya->storage == NULL){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    return MATAMIKYA_SUCCESS;
}

static MatamikyaResult checkIfOrdersNull(Matamikya matamikya)
{
    if(matamikya == NULL || matamikya->orders == NULL){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    return MATAMIKYA_SUCCESS;
}

static bool checkIfOrderIsValidForShipping (AmountSet storage, AmountSet order)
{
    unsigned int* ptr = (unsigned int*)asGetFirst(order);
    double amount_to_reduce_from_storage = 0;
    Product ptr_to_storage_product = NULL;
    while (ptr != NULL) {
        asGetAmount(order, ptr, &amount_to_reduce_from_storage);
        ptr_to_storage_product = getProductInStorage(storage, *ptr);
        if (checkProductAmountSufficient(storage, (-amount_to_reduce_from_storage), ptr_to_storage_product) == MATAMIKYA_INSUFFICIENT_AMOUNT){
            return false;
        }
        ptr = (unsigned int*)asGetNext(order);
    }
    return true;
}


static void updateShippedOrder(AmountSet storage, AmountSet order)
{
    unsigned int* ptr = (unsigned int*)asGetFirst(order);
    double amount_to_reduce_from_storage = 0;
    Product ptr_to_storage_product = NULL;
    while (ptr != NULL) {
        asGetAmount(order, ptr, &amount_to_reduce_from_storage);
        ptr_to_storage_product = getProductInStorage(storage, *ptr);
        asChangeAmount(storage, (ASElement)ptr_to_storage_product, -amount_to_reduce_from_storage);
        updateProfitForProduct(ptr_to_storage_product, amount_to_reduce_from_storage);
        ptr = (unsigned int*)asGetNext(order);
    }
}

static void calculateTotalPriceOfOrder(Matamikya matamikya, const unsigned int order_id)
{
    AmountSet current_order =GetListOfItemsInSpecificOrder(matamikya->orders, order_id);
    if(asGetSize(current_order) == 0){
        return;
    }
    unsigned int* ptr_product_id = (unsigned int*)asGetFirst(current_order);
    Product temp_product = NULL;
    OrderInformation temp_order = findSpecificOrderInOrders(matamikya->orders, order_id);
    double amount = 0;
    double price_to_add = 0;
    while (ptr_product_id != NULL){
        asGetAmount(current_order, (ASElement)ptr_product_id, &amount);
        temp_product = getProductInStorage(matamikya->storage, *ptr_product_id);
        price_to_add += calculatePriceForAmount(temp_product, amount);
        ptr_product_id = (unsigned int*)asGetNext(current_order);
    }
    changeTotalPriceInOrder(temp_order, price_to_add);
}

/////////////////////////////////////////////////
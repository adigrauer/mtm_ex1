#include "set.h"
#include "amount_set.h"
#include "matamikya.h"
#include "orders.h"
#include "product.h"
#include "util.h"
#include "matamikya_print.h"
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

/////static declerations
static MatamikyaResult checkProductValid (Matamikya matamikya, const unsigned int id, const char *name,
                              const double amount, const MatamikyaAmountType amountType,
                              const MtmProductData customData, MtmCopyData copyData,
                              MtmFreeData freeData, MtmGetProductPrice prodPrice);

static MatamikyaResult checkProductAmountValid (const double amount, const MatamikyaAmountType amountType);
static MatamikyaResult checkProductNameValid (const char *name);
static MatamikyaResult checkProductAmountSufficient (AmountSet storage, const double amount, Product product);
static MatamikyaResult checkIfStorageNull (Matamikya matamikya);
static MatamikyaResult checkIfOrdersNull(Matamikya matamikya);
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
    new_warehouse->last_orders_id = 0;
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
    AmountSet ptr_order = findSpecificOrderInOrders(matamikya->orders, orderId);
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
            return MATAMIKYA_PRODUCT_NOT_EXIST;
        }
        unsigned int* new_product_id = createNewIdForItemInOrder(productId);
        asRegister(ptr_order, (ASElement)new_product_id);
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


bool checkIfAmountInOrderValidForShipping(AmountSet items_in_order)
{
   
}

MatamikyaResult mtmShipOrder(Matamikya matamikya, const unsigned int orderId)
{
    if(matamikya == NULL){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    if(checkIfOrderExistById(matamikya->orders, orderId) == false){
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    AmountSet items_in_order = findSpecificOrderInOrders(matamikya->orders, orderId);
    if(items_in_order == NULL){
        return MATAMIKYA_OUT_OF_MEMORY;
    }

    return MATAMIKYA_INSUFFICIENT_AMOUNT;
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
    freeOrder(temp_order);
    return MATAMIKYA_SUCCESS;
}


///////////static functions/////////
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
    if (amountType == MATAMIKYA_INTEGER_AMOUNT &&  difference < (1-INT_VALUE) && difference > INT_VALUE ) {
        return MATAMIKYA_INVALID_AMOUNT;
    }
    if (amountType == MATAMIKYA_HALF_INTEGER_AMOUNT && (difference < ((1-INT_VALUE) - 0.5) && difference > INT_VALUE )
    || (difference) > (0.5 + INT_VALUE) && difference < (1-INT_VALUE)) {
        return MATAMIKYA_INVALID_AMOUNT;
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
}

static MatamikyaResult checkIfOrdersNull(Matamikya matamikya)
{
    if(matamikya == NULL || matamikya->orders == NULL){
        return MATAMIKYA_NULL_ARGUMENT;
    }
}








#include "amount_set.h"
#include "matamikya.h"
#include "product.h"

struct product_t {
    char* product_description;
    unsigned int product_id;
    MtmProductData custom_data;
    MatamikyaAmountType amount_type;
    double profit;
    MtmCopyData copy_function;
    MtmFreeData free_function;
    MtmGetProductPrice price_function;
}; 

Product createProduct ()
{
    Product new_product = (Product)malloc(sizeof(*new_product));
    if (new_product == NULL) {
        return NULL;
    }
    new_product->product_id = 0;
    new_product->product_description = NULL;
    new_product->custom_data = NULL;
    new_product->profit = 0;
    new_product->amount_type = MATAMIKYA_INTEGER_AMOUNT;
    new_product->copy_function = NULL;
    new_product->free_function = NULL;
    new_product->price_function = NULL;
    return new_product;
}



ASElement copyProduct (ASElement product)
{
    if(product == NULL){
        return NULL;
    }
    Product new_product = createProduct();   
    if (new_product == NULL){
        return NULL;
    } 
    new_product->product_id = ((Product)product)->product_id;
    new_product->amount_type = ((Product)product)->amount_type; 
    new_product->profit = ((Product)product)->profit;
    new_product->custom_data = (((Product)product)-> copy_function)(((Product)product)->custom_data);
    if(new_product->custom_data == NULL) {  
        free(new_product);
        return NULL; 
    }
    if (((Product)product)->product_description == NULL || ((Product)product)->copy_function == NULL ||
    ((Product)product)->free_function == NULL || ((Product)product)->price_function == NULL)
    {
        free(new_product);
        return NULL;
    }
    char* name_copy = (char*)malloc(strlen(((Product)product)->product_description)+1);
    if(name_copy == NULL){
        freeProduct(new_product);
        return NULL;
    }
    strcpy (name_copy, ((Product)product)->product_description);
    new_product->product_description = name_copy;
    new_product->copy_function = ((Product)product)->copy_function;
    new_product->free_function = ((Product)product)->free_function;
    new_product->price_function = ((Product)product)->price_function;
    return (ASElement)new_product; 
}




void freeProduct(ASElement product){
    if (product == NULL) {
        return;
    }
    if(((Product)product)->product_description != NULL){
        free(((Product)product)->product_description);
        (((Product)product)->free_function)(((Product)product)->custom_data);
    }
    free ((Product)product);
}

int compareProduct (ASElement product_exist, ASElement product_to_add)
{
    return (((Product)product_exist)->product_id) - (((Product)product_to_add)->product_id);
}

bool productExist (AmountSet products_set, const unsigned int id) {
    /*if(products_set == NULL) {
        return  false;
    }*/
    Product temp_product = createProduct();
    temp_product->product_id = id;
    if (asContains(products_set ,(ASElement)temp_product) == true) {
        freeProduct(temp_product);
        return true;
    }
    freeProduct(temp_product);
    return false;
}

bool registerProduct (Product new_product, const unsigned int id, const char *name,
                              const double amount, const MatamikyaAmountType amountType,
                              const MtmProductData customData, MtmCopyData copyData,
                              MtmFreeData freeData, MtmGetProductPrice prodPrice)
{
    char* name_copy = (char*)malloc(strlen(name)+1);
    if(name_copy == NULL){
        return false;
    }
    strcpy(name_copy, name);
    new_product->product_description = name_copy;
    new_product->product_id = id;
    new_product->custom_data = copyData(customData);
    new_product->amount_type = amountType;
    new_product->copy_function = copyData;
    new_product->free_function = freeData;
    new_product->price_function = prodPrice;
    return true;
}


Product getProductInStorage (AmountSet storage, const unsigned int id)
{
    Product temp_product = createProduct();
    if (temp_product == NULL){
        return NULL;
    }
    temp_product->product_id = id;
    Product ptr = (Product)asGetFirst(storage);
    while (ptr != NULL){
        if(compareProduct((ASElement)ptr, (ASElement)temp_product) == 0){
            freeProduct(temp_product);
            return ptr;
        }
        ptr = (Product)asGetNext(storage);
    }
    freeProduct(temp_product);
    return NULL;
}


Product getBestSelling (AmountSet storage)
{
    Product ptr = (Product)asGetFirst(storage);
    if (ptr == NULL){
        return ptr;
    }
    Product max_profit_ptr = ptr;
    while (ptr != NULL){
        if(ptr->profit > max_profit_ptr->profit){
            max_profit_ptr = ptr;
        }
        if(ptr->profit == max_profit_ptr->profit){
            if (ptr->product_id < max_profit_ptr->product_id) {
                max_profit_ptr = ptr;
            }
        }    
        ptr = (Product)asGetNext(storage);
    }
    return max_profit_ptr;
}


Product getNextMinimalProductById (AmountSet storage, Product last_printed_product) 
{
    Product ptr = (Product)asGetFirst(storage);
    int current_min_id = 0;
    Product current_min_id_product = NULL;
    while (ptr != NULL){
        if (ptr->product_id <= last_printed_product->product_id){
            ptr = (Product)asGetNext(storage);
            continue;
        }
        if (current_min_id != 0) {
            if (ptr->product_id < current_min_id){
                current_min_id = ptr->product_id;
                current_min_id_product = ptr;
                ptr = (Product)asGetNext(storage);
                continue;
            }
        }
        else {
            current_min_id = ptr->product_id;
                current_min_id_product = ptr;
        } 
        ptr = (Product)asGetNext(storage);
    }
    if (current_min_id == last_printed_product-> product_id) {
        return NULL;
    }
    return current_min_id_product;
}


Product getMinIdProduct (AmountSet storage)
{
    Product ptr = (Product)asGetFirst(storage);
    if (ptr == NULL){
        return NULL;
    }
    unsigned int current_min_id = ptr->product_id;
    Product current_min_id_product = ptr;
    while (ptr != NULL) {
        if(ptr->product_id < current_min_id){
            current_min_id = ptr->product_id;
            current_min_id_product = ptr;
        }
        ptr = (Product)asGetNext(storage);
    }
    return current_min_id_product;
}

double calculatePriceForAmount (Product product, double amount)
{
    return (product->price_function)(product->custom_data, amount);
}

void updateProfitForProduct (Product product, double amount)
{
    product->profit += ((product->price_function)(product->custom_data, amount));
}

/////get information for matamikya functions/////
MatamikyaAmountType getAmountType (Product product)
{
    return product->amount_type;
}

char* getProductName (Product product)
{
    return product->product_description;
}

char* getProductNameById (AmountSet storage, unsigned int id)
{
    Product product = getProductInStorage(storage, id);
    return getProductName(product);
}

unsigned int getProductId (Product product)
{
    return product->product_id;
}

double getProductIncome (Product product)
{
    printf ("%f", product->profit);
    return product->profit;
}

double getProductPrice (Product product)
{
    return product->price_function(product->custom_data, 1); //מה היא יחידת מידה???
}

double getProductAmount (AmountSet storage, Product product)
{
    double amount;
    asGetAmount(storage, (ASElement)product, &amount);
    return amount;
}


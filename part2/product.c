#include "amount_set.h"
#include "matamikya.h"
#include "product.h"

/*struct product_t {
    char* product_description;
    unsigned int product_id;
    MtmProductData custom_data;
    //need to implement
    MatamikyaAmountType amount_type;
    double profit;
    /* double amount; no need to include in the struct single_item_in_order cause the items in the orders organized in amount set ADT,
    therefore exit build in a field for amount 
}; 


struct mtmProductData_t {
    double price_for_quantity; 
}; */
 
MtmProductData createProductData ()
{
    ProductData new_data = (ProductData)malloc(sizeof(*new_data));
    if (new_data==NULL){
        return NULL;
    }
     new_data->price_for_quantity = 0;
    return (MtmProductData)new_data;
}

MtmProductData copyProductData (MtmProductData product_data)
{
    if (((ProductData)product_data) == NULL) {
        return NULL;
    }
    ProductData new_data = (ProductData)malloc(sizeof(*new_data));  //malloc!!!! need to free 1
    if(new_data == NULL){
        return NULL;
    }
    new_data->price_for_quantity = ((ProductData)product_data)->price_for_quantity;//////
    return (MtmProductData)new_data;
}

void freeProductData (MtmProductData product_data)
{
    if (product_data==NULL)
    {
        return;
    }
    free(product_data);
}

double getProductPrice (MtmProductData product_data, const double amount)
{
    return (((ProductData)product_data)->price_for_quantity * amount);
}

////product////

ASElement createProduct ()
{
    Product new_product = (Product)malloc(sizeof(*new_product));
    if (new_product==NULL){
        return NULL;
    }
    new_product->product_id = 0;
    new_product->product_description = NULL;
    new_product->custom_data = NULL;
    if(new_product->custom_data == NULL){
        freeProduct(new_product);
        return NULL;
    }
    new_product->profit = 0;
    new_product->amount_type =0;
    return (MtmProductData)new_product;
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
    new_product->amount_type = ((Product)product)->amount_type; // ככה מעתיקים enum?
    new_product->profit = ((Product)product)->profit;
    new_product->custom_data = copyProductData(((Product)product)->custom_data);
    if(new_product->custom_data == NULL) { //  אם הקצאת הקסטום דאטא לא עבדה זה מה שצריך? 
        free(new_product);
        return NULL;
    }
    if (((Product)product)->product_description == NULL ) {
        return (ASElement)new_product;
    }
    char* name_copy = malloc(strlen(((Product)product)->product_description)+1);
    if(name_copy == NULL){
        freeProduct(new_product);
        return NULL;
    }
    strcpy (name_copy, ((Product)product)->product_description);
    new_product->product_description = name_copy;
    return (ASElement)new_product; 
}




void freeProduct(ASElement product){
    if (product==NULL) {
        return;
    }
    free(((Product)product)->product_description);
    freeProductData(((Product)product)->custom_data);
    free ((Product)product);
}

int compareProduct (ASElement product_exist, ASElement product_to_add)
{
    return (((Product)product_exist)->product_id) - (((Product)product_exist)->product_id);
}
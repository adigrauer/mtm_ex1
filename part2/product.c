#include "amount_set.h"
#include "matamikya.h"

struct product_t {
    char* name;
    unsigned int product_id;
    double amount;
    MtmProductData custom_data;
    //need to implement
    MatamikyaAmountType amount_type;
    double profit;
    product_t* next;
    
};


struct mtmProductData_t {
    double price_for_quantity; 
}; 
 
ASElement copyProduct (ASElement product) {
    
}

ASElement freeProduct (ASElement product) {
    
}

ASElement compareProduct (ASElement product1,ASElement product2 ) {
    
}
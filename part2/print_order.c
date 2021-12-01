#include "set.h"
#include "amount_set.h"
#include "matamikya.h"
#include "orders.h"
#include "product.h"
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

MatamikyaResult mtmPrintOrder(Matamikya matamikya, const unsigned int orderId, FILE *output)
{
    if(checkIfOrdersNull(matamikya) == MATAMIKYA_NULL_ARGUMENT || output == NULL){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    if(checkIfOrderExistById(matamikya->orders, orderId) == false){
        return MATAMIKYA_ORDER_NOT_EXIST;
    }
    OrderInformation order = findOrderForChangeTotalPrice(matamikya->orders, orderId);
    calculateTotalPrcieOfOrder(matamikya, orderId);

    mtmPrintOrderSummary((order->total_price), output);
    return MATAMIKYA_SUCCESS;
}

///////////static
void calculateTotalPrcieOfOrder(Matamikya matamikya, const unsigned int order_id)
{
    AmountSet current_order = findSpecificOrderInOrders(matamikya->orders, order_id);
    if(asGetSize(current_order) == 0){
        return;
    }
    unsigned int* ptr_product_id = (unsigned int*)asGetFirst(current_order);
    Product temp_product = NULL;
    OrderInformation temp_order = NULL;
    double amount = 0;
    while (ptr_product_id != NULL){
        asGetAmount(current_order, ASElement(ptr_product_id), &amount);
        temp_product = getProductInStorage(matamikya->storage, *ptr_product_id);
        temp_order = findOrderForChangeTotalPrice(matamikya->orders, order_id);
        (temp_order->total_price) += (temp_product->price_function)(temp_product->custom_data, amount);
    }
}

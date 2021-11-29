#include "set.h"
#include "amount_set.h"
#include "matamikya.h"
#include "orders.h"
#include "product.h"
#include "util.h"
#include <stdlib.h>
#include <stdio.h>

//structs implementation 
////////////////////////////////////////////////
struct Matamikya_t{
   AmountSet storage;
   Set orders; 
   unsigned int last_orders_id;
};
/////////////////////////////////////////////////

Matamikya matamikyaCreate()
{
   Matamikya new_warehouse = (Matamikya)malloc(sizeof(*new_warehouse));   //malloc!!! need to free 1
   if(new_warehouse == NULL){
      return NULL;
   }
   new_warehouse->storage = asCreate(copyProduct, freeProduct, compareProduct); //malloc!!! need to free 2
   if(new_warehouse->storage == NULL){
      free(new_warehouse);  //free 1 in case of error
      return NULL;
   }
   new_warehouse->orders = setCreate(copyOrder, freeOrder, compareOrder);  //malloc!!! need to free 3
   if(new_warehouse->orders == NULL){
      asDestroy(new_warehouse->storage); //free 2 in case of error
      free(new_warehouse);  //free 1 in case of error
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

unsigned int mtmCreateNewOrder(Matamikya matamikya)
{
   if(matamikya == NULL){
      return 0;
   }
   unsigned int new_order_id = matamikya->last_orders_id + 1;
   OrderInformation new_order = createNewEmptyOrder(new_order_id);
   if(new_order == NULL){
      return 0;
   }
   if(setAdd(matamikya->orders, new_order) == SET_SUCCESS){
      matamikya->last_orders_id = new_order_id;
      return new_order_id;
   }
}

MatamikyaResult mtmChangeProductAmountInOrder(Matamikya matamikya, const unsigned int order_id,
                  const unsigned int product_id, const double amount)
{
   /*if(cheack if the item exsit in storage){
      return MATAMIKYA_PRODUCT_NOT_EXIST;
   }*/
   if(matamikya == NULL){
      return MATAMIKYA_NULL_ARGUMENT;
   }
   if(checkIfOrderExistById(matamikya->orders, order_id) == false){
      return MATAMIKYA_ORDER_NOT_EXIST;
   }
   AmountSet ptr_order = findSpecificOrderInOrders(matamikya->orders, order_id);
   if(ptr_order == NULL){
      return MATAMIKYA_OUT_OF_MEMORY;
   }
   if(checkIfItemExistInOrderById(ptr_order, order_id) == false){
      return MATAMIKYA_PRODUCT_NOT_EXIST;
   }
   /*if(){ lottem function
      return MATAMIKYA_INVALID_AMOUNT;
   }*/
   unsigned int* temp_product_id = createNewIdForItemInOrder(product_id);
   double current_amount = 0;
   asGetAmount(ptr_order, temp_product_id, &current_amount);
   if(changeAmountOfItemInOrder(ptr_order, product_id, amount) == AS_INSUFFICIENT_AMOUNT || current_amount == 0){
      asDelete(ptr_order, temp_product_id);
      return MATAMIKYA_SUCCESS;
   }
   return MATAMIKYA_SUCCESS;
}

bool checkIfAmountInOrderValidForShipping(AmountSet items_in_order)
{
   
}

MatamikyaResult mtmShipOrder(Matamikya matamikya, const unsigned int order_id)
{
   if(matamikya == NULL){
      return MATAMIKYA_NULL_ARGUMENT;
   }
   if(checkIfOrderExistById(matamikya->orders, order_id) == false){
      return MATAMIKYA_ORDER_NOT_EXIST;
   }
   AmountSet items_in_order = findSpecificOrderInOrders(matamikya->orders, order_id);
   if(items_in_order == NULL){
      return MATAMIKYA_OUT_OF_MEMORY;
   }

   return MATAMIKYA_INSUFFICIENT_AMOUNT;
}

MatamikyaResult mtmCancelOrder(Matamikya matamikya, const unsigned int order_id)
{
   if(matamikya == NULL){
      return MATAMIKYA_NULL_ARGUMENT;
   }
   if(checkIfOrderExistById(matamikya->orders, order_id) == false){
      return MATAMIKYA_ORDER_NOT_EXIST;
   }
   OrderInformation temp_order = createNewEmptyOrder(order_id);
   if(temp_order == NULL){
      return MATAMIKYA_OUT_OF_MEMORY;
   }  
   setRemove(matamikya->orders, temp_order);
   return MATAMIKYA_SUCCESS;
}









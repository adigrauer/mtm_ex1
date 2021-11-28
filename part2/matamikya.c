#include "set.h"
#include "amount_set.h"
#include "matamikya.h"
#include "orders.h"
#include "product.h"
#include <stdlib.h>
#include <stdio.h>

//structs implementation 
////////////////////////////////////////////////
struct Matamikya_t{
   AmountSet storage;
   Set orders; 
};
/////////////////////////////////////////////////

Matamikya matamikyaCreate()
{
   Matamikya new_warehouse = (Matamikya)malloc(sizeof(*new_warehouse));   //malloc!!! need to free 1
   if(new_warehouse == NULL){
      return NULL;
   }
   new_warehouse->storage =/*need to change the functions*/ asCreate(copyElement, freeElement, compareElements); //malloc!!! need to free 2
   if(new_warehouse->storage == NULL){
      free(new_warehouse);  //free 1 in case of error
      return NULL;
   }
   new_warehouse->orders = setCreate(copyOrder, freeOrder, compareOrder);  //malloc!!! need to free 3
   if(new_warehouse->orders == NULL){
      asDestroy(new_warehouse->storage); //free 2 in case of error
      free(new_warehouse);  //free 1 in case of error
   }
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

MatamikyaResult mtmChangeProductAmountInOrder(Matamikya matamikya, const unsigned int order_id,
                  const unsigned int product_id, const double amount)
{
   if(matamikya == NULL){
      return MATAMIKYA_NULL_ARGUMENT;
   }
   if(checkIfOrderExistById(matamikya->orders, order_id) == false){
      return MATAMIKYA_ORDER_NOT_EXIST;
   }
   AmountSet ptr_order = findSpecificOrderInOrders (matamikya->orders, order_id);
   if(ptr_order == NULL){
      return MATAMIKYA_OUT_OF_MEMORY;
   }
   if(checkIfItemExistInOrderById(ptr_order, order_id) == false){
      return MATAMIKYA_PRODUCT_NOT_EXIST;
   }
   
}




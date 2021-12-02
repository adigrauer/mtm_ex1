#include <stdio.h>
#include <stdbool.h>
#include "product.h"
/*
int main () 
{
    printf ("*********Test_1***********\n");
    Product test_product= createProduct();
    Product copy = copyProduct(test_product);
    freeProduct(copy);
    freeProduct(test_product);
    printf ("test1 finished, check for leaks");
}

product.h
 for case that we will need to print all best selling
Product getBestSellingOfMinimalIdProduct (AmountSet storage);
Product getNextBestSelling (AmountSet storage, Product last_best_selling_printed); 

product.c
///for case that we will need to print all best selling by id order
Product getBestSellingOfMinimalIdProduct (AmountSet storage)
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

Product getNextBestSelling (AmountSet storage, Product last_best_selling_printed)
{
    Product ptr = (Product)asGetFirst(storage);
    int current_min_id = 0;
    Product current_min_id_product = NULL;
    while (ptr != NULL){
        if (ptr->profit < last_best_selling_printed->profit ||  ptr->product_id <= last_best_selling_printed->product_id){
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
    if (current_min_id == last_best_selling_printed-> product_id) {
        return NULL;
    }
    return current_min_id_product;
}

matamikya.c
/*
MatamikyaResult mtmPrintBestSelling(Matamikya matamikya, FILE *output) 
{
    if (checkIfStorageNull(matamikya) == MATAMIKYA_NULL_ARGUMENT || output == NULL){
        return MATAMIKYA_NULL_ARGUMENT;
    }
    Product best_min_selling_product = getBestSellingOfMinimalIdProduct(matamikya->storage);
    double max_profit = getProductIncome(best_min_selling_product);
    if(max_profit == 0) {
        fprintf (output, "Best Selling Product:\nnone\n");
        return MATAMIKYA_SUCCESS;
    }
    fprintf (output, "Best Selling Product:\n");
    while(best_min_selling_product != NULL){
        mtmPrintIncomeLine(getProductName(best_min_selling_product), getProductId(best_min_selling_product), max_profit, output);
        best_min_selling_product = getNextBestSelling (matamikya->storage, best_min_selling_product);
    }
    return MATAMIKYA_SUCCESS;
}
*/
#include <stdio.h>
#include <stdbool.h>
#include "product.h"

int main () 
{
    printf ("*********Test_1***********\n");
    Product test_product= createProduct();
    Product copy = copyProduct(test_product);
    freeProduct(copy);
    freeProduct(test_product);
    printf ("test1 finished, check for leaks");
}
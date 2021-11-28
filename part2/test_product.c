#include <stdio.h>
#include <stdbool.h>
#include "product.h"

int main () 
{
    printf ("*********Test_1***********");
    bool check=true;
    Product test_product= createProduct();
    Product copy = copyProduct(test_product);
    printf ("stop1");
    freeProduct(copy);
    printf ("stop2");
    freeProduct(test_product);
    printf ("are there any leaks?");
}
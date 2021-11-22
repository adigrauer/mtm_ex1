#include "amount_set_str.h"
#include "amount_set_str_tests.h"
#include <stdbool.h>

//tests for asCreate
bool test1()
{
    AmountSet new_set = asCreate();
    if (asGetFirst(new_set) != NULL)
        return false;
    return true;
}



int main()
{
    return 0;
}
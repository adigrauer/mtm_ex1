#ifndef AMOUNT_SET_STR_TESTS_H_
#define AMOUNT_SET_STR_TESTS_H_


#define RUN_TEST(test) \
do{ \
    printf("Running "#test"... "); \
    if(test()) { \
        printf("[OK]"); \
    } \
    printf("\n"); \
}while(0)

#endif  /* AMOUNT_SET_STR_TESTS_H_ */

CC = gcc
EXE_MATAMIKYA = matamikya
EXE_AMOUNT_SET_STR = amount_set_str
OBJS_MATAMIKYA = matamikya_orders.o matamikya_product.o matamikya.o matamikya_print.o
TEST_OBJS_MATAMIKYA = tests/matamikya_main.o tests/matamikya_tests.o
OBJS_AMOUNT_SET_STR = amount_set_str.o
TEST_OBJS_AMOUNT_SET_STR = tests/amount_set_str_main.o
DEBUG_FLAG = -g
CFLAGS = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG $(DEBUG_FLAG)
LIB = -L. -lmtm -lm -las

$(EXE_MATAMIKYA): $(OBJS_MATAMIKYA) $(TEST_OBJS_MATAMIKYA)
	$(CC) $(CFLAGS) $(OBJS_MATAMIKYA) $(TEST_OBJS_MATAMIKYA) $(LIB) -o $(EXE_MATAMIKYA) 
    
matamikya_orders.o: matamikya_orders.c set.h amount_set.h \
	matamikya_orders.h
matamikya_product.o: matamikya_product.c amount_set.h matamikya.h \
	matamikya_product.h 
matamikya.o: matamikya.c matamikya_print.h set.h amount_set.h matamikya.h \
	matamikya_orders.h matamikya_product.h
matamikya_print.o: matamikya_print.c matamikya_print.h
tests/matamikya_tests.o: tests/matamikya_tests.c tests/matamikya_tests.h tests/test_utilities.h matamikya.h
tests/matamikya_main.o: tests/matamikya_main.c tests/matamikya_tests.h tests/test_utilities.h

$(EXE_AMOUNT_SET_STR): $(OBJS_AMOUNT_SET_STR) $(TEST_OBJS_AMOUNT_SET_STR)
	$(CC) $(CFLAGS) $(OBJS_AMOUNT_SET_STR) $(TEST_OBJS_AMOUNT_SET_STR) -o $(EXE_AMOUNT_SET_STR) 

amount_set_str.o: amount_set_str.c amount_set_str.h
tests/amount_set_str_main.o: tests/amount_set_str_main.c amount_set_str.h

clean:
	rm -f $(EXE_MATAMIKYA) $(OBJS_MATAMIKYA) $(TEST_OBJS_MATAMIKYA)	\
		$(EXE_AMOUNT_SET_STR) $(OBJS_AMOUNT_SET_STR) $(TEST_OBJS_AMOUNT_SET_STR)

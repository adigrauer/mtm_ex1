CC = gcc
EXE = matamikya
OBJS = matamikya_orders.o matamikya_product.o matamikya.o matamikya_print.o
TEST_OBJ = tests/matamikya_main.o tests/matamikya_tests.o
DEBUG_FLAG = -g
CFLAGS = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG $(DEBUG_FLAG)
LIB = -L. -lmtm -lm -las

$(EXE): $(OBJS) $(TEST_OBJ)
	$(CC) $(CFLAGS) $(OBJS) $(TEST_OBJ) $(LIB) -o $(EXE) 
    
matamikya_orders.o: matamikya_orders.c set.h amount_set.h \
	matamikya_orders.h
matamikya_product.o: matamikya_product.c amount_set.h matamikya.h \
	matamikya_product.h 
matamikya.o: matamikya.c matamikya_print.h set.h amount_set.h matamikya.h \
	matamikya_orders.h matamikya_product.h
matamikya_print.o: matamikya_print.c matamikya_print.h
tests/matamikya_tests.o: tests/matamikya_tests.c tests/matamikya_tests.h tests/test_utilities.h matamikya.h
tests/matamikya_main.o: tests/matamikya_main.c tests/matamikya_tests.h tests/test_utilities.h

clean:
	rm -f $(EXE) $(OBJS) $(TEST_OBJ) 

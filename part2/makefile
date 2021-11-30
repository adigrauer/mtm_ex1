CC = gcc
EXE = matamikya_exe
OBJS = orders.o product.o matamikya.o
TEST_OBJ = matamikya_main.o matamikya_tests.o
CFLAGS = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG
DEBUG_FLAG = -g 
LIB = -L. -lmtm -lm -las


$(EXE): $(OBJS) $(TEST_OBJ)
	$(CC) $(DEBUG_FLAG) $(CFLAGS) $(OBJS) $(TEST_OBJ) $(LIB) -o $(EXE) 
    
orders.o: orders.c orders.h util.h amount_set.h	\
			set.h 
	$(CC) -c $(DEBUG_FLAG) $(CFLAGS) orders.c orders.h util.h amount_set.h set.h
   
product.o: product.c product.h util.h  amount_set.h	\
			matamikya.h   
	$(CC) -c $(DEBUG_FLAG) $(CFLAGS) product.c product.h util.h  amount_set.h matamikya.h

matamikya.o: matamikya.c orders.h util.h amount_set.h product.h \
			matamikya.h set.h matamikya_print.c matamikya_print.h
	$(CC) -c $(DEBUG_FLAG) $(CFLAGS)  matamikya.c orders.h util.h amount_set.h product.h \
			matamikya.h set.h matamikya_print.c matamikya_print.h
	

matamikya_tests.o: tests/matamikya_tests.c tests/matamikya_tests.h tests/test_utilities.h
	$(CC) -c $(DEBUG_FLAG) $(CFLAGS) tests/matamikya_tests.c tests/matamikya_tests.h	\
			tests/test_utilities.h

matamikya_main.o: tests/matamikya_main.c tests/matamikya_tests.h tests/test_utilities.h
	$(CC) -c $(DEBUG_FLAG) $(CFLAGS) tests/matamikya_main.c tests/matamikya_tests.h	\
			tests/test_utilities.h

	
clean: 
	rm -f $(EXE) $(OBJS) $(TEST_OBJ) 

CC = gcc
EXE = matamikya_exe
OBJS = orders.o product.o matamikya.o
TEST_OBJ = matamikya_test.o // need to update a test
CFLAGS = -std=c99 -Wall -pedantic-errors -Werror -DNDEBUG
DEBUG_FLAG = -g 
LIB = -L. -lmtm -lm -las


$(EXE): $(OBJS) $(TEST_OBJ)
	$(CC) $(DEBUG_FLAG) $(CFLAGS) $(OBJS) $(TEST_OBJ) $(LIB) -o $(EXE)
    
orders.o: orders.c orders.h util.h amount_set.h	\
			set.h libmtm.a libas.a 
	$(CC) -c $(DEBUG_FLAG) $(CFLAGS) -o tournament.c \\last file change to what we changed
   
product.o: product.c product.h util.h  amount_set.h	\
			matamikya.h libas.a 
	$(CC) -c $(DEBUG_FLAG) $(CFLAGS) -o tournament.c

matamikya.o: orders.c orders.h util.h amount_set.h product.c product.h \
			matamikya.h set.h libmtm.a libas.a matamikya_print.c matamikya_print.h
	$(CC) -c $(DEBUG_FLAG) $(CFLAGS) -o game.c 
	

$(TEST_OBJ): tests/chessSystemTestsExample.c matamikya.h test_utilities.h
	$(CC) -c $(DEBUG_FLAG) $(CFLAGS) -o tests/chessSystemTestsExample.c
	
clean: 
	rm -f $(EXE) $(OBJS) $(TEST_OBJ) 

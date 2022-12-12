FILES := ./src/main.c ./include/return_codes.h ./src/dmatrix* ./include/dmatrix* ./include/sparsematrix* ./src/sparsematrix* ./include/d_array.h ./include/darray_methods* ./src/darray_methods* ./src/preprocess* ./include/preprocess.h ./src/preprocess.c
OBJS := app.o menu.o node_methods.o tree_methods.o string_t_methods.o preprocess.o balance_tree.o hash_meth.o# main.o dmatrix.o sparsematrix.o darray_methods.o preprocess.o multiply_sm.o io.o
KEYS := gcc -std=gnu99 -Wall -Werror -Wpedantic
ifeq ($(mode), debug)
	KEYS += -g3 -Wvla -ggdb -O0 --coverage
endif

ifeq ($(mode), debug)
	KEYS += -g3
endif

app.exe: $(OBJS)
	$(KEYS) -Iinc -o $@ $^


hash: hash.exe
hash.exe: happ.o hash_meth.o node_methods.o tree_methods.o string_t_methods.o menu.o preprocess.o ./inc/*.h
	$(KEYS) -Iinc -o $@ $^


balance: bal.exe

bal.exe: ./src/balance_tree.c node_methods.o tree_methods.o string_t_methods.o ./inc/*.h
	$(KEYS) -Iinc -o $@ $^

%.o: ./src/%.c ./inc/*.h
	$(KEYS) -Iinc -c $<

.PHONY: clean memorcheck

memorcheck:
	/bin/valgrind --leak-check=full --leak-resolution=med --log-file=valgrind_out.txt --error-exitcode=4 ./app.exe

clean:
	$(RM) *.exe *.o *.gcno *.gcda

draw:
	#dot -Tpng tree1.gv -otree1.png
	#dot -Tpng tree_out.gv -otree_out.png
	dot -Tpng tree_with_letters_out.gv -otree_with_letters_out.png


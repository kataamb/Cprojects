FILES := ./src/main.c ./include/return_codes.h ./src/dmatrix* ./include/dmatrix* ./include/sparsematrix* ./src/sparsematrix* ./include/d_array.h ./include/darray_methods* ./src/darray_methods* ./src/preprocess* ./include/preprocess.h ./src/preprocess.c
OBJS := main.o graph_methods.o dfs.o
KEYS := gcc -std=gnu99 -Wall -Werror -Wpedantic
ifeq ($(mode), debug)
	KEYS += -g3 -Wvla -ggdb -O0 --coverage
endif

ifeq ($(mode), debug)
	KEYS += -g3
endif

app.exe: $(OBJS)
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
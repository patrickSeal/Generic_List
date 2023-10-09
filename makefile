BUILD = components
CC = gcc -g -Wall

test_list_gen: list_gen.o
	$(CC) src/TEST_list_gen.c $(BUILD)/list_gen.o -o bin/test_list_gen

list_gen.o:
	$(CC) -c src/list_gen.c -o $(BUILD)/list_gen.o

clean:
	rm bin/test_list_gen
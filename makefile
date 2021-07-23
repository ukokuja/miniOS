objects = OS.o Task.o queue.o mutex.o main.o

all: $(objects)
	gcc -pthread $(objects) -o main

%.o: %.c
	gcc -c $< -o $@


clean:
	rm *.o main logAction.csv

rebuild:
	clean all
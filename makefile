objects = OS/OS.o Task/Task.o Queue/queue.o Mutex/mutex.o main.o

all: $(objects)
	gcc -pthread $(objects) -o miniOS

%.o: %.c
	gcc -c $< -o $@


clean:
	rm *.o Queue/*.o OS/*.o Mutex/*.o Task/*.o miniOS logAction.csv

rebuild:
	clean all
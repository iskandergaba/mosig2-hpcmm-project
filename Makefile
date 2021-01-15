CC = gcc
CFLAGS = -O2 -fopenmp
LDFLAGS = -fopenmp

EXEC = 	main.run swarm_parallel.run

HEADER_FILES = $(wildcard *.h)

all: $(EXEC)

%.run: %.o sorting.o utils.o
	$(CC) $(LDFLAGS) -o $@ $^ -lm

%.o: %.c $(HEADER_FILES)
	$(CC) -c $(CONFIG_FLAGS) $(CFLAGS) $< -o $@ -lm

clean:
	rm -f $(EXEC) *.o *~

.PHONY: clean

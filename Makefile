CC = gcc
CFLAGS = -O2 -fopenmp
LDFLAGS = -fopenmp

EXEC = 	main.run

HEADER_FILES = $(wildcard *.h)

all: $(EXEC)

%.run: %.o sorting.o
	$(CC) $(LDFLAGS) -lm -o $@ $^

%.o: %.c $(HEADER_FILES)
	$(CC) -c $(CONFIG_FLAGS) $(CFLAGS) $< -lm -o $@

clean:
	rm -f $(EXEC) *.o *~

.PHONY: clean

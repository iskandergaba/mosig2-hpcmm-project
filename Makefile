CC = gcc
CFLAGS = -O2 -fopenmp
LDFLAGS = -fopenmp

EXEC = 	main.run

HEADER_FILES = $(wildcard *.h)

all: $(EXEC)

%.run: %.o
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c $(HEADER_FILES)
	$(CC) -c $(CONFIG_FLAGS) $(CFLAGS) $< -o $@

clean:
	rm -f $(EXEC) *.o *~

.PHONY: clean

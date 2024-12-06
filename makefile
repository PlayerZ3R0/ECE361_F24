# Compiler and flags
CC = gcc
CFLAGS = -std=c99 -Wall -Wextra

# Executable and object files
EXEC = app.exe
OBJS = app.o BST_ADT.o iom361_r2.o float_rndm.o

# Default target
all: $(EXEC)

# Linking the executable
$(EXEC): $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^

# Compiling object files
app.o: app.c app.h BST_ADT.h iom361_r2.h float_rndm.h
	$(CC) $(CFLAGS) -c app.c

BST_ADT.o: BST_ADT.c BST_ADT.h
	$(CC) $(CFLAGS) -c BST_ADT.c

iom361_r2.o: iom361_r2.c iom361_r2.h float_rndm.h
	$(CC) $(CFLAGS) -c iom361_r2.c

float_rndm.o: float_rndm.c float_rndm.h
	$(CC) $(CFLAGS) -c float_rndm.c

# Clean target to remove object files and executable
clean:
	rm -f $(OBJS) $(EXEC)

# Phony targets
.PHONY: all clean

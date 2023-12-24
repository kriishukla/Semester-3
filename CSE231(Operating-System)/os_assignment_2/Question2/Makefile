# learnt implementation from chat understood it propery and then used in our code 

CC = gcc
CFLAGS = -Wall -lrt

# Define the targets and their dependencies
all: FIFO_program RR_program OTHER_program policies

FIFO_program: FIFO_program.c
	$(CC) $(CFLAGS) -o FIFO_program FIFO_program.c

RR_program: RR_program.c
	$(CC) $(CFLAGS) -o RR_program RR_program.c

OTHER_program: OTHER_program.c
	$(CC) $(CFLAGS) -o OTHER_program OTHER_program.c

policies: policies.c
	$(CC) $(CFLAGS) -o policies policies.c

# Define a clean target to remove compiled files
clean:
	rm -f FIFO_program RR_program OTHER_program policies

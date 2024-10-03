C_SRC = printk.c
OBJ = $(C_SRC:.c=.o)

all: $(OBJ)

%.o: %.c
	$(GCC) $(CFLAG) -c $< 

clean:
	rm -f $(OBJ)

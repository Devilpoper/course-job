TARGET = cw
CC = gcc

CORE = ./core/
HEADER = ./headers/
BIN = ./bin/

CFLAGS = -Wall -std=gnu99 -I$(HEADER)

SRC = $(wildcard $(CORE)*.c)
OBJ = $(patsubst $(CORE)%.c, $(BIN)%.o, $(SRC))

all : create_bin_folder $(TARGET)

$(TARGET) : $(OBJ)
	@$(CC) $(CFLAGS) $^ -o $@

$(BIN)%.o : $(CORE)%.c 
	@$(CC) $(CFLAGS) -c $< -o $@

create_bin_folder :
	@mkdir -p $(BIN)

clean:
	@rm $(TARGET)
	@rm -rf $(BIN)
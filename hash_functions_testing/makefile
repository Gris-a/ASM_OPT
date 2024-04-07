OBJ_DIR = obj
SRC_DIR = source
INC_DIR = include

all: dirs scripts/hash.out

dirs:
	@mkdir -p $(OBJ_DIR)

scripts/hash.out: $(OBJ_DIR)/tester.o $(OBJ_DIR)/hash_table.o $(OBJ_DIR)/hash_functions.o
	@gcc -flto $^ -o $@

$(OBJ_DIR)/tester.o: $(SRC_DIR)/tester.c $(INC_DIR)/hash_table.h $(INC_DIR)/hash_functions.h
	@gcc -c -O3 $< -o $@

$(OBJ_DIR)/hash_table.o: $(SRC_DIR)/hash_table.c $(INC_DIR)/hash_table.h
	@gcc -c -O3 $< -o $@

$(OBJ_DIR)/hash_functions.o: $(SRC_DIR)/hash_functions.c $(INC_DIR)/hash_functions.h
	@gcc -c -O3 $< -o $@
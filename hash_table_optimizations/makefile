OBJ_DIR = obj
SRC_DIR = source
INC_DIR = include

all: dirs scripts/no_opt.out scripts/opt1.out scripts/opt2.out

dirs:
	@mkdir -p $(OBJ_DIR)

scripts/no_opt.out: $(OBJ_DIR)/tester.o $(OBJ_DIR)/hash_table.o
	@gcc -no-pie -lc $^ -o $@

scripts/opt1.out: $(OBJ_DIR)/tester.o $(OBJ_DIR)/hash_table_opt1.o $(OBJ_DIR)/crc32.o
	@gcc -no-pie -lc $^ -o $@

scripts/opt2.out: $(OBJ_DIR)/tester.o $(OBJ_DIR)/hash_table_opt2.o $(OBJ_DIR)/crc32.o
	@gcc -no-pie -lc $^ -o $@

$(OBJ_DIR)/tester.o: $(SRC_DIR)/tester.c $(INC_DIR)/hash_table.h
	@gcc -c -O1 $< -o $@

$(OBJ_DIR)/hash_table.o: $(SRC_DIR)/hash_table.c $(INC_DIR)/hash_table.h
	@gcc -c -O1 $< -o $@

$(OBJ_DIR)/hash_table_opt1.o: $(SRC_DIR)/hash_table_opt1.c $(INC_DIR)/hash_table.h
	@gcc -c -O1 $< -o $@

$(OBJ_DIR)/hash_table_opt2.o: $(SRC_DIR)/hash_table_opt2.c $(INC_DIR)/hash_table.h
	@gcc -c -O1 $< -o $@

$(OBJ_DIR)/crc32.o: $(SRC_DIR)/crc32.asm
	@nasm -felf64 $< -o $@
OBJ_DIR = obj
SRC_DIR = source
INC_DIR = include

LINK    = @gcc -no-pie -lc -flto
COMPILE = @gcc -DNDEBUG -c -O3 -mavx2

all: dirs scripts/no_opt.out scripts/opt1.out scripts/opt2.out scripts/opt3.out

dirs:
	@mkdir -p $(OBJ_DIR)

scripts/no_opt.out: $(OBJ_DIR)/tester.o $(OBJ_DIR)/hash_table.o
	$(LINK) $^ -o $@

scripts/opt1.out: $(OBJ_DIR)/tester.o $(OBJ_DIR)/hash_table_opt1.o $(OBJ_DIR)/crc32.o
	$(LINK) $^ -o $@

scripts/opt2.out: $(OBJ_DIR)/tester.o $(OBJ_DIR)/hash_table_opt2.o
	$(LINK) $^ -o $@

scripts/opt3.out: $(OBJ_DIR)/tester_opt3.o $(OBJ_DIR)/hash_table_opt3.o $(OBJ_DIR)/HashTableFind.o
	$(LINK) $^ -o $@

$(OBJ_DIR)/tester.o: $(SRC_DIR)/tester.c $(INC_DIR)/hash_table.h
	$(COMPILE) $< -o $@

$(OBJ_DIR)/tester_opt3.o: $(SRC_DIR)/tester.c $(INC_DIR)/hash_table_opt3.h
	$(COMPILE) -DOPT3 $< -o $@

$(OBJ_DIR)/hash_table.o: $(SRC_DIR)/hash_table.c $(INC_DIR)/hash_table.h
	$(COMPILE) $< -o $@

$(OBJ_DIR)/hash_table_opt1.o: $(SRC_DIR)/hash_table_opt1.c $(INC_DIR)/hash_table.h
	$(COMPILE) $< -o $@

$(OBJ_DIR)/hash_table_opt2.o: $(SRC_DIR)/hash_table_opt2.c $(INC_DIR)/hash_table.h
	$(COMPILE) $< -o $@

$(OBJ_DIR)/hash_table_opt3.o: $(SRC_DIR)/hash_table_opt3.c $(INC_DIR)/hash_table_opt3.h
	$(COMPILE) $< -o $@

$(OBJ_DIR)/crc32.o: $(SRC_DIR)/crc32.asm
	@nasm -g -f elf64 $< -o $@

$(OBJ_DIR)/HashTableFind.o: $(SRC_DIR)/HashTableFind.asm
	@nasm -g -f elf64 $< -o $@
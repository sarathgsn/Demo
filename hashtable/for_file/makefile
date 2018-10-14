EXE = exe/
OBJ = obj/
vpath %.o obj
vpath %.c src
all: hashtable_without_collusion_using_Structures.o  count.o dispaly.o insert.o hash_function.o search.o
	gcc  -g -o $(EXE)app $(OBJ)*.o
%.o:%.c
	gcc -c $< -o $(OBJ)$@ 
clean:
	rm -f $(OBJ)*.o  
	rm -f $(EXE)app




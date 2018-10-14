EXE = exe/
OBJ = obj/
vpath %.o obj
vpath %.c src
all: main.o stack1.o stack2.o stack3.o towerof_hanoi.o
	gcc -o $(EXE)app $(OBJ)*.o
%.o:%.c
	gcc -c $< -o $(OBJ)$@ 
clean:
	rm -f $(OBJ)*.o  
	rm -f $(EXE)app




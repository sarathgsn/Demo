EXE = exe/
OBJ = obj/
vpath %.o obj
vpath %.c src
all: main.o insert.o pop.o push.o tower.o display.o
	gcc -o $(EXE)app $(OBJ)*.o
%.o:%.c
	gcc -c $< -o $(OBJ)$@ 
clean:
	rm -f $(OBJ)*.o  
	rm -f $(EXE)app




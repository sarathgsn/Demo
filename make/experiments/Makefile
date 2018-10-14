objects := *.o

include config
hello:$(objects)
	$(CC) -o $@ $(objects)
	@echo "hello wordl"

main.o:$(FILE)
	gcc -c $(FILE)

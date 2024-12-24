snake:fonction_Nishimwe.c fonction_Nishimwe.h main_Nishimwe.c
	gcc -o snake fonction_Nishimwe.c main_Nishimwe.c -g -O0 -lm -lpthread -fopenmp -lSDL2 -lSDL2_image -lSDL2_ttf

run:snake
	./snake 
run_valgrind:snake
	valgrind  --tool=memcheck --leak-check=yes --leak-resolution=low --show-reachable=yes  ./snake
clean:
	rm  snake

profile:
	gcc -Wall -pg fonction_Nishimwe.c main_Nishimwe.c -lm -lpthread -o snake

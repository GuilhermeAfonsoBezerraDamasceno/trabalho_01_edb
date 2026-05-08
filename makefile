compile: obj/main.o obj/models.o
	g++ -std=c++17 -o bin/main obj/main.o obj/models.o
	

obj/main.o: src/main.cpp include/models.h
	g++ -std=c++17 -c src/main.cpp -o obj/main.o
	clear

obj/models.o : src/models.cpp include/models.h 
	g++ -std=c++17 -c src/models.cpp -o obj/models.o
	clear

clean:
	rm -f bin/main obj/*o
	clear
	
exec: compile
	@bin/./main

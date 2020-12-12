spielplan: main.o konstellationen.o spielplan.o
	g++ main.o konstellationen.o spielplan.o -o spielplan
main.o: main.cpp spielplan.hpp
	g++ -c main.cpp
konstellation.o: konstellationen.cpp konstellationen.hpp 
	g++ -c konstellationen.cpp
spielplan.o: spielplan.cpp spielplan.hpp konstellationen.hpp
	g++ -c spielplan.cpp
clean:
	rm *.o spielplan
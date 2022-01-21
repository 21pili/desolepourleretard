CPP=g++ -std=c++20
RM=rm -f

graph : adjacent_matrix.o Arete.o adjacent_list.o Pile.o File.o main.o
	$(CPP) $^ -o $@

# vérifiez les dépendances
Arete.o : Arete.cpp Arete.h
adjacent_matrix.o : adjacent_matrix.cpp adjacent_matrix.h
adjacent_list.o : adjacent_list.cpp adjacent_list.h Arete.h adjacent_matrix.h
Pile.o : Pile.cpp Pile.h
File.o : File.cpp File.h
main.o : main.cpp adjacent_list.h Pile.h File.h

%.o:%.cpp
	$(CPP) -o $@ -c $<

clean:
	$(RM) *.o graph

.PHONY: clean

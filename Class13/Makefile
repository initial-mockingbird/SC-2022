EXEFOLDER=./Executables
FLAGS=-std=c++17
all: Example Recorridos Ciclos Wrestlers Paths
	echo "Done"
Example:
	g++ $(FLAGS) Example.cpp -o $(EXEFOLDER)/Example.sh
Recorridos:
	g++ $(FLAGS) Recorridos.cpp -o $(EXEFOLDER)/Recorridos.sh
Ciclos:
	g++ $(FLAGS) Ciclos.cpp -o $(EXEFOLDER)/Ciclos.sh
Wrestlers:
	g++ $(FLAGS) Wrestlers.cpp -o $(EXEFOLDER)/Wrestlers.sh
Paths:
	g++ $(FLAGS) Paths.cpp -o $(EXEFOLDER)/Paths.sh

.PHONY: clean
clean:
	rm $(EXEFOLDER)/*
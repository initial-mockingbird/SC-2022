EXEFOLDER=./Executables
FLAGS=-std=c++17
all: BellmanFord Dijkstra Network Flights
	echo "Done"
BellmanFord:
	g++ $(FLAGS) BellmanFord.cpp -o $(EXEFOLDER)/BellmanFord.sh
Dijkstra:
	g++ $(FLAGS) Dijkstra.cpp -o $(EXEFOLDER)/Dijkstra.sh
Network:
	g++ $(FLAGS) Network.cpp -o $(EXEFOLDER)/Network.sh
Flights:
	g++ $(FLAGS) Flights.cpp -o $(EXEFOLDER)/Flights.sh

.PHONY: clean
clean:
	rm $(EXEFOLDER)/*
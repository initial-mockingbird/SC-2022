EXEFOLDER=./Executables

all: a depth distance ejemplo inversion test treeSums
	echo "Done"
a:
	g++ aux.cpp -o $(EXEFOLDER)/aux.sh
depth:
	g++ Depth.cpp -o $(EXEFOLDER)/Depth.sh
distance:
	g++ Distance.cpp -o $(EXEFOLDER)/Distance.sh
ejemplo:
	g++ ejemplo.cpp -o $(EXEFOLDER)/ejemplo.sh
inversion:
	g++ Inversion.cpp -o $(EXEFOLDER)/Inversion.sh
test:
	g++ test.cpp -o $(EXEFOLDER)/test.sh
treeSums:
	g++ TreeSums.cpp -o $(EXEFOLDER)/TreeSums.sh



.PHONY: clean
clean:
	rm $(EXEFOLDER)/*
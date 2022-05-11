EXEFOLDER=./Executables
FLAGS=-std=c++17
all: RightSideView LCA LCA_BST Symmetric Thief
	echo "Done"
RightSideView:
	g++ $(FLAGS) RightSideView.cpp -o $(EXEFOLDER)/RightSideView.sh
LCA:
	g++ $(FLAGS) LCA.cpp -o $(EXEFOLDER)/LCA.sh
LCA_BST:
	g++ $(FLAGS) LCA_BST.cpp -o $(EXEFOLDER)/LCA_BST.sh
Symmetric:
	g++ $(FLAGS) Symmetric.cpp -o $(EXEFOLDER)/Symmetric.sh
Thief:
	g++ $(FLAGS) Thief.cpp -o $(EXEFOLDER)/Thief.sh

.PHONY: clean
clean:
	rm $(EXEFOLDER)/*
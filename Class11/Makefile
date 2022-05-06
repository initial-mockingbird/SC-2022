EXEFOLDER=./Executables

all: BST ValidatorBST FoldTree KSmall PreOrder
	echo "Done"
BST:
	g++ BST.cpp -o $(EXEFOLDER)/BST.sh
ValidatorBST:
	g++ ValidatorBST.cpp -o $(EXEFOLDER)/ValidatorBST.sh
FoldTree:
	g++ FoldTree.cpp -o $(EXEFOLDER)/FoldTree.sh
KSmall:
	g++ KSmall.cpp -o $(EXEFOLDER)/KSmall.sh
PreOrder:
	g++ PreOrder.cpp -o $(EXEFOLDER)/PreOrder.sh

.PHONY: clean
clean:
	rm $(EXEFOLDER)/*
output: main.o BlockStack.o
	g++ -std=c++17 main.o BlockStack.o -o blocksworld

main.o: main.cpp
	g++ -c main.cpp

BlockStack.o: BlockStack.cpp
	g++ -c BlockStack.cpp

clean:
	rm *.o blocksworld
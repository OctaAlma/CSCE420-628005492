output: main.o BlockStack.o
	g++ -std=c++11 main.o BlockStack.o -o blocksworld

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

BlockStack.o: BlockStack.cpp
	g++ -std=c++11 -c BlockStack.cpp

clean:
	rm *.o blocksworld

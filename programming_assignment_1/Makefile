output: blocksworld.o BlockStack.o
	g++ -std=c++11 blocksworld.o BlockStack.o -o blocksworld

blocksworld.o: blocksworld.cpp
	g++ -std=c++11 -c blocksworld.cpp

BlockStack.o: BlockStack.cpp
	g++ -std=c++11 -c BlockStack.cpp

clean:
	rm *.o blocksworld

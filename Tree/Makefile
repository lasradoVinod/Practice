SRC= binaryTree.cpp main.cpp

OBJS = $(patsubst %.cpp, %.o,$(SRC))

all: main

main:$(OBJS)
	g++ -o $@ $(OBJS)

%.o:%.cpp
	g++ -c $< -o $@

clean:
	rm *.o main
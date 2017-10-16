SRC= GraphArr.cpp main.cpp

OBJS = $(patsubst %.cpp, %.o,$(SRC))

all: main

main:$(OBJS)
	g++ -g -o $@ $(OBJS)

%.o:%.cpp
	g++ -g -c $< -o $@

clean:
	rm *.o main

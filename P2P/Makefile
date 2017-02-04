simple_server_objects = simple_server_main.o
simple_client_objects = simple_client_main.o

PROJECT_ROOT= $(shell pwd)

CXXFLAGS = -Wall -Wextra -g

SRC = 
INCDIR =
VPATH = .

OBJDIR = $(PROJECT_ROOT)/Build

#############   ADDING FILES RELATING TO SOCKET  #######################
-include $(PROJECT_ROOT)/Socket/mak/socket.mak
########################################################################

#############   ADDING GENERIC FILES ###################################
-include $(PROJECT_ROOT)/Generic/mak/generic.mak
########################################################################

OBJS = $(patsubst %.cpp,$(OBJDIR)/%.o,$(SRC))

INC  = $(patsubst %,-I%,$(INCDIR))

all: debug $(OBJDIR) $(OBJS) simple_server simple_client

$(OBJDIR):
	$(shell mkdir $(OBJDIR))
debug:
	@echo $(VPATH)
	@echo $(OBJS)
	@echo $(SRC)


simple_server: 
	g++ -o simple_server $(OBJS) $(INC) $(CXXFLAGS) simple_server_main.cpp


simple_client: 
	g++ -o simple_client $(OBJS)  $(INC) $(CXXFLAGS) simple_client_main.cpp

$(OBJDIR)/%.o: %.cpp
	g++ -c -o $@ $(CXXFLAGS) $(INC) $<

clean:
	rm -f $(OBJDIR)/*.o simple_server simple_client

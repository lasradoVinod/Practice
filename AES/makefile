#
#       !!!! Do NOT edit this makefile with an editor which replace tabs by spaces !!!!    
#
##############################################################################################
# 
# On command line:
#
# make all = Create project
#
# make clean = Clean project files.
#
# To rebuild project do "make clean" and "make all".
#

##############################################################################################
# Start of default section
# specify the path of toolchain before build
# Assuming GNU ARM tool chain path(GNU Tools ARM Embedded\4.8 2014q2\bin) is set in system environment variables 
TOOLCHAIN =
CXX   = $(TOOLCHAIN)g++
CC   = $(TOOLCHAIN)gcc
FILESIZE = $(TOOLCHAIN)size


#
# End of default section
##############################################################################################

##############################################################################################
# Start of user section
#

# 
# Define Debug mode, project name and Ram/Flash mode here
SRCDIR = src
OBJDIR=Build/Obj
EXECUTABLE = Build/Exe
FULL_TARGET_OUT= $(EXECUTABLE)/run.o
VPATH = $(SRCDIR)
# List C source files here
SRC  = AESUtils.c \
	lookUp.c
		
# List ASM source files here
ASRC = 

# List all user directories here
UINCDIR = inc
			
# List the user directory to look for the libraries here
ULIBS = 

# Define optimisation level here
OPT = -O0

STD = -std=c1x
			
CPFLAGS = $(OPT) $(STD) -g -Wall -Wconversion -Wextra 

CXXFLAGS = $(OPT) $(STD) -g -Wall -Wconversion -Wextra 

INCDIR  = $(patsubst %,-I%,$(UINCDIR))

OBJS = $(patsubst %.c,$(OBJDIR)/%.o,$(SRC))

# Generate dependency information
CPFLAGS += -MD -MP -MF .dep/$(@F).d

CXXFLAGS += -MD -MP -MF .dep/$(@F).d
#
# makefile rules
#

.PHONY: all
all: debug $(OBJDIR) $(OBJS) $(FULL_TARGET_OUT) 

debug:
	@echo $(FULL_TARGET_OUT)

$(OBJDIR):
	@mkdir -p $@
	@mkdir -p $(EXECUTABLE)
$(OBJDIR)/%.o : %.cpp
	$(CXX) -c $(CXXFLAGS) -I . $(INCDIR) $< -o $@

$(OBJDIR)/%.o : %.c
	$(CC) -c $(CPFLAGS) -I . $(INCDIR) $< -o $@

$(OBJDIR)/%.o : %.s
	$(CC) -c $(ASFLAGS) $< -o $@

$(FULL_TARGET_OUT) : $(OBJS)
	$(CC) $(CPFLAGS) -I . $(INCDIR) $(OBJS) -o $@


.PHONY: clean	
clean:
	-rm -f $(OBJS)
	-rm -rf $(OBJDIR)
	-rm -rf $(EXECUTABLE)
	-rm -fR .dep

# 
# Include the dependency files, should be the last of the makefile
#
-include $(shell mkdir .dep 2>/dev/null) $(wildcard .dep/*)

# *** EOF ***

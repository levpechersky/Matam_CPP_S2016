CC = g++
SRCS = *.cpp
HEADERS = $(subst .cpp,.hpp,$(SRCS)) 
OBJS = $(subst .cpp,.o,$(SRCS)) 
  
EXEC = ex4
DEBUG_FLAG = -g
RELEASE_FLAGS =# -Werror -pedantic-errors -DNDEBUG
CFLAGS = -std=c99 -Wall -pedantic  $(DEBUG_FLAG) $(RELEASE_FLAGS)

#Main app
$(EXEC): $(OBJS) main.o
	$(CC) -o $@ $^ $(CFLAGS) 

%.o : %.cpp
	$(CC) $(CFLAGS) -c $*.cpp 

#Misc commands:
.PHONY: clean
# *.exe is for windows, $(EXEC) is for linux
clean:
	rm -f *.o *.exe $(EXEC)
	
.PHONY: dependencies
dependencies:
	$(CC) -MM *.cpp 

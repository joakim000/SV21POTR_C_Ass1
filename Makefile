# $(info $(SHELL))
# $(info $(PATH))

.DELETE_ON_ERROR :

SRC = src/
TEST = test/
BUILD = build/
LIB = lib/buffer/
UNITY = lib/unity/

LFLAGS = 
ifdef PROF
CFLAGS = -std=c11 -O3 -pg -g
LFLAGS = -pg
else
ifdef DEBUG
CFLAGS = -std=c11 -O0 -g -DDEBUG
else
CFLAGS = -std=c11 -O3 
endif
endif

objects = $(BUILD)test_buffer.o $(BUILD)buffer.o $(BUILD)unity.o


test_buffer : $(objects)
	cc $(LFLAGS) -o bin/test_buffer $(objects)

# Buffer test 
$(BUILD)test_buffer.o : $(TEST)test_buffer.c $(LIB)buffer.h  
	cc -c $(CFLAGS) $(TEST)test_buffer.c -o $(@D)/test_buffer.o -I$(LIB) -I$(UNITY)	

# Buffer lib
$(BUILD)buffer.o : $(LIB)buffer.c $(LIB)buffer.h
	cc -c $(CFLAGS) $(LIB)buffer.c -o $(@D)/buffer.o -I$(LIB)

# Unity
$(BUILD)unity.o : $(UNITY)unity.c $(UNITY)unity.h
	cc -c $(CFLAGS) $(UNITY)unity.c -o $(@D)/unity.o -I$(UNITY)



.PHONY : debug
debug :
	$(MAKE) DEBUG=1

.PHONY : prof
prof :
	$(MAKE) PROF=1

.PHONY : clean
clean : 
	rm -f $(BUILD)*.o
	
.PHONY : winclean
winclean :
	powershell rm $(BUILD)*.o

.PHONY : superclean
superclean:
	rm -f $(BUILD)*.o
	rm -f test_buffer
	rm -f test_buffer.exe

#.PHONY : cleanportable
#cleanportable : 
#	$(info $(OS))
#ifeq ("$(OS)","Windows_NT")
#cleanportable ::
#	powershell rm $(BUILD)*.o
#else
#cleanportable ::
#	rm -f $(BUILD)*.o
#endif


# Notes

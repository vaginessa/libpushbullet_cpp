CC       = clang++
LD       = clang++


EXEC     = pb.test


DIR_SRC  = ./src
DIR_OBJ  = ./obj
DIR_DEP  = ./dep


$(shell mkdir -p $(DIR_DEP))
$(shell mkdir -p $(DIR_OBJ))


CFLAGS  += -W -Wall -Wextra -fmessage-length=0 -fPIC -Wno-unused-function
LDFLAGS += -lcurl -ljsoncpp -lboost_regex -lboost_log -lboost_log_setup -lboost_program_options


SRC      = $(shell find $(DIR_SRC) -name '*.cpp' | sort)
OBJ      = $(foreach var,$(notdir $(SRC:.cpp=.o)),$(DIR_OBJ)/$(var))
HDR     += $(shell find . -name '*.hpp' -exec dirname {} \;)
DEP      = $(shell find . -name '*.d')

INCLUDE_DIR = $(foreach var,$(shell echo $(HDR) | uniq),-I$(var))


# Which optimisation?
OPTIM   ?= DEBUG
ifeq ($(OPTIM),SIZE)
	CFLAGS   += -Os
else ifeq ($(OPTIM),SPEED)
	CFLAGS   += -Ofast
else ifeq ($(OPTIM),DEBUG)
	CFLAGS   += -g3 -O0 -D_DEBUG_
else ifeq ($(OPTIM),NONE)
	CFLAGS   +=
endif


# C++ 11 ?
CPP11  ?= 1
ifeq ($(CPP11),1)
	CFLAGS   += -D_CPP11_ -std=c++11
endif


# Include librairies directly in the program?
STATIC  ?= 0
ifeq ($(STATIC),1)
	CFLAGS   += -static
endif


# Verbosity
V            ?= 0
ifeq ($(V),1)
	VERBOSE	=
else
	VERBOSE = @
endif


# Look every source files in the directory SRC
vpath %.cpp $(DIR_SRC)


all: $(EXEC)


$(EXEC): $(OBJ)
	$(VERBOSE) echo "\t\033[1;37mLD\t$@\033[0m"
	$(VERBOSE) $(LD) $^ -o $@ $(LDFLAGS)


# Include of the makefiles generated in %.o
-include $(DEP)


# Create every objects files in the same directory of the sources
# Create the dependency files in dep/%i
$(DIR_OBJ)/%.o: %.cpp
	$(VERBOSE) $(CC) $<  $(CFLAGS) $(INCLUDE_DIR) -M -MT $@ -MF $(DIR_DEP)/$(notdir $(<:.cpp=.d))
	$(VERBOSE) echo "\t\033[1;33mCXX\t$<\033[0m"
	$(VERBOSE) $(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE_DIR)


# clean : clean all objects files
clean:
	$(VERBOSE) find $(DIR_OBJ) -type f -name '*.o' -delete


# distclean : clean all objects files and the executable
d: distclean
distclean: clean
	$(VERBOSE) find $(DIR_DEP) -type f -name '*.d' -delete
	$(VERBOSE) rm -rf $(DIR_DOC)/html $(DIR_DOC)/latex
	$(VERBOSE) rm -rf $(DIR_OBJ) $(DIR_DEP)
	$(VERBOSE) rm -f $(EXEC)


mrproper: distclean

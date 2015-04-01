CC       = clang++
LD       = clang++

EXEC       = pb
LIB_SHARED = ./lib/libpushbullet.so
LIB_STATIC = ./lib/libpushbullet.a


DIR_SRC   = ./src
DIR_OBJ   = ./obj
DIR_DEP   = ./dep
DIR_DOC   = ./doxygen
DIR_LIB   = ./lib
DIR_TESTS = ./tests

CONF_UNCRUSTIFY = ./cpp.cfg

INSTALL = $(shell which install) -c -m 644

$(shell mkdir -p $(DIR_DEP))
$(shell mkdir -p $(DIR_OBJ))
$(shell mkdir -p $(DIR_DOC))
$(shell mkdir -p $(DIR_LIB))


CFLAGS  += -W -Wall -Wextra -Wno-unused-function -fmessage-length=0 -fPIC -std=c++11 -DBOOST_LOG_DYN_LINK
LDFLAGS += -lcurl -ljsoncpp -lboost_regex -lpthread -lboost_log -lboost_thread -lboost_system -lboost_log_setup \
           -lboost_date_time -lboost_program_options


SRC      = $(shell find $(DIR_SRC) -name '*.cpp' | sort)
OBJ      = $(foreach var,$(notdir $(SRC:.cpp=.o)),$(DIR_OBJ)/$(var))
OBJ_LIB  = $(filter-out $(DIR_OBJ)/main.o, $(OBJ))
DIR_HDR  = $(foreach var,$(shell find . -name '*.hpp' -exec dirname {} \; | uniq),-I$(var))
DEP      = $(shell find . -name '*.d')


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


# Show Json Output ?
JSON  ?= 0
ifeq ($(JSON),1)
	CFLAGS   += -D_JSON_
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
	$(VERBOSE) echo "\t\033[1;35mLD\t$@\033[0m"
	$(VERBOSE) $(LD) $^ -o $@ $(LDFLAGS)


test:
	$(VERBOSE) $(MAKE) -C $(DIR_TESTS)


lib: $(LIB_SHARED) $(LIB_STATIC)


$(LIB_SHARED): $(OBJ_LIB)
	$(VERBOSE) echo "\t\033[1;35mSO\t$@\033[0m"
	$(VERBOSE) $(LD) -shared -o $@ $^  $(LDFLAGS)


$(LIB_STATIC): $(OBJ_LIB)
	$(VERBOSE) echo "\t\033[1;35mAR\t$@\033[0m"
	$(VERBOSE) ar rs $@ $^


# Include of the makefiles generated in %.o
-include $(DEP)


# Create every objects files in the same directory of the sources
# Create the dependency files in dep/%i
$(DIR_OBJ)/%.o: %.cpp
	$(VERBOSE) $(CC) $<  $(CFLAGS) $(DIR_HDR) -M -MT $@ -MF $(DIR_DEP)/$(notdir $(<:.cpp=.d))
	$(VERBOSE) echo "\t\033[1;32mCXX\t$<\033[0m"
	$(VERBOSE) $(CC) -c -o $@ $< $(CFLAGS) $(DIR_HDR)


# clean : clean all objects files
clean:
	$(VERBOSE) find $(DIR_OBJ) -type f -name '*.o' -delete


libclean:
	$(VERBOSE) rm -rf $(DIR_LIB)


# distclean : clean all objects files and the executable
d: distclean
distclean: clean libclean
	$(VERBOSE) find $(DIR_DEP) -type f -name '*.d' -delete
	$(VERBOSE) rm -rf $(DIR_DOC)/html $(DIR_DOC)/latex
	$(VERBOSE) rm -rf $(DIR_OBJ) $(DIR_DEP)
	$(VERBOSE) rm -f $(EXEC)
	$(VERBOSE) $(MAKE) -C $(DIR_TESTS) $@


mrproper: distclean


doxygen: $(SRC) $(HDR)
	$(VERBOSE) doxygen ./doxygen/Doxyfile


doxywizard: $(SRC) $(HDR)
	$(VERBOSE) doxywizard ./doxygen/Doxyfile

install: lib
	$(VERBOSE) for hpp in $(HDR)
	$(VERBOSE) do
		$(VERBOSE) $(INSTALL) $hpp $(DIR_INSTALL)/include/PushBullet
	$(VERBOSE) done 


# Display the help
help:
	$(VERBOSE) echo "Usage :"
	$(VERBOSE) echo "    $$ make [OPTIONS]"
	$(VERBOSE) echo ""
	$(VERBOSE) echo "Options available :"
	$(VERBOSE) echo "    OPTIM=NONE|DEBUG|SIZE|SPEED   (dft : DEBUG)"
	$(VERBOSE) echo "    STATIC=0|1                    (dft : 0)"
	$(VERBOSE) echo "    V=0|1                         (dft : 0)"


# Indent the files
indent:
	$(VERBOSE) find $(DIR_SRC) -type f -exec uncrustify -c $(CONF_UNCRUSTIFY) --no-backup --replace {} \;
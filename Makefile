CC       = clang++
LD       = clang++

EXEC       = pb
LIB_SHARED = libpushbullet.so
LIB_STATIC = libpushbullet.a


DIR_SRC   = ./src
DIR_OBJ   = ./obj
DIR_DEP   = ./dep
DIR_DOC   = ./doxygen
DIR_LIB   = ./lib
DIR_TESTS = ./tests


$(shell mkdir -p $(DIR_DEP))
$(shell mkdir -p $(DIR_OBJ))
$(shell mkdir -p $(DIR_DOC))
$(shell mkdir -p $(DIR_LIB))


CFLAGS  += -W -Wall -Wextra -fmessage-length=0 -fPIC
LDFLAGS += -lcurl -ljsoncpp -lboost_regex -lboost_log -lboost_log_setup -lboost_program_options


SRC      = $(shell find $(DIR_SRC) -name '*.cpp')
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
	$(VERBOSE) echo [LD] [$(OPTIM)]  $@
	$(VERBOSE) $(LD) $^ -o $@ $(LDFLAGS)


test:
	$(VERBOSE) $(MAKE) -C $(DIR_TESTS)


lib: $(LIB_SHARED) $(LIB_STATIC)


$(LIB_SHARED): $(DIR_OBJ)/PushBullet.o
	$(VERBOSE) echo   [SO] [$(OPTIM)]  $@
	$(VERBOSE) $(LD) -shared -o $(DIR_LIB)/$@ $<  $(LDFLAGS)


$(LIB_STATIC): $(DIR_OBJ)/PushBullet.o
	$(VERBOSE) echo   [AR] [$(OPTIM)]  $@
	$(VERBOSE) ar rs $(DIR_LIB)/$@ $< > /dev/null


# Include of the makefiles generated in %.o
-include $(DEP)


# Create every objects files in the same directory of the sources
# Create the dependency files in dep/%i
$(DIR_OBJ)/%.o: %.cpp
	$(VERBOSE) $(CC) $<  $(CFLAGS) $(INCLUDE_DIR) -M -MT $@ -MF $(DIR_DEP)/$(notdir $(<:.cpp=.d))
	$(VERBOSE) echo   [CC] [$(OPTIM)]  $<
	$(VERBOSE) $(CC) -c -o $@ $< $(CFLAGS) $(INCLUDE_DIR)


# clean : clean all objects files
clean:
	$(VERBOSE) find $(DIR_OBJ) -type f -name '*.o' -delete


# distclean : clean all objects files and the executable
d: distclean
distclean: clean
	$(VERBOSE) find $(DIR_DEP) -type f -name '*.d' -delete
	$(VERBOSE) rm -rf $(DIR_DOC)/html $(DIR_DOC)/latex
	$(VERBOSE) rm -rf $(DIR_OBJ) $(DIR_DEP) $(DIR_LIB)
	$(VERBOSE) rm -f $(EXEC)
	$(VERBOSE) $(MAKE) -C $(DIR_TESTS) $@


mrproper: distclean


doxygen: $(SRC) $(HDR)
	$(VERBOSE) doxygen ./doxygen/Doxyfile


doxywizard: $(SRC) $(HDR)
	$(VERBOSE) doxywizard ./doxygen/Doxyfile


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
	$(VERBOSE) indent \
	--blank-lines-after-declarations \
	--blank-lines-after-procedures \
	--blank-lines-before-block-comments \
	--no-blank-lines-after-commas \
	--braces-on-if-line \
	--braces-on-func-def-line \
	--braces-on-struct-decl-line \
	--case-indentation0 \
	--case-brace-indentation4 \
	--cuddle-do-while \
	--declaration-indentation8 \
	--dont-break-function-decl-args \
	--dont-break-function-decl-args-end \
	--dont-break-procedure-type \
	--dont-format-comments \
	--format-first-column-comments  \
	--dont-cuddle-else \
	--remove-preprocessor-space \
	--space-after-cast \
	--space-after-for \
	--space-after-if \
	--space-after-parentheses \
	--no-space-after-function-call-names \
	--no-space-after-parentheses \
	--space-after-while \
	--indent-level4 \
	--no-tabs \
	--line-length120 \
	--start-left-side-of-comments \
	--comment-indentation60 \
	--declaration-comment-column60 \
	--else-endif-column60 \
	$(DIR_SRC)/*
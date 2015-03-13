CC       = clang++
LD       = clang++

EXEC     = pushbullet


DIR_SRC = ./src
DIR_OBJ = ./obj
DIR_DEP = ./dep


$(shell mkdir -p $(DIR_DEP))
$(shell mkdir -p $(DIR_OBJ))


CFLAGS  += -W -Wall -Wextra -fmessage-length=0
LDFLAGS += -lcurl -ljsoncpp


SRC     = $(shell find $(DIR_SRC) -name '*.cpp')
OBJ     = $(foreach var,$(notdir $(SRC:.cpp=.o)),$(DIR_OBJ)/$(var))
HDR     += $(foreach var,$(shell find . -name '*.hpp' -exec dirname {} \; | uniq),-I$(var))
DEP     = $(shell find . -name '*.d')


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
	$(VERBOSE) echo [LD] [$(OPTIM)]  $(EXEC)
	$(VERBOSE) $(LD) $(OBJ) -o $(EXEC) $(LDFLAGS)

# Include of the makefiles generated in %.o
# -include $(DEP)


# Create every objects files in the same directory of the sources
# Create the dependency files in dep/%i
$(DIR_OBJ)/%.o: %.cpp
	$(VERBOSE) $(CC) $<  $(CFLAGS) $(HDR) -M -MT $@ -MF $(DIR_DEP)/$(notdir $(<:.cpp=.d))
	$(VERBOSE) echo   [CC] [$(OPTIM)]  $<
	$(VERBOSE) $(CC) -c -o $@ $< $(CFLAGS)


# clean : clean all objects files
clean:
	$(VERBOSE) find . -type f -name '*.o' -delete


# distclean : clean all objects files and the executable
distclean: clean
	$(VERBOSE) find . -type f -name '*.d' -delete
	$(VERBOSE) rm -rf $(EXEC)
	$(VERBOSE) rm -rf $(DIR_OBJ) $(DIR_DEP)


mrproper: distclean


# Launch the program
launch: all
	$(VERBOSE) ./$(EXEC)


# TODO: Implement the tests
# test:


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
	$(VERBOSE) rm `find . -name *~`

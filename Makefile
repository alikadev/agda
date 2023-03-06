# +===========================+
# | Author: Alikadev          |
# | Version: 0.1.2            |
# |                           |
# | (May only work in my PC)  |
# +===========================+

MAKEFLAGS += --no-print-directory


# Project specific
D_INC		:= 	include
D_BUILD		:=	build
D_DEBUG 	:=	debug
D_SRC 		:=	src

# Project specific sources
D_SRC_DEB	:=	$(D_SRC)/debug
D_SRC_APP	:=	$(D_SRC)/app
D_SRC_ANY	:=	$(D_SRC)/agda

# Compilator used
CC 			:= 	g++
LD 			:= 	g++

# Project building objects
OUT			:=	agda

CPPFLAGS	:=	-Ofast -std=c++11 -Wno-unused-command-line-argument -fshort-enums -I$(D_INC)
LDFLAGS		:=  

SRC 	:=	$(shell find $(D_SRC) -name '*.cpp')
OBJS	:=	$(subst $(D_SRC), $(D_BUILD), $(SRC:%.cpp=%.o))

# OS Specific
UNAME_S := $(shell uname -s)
ifeq ($(UNAME_S),Darwin)
	APP_CFLAGS+=-I/opt/homebrew/include
	APP_LDFLAGS+=-L/opt/homebrew/lib
endif
ifeq ($(UNAME_S),Linux)
	APP_CFLAGS+=
	APP_LDFLAGS+=
endif

# Implementation
default: $(OBJS) $(OUT)
all: clean $(OBJS) $(OUT)

help:
	@echo "List of command:"
	@echo "  all     | Clean and build to .a lib"
	@echo "  clean   | Clean"
	@echo "  help    | Print this"
	@echo "  $(OUT) = default"
	@exit 0

clean:
	@mkdir -p $(D_BUILD)
	@rm -rf $(D_BUILD)/*
	@rm -f $(OUT)

$(OUT): $(OBJS)
	@echo 
	@echo Linking app objects to $@
	@$(LD) $(LDFLAGS) -o $(OUT) $(OBJS)

$(D_BUILD)/%.o: $(D_SRC)/%.cpp
	@mkdir -p $(dir $@)
	@echo Building $< to $@
	@$(CC) $(CPPFLAGS) -c $< -o $@

BUILD_DIR = build
SRC_DIRS = src
OS = $(shell uname -s)
# INCLUDES = includes

CC = gcc
SRCS = $(shell find $(SRC_DIRS) -name '*.c') main.c
OBJS = $(SRCS:%=$(BUILD_DIR)/%.o)

ifeq ($(OS), Darwin)
    COMPILER_FLAGS=$(shell pkg-config --cflags sdl2 sdl2_image sdl2_ttf)
    COMPILER_FLAGS += -I/opt/homebrew/include #include for m1 mac
    LINKER_FLAGS=$(shell pkg-config --libs sdl2 sdl2_image sdl2_ttf)
	
    OBJ_NAME = projet_c
else
#CC specifies which compiler we're using

#COMPILER_FLAGS specifies the additional compilation options we're using
# -w suppresses all warnings
COMPILER_FLAGS = -Wall
#LINKER_FLAGS specifies the libraries we're linking against
LINKER_FLAGS = -lSDL2 -lSDL2_image -lSDL2_ttf
#OBJ_NAME specifies the name of our exectuable
OBJ_NAME = projet_c
endif


#This is the target that compiles our executable
# all : $(OBJS)
# 	$(CC) $(OBJS) $(COMPILER_FLAGS) $(LINKER_FLAGS) -o $(BUILD_DIR)/$(OBJ_NAME)

# The final build step.
$(BUILD_DIR)/$(OBJ_NAME): $(OBJS)
	$(CC) $(OBJS) $(COMPILER_FLAGS) $(INCLUDES) -o $@ $(LINKER_FLAGS)

# Build step for C source
$(BUILD_DIR)/%.c.o: %.c
	mkdir -p $(dir $@)
	$(CC) $(COMPILER_FLAGS) $(LINKER_FLAGS) -c $< -o $@

.PHONY: clean
clean:
	rm -r $(BUILD_DIR)

.PHONY: run
run:
	make && ./build/$(OBJ_NAME)
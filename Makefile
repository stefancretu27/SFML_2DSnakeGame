CC := g++
CFLAGS := -std=c++17 -g -Wall

SFML_INCLUDE_DIR = C:\SFML-2.5.1\include
LOCAL_INCLUDE_DIR = C:\Users\scretu\VisualCodeProjects\Snake_game\Include
LIBS_DIR := C:\SFML-2.5.1\lib
LIB_FILES := -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

SOURCE_DIR := Src
# use pattern rules, as % is a placeholder, to identify all .cpp files
SOURCE_FILES_PATTERN := $(SOURCE_DIR)/%.cpp
SRC_FILES = $(wildcard $(SOURCE_DIR)/*.cpp) $(wildcard $(SOURCE_DIR)/*/*.cpp)


OBJ_DIR := Obj
# use pattern rules, as % is a placeholder, to identify all .cpp files
OBJ_FILES_PATTERN := $(OBJ_DIR)/%.o
# patsubst stands for pattern substitution, with a replacement, in a given text. It has the generic syntax (pattern, replacement, text)
# below, for each .cpp file, it substitutes .cpp with .o, preserving the filename
OBJ_FILES := $(patsubst $(SOURCE_FILES_PATTERN), $(OBJ_FILES_PATTERN), $(SRC_FILES))

TARGET_EXE_NAME := Exe/snake.exe

# Format of a rule is target : prerequisites
#					  [tab] command
#
# which means that in order to build target, there are required prerequisites
#
# $@: the target filename.
# $*: the target filename without the file extension.
# $<: the first prerequisite filename.
# $^: the filenames of all the prerequisites, separated by spaces, discard duplicates.
# $+: similar to $^, but includes duplicates.
# $?: the names of all prerequisites that are newer than the target, separated by spaces.


all: $(TARGET_EXE_NAME)
	@echo Program compiled

#in order to build the executable, the required prerequisites are all .o files that can be obtained from all .cpp files
$(TARGET_EXE_NAME) : $(OBJ_FILES)
	@echo Linking
	$(CC) $(CFLAGS) $(OBJ_FILES) -o $@ -L$(LIBS_DIR) $(LIB_FILES)

#compile each *.cpp into a .o file, using pattern rules 
$(OBJ_FILES_PATTERN) : $(SOURCE_FILES_PATTERN)
	@echo $(SOURCE_DIR)
	@echo "Compiling: " $^
	$(CC) $(CFLAGS) -I$(SFML_INCLUDE_DIR) -I$(LOCAL_INCLUDE_DIR) -c $< -o $@

#use Win-cmd commands, not bash commands 
clean:
	del Exe\\*.exe
	del $(OBJ_DIR)\\*.o
	del $(OBJ_DIR)\\GameEngine\\*.o
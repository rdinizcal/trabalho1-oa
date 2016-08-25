SRC_PATH=../src
LIB_PATH=../lib
OUT_PATH=../
SOURCES=main.cpp memory.cpp crtMemory.cpp utils.cpp 
LIST_LIBRARIES=$(addprefix $(LIB_PATH)/,$(INCLUDES))
LIST_SOURCES=$(addprefix $(SRC_PATH)/,$(SOURCES))

CC=g++
CFLAGS=-ansi -Wall -std=c++0x

all:
	mkdir -p $(OUT_PATH)
	$(CC) ${CFLAGS} -I${LIB_PATH} ${LIST_SOURCES} -o $(OUT_PATH)main
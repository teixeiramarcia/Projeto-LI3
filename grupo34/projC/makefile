HEADERS = include
SRC = src
CC = gcc
SOURCES = $(wildcard $(SRC)/*.c)
BUILD_DIR = build
OBJ = $(foreach o, $(patsubst $(SRC)/%.c, %.o, $(SOURCES)), $(BUILD_DIR)/$o)
override CFLAGS += -Wall -pedantic -Werror=vla -std=c11 -D_POSIX_C_SOURCE -Werror=return-type

GLIB = `pkg-config --cflags glib-2.0` `pkg-config --libs glib-2.0`

FLAGS = -O0 -g

EXECUTABLE = prog

all: __make_build $(OBJ)
	$(CC) -I$(HEADERS) $(CFLAGS) $(OBJ) $(GLIB) -o $(BUILD_DIR)/$(EXECUTABLE) $(FLAGS)

$(BUILD_DIR)/%.o: $(SOURCES)
	$(CC) -I$(HEADERS) $(CFLAGS) $(patsubst %.o, %.c, $(patsubst $(BUILD_DIR)/%, $(SRC)/%, $@)) -c $(GLIB) -o $@ $(FLAGS)

__make_build:
	mkdir -p build

clean:
	rm -rf build

print-% : ; @echo $* = $($*)


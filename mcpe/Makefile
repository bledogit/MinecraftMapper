CC=g++
LEVELDB=../leveldb-mcpe
CFLAGS=-std=c++11 -DDLLX= -I $(LEVELDB)/include/ -c
LDFLAGS=-L $(LEVELDB)/out-static -lleveldb -lz -lzstd
SOURCES=mcpe.cpp McpeBlock.cpp McpeHandler.cpp
OBJECTS=$(SOURCES:.cpp=.o)
EXECUTABLE=mcpe

all: $(SOURCES) $(EXECUTABLE)

$(EXECUTABLE): $(OBJECTS) 
	$(CC) $(LDFLAGS) $(OBJECTS) -o $@

.cpp.o:
	$(CC) $(CFLAGS) $< -o $@

clean:
	rm -f *.o

test: $(EXECUTABLE)
	./mcpe map ~/Desktop/games/com.mojang/minecraftWorlds/test/db test.pnm

realclean: clean
	rm -f mcpe test.pnm


.PHONY: all clean get-deps test install uninstall self


INSTALL_PATH = /usr/bin/wolves
REQUIREMENTS = libsfml-dev
BIN = ./bin/main.bin

all: $(BIN)

self: .make/dependencies .make/make_self.py
		python3 .make/make_self.py

clean:
		rm -rf bin obj && mkdir bin obj
get-deps:
		apt-get update
		apt-get install $(REQUIREMENTS)
test: ./bin/main.bin
		./bin/main.bin
install: $(BIN)
		cp $(BIN) $(INSTALL_PATH)
uninstall:
		rm -f $(INSTALL_PATH)
./obj/logger.o: ./src/logger/logger.cpp ./inc/logger/logger.hpp
		g++ -c -o ./obj/logger.o ./src/logger/logger.cpp --std=c++11 -O2

./obj/random.o: ./src/tools/random.cpp ./inc/tools/random.hpp
		g++ -c -o ./obj/random.o ./src/tools/random.cpp --std=c++11 -O2

./obj/worldgen.o: ./src/tools/worldgen.cpp ./inc/tools/worldgen.hpp ./obj/logger.o ./obj/random.o
		g++ -c -o ./obj/worldgen.o ./src/tools/worldgen.cpp --std=c++11 -O2

./obj/world.o: ./src/models/world.cpp ./inc/models/world.hpp ./obj/worldgen.o ./obj/containers.o
		g++ -c -o ./obj/world.o ./src/models/world.cpp --std=c++11 -O2

./obj/ai.o: ./src/models/ai.cpp ./inc/models/ai.hpp ./obj/world.o
		g++ -c -o ./obj/ai.o ./src/models/ai.cpp --std=c++11 -O2

./obj/animals.o: ./src/models/animals.cpp ./inc/models/animals.hpp ./obj/world.o ./obj/containers.o ./obj/random.o ./obj/ai.o
		g++ -c -o ./obj/animals.o ./src/models/animals.cpp --std=c++11 -O2

./obj/containers.o: ./src/tools/containers.cpp ./inc/tools/containers.hpp
		g++ -c -o ./obj/containers.o ./src/tools/containers.cpp --std=c++11 -O2

./obj/algorythms.o: ./src/tools/algorythms.cpp ./inc/tools/algorythms.hpp
		g++ -c -o ./obj/algorythms.o ./src/tools/algorythms.cpp --std=c++11 -O2

./obj/graphics.o: ./src/graphics/graphics.cpp ./inc/graphics/graphics.hpp ./obj/logger.o ./obj/world.o ./obj/containers.o ./obj/algorythms.o ./obj/animals.o
		g++ -c -o ./obj/graphics.o ./src/graphics/graphics.cpp --std=c++11 -O2

./obj/main.o: ./src/./main.cpp ./inc/./main.hpp ./obj/logger.o ./obj/containers.o ./obj/graphics.o ./obj/animals.o
		g++ -c -o ./obj/main.o ./src/./main.cpp --std=c++11 -O2


$(BIN): ./obj/animals.o ./obj/graphics.o ./obj/main.o ./obj/world.o ./obj/worldgen.o ./obj/algorythms.o ./obj/containers.o ./obj/ai.o ./obj/random.o ./obj/logger.o
		g++ ./obj/animals.o ./obj/graphics.o ./obj/main.o ./obj/world.o ./obj/worldgen.o ./obj/algorythms.o ./obj/containers.o ./obj/ai.o ./obj/random.o ./obj/logger.o -o $(BIN) -lsfml-graphics -lsfml-window -lsfml-system
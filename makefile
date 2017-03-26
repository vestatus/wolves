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

./obj/hares.o: ./src/models/hares.cpp ./inc/models/hares.hpp ./inc/models/world.hpp
		g++ -c -o ./obj/hares.o ./src/models/hares.cpp --std=c++11 -O2

./obj/wolves.o: ./src/models/wolves.cpp ./inc/models/wolves.hpp
		g++ -c -o ./obj/wolves.o ./src/models/wolves.cpp --std=c++11 -O2

./obj/containers.o: ./src/tools/containers.cpp ./inc/tools/containers.hpp
		g++ -c -o ./obj/containers.o ./src/tools/containers.cpp --std=c++11 -O2

./obj/worldgen.o: ./src/tools/worldgen.cpp ./inc/tools/worldgen.hpp ./inc/logger/logger.hpp ./inc/tools/random.hpp
		g++ -c -o ./obj/worldgen.o ./src/tools/worldgen.cpp --std=c++11 -O2

./obj/world.o: ./src/models/world.cpp ./inc/models/world.hpp ./inc/tools/worldgen.hpp ./inc/tools/containers.hpp ./inc/tools/random.hpp
		g++ -c -o ./obj/world.o ./src/models/world.cpp --std=c++11 -O2

./obj/graphics.o: ./src/graphics/graphics.cpp ./inc/graphics/graphics.hpp ./inc/logger/logger.hpp ./inc/models/world.hpp ./inc/tools/containers.hpp ./inc/models/hares.hpp
		g++ -c -o ./obj/graphics.o ./src/graphics/graphics.cpp --std=c++11 -O2

./obj/main.o: ./src/./main.cpp ./inc/./main.hpp ./inc/logger/logger.hpp ./inc/tools/containers.hpp ./inc/graphics/graphics.hpp ./inc/models/hares.hpp ./inc/models/wolves.hpp
		g++ -c -o ./obj/main.o ./src/./main.cpp --std=c++11 -O2


$(BIN): ./obj/graphics.o ./obj/main.o ./obj/worldgen.o ./obj/wolves.o ./obj/world.o ./obj/containers.o ./obj/random.o ./obj/hares.o ./obj/logger.o
		g++ ./obj/graphics.o ./obj/main.o ./obj/worldgen.o ./obj/wolves.o ./obj/world.o ./obj/containers.o ./obj/random.o ./obj/hares.o ./obj/logger.o -o $(BIN) -lsfml-graphics -lsfml-window -lsfml-system
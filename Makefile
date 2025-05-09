CXX = g++ -g -std=c++20

LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: TD

TD: build/main.o build/game.o build/map.o build/texturemanager.o build/tile.o build/scoreboard.o
	$(CXX) $^ -o $@ $(LFLAGS)

build/main.o: src/main.cpp include/game.hpp include/map.hpp include/texturemanager.hpp include/tile.hpp include/constants.hpp
	$(CXX) -c $< -o $@

build/game.o: src/game.cpp include/game.hpp include/map.hpp include/tile.hpp include/texturemanager.hpp include/constants.hpp include/scoreboard.hpp
	$(CXX) -c $< -o $@

build/map.o: src/map.cpp include/texturemanager.hpp include/tile.hpp include/constants.hpp
	$(CXX) -c $< -o $@

build/texturemanager.o: src/texturemanager.cpp include/texturemanager.hpp
	$(CXX) -c $< -o $@ 

build/tile.o: src/tile.cpp include/tile.hpp include/constants.hpp
	$(CXX) -c $< -o $@

build/scoreboard.o: src/scoreboard.cpp include/scoreboard.hpp include/constants.hpp
	$(CXX) -c $< -o $@

.PHONY: all clean help

clean:
	rm -f build/*.o TD

help:
	@echo "Makefile for Tower Defense project"


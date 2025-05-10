CXX = g++ -g -std=c++20

LFLAGS = -lsfml-graphics -lsfml-window -lsfml-system

all: TD

TD: build/main.o build/game.o build/map.o build/texturemanager.o build/tile.o build/scoreboard.o build/balloon.o build/shop.o build/tower.o
	$(CXX) $^ -o $@ $(LFLAGS)

build/main.o: src/main.cpp include/game.hpp include/map.hpp include/texturemanager.hpp include/tile.hpp include/constants.hpp include/balloon.hpp
	$(CXX) -c $< -o $@

build/game.o: src/game.cpp include/game.hpp include/map.hpp include/tile.hpp include/texturemanager.hpp include/constants.hpp include/scoreboard.hpp include/balloon.hpp
	$(CXX) -c $< -o $@

build/map.o: src/map.cpp include/map.hpp include/texturemanager.hpp include/tile.hpp include/constants.hpp include/balloon.hpp
	$(CXX) -c $< -o $@

build/shop.o: src/shop.cpp include/shop.hpp include/tower.hpp include/texturemanager.hpp include/constants.hpp 
	$(CXX) -c $< -o $@ 

build/texturemanager.o: src/texturemanager.cpp include/texturemanager.hpp
	$(CXX) -c $< -o $@ 

build/tower.o: src/tower.cpp include/tower.hpp include/constants.hpp
	$(CXX) -c $< -o $@ 

build/tile.o: src/tile.cpp include/tile.hpp include/constants.hpp
	$(CXX) -c $< -o $@

build/scoreboard.o: src/scoreboard.cpp include/scoreboard.hpp include/constants.hpp
	$(CXX) -c $< -o $@

build/balloon.o: src/balloon.cpp include/balloon.hpp include/constants.hpp
	$(CXX) -c $< -o $@

.PHONY: all clean help

clean:
	rm -f build/*.o TD

help:
	@echo "Makefile for Tower Defense project"


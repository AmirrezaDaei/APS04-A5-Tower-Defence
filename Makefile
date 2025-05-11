OBJDIR = build
SRCDIR = src
INCDIR = include
ASSESTSDIR = asssets

CXX = g++ -std=c++20 -I./$(INCDIR)
FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

EXE = TD

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))


all: $(EXE)

$(EXE): $(OBJECTS)
	$(CXX) -o $@ $^ $(FLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp $(wildcard $(SRCDIR)/*.hpp)
	@mkdir -p $(OBJDIR)
	$(CXX) -c $< -o $@ -I./$(ASSESTSDIR)/



clean:
	rm -f $(OBJDIR)/*.o $(EXE)


.PHONY: all clean

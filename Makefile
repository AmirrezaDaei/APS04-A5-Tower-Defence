OBJDIR = build
SRCDIR = src
INCDIR = include

CXX = g++ -std=c++20 -I./$(INCDIR)
FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

EXE = TD

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))


all: $(OBJDIR) $(EXE)

$(OBJDIR):
	@mkdir -p $@

$(EXE): $(OBJECTS)
	$(CXX) -o $@ $^ $(FLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp 
	$(CXX) -c $< -o $@

clean:
	rm -f $(OBJDIR)/*.o $(EXE)


.PHONY: all clean

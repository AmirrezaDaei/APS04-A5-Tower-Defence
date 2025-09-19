OBJDIR = build
SRCDIR = src
INCDIR = include

CXX = g++ -std=c++20 -I./$(INCDIR)
FLAGS = -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

EXE = TD

FORMAT = clang-format -style=file -i

SOURCES := $(wildcard $(SRCDIR)/*.cpp)
HEADERS := $(wildcard $(INCDIR)/*.hpp)
OBJECTS := $(patsubst $(SRCDIR)/%.cpp, $(OBJDIR)/%.o, $(SOURCES))


all: $(OBJDIR) $(EXE)

$(OBJDIR):
	@mkdir -p $@

$(EXE): $(OBJECTS)
	$(CXX) -o $@ $^ $(FLAGS)

$(OBJDIR)/%.o: $(SRCDIR)/%.cpp 
	$(CXX) -c $< -o $@

format:
	$(FORMAT) $(SOURCES) $(HEADERS)


clean:
	rm -f $(OBJDIR)/*.o $(EXE)


.PHONY: all clean

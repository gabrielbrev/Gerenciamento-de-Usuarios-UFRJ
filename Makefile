TARGET = app

CXX = g++
CXXFLAGS = -std=c++11 -Wall -Wextra

SOURCES = user.cpp dataManager.cpp menu.cpp main.cpp
OBJECTS = $(SOURCES:.cpp=.o)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) $(OBJECTS) -o $(TARGET)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	rm -f $(OBJECTS) $(TARGET)

# Regra "phony" para evitar conflito com arquivos chamados "clean"
.PHONY: clean
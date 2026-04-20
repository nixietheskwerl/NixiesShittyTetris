CXX = g++
MOC = /usr/lib/qt6/moc
CXXFLAGS = -fdiagnostics-color=always -g -fPIC $(shell pkg-config --cflags Qt6Widgets)
LDFLAGS = $(shell pkg-config --libs Qt6Widgets)

SRCDIR = .
SOURCES = main.cpp engine.cpp gamewidget.cpp playfield.cpp tetromino.cpp
MOC_HEADERS = engine.h gamewidget.h
MOC_SOURCES = $(MOC_HEADERS:.h=.moc.cpp)
OBJECTS = $(SOURCES:.cpp=.o) $(MOC_SOURCES:.cpp=.o)
TARGET = tetris

all: $(TARGET)

$(TARGET): $(OBJECTS)
	$(CXX) $(CXXFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c -o $@ $<

%.moc.cpp: %.h
	$(MOC) $< -o $@

clean:
	rm -f $(OBJECTS) $(MOC_SOURCES) $(TARGET)

.PHONY: all clean

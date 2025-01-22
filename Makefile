# Compiler
CXX = g++
CXXFLAGS = -std=c++17 -I ./src/include

# Linker Flags
LDFLAGS = -L ./src/lib -lsfml-graphics -lsfml-window -lsfml-system -lsfml-audio

# Target
TARGET = main.exe

# Source Files
SRCS = Board.cpp \
       BoardView.cpp \
       Button.cpp \
       Game.cpp \
       GameOverState.cpp \
       InputHandler.cpp \
       main.cpp \
       MainMenu.cpp \
       PauseMenu.cpp \
       Piece.cpp \
       SidePanel.cpp \
       SoundMenu.cpp \
       SplashState.cpp

# Object Files
OBJS = $(SRCS:.cpp=.o)

# Build Rules
all: $(TARGET)

$(TARGET): $(OBJS)
	$(CXX) $(CXXFLAGS) $(OBJS) -o $(TARGET) $(LDFLAGS)

%.o: %.cpp
	$(CXX) $(CXXFLAGS) -c $< -o $@

clean:
	-@del /f /q $(OBJS) $(TARGET) 2>nul
	

# Makefile for chatbot_terminal
# Supports Linux, macOS, and Windows (MSYS2 UCRT64)

CXX := g++
CXXFLAGS := -std=c++17 -Wall -Wextra
LDFLAGS := -lcurl

# Output executable name
ifdef COMSPEC
	OUTPUT := chatbot_terminal.exe
else
	OUTPUT := chatbot_terminal
endif

.PHONY: all build clean help run

all: build

build: $(OUTPUT)

$(OUTPUT): src/main.cpp
	$(CXX) $(CXXFLAGS) src/main.cpp $(LDFLAGS) -o $(OUTPUT)

clean:
	rm -f $(OUTPUT)

run: build
	./$(OUTPUT)

help:
	@echo "Makefile targets:"
	@echo "  make build    - Compile the chatbot_terminal executable"
	@echo "  make clean    - Remove compiled executable"
	@echo "  make run      - Compile and run the chatbot"
	@echo "  make help     - Show this help message"

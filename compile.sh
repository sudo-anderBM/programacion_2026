#!/bin/bash
cd /c/Users/adria/Desktop/Api/chatbot_terminal
g++ -std=c++17 -Wall -Wextra src/main.cpp -lcurl -o chatbot_terminal.exe
echo "Compilation status: $?"

echo off
cls
echo Compilando...
g++ -Wall -o main main.cpp Panel.cpp Console.cpp Field.cpp Player.cpp
cls
echo Pronto
start main.lnk

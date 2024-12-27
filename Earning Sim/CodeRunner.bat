@echo off
color a
cd "\Users\anura\Desktop\Earning Sim\src"
g++ -o earningsim *.cpp -I ..\include
.\earningsim.exe
pause


#!/bin/bash

g++ -c ReadFile.cpp
g++ -c WriteFile.cpp
g++ -c Keyboard.cpp
g++ -c Matrix.cpp
g++ -c Poly.cpp
g++ -c Integer.cpp
g++ -c Double.cpp
g++ -c Permutation.cpp

ar -r libCSC2110.a *.o

set -euo pipefail

CXX=${CXX:-g++}
CXXFLAGS="-std=c++17 -O2 -Wall -Wextra -pedantic"
LIBS="-lraylib -lGL -lm -lpthread -ldl -lrt -lX11"

mkdir -p build

$CXX $CXXFLAGS -c functions.cpp -o build/functions.o
$CXX $CXXFLAGS -c main.cpp -o build/main.o

$CXX build/functions.o build/main.o $LIBS -o build/pong

echo "Built: build/pong"

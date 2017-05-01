all:
	clang++ -std=c++14 `libpng-config --ldflags` \
	-O2 -Wall -Wextra -Wno-unused-const-variable -D_GEANY -o main main.cpp -fopenmp -pthread

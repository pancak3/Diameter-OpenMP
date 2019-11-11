# Diameter-OpenMP
## Requirements
+ OpenMP
+ GCC
## Compile
```shell script
gcc -std=c99 headers/randomgraph.c -o bin/randomgraph
gcc -std=c99 graph-diameter.c -o bin/graph-diameter-sequential
gcc -std=c99 -fopenmp onePunch.c -o bin/graph-diameter-parallel
```
## Usage
Generate graph,
```shell script
./bin/randomgraph 2000 0.343 1000 7 > simple.in
```
Use sequential algorithm,
```shell script
user@machine $ ./bin/graph-diameter-sequential < simple.in
Diameter 42
Time: 55691460 us
```
Use parallel algorithm,
```shell script
user@machine $ ./bin/graph-diameter-parallel < simple.in
Diameter 42
Time: 34230955 us
```

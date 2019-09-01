# USAGE: bash test.sh <PROBLEM_SIZE>
PROBLEM_SIZE=$1
echo "PROBLEM_SIZE: $PROBLEM_SIZE"

# compile random generator
gcc util/randomgraph.c -o ../bin/randomgraph
# compile original solution
gcc -O2 graph-diameter.c -o ../bin/graph-diameter
# compile original solution with parallel for
gcc -O2 -fopenmp graph-diameter-parallel.c -o ../bin/graph-diameter-parallel
# compile original solution with parallel for (fixed)
gcc -O2 -fopenmp graph-diameter-floyd-parallel.c -o ../bin/graph-diameter-floyd-parallel
# compile dijkstra sequential solution
gcc -O2 graph-diameter-dijkstra.c util/dijkstra.c util/heap.c -o ../bin/graph-diameter-dijkstra
# compile dijkstra sequential solution
gcc -O2 -fopenmp graph-diameter-dijkstra-parallel.c util/dijkstra.c util/heap.c -o ../bin/graph-diameter-dijkstra-parallel

# compare
echo "=== DIJKSTRA SEQUENTIAL ==="
../bin/randomgraph $PROBLEM_SIZE 0.3 17 1.2 | ../bin/graph-diameter-dijkstra
echo "=== DIJKSTRA PARALLEL ==="
../bin/randomgraph $PROBLEM_SIZE 0.3 17 1.2 | ../bin/graph-diameter-dijkstra-parallel
echo "=== ORIGINAL SOLUTION + PARALLEL FOR (WRONG) ==="
../bin/randomgraph $PROBLEM_SIZE 0.3 17 1.2 | ../bin/graph-diameter-parallel
echo "=== ORIGINAL SOLUTION + PARALLEL FOR (FIXED) ==="
../bin/randomgraph $PROBLEM_SIZE 0.3 17 1.2 | ../bin/graph-diameter-floyd-parallel
echo "=== ORIGINAL SOLUTION ==="
../bin/randomgraph $PROBLEM_SIZE 0.3 17 1.2 | ../bin/graph-diameter

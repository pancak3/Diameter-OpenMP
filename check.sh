gcc headers/randomgraph.c -o randomgraph


problemSize=$1
maxWeight=233
echo "[*] problem size: $problemSize"
#./randomgraph $problemSize 0.3 $maxWeight 1
#echo ""
#echo "======== onePunch ======="
#gcc -fopenmp onePunch.c  -o onePunch
#./randomgraph $problemSize 0.3 $maxWeight 1|./onePunch

echo ""
echo "======== ours && parallel ======="
gcc -fopenmp graph-diameter.c -o graph-diameter
./randomgraph $problemSize 0.3 $maxWeight 1|./graph-diameter

echo ""
echo "======== origin && parallel ======="
gcc -fopenmp  graph-diameter-origin-parallel.c -o graph-diameter-origin-parallel
./randomgraph $problemSize 0.3 $maxWeight 1 |./graph-diameter-origin-parallel

echo ""
echo "========       origin       ======="
gcc graph-diameter-origin.c -o graph-diameter-origin
./randomgraph $problemSize 0.3 $maxWeight 1 |./graph-diameter-origin

echo ""
echo "========       v2 dijkstra       ======="
gcc -fopenmp graph-diameter-dijkstra-parallel.c  util/heap.c util/dijkstra.c -o graph-diameter-dijkstra-parallel
./randomgraph $problemSize 0.3 $maxWeight 1 |./graph-diameter-dijkstra-parallel


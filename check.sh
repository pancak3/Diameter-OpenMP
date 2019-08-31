PROBLEM_SIZE=$1
WEIGHT=133
PROB_EDGE=0.33
SEED=7


echo ""
echo "[******** onePunch ********]"
gcc -fopenmp onePunch.c  -o onePunch
./randomgraph $PROBLEM_SIZE $PROB_EDGE $WEIGHT $SEED|./onePunch

echo ""
echo "[******** origin ********]"
##./randomgraph 100 0.3 5 1
gcc -fopenmp graph-diameter.c  -o graph-diameter
./randomgraph $PROBLEM_SIZE $PROB_EDGE $WEIGHT $SEED |./graph-diameter

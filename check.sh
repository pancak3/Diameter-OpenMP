PROBLEM_SIZE=$1
WEIGHT=133
PROB_EDGE=0.33
SEED=7

gcc headers/randomgraph.c -o randomgraph
gcc graph-diameter.c -o graph-diameter
echo "+--------------------------------------+" >> test_log
echo "[*] problem size: $PROBLEM_SIZE" >> test_log
date +"     %A, %b %d, %Y %I:%M %p" >> test_log
echo "" >> test_log
echo "[******** onePunch ********]" >> test_log
gcc -fopenmp onePunch.c -o onePunch >> test_log >> test_log
./randomgraph $PROBLEM_SIZE $PROB_EDGE $WEIGHT $SEED | ./onePunch >> test_log

echo "" >> test_log
echo "[******** origin ********]" >> test_log
##./randomgraph 100 0.3 5 1
gcc -fopenmp graph-diameter.c -o graph-diameter >> test_log
./randomgraph $PROBLEM_SIZE $PROB_EDGE $WEIGHT $SEED | ./graph-diameter >> test_log

tail test_log

PROBLEM_SIZE=$1
WEIGHT=1000
PROB_EDGE=0.343
SEED=7

gcc -fopenmp getMaxThreads.c -o getMaxThreads
MAX_THREADS=$(./getMaxThreads)

gcc headers/randomgraph.c -o randomgraph
gcc graph-diameter.c -o graph-diameter
echo "+--------------------------------------+" >>test_log
git log | grep -E -m 1 "commit ([a-z0-9])+" >>test_log

echo "[*] problem size: $PROBLEM_SIZE, max threads: $MAX_THREADS" >>test_log
date +"     %A, %b %d, %Y %I:%M %p" >>test_log

echo "" >>test_log
echo "[******** onePunch ********]" >>test_log
gcc -fopenmp onePunch.c -o onePunch >>test_log >>test_log
./randomgraph $PROBLEM_SIZE $PROB_EDGE $WEIGHT $SEED | ./onePunch >>test_log

echo "" >>test_log
echo "[******** origin-parallel ********]" >>test_log
##./randomgraph 100 0.3 5 1
gcc -fopenmp graph-diameter-parallel.c -o graph-diameter-parallel >>test_log
./randomgraph $PROBLEM_SIZE $PROB_EDGE $WEIGHT $SEED | ./graph-diameter-parallel >>test_log


echo "" >>test_log
echo "[******** origin ********]" >>test_log
##./randomgraph 100 0.3 5 1
gcc -fopenmp graph-diameter.c -o graph-diameter >>test_log
./randomgraph $PROBLEM_SIZE $PROB_EDGE $WEIGHT $SEED | ./graph-diameter >>test_log

tail test_log -n 16

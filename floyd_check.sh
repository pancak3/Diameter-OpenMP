WEIGHT=10
PROB_EDGE=0.343
SEED=7

one_time_check() {
  PROBLEM_SIZE=$1

#  gcc -std=c99 -fopenmp getMaxThreads.c -o getMaxThreads
#  MAX_THREADS=$(./getMaxThreads)

  gcc -std=c99 headers/randomgraph.c -o randomgraph
  gcc -std=c99 graph-diameter.c -o graph-diameter

#  echo -e "$MAX_THREADS,\c" >>log.csv
#  echo -e "$PROBLEM_SIZE,\c" >>log.csv

  ## get diameter and time cost of onePunch
  gcc -std=c99 -fopenmp onePunch.c -o onePunch
  OUTPUT=$(./randomgraph $PROBLEM_SIZE $PROB_EDGE $WEIGHT $SEED |
    ./onePunch)
  echo -e "$OUTPUT <- Dijkstra Parallel\n"


  ## get diameter and time cost of Floyd's Parallel
  gcc -std=c99 -fopenmp FloydsParallel.c -o FloydsParallel
  OUTPUT=$(./randomgraph $PROBLEM_SIZE $PROB_EDGE $WEIGHT $SEED |
    ./FloydsParallel)
  echo -e "$OUTPUT <- Floyd's Parallel\n"

  ## write diameter
#  DIAMETER=$(echo $OUTPUT |
#    grep -Po "Diameter [0-9]+" -m 1 |
#    grep -Po "[0-9]+")
#  echo -e "$DIAMETER,\c" >>log.csv
  ## write time cost
#  TIME_COST=$(echo $OUTPUT |
#    grep -Po "Time: [0-9]+" -m 1 |
#    grep -Po "[0-9]+")
#  echo -e "$TIME_COST,\c" >>log.csv

  ## get diameter and time cost of graph-diameter-parallel
#  gcc -std=c99 -fopenmp graph-diameter-parallel.c -o graph-diameter-parallel
#  OUTPUT=$(./randomgraph $PROBLEM_SIZE $PROB_EDGE $WEIGHT $SEED |
#    ./graph-diameter-parallel)
#  echo $OUTPUT

  ## write diameter
#  DIAMETER=$(echo $OUTPUT |
#    grep -Po "Diameter [0-9]+" -m 1 |
#    grep -Po "[0-9]+")
#  echo -e "$DIAMETER,\c" >>log.csv
#  ## write time cost
#  TIME_COST=$(echo $OUTPUT |
#    grep -Po "Time: [0-9]+" -m 1 |
#    grep -Po "[0-9]+")
#  echo -e "$TIME_COST,\c" >>log.csv

  ## get diameter and time cost of graph-diameter
  gcc -std=c99 -fopenmp graph-diameter.c -o graph-diameter
  OUTPUT=$(./randomgraph $PROBLEM_SIZE $PROB_EDGE $WEIGHT $SEED |
    ./graph-diameter)
  echo -e "$OUTPUT <- Floyd\n"

  ## write diameter
#  DIAMETER=$(echo $OUTPUT |
#    grep -Po "Diameter [0-9]+" -m 1 |
#    grep -Po "[0-9]+")
#  echo -e "$DIAMETER,\c" >>log.csv
#  ## write time cost
#  TIME_COST=$(echo $OUTPUT |
#    grep -Po "Time: [0-9]+" -m 1 |
#    grep -Po "[0-9]+")
#  echo -e "$TIME_COST,\c" >>log.csv

  ## write \r\n to log
#  echo -e "\r" >>log.csv
}

if [ ! $1 ] || [ ! $2 ] || [ ! $3 ] || [ $1 -gt $2 ]; then
  echo -e "Usage:\r\n  check.sh \$problem_size_low \$problem_size_high \$problem_size_step\r\n"
  echo -e "Example:\r\n  check.sh 100 200 50\r\n"

else

  echo "[*] Problem size from $1 to $2 by step $3"

  echo "   +----------------------------------------+"
  for ((i = $1; i < $2 + 1; i += $3)); do
    echo "[*] Testing $i ... "
    one_time_check $i
    echo -e "[*] done.\r\n"
  done

fi

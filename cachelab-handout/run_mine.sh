make
printf "Test: yi.trace\n"
./csim -s 4 -E 2 -b 4 -t traces/yi.trace
./csim-ref -s 4 -E 2 -b 4 -t traces/yi.trace

printf "\nTest: yi.dave\n"
./csim -s 2 -E 1 -b 4 -t traces/dave.trace
./csim-ref -s 2 -E 1 -b 4 -t traces/dave.trace

printf "\nTest: yi.trans-2-1-3\n"
./csim -s 2 -E 1 -b 3 -t traces/trans.trace
./csim-ref -s 2 -E 1 -b 3 -t traces/trans.trace

printf "\nTest: yi.trans-2-2-3\n"
./csim -s 2 -E 2 -b 3 -t traces/trans.trace
./csim-ref -s 2 -E 2 -b 3 -t traces/trans.trace

printf "\nTest: yi.trans-2-4-3\n"
./csim -s 2 -E 4 -b 3 -t traces/trans.trace
./csim-ref -s 2 -E 4 -b 3 -t traces/trans.trace

printf "\nTest: yi.trans-5-1-5\n"
./csim -s 5 -E 1 -b 5 -t traces/trans.trace
./csim-ref -s 5 -E 1 -b 5 -t traces/trans.trace

printf "\nTest: yi.long-5-1-5\n"
./csim -s 5 -E 1 -b 5 -t traces/long.trace
./csim-ref -s 5 -E 1 -b 5 -t traces/long.trace
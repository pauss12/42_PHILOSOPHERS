#!/bin/sh

GREEN="\033[0;32m"
RED="\033[0;31m"
BLUE="\033[1;34m"
BROWN="\033[0;33m"
RESET="\033[0m"

run_awk_check() {
	condition="$1"

	awk -v red="$RED" -v green="$GREEN" -v reset="$RESET" "$condition"' {err=1}
	END {
		if (err)
			print red "\n" "❌ FAIL" reset "\n";
		else
			print green "\n" "✅ OK" reset "\n";
	}'
}

echo "${BROWN}Test 01: 2 800 200 200 10${RESET}"
./philo 2 800 200 200 10 | grep eating | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 < 10'

echo "${BROWN}Test 02: 1 800 200 200${RESET}"
./philo 1 800 200 200 10 | grep died | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 != 1'

echo "${BROWN}Test 03: 5 1000 200 200 7${RESET}"
./philo 5 1000 200 200 7 | grep eating | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 < 7'

echo "${BROWN}Test 04: 1 800 200 200 200${RESET}"
./philo 1 800 200 200 10 | grep died | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 != 1'

echo "${BROWN}Test 05: 5 800 200 200 30${RESET}"
./philo 5 800 200 200 30 | grep eating | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 < 30'

echo "${BROWN}Test 06: 5 800 200 200 7 ${RESET}"
./philo 5 800 200 200 7 | grep eating | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 < 7'

echo "${BROWN}Test 07: 4 410 200 200 200 ${RESET}"
./philo 4 410 200 200 200 | grep eating | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 < 200'

echo "${BROWN}Test 08: 4 310 200 100 ${RESET}"
./philo 4 310 200 100 | grep died | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 != 1'

echo "${BROWN}Test 09: 199 800 200 200 200 ${RESET}"
./philo 199 800 200 200 200 | grep eating | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 < 200'

echo "${BROWN}Test 10: 2 500 250 250 ${RESET}"
./philo 2 500 250 250 | grep died | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 != 1'

echo "${BROWN}Test 11: 2 500 299 201 ${RESET}"
./philo 2 500 299 201 | grep died | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 != 1'

echo "${BROWN}Test 12: 2 500 317 183 ${RESET}"
./philo 2 500 317 183 | grep died | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 != 1'

echo "${BROWN}Test 13: 200 1000 200 200 200 ${RESET}"
./philo 200 1000 200 200 200 | grep eating | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 < 200'

echo "${BROWN}Test 14: 200 1000 200 200 3 ${RESET}"
./philo 200 1000 200 200 3 | grep eating | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 < 3'

echo "${BROWN}Test 15: 2 1000 200 200 50 ${RESET}"
./philo 2 1000 200 200 50 | grep eating | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 < 50'

echo "${BROWN}Test 16: 5 1000 200 200 7 ${RESET}"
./philo 5 1000 200 200 7 | grep eating | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 < 7'

echo "${BROWN}Test 17: 4 610 200 100 10 ${RESET}"
./philo  4 610 200 100 10 | grep eating | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 < 10'

echo "${BROWN}Test 18: 5 1000 200 200 30 ${RESET}"
./philo 5 1000 200 200 30 | grep eating | cut -d' ' -f2 | sort | uniq -c | run_awk_check '$1 < 30'

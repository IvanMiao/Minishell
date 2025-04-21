#!/bin/bash

GREEN="\033[0;32m"
RED="\033[0;31m"
YELLOW="\033[0;33m"
BLUE="\033[0;34m"
CYAN="\033[0;36m"
BOLD="\033[1m"
RESET="\033[0m"

echo_test="echo"
pass_count=0
fail_count=0

echo -e "${BLUE}${BOLD}Test begin: echo${RESET}"
echo ""

while IFS= read -r line
do
    if [[ "$line" == "" || "$line" =~ ^### ]]; then
        continue
    fi

    rm -f .tmp.script .tmp.expected .tmp.actual
    # create file tmp
    echo "$line" | tr ';' '\n' > .tmp.script
    echo "exit" >> .tmp.script
    chmod +x .tmp.script

    # exec  minishell
    ./minishell < .tmp.script > .tmp.actual 2>&1
    sed -i '/^minishell\$/d;/^exit$/d' .tmp.actual
    sed -i 's/minishell\$ exit//g' .tmp.actual
    sed -i 's/^minishell: //g' .tmp.actual
    # cat .tmp.actual #debug

    # exec bash
    bash --posix < .tmp.script > .tmp.expected 2>&1
    sed -i 's/^bash: line [0-9]\+: //g' .tmp.expected
    # cat .tmp.expected # debug

    #  if [[ "$line" == *"-n"* || "$line" == *"|"* ]]; then
    #     echo "DEBUG - Testing special case: $line"
    #     echo "Expected hexdump:"
    #     hexdump -C .tmp.expected
    #     echo "Actual hexdump:"
    #     hexdump -C .tmp.actual
    # fi

    if diff -u ".tmp.actual" ".tmp.expected" > /dev/null; then
        echo -e "${GREEN}✅ $line: PASSED${RESET}"
        ((pass_count++))
    else
        echo -e "${RED}❌ $line: FAILED${RESET}"
        echo -e "${YELLOW}---- Testcase ----${RESET}"
        cat .tmp.script | grep -v "^exit"
        echo -e "${CYAN}** Expected **${RESET}"
        cat .tmp.expected
        echo -e "${CYAN}** Actual **${RESET}"
        cat .tmp.actual
        ((fail_count++))
    fi
done < "$echo_test"

echo -e "\n${BLUE}${BOLD}===== Result =====${RESET}"
total=$((pass_count + fail_count))
echo -e "${GREEN}Pass: $pass_count/$total${RESET}"
echo -e "${RED}Fail: $fail_count/$total${RESET}"

rm .tmp.*


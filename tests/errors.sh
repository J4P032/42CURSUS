#!/bin/bash

# colors:
C_RED='\033[0;31m'
C_YELLOW='\033[0;33m'
C_BLUE='\033[0;34m'
C_GREEN='\033[0;32m'
C_NC='\033[0m'

# =======================
# ======FUNCTIONS========

rnd_msg() {
    local msgs=("$@")
    local random_index=$(($((RANDOM % ${#msgs[@]}))))
    echo "${msgs[$random_index]}"
}

print_args() {
    local args=($@)
    if [ ${#args[@]} -gt 10 ]; then
        echo -ne "   ${args[@]:0:10} ..."
    else
        echo -ne "   ${args[@]}"
    fi
}

_p_error() { echo -e "\n\n${C_RED} ✘${C_NC} $1\n\n"; exit 2; }
_p_info() { echo -ne "${C_BLUE} ℹ${C_NC} $1"; }
_p_section() { echo -ne "・ $1:\t"; }
_p_ok() { echo -ne "${C_GREEN} ✔${C_NC} $1"; }
# =======================

rm -f push_swap.output.txt valgrind.logfile.txt

make -C ../
if [ $? -ne 0 ]; then
    _p_error "\n\nMake failed"
    exit 1
fi

clear
echo -e "\n${C_BLUE} Push Swap${C_NC}\n\ttest error tool by werodrig.\n\n\n"

# All error args
ARG_LIST=(
    "1 2 abc"
    " 1 2 4 3 1"
    "1111111111111111111111111111111"
    "-10 8 7 6 5 4 3 2 1 2147483647 2147483648"
    "-2147483649"
    ""
    "42"
)

for ARG in "${ARG_LIST[@]}"; do
    _p_info "Args to test:"
    print_args $ARG
    echo -e ""

    # Valgrind and leaks check
    _p_section "valgrind"
    valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose -s --log-file=valgrind.logfile.txt .././push_swap $ARG >./push_swap.output.txt 2>&1
    if grep -q "ERROR SUMMARY: [^0]" valgrind.logfile.txt; then
        VAL_MSG_KO=$(rnd_msg "Detected errors." "Oh no, byte babies are orphans now." "Leak hunting begins." "OMG leak before GTA Vl." "Valgrind doesn't like your code.")
        _p_error "${VAL_MSG_KO}\n   You can check ${C_YELLOW}•${C_NC} valgrind.logfile.txt\n   And also      ${C_YELLOW}•${C_NC} push_swap.output.txt"
    fi
    _p_ok



    # The 42 checker linux
    echo -e ""
    _p_section "checker"
    _MSG_CHLI=$(cat push_swap.output.txt | ./checker_linux $ARG 2>&1)
    if [ "$_MSG_CHLI" = "Error" ]; then
        if ! grep -q "^Error$" push_swap.output.txt; then
            _p_error "Your program didn't print Error.\n   You can check ${C_YELLOW}•${C_NC} push_swap.output.txt"
        fi
    elif [ "$_MSG_CHLI" = "" ]; then
        if [ -s push_swap.output.txt ]; then
            _p_error "Your program produced output.\n   You can check ${C_YELLOW}•${C_NC} push_swap.output.txt"
        fi
    elif [ "$_CHLI_MSG" = "KO" ]; then
        CHLI_MSG_KO=$(rnd_msg "Oops, checker doesnt like your answer." "Checker found an error." "(Crash sounds)*" "Debug Time!" "Please dont run this test again until you fixed your code..." "Unsorted?" "KO, Checker wins, FATALITY!!")
        _p_error "$CHLI_MSG_KO\n   You can check ${C_YELLOW}•${C_NC} push_swap.output.txt"
    fi
    _p_ok


    echo -e "\n"
done


# End of test
ALL_MSG_OK=$(rnd_msg "It looks ok!" "404: happy msg not found!" "Errors catched!... for now..." "OK OK OK" "werodrig is proudn't of you :)" "Nice job!" "OMG! no segfault" "All errors detected" "QA Developer eh?" "The last test is heavy?")
echo -e "\n"
_p_ok "${ALL_MSG_OK}"
underline=""
for ((i=0; i<${#ALL_MSG_OK}; i++)); do
    underline+="⎺"
done
echo -e "\n   ${underline}\n\n"
rm -f push_swap.output.txt valgrind.logfile.txt

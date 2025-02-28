#!/bin/bash

# colors:
C_RED='\033[0;31m'
C_YELLOW='\033[0;33m'
C_BLUE='\033[0;34m'
C_GREEN='\033[0;32m'
C_NC='\033[0m'

# =======================
# ======FUNCTIONS========
print_args() {
    local args=($@)
    if [ ${#args[@]} -gt 10 ]; then
        echo "${args[@]:0:10} ..."
    else
        echo "${args[@]}"
    fi
}

rnd_msg() {
    local msgs=("$@")
    local random_index=$(($((RANDOM % ${#msgs[@]}))))
    echo "${msgs[$random_index]}"
}

_p_error() { echo -e "\n${C_RED} ✘${C_NC} $1\n\n"; exit 2; }
_p_info() { echo -e "${C_BLUE} i${C_NC} $1"; }
_p_corner() { echo -ne "  » "; }
_p_ok() { echo -e "${C_GREEN} ✔${C_NC} $1\n"; }
_show_usage() {
    _p_info "Usage:"
    _p_corner; echo -e "--rnd <number_of_args>\tTest with randoms numbers"
    _p_corner; echo -e "--arg <args...>\t\tTest with custom numbers"
    _p_corner; echo -e "--help\t\t\tShow usage info"

    exit 0;
}
# =======================

rm -f push_swap.output.txt valgrind.logfile.txt

make -C ../
if [ $? -ne 0 ]; then
    _p_error "\n\nMake failed"
    exit 1
fi

clear
echo -e "\n${C_BLUE} Push Swap${C_NC}"
echo -e "\ttest tool by werodrig.\n\n\n"



# Args to do the test
if [ "$1" == "--help" ]; then
    _show_usage
elif [ "$1" == "--rnd" ]; then
    if [ -z $2 ]; then
        _p_error "You need to specify the number of arguments.\n  Example: ./test.sh --rnd <number_of_args>"
    fi

    ARG_N=$2
    if ! [[ $ARG_N =~ ^[0-9]+$ ]]; then
        _p_error "arg 2, <number_of_args> must be a number."
    fi
    ARG=$(python3 _rnd_numbers.py $ARG_N -2147483648 2147483647)
elif [ "$1" == "--arg" ]; then
    shift
    ARG=$@
    ARG_N=$#
else
    _show_usage
fi

_p_info "Args to test:"
_p_corner; print_args $ARG
_p_corner; echo -e "size: ${ARG_N}"
echo -e ""

# Valgrind and leaks check
VAL_MSG=$(rnd_msg "Using Valgrind" "What's say Valgrind?" "Do you have leaks?" "Did you remember free()?" "Malloc is easy... or not?" "Valgrind is working")
_p_info "${VAL_MSG}:"
valgrind --leak-check=full --show-leak-kinds=all --track-origins=yes --verbose -s --log-file=valgrind.logfile.txt .././push_swap $ARG >./push_swap.output.txt 2>&1
if grep -q "ERROR SUMMARY: [^0]" valgrind.logfile.txt; then
    VAL_MSG_KO=$(rnd_msg "Detected errors." "Oh no, byte babies are orphans now." "Leak hunting begins." "OMG leak before GTA Vl." "Valgrind doesn't like your code.")
    _p_error "${VAL_MSG_KO}\n   You can check ${C_YELLOW}•${C_NC} valgrind.logfile.txt\n   And also      ${C_YELLOW}•${C_NC} push_swap.output.txt"
fi
VAL_MSG_OK=$(rnd_msg "Amazing!" "Any byte alive!" "Perfect!, leaks are no problem for you." "What is a leak?" "You killed all leaks." "Valgrind can go to sleep now.")
_p_corner; _p_ok "${VAL_MSG_OK}"



# The 42 checker linux
_p_info "The 'checker_linux' say:"
_CHLI_MSG=$(cat push_swap.output.txt | ./checker_linux $ARG 2>&1)
_p_corner; echo -e "${_CHLI_MSG}"
if [ "$_CHLI_MSG" = "Error" ]; then
    if ! grep -q "^Error$" push_swap.output.txt; then
        _p_error "The checker_linux say 'Error' but the output is not 'Error'.\n   You can check ${C_YELLOW}•${C_NC} push_swap.output.txt"
    fi
elif [ "$_CHLI_MSG" = "" ]; then
    if [ -s push_swap.output.txt ]; then
            _p_error "Your program produced output.\n   You can check ${C_YELLOW}•${C_NC} push_swap.output.txt"
    fi
elif [ "$_CHLI_MSG" = "KO" ]; then
    CHLI_MSG_KO=$(rnd_msg "Oops, checker doesnt like your answer." "Checker found an error." "(Crash sounds)*" "Debug Time!" "Please dont run this test again until you fixed your code..." "Unsorted?" "KO, Checker wins, FATALITY!!")
    _p_error "$CHLI_MSG_KO\n   You can check ${C_YELLOW}•${C_NC} push_swap.output.txt"
fi
_CHLI_MSG_OK=$(rnd_msg "Nice!" "The checker, checked." "Cheated?" "Impeccable!" "It's ok!" "Well, if the checker says...")
_p_corner; _p_ok "${_CHLI_MSG_OK}"



# Counting moves
_steps=$(cat ./push_swap.output.txt | wc -l)
_p_info "Moves:"
formatted_steps=$(echo $_steps | sed ':a;s/\B[0-9]\{3\}\>/,&/;ta')
_p_corner; echo -e "${formatted_steps}"



# End of test
ALL_MSG_OK=$(rnd_msg "It looks nice!" "Very good!" "No errors!... for now..." "OK OK OK" "werodrig is proudn't of you :)" "Nice job!" "OMG! everything ok." "Do you follow midudev?")
echo -e "\n\n"
underline=""
for ((i=0; i<${#ALL_MSG_OK}; i++)); do
    underline+="⎺"
done
_p_ok "${ALL_MSG_OK}\n   ${underline}\n\n"

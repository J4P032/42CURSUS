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

_p_error() { echo -e "${C_RED} ✘${C_NC} $1\n\n"; exit 2; }
_p_info() { echo -e "${C_BLUE} i${C_NC} $1"; }
_p_corner() { echo -ne "  » "; }
_p_ok() { echo -e "${C_GREEN} ✔${C_NC} $1"; }
_log_file() { echo -e "$1" >> $LOGFILE; }
_show_usage() {
    _p_info "Usage:"
    _p_corner; echo -e ""
    echo -e "\t<stadistic_logfile_name>\tFilename of the output."
    echo -e "\t<number_of_rnd_args>\t\tCount of random args numbers given in each iteration."
    echo -e "\t<iterations>\t\t\tCount of iterations (100 is  nice)."
    _p_corner; echo -e "--help\t\t\t\tShow usage info."

    exit 0;
}
# =======================

make -C ../
if [ $? -ne 0 ]; then
    _p_error "\n\nMake failed"
    exit 1
fi

clear
echo -e "\n${C_BLUE} Push Swap${C_NC}"
echo -e "\tstadistic tool by werodrig.\n\n\n"

# Args to do the test
if [ "$1" == "--help" -o $# -ne 3 ]; then
    _show_usage
fi

ARG_N=$2
if ! [[ $ARG_N =~ ^[0-9]+$ ]]; then
    _p_error "arg 2, <number_of_args> must be a number."
fi

ITERATE=$3
if ! [[ $ITERATE =~ ^[0-9]+$ ]]; then
    _p_error "arg 3, <iterations> must be a number."
fi

DATE=$(date +%y_%m_%d)
LOGFILE="stats/${1}-A${ARG_N}-I${ITERATE}.txt"

if [ ! -d "stats" ]; then
    mkdir stats
fi
rm -f $LOGFILE


# Print info
_p_info "Arguments"
_p_corner; echo -e "Number of arguments: $ARG_N"
_p_corner; echo -e "Iterations: $ITERATE"
echo -e "\n"



# Var to store results
worst=0
best=0
average=0



# Run the tests
_p_info "Running"
echo -ne " [0%]"
ARG=$(python3 _rnd_numbers.py $ARG_N -2147483648 2147483647)
_moves=$(../push_swap $ARG | wc -l)
worst=$_moves
best=$_moves
move_sum=$_moves
for ((i=2; i<=ITERATE; i++)); do
    # Update progress
    if (( i % (ITERATE / 5) == 0 )); then
        echo -ne " [$((i * 100 / ITERATE))%]"
    fi

    # Run the program
    ARG=$(python3 _rnd_numbers.py $ARG_N -2147483648 2147483647)
    _moves=$(../push_swap $ARG | wc -l)

    # Update info
    if [ $_moves -gt $worst ]; then
        worst=$_moves
    fi

    if [ $_moves -lt $best ]; then
        best=$_moves
    fi

    move_sum=$((move_sum + _moves))
done



# Calculate average
average=$(($move_sum / $ITERATE))



# Print results
echo -e "\n\n"
_p_info "Results"
_p_corner; echo -e "Worst:\t$(printf "%'d" ${worst})"
_p_corner; echo -e "Best:\t$(printf "%'d" ${best})"
_p_corner; echo -e "Move sum:\t$(printf "%'d" ${move_sum})"
_p_corner; echo -e "Average:\t$(printf "%'.2f" ${average})"
echo -e "\n"



# Log stadistic
_log_file "Push Swap stadistic"
_log_file " Date: $DATE"
_log_file " Number of random arguments: $ARG_N"
_log_file " Number of iterations: $ITERATE"
_log_file ""
_log_file "Results:"
_log_file " Worst:\t$(printf "%'d" ${worst})"
_log_file " Best:\t$(printf "%'d" ${best})"
_log_file " Move sum:\t$(printf "%'d" ${move_sum})"
_log_file " Average:\t$(printf "%'.2f" ${average})"



# End of test
ALL_MSG_OK=$(rnd_msg "MMM interesing!" "Can you do it better?" "Used chatgpt or deepsek?" "NuMbErS dAtA mEtRiCsSsS" "werodrig do it better" "It works, right?" "What's next now?" "A lot of steps" "Visual info*")
echo -e "\n"
_p_ok "${ALL_MSG_OK}"
underline=""
for ((i=0; i<${#ALL_MSG_OK}; i++)); do
    underline+="⎺"
done
echo -e "   ${underline}\n\n"
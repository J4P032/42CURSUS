#!/bin/bash

# ===========================
# =      Documentation      =
# https:/man7:/.org/linux/man-pages/man1/pgrep.1.html
# https://commandmasters.com/commands/xdg-open-linux/
# https://commandmasters.com/commands/wmctrl-linux/
# https://stackoverflow.com/questions/2612274/bash-shell-scripting-detect-the-enter-key
# ===========================


# ===========================
# =          Color          =
__nc()      { echo -ne "\033[0m"; }
_red()      { echo -ne "\033[31m$1"$(__nc); }
_green()    { echo -ne "\033[32m$1"$(__nc); }
_yellow()   { echo -ne "\033[33m$1"$(__nc); }
_blue()     { echo -ne "\033[34m$1"$(__nc); }
# ===========================


# ===========================
# =         Congifs         =
HTML_FILENAME="view.html"
HTML_TITLE="PushSwap Viewer"
JS_FILENAME="viewer/_data.js"
PW_OUT_FILENAME="push_swap.output.txt"
ARG_N=0
ARG_N_MAX=100
ARG_N_MIN=1
CMDS_NAME=("pa" "pb" "ra" "rb" "rr" "rra" "rrb" "rrr" "sa" "sb" "ss")
CLRS_COUNT=8
# ===========================



# ===========================
# =        Functions        =
_ask_user_to_open() {
    echo -e "Do you want to $(_blue "open") the viewer in a new tab?"
    echo -e "Press $(_blue "enter") to open, don't press anything to cancel."
    read -s -N 1 -t 3 KEY
    echo -e "\n"

    if [[ "$KEY" == $'\x0a' ]]; then
        echo -e "$(_green "Opening") the viewer in a new tab..."
        xdg-open "viewer/$HTML_FILENAME" &> /dev/null
    else
        echo -e "Please $(_blue "open") or $(_blue "reaload") the page manually."
    fi
}

rnd_arg() {
    local n=$1
    seq -$n $n | shuf -n $n | tr '\n' ' '
}

_get_vari_index() {
    local value=$1
    local min=$2
    local max=$3
    local n=$4

    local index=$(( (value - min) * n / (max - min) ))
    if (( index >= n )); then
        index=$((n - 1))
    elif (( index < 0 )); then
        index=0
    fi

    echo -n "${index}"
}

check_true_command() {
    local cmd=$1

    for valid_cmd in "${CMDS_NAME[@]}"; do
        if [ "$cmd" == "$valid_cmd" ]; then
            return 0
        fi
    done
    return 1
}

_p_error() { echo -e "\n\n$(_red " ✘ ")$1\n\n"; exit 2; }
_p_info() { echo -e " $(_blue "i") $1"; }
_p_corner() { echo -ne "  » "; }

_log_file() { echo -ne "$1" >> $JS_FILENAME; }
_show_usage() {
    echo -e "\n"
    _p_info "Usage:"
    _p_corner; echo -e "--rnd <number_of_args(${ARG_N_MIN}-${ARG_N_MAX})>\tTest with randoms numbers"
    _p_corner; echo -e "--arg <args...>\t\t\tTest with custom numbers"
    _p_corner; echo -e "--help\t\t\t\tShow usage info\n\n"

    exit 0;
}
# ===========================



# Args to do the test
if [ "$1" == "--help" ]; then
    _show_usage
elif [ "$1" == "--rnd" ]; then
    if [ -z $2 ]; then
        _p_error "You need to specify the number of arguments.\n  Example: ./view.sh --rnd <number_of_args>"
    fi

    ARG_N=$2
    if ! [[ $ARG_N =~ ^[0-9]+$ ]]; then
        _p_error "arg 1, <number_of_rnd_args> must be a number."
    elif [ $ARG_N -gt $ARG_N_MAX ]; then
        _p_error "arg 1, <number_of_rnd_args> must be lower than ${ARG_N_MAX}."
    elif [ $ARG_N -lt $ARG_N_MIN ]; then
        _p_error "arg 1, <number_of_rnd_args> must be lower than ${ARG_N_MIN}."
    fi
    ARGS=$(python3 _rnd_numbers.py $ARG_N $(( -ARG_N )) $ARG_N)
elif [ "$1" == "--arg" ]; then
    shift
    ARGS=$@
    ARG_N=$#
else
    _show_usage
fi



make -C ../
if [ $? -ne 0 ]; then
    _p_error "\n\nMake failed"
    exit 1
fi
clear

echo -e "\n$(_blue "Push Swap")"
echo -e "\tviewer by werodrig.\n\n\n"

# Create Js
_p_info "Creating $(_blue "data") file..."

rm -f $PW_OUT_FILENAME $JS_FILENAME
.././push_swap $ARGS >./$PW_OUT_FILENAME 2>&1

# # Moves var
_log_file "const moves = ["
while IFS= read -r line; do
    if [ -z "$line" ]; then
        continue
    fi

    if ! check_true_command "$line"; then
        break
    fi

    _log_file "\"$line\","
done < $PW_OUT_FILENAME
_log_file "];\n"

# # Numbers
set -- $ARGS
_min=$1
_max=$1
for num in $ARGS; do
    if (( num < _min )); then
        _min=$num
    fi

    if (( num > _max )); then
        _max=$num
    fi
done

_log_file "const numbers = ["
for number in $ARGS; do
    _color=$(_get_vari_index $number $_min $_max $CLRS_COUNT);
    _weight=$(_get_vari_index $number $_min $_max 9);
    _log_file "{\"number\":$number,\"color\":$_color,\"weight\":$_weight},"
done
_log_file "];\n"


PROCESS=$(pgrep -f ".*$HTML_FILENAME")
TAB_ID=""
if command -v wmctrl > /dev/null; then
    TAB_ID=$(wmctrl -l | grep -i "$HTML_TITLE" | awk '{print $1}')
fi

if [ -n "$PROCESS" -o -n "$TAB_ID" ]; then
    echo -e "Viewer is already open..."
    
    if [ -n "$TAB_ID" ]; then
        wmctrl -ia "$TAB_ID"
        if command -v xdotool > /dev/null; then
            echo -e "$(_blue "reloading") the page!"
            xdotool key ctrl+r
        else
            echo -e "Please $(_blue "reload") the page manually."
        fi
    else
        _ask_user_to_open
    fi
else
    _ask_user_to_open
fi

echo -e "\n\n"

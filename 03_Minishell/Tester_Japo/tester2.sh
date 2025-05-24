#!/bin/bash

MINISHELL="../minishell"

# Función para limpiar el output y quedarnos con lo anterior al prompt verde
clean_output() {
    input="$1"
    full_output=$(printf "%s\n" "$input" | $MINISHELL)

    output=$(echo "$full_output" | tail -n +2)

    clean=""
    found=0

    while IFS= read -r line; do
        if [[ "$line" == *$'\033[1;32m'miniyo'$'* ]]; then
            before_prompt="${line%%$'\033[1;32m'miniyo\$*}"
            clean+="$before_prompt"
            found=1
            break
        else
            clean+="$line"$'\n'
        fi
    done <<< "$output"
    echo -n "$clean"
}

# Colores
RED='\033[0;31m'
GREEN='\033[0;32m'
RESET='\033[0m'

# Test function
run_test() {
    INPUT="$1"
    EXPECTED="$2"

    clean_output "$INPUT" > temp1
    eval "$EXPECTED" > temp2
    if diff -q temp1 temp2 >/dev/null; then
        echo -e "${GREEN}✔️${RESET}  $INPUT"
    else
        echo -e "${RED}❌${RESET}  $INPUT"
        echo "     Diferencias:"
        cat temp1
        cat temp2
    fi
    rm temp1 temp2
}

run_test 'echo $a""a' 'echo $a""a'
run_test 'echo $a"" a' 'echo $a"" a'
run_test 'echo $a" " a' 'echo $a" " a'
run_test 'echo $a" $USER"' 'echo $a" $USER"'
run_test 'echo $a"$USER"' 'echo $a"$USER"'
run_test 'echo $USERa$HOME' 'echo $USERa$HOME'
run_test 'echo "$  a"' 'echo "$  a"'
run_test 'echo "$  a "' 'echo "$  a "'
run_test 'echo "$?u "' 'echo "$?u "'
run_test 'echo "$? us "' 'echo "$? us "'
export kk=-n
run_test 'echo $kk patata' 'echo $kk patata'
run_test 'echo $a' 'echo $a'
#run_test 'echo $"mgs"' 'echo $"mgs"'
#run_test "echo $'msg'" "echo $'msg'"
export kk="echo -n msg1"
run_test '$kk msg2' '$kk msg2'
export kk="echo -nnnnn -n -nnnann msg1"
run_test '$kk msg2' '$kk msg2'
export kk="echo msg1"
run_test '$kk -n msg2' '$kk -n msg2'
run_test 'echo "-n" patata' 'echo "-n" patata'
run_test "echo '-n' patata" "echo '-n' patata"
run_test 'echo "-n patata"' 'echo "-n patata"'
run_test "echo '-n patata'" "echo '-n patata'"
run_test 'echo "-n -na" patata' 'echo "-n -na" patata'
run_test 'echo "-nnnnnn" patata' 'echo "-nnnnnn" patata'
run_test 'echo "-nnnnn " patata' 'echo "-nnnnn " patata'
run_test 'echo " " -n patata' 'echo " " -n patata'
run_test 'echo " " patata' 'echo " " patata'
export kk="  hola         que     tal      "
run_test 'echo $kk' 'echo $kk'
run_test 'echo "$kk"' 'echo "$kk"'
run_test "echo '\$kk'" "echo '\$kk'"
run_test 'echo "' 'echo -n'
export kk="echo tomate"
run_test '$kk' '$kk'
run_test 'echo $$2patata' 'echo 2patata'
run_test 'echo "$ a"' 'echo "$ a"'
run_test 'echo "$a5e#tomate 'p'"' 'echo "$a5e#tomate 'p'"'
run_test 'echo "$a 'p'"' 'echo "$a 'p'"'
run_test 'echo $$' 'echo'
run_test 'echo "$$$USER"' 'echo "$USER"'
run_test 'echo "$$$patata"' 'echo "$patata"'
run_test 'echo "$$%patata"' 'echo "%patata"'
run_test 'echo "$%patata"' 'echo "$%patata"'
run_test 'echo "$!patata"' 'echo "$!patata"'
run_test 'echo "$a664464562ssertetr)'p'"' 'echo "$a664464562ssertetr)'p'"'
run_test 'echo $2patata' 'echo patata'
run_test 'echo $2 patata' 'echo patata'
run_test 'echo $$2patata' 'echo 2patata'
run_test 'echo $$2 patata' 'echo 2 patata'
run_test 'echo $* patata' 'echo patata'
run_test "echo 'patata"\$USER"'" "echo 'patata"\$USER"'"
run_test 'echo $.' 'echo $.'
run_test 'echo $' 'echo $'
run_test 'echo $$' 'echo'
run_test 'echo $$$' 'echo $'
run_test 'echo hola' 'echo hola'
run_test 'echo "'hola'"' 'echo "'hola'"'
run_test "echo '"hola"'" "echo '"hola"'"
run_test 'echo -n hola' 'echo -n hola'
run_test 'echo -n -n hola' 'echo -n -n hola'
run_test 'echo -n -n -n hola' 'echo -n -n -n hola'
run_test 'echo -n -n -n -n hola' 'echo -n -n -n -n hola'
run_test 'echo -n -nnnn hola' 'echo -n -nnnn hola'
run_test 'echo -nnnn hola' 'echo -nnnn hola'
run_test 'echo hola "\"n mundo' "echo 'hola \n mundo'"
run_test 'echo "hola mundo"' 'echo "hola mundo"'
run_test "echo 'hola mundo'" "echo 'hola mundo'"
run_test 'echo hola" mundo"' 'echo hola" mundo"'
run_test 'echo "hola mundo"' 'echo "hola mundo"'
run_test "echo 'hola mundo'" "echo 'hola mundo'"
run_test "echo 'hola'\" mundo\"" "echo hola mundo"
run_test 'echo "saludo: $HOME"' 'echo "saludo: $HOME"'
export kk=32
run_test 'echo $kk' 'echo $kk'
export kk=hola
run_test 'echo "$kk"' 'echo "$kk"'
run_test 'echo $NOEXISTE' 'echo $NOEXISTE'
run_test 'echo $PATH' 'echo $PATH'
run_test 'echo $LS_COLORS' 'echo $LS_COLORS'
run_test 'echo "$USER$HOME"' 'echo "$USER$HOME"'
run_test 'echo $LS_COLORS$PATH$LS_COLORS$PATH$LS_COLORS$PATH$LS_COLORS$PATH$LS_COLORS$PATH' 'echo $LS_COLORS$PATH$LS_COLORS$PATH$LS_COLORS$PATH$LS_COLORS$PATH$LS_COLORS$PATH'
run_test 'echo "$USER"' 'echo "$USER"'
run_test 'echo $USER' 'echo $USER'
run_test "echo '\$USER'" "echo '\$USER'"
run_test 'echo "$?"' 'echo "$?"'
run_test 'echo "$USER literal $HOME"' 'echo "$USER literal $HOME"'
export UNSETVAR=patata
unset UNSETVAR
run_test 'echo $UNSETVAR' 'echo $UNSETVAR'
run_test 'echo ""' 'echo ""'
run_test "echo ''" "echo ''"
run_test 'echo "hola     mundo"' 'echo "hola     mundo"'
run_test 'echo hola     mundo' 'echo hola     mundo'
run_test 'echo -n "hola\nmundo"' 'echo -n "hola\nmundo"'
run_test 'echo "a'\$USER'"' 'echo "a'\$USER'"'
run_test 'echo "'\$USER'"' 'echo "'\$USER'"'
run_test "echo \"\$USER's folder\"" "echo \"\$USER's folder\""
run_test 'echo "$UNDEFINED"' 'echo "$UNDEFINED"'
run_test 'echo "$UNDEFINED texto"' 'echo "$UNDEFINED texto"'
run_test "echo '\$UNDEFINED texto'" "echo '\$UNDEFINED texto'"
run_test 'echo "$USER''$HOME"' 'echo "$USER''$HOME"'
run_test 'echo "$USER '' $HOME"' 'echo "$USER '' $HOME"'
run_test 'echo "  $USER  "' 'echo "  $USER  "'
run_test "echo \"'single' \"double\"\"" "echo \"'single' double\""
run_test 'echo "$? status"' 'echo "$? status"'
run_test 'echo $?' 'echo $?'
run_test "echo \"'\$?'\"" "echo \"'\$?'\""
run_test "echo '\"hola\"'" "echo '\"hola\"'"
run_test "echo \" \" \$USER \" \"" "echo \" \" \$USER \" \""

run_test 'echo $a " " a' 'echo $a " " a'
run_test 'echo "$ a "' 'echo "$ a "'



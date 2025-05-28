#!/bin/bash

#EN EL CODIGO C EN EL MAIN PONER: printf("%s\n", input.command);

MINISHELL="../minishell"

# Función para limpiar el output y quedarnos con lo anterior al prompt verde
clean_output() {
    input="$1"
    full_output=$(printf "%s\n" "$input" | $MINISHELL 2>/dev/null)
    output=$(echo "$full_output" | tail -n 2 | head -n 1)
    echo -n "$output"
}

# Colores
RED='\033[0;31m'
GREEN='\033[0;32m'
RESET='\033[0m'

run_command() {
    INPUT="$1"
    EXPECTED="$2"

    ACTUAL=$(clean_output "$INPUT")

    echo "$EXPECTED" > temp2
    echo "$ACTUAL" > temp1

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



echo '--------------- COMMANDS -----------------'

run_command '$a""a' 'a'
run_command '$a"" a' ''
run_command '$a" " a' ' ' 
run_command '$a "" a' ''
expected="$a$USER"
run_command '$a" $USER"' " $USER"
run_command '$a"$USER"' "$USER"
run_command '$USERa$HOME' "$USERa$HOME"
run_command '"$  a"' '$  a'
run_command '"$  a "' '$  a '
aux="$?u "
run_command '"$?u "' "$aux"
aux="$? us "
run_command '"$? us "' "$aux"
export kk='n'
run_command "$kk patata" "n"
export kk='patata tomate'
run_command "$kk" "patata"
run_command "$kk lechuga" "patata"
run_command "$a \$a" ""
run_command '$"msg"' '$msg'
run_command "$'msg'" '$msg'
export kk=msg1
run_command "$kk msg2" "msg1"


: <<'FIN'
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
run_test 'echo patata "" "" "" tomate' 'echo patata "" "" "" tomate'
run_test 'echo $a patata $a "" "" "" "" tomate' 'echo $a patata "" "" "" "" tomate'
run_test 'echo patata $a "" "" "" "" tomate' 'echo patata $a "" "" "" "" tomate'
run_test 'echo patata $a "" "" "" "" $a tomate' 'echo patata $a "" "" "" "" $a tomate'
run_test 'echo patata $a """""""" $a tomate' 'echo patata $a """""""" $a tomate'
run_test 'echo ""$a""t' 'echo ""$a""t'
run_test 'echo ""$a"" t' 'echo ""$a"" t'
run_test 'echo ""$a" " t' 'echo ""$a" " t'
run_test 'echo ""$a "  " t ""$a "  " t ' 'echo ""$a "  " t ""$a "  " t '
run_test '>kk echo patata' 'echo patata'
run_test '> kk echo patata' 'echo patata'
run_test '>kk echo -n patata' 'echo -n patata'
run_test '>kk echo -nnnnn -na patata' 'echo -nnnnn -na patata'
run_test '>kk echo -nnnnn' 'echo -nnnnn'
run_test '>kk echo' 'echo'

FIN




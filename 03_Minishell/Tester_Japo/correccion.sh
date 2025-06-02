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

clean_output2() {
    echo "$1" | \
    grep -v 'miniyo\$' | \
    grep -v '^export ' | \
    grep -v '^echo ' | \
    grep -v '^exit$' | \
    sed '/^[[:space:]]*$/d'
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


run_redir() {
    INPUT="$1"
    EXPECTED="$2"

    clean_output "$INPUT" > temp1
    eval "$EXPECTED" > temp2
    if diff -q kk temp2 >/dev/null; then
        echo -e "${GREEN}✔️${RESET}  $INPUT"
    else
        echo -e "${RED}❌${RESET}  $INPUT"
        echo "     Diferencias:"
        cat kk
        cat temp2
    fi
    rm kk temp2
}

run_exit()
{
    INPUT="$1"
	EXPECTED="$2"
    
	echo "$INPUT" | ../minishell > /dev/null 2>&1
    EXIT_CODE=$?

	if [ "$EXIT_CODE" -eq "$EXPECTED" ]; then
        echo -e "${GREEN}✔️${RESET}  $INPUT (exit $EXIT_CODE)"
    else
        echo -e "${RED}❌${RESET}  $INPUT (got $EXIT_CODE, expected $EXPECTED)"
    fi
}

run()
{
	INPUT="$1"
	EXPECTED="$2"

    rm -rf ../redirs
    mkdir ../redirs
	clean_output "$INPUT" > ../redirs/temp1 2>&1
	bash -c "$EXPECTED" > ../redirs/temp2 2>&1
	if diff -q ../redirs/temp1 ../redirs/temp2 >/dev/null; then
        echo -e "${GREEN}✔️${RESET}  $INPUT"
    else
        echo -e "${RED}❌${RESET}  $INPUT"
        echo "     Diferencias:"
        cat ../redirs/temp1
        cat ../redirs/temp2
    fi
    rm -rf ../redirs
}

run_command_invalid()
{
	INPUT="$1"
	EXPECTED="$2"

    rm -rf ../redirs
    mkdir ../redirs
	clean_output "$INPUT" > ../redirs/temp1 2>&1
	bash -c "$EXPECTED" > ../redirs/temp2 2>&1
	if grep -q "command not found" ../redirs/temp1 && grep -q "command not found" ../redirs/temp2; then
        echo -e "${GREEN}✔️${RESET}  $INPUT"
    else
        echo -e "${RED}❌${RESET}  $INPUT"
        echo "     Diferencias:"
        cat ../redirs/temp1
        cat ../redirs/temp2
    fi
    rm -rf ../redirs
}

run_directory_invalid()
{
	INPUT="$1"
	EXPECTED="$2"

    rm -rf ../redirs
    mkdir ../redirs
	clean_output "$INPUT" > ../redirs/temp1 2>&1
	bash -c "$EXPECTED" > ../redirs/temp2 2>&1
	if grep -q "No such file or directory" ../redirs/temp1 && grep -q "No such file or directory" ../redirs/temp2; then
        echo -e "${GREEN}✔️${RESET}  $INPUT"
    else
        echo -e "${RED}❌${RESET}  $INPUT"
        echo "     Diferencias:"
        cat ../redirs/temp1
        cat ../redirs/temp2
    fi
    rm -rf ../redirs
}


run_command_return_value()
{
    INPUT="$1"
	EXPECTED="$2"
    
	echo -e "$INPUT\nexit \$?" | ../minishell > redirs/temp1 2>&1
    EXIT_CODE=$?

	if [ "$EXIT_CODE" -eq "$EXPECTED" ]; then
        echo -e "${GREEN}✔️${RESET}  $INPUT (exit $EXIT_CODE)"
    else
        echo -e "${RED}❌${RESET}  $INPUT (got $EXIT_CODE, expected $EXPECTED)"
		cat temp1
    fi
	rm redirs/temp1
}


clear

echo "##########################"
echo "# COMANDS con ruta       #"
echo "##########################"
echo -e "\n"

run '/bin/ls' '/bin/ls'
run '/bin/pwd' '/bin/pwd'
run '/bin/echo patata' '/bin/echo patata'
run '/bin/echo -n patata' '/bin/echo -n patata'
run '/bin/printf patata' '/bin/printf patata'
run '/bin/cat redirs/a' '/bin/cat redirs/a'
run 'whoami' 'whoami'
run '' ''
run '       ' '       '
run '/bin/ls -la' '/bin/ls -la'
run '/bin/ls -l' '/bin/ls -l'
run 'echo uno dos tres cuatro' 'echo uno dos tres cuatro'
run '/bin/ls -l -a -h' '/bin/ls -l -a -h'
run '/bin/ls -lhS' '/bin/ls -lhS'
run '/bin/cat redirs/a redirs/b' '/bin/cat redirs/a redirs/b'
run 'head -n 5 redirs/a' 'head -n 5 redirs/a'

echo -e "\n"
echo "##############"
echo "# ECHO       #"
echo "##############"
echo -e "\n"

run_test 'echo $a""a' 'echo $a""a'
run_test 'echo $a"" a' 'echo $a"" a'
run_test 'echo $a" " a' 'echo $a" " a'
run_test 'echo $a "" a' 'echo $a "" a'
run_test 'echo $a" $USER"' 'echo $a" $USER"'
run_test 'echo $a"$USER"' 'echo $a"$USER"'
run_test 'echo $USERa$HOME' 'echo $USERa$HOME'
run_test 'echo "$  a"' 'echo "$  a"'
run_test 'echo "$  a "' 'echo "$  a "'
run_test 'echo "$?u "' 'echo "$?u "'
run_test 'echo "$? us "' 'echo "$? us "'
export kk=-n
run_test 'echo $kk patata' 'echo $kk patata'
export kk="-nnn -na patata"
run_test 'echo $kk tomate' 'echo $kk tomate'
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
run_test 'echo patata "" "" "" tomate' 'echo patata "" "" "" tomate'
run_test 'echo $a patata $a "" "" "" "" tomate' 'echo $a patata "" "" "" "" tomate'
run_test 'echo patata $a "" "" "" "" tomate' 'echo patata $a "" "" "" "" tomate'
run_test 'echo patata $a "" "" "" "" $a tomate' 'echo patata $a "" "" "" "" $a tomate'
run_test 'echo patata $a """""""" $a tomate' 'echo patata $a """""""" $a tomate'
run_test 'echo ""$a""t' 'echo ""$a""t'
run_test 'echo ""$a"" t' 'echo ""$a"" t'
run_test 'echo ""$a" " t' 'echo ""$a" " t'
run_test 'echo ""$a "  " t ""$a "  " t ' 'echo ""$a "  " t ""$a "  " t '
run_redir '>kk echo patata' 'echo patata'
run_redir '> kk echo patata' 'echo patata'
run_redir '>kk echo -n patata' 'echo -n patata'
run_redir '>kk echo -nnnnn -na patata' 'echo -nnnnn -na patata'
run_redir '>kk echo -nnnnn' 'echo -nnnnn'
run_redir '>kk echo' 'echo'
run 'echo con redireccion "normal"' 'echo con redireccion "normal"'

echo -e "\n"
echo "############"
echo "# EXIT     #"
echo "############"
echo -e "\n"

run_exit "exit" 0
run_exit "exit 42" 42
run_exit "exit 255" 255
run_exit "exit 255" 255
run_exit "exit 256" 0
run_exit "exit -1" 255
run_exit "exit -255" 1
run_exit "exit -256" 0
run_exit "exit 2147483647" 255
run_exit "exit 2147483648" 0
run_exit "exit 9223372036854775807" 255
run_exit "exit -9223372036854775808" 0
run_exit "exit 9223372036854775808" 2
run_exit "exit -9223372036854775809" 2
run_exit "exit -922337203685477580834" 2
run_exit "exit patata" 2

echo -e "\n"
echo "###################################"
echo "# VALOR RETORNO DE UN PROCESO     #"
echo "###################################"
echo -e "\n"

run_exit "/bin/ls" 0
run_exit "/bin/patata" 127
run_command_return_value "/bin/ls" 0
run_command_return_value "/bin/patata" 127
run_command_return_value "/bin/patata" 127
run_command_return_value '/bin/grep "ejemplo" redirs/a' 0
run_command_return_value '/bin/grep "rollon" redirs/a' 1
run_command_return_value '/bin/grep "rollon" redirs/c' 2
run_command_return_value '/bin/diff redirs/a redirs/b' 1
run_command_return_value '/bin/diff redirs/a redirs/a' 0
run_command_return_value '/bin/diff redirs/a redirs/c' 2
run_command_return_value '/bin/test -f redirs/a' 0
run_command_return_value '/bin/test -f redirs/c' 1
run_command_return_value '/bin/test 5 -gt 3' 0
run_command_return_value '/bin/test 1 -gt 3' 1
run_command_return_value '/bin/test 3 -eq 3' 0
SHLVL_VAL=$SHLVL
run "expr $SHLVL_VAL + $SHLVL_VAL" "expr $SHLVL_VAL + $SHLVL_VAL"
run 'expr $SHLVL + $SHLVL' 'expr $SHLVL + $SHLVL - 2'

echo -e "\n"
echo "######################"
echo "# COMILLAS DOBLES    #"
echo "######################"
echo -e "\n"


run '"/bin/ls"' '"/bin/ls"'
run '"/bin/pwd"' '"/bin/pwd"'
run '"/bin/echo" patata' '"/bin/echo" patata'
run '"/bin/echo" -n patata' '"/bin/echo" -n patata'
run '"/bin/printf" patata' '"/bin/printf" patata'
run '"/bin/cat" redirs/a' '"/bin/cat" redirs/a'
run '"whoami"' '"whoami"'
run_command_invalid '""' '""'
run_command_invalid '   ""    ' '   ""    '
run '"/bin/ls" -la' '"/bin/ls" -la'
run '"/bin/ls" -l' '"/bin/ls" -l'
run '"echo" uno dos tres cuatro' '"echo" uno dos tres cuatro'
run '"/bin/ls" -l -a -h' '"/bin/ls" -l -a -h'
run '"/bin/ls" -lhS' '"/bin/ls" -lhS'
run '"/bin/cat" redirs/a redirs/b' '"/bin/cat" redirs/a redirs/b'
run '"head" -n 5 redirs/a' '"head" -n 5 redirs/a'
run '"""p"w"d"""' '"""p"w"d"""'
run_command_invalid '"pwd "' '"pwd "'
run_command_invalid '"patata"' '"patata"'
run 'echo "cat lol.c | cat > lol.c"' 'echo "cat lol.c | cat > lol.c"'
run 'echo "-n" "cat lol.c | cat > lol.c"' 'echo "-n" "cat lol.c | cat > lol.c"'
run_command_invalid '"ls "' '"ls "'
run_command_invalid '"abc def"' '"abc def"'
run_command_invalid '"echoo"' '"echoo"'
run_directory_invalid '"/noexiste"' '"/noexiste"'


echo -e "\n"
echo "#######################"
echo "# COMILLAS SIMPLES    #"
echo "#######################"
echo -e "\n"

run "'/bin/ls'" "'/bin/ls'"
run "'/bin/pwd'" "'/bin/pwd'"
run "'/bin/echo' patata" "'/bin/echo' patata"
run "'/bin/echo' -n patata" "'/bin/echo' -n patata"
run "'/bin/printf' patata" "'/bin/printf' patata"
run "'/bin/cat' redirs/a" "'/bin/cat' redirs/a"
run "'whoami'" "'whoami'"
run_command_invalid "''" "''"
run_command_invalid "   ''    " "   ''    "
run "'/bin/ls' -la" "'/bin/ls' -la"
run "'/bin/ls' -l" "'/bin/ls' -l"
run "'echo' uno dos tres cuatro" "'echo' uno dos tres cuatro"
run "'/bin/ls' -l -a -h" "'/bin/ls' -l -a -h"
run "'/bin/ls' -lhS" "'/bin/ls' -lhS"
run "'/bin/cat' redirs/a redirs/b" "'/bin/cat' redirs/a redirs/b"
run "'head' -n 5 redirs/a" "'head' -n 5 redirs/a"
run "'''p'w'd'''" "'''p'w'd'''"
run_command_invalid "'pwd '" "'pwd '"
run_command_invalid "'patata'" "'patata'"
run "echo 'cat lol.c | cat > lol.c'" "echo 'cat lol.c | cat > lol.c'"
run "echo '-n' 'cat lol.c | cat > lol.c'" "echo '-n' 'cat lol.c | cat > lol.c'"
run_command_invalid "'ls '" "'ls '"
run_command_invalid "'abc def'" "'abc def'"
run_command_invalid "'echoo'" "'echoo'"
run_directory_invalid "'/noexiste'" "'/noexiste'"
run "'echo' '\$HOME'" "'echo' '\$HOME'"
run "'/bin/echo' '\$PATH'" "'/bin/echo' '\$PATH'"
run "'printenv' 'USER'" "'printenv' 'USER'"
run "'echo' '   uno   dos   tres   '" "'echo' '   uno   dos   tres   '"
run "'/bin/echo' '   '" "'/bin/echo' '   '"
run "'cat' '   redirs/a   '" "'cat' '   redirs/a   '"
run "'/bin/echo' patata '|' 'cat'" "'/bin/echo' patata '|' 'cat'"
run "'/bin/ls' '-l' '|' 'wc' '-l'" "'/bin/ls' '-l' '|' 'wc' '-l'"
run_directory_invalid "'cat' redirs/a '|' 'grep' hola" "'cat' redirs/a '|' 'grep' hola"
run "'echo' hola '>' redirs/salida.txt" "'echo' hola '>' redirs/salida.txt"
run "'cat' '<' redirs/a" "'cat' '<' redirs/a"
run_directory_invalid "'grep' hola '<' redirs/a '>' redirs/out" "'grep' hola '<' redirs/a '>' redirs/out"
run 'echo '\''$USER'\''' 'echo '\''$USER'\'''
run_directory_invalid 'cd '\''~'\''' 'cd '\''~'\'''













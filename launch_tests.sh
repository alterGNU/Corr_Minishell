#!/usr/bin/env bash

# ============================================================================================================
# Launch minishell unitests
# This script take no argument (for now) and will automatically:
#   - 1: check norminette for libft folder, excluding Corr_Minishell folder, tests dont comply with norme
#   - 2: list all home-made fun in libft.a
#   - 3: list all build-in fun in libft.a
#   - 4: launch libft mandatory functions tests.
#   - 5: if detected at least one fun of libft_bonus part, launch test for all libft_bonus functions.
#   - 6: if detected ft_printf() in libft.a, launch tests for ft_printf() tests (bonus too, auto)
#   - 7: if detected get_next_line() in libft.a, launch tests for get_next_line() tests (bonus too, auto)
# ============================================================================================================
 
# =[ VARIABLES ]==============================================================================================
# -[ PATH/FOLDER/FILE ]---------------------------------------------------------------------------------------
SCRIPTNAME=${0##*\/}                                              # ☒ Script's name (no path)
PARENT_DIR=$(dirname $(realpath ${0}))                            # ☒ Name of parent directory
MS_DIR=$(dirname $(realpath ${PARENT_DIR}))                       # ☒ Name of parent directory
PROGRAMM="${MS_DIR}/minishell"                                    # ☒ Object's name to test (here our executable)
LOG_DIR="${PARENT_DIR}/log/$(date +%Y_%m_%d/%Hh%Mm%Ss)"           # ☒ Name of the log folder
LOG_FAIL="${LOG_DIR}/list_errors.log"                             # ☒ File contains list of function that failed
BSL_DIR="${PARENT_DIR}/src/BSL"                                   # ☒ Path to BSL folder
BIN_DIR="${PARENT_DIR}/bin"                                       # ☒ Path to bin folder (test binary)
LIBFT_A=$(find "${MS_DIR}" -type f -name "libft.a")               # ☒ libft.a static library
# -[ LISTS ]--------------------------------------------------------------------------------------------------
EXCLUDE_NORMI_FOLD=( "tests" "${PARENT_DIR##*\/}" )               # ☒ List of folder to be ignore by norminette
FUN_TO_EXCLUDE=( "_fini" "main" "_start" "_init" "_end" "_stop" ) # ☒ List of function name to exclude
FUN_TO_TEST=( )                                                   # ☒ List of user created function specific to minishell
FUN_TESTED=( )                                                    # ☒ List of user created function specific to minishell that have a test founded
HOMEMADE_FUNUSED=( )                                              # ☒ List of user created function in minishell
BUILTIN_FUNUSED=( )                                               # ☒ List of build-in function 
LIBFT_FUN=( )                                                     # ☒ List of user created function in libft.a
OBJ=( )                                                           # ☒ List of object.o (no main function in it)
for obj in $(ls ${MS_DIR}/build/*.o);do if ! nm "${obj}" | grep -qE '\<main\>';then OBJ+=( "${obj}" );fi;done
# -[ COMMANDS ]-----------------------------------------------------------------------------------------------
CC="cc -Wall -Wextra -Werror -I${MS_DIR}/include -I${MS_DIR}/libft/include ${OBJ[@]} -lreadline"
VAL_ERR=42
VALGRIND="valgrind --leak-check=full --track-fds=yes --error-exitcode=${VAL_ERR}"
# -[ LAYOUT ]-------------------------------------------------------------------------------------------------
LEN=100                                                           # ☑ Width of the box
# -[ COLORS ]-------------------------------------------------------------------------------------------------
E="\033[0m"                                                        # ☒ END color balise
N0="\033[0;30m"                                                    # ☒ START BLACK
R0="\033[0;31m"                                                    # ☒ START RED
RU="\033[4;31m"                                                    # ☒ START RED UNDERSCORED
V0="\033[0;32m"                                                    # ☒ START GREEN
M0="\033[0;33m"                                                    # ☒ START BROWN
Y0="\033[0;93m"                                                    # ☒ START YELLOW
YU="\033[4;93m"                                                    # ☒ START YELLOW UNDERSCORED
B0="\033[0;34m"                                                    # ☒ START BLUE
BU="\033[4;34m"                                                    # ☒ START BLUE
BC0="\033[0;36m"                                                   # ☒ START AZURE
BCU="\033[4;36m"                                                   # ☒ START AZURE UNDERSCORED
P0="\033[0;35m"                                                    # ☒ START PINK
G0="\033[2;47m"                                                    # ☒ START GREY
GU="\033[4;47m"                                                    # ☒ START GREY
# -[ COUNT ]--------------------------------------------------------------------------------------------------
TOT_FAILS=0                                                       # ☒ Count how many fun have failed
# =[ SOURCES ]================================================================================================
source ${BSL_DIR}/src/check42_norminette.sh
source ${BSL_DIR}/src/print.sh
# =[ FUNCTIONS ]==============================================================================================
# -[ USAGE ]--------------------------------------------------------------------------------------------------
# Display usage with arg1 as error_msg and arg2 as exit_code
script_usage()
{
    echo -e "${RU}[Err:${2}] Wrong usage${R0}: ${1}${E}\n${BU}Usage:${R0}  \`${V0}./${SCRIPTNAME}\`${E}"
    echo -e " 🔹 ${V0}${SCRIPTNAME}${E} has as a prerequisites:"
    echo -e "    ${B0}‣ ${R0}i) ${E}: To be cloned inside the project ${M0}path/minishell/${E} to be tested."
    echo -e "    ${B0}‣ ${R0}ii)${E}: The programm ${M0}path/minishell/${V0}minishell${E} has to be compiled before using ${V0}./${SCRIPTNAME}${E}."
    echo -e " 🔹 ${V0}${SCRIPTNAME}${E} takes no arguments and will automatically:"
    echo -e "    ${B0}‣ ${R0}0${E}: Check if ${M0}minishell/${E} complies with the 42-norme"
    echo -e "    ${B0}‣ ${R0}1${E}: Set a list of all user-made function called by ${V0}minishell${E} programm.(including ${V0}libft.a${E} functions)"
    echo -e "    ${B0}‣ ${R0}2${E}: Set a list of all user-made function specific to ${V0}minishell${E} programm.(excluding ${V0}libft.a${E} functions)"
    echo -e "    ${B0}‣ ${R0}3${E}: Set a list of all built-in function called by ${V0}minishell${E}"
    echo -e "    ${B0}‣ ${R0}4${E}: for each specific fun of ${V0}minishell${E}, search its unitest, if found launch test, else pass${E}"
    echo -e "    ${B0}‣ ${R0}5${E}: Display a resume."
    exit ${2}
}
# -[ PRINT_RELATIF_PATH() ]-----------------------------------------------------------------------------------
# substract pwd from arg1 abs-path given
print_shorter_path() { echo "${1/${PWD}/.}" ; }
# -[ EXEC_ANIM_IN_BOX ]---------------------------------------------------------------------------------------
# Takes 2args: arg1:<cmd> [arg2:<title>]
# exec command passed as arg1 while displaying animation, return result in a box colored red if cmd failed, green else
exec_anim_in_box()
{
    [[ ( ${#} -gt 2 ) ]] && { echo -e "\033[1;31mWRONG USAGE of:\033[1;36mexec_anim()\033[1;31m, this function take 2 arguments max.\033[0m" && exit 3 ; }
    local frames=( 🕛  🕒  🕕  🕘 )
    local delay=0.15
    local cmd="${1}"
    [[ ${#} -eq 2 ]] && local boxtitle="${2}" || local boxtitle="${cmd}"
    local tmpfile=$(mktemp "${TMPDIR:-/tmp}/exec_anim_${cmd%% *}_XXXXXX")
    trap '[[ -f "${tmpfile}" ]] && rm -f "${tmpfile}"' EXIT RETURN
    ${1} > "${tmpfile}" 2>&1 &
    local pid=${!}
    while kill -0 ${pid} 2>/dev/null; do
        for frame in "${frames[@]}"; do printf "${frame} \033[1;40mwaiting for cmd:${1}\033[0m\r" && sleep ${delay} ; done
    done
    printf "\r\033[K" && wait ${pid}
    local exit_code=${?}
    [[ ${exit_code} -eq 0 ]] && local color="green" || local color="red"
    print_box_title -t 1 -c ${color} "${boxtitle}"
    while IFS= read -r line; do
        echol -i 0 -c ${color} -t 1 "${line}"
    done < "${tmpfile}"
    print_last -t 1 -c ${color}
    return ${exit_code}
}

# -[ LAUNCH_UNITESTS() ]--------------------------------------------------------------------------------------
# Function that launch unitests for each <function_name> found in <list_name> given as arg1 or arg2.
# Compile then Exec unitests will creating log_files then returns the numbers of errors encountred.
# - USAGE:
#   - Take one to two arguments:
#     - arg1 (mandatory): list_name of a list that contains all the <function_name> fount in object.
#       - `launch_unitests FUN_TO_TEST` --> will launch unitests for all function in list name: FUN_TO_TEST
#     - arg2 (optionnal): list_name of a list that contains all the <function_name> THAT HAVE TO BE FOUND in object.
#       - `launch_unitests LST1 LST2` --> will launch unitests for all fun in LST2 and LST1, if not in LST1=ERROR
# - LOG FILES PRODUCE:
# - ../log/<date>/<time>/${LOG_FAIL}                --> File contains list of all encountred errors, format="<fun_name>\t<error_type>"
#                                                   └-> error_type = {compilation, errors, leaks, missing}                        
# - ../log/<date>/<time>/<fun_name>/                --> Folder created for each function tested (remove if empty at the end)
# - ../log/<date>/<time>/<fun_name>/comp_stderr.txt --> File created only when compilation failed: contains compilation error messages.
# - ../log/<date>/<time>/<fun_name>/exec.log        --> File contains execution's outputs (stdout && stderr)
# - ../log/<date>/<time>/<fun_name>/leaks.log       --> File contains valgrind's outputs (stdout && stderr)
# - PSEUDO-CODE:
#   - (0): INPUT VALIDATION
#     - Check number of args given valid, else exit.
#     - Build the 2 needed arrays: FUN_FOUND (list of fun found in obj), FUN_MANDA (list of fun needed)
#       - If only arg1    --> FUN_FOUND == FUN_MANDA == ${arg1[@]}
#       - If arg1 && arg2 --> FUN_FOUND == ${arg1[@]} && FUN_MANDA == ${arg2[@]}
#     - Check if builded lists valid, else exit.
#   - (1): LOOP TROUGHT FUN_MANDA
#     - if <fun> not in FUN_FOUND --> nb_err++;
#     - else check if an unitests exist:
#        - (1.0) Create directory ../log/<date>/<time>/<fun_name>/
#        - (1.1) COMPILE if compilation needed, if compilation fail --> nb_err++ && create comp_stderr.txt
#        - (1.2) EXEC if compilation succed, redir stdout && stderr to exec.log, if exec failed --> nb_err++
#        - (1.3) VALGRIND if compilation succed, redir stdout && stderr to leaks.log, if valgrind failed --> nb_err++
#        - (1.4) If ../log/<date>/<time>/<fun_name>/ empty, remove the directory
launch_unitests()
{
    # INPUT VALIDATION
    [[ ${#} -eq 0 || ${#} -gt 2 ]] && { echo "${R0}WRONG USAGE OF launch_unitests():wrong number of argument" && exit 2 ; }
    local -a FUN_FOUND=( )     # list of all fun found in object (==arg1)
    local -a FUN_MANDA=( ) # list of all fun needed, (set as arg2 if given, else is a copy of arg1)
    eval "local -a FUN_FOUND=( \"\${${1}[@]}\" )"
    [[ -n ${2} ]] && eval "local -a FUN_MANDA+=( \"\${${2}[@]}\" )" || eval "local -a FUN_MANDA+=( \"\${${1}[@]}\" )"
    [[ ${#FUN_FOUND[@]} -eq 0 ]] && { echo "${R0}WRONG USAGE OF launch_unitests():FUN_FOUND created is an empty list" && exit 2 ; }
    [[ ${#FUN_MANDA[@]} -eq 0 ]] && { echo "${R0}WRONG USAGE OF launch_unitests():FUN_MANDA created is an empty list" && exit 2 ; }

    local nb_err=0
    for fun in ${FUN_MANDA[@]};do
        echo "🔹${BCU}${fun}():${E}"
        if [[ " ${FUN_FOUND[@]} " =~ " ${fun} " ]];then
            local FUN_LOG_DIR="${LOG_DIR}/${fun}"
            [[ ! -d ${FUN_LOG_DIR} ]] && mkdir -p ${FUN_LOG_DIR}
            local test_main=$(find "${PARENT_DIR}/src" -type f -name *"${fun}.c")
            local test_txt=$(find "${PARENT_DIR}/src" -type f -name *"${fun}.txt")
            if [[ -n "${test_main}" ]];then
                # STEP 1 : COMPILATION --> IF NO BINARY OR IF SOURCES NEWER THAN BINARY
                [[ ! -d ${BIN_DIR} ]] && mkdir -p ${BIN_DIR}
                exe="${BIN_DIR}/test_${fun}"
                echo -en " ${BC0} ⤷${E} ⚙️  ${GU}Compilation:${E}"
                # cases where compilation needed: (1:no binary),(2:sources newer than binary),(3:text exist and newer than binary)
                # TODO: handle when OBJ file are newer that exe too
                if [[ ! -f "${exe}" || "${test_main}" -nt "${exe}" || ( -n "${test_txt}" && "${test_txt}" -nt "${exe}" ) ]];then
                    local res_compile=$(${CC} ${test_main} ${LIBFT_A} -o ${exe} -lbsd > "${FUN_LOG_DIR}/comp_stderr.log" 2>&1 && echo ${?} || echo ${?})
                    if [[ "${res_compile}" -eq 0 ]];then
                        echo -en " ✅ ${V0} Successfull.${E}\n"
                        rm "${FUN_LOG_DIR}/comp_stderr.log"
                    else
                        local log_comp_fail=$(print_shorter_path ${FUN_LOG_DIR}/comp_stderr.log)
                        nb_err=$(( nb_err + 1 ))
                        echo -e "${fun}\tcompilation\t${log_comp_fail}" >> ${LOG_FAIL}
                        echo -en " ❌ ${R0}Compilation failed.${E}\n"
                        sed 's/^/\x1b[0;31m       /' ${log_comp_fail}
                        continue
                    fi
                else
                    echo -en " ☑️  ${BC0} Not needed.\n${E}"
                fi
                # STEP 2 : EXECUTION
                echo -en " ${BC0} ⤷${E} 🚀 ${GU}Execution  :${E}"
                if [[ -f "${test_txt}" ]];then
                    local res_tests=$(${exe} "$(dirname "${test_txt}")" "${FUN_LOG_DIR}" > "${FUN_LOG_DIR}/exec.log" 2>&1 && echo ${?} || echo ${?})
                else
                    local res_tests=$(${exe} > "${FUN_LOG_DIR}/exec.log" 2>&1 && echo ${?} || echo ${?})
                fi
                echo "EXIT_VALUE=${res_tests}" >> "${FUN_LOG_DIR}/exec.log"
                if [[ ${res_tests} -eq 0 ]];then
                    echo -en " ✅ ${V0} No error detected.${E}\n"
                else
                    local exec_log_file=$(print_shorter_path ${FUN_LOG_DIR}/exec.log)
                    nb_err=$(( nb_err + 1 ))
                    echo -e "${fun}\terrors\t${exec_log_file}" >> ${LOG_FAIL}
                    echo -en " ❌ ${R0} Error detected (exec return value=${res_tests})\n"
                    echo "      🔸${Y0}check log file 👉 ${M0}${exec_log_file}${E}"
                fi
                # STEP 3 : VALGRIND
                echo -en " ${BC0} ⤷${E} 🚰 ${GU}Valgrind   :${E}"
                if [[ -f "${test_txt}" ]];then
                    local res_val=$(${VALGRIND} ${exe} "$(dirname "${test_txt}")" "${FUN_LOG_DIR}" > "${FUN_LOG_DIR}/leaks.log" 2>&1 && echo ${?} || echo ${?})
                else
                    local res_val=$(${VALGRIND} ${exe} > "${FUN_LOG_DIR}/leaks.log" 2>&1 && echo ${?} || echo ${?})
                fi
                if [[ ${res_val} -ne ${VAL_ERR} ]];then
                    echo -en " ✅ ${V0} No leak detected.${E}\n"
                else
                    local leaks_log_file=$(print_shorter_path ${FUN_LOG_DIR}/leaks.log)
                    nb_err=$(( nb_err + 1 ))
                    echo -e "${fun}\tleaks\t${leaks_log_file}" >> ${LOG_FAIL}
                    echo -en " ❌ ${R0} Leak detected (valgrind return value=${res_val})\n"
                    echo "      🔸${Y0}check log file 👉 ${M0}${leaks_log_file}${E}"
                fi
            else
                echo " ${BC0} ⤷${E} ✖️  ${G0}Tests not found.${E}"
                rmdir "${FUN_LOG_DIR}" > /dev/null 2>&1
            fi
        else
            echo -e "${fun}\tmissing\t⭙" >> ${LOG_FAIL}
            nb_err=$(( nb_err + 1 ))
            echo " ${BC0} ⤷${E} ❌ ${R0}Function not found in object.${E}"
        fi
    done
    return ${nb_err}
}

# -[ DISPLAY_RESUME() ]---------------------------------------------------------------------------------------
# Display the resume of test (norminette, tests results, log files produces ...)
# Take on optionnal argument, text to add between the <🔶 RESUME> and the <:>.
display_resume()
{
    [[ -n "${1}" ]] && local args=( "🔶 ${YU}RESUME ${1}:${E}" ) || local args=( "🔶 ${YU}RESUME :${E}" )
    [[ ${res_normi} -eq 0 ]] && args+=( " 🔸 ${YU}Norminette:${V0} ✅ PASS${E}" ) || args+=( " 🔸 ${YU}Norminette:${R0} ❌ FAIL (${res_normi} wrong files detected)${E}" )
    local short_log_dir=$(print_shorter_path ${LOG_DIR})
    local tot_tested=$(find ${short_log_dir} -mindepth 1 -maxdepth 1 -type d | wc -l )
    local lst_fail=( )
    local causes=( )
    local causes=( )
    [[ -f "${LOG_FAIL}" ]] && for ff in $(cat ${LOG_FAIL} | awk '{print $1}' | sort -u);do [[ ! " ${lst_fail[@]} " =~ " ${ff} " ]] && lst_fail+=( "${ff}" );done
    if [[ ${#lst_fail[@]} -eq 0 ]];then
        args+=( " 🔸 ${YU}${tot_tested} functions have been tested:${V0} ✅ PASS${E}" ) 
    else
        args+=( " 🔸 ${YU}${tot_tested} functions have been tested:${E}" )
        args+=( \
            "    ${V0}✅ $(( tot_tested - ${#lst_fail[@]} )) functions ${V0}PASSED.${E}" \
            "    ${R0}❌ ${#lst_fail[@]} functions ${R0}FAILLED:${E}" \
        )
        for fun in "${lst_fail[@]}";do
            args+=( "      ${R0}✘ ${RU}${fun}():${E}" )
            local link1=$(awk -v f="${fun}" '$1 == f &&  $2 == "compilation" {print $3}' ${LOG_FAIL})
            local link2=$(awk -v f="${fun}" '$1 == f &&  $2 == "errors" {print $3}' ${LOG_FAIL})
            local link3=$(awk -v f="${fun}" '$1 == f &&  $2 == "leaks" {print $3}' ${LOG_FAIL})
            local link4=$(awk -v f="${fun}" '$1 == f &&  $2 == "missing" {print $3}' ${LOG_FAIL})
            [[ -n "${link1}" ]] && args+=( "      ${R0}⤷ Error occure will compilling ${M0}👉 ${link1}${E}" )
            [[ -n "${link2}" ]] && args+=( "      ${R0}⤷ Error detected ${M0}👉 ${link2}${E}" )
            [[ -n "${link3}" ]] && args+=( "      ${R0}⤷ Leaks detected ${M0}👉 ${link3}${E}" )
            [[ -n "${link4}" ]] && args+=( "      ${R0}⤷ Missing function, not found in object file.${E}" )
        done
    fi
    print_in_box -t 2 -c y "${args[@]}"
}

# ============================================================================================================
# MAIN
# ============================================================================================================
# =[ CHECK IF LIBFT.A FOUNDED ]===============================================================================
[[ -x ${PROGRAMM} ]] || { script_usage "${R0}Programm not found: No ${BC0}${PROGRAMM}${R0} found.${E}" 2; }
# =[ CREATE LOG_DIR ]=========================================================================================
[[ ! -d ${LOG_DIR} ]] && mkdir -p ${LOG_DIR}
# =[ START MESSAGE ]==========================================================================================
print_in_box -t 2 -c y "🔶 ${Y0}START Minishell's Tests${E}"
# =[ CHECK NORMINETTE ]=======================================================================================
exec_anim_in_box "check42_norminette ${MS_DIR}" "Check Norminette"
res_normi=${?}
# =[ SET LISTS ]==============================================================================================
# -[ SET LIBFT_FUN ]------------------------------------------------------------------------------------------
if file "${LIBFT_A}" | grep -qE 'relocatable|executable|shared object|ar archive';then
    for fun in $(nm -g "${LIBFT_A}" | grep " T " | awk '{print $NF}' | sort | uniq);do
        [[ ! " ${LIBFT_FUN[@]} " =~ " ${fun} " ]] && LIBFT_FUN+=( "${fun}" )
    done
else
    echo -e "LIBFT_A=${BC0}${LIBFT_A}${E} is not an object file\033[m"
fi
# -[ SET HOMEMADE_FUNUSED & BUILTIN_FUNUSED ]-----------------------------------------------------------------
if file "${PROGRAMM}" | grep -qE 'relocatable|executable|shared object|ar archive';then
    for fun in $(nm -g "${PROGRAMM}" | grep " T " | awk '{print $NF}' | sort | uniq);do
        [[ ! " ${HOMEMADE_FUNUSED[@]} " =~ " ${fun} " ]] && HOMEMADE_FUNUSED+=( "${fun}" )
        if [[ " ${FUN_TO_EXCLUDE[@]} " =~ " ${fun} " && " ${fun} " != " main " ]];then
            [[ ! " ${BUILTIN_FUNUSED[@]} " =~ " ${fun} " ]] && BUILTIN_FUNUSED+=( "${fun}" )
        fi
    done
    for fun in $(nm -g "${PROGRAMM}" | grep " U " | awk '{print $NF}' | sort | uniq);do
        if [[ ! " ${HOMEMADE_FUNUSED[@]} " =~ " ${fun} " ]];then
            [[ ! " ${BUILTIN_FUNUSED[@]} " =~ " ${fun} " ]] && BUILTIN_FUNUSED+=( "${fun}" )
        fi
    done
else
    echo -e "${BC0}${PROGRAMM}${E} is not an object file\033[m"
fi
# -[ PERSONNAL FUNCTION ]-------------------------------------------------------------------------------------
FUN_TO_TEST=($(printf "%s\n" "${HOMEMADE_FUNUSED[@]}" | grep -vxF -f <(printf "%s\n" "${LIBFT_FUN[@]}" "${FUN_TO_EXCLUDE[@]}")))
for fun in "${FUN_TO_TEST[@]}";do [[ -n "$(find "${PARENT_DIR}/src" -type f -name "${fun}.c")" ]] && FUN_TESTED+=( "${fun}" );done
exec_anim_in_box "launch_unitests FUN_TO_TEST" "Launch Unitests on Minishell's functions"
# =[ RESUME ]=================================================================================================
display_resume "Minishell's tests"

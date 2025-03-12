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
BSL_DIR="${PARENT_DIR}/src/BSL"                                   # ☒ Path to BSL folder
BIN_DIR="${PARENT_DIR}/bin"                                       # ☒ Path to bin folder (test binary)
LIBFT_A=$(find "${MS_DIR}" -type f -name "libft.a")               # ☒ libft.a static library
# -[ COMMANDS ]-----------------------------------------------------------------------------------------------
CC="cc -Wall -Wextra -Werror -I${MS_DIR}/libft/include -I${MS_DIR}/include -I${MS_DIR}/build/*.o"
VALGRIND="valgrind --leak-check=full --track-fds=yes --error-exitcode=1"
# -[ LISTS ]--------------------------------------------------------------------------------------------------
EXCLUDE_NORMI_FOLD=( "tests" "${PARENT_DIR##*\/}" )               # ☒ List of folder to be ignore by norminette
FUN_TO_EXCLUDE=( "_fini" "main" "_start" "_init" "_end" "_stop" ) # ☒ List of function name to exclude
FUN_TO_TEST=( )                                                   # ☒ List of user created function specific to minishell
FUN_TESTED=( )                                                    # ☒ List of user created function specific to minishell that have a test founded
HOMEMADE_FUNUSED=( )                                              # ☒ List of user created function in minishell
BUILTIN_FUNUSED=( )                                               # ☒ List of build-in function 
LIBFT_FUN=( )                                                     # ☒ List of user created function in libft.a
# -[ LAYOUT ]-------------------------------------------------------------------------------------------------
LEN=100                                                           # ☑ Width of the box
# -[ COLORS ]-------------------------------------------------------------------------------------------------
E="\033[0m"                                                       # ☒ END color balise
N0="\033[0;30m"                                                   # ☒ START BLACK
R0="\033[0;31m"                                                   # ☒ START RED
RU="\033[4;31m"                                                   # ☒ START RED UNDERSCORED
V0="\033[0;32m"                                                   # ☒ START GREEN
M0="\033[0;33m"                                                   # ☒ START BROWN
Y0="\033[0;93m"                                                   # ☒ START YELLOW
B0="\033[0;34m"                                                   # ☒ START BLUE
BU="\033[4;34m"                                                   # ☒ START BLUE
BC0="\033[0;36m"                                                  # ☒ START AZURE
BCU="\033[4;36m"                                                  # ☒ START AZURE UNDERSCORED
P0="\033[0;35m"                                                   # ☒ START PINK
G0="\033[0;37m"                                                   # ☒ START GREY
GU="\033[4;37m"                                                   # ☒ START GREY UNDERSCORED
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

# -[ LAUNCH_TESTS_PERSO_FUN() ]-------------------------------------------------------------------------------
# Launch tests for all my personnal functions
launch_tests_perso_fun()
{
    local DOC_PERSO_FUN="${LOG_DIR}/files_generated"
    local nb_err=0
    for fun in ${FUN_TO_TEST[@]};do
        local test_main=$(find "${PARENT_DIR}/src" -type f -name "${fun}.c")
        echo "🔹${BCU}${fun}():${E}"
        if [[ -n "${test_main}" ]];then
            [[ ! -d ${BIN_DIR} ]] && mkdir -p ${BIN_DIR}
            exe="${BIN_DIR}/test_${fun}"
            echo -en "  - ⚙️  ${GU}Compilation:${E}"
            if [[ ! -f "${exe}" ]];then
                local fun_obj=$(find "${MS_DIR}/build" -type f -name "${fun}.o")
                local res_compile=$(${CC} ${test_main} ${fun_obj} ${LIBFT_A} -o ${exe} -lbsd > "${LOG_DIR}/${fun}.compile" 2>&1)
                if [[ "${res_compile}" -eq 0 ]];then
                    echo -en " ✅ ${V0} Successfull.${E}\n"
                else
                    nb_err=$(( nb_err + 1 ))
                    local log_comp_fail=$(print_shorter_path ${LOG_DIR}/${fun}.compile)
                    echo -en " ❌ ${R0}compilation failed.${E}\n"
                    sed 's/^/\x1b[0;31m       /' ${log_comp_fail}
                    echo "      🔸${Y0}check log file 👉 ${M0}${log_comp_fail}${E}"
                    continue
                fi
            else
                echo -en " ☑️  ${BC0} Not needed.\n${E}"
            fi
            if [[ -f "${exe}" ]];then
                echo -en "  - 🚀 ${GU}Execution  :${E}"
                if [[ -f "${PARENT_DIR}/src/unitests/docs/${fun}.txt" ]];then
                    [[ ! -d ${DOC_PERSO_FUN} ]] && mkdir -p ${DOC_PERSO_FUN}
                    local res_tests=$(${exe} "${PARENT_DIR}/src/unitests/docs" "${DOC_PERSO_FUN}" > "${LOG_DIR}/${fun}.log" 2>&1)
                else
                    local res_tests=$(${exe} > "${LOG_DIR}/${fun}.log" 2>&1)
                fi 
                if [[ ${res_tests} -eq 0 ]];then
                    echo -en " ✅ ${V0} ${res_tests} error(s) detected.${E}\n"
                else
                    nb_err=$(( nb_err + 1 ))
                    echo -en " ❌${R0} ${res_tests} error(s) detected\n"

                    echo "      🔸${Y0}check log file 👉 ${M0}$(print_shorter_path ${LOG_DIR}/${fun}.log)${E}"
                fi
                echo -en "  - 🚰 ${GU}Valgrind   :${E}"
                if [[ -f "${PARENT_DIR}/src/unitests/docs/${fun}.txt" ]];then
                    [[ ! -d ${DOC_PERSO_FUN} ]] && mkdir -p ${DOC_PERSO_FUN}
                    res_val=$(${VALGRIND} ${exe} "${PARENT_DIR}/src/unitests/docs" "${DOC_PERSO_FUN}" > "${LOG_DIR}/${fun}.val" 2>&1)
                else
                    res_val=$(${VALGRIND} ${exe} > "${LOG_DIR}/${fun}.val" 2>&1)
                fi
                if [[ ${res_val} -eq 0 ]];then
                    echo -en " ✅ ${V0} no leaks detected.${E}\n"
                else
                    nb_err=$(( nb_err + 1 ))
                    echo -en " ❌ ${R0} leaks detected\n"
                    echo "      🔸${Y0}check log file 👉 ${M0}$(print_shorter_path ${LOG_DIR}/${fun}.val)${E}"
                fi
            else
                echo "${R0}  - no binary ${B0}${exe}${R0} found${E}"
            fi
        else
            echo "${M0}  - No tests founded."
        fi
    done
    return ${nb_err}
}

# ============================================================================================================
# MAIN
# ============================================================================================================
# =[ CHECK IF LIBFT.A FOUNDED ]===============================================================================
[[ -x ${PROGRAMM} ]] || { script_usage "${R0}Programm not found: No ${BC0}${PROGRAMM}${R0} found.${E}" 2; }
# =[ CREATE LOG_DIR ]=========================================================================================
[[ ! -d ${LOG_DIR} ]] && mkdir -p ${LOG_DIR}
# =[ START MESSAGE ]==========================================================================================
print_in_box -t 2 -c y "🚧${Y0} START Minishell's Tests${E}"
# =[ CHECK NORMINETTE ]=======================================================================================
exec_anim_in_box "check42_norminette ${MS_DIR}" "Check Norminette"
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
exec_anim_in_box "launch_tests_perso_fun" "Tests personnal functions"
last_cmd=${?}
TOT_FAILS=$(( TOT_FAILS + last_cmd ))
# =[ RESUME ]=================================================================================================
short_log_dir=$(print_shorter_path ${LOG_DIR})
print_in_box -t 2 -c y \
    "🚧${Y0} RESUME Libft_Enhanced's Tests${E}" \
    "   - 🚀 ${GU}${#FUN_TESTED[@]}/${#FUN_TO_TEST[@]} functions have been tested:${E}" \
    "      - $(( "${#FUN_TESTED[@]}" - TOT_FAILS)) functions ${V0}PASSED${E} there tests." \
    "      - ${TOT_FAILS} functions ${R0}FAILLED${E} there tests:" \
    "   - 📂 ${GU}Log files created at:${E} ${M0}${short_log_dir}/*${E}" \
    "      - $(find ${short_log_dir} -type f | grep '.log$' | wc -l) ${M0}exec log files${E} where created." \
    "      - $(find ${short_log_dir} -type f | grep '.val$' | wc -l) ${M0}valgrind log files${E} where created." \
    "      - $(find ${short_log_dir} -type f | grep '.txt$' | wc -l) ${M0}outputs files${E} where produce by test."

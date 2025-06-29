#!/usr/bin/env bash

# ============================================================================================================
# TODO
#  - [ ] if arg is a folder, search inside the folder all the *.test
# Launch minishell tests
# - For each commands files cmdfiles.test:
#   - 1| run `<cmdfiles.test ./minishell  >minishell_cmdfiles.res`
#   - 2| run `<cmdfiles.test bash --posix >bashposix_cmdfiles.res`
#   - 3| run `vimdiff bash_cmd_files.res minishell_cmdfiles.res`
# - If no args given, (default tests) --> search in minishell_tests/ folder each tests

# =[ VARIABLES ]==============================================================================================
ARGS=()                                                           # ☒ Copy of arguments pass to the script
for arg in "${@}";do ARGS+=( "${arg}" );done
PARENT_DIR=$(cd $(dirname ${0}) && pwd)                           # ☒ Name of parent directory (TEST_DIR)
MS_DIR=$(cd $(dirname ${PARENT_DIR}) && pwd)                      # ☒ Name of great-parent directory (MINISHELL_DIR)
LOG_DIR="${PARENT_DIR}/log/$(date +%Y_%m_%d/%Hh%Mm%Ss)"           # ☒ Name of the log folder
LIBFT_A=$(find "${MS_DIR}" -type f -name "libft.a")               # ☒ libft.a static library
MINISHELL=$(find "${MS_DIR}" -type f -name "minishell")           # ☒ minishell program
PROGRAMM="${MS_DIR}/minishell"                                    # ☒ Object's name to test (here our executable)
BSL_DIR="${PARENT_DIR}/src/BSL"                                   # ☒ Path to BSL folder
# -[ LISTS ]--------------------------------------------------------------------------------------------------
TEST_FILE=()                                                      # ☒ List of file.test to use to compare minishell's return and bash --posix return's
# -[ COMMANDS ]-----------------------------------------------------------------------------------------------
CC="cc -Wall -Wextra -Werror -I${MS_DIR}/include -I${MS_DIR}/libft/include ${OBJ[@]}"
# -[ LAYOUT ]-------------------------------------------------------------------------------------------------
LEN=100                                                            # ☑ Width of the box
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
G0="\033[2;37m"                                                    # ☒ START GREY
GU="\033[4;37m"                                                    # ☒ START GREY
CT="\033[97;100m"                                                  # ☒ START TITLE
# =[ SOURCES ]================================================================================================
source ${BSL_DIR}/src/check42_norminette.sh
source ${BSL_DIR}/src/print.sh
# =[ FUNCTIONS ]==============================================================================================
print_shorter_path() { echo "${1/${PWD}/.}" ; }
# ============================================================================================================
# MAIN
# ============================================================================================================
# =[ CHECK IF LIBFT.A FOUNDED ]===============================================================================
[[ -x ${PROGRAMM} ]] || { script_usage "${R0}Programm not found: No ${BC0}${PROGRAMM}${R0} found.${E}" 2; }
# =[ CREATE LOG_DIR ]=========================================================================================
[[ ! -d ${LOG_DIR}/tests ]] && mkdir -p ${LOG_DIR}/tests
# =[ SET LISTS ]==============================================================================================
if [[ "${#ARGS[@]}" -gt 0 ]];then
    for arg in "${ARGS[@]}";do
        for ft in $(find "${arg}" -type f -name "*.test");do TEST_FILE+=( "${ft}" );done
    done
else
    for arg in $(find "${PARENT_DIR}/src/tests" -type f -name "*.test");do TEST_FILE+=( "${arg}" );done
fi
# =[ LAUNCH TESTS ]===========================================================================================
for tst_file in ${TEST_FILE[@]};do
    filename=${tst_file##*\/}
    res_name=${filename%%\.test*}
    bash_res_name=${LOG_DIR}/tests/$res_name.bsp
    msll_res_name=${LOG_DIR}/tests/$res_name.msl
    comp_file=${LOG_DIR}/tests/$res_name.diff
    fun_log_file=$(print_shorter_path $comp_file)
    <$tst_file bash --posix >$bash_res_name 2>&1
    <$tst_file $PROGRAMM >$msll_res_name 2>&1
    RES_DIFF=$(diff $bash_res_name $msll_res_name > $comp_file && echo 0 || echo 1)
    if [[ "${RES_DIFF}" -eq 0 ]];then
        # PASS --> remove .diff file (empty)
        separators=$(pnt "." $((LEN - $(get_len "🔸${YU}TESTS of ${res_name}:") - 13)))
        print_in_box -t 1 -c g "🔸${YU}TESTS of ${res_name}:${V0} ${separators} ✅ PASS${E}"
        rm $comp_file
    else
        # FAIL --> display error
        separators=$(pnt "." $((LEN - $(get_len "🔸${YU}TESTS of ${res_name}:") - 23)))
        print_in_box -t 1 -c w "🔸${YU}TESTS of ${res_name}${E}:${G0} ${separators} ✖️  DIFF. DETECTED${E}" "    ${Y0}👉 Check log file:${M0}${fun_log_file}${E}"
    fi
    vimdiff $bash_res_name $msll_res_name
done

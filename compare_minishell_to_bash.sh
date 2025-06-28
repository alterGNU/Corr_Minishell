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
MINISHELL=$(find "${MS_DIR}" -type f -name "minishell")           # ☒ minishell program
LOG_DIR="${PARENT_DIR}/log/$(date +%Y_%m_%d/%Hh%Mm%Ss)/tests"     # ☒ Name of the log folder
DEFAULT_TESTS="${PARENT_DIR}//"
TEST=()

# ============================================================================================================
# MAIN
# ============================================================================================================

# =[ CREATE LOG_DIR ]=========================================================================================
#[[ ! -d ${LOG_DIR} ]] && mkdir -p ${LOG_DIR}

#echo MINISHELL=$MINISHELL
#echo PARENT_DIR=$PARENT_DIR
echo LOG_DIR=$LOG_DIR
if [[ "${#ARGS[@]}" -gt 0 ]];then
    echo loop trought each args given
    for arg in "${ARGS[@]}";do
        echo arg=$arg
    done
else
    for file in $(find "${LOG_DIR}" -type f -name "*.test");do
        echo file=$file
    done
fi

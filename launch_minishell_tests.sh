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
MINISHELL=$(find "${MS_DIR}" -type f -name "minishell")           # ☒ minishell program
PARENT_DIR=$(cd $(dirname ${0}) && pwd)                           # ☒ Name of parent directory (TEST_DIR)
LOG_DIR="${PARENT_DIR}/log/$(date +%Y_%m_%d/%Hh%Mm%Ss)"           # ☒ Name of the log folder

# ============================================================================================================
# MAIN
# ============================================================================================================

echo MINISHELL=$MINISHELL
echo PARENT_DIR=$PARENT_DIR
echo LOG_DIR=$LOG_DIR
if [[ "${#ARGS[@]}" -gt 0 ]];then
    echo loop trought each args given
    for arg in "${ARGS[@]}";do
        echo arg=$arg
    done
else
    echo MODE DEFAULT
fi

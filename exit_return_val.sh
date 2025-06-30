#!/bin/bash
bash_rv=$(echo "exit $1" | bash --posix > /dev/null 2>&1 && echo $? || echo $?)
echo "exit $1" | bash --posix
mshl_rv=$(echo "exit $1" | ./minishell > /dev/null 2>&1 && echo $? || echo $?)
echo "exit $1" | ./minishell
echo "bash_rv:${bash_rv} VS mshl_rv:${mshl_rv}"
[[ "${bash_rv}" -eq "${mshl_rv}" ]] && echo "✅PASS" || echo "❌FAIL"

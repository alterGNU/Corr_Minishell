# Corr_Minishell

## Usage
- This repo is use to:
    - **store** our Minishell's project **documentation**:
        - builtin.md : list of builtin to implement and Notes on how to do it.
        - chatgpt.md : Docs on how to start the project.
        - en.subject.pdf : Subject in english.
        - functions.md : Docs on functions allowed, sort by lib to include (signatures + examples).
        - list_allowed_fun.txt : Simple list sorted by alphanum order of function allowed.
        - minishell_exam42.pdf : 42 pages for Minishell Project Correction pages.
    - **launch** our Minishell's project **tests**:
        - all our minishell functions **unitests** write in c and launch by a bash script.
    - **launch** our libft unitest using the Minishell/libft/Makefile using Minishell/Makefile: `make test` cmd
        - `make test-libft OPT="<ARGS>` 🡆 `./Minishell/libft/tests/launch_unitest.sh <ARGS>`
        - <args> value = OPTION availlable
            - NO-ARGS                        🢥  Default behavior:enable all MY_UNITESTS_{LIBFT,GNL,PRINTF,OTHERS}->{MY_UNITESTS}
            - ARGS ∈ {--help, -h}            🢥  Enable HELP option that display script usage---------------------->{MY_UNITESTS, TRIPOUILLE}
            - ARGS ∈ {--no-norm, -n}         🢥  Desable the NORMINETTE tester------------------------------------->{MY_UNITESTS, TRIPOUILLE}
            - ARGS ∈ {--bonus, -b}           🢥  Enable Bonus option for all tester-------------------------------->{MY_UNITESTS, TRIPOUILLE}
            - ARGS ∈ {--all, -a}             🢥  Enable ALL TRIPOUILLE AND MY_UNITESTS OPTION WITHOUT BONUS-------->{MY_UNITESTS, TRIPOUILLE}
            - ARGS ∈ {--tripouille, -t}      🢥  Enable ALL TRIPOUILLE && Disable ALL MY_UNITESTS------------------>{MY_UNITESTS, TRIPOUILLE}
            - ARGS ∈ {--libft, -lft}         🢥  Enable test for LIBFT--------------------------------------------->{MY_UNITESTS, TRIPOUILLE}
            - ARGS ∈ {--ft_printf, -p}       🢥  Enable test for FT_PRINTF----------------------------------------->{MY_UNITESTS, TRIPOUILLE}
            - ARGS ∈ {--get_next_line, -gnl} 🢥  Enable test for GET_NEXT_LINE------------------------------------->{MY_UNITESTS, TRIPOUILLE}
            - ARGS ∈ {--other, -o}           🢥  Enable test for OTHERS FUNCTIONS FOUND---------------------------->{MY_UNITESTS}
            - OPT="-a -b -n" 🡆 launch `--all` testers (MY_UNITEST && TRIPOUILLE) for all function, with `--bonus` part and without norminette-checker `--no-norm`
        - Examples:
            - `make test-libft`                🢥 Default: launch My_unitests tester on any function found in libft.a
            - `make test-libft OPT="-v"`       🢥 Display libft/launch_tests.sh usage.
            - `make test-libft OPT="-n -a -b"` 🢥 Launch both testers for all functions, bonus part include, without norminette-check step.
            - `make test-libft OPT="-g"`       🢥 Launch both testers only on get_next_line() function.

## TODO
### Corr_Minishell
- [ ] Create parser() unitests.
### Minishell
- [ ] Create parser().

## Notes 📓  
### Leaf exec
- while (first_word ∈ '=')
    - if (ft_char_in_str('=', 0)
        - return ERROR
    - else
        - skip to next word
- no next work (cas 0)
    - do nothing
- if word is build-in (cas 1)
    - exec_buildin
- else (cas 2)
    - exec_cmd: search in path, exec if found
   
### Builtin
- export:
    ```c
    $> export t1=a t2=$t1 ls t3=c
    $> env | grep ^t
    t1=a
    t2=
    t3=c
    ```
    - Add all t1,t2 and t3 variable to env_lst, even if ls does not match the export argument's pattern.
    - Variable expansion happend once before exec leaf, that's why t2 doesn't have t1's value
### Questions❓
- [ ] ⚠️ Can we organise our project with folders struct:`minishell/{include/*.h,src/*,libft/**/*,build/*.o,minishell}`

#### Checking-Lexical-Rules such as Detect-Unclosed-{Quotes,Parenthesis} happen before exec:
```bash
$> gaa && gc -m'ce nez PAS fini
'
```
- `gaa` not done at all

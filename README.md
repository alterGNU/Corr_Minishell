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
## Questions❓
- [ ] ⚠️ Can we organise our project with folders struct:`minishell/{include/*.h,src/*,libft/**/*,build/*.o,minishell}`
## Notes 📓  
- [ ] `char **ft_split2(char *src, char **pattern)`
    - ⚠️  `echo coucou&&` == `echo coucou &&` --> like heredoc, take a command to exec

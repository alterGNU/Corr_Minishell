# Corr_Minishell

## TODO
- [.] Unitests : utils_env.c/init_env() --> test if ev==NULL, and else.
    - [X] Create simple visual tests
    - [ ] Create automatics tests that pass
    - [ ] Create automatics tests that fail (fork needed)
- [X] Function : main.c/main() --> write loop
- [X] Structs  : minishell.h --> `t_struct *token` (`.->char *str`, `.->int type`)
- [ ] Function : libft_enhanced-->`get_next_line()`
- [ ] Function : lexer.c/lexer() `char *line` --> `t_struct *token`
    - [X] `static void	free_token(void *ptr)`
    - [ ] `char **build_str_arr_from_str(char *str)`
        - [ ] add token->quotes char:{0,'\'','\"'} // should we add another one that says if a quotes is ended?
	    - [ ] t_lst *tok_lst = build_tok_lst_split_by_quotes(char *str) --from str to t_lst *tok_lst;
	    - [ ] t_lst *tok_lst = build_tok_lst_split_by_sep(char *str, char *sep, int include)
            - include = 0 --> do not include sep as token => sep=" \t\n\r"
            - include = 1 --> include sep as token => sep="&|<>"
	    - [ ] void set_token_type(t_list *res) /
    - [ ] `static t_list *create_tok_lst_node()`
    - [ ] `t_list *build_tok_lst_from_str_arr(char **str)`
    - [ ] `void	check_lexical_rules(t_list **tok_lst)`
- [ ] Unitests : lexer.c/lexer() --> tests
    - [ ] `static void	free_token(void *ptr)`
    - [ ] `char **build_str_arr_from_str(char *str)`
    - [ ] `static t_list *create_tok_lst_node()`
    - [ ] `t_list *build_tok_lst_from_str_arr(char **str)`
    - [ ] `void	check_lexical_rules(t_list **tok_lst)`

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
### Handle unclosed quotes (double or single)
```bash
$> ls | cat && echo "pop
> op" | cat | ls
include
libft
Makefile
src
include  libft	Makefile  src
```
```bash
$> bash-5.2$ echo '1
> ' && echo "2
> " && echo "'3"
1

2

'3
```
- Pseudo-code
    - split --> ["ls", "|", "cat", "&&", "echo \"pop", NULL]
    - build_struct:
        - if last node not quote_terminated (closed)
            - give prompt back, and cmd_to_add=get_next_line(0)
            - store in a tempory file (heredoc) the cmd_to_add until all quote(even the on given in heredoc) are closed.
            - split(concatenate(heredoc))
            - ADD_TO_STRUCT new commandes
    - run trought struct conditionnaly (each leaf == fork)

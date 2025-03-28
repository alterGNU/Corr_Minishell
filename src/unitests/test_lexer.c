#include "minishell.h"  // build_tok_lst_split_by_quotes build_tok_lst_split_by_spaces build_tok_lst_split_by_operators set_tok_lst_type
#include <string.h>     // strncmp
#include <stdio.h>      // printf

#define LEN 90
#define f_name "lexer"

int	printntime(char c, int n)
{
	for (int i = 0 ; i < n; i++)
		ft_printf("%c", c);
	return (n);
}

int	count_char_in_str(char c, char *str)
{
	int	res;

	res = 0;
	while(*str)
	{
		if (*str == c)
			res++;
		str++;
	}
	return (res);
}

void print_title(const char *title)
{
	int print_sofar = ft_printf("\n=[ %s ]", title);
	printntime('=', LEN - print_sofar + 2);
	ft_printf("\n");
}

int	test(char *str, char **tab_res, int *type_res, char **ev)
{
	t_list *env_lst = build_env_lst(ev);
	int	last_cmd_exit_status = 0;
	// Print test header
	int print_sofar = ft_printf("%s(<%s>)", f_name, str);
	if (str)
	{
		int c = count_char_in_str('\t', str);
		if (c)
			print_sofar+=c*4;
	}
	printntime('-', LEN - print_sofar);
	ft_printf("\n");
	// LEXING
	t_list	*tok_lst = lexer(str, &last_cmd_exit_status, &env_lst);
	ft_printf("\nafter lexer:[%d]=", last_cmd_exit_status);
	print_tok_lst(tok_lst);
	ft_printf("\n");

	if (!tok_lst)
	{
		if (!tab_res)
			return (ft_lstclear(&env_lst, free_env), printntime('-', LEN - 3), ft_printf("> ✅\n"), 0);
		return (ft_lstclear(&env_lst, free_env), ft_printf("tab_res=", f_name), ft_print_str_array(tab_res), ft_printf("\ntok_lst=NULL\n"), printntime('-', LEN - 3), ft_printf("> ❌\n"), 1);
	}
	printf("\nEXIT 1\n");
	int	i = 0;
	t_list	*act = tok_lst;
	while (tab_res[i] && act && !strcmp(tab_res[i], ((t_token *)(act->content))->str))
	{
		if (type_res[i] != ((t_token *)act->content)->type)
			return (ft_lstclear(&tok_lst, free_token), printntime('-', LEN - 3), ft_printf("> ❌\n"), 1);
		act = act->next;
		i++;
	}
	ft_printf("tab_res=");
	ft_print_str_array(tab_res);
	ft_printf("\ntok_lst=");
	print_tok_lst(tok_lst);
	ft_printf("\n");
	if (!tab_res[i] && !act)
		return (ft_lstclear(&tok_lst, free_token), ft_lstclear(&env_lst, free_env), printntime('-', LEN - 3), ft_printf("> ✅\n"), 0);
	if ((!tab_res[i] && act) || (tab_res[i] && !act))
		return (ft_lstclear(&tok_lst, free_token), ft_lstclear(&env_lst, free_env), printntime('-', LEN - 3), ft_printf("> ❌\n"), 1);
	if (strcmp(tab_res[i], ((t_token *)(act->content))->str))
		return (ft_lstclear(&tok_lst, free_token), ft_lstclear(&env_lst, free_env), printntime('-', LEN - 3), ft_printf("> ❌\n"), 1);
	return (ft_lstclear(&tok_lst, free_token), ft_lstclear(&env_lst, free_env), ft_printf("> ✅\n"), 0);
}

int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	int	nb_err = 0;

	// TODO: find a way to test this without cause exit() kill testeur
	//print_title("CAS:NULL");
	//nb_err += test(NULL, NULL, NULL, ev);
	//nb_err += test("", NULL, NULL, ev);

	print_title("A| PASS COMMANDS");
	int ai1[13] = {RLS, ESP, UNSET, ESP, UNSET, ESP, PIP, ESP, UNSET, ESP, RRS, ESP, UNSET};
	char *as1[] = {"<", " ", "file1", " ", "cat", " ", "|", " ", "cat", " ", ">", " ", "file2", NULL};
	nb_err += test("< file1 cat | cat > file2", as1, ai1, ev);
	
	int ai2[5] = {UNSET, ESP, UNSET, RRD, UNSET};
	char *as2[] = {"'e'''cho", " ", "toto", ">>", "file1", NULL};
	nb_err += test("'e'''cho toto>>file1", as2, ai2, ev);
	
	int ai3[12] = {ESP, UNSET, ESP, UNSET, OPA, UNSET, ESP, UNSET, OPO, UNSET, ESP, UNSET};
	char *as3[] = {" ","'e'\"c\"ho", " ", "toto", "&&", "echo", " ", "OK", "||", "echo"," ", "KO", NULL};
	nb_err += test("    'e'\"c\"ho  toto&&echo OK||echo  KO", as3, ai3, ev);

	print_title("B| FAIL MULTIPLES");
	nb_err += test("< << <<< <<<< <<<<< <<<<<<", NULL, NULL, ev);
	nb_err += test("> >> >>> >>>> >>>>> >>>>>>", NULL, NULL, ev);
	nb_err += test("| || ||| |||| ||||| ||||||", NULL, NULL, ev);
	nb_err += test("& && &&& &&&& &&&&& &&&&&&", NULL, NULL, ev);
	nb_err += test(" <><<<< < ||| & &&&", NULL, NULL, ev);
	nb_err += test(" <><<<< < ||| & &&&", NULL, NULL, ev);

	print_title("C| FAIL <");
	nb_err += test("cat < |", NULL, NULL, ev);
	nb_err += test("cat < ", NULL, NULL, ev);
	nb_err += test("cat <", NULL, NULL, ev);

	print_title("D| FAIL <<");
	nb_err += test("cat << |", NULL, NULL, ev);
	nb_err += test("cat << ", NULL, NULL, ev);
	nb_err += test("cat <<", NULL, NULL, ev);

	print_title("E| FAIL <<<");
	nb_err += test("<<< |", NULL, NULL, ev);
	nb_err += test("<<< ", NULL, NULL, ev);
	nb_err += test("<<<", NULL, NULL, ev);

	print_title("E| FAIL >");
	nb_err += test("echo toto >|", NULL, NULL, ev);
	nb_err += test("echo toto >", NULL, NULL, ev);
	nb_err += test("echo toto > ", NULL, NULL, ev);

	print_title("G| FAIL >>");
	nb_err += test("echo toto >>|", NULL, NULL, ev);
	nb_err += test("echo toto >>", NULL, NULL, ev);
	nb_err += test("echo toto >> ", NULL, NULL, ev);

	print_title("H| FAIL &&");
	nb_err += test("&&", NULL, NULL, ev);
	nb_err += test("echo toto&&", NULL, NULL, ev);
	nb_err += test("&&echo toto", NULL, NULL, ev);

	print_title("I| FAIL ||");
	nb_err += test("||", NULL, NULL, ev);
	nb_err += test("echo toto||", NULL, NULL, ev);
	nb_err += test("||echo toto", NULL, NULL, ev);

	print_title("J| FAIL |");
	nb_err += test("|", NULL, NULL, ev);
	nb_err += test("ls|", NULL, NULL, ev);
	nb_err += test("|ls", NULL, NULL, ev);

	print_title("K| FAIL ERR_TYPE");
	nb_err += test("<<<<", NULL, NULL, ev);
	nb_err += test(">>>", NULL, NULL, ev);
	nb_err += test("|||", NULL, NULL, ev);
	nb_err += test("&&&", NULL, NULL, ev);
	nb_err += test("&", NULL, NULL, ev);
	nb_err += test("&&&&", NULL, NULL, ev);
	return (nb_err);
}

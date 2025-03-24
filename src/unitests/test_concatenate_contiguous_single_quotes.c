#include "minishell.h"  // build_tok_lst_split_by_quotes build_tok_lst_split_by_spaces build_tok_lst_split_by_operators concatenate_contiguous_single_quotes
#include <string.h>     // strncmp
#include <stdio.h>      // printf

#define LEN 90
#define f_name "concatenate_contiguous_single_quotes"

int	printntime(char c, int n)
{
	for (int i = 0 ; i < n; i++)
		printf("%c", c);
	return (n);
	fflush(stdout);
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
	int print_sofar = printf("=[ %s ]", title);
	printntime('=', LEN - print_sofar + 1);
	printf("\n");
	fflush(stdout);
}

int	test(char *str, char **tab_res)
{
	int	i = 0;
	t_list	*act;
	int print_sofar = printf("%s(<%s>)", f_name, str);
	if (str)
	{
		int c = count_char_in_str('\t', str);
		if (c)
			print_sofar+=c*4;
	}
	t_list	*tok_lst;
	tok_lst = build_tok_lst_split_by_quotes(str);                                // STEP1: split_by_quote(str, "\'\"") 
	map_tok_lst_if_node_not_quoted(&tok_lst, build_tok_lst_split_by_spaces);     // STEP2: split_by_space(str, "\t\r\s\n")
	map_tok_lst_if_node_not_quoted(&tok_lst, build_tok_lst_split_by_operators);  // STEP3: split_by_separator(str, "|&<>","")
	concatenate_contiguous_single_quotes(&tok_lst);

	printntime('-', LEN - print_sofar - 3);
	fflush(stdout);
	t_list	*res = build_tok_lst_split_by_spaces(str);
	if (!res)
	{
		if (!tab_res)
			return (printf("---\n"), printntime('-', LEN - 3), printf("> ✅\n"), 0);
		printf("---\n%s return NULL\ntab_res=", f_name); 
		fflush(stdout);
		ft_print_str_array(tab_res);
		return (printf("\n"), printntime('-', LEN - 3), printf("> ❌\n"), 1);
	}
	act = res;
	while (tab_res[i] && act && !strcmp(tab_res[i], ((t_token *)(act->content))->str))
	{
		act = act->next;
		i++;
	}
	printf("-----\ntab_res=");
	fflush(stdout);
	ft_print_str_array(tab_res);
	printf("\ntok_lst=");
	fflush(stdout);
	print_tok_lst(res);
	printf("\n");
	if (!tab_res[i] && !act)
		return (ft_lstclear(&res, free_token), printntime('-', LEN - 3), printf("> ✅\n"), 0);
	if ((!tab_res[i] && act) || (tab_res[i] && !act))
		return (ft_lstclear(&res, free_token), printntime('-', LEN - 3), printf("> ❌\n"), 1);
	if (strcmp(tab_res[i], ((t_token *)(act->content))->str))
		return (ft_lstclear(&res, free_token), printntime('-', LEN - 3), printf("> ❌\n"), 1);
	return (ft_lstclear(&res, free_token), printf("> ✅\n"), 0);
}

int main()
{
	int	nb_err = 0;

	print_title("CAS:NULL");
	nb_err += test(NULL, NULL);
	nb_err += test("", NULL);

	print_title("SIMPLE CAS NO QUOTES");
	char *tn0[] = {" ", "echo"," ","toto"," ","|","ls",NULL};
	nb_err += test(" echo toto |ls", tn0);
	char *tn1[] = {"super=echo", "&&", "$super", " ", "toto", NULL};
	nb_err += test("super=echo&&$super toto", tn1); // --> echo toto --> toto;

	print_title("SIMPLE CASES WITH QUOTES BUT NO NEED TO CONCATENATE");
	char *t1[] = {" ", "'ec'", " ", "'ho'"," ","toto"," ","|","ls",NULL};
	nb_err += test(" 'ec' 'ho' toto |ls", t1);

	print_title("SIMPLE CASES WITH QUOTES NEED TO CONCATENATE");
	char *t2[] = {"'echo'"," ","toto"," ","|","ls",NULL};
	nb_err += test("'ec''ho' toto |ls", t2);
	char *t3[] = {" ", "'echo'"," ","toto"," ","|","ls",NULL};
	nb_err += test(" 'ec''ho' toto |ls", t3);

	print_title("COMPLEXE IMBRICATION CASES WITH QUOTES NEED TO CONCATENATE");
	char *tt0[] = {"echo"," ","'o\"\"i'", NULL};
	nb_err += test("echo 'o\"''\"i'", tt0);

	return (nb_err);
}

#include "minishell.h"  // build_tok_lst_split_by_quotes build_tok_lst_split_by_spaces build_tok_lst_split_by_operators concatenate_contiguous_single_quotes
#include <string.h>     // strncmp
#include <stdio.h>      // printf

#define LEN 90
#define f_name "concatenate_contiguous_single_quotes"

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
	int print_sofar = ft_printf("=[ %s ]", title);
	printntime('=', LEN - print_sofar + 1);
	ft_printf("\n");
}

int	test(char *str, char **tab_res)
{
	// Print test header
	int print_sofar = ft_printf("%s(<%s>)", f_name, str);
	if (str)
	{
		int c = count_char_in_str('\t', str);
		if (c)
			print_sofar+=c*4;
	}
	printntime('-', LEN - print_sofar);
	// STEP1: split_by_quote(str, "\'\"") 
	ft_printf("\n");
	t_list	*tok_lst = build_tok_lst_split_by_quotes(str);
	ft_printf("\nafter split_by_quote tok_lst=");
	print_tok_lst(tok_lst);
	// STEP2: split_by_space(str, "\t\r\s\n") 
	map_tok_lst_if_node_not_quoted(&tok_lst, build_tok_lst_split_by_spaces);
	ft_printf("\nafter split_by_spaces=");
	print_tok_lst(tok_lst);
  	// STEP3: split_by_separator(str, "|&<>","")
	map_tok_lst_if_node_not_quoted(&tok_lst, build_tok_lst_split_by_operators);
	ft_printf("\nafter split_by_operators=");
	print_tok_lst(tok_lst);
	// STEP4: concatenate
	concatenate_contiguous_single_quotes(&tok_lst);
	ft_printf("\nafter split_by_contiguous_single_quotes=");
	print_tok_lst(tok_lst);
	ft_printf("\n");

	if (!tok_lst)
	{
		if (!tab_res)
			return (printntime('-', LEN - 3), ft_printf("> ✅\n"), 0);
		return (ft_printf("tab_res=", f_name), ft_print_str_array(tab_res), ft_printf("\ntok_lst=NULL\n"), printntime('-', LEN - 3), ft_printf("> ❌\n"), 1);
	}
	int	i = 0;
	t_list	*act = tok_lst;
	while (tab_res[i] && act && !strcmp(tab_res[i], ((t_token *)(act->content))->str))
	{
		act = act->next;
		i++;
	}
	ft_printf("tab_res=");
	ft_print_str_array(tab_res);
	ft_printf("\ntok_lst=");
	print_tok_lst(tok_lst);
	ft_printf("\n");
	if (!tab_res[i] && !act)
		return (ft_lstclear(&tok_lst, free_token), printntime('-', LEN - 3), ft_printf("> ✅\n"), 0);
	if ((!tab_res[i] && act) || (tab_res[i] && !act))
		return (ft_lstclear(&tok_lst, free_token), printntime('-', LEN - 3), ft_printf("> ❌\n"), 1);
	if (strcmp(tab_res[i], ((t_token *)(act->content))->str))
		return (ft_lstclear(&tok_lst, free_token), printntime('-', LEN - 3), ft_printf("> ❌\n"), 1);
	return (ft_lstclear(&tok_lst, free_token), ft_printf("> ✅\n"), 0);
}

int main()
{
	int	nb_err = 0;

	print_title("CAS:NULL");
	nb_err += test(NULL, NULL);
	nb_err += test("", NULL);

	print_title("\nA|SIMPLE CAS NO QUOTES:");
	char *a0[] = {" ", "echo"," ","toto"," ","|","ls",NULL};
	nb_err += test(" echo toto |ls", a0);
	char *a1[] = {"super=echo", "&&", "$super", " ", "toto", NULL};
	nb_err += test("super=echo&&$super toto", a1); // ⚠️  --> echo toto --> toto;

	print_title("\nB|SIMPLE CASES WITH QUOTES BUT NO NEED TO CONCATENATE:");
	char *b0[] = {" ", "'ec'", " ", "'ho'"," ","toto"," ","|","ls",NULL};
	nb_err += test(" 'ec' 'ho' toto |ls", b0);

	print_title("\nC|SIMPLE CASES WITH QUOTES THAT NEED TO BE CONCATENATE:");
	char *c0[] = {" ", "'echo'"," ","toto"," ","|","ls",NULL};
	nb_err += test(" 'ec''ho' toto |ls", c0);
	char *c1[] = {"'echo'"," ","toto"," ","|","ls",NULL};
	nb_err += test("'ec''ho' toto |ls", c1);
	char *c2[] = {"'echo'"," ","'toto'"," ","|","ls",NULL};
	nb_err += test("'e''c''h'o' 't''o''t'o' |ls", c2);

	print_title("\nD|COMPLEXE IMBRICATION CASES WITH QUOTES NEED TO CONCATENATE:");
	char *d0[] = {"echo"," ","'o\"\"i'", NULL};
	nb_err += test("echo 'o\"''\"i'", d0);
	char *d1[] = {"echo"," ","'tototiti", NULL}; // ⚠️  --> exec open quotes (~ heredoc << ')
	nb_err += test("echo 'toto''titi", d1);

	return (nb_err);
}

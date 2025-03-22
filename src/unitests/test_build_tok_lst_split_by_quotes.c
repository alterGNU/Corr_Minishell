#include "minishell.h"  // build_tok_lst_split_by_quotes
#include <string.h>     // strncmp
#include <stdio.h>      // printf

#define LEN 90
#define f_name "build_tok_lst_split_by_quotes"

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

 //	- FROM	: char *str = "    echo "toto tutu"|echo\ttutu     "
 //	- TO	: t_list *res = {v:"    echo ", t:-1, q:-1}->{v:"\"toto tutu\"", t:-1, q:-1}->{v:"|echo\ttutu     ", t:-1, q:-1}->NULL
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
	printntime('-', LEN - print_sofar - 3);
	fflush(stdout);
	t_list	*res = build_tok_lst_split_by_quotes(str);
	if (!res)
	{
		if (!tab_res)
			return (printf("> ✅\n"), 0);
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
	if (!tab_res[i] && !act)
		return (ft_lstclear(&res, free_token), printf("> ✅\n"), 0);
	if ((!tab_res[i] && act) || (tab_res[i] && !act))
	{
		printf("-----\ntab_res=%d",count_char_in_str('\t', str));
		fflush(stdout);
		ft_print_str_array(tab_res);
		printf("\ntok_len=");
		fflush(stdout);
		print_tok_lst(res);
		printf("\n");
		return (ft_lstclear(&res, free_token), printntime('-', LEN - 3), printf("> ❌\n"), 1);
	}
	if (strcmp(tab_res[i], ((t_token *)(act->content))->str))
	{
		printf("-----\ntab_res=%d",count_char_in_str('\t', str));
		fflush(stdout);
		ft_print_str_array(tab_res);
		printf("\ntok_len=");
		fflush(stdout);
		print_tok_lst(res);
		printf("\n");
		return (ft_lstclear(&res, free_token), printntime('-', LEN - 3), printf("> ❌\n"), 1);
	}
	return (ft_lstclear(&res, free_token), printf("> ✅\n"), 0);
}

int main()
{
	int	nb_err = 0;

	print_title("CAS:NULL");
	nb_err += test(NULL, NULL);
	nb_err += test("", NULL);

	print_title("CAS CLASSIC NO QUOTES");
	char *t0[] = {"echo toto", NULL};
	nb_err += test("echo toto", t0);
	char *t1[] = {" echo toto hello world",NULL};
	nb_err += test(" echo toto hello world", t1);

	print_title("CAS CLASSIC WITH QUOTES");
	char *t2[] = {"echo ", "\"hello world\"", NULL};
	nb_err += test("echo \"hello world\"", t2);
	char *t3[] = {"echo ", "\"hello 'world'\""," &&", "'ec'", "ho ", "'slt'", NULL};
	nb_err += test("echo \"hello 'world'\" &&'ec'ho 'slt'", t3);
	char *t4[] = {"     echo ", "\"toto hello world\"", " ", NULL};
	nb_err += test("     echo \"toto hello world\" ", t4);
	char *t5[] = {"     ", "\'ec\'", "ho ", "\'toto hello world\'", " ", NULL};
	nb_err += test("     'ec'ho \'toto hello world\' ", t5);
	char *t6[] = {"'ec'","'ho'","' hello'","world", NULL};
	nb_err += test("'ec''ho'' hello'world", t6);

	print_title("CAS IMBRICATION QUOTES");
	char *t7[] = {"'ec'", "'ho'"," ", "\" hello 'world'\"", "&&echo ", "'\"salut\" monde\'"," | cat toto", NULL};
	nb_err += test("'ec''ho' \" hello 'world'\"&&echo '\"salut\" monde\' | cat toto", t7);

	return (nb_err);
}

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
}

void print_title(const char *title)
{
	int print_sofar = printf("=[ %s ]", title);
	printntime('=', LEN - print_sofar);
	printf("\n");
}

 //	- FROM	: char *str = "    echo "toto tutu"|echo\ttutu     "
 //	- TO	: t_list *res = {v:"    echo ", t:-1, q:-1}->{v:"\"toto tutu\"", t:-1, q:-1}->{v:"|echo\ttutu     ", t:-1, q:-1}->NULL
int	test(char *str, char **res_att)
{
	int	i = 0;
	t_list	*act;
	int print_sofar = printf("%s(<%s>)\n", f_name, str);
	t_list	*res = build_tok_lst_split_by_quotes(str);
	if (!str || !res_att)
	{
		if (!res)
			return (printntime('=', LEN - print_sofar - 3), printf("> ✅\n"), 0);
		return (printntime('=', LEN - print_sofar - 3), printf(" ❌\n"), 1); 
	}
	act = res;
	print_tok_lst(res); // TODO rm then add print_sofar to print_n_time => oneline result
	while (res_att[i] && act && strcmp(res_att[i], ((t_token *)(act->content))->str))
	{
		act = act->next;
		i++;
	}
	if (!res_att[i] && !act)
		return (ft_lstclear(&res, free_token), printntime('=', LEN-3), printf("> ✅\n"), 0);
	if ((!res_att[i] && act) || (res_att[i] && !act))
		return (ft_lstclear(&res, free_token), printntime('=', LEN-3), printf(" ❌\n"), 1);
	if (strcmp(res_att[i], ((t_token *)(act->content))->str))
		return (ft_lstclear(&res, free_token), printntime('=', LEN-3), printf(" ❌\n"), 1);
	return (ft_lstclear(&res, free_token), printntime('=', LEN-3), printf("> ✅\n"), 0);
}

int main()
{
	int	nb_err = 0;

	print_title("CAS:NULL");
	nb_err += test(NULL, NULL);

	print_title("CAS CLASSIC JUST SPACES");
	nb_err += test("echo toto", {"echo toto", NULL});
	nb_err += test("	   	echo toto	hello world    ", {"	   	echo toto	hello world    ",NULL});

	print_title("CAS CLASSIC WITH QUOTES");
	nb_err += test("	   	echo \"toto	hello world\"    ", {"	   	echo ", "\"toto	hello world\"", "    ", NULL});
	nb_err += test("	   	'ec'ho \'toto	hello world\'    ", {"	   	", "\'ec\'", "ho ", "\'toto	hello world\'", "    ", NULL});

	print_title("CAS IMBRICATION QUOTES");
	nb_err += test("	echo    \"\'      \" hello world   \'\" sdf \"\' ", {"\"\'      \"", "hello", "world",   "\'\" sdf \"\'", NULL});

	return (nb_err);
}
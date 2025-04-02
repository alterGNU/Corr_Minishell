#include "minishell.h"  // build_tok_lst_split_by_parenthesis
#include <string.h>     // strncmp
#include <stdio.h>      // printf

#define LEN 90
#define f_name "build_tok_lst_split_by_parenthesis"

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

 //	- FROM	: char *str = "    echo "toto titi"    "
 //	- TO	: t_list *res = {v:"echo", t:-1, q:-1}->{v:"\"toto", t:-1, q:-1}->{v:"titi\"", t:-1, q:-1}->NULL
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
	t_list	*res = build_tok_lst_split_by_parenthesis(str);
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

	print_title("CAS NO PARENTHESIS");
	char *t0[] = {"   abcd   ", NULL};
	nb_err += test("   abcd   ", t0);

	print_title("CAS ONE PARENTHESIS");
	char *t1[] = {"(", NULL};
	nb_err += test("(", t1);
	char *t2[] = {")", NULL};
	nb_err += test(")", t2);

	print_title("CAS ONLY PARENTHESIS (MULTIPLE)");
	char *t5[] = {"(", ")", NULL};
	nb_err += test("()", t5);
	char *t6[] = {")", "(", NULL};
	nb_err += test(")(", t6);
	char *t7[] = {"(", "(", "(", ")", ")", ")", "(", "(", ")", ")", "(", ")",  NULL};
	nb_err += test("((()))(())()", t7);
	char *t8[] = {"  ", "(", "(", ")", ")", "   ", ")", "  ", ")", ")", "  ", "(", "  ", NULL};
	nb_err += test("  (())   )  ))  (  ", t8);

	print_title("CAS NOT ONLY PARENTHESIS");
	char *t9[] = {"(","(","cmd1",")"," && " ,"(", "cmd2", ")", " || cmd3", ")", NULL};
	nb_err += test("((cmd1) && (cmd2) || cmd3)", t9);

	char *t10[] = {"(","cmd1",")","&&","(","(","cmd2",")","||cmd3",")", NULL};
	nb_err += test("(cmd1)&&((cmd2)||cmd3)", t10);

	return (nb_err);
}

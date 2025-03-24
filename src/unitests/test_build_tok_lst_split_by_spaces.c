#include "minishell.h"  // build_tok_lst_split_by_spaces
#include <string.h>     // strncmp
#include <stdio.h>      // printf

#define LEN 90
#define f_name "build_tok_lst_split_by_spaces"

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
	t_list	*res = build_tok_lst_split_by_spaces(str);
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

//     echo   'toto'   'titi'       
//{     echo   }->{'toto'}->{   }->{'titi'}->{       }->NULL
//{echo}->{'toto'}->{ }->{'titi}->{ }->NULL

// -->{     echo   }->{'toto'}->{   }->{'titi'}->{      }
// -->{echo}->{'toto'}->{   }->{'titi'}->{      }

// -->     'ec'ho   'toto'   'titi'      >
// -->{     'ec'ho   }->{'toto'}->{   }->{'titi'}->{      }
// -->{     }->{'ec'}->{ho   }->{'toto'}->{   }->{'titi'}->{      }
// -->{ }->{'ec'}->{ho}->{'toto'}->{ }->{'titi'}->{ }

//      ls | cat      
// ->{ls}->{|}->{cat}
// ->{space}->{ls}->{space}->{|}->{space}->{cat}->{space}
int main()
{
	int	nb_err = 0;

	print_title("CAS:NULL");
	nb_err += test(NULL, NULL);
	nb_err += test("", NULL);

	print_title("CAS FULL SPACES");
	char *t0[] = {" ", NULL};
	nb_err += test(" ", t0);
	nb_err += test("	", t0);
	nb_err += test("      ", t0);
	nb_err += test("			", t0);
	nb_err += test("   	   	   ", t0);

	print_title("CAS CLASSIC NO SPACES");
	char *t1[] = {"i", NULL};
	nb_err += test("i", t1);
	char *t2[] = {"echo'toto'", NULL};
	nb_err += test("echo'toto'", t2);

	print_title("CAS CLASSIC WITH SPACES");
	char *t3[] = {"echo", " ", "\"hello", " ", "world\"", NULL};
	nb_err += test("echo \"hello world\"", t3);
	char *t4[] = {" ", "echo", " ", "hello", " ", "world", " ", NULL};
	nb_err += test("	 echo   	   hello	world	  ", t4);

	return (nb_err);
}

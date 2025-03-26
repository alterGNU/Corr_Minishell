#include "minishell.h"  // build_tok_lst_split_by_quotes build_tok_lst_split_by_spaces build_tok_lst_split_by_operators set_tok_lst_type
#include <string.h>     // strncmp
#include <stdio.h>      // printf

#define LEN 90
#define f_name "set_tok_lst_type"

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

int	test(char *str, char **tab_res, int *type_res)
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
	concatenate_contiguous_str(&tok_lst);
	ft_printf("\nafter split_by_contiguous_single_quotes=");
	print_tok_lst(tok_lst);
	// STEP 5: set_tok_lst_type
	set_tok_lst_type(tok_lst);
	ft_printf("\nafter set_tok_lst_type=");
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

	//print_title("CAS:NULL");
	//nb_err += test(NULL, NULL);
	//nb_err += test("", NULL);

	//print_title("A| SIMPLE CAS NO QUOTES:");
	//char *a1[] = {" ", "echo"," ","toto"," ","|","ls",NULL};
	//nb_err += test(" echo toto |ls", a1);
	//char *a2[] = {"super=echo", "&&", "$super", " ", "toto", NULL};
	//nb_err += test("super=echo&&$super toto", a2); // ⚠️  --> echo toto --> toto;

	//print_title("B| SIMPLE CASES WITH QUOTES BUT NO NEED TO CONCATENATE:");
	//char *b1[] = {" ", "'ec'", " ", "'ho'", " ", "toto", " ", "|", "ls", NULL};
	//nb_err += test("     'ec'   'ho'  toto |ls", b1);

	//print_title("C| SIMPLE CASES WITH QUOTES THAT NEED TO BE CONCATENATE:");
	//char *c1[] = {"'ec''ho'"," ","toto"," ","|","ls",NULL};
	//nb_err += test("'ec''ho' toto |ls", c1);
	//char *c2[] = {"'e''c''h''o'"," ","'t''o''t''o'"," ","|","ls",NULL};
	//nb_err += test("'e''c''h''o' 't''o''t''o' |ls", c2);
	//char *c3[] = {"\"\"''", " ", "echo", " ", "\"t\"u't '''\"\"u", NULL};
	//nb_err += test("\"\"'' echo \"t\"u't '''\"\"u", c3);
	//char *c4[] = {"echo", " ", "tutu", " ", "\"\"", " ", "''", " ", "titi", NULL};
	//nb_err += test("echo tutu    \"\"  ''  titi", c4);
	//char *c5[] = {"c'a'\"t\"", " ", "\"fi\"l'e'", "|", "'c'a\"t\"", ">", "'f'ile\"2\"", NULL};
	//nb_err += test("c'a'\"t\"   \"fi\"l'e'|'c'a\"t\">'f'ile\"2\"", c5);
	//char *c6[] = {" ", "'ec''ho'"," ","toto"," ","|","ls",NULL};
	//nb_err += test(" 'ec''ho' toto |ls", c6);

	//print_title("D| COMPLEXE IMBRICATION CASES WITH QUOTES NEED TO CONCATENATE:");
	//char *d1[] = {"echo", " ", "'o\"''\"i'", NULL};
	//nb_err += test("echo 'o\"''\"i'", d1);
	//char *d2[] = {"'\"\"'echo"," ","toto", NULL};
	//nb_err += test("'\"\"'echo toto", d2);

	//print_title("E| NOT TERMINATED QUOTES");
	//char *e1[] = {"echo"," ","'toto''titi", NULL}; // ⚠️  --> exec open quotes (~ heredoc << ')
	//nb_err += test("echo 'toto''titi", e1);
	//char *e2[] = {"\"'e'''cho ", NULL};            // ⚠️  --> exec open quotes (~ heredoc << ")
	//nb_err += test("\"'e'''cho ", e2);

	print_title("F| ONLY OPERATOR");
	int int_f1[11] =  {RLS, ESP, RLD, ESP, RLT, ESP, ERR, ESP, ERR, ESP, ERR};
	char *char_f1[] = {"<", " ", "<<", " ", "<<<", " ", "<<<<", " ", "<<<<<"," ", "<<<<<<", NULL};
	nb_err += test("< << <<< <<<< <<<<< <<<<<<", char_f1, int_f1);
	int int_f2[12] =  {RRS, ESP, RRD, ESP, ERR, ESP, ERR, ESP, ERR, ESP, ERR};
	char *char_f2[] = {">", " ", ">>", " ", ">>>", " ", ">>>>", " ", ">>>>>"," ", ">>>>>>", NULL};
	nb_err += test("> >> >>> >>>> >>>>> >>>>>>", char_f2, int_f2);
	int int_f3[12] =  {PIP, ESP, OPO, ESP, ERR, ESP, ERR, ESP, ERR, ESP, ERR};
	char *char_f3[] = {"|", " ", "||", " ", "|||", " ", "||||", " ", "|||||"," ", "||||||", NULL};
	nb_err += test("| || ||| |||| ||||| ||||||", char_f3, int_f3);
	int int_f4[12] =  {ERR, ESP, OPA, ESP, ERR, ESP, ERR, ESP, ERR, ESP, ERR};
	char *char_f4[] = {"&", " ", "&&", " ", "&&&", " ", "&&&&", " ", "&&&&&"," ", "&&&&&&", NULL};
	nb_err += test("& && &&& &&&& &&&&& &&&&&&", char_f4, int_f4);
	int int_f5[12] = {ESP, RLS, RRS, ERR, ESP, RLS, ESP, ERR, ESP, ERR, ESP, ERR};
	char *char_f5[] = {" ", "<", ">", "<<<<", " ", "<", " ", "|||", " ", "&", " ", "&&&", NULL};
	nb_err += test(" <><<<< < ||| & &&&", char_f5, int_f5);

	print_title("D| WITH OPERATOR");
	int int_1[12] = {ESP, -1, ESP, -1, OPA, -1, ESP, -1, OPO, -1, ESP, -1};
	char *char_1[] = {" ","'e'\"c\"ho", " ", "toto", "&&", "echo", " ", "OK", "||", "echo"," ", "KO", NULL};
	nb_err += test("    'e'\"c\"ho  toto&&echo OK||echo  KO", char_1, int_1);
	return (nb_err);
}

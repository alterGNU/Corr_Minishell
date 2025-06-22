// =[ INCLUDE ]=================================================================
#include "minishell.h"    // build_tok_lst_split_by_quotes,build_tok_lst_split_by_spaces,build_tok_lst_split_by_operators,set_tok_lst_type
#include <string.h>       // strcmp
#include <stdio.h>        // printf, fflush
						  // ⚠️  Some of minishell print fun. use ~write=>fflush
						  // ⚠️  Depends on libft/array/ft_print_str_array()
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "build_tok_lst_split_by_quotes"
#define E "\033[0m"      // COLOR END
#define CR "\033[0;31m"   // COLOR RED
#define CV "\033[0;32m"   // COLOR GREEN
#define CM "\033[0;33m"   // COLOR BROWN
#define CY "\033[0;93m"   // COLOR YELLOW
#define CB "\033[0;36m"   // COLOR AZURE
#define CG "\033[0;37m"   // COLOR GREY
#define CT "\033[97;100m" // COLOR GREY
#define PASS "> \033[37;42m ✓ \033[0m\n"
#define	FAIL "> \033[30;41m ✗ \033[0m\n"
#define	S1 CT"="E
#define	S2 CB"*"E
#define	S3 "-"
// =[ STRUCT ]==================================================================
typedef struct s_tok
{
	int		type;
	char	*str;
	int		par;
}			t_tok;
// =[ UTILS FUN ]===============================================================
// -[ PRINTNTIME ]--------------------------------------------------------------
int	printntime(char *str, int n)
{
	for (int i = 0 ; i < n; i++)
		printf("%s", str);
	return (n);
}
// -[ PRINT_TITLE ]-------------------------------------------------------------
void print_title(char *title)
{
	printf(S1""CT);
	int psf = printf("[ %s ]", title);
	printntime(S1, LEN - psf - 1);
	printf(E"\n");
}
// -[ PRINT_SUB_TITLE ]---------------------------------------------------------
void print_subtitle(char *subtitle)
{
	printf(S2""CB);
	int psf = printf("( %s )", subtitle);
	printntime(S2, LEN - psf - 1);
	printf(E"\n");
}
// -[ PRINT_SEP ]---------------------------------------------------------------
void print_sep(char *sep)
{
	int	i = -1;
	while (++i < LEN)
		printf("%s", sep);
	printf("\n\n");
}
// -[ COUNT_CHAR_IN_STR ]-------------------------------------------------------
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
// =[ TESTS FUNCTIONS ]=========================================================
/* convert int to t_token->type */
void	print_t_token_type(int i)
{
	if (i == -1)
		printf("UNSET");
	else if (i == 0)
		printf("ESP");
	else if (i ==1)
		printf("CMD");
 	else if (i == 2)
		printf("ARG");
 	else if (i == 10)
		printf("RLS");
 	else if (i == 11)
		printf("RLD");
 	else if (i == 12)
		printf("RLT");
 	else if (i == 13)
		printf("RRS");
 	else if (i == 14)
		printf("RRD");
 	else if (i == 15)
		printf("PIP");
 	else if (i == 20)
		printf("OPO");
 	else if (i == 21)
		printf("OPA");
 	else if (i == 30)
		printf("PARO");
 	else if (i == 31)
		printf("PARC");
 	else if (i == 42)
		printf("ERR");
	else
		printf("???");
}
// print t_tok array
void	display_tok_array(t_tok tab[])
{
	int	i = -1;
	if (!tab)
		printf("NULL");
	while (tab[++i].str)
	{
		printf("{");
		print_t_token_type(tab[i].type);
		printf(",%s,%d}-->",tab[i].str,tab[i].par);
	}
	printf("NULL");
}
// print tok_lst
void	display_tok_lst(t_list *tok_lst)
{
	t_token	*token;
	t_list	*act = tok_lst;
	while (act)
	{
		token = ((t_token *)act->content);
		printf("{");
		print_t_token_type(token->type);
		printf(",%s,%d}-->",token->str,token->parenthesis);
		act = act->next;
	}
	printf("NULL");
}
// Return size of t_tok tab
int	len_of_tab_res(t_tok tab[])
{
	int	i = 0;
	if (!tab)
		return (0);
	while (tab[i].str)
		i++;
	return (i);
}
// Compare a t_token and a t_tok
int	tok_diff_token(t_tok tok, t_token *token)
{
	if (tok.type != token->type)
		return (1);
	if (strcmp(tok.str, token->str))
		return (1);
	return (0);
}

// This function print details only on failures.
int	test(char *str, t_tok tab_res[])
{
	// Print test header
	int print_sofar	 = printf("%s(", f_name);
	printf(CB);
	print_sofar 	+= printf("%s", str);
	printf(E);
	print_sofar 	+= printf(")");
	if (str)
	{
		int c = count_char_in_str('\t', str);
		if (c)
			print_sofar+=c*4;
	}
	printntime(S3, LEN - print_sofar);
	printf("\n");
	// STEP 1
	t_list *tok_lst = build_tok_lst_split_by_quotes(str);
	// CHECK TOK_LST == NULL
	if (!tok_lst)
	{
		if (!tab_res)
			return (printf(CV" (tok_lst == tab_res == NULL)\n"E),printntime(S3, LEN - 5), printf(PASS), 0);
		write(1, "\n", 1);
		return (printntime(S3, LEN - 5), printf(FAIL), 1);
	}
	// Print result
	printf("tab_res=");
	display_tok_array(tab_res);
	printf("\ntok_lst=");
	display_tok_lst(tok_lst);
	printf("\n");
	// COMPARE TOTAL SIZE
	int len_tab_res = len_of_tab_res(tab_res);
	int len_tok_lst = ft_lstsize(tok_lst);
	if (len_tok_lst != len_tab_res)
		return (printntime(S3, LEN - 5), printf(FAIL), 1);
	// COMPARE EACH NODE
	int	i = 0;
	t_list	*act = tok_lst;
	while (tab_res[i].str && act)
	{
		if (tok_diff_token(tab_res[i], ((t_token *)act->content)))
		{
			printf(CR"tok diff. token at i=%d:\n", i);
			printf("tok  ={");
			print_t_token_type(tab_res[i].type);
			printf(",%s,%d}\n",tab_res[i].str,tab_res[i].par);
			printf("token={");
			print_t_token_type(((t_token *)act->content)->type);
			printf(",%s,%d}\n"E,((t_token *)act->content)->str,((t_token *)act->content)->parenthesis);
			return (ft_lstclear(&tok_lst, free_token),printntime(S3, LEN - 5), printf(FAIL), 1);
		}
		act = act->next;
		i++;
	}
	return (ft_lstclear(&tok_lst, free_token),printntime(S3, LEN - 5), printf(PASS), 0);
}

// =============================================================================
// MAIN
// =============================================================================
int	main(void)
{
	int	nb_err = 0;
	// =[  ]====================================================================
	print_title("0| NULL CASES");
	// -[  ]--------------------------------------------------------------------
	print_subtitle("str==NULL");
	nb_err += test(NULL, NULL);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("str==Empty");
	nb_err += test("", NULL);
	print_sep(S2);
	print_sep(S1);
	// =[  ]====================================================================
	print_title("A| NO QUOTES");
	t_tok a0[]={{-1,"echo toto&&echo titi",0},{0,0,0}};
	nb_err += test("echo toto&&echo titi", a0);
	print_sep(S1);
	// =[  ]====================================================================
	print_title("B| ONLY ONE TYPE AT THE TIME");
	// -[  ]--------------------------------------------------------------------
	print_subtitle("ONLY SINGLE QUOTES");
	t_tok b0[] = {{-1,"''",0},{0,0,0}};
	nb_err += test("''", b0);
	t_tok b1[] = {{-1,"''",0},{-1,"''",0},{0,0,0}};
	nb_err += test("''''", b1);
	t_tok b2[] = {{-1,"'hello'",0},{-1,"'world'",0},{0,0,0}};
	nb_err += test("'hello''world'", b2);
	t_tok b3[] = {{-1,"'hello'",0},{-1," ",0},{-1,"'world'",0},{0,0,0}};
	nb_err += test("'hello' 'world'", b3);
	t_tok b4[] = {{-1,"'hello'",0},{-1,"the",0},{-1,"'world'",0},{0,0,0}};
	nb_err += test("'hello'the'world'", b4);
	t_tok b5[] = {{-1,"wow",0},{-1,"'hello'",0},{-1,"the",0},{-1,"'amazing'",0},{-1,"world",0},{0,0,0}};
	nb_err += test("wow'hello'the'amazing'world", b5);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("ONLY DOUBLE QUOTES");
	t_tok b6[] = {{-1,"\"\"",0},{0,0,0}};
	nb_err += test("\"\"", b6);
	t_tok b7[] = {{-1,"\"\"",0},{-1,"\"\"",0},{0,0,0}};
	nb_err += test("\"\"\"\"", b7);
	t_tok b8[] = {{-1,"\"hello\"",0},{-1,"\"world\"",0},{0,0,0}};
	nb_err += test("\"hello\"\"world\"", b8);
	t_tok b9[] = {{-1,"\"hello\"",0},{-1," ",0},{-1,"\"world\"",0},{0,0,0}};
	nb_err += test("\"hello\" \"world\"", b9);
	t_tok b10[] = {{-1,"\"hello\"",0},{-1,"the",0},{-1,"\"world\"",0},{0,0,0}};
	nb_err += test("\"hello\"the\"world\"", b10);
	t_tok b11[] = {{-1,"wow",0},{-1,"\"hello\"",0},{-1,"the",0},{-1,"\"amazing\"",0},{-1,"world",0},{0,0,0}};
	nb_err += test("wow\"hello\"the\"amazing\"world", b11);
	print_sep(S2);
	// =[  ]====================================================================
	print_title("C| MIX & TWIX");
	// -[  ]--------------------------------------------------------------------
	print_subtitle("NO IMBRICATION");
	t_tok c0[] = {{-1,"\"\"",0},{-1,"''",0},{0,0,0}};
	nb_err += test("\"\"''", c0);
	t_tok c1[] = {{-1,"\"hello\"",0},{-1,"'world'",0},{0,0,0}};
	nb_err += test("\"hello\"'world'", c1);
	t_tok c2[] = {{-1,"wow",0},{-1,"\"hello\"",0},{-1,"the",0},{-1,"'amazing'",0},{-1,"world",0},{0,0,0}};
	nb_err += test("wow\"hello\"the'amazing'world", c2);
	print_sep(S2);
	print_subtitle("IMBRICATION");
	t_tok c3[] = {{-1,"\"''\"",0},{-1,"'\"\"'",0},{0,0,0}};
	nb_err += test("\"''\"'\"\"'", c3);
	t_tok c4[] = {{-1,"\"coucou' 'petite\"",0},{-1,"'perruche'",0},{0,0,0}};
	nb_err += test("\"coucou' 'petite\"'perruche'", c4);
	t_tok c5[] = {{-1,"'coucou\" \"petite'",0},{-1,"\"perruche\"",0},{0,0,0}};
	nb_err += test("'coucou\" \"petite'\"perruche\"", c5);
	print_sep(S2);
	print_sep(S1);
	return (nb_err);
}

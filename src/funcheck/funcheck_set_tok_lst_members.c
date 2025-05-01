// =[ INCLUDE ]=================================================================
#include "minishell.h"    // build_tok_lst_split_by_quotes,build_tok_lst_split_by_spaces,build_tok_lst_split_by_operators,set_tok_lst_type
#include <string.h>       // strcmp
#include <stdio.h>        // printf, fflush
						  // ⚠️  Some of minishell print fun. use ~write=>fflush
						  // ⚠️  Depends on libft/array/ft_print_str_array()
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "set_tok_lst_members"
#define CE "\033[0m"      // COLOR END
#define CR "\033[0;31m"   // COLOR RED
#define CV "\033[0;32m"   // COLOR GREEN
#define CM "\033[0;33m"   // COLOR BROWN
#define CY "\033[0;93m"   // COLOR YELLOW
#define CB "\033[0;36m"   // COLOR AZURE
#define CG "\033[0;37m"   // COLOR GREY
#define CT "\033[97;100m" // COLOR GREY
#define PASS "> \033[37;42m ✓ \033[0m\n"
#define	FAIL "> \033[30;41m ✗ \033[0m\n"
#define	S1 CT"="CE
#define	S2 CB"*"CE
#define	S3 "-"
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
	printf(CE"\n");
}
// -[ PRINT_SUB_TITLE ]---------------------------------------------------------
void print_subtitle(char *subtitle)
{
	printf(S2""CB);
	int psf = printf("( %s )", subtitle);
	printntime(S2, LEN - psf - 1);
	printf(CE"\n");
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
// print tok_lst_const
void	display_token_array(t_token token_arr[])
{
	if (token_arr)
	{
		int i = -1;
		while (token_arr[++i].str)
		{
			printf("{");
			print_t_token_type(token_arr[i].type);
			printf(",%s,%d}-->",token_arr[i].str,token_arr[i].parenthesis);
		}
	}
	printf("NULL");
}
// Return size of t_token array
int	len_of_tab_res(t_token tab[])
{
	int	i = 0;
	if (!tab)
		return (0);
	while (tab[i].str)
		i++;
	return (i);
}
// Compare a t_token and a t_tok
int	tokcst_diff_token(t_token tok_cst, t_token *token)
{
	if (tok_cst.type != token->type)
		return (1);
	if (strcmp(tok_cst.str, token->str))
		return (1);
	if (tok_cst.parenthesis != token->parenthesis)
		return (1);
	return (0);
}

// This function print details only on failures.
int	test(t_data *dt, char *str, t_token tab_res[])
{
	// Print test header
	int print_sofar	 = printf("%s(", f_name);
	printf(CB);
	print_sofar 	+= printf("%s", str);
	printf(CE);
	print_sofar 	+= printf(")");
	if (str)
	{
		int c = count_char_in_str('\t', str);
		if (c)
			print_sofar+=c*2;
	}
	printntime(S3, LEN - print_sofar);
	printf("\n");
	// STEP 1
	dt->tok_lst = build_tok_lst_split_by_quotes(str);
	if (!dt->tok_lst)
		write(1, "\n", 1);
	// STEP 2
	map_tok_lst_if_node_not_quoted(&dt->tok_lst, build_tok_lst_split_by_spaces);
	// STEP 3
	map_tok_lst_if_node_not_quoted(&dt->tok_lst, build_tok_lst_split_by_operators);
	// STEP 4
	map_tok_lst_if_node_not_quoted(&dt->tok_lst, build_tok_lst_split_by_parenthesis);
	// STEP 5
	concatenate_contiguous_str(&dt->tok_lst);
	// STEP 6
	set_tok_lst_members(dt);
	// CHECK TOK_LST == NULL
	if (!dt->tok_lst)
	{
		if (!tab_res)
			return (printf(CV"dt->tok_lst == tab_res == NULL\n"CE),printntime(S3, LEN - 5), printf(PASS), 0);
		write(1, "\n", 1);
		return (printntime(S3, LEN - 5), printf(FAIL), 1);
	}
	// Print result
	printf("dt->odd_par_nbr=%d\ndt->pair_of_par=%d\ntab_res    =",dt->odd_par_nbr,dt->pair_of_par);
	display_token_array(tab_res);
	printf("\ndt->tok_lst=");
	display_tok_lst(dt->tok_lst);
	printf("\n");
	// COMPARE TOTAL SIZE
	int len_tab_res = len_of_tab_res(tab_res);
	int len_tok_lst = ft_lstsize(dt->tok_lst);
	if (len_tok_lst != len_tab_res)
		return (printntime(S3, LEN - 5), printf(FAIL), 1);
	// COMPARE EACH NODE
	int	i = 0;
	t_list	*act = dt->tok_lst;
	while (tab_res[i].str && act)
	{
		if (tokcst_diff_token(tab_res[i], ((t_token *)act->content)))
		{
			printf(CR"tok diff. token at i=%d:\n", i);
			printf("tok_cst={");
			print_t_token_type(tab_res[i].type);
			printf(",%s,%d}\n",tab_res[i].str,tab_res[i].parenthesis);
			printf("token ={");
			print_t_token_type(((t_token *)act->content)->type);
			printf(",%s,%d}\n"CE,((t_token *)act->content)->str,((t_token *)act->content)->parenthesis);
			return (ft_lstclear(&dt->tok_lst, free_token),printntime(S3, LEN - 5), printf(FAIL), 1);
		}
		act = act->next;
		i++;
	}
	return (ft_lstclear(&dt->tok_lst, free_token),printntime(S3, LEN - 5), printf(PASS), 0);
}

// =============================================================================
// MAIN
// =============================================================================
int main(int ac, char **av, char **ev)
{
	int	nb_err = 0;
	(void) ac;
	(void) av;
	t_data	*dt = init_data(ev);
	// =[  ]====================================================================
	print_title("0| NULL CASES");
	// -[  ]--------------------------------------------------------------------
	print_subtitle("str==NULL");
	nb_err += test(dt, NULL, NULL);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("str==Empty");
	nb_err += test(dt, "", NULL);
	print_sep(S2);
	print_sep(S1);
	// =[ 	 ]==================================================================
	print_title("A| SET TYPE");
	//t_token a0[]={{ESP," ",0},{UNSET,"echo",0},{ESP," ",0},{UNSET,"coucou",0},{ESP," ",0},{UNSET,"petite",0},{ESP," ",0},{UNSET,"perruche",0},{ESP," ",0},{0,0,0}};
	//nb_err += test(dt, " echo coucou petite perruche ", a0);
	//t_token a1[]={{RLS,"<",0},{ESP," ",0},{RLD,"<<",0},{ESP," ",0},{RLT,"<<<",0},{ESP," ",0},{ERR,"<<<<",0},{ESP," ",0},{ERR,"<<<<<",0},{0,0,0}};
	//nb_err += test(dt, "< << <<< <<<< <<<<<", a1);
	//t_token a2[]={{RRS,">",0},{ESP," ",0},{RRD,">>",0},{ESP," ",0},{ERR,">>>",0},{ESP," ",0},{ERR,">>>>",0},{ESP," ",0},{ERR,">>>>>",0},{0,0,0}};
	//nb_err += test(dt, "> >> >>> >>>> >>>>>", a2);
	//t_token a3[]={{PIP,"|",0},{ESP," ",0},{OPO,"||",0},{ESP," ",0},{ERR,"|||",0},{ESP," ",0},{ERR,"||||",0},{ESP," ",0},{ERR,"|||||",0},{0,0,0}};
	//nb_err += test(dt, "| || ||| |||| |||||", a3);
	//t_token a4[]={{ERR,"&",0},{ESP," ",0},{OPA,"&&",0},{ESP," ",0},{ERR,"&&&",0},{ESP," ",0},{ERR,"&&&&",0},{ESP," ",0},{ERR,"&&&&&",0},{0,0,0}};
	//nb_err += test(dt, "& && &&& &&&& &&&&&", a4);
	t_token a5[]={{ESP," ",0},{ERR,"&",0},{RLS,"<",0},{RRS,">",0},{PIP,"|",0},\
				  {ESP," ",0},{OPA,"&&",0},{RLD,"<<",0},{RRD,">>",0},{OPO,"||",0},\
				  {ESP," ",0},{ERR,"&&&",0},{RLT,"<<<",0},{ERR,">>>",0},{ERR,"|||",0},\
				  {ESP," ",0},{ERR,"&&&&",0},{ERR,"<<<<",0},{ERR,">>>>",0},{ERR,"||||",0},\
				  {ESP," ",0},{0,0,0}};
	nb_err += test(dt, " &<>|  &&<<>>||   &&&<<<>>>|||    &&&&<<<<>>>>||||     ", a5);
	print_sep(S1);
	// =[  ]====================================================================
	print_title("B| SET QUOTES");
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Case of concat_contiguous_str that start with quoted token");
	t_token b0[]={{ESP," ",0},{UNSET,"'e'ch\"o\"",0},{ESP," ",0},{UNSET,"\"coucou 'petite' perruche\"",0},{0,0,0}};
	nb_err += test(dt, " 'e'ch\"o\" \"coucou 'petite' perruche\"", b0);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	//print_subtitle("Case of concat_contiguous_str that does not start unquoted token");
	//t_token b1[]={{UNSET,"e'c'h\"o\"",0},{ESP," ",0},{UNSET,"\"coucou 'petite' perruche\"",0},{0,0,0}};
	//nb_err += test(dt, "e'c'h\"o\" \"coucou 'petite' perruche\"", b1);
	//print_sep(S2);
	print_sep(S1);
	// =[  ]====================================================================
	print_title("C| SET PARENTHESIS");
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("Simple:No priority changes");
	//t_token c0[]={{PARO,"(",1},{UNSET,"echo",1},{ESP," ",1},{UNSET,"toto",1},{PARC,")",0},{0,0,0}};
	//nb_err += test(dt, "(echo toto)", c0);
	//print_sep(S2);
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("Simple:With priority changes");
	//t_token c1[]={{PARO,"(",1},{UNSET,"cmd1",1},{OPA,"&&",1},{UNSET,"cmd2",1},{PARC,")",0},{OPO,"||",0},{PARO,"(",1},{UNSET,"cmd3",1},{OPA,"&&",1},{UNSET,"cmd4",1},{PARC,")",0},{0,0,0}};
	//nb_err += test(dt, "(cmd1&&cmd2)||(cmd3&&cmd4)", c1);
	//print_sep(S2);
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("Imbrication:No priority changes");
	//t_token c2[]={{PARO,"(",1},{PARO,"(",2},{UNSET,"cmd1",2},{PARC,")",1},{OPA,"&&",1},{PARO,"(",2},{UNSET,"cmd2",2},{PARC,")",1},{PARC,")",0},{0,0,0}};
	//nb_err += test(dt, "((cmd1)&&(cmd2))", c2);
	//print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Imbrication:With priority changes");
	t_token c3[]={{PARO,"(",1},{PARO,"(",2},{PARO,"(",3},{UNSET,"cmd1",3},{PARC,")",2},{OPA,"&&",2},{PARO,"(",3},{UNSET,"cmd2",3},{PARC,")",2},{PARC,")",1},{OPO,"||",1},{PARO,"(",2},{PARO,"(",3},{UNSET,"cmd3",3},{PARC,")",2},{OPA,"&&",2},{PARO,"(",3},{UNSET,"cmd4",3},{PARC,")",2},{PARC,")",1},{PARC,")",0},{0,0,0}};
	nb_err += test(dt, "(((cmd1)&&(cmd2))||((cmd3)&&(cmd4)))", c3);
	print_sep(S2);
	print_sep(S1);
	return (free_data(&dt), nb_err);
}

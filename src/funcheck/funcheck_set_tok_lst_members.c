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
int printntime(char *str, int n)
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
// a==b return 0, else return 1
int	compare_int(int a, int b)
{
	if (a != b)
		return (1);
	return (0);
}

int	compare_token(t_token *a, t_token b)
{
	return (compare_int(a->type, b.type) + strcmp(a->str, b.str)+ compare_int(a->parenthesis, b.parenthesis));
}

void	print_token_arr(t_token *tab)
{
	int i;

	i = -1;
	while (tab[++i].str)
			printf("{%d,%s,%d}-->",tab[i].type,tab[i].str,tab[i].parenthesis);
	printf("NULL");
}

int	test(char *str, t_token tab_res[])
{
	// Print test header
	int print_sofar = printf("%s(%s)", f_name, str);
	if (str)
	{
		int c = count_char_in_str('\t', str);
		if (c)
			print_sofar+=c*4;
	}
	printntime(S3, LEN - print_sofar);
	t_list	*tok_lst = build_tok_lst_split_by_quotes(str);                       // STEP1: split by quote
	map_tok_lst_if_node_not_quoted(&tok_lst, build_tok_lst_split_by_spaces);     // STEP2: split by space
	map_tok_lst_if_node_not_quoted(&tok_lst, build_tok_lst_split_by_operators);  // STEP3: split by operator
	map_tok_lst_if_node_not_quoted(&tok_lst, build_tok_lst_split_by_parenthesis);// STEP4: split by parenthesis
	concatenate_contiguous_str(&tok_lst);                                        // STEP5: concatenate contiguous unset
	if (!tok_lst)
		write(1, "\n", 1);
	set_tok_lst_members(tok_lst);                                                // 🎯STEP 6: set tok_lst members (type, parenthesis, quote)
	printf("\ntab_res=");
	print_token_arr(tab_res);
	printf("\ntok_lst=");
	fflush(stdout);
	print_tok_lst(tok_lst);
	printf("\n");
	// CHECK NULL CASES
	if (!tok_lst)
	{
		if (!tab_res)
			return (printntime(S3, LEN - 5), printf(PASS), 0);
		return (printntime(S3, LEN - 5), printf(FAIL), 1);
	}
	// Get len of tab_res
	int tab_len = 0;
	int	i = -1;
	while (tab_res[++i].str)
		tab_len++;
	// Get len of tok_lst
	int lst_len = ft_lstsize(tok_lst);
	// COMPARE SIZE
	if (lst_len != tab_len)
		return (ft_lstclear(&tok_lst, free_token), printntime(S3, LEN - 5), printf(FAIL), 1);
	// COMPARE EACH NODE
	i = 0;
	t_list *act = tok_lst;
	while (i < tab_len && act)
	{
		if(compare_token(((t_token *)act->content), tab_res[i]))
		{
			printf(CR"Diff. Token at i=%d:\n tok_lst token=", i);
			printf("{%d,%s,%d}",((t_token *)act->content)->type,((t_token *)act->content)->str,((t_token *)act->content)->parenthesis);
			printf("\n tab_res token=");
			printf("{%d,%s,%d}\n"CE,tab_res[i].type,tab_res[i].str,tab_res[i].parenthesis);
			return (ft_lstclear(&tok_lst, free_token), printntime(S3, LEN - 5), printf(FAIL), 1);
		}
		i++;
		act = act->next;
	}
	return (ft_lstclear(&tok_lst, free_token), printntime(S3, LEN - 5), printf(PASS), 0);
}

int main()
{
	int	nb_err = 0;
	// =[ 	 ]==================================================================
	print_title("A| SET TYPE");
	t_token a0[]={{ESP," ",0},{UNSET,"echo",0},{ESP," ",0},{UNSET,"coucou",0},{ESP," ",0},{UNSET,"petite",0},{ESP," ",0},{UNSET,"perruche",0},{ESP," ",0},{0,0,0}};
	nb_err += test(" echo coucou petite perruche ", a0);
	t_token a1[]={{RLS,"<",0},{ESP," ",0},{RLD,"<<",0},{ESP," ",0},{RLT,"<<<",0},{ESP," ",0},{ERR,"<<<<",0},{ESP," ",0},{ERR,"<<<<<",0},{0,0,0}};
	nb_err += test("< << <<< <<<< <<<<<", a1);
	//t_token a2[]={{RRS,">",0},{ESP," ",0},{RRD,">>",0},{ESP," ",0},{ERR,">>>",0},{ESP," ",0},{ERR,">>>>",0},{ESP," ",0},{ERR,">>>>>",0},{0,0,0}};
	//nb_err += test("> >> >>> >>>> >>>>>", a2);
	//t_token a3[]={{PIP,"|",0},{ESP," ",0},{OPO,"||",0},{ESP," ",0},{ERR,"|||",0},{ESP," ",0},{ERR,"||||",0},{ESP," ",0},{ERR,"|||||",0},{0,0,0}};
	//nb_err += test("| || ||| |||| |||||", a3);
	//t_token a4[]={{ERR,"&",0},{ESP," ",0},{OPA,"&&",0},{ESP," ",0},{ERR,"&&&",0},{ESP," ",0},{ERR,"&&&&",0},{ESP," ",0},{ERR,"&&&&&",0},{0,0,0}};
	//nb_err += test("& && &&& &&&& &&&&&", a4);
	print_sep(S1);
	// =[  ]====================================================================
	print_title("B| SET QUOTES");
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Case of concat_contiguous_str that start with quoted token");
	t_token b0[]={{ESP," ",0},{UNSET,"'e'ch\"o\"",0},{ESP," ",0},{UNSET,"\"coucou 'petite' perruche\"",0},{0,0,0}};
	nb_err += test(" 'e'ch\"o\" \"coucou 'petite' perruche\"", b0);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	//print_subtitle("Case of concat_contiguous_str that does not start unquoted token");
	//t_token b1[]={{UNSET,"e'c'h\"o\"",0},{ESP," ",0},{UNSET,"\"coucou 'petite' perruche\"",0},{0,0,0}};
	//nb_err += test("e'c'h\"o\" \"coucou 'petite' perruche\"", b1);
	//print_sep(S2);
	print_sep(S1);
	// =[  ]====================================================================
	print_title("C| SET PARENTHESIS");
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("Simple:No priority changes");
	//t_token c0[]={{PARO,"(",1},{UNSET,"echo",1},{ESP," ",1},{UNSET,"toto",1},{PARC,")",0},{0,0,0}};
	//nb_err += test("(echo toto)", c0);
	//print_sep(S2);
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("Simple:With priority changes");
	//t_token c1[]={{PARO,"(",1},{UNSET,"cmd1",1},{OPA,"&&",1},{UNSET,"cmd2",1},{PARC,")",0},{OPO,"||",0},{PARO,"(",1},{UNSET,"cmd3",1},{OPA,"&&",1},{UNSET,"cmd4",1},{PARC,")",0},{0,0,0}};
	//nb_err += test("(cmd1&&cmd2)||(cmd3&&cmd4)", c1);
	//print_sep(S2);
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("Imbrication:No priority changes");
	//t_token c2[]={{PARO,"(",1},{PARO,"(",2},{UNSET,"cmd1",2},{PARC,")",1},{OPA,"&&",1},{PARO,"(",2},{UNSET,"cmd2",2},{PARC,")",1},{PARC,")",0},{0,0,0}};
	//nb_err += test("((cmd1)&&(cmd2))", c2);
	//print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Imbrication:With priority changes");
	t_token c3[]={{PARO,"(",1},{PARO,"(",2},{PARO,"(",3},{UNSET,"cmd1",3},{PARC,")",2},{OPA,"&&",2},{PARO,"(",3},{UNSET,"cmd2",3},{PARC,")",2},{PARC,")",1},{OPO,"||",1},{PARO,"(",2},{PARO,"(",3},{UNSET,"cmd3",3},{PARC,")",2},{OPA,"&&",2},{PARO,"(",3},{UNSET,"cmd4",3},{PARC,")",2},{PARC,")",1},{PARC,")",0},{0,0,0}};
	nb_err += test("(((cmd1)&&(cmd2))||((cmd3)&&(cmd4)))", c3);
	print_sep(S2);
	print_sep(S1);
	return (nb_err);
}

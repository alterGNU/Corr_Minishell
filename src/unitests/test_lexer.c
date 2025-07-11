// =[ INCLUDE ]=================================================================
#include "minishell.h"    // 
#include <string.h>       // strcmp
#include <stdio.h>        // printf, fflush
						  // ⚠️  Some of minishell print fun. use ~write=>fflush
						  // ⚠️  Depends on libft/array/ft_print_str_array()
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "lexer"
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
int	test(char **ev, char *str, t_token tab_res[])
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
			print_sofar+=c*2;
	}
	printntime(S3, LEN - print_sofar);
	printf("\n");
	fflush(stdout);
	// STEP 0
	t_data *dt = init_data(ev);
	if (!dt)
		return (ft_fprintf(2, "init_data()->fail"));
	dt->line = strdup(str);
	if (!dt->line)
		return (free_data(&dt), ft_fprintf(2, "init_data()->fail"));
	// STEP 1
	lexer(&dt);
	// CHECK TOK_LST == NULL
	if (!dt->tok_lst)
	{
		if (!tab_res)
			return (free_data(&dt), printf(CV"tok_lst == tab_res == NULL\n"E),printntime(S3, LEN - 5), printf(PASS), 0);
		write(1, "\n", 1);
		return (free_data(&dt), printntime(S3, LEN - 5), printf(FAIL), 1);
	}
	// Print result
	printf("dt->odd_par_nbr=%d\ntab_res=", dt->odd_par_nbr);
	display_token_array(tab_res);
	printf("\ntok_lst=");
	display_tok_lst(dt->tok_lst);
	printf("\n");
	// COMPARE TOTAL SIZE
	int len_tab_res = len_of_tab_res(tab_res);
	int len_tok_lst = ft_lstsize(dt->tok_lst);
	if (len_tok_lst != len_tab_res)
		return (printf(CR"DIFF.IN.SIZE:len_tab_res=%d VS len_tok_lst=%d\n"E, len_tab_res, len_tok_lst), printntime(S3, LEN - 5), printf(FAIL), 1);
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
			printf(",%s,%d}\n"E,((t_token *)act->content)->str,((t_token *)act->content)->parenthesis);
			return (free_data(&dt),printntime(S3, LEN - 5), printf(FAIL), 1);
		}
		act = act->next;
		i++;
	}
	return (free_data(&dt),printntime(S3, LEN - 5), printf(PASS), 0);
}

// =============================================================================
// MAIN
// =============================================================================
int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	int	nb_err = 0;

	////TODO: find a way to test this without cause exit() kill testeur
	//print_title("0| NULL CASES");
	//nb_err += test(ev,NULL,NULL);
	//nb_err += test(ev,"",NULL);
	//print_sep(S2);
	// =[  ]====================================================================
	print_title("A| FAILS UNSUPPORT OPERATORS");
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Cases of 'PROCESS SUBSTITUTION' (Not Handle For Now)");
	nb_err += test(ev,"<(cmd)",NULL);
	nb_err += test(ev,">(cmd)",NULL);
	print_sep(S2);
	// -[ 	 ]------------------------------------------------------------------
	print_subtitle("Cases of 'ARITHMETIC OPERATOR' (Not Handle For Now)");
	nb_err += test(ev,"(())",NULL);
	nb_err += test(ev,"(( ))",NULL);
	nb_err += test(ev,"((0))",NULL);
	nb_err += test(ev,"((echo toto))",NULL);
	nb_err += test(ev,"((1 + 2))",NULL);
	print_sep(S2);
	// =[  ]====================================================================
	print_title("B| FAILS UNKNOWN OPERATORS");
	// -[  ]--------------------------------------------------------------------
	print_subtitle("List of 'UNKNOWN operators' == type:ERR");
	nb_err += test(ev,"<<<<",NULL);
	nb_err += test(ev,"<<<<f1",NULL);
	nb_err += test(ev,">>>",NULL);
	nb_err += test(ev,">>>f1",NULL);
	nb_err += test(ev,"|||",NULL);
	nb_err += test(ev,"cmd1|||cmd2",NULL);
	nb_err += test(ev,"&&&",NULL);
	nb_err += test(ev,"cmd1&&&cmd2",NULL);
	print_sep(S1);
	// =[  ]====================================================================
	print_title("C| FAILS OF UNARY OPERATOR SYNTAX ");
	print_subtitle("Cases of '<' RSL operator");
	nb_err += test(ev,"<",NULL);
	nb_err += test(ev,"< ",NULL);
	nb_err += test(ev,"<>f1",NULL);
	nb_err += test(ev," < > f1 ",NULL);
	nb_err += test(ev,"cmd1<",NULL);
	nb_err += test(ev,"<|cmd2",NULL);
	nb_err += test(ev,"<&&cmd2",NULL);
	nb_err += test(ev,"<||cmd2",NULL);
	nb_err += test(ev,"< (cmd1&&cmd2)",NULL);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Cases of '<<' RDL operator");
	nb_err += test(ev,"<<",NULL);
	nb_err += test(ev,"<< ",NULL);
	nb_err += test(ev,"<<>f1",NULL);
	nb_err += test(ev," << > f1 ",NULL);
	nb_err += test(ev,"cmd1<<",NULL);
	nb_err += test(ev,"<<|cmd2",NULL);
	nb_err += test(ev,"<<&&cmd2",NULL);
	nb_err += test(ev,"<<||cmd2",NULL);
	nb_err += test(ev,"<< (cmd1&&cmd2)",NULL);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Cases of '<<<' RTL operator");
	nb_err += test(ev,"<<<",NULL);
	nb_err += test(ev,"<<< ",NULL);
	nb_err += test(ev,"<<<>f1",NULL);
	nb_err += test(ev," <<< > f1 ",NULL);
	nb_err += test(ev,"cmd1<<<",NULL);
	nb_err += test(ev,"<<<|cmd2",NULL);
	nb_err += test(ev,"<<<&&cmd2",NULL);
	nb_err += test(ev,"<<<||cmd2",NULL);
	nb_err += test(ev,"<<< (cmd1&&cmd2)",NULL);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Cases of '>' RRS operator");
	nb_err += test(ev,">",NULL);
	nb_err += test(ev,"> ",NULL);
	nb_err += test(ev,"cmd>",NULL);
	nb_err += test(ev,"cmd> ",NULL);
	nb_err += test(ev,"<f1>",NULL);
	nb_err += test(ev," < f1 > ",NULL);
	nb_err += test(ev,">|cmd2",NULL);
	nb_err += test(ev,"cmd1>|cmd2",NULL);
	nb_err += test(ev,">||cmd2",NULL);
	nb_err += test(ev,"cmd1>||cmd2",NULL);
	nb_err += test(ev,">&&cmd2",NULL);
	nb_err += test(ev,"cmd1>&&cmd2",NULL);
	nb_err += test(ev,"> (cmd1&&cmd2)",NULL);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Cases of '>>' RRD operator");
	nb_err += test(ev,">>",NULL);
	nb_err += test(ev,">> ",NULL);
	nb_err += test(ev,"cmd>>",NULL);
	nb_err += test(ev,"cmd>> ",NULL);
	nb_err += test(ev,"<f1>>",NULL);
	nb_err += test(ev," < f1 >> ",NULL);
	nb_err += test(ev,">>|cmd2",NULL);
	nb_err += test(ev,"cmd1>>|cmd2",NULL);
	nb_err += test(ev,">>||cmd2",NULL);
	nb_err += test(ev,"cmd1>>||cmd2",NULL);
	nb_err += test(ev,">>&&cmd2",NULL);
	nb_err += test(ev,"cmd1>>&&cmd2",NULL);
	nb_err += test(ev,">> (cmd1&&cmd2)",NULL);
	print_sep(S2);
	print_sep(S1);
	// =[  ]====================================================================
	print_title("D| FAILS OF BINARY OPERATORS SYNTAX ");
	print_subtitle("Cases of '&& OPA operator");
	nb_err += test(ev,"&&",NULL);
	nb_err += test(ev," && ",NULL);
	nb_err += test(ev,"cmd&&",NULL);
	nb_err += test(ev," cmd && ",NULL);
	nb_err += test(ev,"&&cmd",NULL);
	nb_err += test(ev," && cmd ",NULL);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Cases of '||' OPO operator");
	nb_err += test(ev,"||",NULL);
	nb_err += test(ev," || ",NULL);
	nb_err += test(ev,"cmd||",NULL);
	nb_err += test(ev," cmd || ",NULL);
	nb_err += test(ev,"||cmd",NULL);
	nb_err += test(ev," || cmd ",NULL);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Cases of '|' PIP operator");
	nb_err += test(ev,"|",NULL);
	nb_err += test(ev," | ",NULL);
	nb_err += test(ev,"cmd|",NULL);
	nb_err += test(ev," cmd | ",NULL);
	nb_err += test(ev,"|cmd",NULL);
	nb_err += test(ev," | cmd ",NULL);
	print_sep(S2);
	print_sep(S1);
	// =[  ]====================================================================
	print_title("E| FAILS OF PARENTHESIS SYNTAX ");
	print_subtitle("Cases of 'Empty parenthesis'");
	nb_err += test(ev,"()",NULL);
	nb_err += test(ev," ( ) ",NULL);
	nb_err += test(ev," ( ( ) ) ",NULL);
	nb_err += test(ev,"( ( ) )",NULL);
	nb_err += test(ev,"(( ) )",NULL);
	nb_err += test(ev,"( ( ))",NULL);
	print_sep(S2);
	// -[ 	 ]------------------------------------------------------------------
	print_subtitle("Cases of 'Odd number of parenthesis'");
	nb_err += test(ev,"(",NULL);
	nb_err += test(ev," ( ",NULL);
	nb_err += test(ev,")",NULL);
	nb_err += test(ev," ) ",NULL);
	nb_err += test(ev,"((cmd)",NULL);
	nb_err += test(ev," ( ( cmd ) ",NULL);
	nb_err += test(ev,"(cmd))",NULL);    
	nb_err += test(ev," ( cmd ) )",NULL);
	print_sep(S2);
	// -[ 	 ]------------------------------------------------------------------
	print_subtitle("Cases of 'Wrong order of parenthesis'");
	nb_err += test(ev,")(",NULL);
	nb_err += test(ev," ) ( ",NULL);
	nb_err += test(ev,")cmd1(",NULL);
	nb_err += test(ev,"cmd1)(cmd2",NULL);
	nb_err += test(ev,"cmd1)cmd2(cmd3",NULL);
	print_sep(S2);
	// -[ 	 ]------------------------------------------------------------------
	print_subtitle("Cases of 'Wrong syntax with parenthesis'");
	nb_err += test(ev,"(cmd1)cmd2",NULL);
	nb_err += test(ev,"(cmd1) cmd2",NULL);
	nb_err += test(ev,"cmd1(cmd2)",NULL);
	nb_err += test(ev,"cmd1 ( cmd2 )",NULL);
	nb_err += test(ev,"(cmd1)(cmd2)",NULL);
	nb_err += test(ev," ( cmd1 ) ( cmd2 ) ",NULL);
	print_sep(S2);
	print_sep(S1);
	// =[  ]====================================================================
	print_title("F| PASS COMMANDS");
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Only unset and spaces-> check if quotes is count as one UNSET");
	t_token a0[] = {{ESP," ",0}, {UNSET,"cmd1",0}, {ESP," ",0}, {UNSET,"arg1",0}, {ESP," ",0}, {UNSET,"arg2",0}, {ESP," ",0}, {UNSET,"\"arg3 && arg4\"",0}, {ESP," ",0}, {0,0,0}};
	nb_err += test(ev," cmd1 arg1   arg2   \"arg3 && arg4\" ",a0);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Real command with REDIR and PIPE OPERATORS");
	t_token a1[] = {{RLS,"<",0}, {ESP," ",0}, {UNSET,"file1",0}, {ESP," ",0}, {UNSET,"cat",0}, {ESP," ",0}, {PIP,"|",0}, {ESP," ",0}, {UNSET,"cat",0}, {ESP," ",0}, {RRS,">",0}, {ESP," ",0}, {UNSET,"file2",0},{0,0,0}};
	nb_err += test(ev,"< file1 cat | cat > file2",a1);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("3 tests to check concatenation of contiguous quoted unset");
	t_token a2[] = {{UNSET,"'e'''cho",0}, {ESP," ",0}, {UNSET,"toto",0}, {RRD,">>",0}, {UNSET,"file1",0},{0,0,0}};
	nb_err += test(ev,"'e'''cho toto>>file1",a2);
	
	t_token a3[] = {{ESP," ",0},{UNSET,"'e'\"c\"ho",0}, {ESP," ",0}, {UNSET,"toto",0}, {OPA,"&&",0}, {UNSET,"echo",0}, {ESP," ",0}, {UNSET,"OK",0}, {OPO,"||",0}, {UNSET,"echo",0},{ESP," ",0}, {UNSET,"KO",0},{0,0,0}};
	nb_err += test(ev,"    'e'\"c\"ho  toto&&echo OK||echo  KO",a3);

	t_token a4[] = {{ESP," ",0},{PARO,"(",1},{UNSET,"'e'\"c\"ho",1}, {ESP," ",1}, {UNSET,"toto",1},{PARC,")",0},{OPA,"&&",0}, {UNSET,"echo",0}, {ESP," ",0}, {UNSET,"OK",0}, {OPO,"||",0}, {UNSET,"echo",0},{ESP," ",0}, {UNSET,"KO",0}, {ESP," ",0},{0,0,0}};
	nb_err += test(ev,"    ('e'\"c\"ho  toto)&&echo OK||echo  KO    ",a4);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Check all binary operators");
	t_token a5[] = {{UNSET,"cmd1",0}, {PIP,"|",0}, {UNSET,"cmd2",0}, {OPA,"&&",0}, {UNSET,"cmd3",0}, {OPO,"||",0}, {UNSET,"cmd4",0},{0,0,0}};
	nb_err += test(ev,"cmd1|cmd2&&cmd3||cmd4",a5);

	t_token a6[] = {{ESP," ",0}, {UNSET,"cmd1",0}, {ESP," ",0},  {PIP,"|",0}, {ESP," ",0},  {UNSET,"cmd2",0}, {ESP," ",0},  {OPA,"&&",0}, {ESP," ",0},  {UNSET,"cmd3",0}, {ESP," ",0},  {OPO,"||",0}, {ESP," ",0},  {UNSET,"cmd4",0}, {ESP," ",0},{0,0,0}};
	nb_err += test(ev,"   cmd1   |   cmd2   &&   cmd3   ||   cmd4   ",a6);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Check all unary operators");
	t_token a7[] = {{RLS,"<",0}, {UNSET,"f1",0}, {RLD,"<<",0}, {UNSET,"f2",0}, {RLT,"<<<",0}, {UNSET,"f3",0}, {RRS,">",0}, {UNSET,"f4",0},{RRD,">>",0}, {UNSET,"f5",0},{0,0,0}};
	nb_err += test(ev,"<f1<<f2<<<f3>f4>>f5",a7);

	t_token a8[] = {{ESP," ",0}, {RLS,"<",0}, {ESP," ",0}, {UNSET,"f1",0}, {ESP," ",0}, {RLD,"<<",0}, {ESP," ",0}, {UNSET,"f2",0}, {ESP," ",0}, {RLT,"<<<",0}, {ESP," ",0}, {UNSET,"f3",0}, {ESP," ",0}, {RRS,">",0}, {ESP," ",0}, {UNSET,"f4",0}, {ESP," ",0},{RRD,">>",0}, {ESP," ",0}, {UNSET,"f5",0}, {ESP," ",0},{0,0,0}};
	nb_err += test(ev,"  <  f1  <<  f2  <<<  f3  >  f4  >>  f5  ",a8);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Check parenthesis");
	t_token a9[] = {{PARO,"(",1}, {UNSET,"cmd",1}, {PARC,")",0},{0,0,0}};
	nb_err += test(ev,"(cmd)",a9);

	t_token a10[] = {{PARO,"(",1}, {UNSET,"cmd1",1}, {OPA,"&&",1}, {UNSET,"cmd2",1}, {PARC,")",0}, {OPO,"||",0}, {PARO,"(",1}, {UNSET,"cmd3",1}, {OPA,"&&",1}, {UNSET,"cmd4",1}, {PARC,")",0},{0,0,0}};
	nb_err += test(ev,"(cmd1&&cmd2)||(cmd3&&cmd4)",a10);

	t_token a11[] = {{PARO,"(",1},{ESP," ",1}, {PARO,"(",2}, {PARO,"(",3}, {UNSET,"cmd1",3}, {OPA,"&&",3}, {UNSET,"cmd2",3},{PARC,")",2},{ESP," ",2}, {PARC,")",1}, {PARC,")",0},{0,0,0}};
	nb_err += test(ev,"( ((cmd1&&cmd2) ))",a11);

	t_token a12[] = {{ESP," ",0}, {PARO,"(",1}, {ESP," ",1}, {PARO,"(",2}, {ESP," ",2}, {PARO,"(",3}, {UNSET,"cmd1",3}, {OPA,"&&",3}, {UNSET,"cmd2",3}, {PARC,")",2}, {ESP," ",2}, {PARC,")",1}, {ESP," ",1}, {PARC,")",0}, {ESP," ",0},{0,0,0}};
	nb_err += test(ev," ( ( (cmd1&&cmd2) ) ) ",a12);

	t_token a13[] = {{PARO,"(",1},{PARO,"(",2},{UNSET,"cmd1",2},{PARC,")",1},{OPA,"&&",1},{PARO,"(",2},{UNSET,"cmd2",2},{PIP,"|",2},{UNSET,"cmd3",2},{PARC,")",1},{PARC,")",0},{0,0,0}};
	nb_err += test(ev,"((cmd1)&&(cmd2|cmd3))",a13);
	
	t_token a14[] = {{PARO,"(",1}, {PARO,"(",2}, {PARO,"(",3}, {UNSET,"cmd1",3}, {OPA,"&&",3}, {UNSET,"cmd2",3}, {PARC,")",2}, {OPO,"||",2}, {PARO,"(",3}, {UNSET,"cmd3",3}, {OPA,"&&",3}, {UNSET,"cmd4",3}, {PARC,")",2}, {PARC,")",1}, {OPA,"&&",1}, {PARO,"(",2}, {UNSET,"cmd5",2}, {PIP,"|",2}, {UNSET,"cmd6",2}, {PARC,")",1}, {PARC,")",0},{0,0,0}};
	nb_err += test(ev,"(((cmd1&&cmd2)||(cmd3&&cmd4))&&(cmd5|cmd6))",a14);

	t_token a15[] = {{PARO,"(",1}, {PARO,"(",2}, {PARO,"(",3}, {PARO,"(",4}, {UNSET,"echo",4}, {ESP," ",4}, {UNSET,"\"inside f1\"",4}, {PARC,")",3}, {RRS,">",3}, {UNSET,"f1",3}, {PARC,")",2}, {OPA,"&&",2}, {PARO,"(",3}, {PARO,"(",4}, {RLS,"<",4}, {UNSET,"f1",4}, {ESP," ",4}, {UNSET,"cat",4}, {PARC,")",3}, {ESP," ",3}, {RRS,">",3}, {UNSET,"f2",3}, {PARC,")",2}, {PARC,")",1}, {OPA,"&&",1}, {PARO,"(",2}, {RLS,"<",2}, {UNSET,"f2",2}, {ESP," ",2}, {UNSET,"cat",2}, {PARC,")",1}, {PARC,")",0},{0,0,0}};
	nb_err += test(ev,"((((echo \"inside f1\")>f1)&&((<f1 cat) >f2))&&(<f2 cat))",a15);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Valid Parenthesis imbrication~nesting");
	t_token b0[] = {{PARO,"(",1},{ESP," ", 1},{PARO,"(",2},{UNSET,"0",2},{PARC,")",1},{ESP," ",1},{PARC,")",0},{0,0,0}};
	nb_err += test(ev,"( (0) )",b0);

	t_token b1[] = {{PARO,"(",1},{ESP," ", 1},{PARO,"(",2},{UNSET,"echo",2},{ESP," ",2},{UNSET,"toto",2},{PARC,")",1},{ESP," ",1},{PARC,")",0},{0,0,0}};
	nb_err += test(ev,"( (echo toto) )",b1);

	t_token b2[] = {{PARO,"(",1},{PARO,"(",2},{UNSET,"echo",2},{ESP," ",2},{UNSET,"toto",2},{PARC,")",1},{ESP," ",1},{PARC,")",0},{0,0,0}};
	nb_err += test(ev,"((echo toto) )",b2);

	t_token b3[] = {{PARO,"(",1},{ESP," ", 1},{PARO,"(",2},{UNSET,"echo",2},{ESP," ",2},{UNSET,"toto",2},{PARC,")",1},{PARC,")",0},{0,0,0}};
	nb_err += test(ev,"( (echo toto))",b3);

	t_token b4[] = {{PARO,"(",1},{ESP," ", 1},{PARO,"(",2},{ESP," ", 2},{PARO,"(",3},{ESP," ", 3}, {UNSET,"echo",3},{ESP," ",3},{UNSET,"toto",3},{ESP," ",3}, {PARC,")",2},{ESP," ",2},{PARC,")",1},{ESP," ",1},{PARC,")",0},{0,0,0}};
	nb_err += test(ev,"( ( ( echo toto ) ) )",b4);

	t_token b5[] = {{PARO,"(",1},{PARO,"(",2},{ESP," ", 2},{PARO,"(",3},{ESP," ", 3}, {UNSET,"echo",3},{ESP," ",3},{UNSET,"toto",3},{ESP," ",3}, {PARC,")",2},{PARC,")",1},{ESP," ",1},{PARC,")",0},{0,0,0}};
	nb_err += test(ev,"(( ( echo toto )) )",b5);

	t_token b6[] = {{PARO,"(",1},{ESP," ", 1},{PARO,"(",2},{PARO,"(",3},{ESP," ", 3}, {UNSET,"echo",3},{ESP," ",3},{UNSET,"toto",3},{ESP," ",3}, {PARC,")",2},{ESP," ",2},{PARC,")",1},{PARC,")",0},{0,0,0}};
	nb_err += test(ev,"( (( echo toto ) ))",b6);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Combos");
	t_token a24[] = {{PARO,"(",1},{PARO,"(",2},{UNSET,"cat",2},{PARC,")",1},{RLS,"<",1},{UNSET,"f2",1},{PARC,")",0},{PIP,"|",0},{PARO,"(",1},{RRS,">",1},{UNSET,"f3",1},{ESP," ",1},{UNSET,"cat",1},{PARC,")",0},{0,0,0}};
	nb_err += test(ev,"((cat)<f2)|(>f3 cat)",a24);
	print_sep(S2);
	print_sep(S1);
	return (nb_err);
}

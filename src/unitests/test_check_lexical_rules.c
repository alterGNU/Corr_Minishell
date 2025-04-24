// =[ INCLUDE ]=================================================================
#include "minishell.h"    // 
#include <string.h>       // strcmp
#include <stdio.h>        // printf, fflush
						  // ⚠️  Some of minishell print fun. use ~write=>fflush
						  // ⚠️  Depends on libft/array/ft_print_str_array()
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "check_lexical_rules"
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
int	test(char **ev, char *str, t_token tab_res[])
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
	// STEP 0
	t_data *dt = init_data(ev);
	if (!dt)
		return (ft_fprintf(2, "init_data()->fail"));
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
	int res = set_tok_lst_members(dt->tok_lst);
	// CHECK TOK_LST == NULL
	if (!dt->tok_lst)
	{
		if (!tab_res)
			return (printf(CV"tok_lst == tab_res == NULL\n"CE),printntime(S3, LEN - 5), printf(PASS), 0);
		write(1, "\n", 1);
		return (printntime(S3, LEN - 5), printf(FAIL), 1);
	}
	// Print result
	printf("set_tok_lst_members() returns %d\ntab_res=", res);
	display_token_array(tab_res);
	printf("\ntok_lst=");
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
			return (free_data(&dt),printntime(S3, LEN - 5), printf(FAIL), 1);
		}
		act = act->next;
		i++;
	}
	return (free_data(&dt),printntime(S3, LEN - 5), printf(PASS), 0);
}

int main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;

	int	nb_err = 0;

	print_title("CAS:NULL");
	print_subtitle("These cases never really happen because they're handled in main, before lexer(dt, line) is called");
	nb_err += test(ev, NULL, NULL, NULL);
	nb_err += test(ev, "", NULL, NULL);
	print_sep(S2);
	print_sep(S1);

	print_title("A| PASS COMMANDS");
	print_subtitle("Only unset and spaces-> check if quotes is count as one UNSET");
	int ai0[9] = {ESP, UNSET, ESP, UNSET, ESP, UNSET, ESP, UNSET, ESP};
	char *as0[] = {" ", "cmd1", " ", "arg1", " ", "arg2", " ", "\"arg3 && arg4\"", " ", NULL};
	nb_err += test(ev, " cmd1 arg1   arg2   \"arg3 && arg4\" ", as0, ai0);
	print_sep(S2);

	print_subtitle("Real command with REDIR and PIPE OPERATORS");
	int ai1[13] = {RLS, ESP, UNSET, ESP, UNSET, ESP, PIP, ESP, UNSET, ESP, RRS, ESP, UNSET};
	char *as1[] = {"<", " ", "file1", " ", "cat", " ", "|", " ", "cat", " ", ">", " ", "file2", NULL};
	nb_err += test(ev, "< file1 cat | cat > file2", as1, ai1);
	print_sep(S2);
	
	print_subtitle("3 tests to check concatenation of contiguous quoted unset");
	int ai2[5] = {UNSET, ESP, UNSET, RRD, UNSET};
	char *as2[] = {"'e'''cho", " ", "toto", ">>", "file1", NULL};
	nb_err += test(ev, "'e'''cho toto>>file1", as2, ai2);
	
	int ai3[12] = {ESP, UNSET, ESP, UNSET, OPA, UNSET, ESP, UNSET, OPO, UNSET, ESP, UNSET};
	char *as3[] = {" ","'e'\"c\"ho", " ", "toto", "&&", "echo", " ", "OK", "||", "echo"," ", "KO", NULL};
	nb_err += test(ev, "    'e'\"c\"ho  toto&&echo OK||echo  KO", as3, ai3);

	int ai4[13] = {ESP, UNSET, ESP, UNSET, OPA, UNSET, ESP, UNSET, OPO, UNSET, ESP, UNSET, ESP};
	char *as4[] = {" ","'e'\"c\"ho", " ", "toto", "&&", "echo", " ", "OK", "||", "echo"," ", "KO", " ", NULL};
	nb_err += test(ev, "    'e'\"c\"ho  toto&&echo OK||echo  KO    ", as4, ai4);
	print_sep(S2);

	print_subtitle("Check all binary operators");
	int ai5[8] = {UNSET, PIP, UNSET, OPA, UNSET, OPO, UNSET};
	char *as5[] = {"cmd1", "|", "cmd2", "&&", "cmd3", "||", "cmd4", NULL};
	nb_err += test(ev, "cmd1|cmd2&&cmd3||cmd4", as5, ai5);

	int ai6[15] = {ESP, UNSET, ESP, PIP, ESP, UNSET, ESP, OPA, ESP, UNSET, ESP, OPO, ESP, UNSET, ESP};
	char *as6[] = {" ", "cmd1", " ",  "|", " ",  "cmd2", " ",  "&&", " ",  "cmd3", " ",  "||", " ",  "cmd4", " ",  NULL};
	nb_err += test(ev, "   cmd1   |   cmd2   &&   cmd3   ||   cmd4   ", as6, ai6);
	print_sep(S2);

	print_subtitle("Check all unary operators");
	int ai7[10] = {RLS, UNSET, RLD, UNSET, RLT, UNSET, RRS, UNSET, RRD, UNSET};
	char *as7[] = {"<", "f1", "<<", "f2", "<<<", "f3", ">", "f4",">>", "f5", NULL};
	nb_err += test(ev, "<f1<<f2<<<f3>f4>>f5", as7, ai7);

	int ai8[21] = {ESP, RLS, ESP, UNSET, ESP, RLD, ESP, UNSET, ESP, RLT, ESP, UNSET, ESP, RRS, ESP, UNSET, ESP, RRD, ESP, UNSET, ESP};
	char *as8[] = {" ", "<", " ", "f1", " ", "<<", " ", "f2", " ", "<<<", " ", "f3", " ", ">", " ", "f4", " ",">>", " ", "f5", " ", NULL};
	nb_err += test(ev, "  <  f1  <<  f2  <<<  f3  >  f4  >>  f5  ", as8, ai8);
	print_sep(S2);

	print_subtitle("Check parenthesis");
	int ai9[3] = {PARO, UNSET, PARC};
	char *as9[] = {"(", "cmd", ")", NULL};
	nb_err += test(ev, "(cmd)", as9, ai9);

	int ai10[11] = {PARO, UNSET, OPA, UNSET, PARC, OPO, PARO, UNSET, OPA, UNSET, PARC};
	char *as10[] = {"(", "cmd1", "&&", "cmd2", ")", "||", "(", "cmd3", "&&", "cmd4", ")", NULL};
	nb_err += test(ev, "(cmd1&&cmd2)||(cmd3&&cmd4)", as10, ai10);

	int ai11[10] = {PARO, PARO, PARO, UNSET, OPA, UNSET, PARC, PARC, PARC};
	char *as11[] = {"(", "(", "(", "cmd1", "&&", "cmd2", ")", ")", ")",NULL};
	nb_err += test(ev, "(((cmd1&&cmd2)))", as11, ai11);

	int ai12[16] = {ESP, PARO, ESP, PARO, ESP, PARO, UNSET, OPA, UNSET, PARC, ESP, PARC, ESP, PARC, ESP};
	char *as12[] = {" ", "(", " ", "(", " ", "(", "cmd1", "&&", "cmd2", ")", " ", ")", " ", ")", " ", NULL};
	nb_err += test(ev, " ( ( (cmd1&&cmd2) ) ) ", as12, ai12);
	print_sep(S2);

	print_subtitle("Combos");
	int ai13[9] = {UNSET, RLS, UNSET, PIP, RRS, UNSET, ESP, UNSET};
	char *as13[] = {"cmd1", "<", "f2", "|", ">", "f3", " ", "cmd2", NULL};
	nb_err += test(ev, "cmd1<f2|>f3 cmd2", as13, ai13);
	print_sep(S2);
	print_sep(S1);

	print_title("B| FAIL UNARY UNKNOWN OPERATOR");
	nb_err += test(ev, "<<<<", NULL, NULL);
	nb_err += test(ev, "<<<<f1", NULL, NULL);
	nb_err += test(ev, ">>>", NULL, NULL);
	nb_err += test(ev, ">>>f1", NULL, NULL);
	nb_err += test(ev, "|||", NULL, NULL);
	nb_err += test(ev, "cmd1|||cmd2", NULL, NULL);
	nb_err += test(ev, "&&&", NULL, NULL);
	nb_err += test(ev, "cmd1&&&cmd2", NULL, NULL);
	print_subtitle("List of operators not handle for now");
	nb_err += test(ev, "<(cmd)", NULL, NULL);
	nb_err += test(ev, ">(cmd)", NULL, NULL);
	print_sep(S2);
	print_sep(S1);

	print_title("C| FAIL UNARY RLS <");
	nb_err += test(ev, "<", NULL, NULL);
	nb_err += test(ev, "< ", NULL, NULL);
	nb_err += test(ev, "<>f1", NULL, NULL);
	nb_err += test(ev, " < > f1 ", NULL, NULL);
	nb_err += test(ev, "cmd1<", NULL, NULL);
	nb_err += test(ev, "<|cmd2", NULL, NULL);
	nb_err += test(ev, "<&&cmd2", NULL, NULL);
	nb_err += test(ev, "<||cmd2", NULL, NULL);
	nb_err += test(ev, "< (cmd1&&cmd2)", NULL, NULL);
	print_sep(S1);

	print_title("D| FAIL UNARY RLD <<");
	nb_err += test(ev, "<<", NULL, NULL);
	nb_err += test(ev, "<< ", NULL, NULL);
	nb_err += test(ev, "<<>f1", NULL, NULL);
	nb_err += test(ev, " << > f1 ", NULL, NULL);
	nb_err += test(ev, "cmd1<<", NULL, NULL);
	nb_err += test(ev, "<<|cmd2", NULL, NULL);
	nb_err += test(ev, "<<&&cmd2", NULL, NULL);
	nb_err += test(ev, "<<||cmd2", NULL, NULL);
	nb_err += test(ev, "<< (cmd1&&cmd2)", NULL, NULL);
	print_sep(S1);

	print_title("E| FAIL UNARY RLT <<<");
	nb_err += test(ev, "<<<", NULL, NULL);
	nb_err += test(ev, "<<< ", NULL, NULL);
	nb_err += test(ev, "<<<>f1", NULL, NULL);
	nb_err += test(ev, " <<< > f1 ", NULL, NULL);
	nb_err += test(ev, "cmd1<<<", NULL, NULL);
	nb_err += test(ev, "<<<|cmd2", NULL, NULL);
	nb_err += test(ev, "<<<&&cmd2", NULL, NULL);
	nb_err += test(ev, "<<<||cmd2", NULL, NULL);
	nb_err += test(ev, "<<< (cmd1&&cmd2)", NULL, NULL);
	print_sep(S1);

	print_title("F| FAIL UNARY RRS >");
	nb_err += test(ev, ">", NULL, NULL);
	nb_err += test(ev, "> ", NULL, NULL);
	nb_err += test(ev, "cmd>", NULL, NULL);
	nb_err += test(ev, "cmd> ", NULL, NULL);
	nb_err += test(ev, "<f1>", NULL, NULL);
	nb_err += test(ev, " < f1 > ", NULL, NULL);
	nb_err += test(ev, ">|cmd2", NULL, NULL);
	nb_err += test(ev, "cmd1>|cmd2", NULL, NULL);
	nb_err += test(ev, ">||cmd2", NULL, NULL);
	nb_err += test(ev, "cmd1>||cmd2", NULL, NULL);
	nb_err += test(ev, ">&&cmd2", NULL, NULL);
	nb_err += test(ev, "cmd1>&&cmd2", NULL, NULL);
	nb_err += test(ev, "> (cmd1&&cmd2)", NULL, NULL);
	print_sep(S1);

	print_title("G| FAIL UNARY RRD >");
	nb_err += test(ev, ">>", NULL, NULL);
	nb_err += test(ev, ">> ", NULL, NULL);
	nb_err += test(ev, "cmd>>", NULL, NULL);
	nb_err += test(ev, "cmd>> ", NULL, NULL);
	nb_err += test(ev, "<f1>>", NULL, NULL);
	nb_err += test(ev, " < f1 >> ", NULL, NULL);
	nb_err += test(ev, ">>|cmd2", NULL, NULL);
	nb_err += test(ev, "cmd1>>|cmd2", NULL, NULL);
	nb_err += test(ev, ">>||cmd2", NULL, NULL);
	nb_err += test(ev, "cmd1>>||cmd2", NULL, NULL);
	nb_err += test(ev, ">>&&cmd2", NULL, NULL);
	nb_err += test(ev, "cmd1>>&&cmd2", NULL, NULL);
	nb_err += test(ev, ">> (cmd1&&cmd2)", NULL, NULL);
	print_sep(S1);

	print_title("H| FAIL BINARY OPA &&");
	nb_err += test(ev, "&&", NULL, NULL);
	nb_err += test(ev, " && ", NULL, NULL);
	nb_err += test(ev, "cmd&&", NULL, NULL);
	nb_err += test(ev, " cmd && ", NULL, NULL);
	nb_err += test(ev, "&&cmd", NULL, NULL);
	nb_err += test(ev, " && cmd ", NULL, NULL);
	print_sep(S1);

	print_title("I| FAIL BINARY OPO ||");
	nb_err += test(ev, "||", NULL, NULL);
	nb_err += test(ev, " || ", NULL, NULL);
	nb_err += test(ev, "cmd||", NULL, NULL);
	nb_err += test(ev, " cmd || ", NULL, NULL);
	nb_err += test(ev, "||cmd", NULL, NULL);
	nb_err += test(ev, " || cmd ", NULL, NULL);
	print_sep(S1);

	print_title("J| FAIL BINARY PIP |");
	nb_err += test(ev, "|", NULL, NULL);
	nb_err += test(ev, " | ", NULL, NULL);
	nb_err += test(ev, "cmd|", NULL, NULL);
	nb_err += test(ev, " cmd | ", NULL, NULL);
	nb_err += test(ev, "|cmd", NULL, NULL);
	nb_err += test(ev, " | cmd ", NULL, NULL);
	print_sep(S1);

	print_title("K| FAIL WITH PARENTHESIS");
	print_subtitle("Cases of 'Empty parenthesis'");
	nb_err += test(ev, "()", NULL, NULL);
	nb_err += test(ev, " ( ) ", NULL, NULL);
	nb_err += test(ev, "(())", NULL, NULL);
	nb_err += test(ev, " ( ( ) ) ", NULL, NULL);
	print_sep(S2);

	print_subtitle("Cases of 'Odd number of parenthesis'");
	nb_err += test(ev, "(", NULL, NULL);
	nb_err += test(ev, " ( ", NULL, NULL);
	nb_err += test(ev, ")", NULL, NULL);
	nb_err += test(ev, " ) ", NULL, NULL);
	nb_err += test(ev, "((cmd)", NULL, NULL);
	nb_err += test(ev, " ( ( cmd ) ", NULL, NULL);
	nb_err += test(ev, "(cmd))", NULL, NULL);    
	nb_err += test(ev, " ( cmd ) )", NULL, NULL);
	print_sep(S2);

	print_subtitle("Cases of 'Wrong order of parenthesis'");
	nb_err += test(ev, ")(", NULL, NULL);
	nb_err += test(ev, " ) ( ", NULL, NULL);
	print_sep(S2);

	print_subtitle("Cases of 'Wrong syntax with parenthesis'");
	nb_err += test(ev, "(cmd1)cmd2", NULL, NULL);
	nb_err += test(ev, "(cmd1) cmd2", NULL, NULL);
	nb_err += test(ev, "cmd1(cmd2)", NULL, NULL);
	nb_err += test(ev, "cmd1 ( cmd2 )", NULL, NULL);
	nb_err += test(ev, "(cmd1)(cmd2)", NULL, NULL);
	nb_err += test(ev, " ( cmd1 ) ( cmd2 ) ", NULL, NULL);
	print_sep(S2);
	print_sep(S1);

	return (nb_err);
}

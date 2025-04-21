// =[ INCLUDE ]=================================================================
#include "minishell.h"    // build_tok_lst_split_by_quotes,build_tok_lst_split_by_spaces,build_tok_lst_split_by_operators,set_tok_lst_type
#include <string.h>       // strcmp
#include <stdio.h>        // printf, fflush
						  // ⚠️  Some of minishell print fun. use ~write=>fflush
						  // ⚠️  Depends on libft/array/ft_print_str_array()
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "lexer"
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
// print_str_array
int	print_strarr(char **str)
{
	int psf = printf("tab_res=");
	fflush(stdout);
	psf += ft_print_str_array(str);
	return (psf);
}

// This function print details only on failures.
int	test(char *str, char **tab_res, int *type_res, char **ev)
{
	t_data	*data = init_data(ev);
	if (!data)
		return (1);
	// Print test header
	int print_sofar = printf("%s(\"%s\")", f_name, str);
	if (str)
	{
		int c = count_char_in_str('\t', str);
		if (c)
			print_sofar+=c*4;
	}
	printntime(S3, LEN - print_sofar);
	printf("\n");
	// LEXING
	lexer(str, &data);
	// CHECK TOK_LST == NULL
	if (!data->tok_lst)
	{
		printf("\n");
		if (!tab_res)
			return (free_data(&data), printntime(S3, LEN - 5), printf(PASS), 0);
		return (free_data(&data), print_strarr(tab_res), printf("\ntok_lst=NULL\n"), printntime(S3, LEN - 5), printf(FAIL), 1);
	}
	int	i = 0;
	t_list	*act = data->tok_lst;
	while (tab_res[i] && act && !strcmp(tab_res[i], ((t_token *)(act->content))->str))
	{
		if (type_res[i] != ((t_token *)act->content)->type)
			return (free_data(&data), printntime(S3, LEN - 5), printf(FAIL), 1);
		act = act->next;
		i++;
	}
	print_strarr(tab_res);
	printf("\ntok_lst=");
	fflush(stdout);
	print_tok_lst(data->tok_lst);
	printf("\n");
	if (!tab_res[i] && !act)
		return (free_data(&data), printntime(S3, LEN - 5), printf(PASS), 0);
	if ((!tab_res[i] && act) || (tab_res[i] && !act))
		return (free_data(&data), printntime(S3, LEN - 5), printf(FAIL), 1);
	if (strcmp(tab_res[i], ((t_token *)(act->content))->str))
		return (free_data(&data), printntime(S3, LEN - 5), printf(FAIL), 1);
	return (free_data(&data), printf(PASS), 0);
}

int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	int	nb_err = 0;

	////TODO: find a way to test this without cause exit() kill testeur
	//print_title("CAS:NULL");
	//nb_err += test(NULL, NULL, NULL, ev);
	//nb_err += test("", NULL, NULL, ev);

	print_title("A| PASS COMMANDS");
	print_subtitle("Only unset and spaces-> check if quotes is count as one UNSET");
	int ai0[9] = {ESP, UNSET, ESP, UNSET, ESP, UNSET, ESP, UNSET, ESP};
	char *as0[] = {" ", "cmd1", " ", "arg1", " ", "arg2", " ", "\"arg3 && arg4\"", " ", NULL};
	nb_err += test(" cmd1 arg1   arg2   \"arg3 && arg4\" ", as0, ai0, ev);
	print_sep(S2);

	print_subtitle("Real command with REDIR and PIPE OPERATORS");
	int ai1[13] = {RLS, ESP, UNSET, ESP, UNSET, ESP, PIP, ESP, UNSET, ESP, RRS, ESP, UNSET};
	char *as1[] = {"<", " ", "file1", " ", "cat", " ", "|", " ", "cat", " ", ">", " ", "file2", NULL};
	nb_err += test("< file1 cat | cat > file2", as1, ai1, ev);
	print_sep(S2);
	
	print_subtitle("3 tests to check concatenation of contiguous quoted unset");
	int ai2[5] = {UNSET, ESP, UNSET, RRD, UNSET};
	char *as2[] = {"'e'''cho", " ", "toto", ">>", "file1", NULL};
	nb_err += test("'e'''cho toto>>file1", as2, ai2, ev);
	
	int ai3[12] = {ESP, UNSET, ESP, UNSET, OPA, UNSET, ESP, UNSET, OPO, UNSET, ESP, UNSET};
	char *as3[] = {" ","'e'\"c\"ho", " ", "toto", "&&", "echo", " ", "OK", "||", "echo"," ", "KO", NULL};
	nb_err += test("    'e'\"c\"ho  toto&&echo OK||echo  KO", as3, ai3, ev);

	int ai4[13] = {ESP, UNSET, ESP, UNSET, OPA, UNSET, ESP, UNSET, OPO, UNSET, ESP, UNSET, ESP};
	char *as4[] = {" ","'e'\"c\"ho", " ", "toto", "&&", "echo", " ", "OK", "||", "echo"," ", "KO", " ", NULL};
	nb_err += test("    'e'\"c\"ho  toto&&echo OK||echo  KO    ", as4, ai4, ev);
	print_sep(S2);

	print_subtitle("Check all binary operators");
	int ai5[8] = {UNSET, PIP, UNSET, OPA, UNSET, OPO, UNSET};
	char *as5[] = {"cmd1", "|", "cmd2", "&&", "cmd3", "||", "cmd4", NULL};
	nb_err += test("cmd1|cmd2&&cmd3||cmd4", as5, ai5, ev);

	int ai6[15] = {ESP, UNSET, ESP, PIP, ESP, UNSET, ESP, OPA, ESP, UNSET, ESP, OPO, ESP, UNSET, ESP};
	char *as6[] = {" ", "cmd1", " ",  "|", " ",  "cmd2", " ",  "&&", " ",  "cmd3", " ",  "||", " ",  "cmd4", " ",  NULL};
	nb_err += test("   cmd1   |   cmd2   &&   cmd3   ||   cmd4   ", as6, ai6, ev);
	print_sep(S2);

	print_subtitle("Check all unary operators");
	int ai7[10] = {RLS, UNSET, RLD, UNSET, RLT, UNSET, RRS, UNSET, RRD, UNSET};
	char *as7[] = {"<", "f1", "<<", "f2", "<<<", "f3", ">", "f4",">>", "f5", NULL};
	nb_err += test("<f1<<f2<<<f3>f4>>f5", as7, ai7, ev);

	int ai8[21] = {ESP, RLS, ESP, UNSET, ESP, RLD, ESP, UNSET, ESP, RLT, ESP, UNSET, ESP, RRS, ESP, UNSET, ESP, RRD, ESP, UNSET, ESP};
	char *as8[] = {" ", "<", " ", "f1", " ", "<<", " ", "f2", " ", "<<<", " ", "f3", " ", ">", " ", "f4", " ",">>", " ", "f5", " ", NULL};
	nb_err += test("  <  f1  <<  f2  <<<  f3  >  f4  >>  f5  ", as8, ai8, ev);
	print_sep(S2);

	print_subtitle("Check parenthesis");
	int ai9[3] = {PARO, UNSET, PARC};
	char *as9[] = {"(", "cmd", ")", NULL};
	nb_err += test("(cmd)", as9, ai9, ev);

	int ai10[11] = {PARO, UNSET, OPA, UNSET, PARC, OPO, PARO, UNSET, OPA, UNSET, PARC};
	char *as10[] = {"(", "cmd1", "&&", "cmd2", ")", "||", "(", "cmd3", "&&", "cmd4", ")", NULL};
	nb_err += test("(cmd1&&cmd2)||(cmd3&&cmd4)", as10, ai10, ev);

	int ai11[10] = {PARO, PARO, PARO, UNSET, OPA, UNSET, PARC, PARC, PARC};
	char *as11[] = {"(", "(", "(", "cmd1", "&&", "cmd2", ")", ")", ")",NULL};
	nb_err += test("(((cmd1&&cmd2)))", as11, ai11, ev);

	int ai12[16] = {ESP, PARO, ESP, PARO, ESP, PARO, UNSET, OPA, UNSET, PARC, ESP, PARC, ESP, PARC, ESP};
	char *as12[] = {" ", "(", " ", "(", " ", "(", "cmd1", "&&", "cmd2", ")", " ", ")", " ", ")", " ", NULL};
	nb_err += test(" ( ( (cmd1&&cmd2) ) ) ", as12, ai12, ev);

	// TODO
	//int ai13[11] = {PARO, PARO, UNSET, PARC, OPA, PARO, UNSET, PIP, UNSET, PARC, PARC};
	//char *as13[] = {"(","(","cmd1",")","&&","(","cmd2","|","cmd3",")",")",NULL};
	//nb_err += test("((cmd1)&&(cmd2|cmd3))", as13, ai13, ev);
	
	//int ai14[21] = {PARO, PARO, PARO, UNSET, OPA, UNSET, PARC, OPO, PARO, UNSET, OPA, UNSET, PARC, PARC, OPA, PARO, UNSET, PIP, UNSET, PARC, PARC};
	//char *as14[] = {"(", "(", "(", "cmd1", "&&", "cmd2", ")", "||", "(", "cmd3", "&&", "cmd4", ")", ")", "&&", "(", "cmd5", "|", "cmd6", ")", ")", NULL};
	//nb_err += test("(((cmd1&&cmd2)||(cmd3&&cmd4))&&(cmd5|cmd6))", as14, ai14, ev);

	//int ai15[32] = {PARO, PARO, PARO, PARO, UNSET, ESP, UNSET, PARC, RRS, UNSET, PARC, OPA, PARO, PARO, RLS, UNSET, ESP, UNSET, PARC, ESP, RRS, UNSET, PARC, PARC, OPA, PARO, RLS, UNSET, ESP, UNSET, PARC, PARC};
	//char *as15[] = {"(", "(", "(", "(", "echo", " ", "\"inside f1\"", ")", ">", "f1", ")", "&&", "(", "(", "<", "f1", " ", "cat", ")", " ", ">", "f2", ")", ")", "&&", "(", "<", "f2", " ", "cat", ")", ")", NULL};
	//nb_err += test("((((echo \"inside f1\")>f1)&&((<f1 cat) >f2))&&(<f2 cat))", as15, ai15, ev);
	//print_sep(S2);

	print_subtitle("Combos");
	int ai24[9] = {UNSET, RLS, UNSET, PIP, RRS, UNSET, ESP, UNSET};
	char *as24[] = {"cmd1", "<", "f2", "|", ">", "f3", " ", "cmd2", NULL};
	nb_err += test("cmd1<f2|>f3 cmd2", as24, ai24, ev);
	print_sep(S2);
	print_sep(S1);

	print_title("B| FAIL UNARY UNKNOWN OPERATOR");
	nb_err += test("<<<<", NULL, NULL, ev);
	nb_err += test("<<<<f1", NULL, NULL, ev);
	nb_err += test(">>>", NULL, NULL, ev);
	nb_err += test(">>>f1", NULL, NULL, ev);
	nb_err += test("|||", NULL, NULL, ev);
	nb_err += test("cmd1|||cmd2", NULL, NULL, ev);
	nb_err += test("&&&", NULL, NULL, ev);
	nb_err += test("cmd1&&&cmd2", NULL, NULL, ev);
	print_subtitle("List of operators not handle for now");
	nb_err += test("<(cmd)", NULL, NULL, ev);
	nb_err += test(">(cmd)", NULL, NULL, ev);
	print_sep(S2);
	print_sep(S1);

	print_title("C| FAIL UNARY RLS <");
	nb_err += test("<", NULL, NULL, ev);
	nb_err += test("< ", NULL, NULL, ev);
	nb_err += test("<>f1", NULL, NULL, ev);
	nb_err += test(" < > f1 ", NULL, NULL, ev);
	nb_err += test("cmd1<", NULL, NULL, ev);
	nb_err += test("<|cmd2", NULL, NULL, ev);
	nb_err += test("<&&cmd2", NULL, NULL, ev);
	nb_err += test("<||cmd2", NULL, NULL, ev);
	nb_err += test("< (cmd1&&cmd2)", NULL, NULL, ev);
	print_sep(S1);

	print_title("D| FAIL UNARY RLD <<");
	nb_err += test("<<", NULL, NULL, ev);
	nb_err += test("<< ", NULL, NULL, ev);
	nb_err += test("<<>f1", NULL, NULL, ev);
	nb_err += test(" << > f1 ", NULL, NULL, ev);
	nb_err += test("cmd1<<", NULL, NULL, ev);
	nb_err += test("<<|cmd2", NULL, NULL, ev);
	nb_err += test("<<&&cmd2", NULL, NULL, ev);
	nb_err += test("<<||cmd2", NULL, NULL, ev);
	nb_err += test("<< (cmd1&&cmd2)", NULL, NULL, ev);
	print_sep(S1);

	print_title("E| FAIL UNARY RLT <<<");
	nb_err += test("<<<", NULL, NULL, ev);
	nb_err += test("<<< ", NULL, NULL, ev);
	nb_err += test("<<<>f1", NULL, NULL, ev);
	nb_err += test(" <<< > f1 ", NULL, NULL, ev);
	nb_err += test("cmd1<<<", NULL, NULL, ev);
	nb_err += test("<<<|cmd2", NULL, NULL, ev);
	nb_err += test("<<<&&cmd2", NULL, NULL, ev);
	nb_err += test("<<<||cmd2", NULL, NULL, ev);
	nb_err += test("<<< (cmd1&&cmd2)", NULL, NULL, ev);
	print_sep(S1);

	print_title("F| FAIL UNARY RRS >");
	nb_err += test(">", NULL, NULL, ev);
	nb_err += test("> ", NULL, NULL, ev);
	nb_err += test("cmd>", NULL, NULL, ev);
	nb_err += test("cmd> ", NULL, NULL, ev);
	nb_err += test("<f1>", NULL, NULL, ev);
	nb_err += test(" < f1 > ", NULL, NULL, ev);
	nb_err += test(">|cmd2", NULL, NULL, ev);
	nb_err += test("cmd1>|cmd2", NULL, NULL, ev);
	nb_err += test(">||cmd2", NULL, NULL, ev);
	nb_err += test("cmd1>||cmd2", NULL, NULL, ev);
	nb_err += test(">&&cmd2", NULL, NULL, ev);
	nb_err += test("cmd1>&&cmd2", NULL, NULL, ev);
	nb_err += test("> (cmd1&&cmd2)", NULL, NULL, ev);
	print_sep(S1);

	print_title("G| FAIL UNARY RRD >");
	nb_err += test(">>", NULL, NULL, ev);
	nb_err += test(">> ", NULL, NULL, ev);
	nb_err += test("cmd>>", NULL, NULL, ev);
	nb_err += test("cmd>> ", NULL, NULL, ev);
	nb_err += test("<f1>>", NULL, NULL, ev);
	nb_err += test(" < f1 >> ", NULL, NULL, ev);
	nb_err += test(">>|cmd2", NULL, NULL, ev);
	nb_err += test("cmd1>>|cmd2", NULL, NULL, ev);
	nb_err += test(">>||cmd2", NULL, NULL, ev);
	nb_err += test("cmd1>>||cmd2", NULL, NULL, ev);
	nb_err += test(">>&&cmd2", NULL, NULL, ev);
	nb_err += test("cmd1>>&&cmd2", NULL, NULL, ev);
	nb_err += test(">> (cmd1&&cmd2)", NULL, NULL, ev);
	print_sep(S1);

	print_title("H| FAIL BINARY OPA &&");
	nb_err += test("&&", NULL, NULL, ev);
	nb_err += test(" && ", NULL, NULL, ev);
	nb_err += test("cmd&&", NULL, NULL, ev);
	nb_err += test(" cmd && ", NULL, NULL, ev);
	nb_err += test("&&cmd", NULL, NULL, ev);
	nb_err += test(" && cmd ", NULL, NULL, ev);
	print_sep(S1);

	print_title("I| FAIL BINARY OPO ||");
	nb_err += test("||", NULL, NULL, ev);
	nb_err += test(" || ", NULL, NULL, ev);
	nb_err += test("cmd||", NULL, NULL, ev);
	nb_err += test(" cmd || ", NULL, NULL, ev);
	nb_err += test("||cmd", NULL, NULL, ev);
	nb_err += test(" || cmd ", NULL, NULL, ev);
	print_sep(S1);

	print_title("J| FAIL BINARY PIP |");
	nb_err += test("|", NULL, NULL, ev);
	nb_err += test(" | ", NULL, NULL, ev);
	nb_err += test("cmd|", NULL, NULL, ev);
	nb_err += test(" cmd | ", NULL, NULL, ev);
	nb_err += test("|cmd", NULL, NULL, ev);
	nb_err += test(" | cmd ", NULL, NULL, ev);
	print_sep(S1);

	print_title("K| FAIL WITH PARENTHESIS");
	print_subtitle("Cases of 'Empty parenthesis'");
	nb_err += test("()", NULL, NULL, ev);
	nb_err += test(" ( ) ", NULL, NULL, ev);
	nb_err += test("(())", NULL, NULL, ev);
	nb_err += test(" ( ( ) ) ", NULL, NULL, ev);
	print_sep(S2);

	print_subtitle("Cases of 'Odd number of parenthesis'");
	nb_err += test("(", NULL, NULL, ev);
	nb_err += test(" ( ", NULL, NULL, ev);
	nb_err += test(")", NULL, NULL, ev);
	nb_err += test(" ) ", NULL, NULL, ev);
	nb_err += test("((cmd)", NULL, NULL, ev);
	nb_err += test(" ( ( cmd ) ", NULL, NULL, ev);
	nb_err += test("(cmd))", NULL, NULL, ev);    
	nb_err += test(" ( cmd ) )", NULL, NULL, ev);
	print_sep(S2);

	print_subtitle("Cases of 'Wrong order of parenthesis'");
	nb_err += test(")(", NULL, NULL, ev);
	nb_err += test(" ) ( ", NULL, NULL, ev);
	nb_err += test(")cmd1(", NULL, NULL, ev);
	nb_err += test("cmd1)(cmd2", NULL, NULL, ev);
	nb_err += test("cmd1)cmd2(cmd3", NULL, NULL, ev);
	print_sep(S2);

	print_subtitle("Cases of 'Wrong syntax with parenthesis'");
	nb_err += test("(cmd1)cmd2", NULL, NULL, ev);
	nb_err += test("(cmd1) cmd2", NULL, NULL, ev);
	nb_err += test("cmd1(cmd2)", NULL, NULL, ev);
	nb_err += test("cmd1 ( cmd2 )", NULL, NULL, ev);
	nb_err += test("(cmd1)(cmd2)", NULL, NULL, ev);
	nb_err += test(" ( cmd1 ) ( cmd2 ) ", NULL, NULL, ev);
	
	// TODO:Check if recursive check_lexical_rule work()
	print_subtitle("Cases of 'Wrong syntax with IMBRICATED parenthesis'");
	nb_err += test("((echo toto))", NULL, NULL, ev);
	nb_err += test("(())", NULL, NULL, ev);
	print_sep(S2);
	print_sep(S1);

	return (nb_err);
}

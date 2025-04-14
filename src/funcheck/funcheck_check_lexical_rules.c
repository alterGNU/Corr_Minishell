// =[ INCLUDE ]=================================================================
#include "minishell.h"    // ft_printf,build_tok_lst_split_by_quotes,build_tok_lst_split_by_spaces,build_tok_lst_split_by_operators,set_tok_lst_type
#include <string.h>       // strcmp
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
#define	SEPT CT"="CE
#define	SEPSUBT CB"-"CE
// =[ UTILS FUN ]===============================================================
// -[ PRINTNTIME ]--------------------------------------------------------------
int	printntime(char c, int n)
{
	for (int i = 0 ; i < n; i++)
		ft_printf("%c", c);
	return (n);
}
// -[ PRINT_TITLE ]-------------------------------------------------------------
void print_title(const char *title)
{
	ft_printf("\n"CT);
	int print_sofar = ft_printf("=[ %s ]", title);
	printntime('=', LEN - print_sofar);
	ft_printf(CE"\n");
}
// -[ PRINT_SUB_TITLE ]---------------------------------------------------------
void print_subtitle(const char *title)
{
	ft_printf("\n"CB);
	int print_sofar = ft_printf("- %s ", title);
	printntime('-', LEN - print_sofar);
	ft_printf(CE"\n");
}
// -[ PRINT_SEP ]---------------------------------------------------------------
void print_sep(const char *sep)
{
	int	i = -1;
	while (++i < LEN)
		ft_printf("%s", sep);
	ft_printf("\n");
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
// This function print details only on failures.
int	test(t_data *dt, char *str, char **tab_res, int *type_res)
{
	// Print test header
	int print_sofar = ft_printf("%s(\"%s\")", f_name, str);
	if (str)
	{
		int c = count_char_in_str('\t', str);
		if (c)
			print_sofar+=c*4;
	}
	printntime('-', LEN - print_sofar);
	// STEP1: split_by_quote(str, "\'\"") 
	dt->tok_lst = build_tok_lst_split_by_quotes(str);
	// STEP2: split_by_space(str, "\t\r\s\n") 
	map_tok_lst_if_node_not_quoted(&dt->tok_lst, build_tok_lst_split_by_spaces);
 	// STEP3: split_by_separator(str, "|&<>","")
	map_tok_lst_if_node_not_quoted(&dt->tok_lst, build_tok_lst_split_by_operators);
 	// STEP4: split_by_separator(str, "|&<>","")
	map_tok_lst_if_node_not_quoted(&dt->tok_lst, build_tok_lst_split_by_parenthesis);
	// STEP5: concatenate
	concatenate_contiguous_str(&dt->tok_lst);
	// STEP6: set_tok_lst_type
	set_tok_lst_type(dt->tok_lst);
	// STEP7: set_tok_lst_parenthesis
	set_tok_lst_parenthesis(dt);
	// STEP8: check_lexical_rules
	ft_printf("\n");
	check_lexical_rules(dt);
	ft_printf("\ntok_lst=");
	print_tok_lst(dt->tok_lst);
	ft_printf("\n");
	
	// NULL Cases
	if (!dt->tok_lst)
	{
		if (!tab_res)
			return (printntime('-', LEN - 5), ft_printf(PASS), 0);
		return (ft_printf("tab_res="), ft_print_str_array(tab_res), printntime('-', LEN - 5), ft_printf(FAIL), 1);
	}
	else
	{
		if (!tab_res)
			return (ft_printf(CR"tab_res == NULL:\n"CE), ft_lstclear(&dt->tok_lst, free_token), printntime('-', LEN - 5), ft_printf(FAIL), 1);
		if (!type_res)
			return (ft_printf(CR"type_res == NULL:\n"CE), ft_lstclear(&dt->tok_lst, free_token), printntime('-', LEN - 5), ft_printf(FAIL), 1);
	}
	// Check same size in tok_lst and in tab_res
	int size_tab_res = 0;
	while (tab_res[size_tab_res])
		size_tab_res++;
	int nb_node = 0;
	t_list	*act = dt->tok_lst;
	while (act)
	{
		nb_node++;
		act = act->next;
	}
	if (nb_node != size_tab_res)
		return (ft_printf(CR"NOT SAME SIZE:\n"CE"tab_res="), ft_print_str_array(tab_res), ft_printf("\ntok_lst="), print_tok_lst(dt->tok_lst), ft_printf("\n"),ft_lstclear(&dt->tok_lst, free_token), printntime('-', LEN - 5), ft_printf(FAIL), 1);
	int i = 0;
	act = dt->tok_lst;
	while (tab_res[i] && act)
	{
 		if (strcmp(tab_res[i], ((t_token *)act->content)->str))
			return (ft_printf(CR"NOT SAME STR:%s!=%s\n"CE"tab_res=",tab_res[i], ((t_token *)act->content)->str), ft_print_str_array(tab_res), ft_printf("\ntok_lst="), print_tok_lst(dt->tok_lst), ft_printf("\n"),ft_lstclear(&dt->tok_lst, free_token), printntime('-', LEN - 5), ft_printf(FAIL), 1);
		if (type_res[i] != ((t_token *)act->content)->type)
			return (ft_printf(CR"NOT SAME TYPE:%d!=%d\n"CE"tab_res=",type_res[i] != ((t_token *)act->content)->type), ft_print_str_array(tab_res), ft_printf("\ntok_lst="), print_tok_lst(dt->tok_lst), ft_printf("\n"),ft_lstclear(&dt->tok_lst, free_token), printntime('-', LEN - 5), ft_printf(FAIL), 1);
		act = act->next;
		i++;
	}
	return (ft_lstclear(&dt->tok_lst, free_token), printntime('-', LEN - 5), ft_printf(PASS), 0);
}

int main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;

	t_data	*dt = init_data(ev);
	if (!dt)
		return (1);
	int	nb_err = 0;

	print_title("CAS:NULL");
	print_subtitle("These cases never really happen because they're handled in main, before lexer(dt, line) is called");
	nb_err += test(dt, NULL, NULL, NULL);
	nb_err += test(dt, "", NULL, NULL);
	print_sep(SEPSUBT);

	print_title("A| PASS COMMANDS");
	//print_subtitle("Only unset and spaces-> check if quotes is count as one UNSET");
	//int ai0[9] = {ESP, UNSET, ESP, UNSET, ESP, UNSET, ESP, UNSET, ESP};
	//char *as0[] = {" ", "cmd1", " ", "arg1", " ", "arg2", " ", "\"arg3 && arg4\"", " ", NULL};
	//nb_err += test(dt, " cmd1 arg1   arg2   \"arg3 && arg4\" ", as0, ai0);
	//print_sep(SEPSUBT);

	//print_subtitle("Real command with REDIR and PIPE OPERATORS");
	//int ai1[13] = {RLS, ESP, UNSET, ESP, UNSET, ESP, PIP, ESP, UNSET, ESP, RRS, ESP, UNSET};
	//char *as1[] = {"<", " ", "file1", " ", "cat", " ", "|", " ", "cat", " ", ">", " ", "file2", NULL};
	//nb_err += test(dt, "< file1 cat | cat > file2", as1, ai1);
	//print_sep(SEPSUBT);
	//
	//print_subtitle("3 tests to check concatenation of contiguous quoted unset");
	//int ai2[5] = {UNSET, ESP, UNSET, RRD, UNSET};
	//char *as2[] = {"'e'''cho", " ", "toto", ">>", "file1", NULL};
	//nb_err += test(dt, "'e'''cho toto>>file1", as2, ai2);
	//
	//int ai3[12] = {ESP, UNSET, ESP, UNSET, OPA, UNSET, ESP, UNSET, OPO, UNSET, ESP, UNSET};
	//char *as3[] = {" ","'e'\"c\"ho", " ", "toto", "&&", "echo", " ", "OK", "||", "echo"," ", "KO", NULL};
	//nb_err += test(dt, "    'e'\"c\"ho  toto&&echo OK||echo  KO", as3, ai3);

	int ai4[13] = {ESP, UNSET, ESP, UNSET, OPA, UNSET, ESP, UNSET, OPO, UNSET, ESP, UNSET, ESP};
	char *as4[] = {" ","'e'\"c\"ho", " ", "toto", "&&", "echo", " ", "OK", "||", "echo"," ", "KO", " ", NULL};
	nb_err += test(dt, "    'e'\"c\"ho  toto&&echo OK||echo  KO    ", as4, ai4);
	print_sep(SEPSUBT);

	//print_subtitle("Check all binary operators");
	//int ai5[8] = {UNSET, PIP, UNSET, OPA, UNSET, OPO, UNSET};
	//char *as5[] = {"cmd1", "|", "cmd2", "&&", "cmd3", "||", "cmd4", NULL};
	//nb_err += test(dt, "cmd1|cmd2&&cmd3||cmd4", as5, ai5);

	//int ai6[15] = {ESP, UNSET, ESP, PIP, ESP, UNSET, ESP, OPA, ESP, UNSET, ESP, OPO, ESP, UNSET, ESP};
	//char *as6[] = {" ", "cmd1", " ",  "|", " ",  "cmd2", " ",  "&&", " ",  "cmd3", " ",  "||", " ",  "cmd4", " ",  NULL};
	//nb_err += test(dt, "   cmd1   |   cmd2   &&   cmd3   ||   cmd4   ", as6, ai6);
	//print_sep(SEPSUBT);

	//print_subtitle("Check all unary operators");
	//int ai7[10] = {RLS, UNSET, RLD, UNSET, RLT, UNSET, RRS, UNSET, RRD, UNSET};
	//char *as7[] = {"<", "f1", "<<", "f2", "<<<", "f3", ">", "f4",">>", "f5", NULL};
	//nb_err += test(dt, "<f1<<f2<<<f3>f4>>f5", as7, ai7);

	//int ai8[21] = {ESP, RLS, ESP, UNSET, ESP, RLD, ESP, UNSET, ESP, RLT, ESP, UNSET, ESP, RRS, ESP, UNSET, ESP, RRD, ESP, UNSET, ESP};
	//char *as8[] = {" ", "<", " ", "f1", " ", "<<", " ", "f2", " ", "<<<", " ", "f3", " ", ">", " ", "f4", " ",">>", " ", "f5", " ", NULL};
	//nb_err += test(dt, "  <  f1  <<  f2  <<<  f3  >  f4  >>  f5  ", as8, ai8);
	//print_sep(SEPSUBT);

	//print_subtitle("Check parenthesis");
	//int ai9[3] = {PARO, UNSET, PARC};
	//char *as9[] = {"(", "cmd", ")", NULL};
	//nb_err += test(dt, "(cmd)", as9, ai9);

	//int ai10[11] = {PARO, UNSET, OPA, UNSET, PARC, OPO, PARO, UNSET, OPA, UNSET, PARC};
	//char *as10[] = {"(", "cmd1", "&&", "cmd2", ")", "||", "(", "cmd3", "&&", "cmd4", ")", NULL};
	//nb_err += test(dt, "(cmd1&&cmd2)||(cmd3&&cmd4)", as10, ai10);

	//int ai11[10] = {PARO, PARO, PARO, UNSET, OPA, UNSET, PARC, PARC, PARC};
	//char *as11[] = {"(", "(", "(", "cmd1", "&&", "cmd2", ")", ")", ")",NULL};
	//nb_err += test(dt, "(((cmd1&&cmd2)))", as11, ai11);

	//int ai12[16] = {ESP, PARO, ESP, PARO, ESP, PARO, UNSET, OPA, UNSET, PARC, ESP, PARC, ESP, PARC, ESP};
	//char *as12[] = {" ", "(", " ", "(", " ", "(", "cmd1", "&&", "cmd2", ")", " ", ")", " ", ")", " ", NULL};
	//nb_err += test(dt, " ( ( (cmd1&&cmd2) ) ) ", as12, ai12);

	//int ai13[9] = {UNSET, RLS, UNSET, PIP, RRS, UNSET, ESP, UNSET};
	//char *as13[] = {"cmd1", "<", "f2", "|", ">", "f3", " ", "cmd2", NULL};
	//nb_err += test(dt, "cmd1<f2|>f3 cmd2", as13, ai13);
	//print_sep(SEPSUBT);
	//print_sep(SEPT);

	//print_title("B| FAIL UNARY UNKNOWN OPERATOR");
	//nb_err += test(dt, "<<<<", NULL, NULL);
	//nb_err += test(dt, "<<<<f1", NULL, NULL);
	//nb_err += test(dt, ">>>", NULL, NULL);
	//nb_err += test(dt, ">>>f1", NULL, NULL);
	//nb_err += test(dt, "|||", NULL, NULL);
	//nb_err += test(dt, "cmd1|||cmd2", NULL, NULL);
	//nb_err += test(dt, "&&&", NULL, NULL);
	//nb_err += test(dt, "cmd1&&&cmd2", NULL, NULL);
	//print_subtitle("List of operators not handle for now");
	//nb_err += test(dt, "<(cmd)", NULL, NULL);
	//nb_err += test(dt, ">(cmd)", NULL, NULL);
	//print_sep(SEPSUBT);
	//print_sep(SEPT);

	//print_title("C| FAIL UNARY RLS <");
	//nb_err += test(dt, "<", NULL, NULL);
	//nb_err += test(dt, "< ", NULL, NULL);
	//nb_err += test(dt, "<>f1", NULL, NULL);
	//nb_err += test(dt, " < > f1 ", NULL, NULL);
	//nb_err += test(dt, "cmd1<", NULL, NULL);
	//nb_err += test(dt, "<|cmd2", NULL, NULL);
	//nb_err += test(dt, "<&&cmd2", NULL, NULL);
	//nb_err += test(dt, "<||cmd2", NULL, NULL);
	//nb_err += test(dt, "< (cmd1&&cmd2)", NULL, NULL);
	//print_sep(SEPT);

	//print_title("D| FAIL UNARY RLD <<");
	//nb_err += test(dt, "<<", NULL, NULL);
	//nb_err += test(dt, "<< ", NULL, NULL);
	//nb_err += test(dt, "<<>f1", NULL, NULL);
	//nb_err += test(dt, " << > f1 ", NULL, NULL);
	//nb_err += test(dt, "cmd1<<", NULL, NULL);
	//nb_err += test(dt, "<<|cmd2", NULL, NULL);
	//nb_err += test(dt, "<<&&cmd2", NULL, NULL);
	//nb_err += test(dt, "<<||cmd2", NULL, NULL);
	//nb_err += test(dt, "<< (cmd1&&cmd2)", NULL, NULL);
	//print_sep(SEPT);

	//print_title("E| FAIL UNARY RLT <<<");
	//nb_err += test(dt, "<<<", NULL, NULL);
	//nb_err += test(dt, "<<< ", NULL, NULL);
	//nb_err += test(dt, "<<<>f1", NULL, NULL);
	//nb_err += test(dt, " <<< > f1 ", NULL, NULL);
	//nb_err += test(dt, "cmd1<<<", NULL, NULL);
	//nb_err += test(dt, "<<<|cmd2", NULL, NULL);
	//nb_err += test(dt, "<<<&&cmd2", NULL, NULL);
	//nb_err += test(dt, "<<<||cmd2", NULL, NULL);
	//nb_err += test(dt, "<<< (cmd1&&cmd2)", NULL, NULL);
	//print_sep(SEPT);

	//print_title("F| FAIL UNARY RRS >");
	//nb_err += test(dt, ">", NULL, NULL);
	//nb_err += test(dt, "> ", NULL, NULL);
	//nb_err += test(dt, "cmd>", NULL, NULL);
	//nb_err += test(dt, "cmd> ", NULL, NULL);
	//nb_err += test(dt, "<f1>", NULL, NULL);
	//nb_err += test(dt, " < f1 > ", NULL, NULL);
	//nb_err += test(dt, ">|cmd2", NULL, NULL);
	//nb_err += test(dt, "cmd1>|cmd2", NULL, NULL);
	//nb_err += test(dt, ">||cmd2", NULL, NULL);
	//nb_err += test(dt, "cmd1>||cmd2", NULL, NULL);
	//nb_err += test(dt, ">&&cmd2", NULL, NULL);
	//nb_err += test(dt, "cmd1>&&cmd2", NULL, NULL);
	//nb_err += test(dt, "> (cmd1&&cmd2)", NULL, NULL);
	//print_sep(SEPT);

	//print_title("G| FAIL UNARY RRD >");
	//nb_err += test(dt, ">>", NULL, NULL);
	//nb_err += test(dt, ">> ", NULL, NULL);
	//nb_err += test(dt, "cmd>>", NULL, NULL);
	//nb_err += test(dt, "cmd>> ", NULL, NULL);
	//nb_err += test(dt, "<f1>>", NULL, NULL);
	//nb_err += test(dt, " < f1 >> ", NULL, NULL);
	//nb_err += test(dt, ">>|cmd2", NULL, NULL);
	//nb_err += test(dt, "cmd1>>|cmd2", NULL, NULL);
	//nb_err += test(dt, ">>||cmd2", NULL, NULL);
	//nb_err += test(dt, "cmd1>>||cmd2", NULL, NULL);
	//nb_err += test(dt, ">>&&cmd2", NULL, NULL);
	//nb_err += test(dt, "cmd1>>&&cmd2", NULL, NULL);
	//nb_err += test(dt, ">> (cmd1&&cmd2)", NULL, NULL);
	//print_sep(SEPT);

	//print_title("H| FAIL BINARY OPA &&");
	//nb_err += test(dt, "&&", NULL, NULL);
	//nb_err += test(dt, " && ", NULL, NULL);
	//nb_err += test(dt, "cmd&&", NULL, NULL);
	//nb_err += test(dt, " cmd && ", NULL, NULL);
	//nb_err += test(dt, "&&cmd", NULL, NULL);
	//nb_err += test(dt, " && cmd ", NULL, NULL);
	//print_sep(SEPT);

	//print_title("I| FAIL BINARY OPO ||");
	//nb_err += test(dt, "||", NULL, NULL);
	//nb_err += test(dt, " || ", NULL, NULL);
	//nb_err += test(dt, "cmd||", NULL, NULL);
	//nb_err += test(dt, " cmd || ", NULL, NULL);
	//nb_err += test(dt, "||cmd", NULL, NULL);
	//nb_err += test(dt, " || cmd ", NULL, NULL);
	//print_sep(SEPT);

	//print_title("J| FAIL BINARY PIP |");
	//nb_err += test(dt, "|", NULL, NULL);
	//nb_err += test(dt, " | ", NULL, NULL);
	//nb_err += test(dt, "cmd|", NULL, NULL);
	//nb_err += test(dt, " cmd | ", NULL, NULL);
	//nb_err += test(dt, "|cmd", NULL, NULL);
	//nb_err += test(dt, " | cmd ", NULL, NULL);
	//print_sep(SEPT);

	print_title("K| FAIL WITH PARENTHESIS");
	print_subtitle("Cases of 'Empty parenthesis'");
	nb_err += test(dt, "()", NULL, NULL);
	//nb_err += test(dt, " ( ) ", NULL, NULL);
	//nb_err += test(dt, "(())", NULL, NULL);
	//nb_err += test(dt, " ( ( ) ) ", NULL, NULL);
	print_sep(SEPSUBT);

	print_subtitle("Cases of 'Odd number of parenthesis'");
	nb_err += test(dt, "(", NULL, NULL);
	//nb_err += test(dt, " ( ", NULL, NULL);
	//nb_err += test(dt, ")", NULL, NULL);
	//nb_err += test(dt, " ) ", NULL, NULL);
	//nb_err += test(dt, ")(", NULL, NULL);
	//nb_err += test(dt, " ) ( ", NULL, NULL);
	//nb_err += test(dt, "((cmd)", NULL, NULL);
	//nb_err += test(dt, " ( ( cmd ) ", NULL, NULL);
	//nb_err += test(dt, "(cmd))", NULL, NULL);    
	//nb_err += test(dt, " ( cmd ) )", NULL, NULL);
	//nb_err += test(dt, "(cmd1)cmd2", NULL, NULL);
	//nb_err += test(dt, "(cmd1) cmd2", NULL, NULL);
	//nb_err += test(dt, "cmd1(cmd2)", NULL, NULL);
	//nb_err += test(dt, "cmd1 ( cmd2 )", NULL, NULL);
	//nb_err += test(dt, "(cmd1)(cmd2)", NULL, NULL);
	//nb_err += test(dt, " ( cmd1 ) ( cmd2 ) ", NULL, NULL);
	print_sep(SEPSUBT);
	print_sep(SEPT);

	return (free_data(&dt), nb_err);
}

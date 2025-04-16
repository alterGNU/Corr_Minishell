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
	if (!tab_res || !type_res)
		printf("\n");
	// LEXING
	lexer(str, &data);
	printf("\n");
	// CHECK TOK_LST == NULL
	if (!data->tok_lst)
	{
		if (!tab_res)
			return (free_data(&data), printntime(S3, LEN - 5), printf(PASS), 0);
		return (free_data(&data), print_strarr(tab_res), printf("\ntok_lst=NULL\n"), printntime(S3, LEN - 5), printf(FAIL), 1);
	}
	printf("\nEXIT 1\n");
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
	int ai1[13] = {RLS, ESP, UNSET, ESP, UNSET, ESP, PIP, ESP, UNSET, ESP, RRS, ESP, UNSET};
	char *as1[] = {"<", " ", "file1", " ", "cat", " ", "|", " ", "cat", " ", ">", " ", "file2", NULL};
	nb_err += test("< file1 cat | cat > file2", as1, ai1, ev);
	
	int ai2[5] = {UNSET, ESP, UNSET, RRD, UNSET};
	char *as2[] = {"'e'''cho", " ", "toto", ">>", "file1", NULL};
	nb_err += test("'e'''cho toto>>file1", as2, ai2, ev);
	
	int ai3[12] = {ESP, UNSET, ESP, UNSET, OPA, UNSET, ESP, UNSET, OPO, UNSET, ESP, UNSET};
	char *as3[] = {" ","'e'\"c\"ho", " ", "toto", "&&", "echo", " ", "OK", "||", "echo"," ", "KO", NULL};
	nb_err += test("    'e'\"c\"ho  toto&&echo OK||echo  KO", as3, ai3, ev);

	int ai4[31] = {ESP,PARO,ESP,UNSET,ESP,UNSET,ESP,OPA,ESP,UNSET,ESP,UNSET,ESP,PARC,ESP,OPO,ESP,PARO,ESP,UNSET,ESP,UNSET,ESP,OPA,ESP,UNSET,ESP,UNSET,ESP,PARC,ESP};
	char *as4[] = {" ","("," ","echo"," ","1"," ","&&"," ","echo"," ","2"," ",")"," ","||"," ","("," ", "echo"," ", "3"," ","&&"," ","echo"," ","4"," ",")"," ",NULL};
	nb_err += test("   ( echo 1 && echo 2 ) || ( echo 3 && echo 4 )   ", as4, ai4, ev);

	int ai5[17] = {UNSET, ESP, OPA, ESP, PARO, UNSET, ESP, OPO, ESP, PARO, UNSET, ESP, OPA, ESP, UNSET, PARC, PARC};
	char *as5[] = {"cmd1", " ", "&&", " ", "(", "cmd2", " ", "||", " ", "(", "cmd3", " ", "&&", " ", "cmd4", ")", ")", NULL};
	nb_err += test("cmd1 && (cmd2 || (cmd3 && cmd4))", as5, ai5, ev);

	int ai6[11] = {UNSET, OPA, PARO, UNSET, OPO, PARO, UNSET, OPA, UNSET, PARC, PARC};
	char *as6[] = {"cmd1", "&&", "(", "cmd2", "||", "(", "cmd3", "&&", "cmd4", ")", ")", NULL};
	nb_err += test("cmd1&&(cmd2||(cmd3&&cmd4))", as6, ai6, ev);

	int ai7[11] = {PARO, PARO, UNSET, OPA, UNSET, PARC, OPO, UNSET, PARC, OPA, UNSET};
	char *as7[] = {"(","(","cmd1", "&&","cmd2", ")", "||", "cmd3", ")", "&&", "cmd4", NULL};
	nb_err += test("((cmd1&&cmd2)||cmd3)&&cmd4", as7, ai7, ev);

	nb_err += test("diff <(echo toto) <(echo toto)", NULL, NULL, ev);
	nb_err += test("cat >(echo toto)", NULL, NULL, ev);

	print_title("B| FAIL MULTIPLES");
	nb_err += test("< << <<< <<<< <<<<< <<<<<<", NULL, NULL, ev);
	nb_err += test("> >> >>> >>>> >>>>> >>>>>>", NULL, NULL, ev);
	nb_err += test("| || ||| |||| ||||| ||||||", NULL, NULL, ev);
	nb_err += test("& && &&& &&&& &&&&& &&&&&&", NULL, NULL, ev);
	nb_err += test(" <><<<< < ||| & &&&", NULL, NULL, ev);
	nb_err += test(" <><<<< < ||| & &&&", NULL, NULL, ev);

	print_title("C| FAIL <");
	nb_err += test("cat < |", NULL, NULL, ev);
	nb_err += test("cat < ", NULL, NULL, ev);
	nb_err += test("cat <", NULL, NULL, ev);
	nb_err += test("(cat < )", NULL, NULL, ev);
	nb_err += test("(cat <)", NULL, NULL, ev);

	print_title("D| FAIL <<");
	nb_err += test("cat << |", NULL, NULL, ev);
	nb_err += test("cat << ", NULL, NULL, ev);
	nb_err += test("cat <<", NULL, NULL, ev);
	nb_err += test("(cat <<)", NULL, NULL, ev);
	nb_err += test("(cat << )", NULL, NULL, ev);

	print_title("E| FAIL <<<");
	nb_err += test("<<< |", NULL, NULL, ev);
	nb_err += test("<<< ", NULL, NULL, ev);
	nb_err += test("<<<", NULL, NULL, ev);
	nb_err += test("( <<<)", NULL, NULL, ev);
	nb_err += test("( <<< )", NULL, NULL, ev);

	print_title("E| FAIL >");
	nb_err += test("echo toto >|", NULL, NULL, ev);
	nb_err += test("echo toto >", NULL, NULL, ev);
	nb_err += test("echo toto > ", NULL, NULL, ev);
	nb_err += test("(echo toto >)", NULL, NULL, ev);
	nb_err += test("(echo toto > )", NULL, NULL, ev);
	nb_err += test("echo toto >(f2)", NULL, NULL, ev);
	nb_err += test("echo toto > (f2)", NULL, NULL, ev);

	print_title("G| FAIL >>");
	nb_err += test("echo toto >>|", NULL, NULL, ev);
	nb_err += test("echo toto >>", NULL, NULL, ev);
	nb_err += test("echo toto >> ", NULL, NULL, ev);
	nb_err += test("(echo toto >>)", NULL, NULL, ev);
	nb_err += test("(echo toto >> )", NULL, NULL, ev);
	nb_err += test("echo toto >>(f2)", NULL, NULL, ev);
	nb_err += test("echo toto >> (f2)", NULL, NULL, ev);

	print_title("H| FAIL &&");
	nb_err += test("&&", NULL, NULL, ev);
	nb_err += test("echo toto&&", NULL, NULL, ev);
	nb_err += test("&&echo toto", NULL, NULL, ev);

	print_title("I| FAIL ||");
	nb_err += test("||", NULL, NULL, ev);
	nb_err += test("echo toto||", NULL, NULL, ev);
	nb_err += test("||echo toto", NULL, NULL, ev);

	print_title("J| FAIL |");
	nb_err += test("|", NULL, NULL, ev);
	nb_err += test("ls|", NULL, NULL, ev);
	nb_err += test("|ls", NULL, NULL, ev);

	print_title("K| FAIL ERR_TYPE");
	nb_err += test("<<<<", NULL, NULL, ev);
	nb_err += test(">>>", NULL, NULL, ev);
	nb_err += test("|||", NULL, NULL, ev);
	nb_err += test("&&&", NULL, NULL, ev);
	nb_err += test("&", NULL, NULL, ev);
	nb_err += test("&&&&", NULL, NULL, ev);

	print_title("K| FAIL PARENTHESIS LEXICAL RULES");
	nb_err += test("(", NULL, NULL, ev);
	nb_err += test(" ( ", NULL, NULL, ev);
	nb_err += test(")", NULL, NULL, ev);
	nb_err += test(" ) ", NULL, NULL, ev);
	nb_err += test(")(", NULL, NULL, ev);
	nb_err += test(" ) ( ", NULL, NULL, ev);
	nb_err += test("()", NULL, NULL, ev);
	nb_err += test(" ( ) ", NULL, NULL, ev);
	nb_err += test("(())", NULL, NULL, ev);
	nb_err += test(" ( ( ) ) ", NULL, NULL, ev);
	nb_err += test("( echo toto", NULL, NULL, ev);
	nb_err += test("echo toto)", NULL, NULL, ev);
	nb_err += test("(< file1 cat |) cat >> file2", NULL, NULL, ev);
	nb_err += test("(< file1 cat | ) cat >> file2", NULL, NULL, ev);
	nb_err += test("< file1 cat ( | cat >> file2)", NULL, NULL, ev);
	nb_err += test("< file1 cat (| cat >> file2)", NULL, NULL, ev);
	nb_err += test("(echo toto && ) echo tata", NULL, NULL, ev);
	nb_err += test("echo toto ( && echo tata)", NULL, NULL, ev);
	nb_err += test("(echo toto || ) echo tata", NULL, NULL, ev);
	nb_err += test("echo toto ( || echo tata)", NULL, NULL, ev);
	//nb_err += test("((echo toto))", NULL, NULL, ev);// TODO:repare check_lexical_rules()

	return (nb_err);
}

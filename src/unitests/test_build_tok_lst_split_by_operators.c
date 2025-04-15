// =[ INCLUDE ]=================================================================
#include "minishell.h"  // ⚠️ ft_print_str_array, ⚠️ print_tok_lst, build_tok_lst_split_by_operators
#include <string.h>     // strncmp
#include <stdio.h>      // printf ⚠️  Use printf, not ft_printf or write
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "build_tok_lst_split_by_operators"
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
	printntime(S3, LEN - print_sofar - 5);
	if (!str || !tab_res || !*tab_res)
		printf("---\n");
	t_list	*res = build_tok_lst_split_by_operators(str);
	if (!res)
	{
		if (!tab_res)
			return (printntime(S3, LEN - 5), printf(PASS), 0);
		return (printf("---\n%s return NULL\n", f_name), print_strarr(tab_res), printf("\n"), printntime(S3, LEN - 5), printf(FAIL), 1);
	}
	act = res;
	while (tab_res[i] && act && !strcmp(tab_res[i], ((t_token *)(act->content))->str))
	{
		act = act->next;
		i++;
	}
	printf("-----\n");
	print_strarr(tab_res);
	printf("\ntok_lst=");
	fflush(stdout);
	print_tok_lst(res);
	printf("\n");
	if (!tab_res[i] && !act)
		return (ft_lstclear(&res, free_token), printntime(S3, LEN - 5), printf(PASS), 0);
	if ((!tab_res[i] && act) || (tab_res[i] && !act))
		return (ft_lstclear(&res, free_token), printntime(S3, LEN - 5), printf(FAIL), 1);
	if (strcmp(tab_res[i], ((t_token *)(act->content))->str))
		return (ft_lstclear(&res, free_token), printntime(S3, LEN - 5), printf(FAIL), 1);
	return (ft_lstclear(&res, free_token), printf(PASS), 0);
}

int main()
{
	int	nb_err = 0;

	print_title("CAS:NULL");
	print_subtitle("These cases never really happen because they're handled in main, before lexer(dt, line) is called");
	nb_err += test(NULL, NULL);
	nb_err += test("", NULL);
	print_sep(S2);
	print_sep(S1);

	print_title("CAS NO OPERATOR");
	char *t0[] = {"   abcd   ", NULL};
	nb_err += test("   abcd   ", t0);
	print_sep(S1);

	print_title("CAS ONE OPERATOR");
	char *t1[] = {"<", NULL};
	nb_err += test("<", t1);
	char *t2[] = {">", NULL};
	nb_err += test(">", t2);
	char *t3[] = {"|", NULL};
	nb_err += test("|", t3);
	char *t4[] = {"&", NULL};
	nb_err += test("&", t4);
	print_sep(S1);

	print_title("CAS ONLY OPERATORS (MULTIPLE)");
	char *t5[] = {"<<<", NULL};
	nb_err += test("<<<", t5);
	char *t6[] = {"<", ">", "&", "|", NULL};
	nb_err += test("<>&|", t6);
	char *t7[] = {"<<<", ">", "&&", "|", NULL};
	nb_err += test("<<<>&&|", t7);
	char *t8[] = {"  ", "<<<", "   ", ">", "  ", "&&", "  ","|", "  ", NULL};
	nb_err += test("  <<<   >  &&  |  ", t8);
	char *t9[] = {"|", "&&&", "||", NULL};
	nb_err += test("|&&&||", t9);
	char *t10[] = {"<", ">", "<", ">", NULL};
	nb_err += test("<><>", t10);
	print_sep(S1);

	print_title("CAS SIMPLE-OPERATORS WITH COMMANDS");
	char *t11[] = {"<", " echo titi", "|", "cat", NULL};
	nb_err += test("< echo titi|cat", t11);
	char *t12[] = {"  ","<", " echo titi", "|", "cat", NULL};
	nb_err += test("  < echo titi|cat", t12);
	char *tt12[] = {"  ","<", " echo titi ", "|", "ls", NULL};
	nb_err += test("  < echo titi |ls", tt12);
	print_sep(S1);

	print_title("CAS MULTIPLE-OPERATORS WITH COMMANDS");
	char *t13[] = {"<<<", " $titi ", "|", " cat", NULL};
	nb_err += test("<<< $titi | cat", t13);
	char *t14[] = {"tutu=titi", "&&", "<<<", "$titi cat ", "&", NULL};
	nb_err += test("tutu=titi&&<<<$titi cat &", t14);
	print_sep(S1);

	return (nb_err);
}

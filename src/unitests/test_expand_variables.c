// =[ INCLUDE ]=================================================================
#include "minishell.h"    // char	*expand_variables(t_data **dt, char *str)
#include <string.h>       // strcmp
#include <stdio.h>        // printf, fflush
						  // ⚠️  Some of minishell print fun. use ~write=>fflush
						  // ⚠️  Depends on libft/array/ft_print_str_array()
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "expand_variables"
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
int	test(t_list *env_lst, char *src, char *res)
{
	// Print test header
	int print_sofar	 = printf("%s(env_lst, ", f_name);
	printf(CB);
	print_sofar 	+= printf("%s", src);
	printf(CE);
	print_sofar 	+= printf(")==");
	printf(CV);
	print_sofar 	+= printf("%s", res);
	printf(CE);
	if (src)
	{
		int c = count_char_in_str('\t', src);
		if (c)
			print_sofar+=c*2;
	}
	printntime(S3, LEN - print_sofar);
	printf("\n");
	char *ft = expand_variables(env_lst, src);
	if (!src && env_lst)
		write(1,"\n",1);
	// CHECK ft == NULL
	if (!ft)
	{
		if (!res)
			return (printntime(S3, LEN - 5), printf(PASS), 0);
		return (printf(CY"ft:"CR"NULL"CY" != res:"CR"%s\n"CE, res), printntime(S3, LEN - 5), printf(FAIL), 1);
	}
	if (!strcmp(ft, res))
		return (ft_free((void **)&ft), printntime(S3, LEN - 5), printf(PASS), 0);
	return (printf(CY"ft:"CR"%s"CY" != res:"CR"%s\n"CE, ft, res), ft_free((void **)&ft), printntime(S3, LEN - 5), printf(FAIL), 1);
}

// =============================================================================
// MAIN
// =============================================================================
int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	int	nb_err = 0;
	
	// =[ 	DATA USED ]=========================================================
	// char	*expand_variables(t_list *env_lst, char *str);
	t_list *real_env_lst = build_env_lst(ev);
	//print_env_lst(real_env_lst); // TODO: UN-COMMENT TO PRINT REAL_ENV_LST
	char *ev1[7] = {"v1=A", "v2=B", "v3=", "v_4=D=d", "v_5==E", "v_6='fff'", NULL};
	t_list *env_lst_1 = build_env_lst(ev1);
	//print_env_lst(env_lst_1); // TODO: UN-COMMENT TO PRINT ENV_LST_1
	
	// =[ NULL CASES ]==========================================================
	print_title("A| NULL CASES");
	print_subtitle("env_lst==NULL && str==NULL");
	nb_err += test(NULL, NULL, NULL);
	print_sep(S2);
	print_subtitle("env_lst==NULL");
	nb_err += test(NULL, "coucou", NULL);
	print_sep(S2);
	print_subtitle("str == NULL");
	nb_err += test(env_lst_1, NULL, NULL);
	print_sep(S2);
	print_subtitle("str == EMPTY");
	nb_err += test(env_lst_1, "", NULL);
	print_sep(S2);
	print_sep(S1);
	
	// =[ SIMPLE CASES ]========================================================
	print_title("B| SIMPLE CASES");
	print_subtitle("NO QUOTES, NO EQUALS, NO DOLLARS, NO BACKSLASH");
	nb_err += test(env_lst_1, "ls", "ls");
	nb_err += test(env_lst_1, "echo toto", "echo toto");
	print_sep(S2);

	print_subtitle("ONLY QUOTES");
	char *b1 = "'e'ch\"o\" \"toto titi 'tu''tu'\"";
	nb_err += test(env_lst_1, b1, b1);
	print_sep(S2);

	print_subtitle("ONLY EQUALS");
	char *b2 = "toto=titi";
	char *b3 = "empty=";
	char *b4 = "_=should_be_protected";
	char *b5 = "=invalid_affectation";
	char *b6 = "a=A b=B c=";
	nb_err += test(env_lst_1, b2, b2);
	nb_err += test(env_lst_1, b3, b3);
	nb_err += test(env_lst_1, b4, b4);
	nb_err += test(env_lst_1, b5, b5);
	nb_err += test(env_lst_1, b6, b6);
	print_sep(S2);

	print_subtitle("ONLY DOLLARS");
	char *b7 = "echo $";
	char *rb7 = "echo $";
	nb_err += test(env_lst_1, b7, rb7);
	char *b8 = "$unknown_var_name";
	char *rb8 = "";
	nb_err += test(env_lst_1, b8, rb8);
	char *b9 = "$ var";
	char *rb9 = "$ var";
	nb_err += test(env_lst_1, b9, rb9);
	// TODO: Implement ft_get_pid() and then compare with real get_pid() value
	//char *b10 = "$$ $$$ $$$$";
	//char *rb10 = "PID PID$ PIDPID";
	//nb_err += test(env_lst_1, b10, rb10);
	char *b11 = "$ $v1 v2:$v2 $ v3:$v3 $ unk=<$unk>";
	char *rb11 = "$ A v2:B $ v3: $ unk=<>";
	ft_printf(CB"ENV_LST=\n"CY);
	print_env_lst(env_lst_1);
	ft_printf(CE);
	nb_err += test(env_lst_1, b11, rb11);
	print_sep(S2);

	print_subtitle("ONLY BACKSLASH");
	char *b12 = "\\a\\b\\ \\c\\d" ;
	char *rb12 = "ab cd";
	nb_err += test(env_lst_1, b12, rb12);
	char *b13 = "\\\\a\\\\b\\\\ \\\\c\\\\d" ;
	char *rb13 = "\\a\\b\\ \\c\\d";
	nb_err += test(env_lst_1, b13, rb13);
	print_sep(S2);
	print_sep(S1);

	// =[ 	COMBOS NO QUOTES ]==================================================
	print_title("C| COMBOS WITHOUT QUOTES");
	print_sep(S1);
	
	// =[ 	FREE ENV_LST ]======================================================
	ft_lstclear(&real_env_lst, free_env);
	ft_lstclear(&env_lst_1, free_env);
	return (nb_err);
}

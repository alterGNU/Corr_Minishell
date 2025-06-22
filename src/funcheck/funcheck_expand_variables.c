// =[ INCLUDE ]=================================================================
#include "minishell.h"    // char	*expand_variables(t_data **dt, char *str)
#include <string.h>       // strcmp
#include <stdio.h>        // printf, fflush
						  // ⚠️  Some of minishell print fun. use ~write=>fflush
						  // ⚠️  Depends on libft/array/ft_print_str_array()
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "expand_variables"
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
int	test(t_list *env_lst, char *src, char *res)
{
	// Print test header
	int print_sofar	 = printf("%s(env_lst, ", f_name);
	printf(CB);
	print_sofar 	+= printf("%s", src);
	printf(E);
	print_sofar 	+= printf(")==");
	printf(CV);
	print_sofar 	+= printf("%s", res);
	printf(E);
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
		return (printf(CY"ft:"CR"NULL"CY" != res:"CR"%s\n"E, res), printntime(S3, LEN - 5), printf(FAIL), 1);
	}
	if (!strcmp(ft, res))
		return (ft_free((void **)&ft), printntime(S3, LEN - 5), printf(PASS), 0);
	return (printf(CY"ft :"CR"%s"CY"\nres:"CR"%s\n"E, ft, res), ft_free((void **)&ft), printntime(S3, LEN - 5), printf(FAIL), 1);
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
	t_data *dt = init_data(ev);
	char *ev1[7] = {"v1=A", "v2=B", "v3=", "v_4=D=d", "v_5==E", "v_6='fff'", NULL};
	t_list *env_lst_1 = build_env_lst(ev1);
	
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
	char *rb1 = "echo toto titi 'tu''tu'";
	nb_err += test(env_lst_1, b1, rb1);
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
	char *b07 = "$";
	nb_err += test(env_lst_1, b07, b07);
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
	nb_err += test(env_lst_1, b11, rb11);
	print_sep(S2);

	print_subtitle("ONLY BACKSLASH");
	char *b12 = "\\" ;
	char *rb12 = "\\";
	nb_err += test(env_lst_1, b12, rb12);
	char *b13 = "\\\\" ;
	char *rb13 = "\\";
	nb_err += test(env_lst_1, b13, rb13);
	char *b14 = "\\a\\b\\ \\c\\d" ;
	char *rb14 = "ab cd";
	nb_err += test(env_lst_1, b14, rb14);
	char *b15 = "\\\\a\\\\b\\\\ \\\\c\\\\d" ;
	char *rb15 = "\\a\\b\\ \\c\\d";
	nb_err += test(env_lst_1, b15, rb15);
	char *b16 = ". \\ \\ ." ;
	char *rb16 = ".   ." ;
	nb_err += test(env_lst_1, b16, rb16);
	print_sep(S2);
	print_sep(S1);

	// =[ 	COMBOS NO QUOTES ]==================================================
	print_title("C| COMBOS WITHOUT QUOTES");
	//char *c0 = "valid=value empty= =unvalid";

	print_subtitle("COMBOS EQUALS x DOLLARS");
	char *c1 = "user=$USER empty=$unknown $unk=unknown $unk=$USER";
	char *rc1 = "user=altergnu empty= =unknown =altergnu";
	nb_err += test(dt->env_lst, c1, rc1);
	print_sep(S2);

	print_subtitle("COMBOS EQUALS x BACKSLASHS");
	char *c2 = "\\valid\\=value\\ empty=\\ \\\\=unvalid\\";
	char *rc2 = "valid=value empty= \\=unvalid\\";
	nb_err += test(dt->env_lst, c2, rc2);
	print_sep(S2);

	print_subtitle("COMBOS EQUALS x DOLLARS x BACKSLASHS");
	char *c3 = "\\user\\=$USER\\ empty=\\$unknown $\\unk=unknown $unk=$USER";
	char *rc3 = "user=altergnu empty=$unknown $unk=unknown =altergnu";
	nb_err += test(dt->env_lst, c3, rc3);
	print_sep(S2);

	print_sep(S1);

	// =[ 	COMBOS DOUBLE QUOTES ] =============================================
	print_title("D| COMBOS DOUBLE QUOTES");
	//char *d0 = "\"unvalid\"=value var_name=\"valid affect\" \"not_a=valid_affect\"";

	// UNCOMMENT BUT WILL FAIL 
	//print_subtitle("COMBOS $$ and $?");
	//char *d0 = "\"$\" \"$$\" \" $ \" \"'$?'\" \"$'v1' $\\v2\"";
	//char *rd0 = "$ PID  $  '0' $'v1' $\\v2";
	//nb_err += test(dt->env_lst, d0, rd0);
	//print_sep(S2);

	print_subtitle("COMBOS DOUBLE x DOLLARS");
	char *d1 = "\"$\" \"$ $\" \" $ \" \"'$v_4'$v_5'$v_6'\" \"$'v1' $\\v2\"";
	char *rd1 = "$ $ $  $  'D=d'=E''fff'' $'v1' $\\v2";
	nb_err += test(env_lst_1, d1, rd1);
	char *d2 = "$\"v1\" $\"v2 $v2\"";
	char *rd2 = "$v1 $v2 B";
	nb_err += test(env_lst_1, d2, rd2);
	print_sep(S2);

	print_subtitle("COMBOS DOUBLE x BACKSLASHS");
	char *d3 = "\"\\\\ \\a\\b\\ \\c\\d\"";
	char *rd3 = "\\ \\a\\b\\ \\c\\d";
	nb_err += test(env_lst_1, d3, rd3);
	print_sep(S2);

	print_subtitle("COMBOS DOUBLE x BACKSLASHS x DOLLARS");
	char *d4 = "\"$v1 $\\v1 \\$v1\"";
	char *rd4 = "A $\\v1 $v1";
	nb_err += test(env_lst_1, d4, rd4);
	print_sep(S2);

	print_subtitle("COMBOS DOUBLE x SINGLE x BACKSLASHS x DOLLARS");
	char *d5 = "\"\'$v1\' \'$\'v1 \'$v\'1 \'$\'\'v\'\'1\'\'\"";
	char *rd5 = "\'A\' \'$\'v1 \'\'1 \'$\'\'v\'\'1\'\'";
	nb_err += test(env_lst_1, d5, rd5);
	print_sep(S2);

	print_sep(S1);

	// =[ 	COMBOS SINGLE QUOTES ] =============================================
	print_title("COMBOS SINGLES");

	print_subtitle("COMBOS SINGLE x DOUBLE");
	char *e1 = "\'\"$v_4\" \"$\"v_4 \"$v\"_4\'";
	char *re1 = "\"$v_4\" \"$\"v_4 \"$v\"_4";
	nb_err += test(env_lst_1, e1, re1);
	print_sep(S2);

	print_subtitle("COMBOS SINGLE x BACKSLASHS");
	char *e2 = "\'\\\\ \\a\\b\\ \\c\\d\'";
	char *re2 = "\\\\ \\a\\b\\ \\c\\d";
	nb_err += test(env_lst_1, e2, re2);
	print_sep(S2);

	print_subtitle("COMBOS SINGLE x BACKSLASHS");
	char *e3 = "\'\\\\ \\a\\b\\ \\c\\d\'";
	char *re3 = "\\\\ \\a\\b\\ \\c\\d";
	nb_err += test(env_lst_1, e3, re3);
	print_sep(S2);

	print_subtitle("COMBOS SINGLE x BACKSLASHS x DOLLARS");
	char *e4 = "\'$v1 $\\v1 \\$v1\'";
	char *re4 = "$v1 $\\v1 \\$v1";
	nb_err += test(env_lst_1, e4, re4);
	print_sep(S2);
	
	print_sep(S1);
	
	// =[ 	FREE ENV_LST ]======================================================
	free_data(&dt);
	ft_lstclear(&env_lst_1, free_env);
	return (nb_err);
}

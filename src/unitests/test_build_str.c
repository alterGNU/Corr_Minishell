// =[ INCLUDE ]=================================================================
#include "minishell.h"    // char	*build_str(t_data **dt, char *str)
#include <string.h>       // strcmp
#include <stdio.h>        // printf, fflush
						  // ⚠️  Some of minishell print fun. use ~write=>fflush
						  // ⚠️  Depends on libft/array/ft_print_str_array()
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "build_str"
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
int	test(t_data **dt, char *str, char *res)
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
	lexer(str, &dt);
	// CHECK TOK_LST == NULL
	if (!dt->tok_lst)
	{
		if (!tab_res)
			return (free_data(&dt), printf(CV"tok_lst == tab_res == NULL\n"CE),printntime(S3, LEN - 5), printf(PASS), 0);
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
		return (printf(CR"DIFF.IN.SIZE:len_tab_res=%d VS len_tok_lst=%d\n"CE, len_tab_res, len_tok_lst), printntime(S3, LEN - 5), printf(FAIL), 1);
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

// =============================================================================
// MAIN
// =============================================================================
int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	t_data	*dt = init_data(ev);
	if (!dt)
		return (ft_fprintf(2, ER"fail init_data()"CE));
	add_env_lst_node(&dt->env, NULL);
	add_env_lst_node(&dt->env, "N0=");
	add_env_lst_node(&dt->env, "Dq=\"\"");
	add_env_lst_node(&dt->env, "Sq=''");
	add_env_lst_node(&dt->env, "v1=toto");
	add_env_lst_node(&dt->env, "v_2=titi");
	add_env_lst_node(&dt->env, "v3= 'with' \"quotes\"");
	add_env_lst_node(&dt->env, "v4= spaces before and after ");
	//ft_printf("ENV=");
	//print_env_lst(dt->env);
	//ft_printf("\n");
	int	nb_err = 0;
	// =[  ]====================================================================
	print_title("A| NULL CASES");
	print_subtitle("str == NULL");
	//nb_err += test(dt,NULL,NULL);
	print_sep(S2);
	print_subtitle("str == EMPTY");
	//nb_err += test(dt,"",NULL);
	print_sep(S2);
	print_sep(S1);
	// =[  ]====================================================================
	print_title("B| NO VAR IN STR");
	print_sep(S1);
	// =[  ]====================================================================
	print_title("C| SINGLE VAR IN STR");
	print_sep(S1);
	// =[  ]====================================================================
	print_title("D| MULTIPLE VAR IN STR");
	print_sep(S1);
	
	return (free_data(&dt), nb_err);
}

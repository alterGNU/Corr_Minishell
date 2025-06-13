// =[ INCLUDE ]=================================================================
#include "minishell.h"    // build_tok_lst_split_by_quotes,build_tok_lst_split_by_spaces,build_tok_lst_split_by_operators,set_tok_lst_type
#include <string.h>       // strcmp
#include <stdio.h>        // printf, fflush
						  // ⚠️  Some of minishell print fun. use ~write=>fflush
						  // ⚠️  Depends on libft/array/ft_print_str_array()
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "build_str_arr"
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
int	print_t_token_type(int i)
{
	if (i == -1)
		return (printf("UNSET"));
	if (i == 0)
		return (printf("ESP"));
	if (i == 1)
		return (printf("CMD"));
	if (i == 2)
		return (printf("ARG"));
	if (i == 3)
		return (printf("FIL"));
	if (i == 4)
		return (printf("AFF"));
	if (i == 10)
		return (printf("RLS"));
	if (i == 11)
		return (printf("RLD"));
	if (i == 12)
		return (printf("RLT"));
	if (i == 13)
		return (printf("RRS"));
	if (i == 14)
		return (printf("RRD"));
	if (i == 15)
		return (printf("PIP"));
	if (i == 20)
		return (printf("OPO"));
	if (i == 21)
		return (printf("OPA"));
	if (i == 30)
		return (printf("PARO"));
	if (i == 31)
		return (printf("PARC"));
	if (i == 42)
		return (printf("ERR"));
	return (printf("???"));
}

/*
 * print a t_token tab_raw[]
 */
int	print_tab_raw(t_token tab_raw[])
{
	int		i;
	int		psf;

	printf(CY);
	psf = printf("[");
	i = 0;
	while (tab_raw[i].str)
	{
		printf(CY"\""CM);
		psf += 2 + printf("%s", tab_raw[i].str);
		printf(CY"\"");
		if (tab_raw[i + 1].str)
			psf += printf(", ");
		printf(CY);
		i++;
	}
	psf += printf("]");
	printf(CE);
	return (psf);
}

/*
 * print a t_env tab_res[]
 */
int	print_tab_res(t_env tab_res[])
{
	int		i;
	int		psf;

	printf(CY);
	psf = printf("tab_res=[");
	i = 0;
	while (tab_res[i].name && tab_res[i].value)
	{
		printf(CY"\""CM);
		psf += 2 + printf("{%s, %s}", tab_res[i].name, tab_res[i].value);
		printf(CY"\"");
		if (tab_res[i+1].name && tab_res[i+1].value)
			psf += printf(", ");
		printf(CY);
		i++;
	}
	psf += printf("]");
	printf(CE);
	return (psf);
}

/*
 * create a t_dlist of t_token from an array of t_token
 */
t_dlist	*create_raw_from_tab_raw(t_token tab_raw[])
{
	t_dlist *raw = NULL;
	int i = 0;
	while (tab_raw[i].str)
	{
		t_token	*new_token = cpy_token(tab_raw[i]);
		if (!new_token)
			return (ft_dlstclear(&raw, free_token), \
					ft_printf(CR"inside create_raw_from_tab_raw()-->cpy_token()-->FAILED\n"CE), \
					NULL);
		t_dlist	*new_node = ft_dlstnew(new_token);
		if (!new_node)
			return (ft_dlstclear(&raw, free_token), \
					ft_printf(CR"inside create_raw_from_tab_raw()-->ft_dlstnew()-->FAILED\n"CE), \
					NULL);
		if (!ft_dlstadd_back(&raw, new_node))
			return (ft_dlstclear(&raw, free_token), \
					ft_printf(CR"%s-->ADD BACK node {%s} FAILED\n"CE, tab_raw[i].str, ((t_token *)new_node->content)->str), \
					NULL);
		//ft_printf(CV"%s-->ADD BACK node {%s} SUCCESS\n"CE, tab_raw[i].str, ((t_token *)new_node->content)->str);
		i++;
	}
	return (raw);
}

/*
 * print a tok_lst (t_dlist->content == t_token)
 */
int	print_raw(t_dlist *raw)
{
	t_dlist *act = raw;
	t_token	*act_tok;
	printf(CY);
	int tot = printf("raw=");
	while (act && act->content)
	{
		printf(CM);
		act_tok = ((t_token *)act->content);
		tot += printf("{");
		tot += print_t_token_type(act_tok->type);
		tot += printf(", %s, %d}-->", act_tok->str, act_tok->parenthesis);
		act = act->next;
	}
	tot += printf("NULL\n");
	printf(CE);
	return (tot);
}

/*
 * test(char **ev, t_token *tab_raw, char **res)
 * step0) print header
 * step1) build t_dlist *raw from tab_raw
 * step2) set_raw_type(act_node->raw) --> print
 * step3) create a dt from <ev>
 * step4) call ft=build_str_arr(dt, raw)
 * step5) compare ft=build_str_arr() VS <res>
 */
int	test(char **ev, t_token tab_raw[], char **res)
{
	//// -[ 	STEP 0: PRINT TEST HEADER ]-----------------------------------------
	//int print_sofar = printf("%s(dt, ", f_name);
	//print_sofar += print_tab_raw(tab_raw);
	//print_sofar += printf(")");
	//printntime(S3, LEN - print_sofar);
	//printf("\n");
	//print_tab_res(tab_res);
	//printf("\n");

	//// -[ 	STEP1: BUILD RAW FROM TAB_RAW ]-------------------------------------
	//t_dlist *raw = create_raw_from_tab_raw(tab_raw);
	//if (!raw)
	//	return (42);
	//print_raw(raw);
	//
	//// -[ STEP2: BUILD T_DATA ]-------------------------------------------------
	//t_data	*data = init_data(ev);
	//if (!data)
	//	return (ft_dlstclear(&raw, free_token), 42);
	//printf(CY"BEFORE data->env_lst=\n"CB"{\n");
	//fflush(stdout);
	//print_env_lst(data->env_lst);
	//printf("}\n"CE);
	//
	//
	//// -[ STEP3: CALL build_str_arr ]----------------------------------------
	//build_str_arr(&data, raw);
	//printf(CY"AFTER data->env_lst=\n"CB"{\n");
	//fflush(stdout);
	//print_env_lst(data->env_lst);
	//printf("}\n"CE);

	//// -[ STEP4: CHECK AFFECTATION ]--------------------------------------------
	//// Check that every tab_res t_env has been correctly add to data->env_lst
	//char	*key;
	//char	*val;
	//int i = 0;
	//while (tab_res[i].name && tab_res[i].value)
	//{
	//	t_list	*env_lst_node_found = get_env_lst_node_form_key(data->env_lst, tab_res[i].name);
	//	if (!env_lst_node_found)
	//		return (ft_printf(CR"act_env={%s,%s} NOT FOUND IN data->env_lst\n"CE, tab_res[i].name, tab_res[i].value), ft_dlstclear(&raw, free_token),free_data(&data), printntime(S3, LEN - 5), printf(FAIL), 1);
	//	key = ((t_env *)env_lst_node_found->content)->name;
	//	val = ((t_env *)env_lst_node_found->content)->value;
	//	if (strcmp(tab_res[i].name, key) || strcmp(tab_res[i].value, val))
	//		return (printf(CR"tab_res[%d]:{%s, %s}!=env_lst:{%s, %s}\n"CE, i, tab_res[i].name, tab_res[i].value, key, val), ft_dlstclear(&raw, free_token), free_data(&data), printntime(S3, LEN - 5), printf(FAIL), 1);
	//	i++;
	//}
	//return (ft_dlstclear(&raw, free_token),free_data(&data), printntime(S3, LEN - 5), printf(PASS), 0);
}

int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	(void) ev;
	int	nb_err = 0;

	/*
	 * A| No AFF. No expand, (no skip aff. mecanism)
	 *  A.1 No args: `ls`
	 *  A.2 Cmd with args: `echo toto tata titi tutu`
	 * B| No AFF. EXPAND, (no skip aff. mecanism)
	 *  B.1 No args: `'l's`
	 *  B.2 No args: `$var` [{var, "ls"}]
	 *  B.3 Cmd with args: `'e'$v0"o" v1=error "v1=$v1 v2=$v2" 'v1=$v1 v2=$v2'` [{v0,"ch"},{v1,toto},{v2,tata}]
	 * C| No AFF. EXPAND with cmd and arg in a var
	 *  C.1 not in quote=>re-split_by_spaces: `$cmd_arg "v1=$v1 v2=$v2" 'v1=$v1 v2=$v2'` [{cmd_arg,"echo \"arg 1\" 'arg 2'"},{v1,toto},{v2,tata}]
	 *  C.2 in quote                        : `"$cmd_arg" "v1=$v1 v2=$v2" 'v1=$v1 v2=$v2'` [{cmd_arg,"echo \"arg 1\" 'arg 2'"},{v1,toto},{v2,tata}]
	 *  C.3 in quote                        : `"$cmd_arg v1=$v1 v2=$v2" 'v1=$v1 v2=$v2'` [{cmd_arg,"echo \"arg 1\" 'arg 2'"},{v1,toto},{v2,tata}]
	 *  C.4 in quote                        : `'$cmd_arg' "v1=$v1 v2=$v2" 'v1=$v1 v2=$v2'` [{cmd_arg,"echo \"arg 1\" 'arg 2'"},{v1,toto},{v2,tata}]
	 */
	print_title("A| SIMPLE AFFECTATION ");

	print_subtitle("A.1| ADD AFFECTATION TO ENV_LST");
	char *ev_a1[]		= {"old_1=a","old2=",NULL};
	t_token tab_raw_a1[]= {{AFF,"new_1=val_1",0},{CMD,"ls",0},{0,0,0}};
	char *res_a1[]	= {"ls", NULL};
	nb_err += test(ev_a1, tab_raw_a1, res_a1);
	print_sep(S2);

	print_subtitle("A.2| UPDATE AFFECTATION IN ENV_LST");
	char *ev_a2[]		= {"v1=old_value_1","v2=old_value_2'",NULL};
	t_token tab_raw_a2[]= {{AFF,"v1=new_value_1",0},{AFF,"v2='new value 2'",0},{AFF,"v3=\"new value 3\"",0},{0,0,0}};
	t_env tab_res_a2[]	= {{"v1","new_value_1"},{"v2","new value 2"},{"v3","new value 3"},{0,0}};
	nb_err += test(ev_a2, tab_raw_a2, tab_res_a2);
	print_sep(S2);

	print_sep(S1);
	
	// =[ 	B | SPECIAL AFF ]===================================================
	print_title("B| SPECIAL AFFECTATION ");

	print_subtitle("B.1| ADD && UPDATE WITH MULTIPLE EQUALS");
	char *ev_b1[]		= {"v1=a","v2=b",NULL};
	t_token tab_raw_b1[]= {{AFF,"v1==",0},{AFF,"v2=E=e",0},{AFF,"v_3===e==",0},{0,0,0}};
	t_env tab_res_b1[]	= {{"v1","="},{"v2","E=e"},{"v_3","==e=="},{0,0}};
	nb_err += test(ev_b1, tab_raw_b1, tab_res_b1);
	print_sep(S2);

	print_subtitle("B.2| ADD && UPDATE WITH QUOTES");
	char *ev_b2[]		= {"v1=old_value_1","v2='old value 2'","v3=\"old value 3\"",NULL};
	t_token tab_raw_b2[]= {{AFF,"v1=new_value_1",0},{AFF,"v2='new value 2'",0},{AFF,"v3=\"new value 3\"",0},{0,0,0}};
	t_env tab_res_b2[]	= {{"v1","new_value_1"},{"v2","new value 2"},{"v3","new value 3"},{0,0}};
	nb_err += test(ev_b2, tab_raw_b2, tab_res_b2);
	print_sep(S2);
	
	// =[ 	C | CHAIN AFF ]=====================================================
	print_title("C| CHAIN AFFECTATION ");

	print_subtitle("C.1| ADD && UPDATE WITH DOLLARS SYMBOL-->SWAP");
	char *ev_c1[]		= {"v1=val2","v2=val1",NULL};
	t_token tab_raw_c1[]= {{AFF,"tmp=$v1",0},{AFF,"v1=$v2",0},{AFF,"v2=$tmp",0},{AFF,"tmp=",0},{0,0,0}};
	t_env tab_res_c1[]	= {{"tmp",""},{"v1","val1"},{"v2","val2"},{0,0}};
	nb_err += test(ev_c1, tab_raw_c1, tab_res_c1);
	print_sep(S2);

	print_sep(S1);
	return (nb_err);
}

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
	// -[ 	STEP 0: PRINT TEST HEADER ]-----------------------------------------
	int psf = printf("%s(dt, ", f_name);
	psf += print_tab_raw(tab_raw);
	psf += printf(")");
	printntime(S3, LEN - psf);
	printf(CY"\nres="CV);
	fflush(stdout);
	ft_print_str_array(res);
	printf(CY"\nev ="CM);
	fflush(stdout);
	ft_print_str_array(ev);
	printf("\n"CE);

	// -[ 	STEP1: BUILD RAW FROM TAB_RAW ]-------------------------------------
	t_dlist *raw = create_raw_from_tab_raw(tab_raw);
	if (!raw)
		return (42);
	print_raw(raw);
	
	// -[ 	STEP2: SET_RAW_TYPE(ACT_NODE->RAW) --> PRINT ]----------------------
	set_raw_type(raw);
	printf("AFTER set_raw_type():\n"CV);
	print_raw(raw);
	printf(CE);

	// -[ STEP3: CREATE A DT FROM <EV> ]----------------------------------------
	t_data	*data = init_data(ev);
	if (!data)
		return (ft_dlstclear(&raw, free_token), 42);
	printf(CY"env_lst=\n"CB"{\n"CM);
	fflush(stdout);
	print_env_lst(data->env_lst);
	printf(CB"}\n"CE);
	
	// -[ STEP4: CALL FT=BUILD_STR_ARR(DT, RAW) ]-------------------------------
	char **ft = build_str_arr(&data, raw);
	printf(CY"\nft =");
	fflush(stdout);
	ft_print_str_array(ft);

	return (ft_dlstclear(&raw, free_token),free_data(&data), ft_free_str_array(&ft),printntime(S3, LEN - 5), printf(PASS), 0);
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
	 *  ✅A.1 No args: `ls`
	 *  ✅A.2 Cmd with args: `echo toto tata titi tutu`
	 * B| No AFF. EXPAND, (no skip aff. mecanism)
	 *  B.1 No args: `'l's`
	 *  B.2 No args: `$var` [{var, "ls"}]
	 *  B.3 Cmd with args: `'e'$v0"o" v1=error "v1=$v1 v2=$v2" 'v1=$v1 v2=$v2'` [{v0,"ch"},{v1,toto},{v2,tata}]
	 * C| No AFF. EXPAND with cmd and arg in a var
	 *  C.1 not in quote=>re-split_by_spaces: `$cmd_arg "v1=$v1 v2=$v2" 'v1=$v1 v2=$v2'` [{cmd_arg,"echo \"arg 1\" 'arg 2'"},{v1,toto},{v2,tata}]
	 *  C.2 in quote                        : `"$cmd_arg" "v1=$v1 v2=$v2" 'v1=$v1 v2=$v2'` [{cmd_arg,"echo \"arg 1\" 'arg 2'"},{v1,toto},{v2,tata}]
	 *  C.3 in quote                        : `"$cmd_arg v1=$v1 v2=$v2" 'v1=$v1 v2=$v2'` [{cmd_arg,"echo \"arg 1\" 'arg 2'"},{v1,toto},{v2,tata}]
	 *  C.4 in quote                        : `'$cmd_arg' "v1=$v1 v2=$v2" 'v1=$v1 v2=$v2'` [{cmd_arg,"echo \"arg 1\" 'arg 2'"},{v1,toto},{v2,tata}]
	 *  TODO : DO NOT FORGET TO ADD THE OTHER TESTS (other combinaison+null *  cases)
	 */
	print_title("A| NO AFFECTATION AND NO EXPAND");

	print_subtitle("A.1| NO ARGS");
	char *ev_a1[]		= {"v1=val1","v2=val2",NULL};
	t_token tab_raw_a1[]= {{UNSET,"ls",0},{0,0,0}};
	char *res_a1[]	= {"ls", NULL};
	nb_err += test(ev_a1, tab_raw_a1, res_a1);
	print_sep(S2);

	print_subtitle("A.2| CMD WITH ARGS");
	char *ev_a2[]		= {"v1=val1","v2=val2",NULL};
	t_token tab_raw_a2[]= {{UNSET,"echo",0},{UNSET,"toto",0},{UNSET,"\"ta ta\"",0},{UNSET,"\'ti ti\'",0},{0,0,0}};
	char *res_a2[]	= {"echo","toto","ta ta","ti ti",0};
	nb_err += test(ev_a2, tab_raw_a2, res_a2);
	print_sep(S2);

	print_sep(S1);
	return (nb_err);
}

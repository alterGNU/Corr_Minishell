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

int	str_arr_cmp(char **ft, char **res)
{
	if (ft_get_len_str_arr(ft) != ft_get_len_str_arr(res))
		return (0);
	int	i = 0;
	while (ft[i] && res[i])
	{
		if (strcmp(ft[i], res[i]))
			return (0);
		i++;
	}
	return (1);
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
	ft_printf("\n"CE);

	// -[ 	STEP1: BUILD RAW FROM TAB_RAW ]-------------------------------------
	t_dlist *raw = create_raw_from_tab_raw(tab_raw);
	if (!raw)
		return (42);
	//print_raw(raw);
	
	// -[ STEP2: CREATE A DT FROM <EV> ]----------------------------------------
	t_data	*data = init_data(ev);
	if (!data)
		return (ft_dlstclear(&raw, free_token), 42);
	
	// -[ 	STEP3: SET_RAW_TYPE(ACT_NODE->RAW) --> PRINT ]----------------------
	set_raw_type(&data, raw);
	print_raw(raw);

	
	// -[ STEP4: CALL FT=BUILD_STR_ARR(DT, RAW) ]-------------------------------
	char **ft = build_str_arr(&data, raw);

	// -[ STEP5: COMPARE FT VS RES ] -------------------------------------------
	if (!str_arr_cmp(ft, res))
	{
		print_env_lst(data->env_lst);
		printf(ER" res != ft:\n");
		printf("res=");
		fflush(stdout);
		ft_print_str_array(res);
		printf("\nft =");
		fflush(stdout);
		ft_print_str_array(ft);
		printf("\n"CE);
		return (ft_dlstclear(&raw, free_token),free_data(&data), ft_free_str_array(&ft),printntime(S3, LEN - 5), printf(FAIL), 1);
	}
	return (ft_dlstclear(&raw, free_token),free_data(&data), ft_free_str_array(&ft),printntime(S3, LEN - 5), printf(PASS), 0);
}

int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	(void) ev;
	int	nb_err = 0;

	// -[ A| NO AFFECTATION AND NO EXPAND ]-------------------------------------
	print_title("A| NO AFFECTATION AND NO EXPAND");

	print_subtitle("A.1| NO ARGS");
	char *ev_a1[]		= {"v1=val1","v2=val2",NULL};
	t_token tab_raw_a1[]= {{UNSET,"ls",0},{0,0,0}};
	char *res_a1[]		= {"ls", NULL};
	nb_err += test(ev_a1, tab_raw_a1, res_a1);
	print_sep(S2);

	print_subtitle("A.2| CMD WITH ARGS");
	char *ev_a2[]		= {"v1=val1","v2=val2",NULL};
	t_token tab_raw_a2[]= {{UNSET,"echo",0},{UNSET,"toto",0},{UNSET,"\"ta ta\"",0},{UNSET,"\'ti ti\'",0},{0,0,0}};
	char *res_a2[]		= {"echo","toto","ta ta","ti ti",0};
	nb_err += test(ev_a2, tab_raw_a2, res_a2);
	print_sep(S2);

	print_sep(S1);
	
	// -[ B| NO AFF. EXPAND, (NO SKIP AFF. MECANISM) ]--------------------------
	print_title("B| No AFF. EXPAND, (no skip aff. mecanism)");

	print_subtitle("B.1| No args: `'e'$v1\"o\"`");
	char *ev_b1[]		= {"v1=ch",NULL};
	t_token tab_raw_b1[]= {{UNSET,"'e'$v1\"o\"",0},{UNSET,"toto",0},{0,0,0}};
	char *res_b1[]		= {"echo", "toto", NULL};
	nb_err += test(ev_b1, tab_raw_b1, res_b1);
	print_sep(S2);

	print_subtitle("B.2| No args: `'e'$v1$v2`");
	char *ev_b2[]		= {"v1=ch","v2=o",NULL};
	t_token tab_raw_b2[]= {{UNSET,"'e'$v1$v2",0},{UNSET,"t$v2.t$v2",0},{0,0,0}};
	char *res_b2[]		= {"echo", "to.to", NULL};
	nb_err += test(ev_b2, tab_raw_b2, res_b2);
	print_sep(S2);

	print_subtitle("B.3| No args: `'e'$v1$v2`");
	char *ev_b3[]		= {"v1=ch","v2=o",NULL};
	t_token tab_raw_b3[]= {{UNSET,"\"e$v1$v2\"",0},{UNSET,"\"t$v2.t$v2\"",0},{UNSET,"\'t$v2.t$v2\'",0},{0,0,0}};
	char *res_b3[]		= {"echo", "to.to", "t$v2.t$v2", NULL};
	nb_err += test(ev_b3, tab_raw_b3, res_b3);
	print_sep(S2);

	print_sep(S1);
	
	// -[ C| NO AFF. EXPAND WITH CMD AND ARG IN A VAR ]-------------------------
	print_title("C| No AFF. EXPAND, (no skip aff. mecanism)");

	print_subtitle("C.1| ... ");
	char *ev_c1[]		= {"v1=old_val1",NULL};
	t_token tab_raw_c1[]= {{UNSET,"v1=new_val1",0},{UNSET,"=$v1",0},{0,0,0}};
	char *res_c1[]		= {"=old_val1", NULL};
	nb_err += test(ev_c1, tab_raw_c1, res_c1);
	print_sep(S2);

	print_subtitle("C.2| ... ");
	char *ev_c2[]		= {"v1=echo toto",NULL};
	t_token tab_raw_c2[]= {{UNSET,"v1=new_val1",0},{UNSET,"v1=new_val2",0},{UNSET,"$v1",0},{0,0,0}};
	char *res_c2[]		= {"echo", "toto", NULL};
	nb_err += test(ev_c2, tab_raw_c2, res_c2);
	print_sep(S2);

	print_subtitle("C.3| ... ");
	char *ev_c3[]		= {"v1=echo toto",NULL};
	t_token tab_raw_c3[]= {{UNSET,"v1=new_val1",0},{UNSET,"v1=new_val2",0},{UNSET,"$v1",0},{UNSET,"$v1",0},{UNSET,"\"v1=$v1\"",0},{UNSET,"\'v1=$v1\'",0},{0,0,0}};
	char *res_c3[]		= {"echo", "toto", "echo", "toto", "v1=echo toto", "v1=$v1", NULL};
	nb_err += test(ev_c3, tab_raw_c3, res_c3);
	print_sep(S2);

	print_subtitle("C.4| ... ");
	char *ev_c4[]		= {"v1=\"'echo toto'\"", "v2='\"echo toto\"'", "v3=   echo   toto   tata   ", NULL};
	t_token tab_raw_c4[]= {{UNSET,"v1=new_val1",0},{UNSET,"v1=new_val2",0},{UNSET,"$v1",0},{UNSET,"$v2",0},{UNSET,"$v3",0},{0,0,0}};
	char *res_c4[]		= {"'echo toto'", "\"echo toto\"", "echo", "toto", "tata", NULL};
	nb_err += test(ev_c4, tab_raw_c4, res_c4);
	print_sep(S2);
	
	print_sep(S1);
	return (nb_err);
}

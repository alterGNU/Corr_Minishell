// =[ INCLUDE ]=================================================================
#include "minishell.h"    // build_tok_lst_split_by_quotes,build_tok_lst_split_by_spaces,build_tok_lst_split_by_operators,set_tok_lst_type
#include <string.h>       // strcmp
#include <stdio.h>        // printf, fflush
						  // ⚠️  Some of minishell print fun. use ~write=>fflush
						  // ⚠️  Depends on libft/array/ft_print_str_array()
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "builtin_unset"
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

/*
 * print a char array with syntaxique coloration
 */
int	print_char_array(char *char_arr[])
{
	int		i;
	int		psf;

	if (!char_arr || !char_arr[0])
		return (printf(CY"["CM"NULL"CY"]"E), 6);
	printf(CY);
	psf = printf("[");
	i = 0;
	while (char_arr[i])
	{
		printf(CY"\""CM);
		psf += 2 + printf("%s", char_arr[i]);
		printf(CY"\"");
		psf += printf(", ");
		printf(CY);
		i++;
	}
	printf(CM);
	psf += printf("NULL");
	printf(CY);
	psf += printf("]");
	printf(E);
	return (psf);
}

int	print_env_array(t_env env_lst[])
{
	int		i;
	int		psf;

	if (!env_lst[0].name || !env_lst[0].value)
		return (printf(CY"["CM"NULL"CY"]"E), 6);
	printf(CY);
	psf = printf("[");
	i = 0;
	while (env_lst[i].name && env_lst[i].value)
	{
		printf(CM);
		psf += 2 + printf("{%s, %s}", env_lst[i].name, env_lst[i].value);
		printf(CY);
		psf += printf(", ");
		printf(CY);
		i++;
	}
	printf(CM);
	psf += printf("NULL");
	printf(CY);
	psf += printf("]");
	printf(E);
	return (psf);
}

int	print_env_lst_oneline(t_list *env_lst)
{
	int	psf;
	t_list	*act;
	t_env	*act_env;

	if (!env_lst)
		return (printf(CM"NULL"E), 4);
	psf = 0;
	act = env_lst;
	while (act)
	{
		act_env = (t_env *)act->content;
		if (!act_env)
			printf(CR"[missing content in env_lst]"E);
		printf(CY);
		psf += printf("{");
		printf(CM);
		psf += printf("%s", act_env->name);
		printf(CY);
		psf += printf(", ");
		printf(CM);
		psf += printf("%s", act_env->value);
		printf(CY);
		psf += printf("}->");
		act = act->next;
	}
	printf(CM);
	psf += printf("NULL");
	printf(E);
	return (psf);
}

/*
 * test(char **ev_src, t_env **env_lst, char **tab_str, char **ev_res, int res)
 * ✅step0)		print cases/header
 * ✅step1.1)	build data->ev from <ev_src>
 * ✅step1.2)	build data->env_lst from <env_lst>
 * ✅step2)		ft = builtin_unset(data, <tab_str>)
 * ✅step3.1)	check ft == res
 * ✅step3.2)	check unset done in data->ev		:for each char *key in str_arr		->NOT FOUND in data->ev
 * ✅step3.3)	check ev_res == data->ev      		:for each char *key in ev_res		->FOUND in data->ev
 * ✅step3.4) 	check unset done in data->env_lst	:for each char *key in str_arr		->NOT FOUND in data->env_lst
 * ✅step3.5) 	check env_lst_res == data->env_lst 	:for each char *key in env_lst_res	->FOUND in data->env_lst
 */
int test(char *ev_src[], char *env_lst_src[], char *str_arr[], char *ev_res[], t_env env_lst_res[], int res_value)
{
	// -[ 	STEP 0: PRINT TEST HEADER ]-----------------------------------------
	int print_sofar = printf("%s(data, ", f_name);
	print_sofar += print_char_array(str_arr);
	print_sofar += printf(")=[%d]", res_value);
	printntime(S3, LEN - print_sofar);
	printf(CB"\nchar **ev_src     = ");
	print_char_array(ev_src);
	printf(CB"\nchar **env_lst_src= ");
	print_char_array(env_lst_src);
	printf(CV"\nchar **ev_res     = ");
	print_char_array(ev_res);
	printf(CV"\nchar **env_lst_res= ");
	print_env_array(env_lst_res);
	printf("\n"E);

	// -[ STEP1:	BUILD DT->EV FROM <EV> ]------------------------------------
	t_data	*data = (t_data *)ft_calloc(1, sizeof(t_data));
	if (!data)
		return(printf(ER"init_data():!ft_calloc()"E), 42);
	data->ev = build_ev_from_envp(ev_src);
	if (!data->ev)
		return(free_data(&data), printf(ER"init_data():!build_ev_from_envp()"E), 42);
	data->env_lst = build_env_lst(env_lst_src);
	if (!data->env_lst)
		return(free_data(&data), printf(ER"init_data():!build_env_lst()"E), 42);

	printf("\n"CT"BEFORE"E"\n");
	printf(CY"data->ev     =");
	print_char_array(data->ev);
	printf(CY"\ndata->env_lst="E);
	print_env_lst_oneline(data->env_lst);
	printf("\n"E);
	
	// -[ STEP2)	FT = BUILTIN_UNSET(DATA, <TAB_STR>) ]-----------------------
	int ft = builtin_unset(&data, str_arr);
	printf("\n"CT"CALL %s()=[%d]"E"\n", f_name, ft);

	printf("\n"CT"AFTER"E"\n");
	printf(CY"data->ev     =");
	print_char_array(data->ev);
	printf(CY"\ndata->env_lst="E);
	print_env_lst_oneline(data->env_lst);
	printf("\n"E);

	// -[ STEP3.1) CHECKS FT != RES]--------------------------------------------
	if (ft != res_value)
		return (free_data(&data), printf(CR"RETURN VALUE DIFF. :ft:%d != %d:res_value\n"E, ft, res_value), printntime(S3, LEN - 5), printf(FAIL), 1);
	//printf(CV"\nCHECK 3.1 ");
	//printntime(S3, LEN - 15);
	//printf(PASS);

	// -[ STEP3.2) CHECK UNSET DONE IN DATA->EV ] -----------------------------
	// FOR EACH CHAR *KEY IN STR_ARR		->NOT FOUND IN DATA->EV ]
	int		i,j;
	char	*key;
	i = 0;
	while (str_arr[++i])
	{
		j = -1;
		while (data->ev[++j])
		{
			if (!data->ev[j])
				return (free_data(&data), printf(CR"PANIC\n"E), printntime(S3, LEN - 5), printf(FAIL), 42);
			key = get_aff_key(data->ev[j]);
			//printf("%s VS (%s ~ %s)\n", str_arr[i], data->ev[j], key);
			if (!key)
				return (free_data(&data), 42);
			if (!strcmp(str_arr[i], key))
			{
				printf("INSIDE-->return\n");
				return (ft_free((void **)&key), printf(CR"`UNSET %s`DID NOT WORK SINCE <%s> FOUND IN data->ev\n"E, str_arr[i], data->ev[j]), free_data(&data), printntime(S3, LEN - 5), printf(FAIL), 1);
			}
			ft_free((void **)&key);
		}
	}
	//printf(CV"CHECK 3.2 ");
	//printntime(S3, LEN - 15);
	//printf(PASS);

	// -[ STEP3.3) CHECK EV_RES == DATA->EV ]-----------------------------------
	// for each char *key in ev_res		->FOUND in data->ev
	i = -1;
	while (ev_res[++i])
	{
		int found_in_ev = 0;
		int j = -1;
		while (data->ev[++j] && !found_in_ev)
		{
			//printf("%s VS %s\n", ev_res[i], data->ev[j]);
			if (!strcmp(ev_res[i], data->ev[j]))
				found_in_ev = 1;
		}
		if (!found_in_ev)
			return (free_data(&data), printf(CR"in RES:<%s> NOT FOUND IN data->ev\n"E, ev_res[i]), printntime(S3, LEN - 5), printf(FAIL), 1);
	}
	//printf(CV"CHECK 3.3 ");
	//printntime(S3, LEN - 15);
	//printf(PASS);
	
	// -[ STEP3.4) CHECK UNSET DONE IN DATA->ENV_LST ] -----------------------------
	// FOR EACH CHAR *KEY IN STR_ARR		->NOT FOUND IN DATA->ENV_LST ]
	t_list *act;
	char	*act_name;
	i = 0;
	while (str_arr[++i])
	{
		act = data->env_lst;
		while (act)
		{
			act_name = ((t_env *)act->content)->name;
			//printf("%s VS %s\n", str_arr[i], act_name);
			if (!strcmp(str_arr[i], act_name))
			{
				printf("INSIDE-->return\n");
				return (printf(CR"`UNSET %s`DID NOT WORK SINCE <{%s, %s}> FOUND IN data->env_lst\n"E, str_arr[i], act_name, ((t_env *)act->content)->value), free_data(&data), printntime(S3, LEN - 5), printf(FAIL), 1);
			}
			act = act->next;
		}
	}
	//printf(CV"CHECK 3.4 ");
	//printntime(S3, LEN - 15);
	//printf(PASS);

	// -[ STEP3.5) CHECK EV_RES == DATA->ENV_LST ]-----------------------------------
    // for each char *key in env_lst_res	->FOUND in data->env_lst
	i = 0;
	while (env_lst_res[i].name || env_lst_res[i].value)
	{
		act = data->env_lst;
		int	found_in_env_lst = 0;
		while (act && !found_in_env_lst)
		{
			act_name = ((t_env *)act->content)->name;
			//printf("%s VS %s\n",env_lst_res[i].name, act_name);
			if (!strcmp(env_lst_res[i].name, act_name))
				found_in_env_lst = 1;
			act = act->next;
		}
		if (!found_in_env_lst)
			return (free_data(&data), printf(CR"in RES:<%s> NOT FOUND IN data->env_lst\n"E, env_lst_res[i].name), printntime(S3, LEN - 5), printf(FAIL), 1);
		i++;
	}
	//printf(CV"CHECK 3.3 ");
	//printntime(S3, LEN - 15);
	//printf(PASS);
	return (free_data(&data), printntime(S3, LEN - 5), printf(PASS), 0);
}

int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	(void) ev;
	int	nb_err = 0;

	/*
	 * A | UNSET ONLY in dt->ev
	 *  ✅- A.1 | Unset one valid FOUND in ev
	 *  ❌- A.2 | Unset one valid NOT FOUND in ev
	 *  ❌- A.3 | Unset one unvalid in ev
	 *  ❌- A.4 | Unset Multiple valid and unvalid
	 * B | UNSET ONLY in dt->env_lst
	 *  ❌- B.1 | Unset one valid FOUND in env_lst
	 *  ❌- B.2 | Unset one valid NOT FOUND in env_lst
	 *  ❌- B.3 | Unset one unvalid in env_lst
	 *  ❌- B.4 | Unset Multiple valid and unvalid
	 * C | UNSET in dt->ev AND in dt->env_lst
	 *  ❌- C.1 | Unset one valid FOUND in ev AND env_lst 
	 *  ❌- C.2 | Unset one valid NOT FOUND in ev AND env_lst
	 *  ❌- C.3 | Unset one unvalid in ev AND env_lst
	 *  ❌- C.4 | Unset Multiple valid and unvalid
	 */
	
	// =[ A | UNSET ONLY IN DT->EV ]============================================
	print_title("A | UNSET ONLY in dt->ev");

	print_subtitle("A.1| Unset ONE VALID FOUND in ev");
	char *ev_src_a1[]		= {"k1=kv1","k2=to_unset",NULL};
	char *env_lst_src_a1[]	= {"v1=v1",NULL};
	char *tab_str_a1[]		= {"unset","k2",NULL};
	char *ev_res_a1[]		= {"k1=kv1",NULL};
	t_env env_lst_res_a1[]	= {{"v1", "v1"},{0,0}};
	nb_err += test(ev_src_a1, env_lst_src_a1, tab_str_a1, ev_res_a1, env_lst_res_a1, 0);
	print_sep(S2);

	print_subtitle("A.2| Unset ONE VALID NOT FOUND in ev");
	char *ev_src_a2[]		= {"k1=kv1","k2=kv2",NULL};
	char *env_lst_src_a2[]	= {"v1=v1",NULL};
	char *tab_str_a2[]		= {"unset","k3",NULL};
	char *ev_res_a2[]		= {"k1=kv1","k2=kv2",NULL};
	t_env env_lst_res_a2[]	= {{"v1", "v1"},{0,0}};
	nb_err += test(ev_src_a2, env_lst_src_a2, tab_str_a2, ev_res_a2, env_lst_res_a2, 0);
	print_sep(S2);

	print_subtitle("A.3| Unset ONE UNVALID");
	char *ev_src_a3[]		= {"k1=kv1","k2=kv2",NULL};
	char *env_lst_src_a3[]	= {"v1=v1",NULL};
	char *tab_str_a3[]		= {"unset","1_toto",NULL};
	char *ev_res_a3[]		= {"k1=kv1","k2=kv2",NULL};
	t_env env_lst_res_a3[]	= {{"v1", "v1"},{0,0}};
	nb_err += test(ev_src_a3, env_lst_src_a3, tab_str_a3, ev_res_a3, env_lst_res_a3, 1);
	print_sep(S2);
	
	print_subtitle("A.4| Unset Multiple valid and unvalid");
	char *ev_src_a4[]		= {"k1=kv1","k2=kv2","k3=kv3","k4=kv4","k5=kv5", NULL};
	char *env_lst_src_a4[]	= {"v1=v1", "v2=v2", NULL};
	char *tab_str_a4[]		= {"unset", "k1", "k2=", "k3", "k", "","1_toto","=", "k5", NULL};
	char *ev_res_a4[]		= {"k2=kv2","k4=kv4",NULL};
	t_env env_lst_res_a4[]	= {{"v1", "v1"}, {"v2", "v2"}, {0,0}};
	nb_err += test(ev_src_a4, env_lst_src_a4, tab_str_a4, ev_res_a4, env_lst_res_a4, 4);
	print_sep(S2);

	print_sep(S1);

	// =[ B | UNSET ONLY IN DT->ENV_LST ]============================================
	print_title("B | UNSET ONLY in dt->env_lst");

	print_subtitle("B.1| Unset ONE VALID FOUND in env_lst");
	char *ev_src_b1[]		= {"v1=v1",NULL};
	char *env_lst_src_b1[]	= {"k1=kv1","k2=to_unset",NULL};
	char *tab_str_b1[]		= {"unset","k2",NULL};
	char *ev_res_b1[]		= {"v1=v1",NULL};
	t_env env_lst_res_b1[]	= {{"k1", "kv1"},{0,0}};
	nb_err += test(ev_src_b1, env_lst_src_b1, tab_str_b1, ev_res_b1, env_lst_res_b1, 0);
	print_sep(S2);

	print_subtitle("B.2| Unset ONE VALID NOT FOUND in env_lst");
	char *ev_src_b2[] 		= {"v1=v1",NULL};
	char *env_lst_src_b2[]	= {"k1=kv1","k2=kv2",NULL};
	char *tab_str_b2[]		= {"unset","k3",NULL};
	char *ev_res_b2[]		= {"v1=v1",NULL};
	t_env env_lst_res_b2[]	= {{"k1", "kv1"},{"k2", "kv2"},{0,0}};
	nb_err += test(ev_src_b2, env_lst_src_b2, tab_str_b2, ev_res_b2, env_lst_res_b2, 0);
	print_sep(S2);

	print_subtitle("B.3| Unset ONE UNVALID");
	char *ev_src_b3[]		= {"v1=v1",NULL};
	char *env_lst_src_b3[]	= {"k1=kv1","k2=kv2",NULL};
	char *tab_str_b3[]		= {"unset","1_toto",NULL};
	char *ev_res_b3[]		= {"v1=v1",NULL};
	t_env env_lst_res_b3[]	= {{"k1", "v1"},{"k2", "kv2"},{0,0}};
	nb_err += test(ev_src_b3, env_lst_src_b3, tab_str_b3, ev_res_b3, env_lst_res_b3, 1);
	print_sep(S2);
	
	print_subtitle("B.4| Unset Multiple valid and unvalid");
	char *ev_src_b4[]		= {"v1=v1", "v2=v2", NULL};
	char *env_lst_src_b4[]	= {"k1=kv1","k2=kv2","k3=kv3","k4=kv4","k5=kv5", NULL};
	char *tab_str_b4[]		= {"unset", "k1", "k2=", "k3", "k", "","1_toto","=", "k5", NULL};
	char *ev_res_b4[]		= {"v1=v1","v2=v2",NULL};
	t_env env_lst_res_b4[]	= {{"k2", "kv2"}, {"k4", "kv4"}, {0,0}};
	nb_err += test(ev_src_b4, env_lst_src_b4, tab_str_b4, ev_res_b4, env_lst_res_b4, 4);
	print_sep(S2);

	print_sep(S1);

	print_title("C | UNSET in dt->ev AND dt->env_lst");

	print_subtitle("C.1| Unset ONE VALID FOUND in ev");
	char *src_c1[]			= {"k1=kv1","k2=to_unset",NULL};
	char *tab_str_c1[]		= {"unset","k2",NULL};
	char *ev_res_c1[]		= {"k1=kv1",NULL};
	t_env env_lst_res_c1[]	= {{"k1", "kv1"},{0,0}};
	nb_err += test(src_c1, src_c1, tab_str_c1, ev_res_c1, env_lst_res_c1, 0);
	print_sep(S2);

	print_subtitle("C.2| Unset ONE VALID NOT FOUND in ev");
	char *src_c2[]			= {"k1=kv1","k2=kv2",NULL};
	char *tab_str_c2[]		= {"unset","k3",NULL};
	char *ev_res_c2[]		= {"k1=kv1","k2=kv2",NULL};
	t_env env_lst_res_c2[]	= {{"k1", "kv1"},{"k2", "kv2"},{0,0}};
	nb_err += test(src_c2, src_c2, tab_str_c2, ev_res_c2, env_lst_res_c2, 0);
	print_sep(S2);

	print_subtitle("C.3| Unset ONE UNVALID");
	char *src_c3[]			= {"k1=kv1","k2=kv2",NULL};
	char *tab_str_c3[]		= {"unset","1_toto",NULL};
	char *ev_res_c3[]		= {"k1=kv1","k2=kv2",NULL};
	t_env env_lst_res_c3[]	= {{"k1", "kv1"},{"k2", "kv2"},{0,0}};
	nb_err += test(src_c3, src_c3, tab_str_c3, ev_res_c3, env_lst_res_c3, 1);
	print_sep(S2);
	
	print_subtitle("C.4| Unset Multiple valid and unvalid");
	char *src_c4[]			= {"k1=kv1","k2=kv2","k3=kv3","k4=","k5=kv5","k6=", NULL};
	char *tab_str_c4[]		= {"unset", "k1", "k2=", "k3", "k", "","1_toto","=", "k5","k6", NULL};
	char *ev_res_c4[]		= {"k2=kv2","k4=",NULL};
	t_env env_lst_res_c4[]	= {{"k2", "kv2"}, {"k4", ""}, {0,0}};
	nb_err += test(src_c4, src_c4, tab_str_c4, ev_res_c4, env_lst_res_c4, 4);
	print_sep(S2);

	print_sep(S1);

	return (nb_err);
}

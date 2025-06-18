// =[ INCLUDE ]=================================================================
#include "minishell.h"    // build_tok_lst_split_by_quotes,build_tok_lst_split_by_spaces,build_tok_lst_split_by_operators,set_tok_lst_type
#include <string.h>       // strcmp
#include <stdio.h>        // printf, fflush
						  // ⚠️  Some of minishell print fun. use ~write=>fflush
						  // ⚠️  Depends on libft/array/ft_print_str_array()
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "builtin_unset"
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

/*
 * print a char array with syntaxique coloration
 */
int	print_char_array(char *char_arr[])
{
	int		i;
	int		psf;

	if (!char_arr || !char_arr[0])
		return (printf(CY"["CM"NULL"CY"]"CE), 6);
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
	printf(CE);
	return (psf);
}

int	print_env_array(t_env env_lst[])
{
	int		i;
	int		psf;

	if (!env_lst[0].name || !env_lst[0].value)
		return (printf(CY"["CM"NULL"CY"]"CE), 6);
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
	printf(CE);
	return (psf);
}

int	print_env_lst_oneline(t_list *env_lst)
{
	int	psf;
	t_list	*act;
	t_env	*act_env;

	if (!env_lst)
		return (printf(CM"NULL"CE), 4);
	act = env_lst;
	while (act)
	{
		act_env = (t_env *)act->content;
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
	printf(CE);
	return (psf);
}

/*
 * test(char **ev_src, t_env **env_lst, char **tab_str, char **ev_res, int res)
 * ✅step0)		print cases/header
 * ✅step1.1)	build data->ev from <ev_src>
 * ✅step1.2)	build data->env_lst from <env_lst>
 * ✅step2)		ft = builtin_unset(data, <tab_str>)
 * ✅step3.1)	check ft == res
 * ❌step3.2)	check unset done in data->ev		:for each char *key in str_arr		->NOT FOUND in data->ev
 * ❌step3.3)	check ev_res == data->ev      		:for each char *key in ev_res		->FOUND in data->ev
 * ❌step3.4) 	check unset done in data->env_lst	:for each char *key in str_arr		->NOT FOUND in data->env_lst
 * ❌step3.5) 	check env_lst_res == data->env_lst 	:for each char *key in env_lst_res	->FOUND in data->env_lst
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
	printf("\n"CE);

	// -[ STEP1:	BUILD DT->EV FROM <EV> ]------------------------------------
	t_data	*data = (t_data *)ft_calloc(sizeof(t_data), 1);
	if (!data)
		return(printf(ER"init_data():!ft_calloc()"CE), 42);
	data->ev = build_ev_from_envp(ev_src);
	if (!data->ev)
		return(free_data(&data), printf(ER"init_data():!build_ev_from_envp()"CE), 42);
	data->env_lst = build_env_lst(env_lst_src);
	if (!data->env_lst)
		return(free_data(&data), printf(ER"init_data():!build_env_lst()"CE), 42);

	printf("\n"CT"BEFORE"CE"\n");
	printf(CY"data->ev     =");
	print_char_array(data->ev);
	printf(CY"\ndata->env_lst="CE);
	print_env_lst_oneline(data->env_lst);
	printf("\n"CE);
	
	// -[ STEP2)	FT = BUILTIN_UNSET(DATA, <TAB_STR>) ]-----------------------
	int ft = builtin_unset(&data, str_arr);
	printf("\n"CT"CALL %s()=[%d]"CE"\n", f_name, ft);

	printf("\n"CT"AFTER"CE"\n");
	printf(CY"data->ev     =");
	print_char_array(data->ev);
	printf(CY"\ndata->env_lst="CE);
	print_env_lst_oneline(data->env_lst);
	printf("\n"CE);
	return (0); // TODO remove

	// -[ STEP3.1) CHECKS FT != RES]--------------------------------------------
	if (ft != res_value)
		return (free_data(&data), printf(CR"RETURN VALUE DIFF. :ft:%d != %d:res_value\n"CE, ft, res_value), printntime(S3, LEN - 5), printf(FAIL), 1);
	printf(CV"CHECK 3.1 ");
	printntime(S3, LEN - 10);
	printf(PASS);

	// -[ STEP3.2) CHECK UNSET DONE IN DATA->EV ] -----------------------------
	// FOR EACH CHAR *KEY IN STR_ARR		->NOT FOUND IN DATA->EV ]
	int		i,j;
	char	*key;
	i = -1;
	while (str_arr[++i])
	{
		j = -1;
		while (data->ev[++j])
		{
			key = get_aff_key(data->ev[j]);
			printf("%s VS (%s ~ %s)\n", str_arr[i], data->ev[j], key);
			if (!key)
				return (free_data(&data), 42);
			if (!strcmp(str_arr[i], key))
			{
				printf("INSIDE-->return\n");
				return (free_data(&data), printf(CR"`UNSET %s`DID NOT WORK SINCE <%s> FOUND IN data->ev\n"CE, str_arr[i], data->ev[j]), free(key), printntime(S3, LEN - 5), printf(FAIL), 1);
			}
			free(key);
		}
	}
	printf(CV"CHECK 3.2 ");
	printntime(S3, LEN - 10);
	printf(PASS);
	return (free_data(&data), printntime(S3, LEN - 5), printf(PASS), 0);

	//// -[ STEP3.3) CHECK EV_RES == DATA->EV ]-----------------------------------
	//// for each char *key in ev_res		->FOUND in data->ev
	//i = -1;
	//while (ev_res[++i])
	//{
	//	int found_in_ev = 0;
	//	int j = -1;
	//	while (data->ev[++j] && !found_in_ev)
	//	{
	//		char *key = get_aff_key(data->ev[j]);
	//		if (!key)
	//			return (free_data(&data), 42);
	//		if (!strcmp(str_arr[i], key))
	//			found_in_ev = 1;
	//		ft_free((void **)&key);
	//	}
	//	if (!found_in_ev)
	//		return (free_data(&data), printf(CR"in RES:<%s> NOT FOUND IN data->ev\n"CE, ev_res[i]), printntime(S3, LEN - 5), printf(FAIL), 1);
	//}
	//return (free_data(&data), printntime(S3, LEN - 5), printf(PASS), 0);
	
	//int	j = -1;
	//while (ev_res[++j])
	//{
	//	// step 3.1: compare with dt->ev[k]
	//	int ev_found = 0;
	//	int k = -1;
	//	while (data->ev[++k] && !ev_found)
	//	{
	//		if (!strcmp(ev_res[j], data->ev[k]))
	//			ev_found++;
	//	}
	//	if (!ev_found)
	//		return (free_data(&data), printf(CR"ev_res[%d]=<%s> NOT FOUND IN data->ev\n"CE, j, ev_res[j]), printntime(S3, LEN - 5), printf(FAIL), 1);
	//	// step 3.2: compare with dt->env_lst
	//	int env_lst_found = 0;
	//	char *act_res_key = get_aff_key(ev_res[j]);
	//	if (!act_res_key)
	//		return (free_data(&data), printf(CR"get_aff_key()->!malloc failed\n"CE), printntime(S3, LEN - 5), printf(FAIL), 42);
	//	t_list *act = data->env_lst;
	//	while (act && !env_lst_found)
	//	{
	//		char *act_key = ((t_env *)act->content)->name;
	//		if (!strcmp(act_res_key, act_key))
	//			env_lst_found++;
	//		act = act->next;
	//	}
	//	if (!env_lst_found)
	//		return (ft_free((void **)&act_res_key), free_data(&data), printf(CR"ev_res[%d]=<%s> NOT FOUND IN data->env_lst\n"CE, j, ev_res[j]), printntime(S3, LEN - 5), printf(FAIL), 1);
	//	ft_free((void **)&act_res_key);
	//}
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
	 *  - A.1 | Unset one valid FOUND in ev
	 *  - A.2 | Unset one valid NOT FOUND in ev
	 *  - A.3 | Unset one unvalid in ev
	 *  - A.4 | Unset Multiple valid and unvalid
	 * B | UNSET ONLY in dt->env_lst
	 *  - B.1 | Unset one valid FOUND in env_lst
	 *  - B.2 | Unset one valid NOT FOUND in env_lst
	 *  - B.3 | Unset one unvalid in env_lst
	 *  - B.4 | Unset Multiple valid and unvalid
	 * C | UNSET in dt->ev AND in dt->env_lst
	 *  - C.1 | Unset one valid FOUND in ev AND env_lst 
	 *  - C.2 | Unset one valid NOT FOUND in ev AND env_lst
	 *  - C.3 | Unset one unvalid in ev AND env_lst
	 *  - C.4 | Unset Multiple valid and unvalid
	 */
	
	// =[ A | UNSET ONLY IN DT->EV ]============================================
	print_title("A | UNSET ONLY in dt->ev");

	print_subtitle("A.1| Unset ONE VALID FOUND in ev");
	char *ev_src_a1[]		= {"key=value","old_1=oldvalue1",NULL};
	char *env_lst_src_a1[]	= {"v1=val1",NULL};
	char *tab_str_a1[]		= {"unset","old_1",NULL};
	char *ev_res_a1[]		= {"key=value",NULL};
	t_env env_lst_res_a1[]	= {{"v1", "val1"},{0,0}};
	nb_err += test(ev_src_a1, env_lst_src_a1, tab_str_a1, ev_res_a1, env_lst_res_a1, 0);
	print_sep(S2);

	print_sep(S1);

	//print_subtitle("A.2| UN-VALID EXP WITH ADD AND UPDATE");
	//char *ev_a2[]		= {"key=value","old_1=oldvalue1","old2=","old_3=old_value_3",NULL};
	//char *tab_str_a2[]	= {"unset","=","new_1=val_1","=tata","new2=","","old_1=newval1","super","old2=new_val2","1un.valid=unvalid","old_3=",NULL};
	//char *ev_res_a2[]	= {"key=value","new_1=val_1","new2=","old_1=newval1","old2=new_val2","old_3=",NULL};
	//nb_err += test(ev_a2, tab_str_a2, ev_res_a2, 1);
	//print_sep(S2);
	//print_sep(S1);
	//
	//print_title("B| CHECK PROTECTED KEYS ");

	//print_subtitle("B.1| CHECK UNDERSCORE");
	//char *ev_b1[]		= {"_=old_underscore_value","_old_1=oldvalue1","old2=","old_3=old_value_3",NULL};
	//char *tab_str_b1[]	= {"unset","new_1=val_1","=unvalid","new2=","_old_1=newval1","_=new_undescore_value","old2=new_val2","old_3=",NULL};
	//char *ev_res_b1[]	= {"_=old_underscore_value","new_1=val_1","new2=","_old_1=newval1","old2=new_val2","old_3=",NULL};
	//nb_err += test(ev_b1, tab_str_b1, ev_res_b1, 1);
	//print_sep(S2);
	return (nb_err);
}

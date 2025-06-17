// =[ INCLUDE ]=================================================================
#include "minishell.h"    // build_tok_lst_split_by_quotes,build_tok_lst_split_by_spaces,build_tok_lst_split_by_operators,set_tok_lst_type
#include <string.h>       // strcmp
#include <stdio.h>        // printf, fflush
						  // ⚠️  Some of minishell print fun. use ~write=>fflush
						  // ⚠️  Depends on libft/array/ft_print_str_array()
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "builtin_export"
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

	printf(CY);
	psf = printf("[");
	i = 0;
	while (char_arr[i])
	{
		printf(CY"\""CM);
		psf += 2 + printf("%s", char_arr[i]);
		printf(CY"\"");
		if (char_arr[i + 1])
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
int	print_tab_res(char *tab_res[])
{
	int		i;
	int		psf;

	printf(CY);
	psf = printf("tab_res=[");
	i = 0;
	while (tab_res[i])
	{
		printf(CY"\""CM);
		psf += 2 + printf("%s", tab_res[i]);
		printf(CY"\"");
		if (tab_res[i+1])
			psf += printf(", ");
		printf(CY);
		i++;
	}
	psf += printf("]");
	printf(CE);
	return (psf);
}

/*
 * test(char **ev, char *str_arr[], char *tab_res)
 * step1) create a dt from <char **ev>
 * step2) call builtin_export(dt, *str_arr[])
 * step3.1) check export done for each char *aff in tab_res found in dt->ev
 * step3.2) check export done for each char *aff in tab_res found in dt->env_lst
 */
int	test(char **ev, char *str_arr[], char *tab_res[], int res_value)
{
	if (!ev || !*ev)
		printf("OK\n");
	// -[ 	STEP 0: PRINT TEST HEADER ]-----------------------------------------
	int print_sofar = printf("%s(dt, ", f_name);
	print_sofar += print_char_array(str_arr);
	print_sofar += printf(")");
	printntime(S3, LEN - print_sofar);
	printf("\n");
	print_tab_res(tab_res);
	printf("\n");

	// -[ 	STEP 1: BUILD DATA FROM EV ]----------------------------------------
	t_data	*data = init_data(ev);
	if (!data)
		return (ft_printf(CR"MALLOC FAILLED\n"CE), printntime(S3, LEN - 5), printf(FAIL), 42);
	printf(CY"BEFORE data->ev     ="CB);
	print_sofar += print_char_array(data->ev);
	printf(CY"\nBEFORE data->env_lst=\n"CB"{\n");
	fflush(stdout);
	print_env_lst(data->env_lst);
	printf("}\n"CE);
	
	// -[ STEP 2 : CALL builtin_export ]----------------------------------------
	int ft = builtin_export(&data, str_arr);
	printf(CY"AFTER ft=%d\nAFTER  data->ev     ="CB, ft);
	print_sofar += print_char_array(data->ev);
	printf(CY"\nAFTER  data->env_lst=\n"CB"{\n");
	fflush(stdout);
	print_env_lst(data->env_lst);
	printf("}\n"CE);

	// -[ STEP 3 : COMPARE WITH RESULT ]----------------------------------------

	if (ft != res_value)
		return (free_data(&data), ft_printf(CR"RETURN VALUE DIFF. :ft:%d != %d:res_value\n"CE, ft, res_value), printntime(S3, LEN - 5), printf(FAIL), 1);
	int	j = -1;
	while (tab_res[++j])
	{
		// step 3.1: compare with dt->ev[k]
		int ev_found = 0;
		int k = -1;
		while (data->ev[++k] && !ev_found)
		{
			if (!strcmp(tab_res[j], data->ev[k]))
				ev_found++;
		}
		if (!ev_found)
			return (free_data(&data), ft_printf(CR"tab_res[%d]=<%s> NOT FOUND IN data->ev\n"CE, j, tab_res[j]), printntime(S3, LEN - 5), printf(FAIL), 1);
		// step 3.2: compare with dt->env_lst
		int env_lst_found = 0;
		char *act_res_key = get_aff_key(tab_res[j]);
		if (!act_res_key)
			return (free_data(&data), ft_printf(CR"get_aff_key()->!malloc failed\n"CE), printntime(S3, LEN - 5), printf(FAIL), 42);
		t_list *act = data->env_lst;
		while (act && !env_lst_found)
		{
			char *act_key = ((t_env *)act->content)->name;
			if (!strcmp(act_res_key, act_key))
				env_lst_found++;
			act = act->next;
		}
		if (!env_lst_found)
			return (ft_free((void **)&act_res_key), free_data(&data), ft_printf(CR"tab_res[%d]=<%s> NOT FOUND IN data->env_lst\n"CE, j, tab_res[j]), printntime(S3, LEN - 5), printf(FAIL), 1);
		ft_free((void **)&act_res_key);
	}
	return (free_data(&data), printntime(S3, LEN - 5), printf(PASS), 0);
}

int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	(void) ev;
	int	nb_err = 0;

	// =[ 	A | SIMPLE ]========================================================
	print_title("A| SIMPLE AFFECTATION ");

	print_subtitle("A.1| ALL VALID EXP:ADD AND UPDATE");
	char *ev_a1[]		= {"key=value","old_1=oldvalue1","old2=","old_3=old_value_3",NULL};
	char *tab_str_a1[]	= {"export","new_1=val_1","new2=","old_1=newval1","old2=new_val2","old_3=",NULL};
	char *tab_res_a1[]	= {"key=value","new_1=val_1","new2=","old_1=newval1","old2=new_val2","old_3=",NULL};
	nb_err += test(ev_a1, tab_str_a1, tab_res_a1, 0);
	print_sep(S2);

	print_subtitle("A.2| UN-VALID EXP WITH ADD AND UPDATE");
	char *ev_a2[]		= {"key=value","old_1=oldvalue1","old2=","old_3=old_value_3",NULL};
	char *tab_str_a2[]	= {"export","=","new_1=val_1","=tata","new2=","","old_1=newval1","super","old2=new_val2","1un.valid=unvalid","old_3=",NULL};
	char *tab_res_a2[]	= {"key=value","new_1=val_1","new2=","old_1=newval1","old2=new_val2","old_3=",NULL};
	nb_err += test(ev_a2, tab_str_a2, tab_res_a2, 1);
	print_sep(S2);
	print_sep(S1);
	
	print_title("B| CHECK PROTECTED KEYS ");

	print_subtitle("B.1| CHECK UNDERSCORE");
	char *ev_b1[]		= {"_=old_underscore_value","_old_1=oldvalue1","old2=","old_3=old_value_3",NULL};
	char *tab_str_b1[]	= {"export","new_1=val_1","=unvalid","new2=","_old_1=newval1","_=new_undescore_value","old2=new_val2","old_3=",NULL};
	char *tab_res_b1[]	= {"_=old_underscore_value","new_1=val_1","new2=","_old_1=newval1","old2=new_val2","old_3=",NULL};
	nb_err += test(ev_b1, tab_str_b1, tab_res_b1, 1);
	print_sep(S2);
	return (nb_err);
}

// =============================================================================
// test affect_variables()
// CASES:
//   ⭙ : unknown
//   ✔ : pass
//   ✘ : fail
//	 - | unitest | funcheck | examples                                                                     |
//   -----------------------| A| SINGLE NODE                                                               |
//	 - |    ⭙    |     ✔    | str_a0="cmd"                                                                 |
//	 - |    ⭙    |     ✔    | str_a1="<f1"                                                                 |
//   -----------------------| B| MULTIPLE NODES                                                            |
//	 - |    ✔    |     ✔    | str_b0=" cmd1 &&cmd2||cmd3 "                                                 |
//	 - |    ✔    |     ✔    | str_b1=" cmd1 &&cmd2||cmd3&& cmd4 "                                          |
// =============================================================================
 
// =[ INCLUDE ]=================================================================
#include "minishell.h"    // build_tok_lst_split_by_quotes,build_tok_lst_split_by_spaces,build_tok_lst_split_by_operators,set_tok_lst_type
#include <string.h>       // strcmp
#include <stdio.h>        // printf, fflush
						  // ⚠️  Some of minishell print fun. use ~write=>fflush
						  // ⚠️  Depends on libft/array/ft_print_str_array()
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "affect_variables"
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
/*
 * Get the node in <env_lst> where node->name == <key>
 *   NULL		: FAIL : error args == NULL
 *   NULL		: FAIL : error detected in <env_lst>
 *   NULL		: FAIL : No node with <key> exist in <env_lst>
 *   <env_lst>	: PASS : Node <env_lst>->name == <key> 
 */
t_list	*tester_get_env_lst_node(t_list *env_lst, char *key)
{
	t_list	*act;
	char	*act_str;
	int		act_str_len;

	if (!env_lst)
		return (NULL);
	act = env_lst;
	while (act && act->content)
	{
		act_str = ((t_token *)act->content)->str;
		act_str_len = ft_strlen(act_str);
		if (act_str_len < 1)
			return (NULL);
		if (!ft_strncmp(key, act_str, act_str_len))
			return (act);
		act = act->next;
	}
	return (NULL);
}

int	print_raw(t_dlist *raw)
{
	if (!raw)
		return (0);
	t_dlist *act = raw;
	int tot = printf("raw={");
	while (act && act->content)
	{
		fflush(stdout);
		print_token(((t_token *)act->content));
		act = act->next;
	}
	tot += printf("NULL}\n");
	fflush(stdout);
	return (tot);
}

/*
 * test(char **ev, t_token *tab_raw, t_env *tab_res)
 * step1) create a dt from <char **ev>
 * step2) build raw from tab_res
 * step3) call affect_variables(dt, raw)
 * step4) check effect of call on dt->env_lst
 *        for each env in tab env in dt->env_lst
 * void	affect_variables(t_data **dt, t_dlist *raw)
 */
int	test(char **ev, t_token tab_raw[], t_env tab_res[])
{
	// STEP1
	t_data	*data = init_data(ev);
	if (!data)
		return (1);
	// Print test header
	int print_sofar = printf("%s(dt, \"", f_name);
	printf(CB);
	//print_sofar += print_tab_raw(tab_raw); // TODO: print {"%s1","%s2",...,"%sn"}
	print_sofar += printf("{tab_raw}");
	printf(CE);
	print_sofar += printf("\")");
	printntime(S3, LEN - print_sofar);
	printf("\n");

	// STEP2) build raw from tab_raw
	t_dlist *raw = NULL;
	int i = 0;
	//ft_printf("START-->&raw=%p", &raw);
	while (tab_raw[i].str)
	{
		t_token	*new_token = cpy_token(tab_raw[i]);
		if (!new_token)
			return (ft_dlstclear(&raw, free_token), 1);
		//ft_printf("INSIDE LOOP%d new_tok={%d,%s,%d}\n", i,new_token->type,new_token->str,new_token->parenthesis);
		t_dlist	*new_node = ft_dlstnew(new_token);
		if (!new_node)
			return (free_token(new_token), ft_dlstclear(&raw, free_token), 1);
		//ft_printf("ICI-->nod=%p", new_node);
		if (!ft_dlstadd_back(&raw, new_node))
			ft_printf(CR"%s-->ADD BACK node {%s} FAILED\n"CE, tab_raw[i].str, ((t_token *)new_node->content)->str);
		else
			ft_printf(CV"%s-->ADD BACK node {%s} SUCCESS\n"CE, tab_raw[i].str, ((t_token *)new_node->content)->str);
		//ft_printf("END-->raw=%p", raw);
		i++;
	}
	// PRINT RAW
	print_raw(raw);
	ft_printf(CB);
	print_env_lst(data->env_lst);
	ft_printf(CE);
	// STEP3) call affect_variables
	affect_variables(&data, raw);
	ft_printf(CY);
	print_env_lst(data->env_lst);
	ft_printf(CE);

	// STEP4) check affectation
	// Check that every tab_res t_env has been correctly add to data->env_lst
	i = 0;
	while (tab_res[i].name)
	{
		t_list	*env_lst_node_found = tester_get_env_lst_node(data->env_lst, tab_res[i].name);
		if (!env_lst_node_found)
			return (ft_printf(CR"act_env={%s,%s} NOT FOUND IN data->env_lst\n"CE, tab_res[i].name, tab_res[i].value), ft_dlstclear(&raw, free_token),free_data(&data), printntime(S3, LEN - 5), printf(FAIL), 1);
		// compare_env(t_env *, t_env)
		t_env *act_env = (t_env *)env_lst_node_found->content;
		int act_name_len = ft_strlen(act_env->name);
		int act_val_len = ft_strlen(act_env->value);
		int res_name_len = ft_strlen(tab_res[i].name);
		int res_val_len = ft_strlen(tab_res[i].value);
		if (act_name_len != res_name_len)
			return (ft_printf(CR"act_env={%s,%s}-->act_name_len != res_name_len\n"CE, tab_res[i].name, tab_res[i].value), ft_dlstclear(&raw, free_token),free_data(&data), printntime(S3, LEN - 5), printf(FAIL), 1);
		if (act_val_len != res_val_len)
			return (ft_printf(CR"act_env={%s,%s}-->act_val_len != res_val_len\n"CE, tab_res[i].name, tab_res[i].value), ft_dlstclear(&raw, free_token),free_data(&data), printntime(S3, LEN - 5), printf(FAIL), 1);
		if (ft_strncmp(act_env->name, tab_res[i].name, res_name_len))
			return (ft_printf(CR"act_env={%s,%s}--> %s != %s\n"CE,tab_res[i].name,tab_res[i].value,act_env->name, tab_res[i].name), ft_dlstclear(&raw, free_token),free_data(&data), printntime(S3, LEN - 5), printf(FAIL), 1);
		if (ft_strncmp(act_env->value, tab_res[i].value, res_val_len))
			return (ft_printf(CR"act_env={%s,%s}--> %s != %s\n"CE,tab_res[i].name,tab_res[i].value,act_env->value, tab_res[i].value), ft_dlstclear(&raw, free_token),free_data(&data), printntime(S3, LEN - 5), printf(FAIL), 1);
		i++;
	}
	// Check data->env_lst is valid:
	//   1|all t_env has valid key
	//   2|all t_env key is uniq
	t_list	*act_1 = data->env_lst;
	while (act_1)
	{
		char *act_1_name = ((t_env *)act_1)->name;
		char *act_1_value = ((t_env *)act_1)->value;
		if (!act_1_name)
			return (ft_printf(CR"INVALID KEY:%s\n"CE,act_1_name), ft_dlstclear(&raw, free_token),free_data(&data), printntime(S3, LEN - 5), printf(FAIL), 1);
		int act_1_name_len = ft_strlen(act_1_name);
		if (act_1_name_len < 1)
			return (ft_printf(CR"INVALID KEY:%s (empty)\n"CE,act_1_name), ft_dlstclear(&raw, free_token),free_data(&data), printntime(S3, LEN - 5), printf(FAIL), 1);
		t_list	*act_2 = act_1->next;
		while (act_2)
		{
			char *act_2_name = ((t_env *)act_2)->name;
			char *act_2_value = ((t_env *)act_2)->value;
			if (!act_2_name)
				return (ft_printf(CR"INVALID KEY:%s (empty)\n"CE,act_2_name), ft_dlstclear(&raw, free_token),free_data(&data), printntime(S3, LEN - 5), printf(FAIL), 1);
			if (ft_strncmp(act_1_name, act_2_name, ft_strlen(act_2_name)))
				return (ft_printf(CR"DOUBLONS KEY:{%s,%s} AND {%s,%s} (found twice)\n"CE,act_1_name,act_1_value,act_2_name,act_2_value), ft_dlstclear(&raw, free_token),free_data(&data), printntime(S3, LEN - 5), printf(FAIL), 1);
			act_2 = act_2->next;
		}
		act_1 = act_1->next;
	}
	return (ft_dlstclear(&raw, free_token),free_data(&data), printntime(S3, LEN - 5), printf(PASS), 0);
}

int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	(void) ev;
	int	nb_err = 0;

	// =[ 	 ]==================================================================
	print_title("A| ---------------------------");
	// -[  ]--------------------------------------------------------------------
	print_subtitle("A0|--------------------");
	char *ev_a0[]		= {"i1=a","i2=b","i3=c",NULL};
	//t_token tab_raw_a0[]= {{AFF,"key1=val01",0},{AFF,"key2=val_2",0},{AFF,"key3=val_03",0},{AFF,"key4=\"hello world\"",0},{0,0,0}};
	t_token tab_raw_a0[]= {{AFF,"key1=val01",0},{AFF,"key2=val_2",0},{AFF,"key3=val_03",0},{0,0,0}};
	t_env tab_res_a0[]	= {{"key1","val1"},{"key2","val2"},{"key3","val3"},{0,0}};
	nb_err += test(ev_a0, tab_raw_a0, tab_res_a0);
	print_sep(S2);
	print_sep(S1);
	return (nb_err);
}

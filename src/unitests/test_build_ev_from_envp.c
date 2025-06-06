// =[ INCLUDE ]=================================================================
#include "minishell.h"  // build_ev_from_envp
#include <string.h>     // strncmp
#include <stdio.h>      // printf ⚠️  Use printf, not ft_printf or write
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "build_ev_from_envp"
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
int compare_two_str_arrays(char **t1, char **t2)
{
	// test len
	int len_1 = 0;
	while (t1[len_1])
		len_1++;
	int len_2 = 0;
	while (t2[len_2])
		len_2++;
	if (len_1 != len_2)
		return (printf(CR"in compare_two_str_array(t1,t2): len(t1):%d!=len(t2):%d\n"CE, len_1, len_2), 1);
	// test each cases
	int i = 0;
	while (i < len_1)
	{
		if (strcmp(t1[i], t2[i]))
			return (printf(CR"in compare_two_str_array(t1,t2): t1[%d]:%s!= t2[%d]:%s\n"CE, i, t1[i], i, t2[i]), 1);
		i++;
	}
	return (0);
}

int	test_build_ev_from_envp(char **ev, char **res)
{
	char	**ft = build_ev_from_envp(ev);
	int		psf = printf("%s()", f_name);
	printntime(S3, LEN - psf);
	printf("\n");
	if (!ev)
		printf("ev=NULL");
	else
	{
		printf("ev=[\n");
		int i = 0;
		while (ev[i])
			printf("    %s, \n", ev[i++]);
		printf("    NULL\n    ]");
	}
	printf("\n");
	if (!ft)
	{
		if (!ev)
			return (printntime(S3, LEN - 5), printf(PASS), 0);
		return (printntime(S3, LEN - 5), printf(FAIL), 1);
	}
	if (compare_two_str_arrays(res, ft))
		return (ft_free_str_array(&ft), printntime(S3, LEN - 5), printf(FAIL), 1);
	return (ft_free_str_array(&ft), printntime(S3, LEN - 5), printf(PASS), 0);
}

/*
 * UNVALID CASES
 *   u0 = (NULL)          --> NULL (error)
 *   u1 = [=1,0]          --> NULL (error)
 *   u2 = [B2,0]          --> NULL (error)
 *   u3 = [1C=3,0]        --> NULL (error)
 * VALID CASES
 *   v0 = [NULL]          --> [pwd:..., shelvl:1, _:./minishell, 0]
 *   EV = [EV]            --> [all_EV_values, 0]
 *   v1 = [A=1,B=2,C=3,0] --> [A=1,B=2,C=3,0]
 */
int main(int AC, char **AV, char **EV)
{
	(void) AC;
	(void) AV;
	(void) EV;

	int	nb_err = 0;

	print_title("UNVALID CASES");
	print_subtitle("CAS ptr is NULL:ev-->NULL");
	char **u0 = NULL;
	nb_err += test_build_ev_from_envp(u0, NULL);
	print_sep(S2);
	// TODO : ADD u1,u2,...,un
	print_sep(S1);

	print_title("VALID CASES");
	print_subtitle("CAS ev is an empty list:ev-->[NULL]");

	char **v0 = ft_calloc(1, sizeof(char *));
	if (!v0)
		return (nb_err);
	char **res0 = ft_calloc(4, sizeof(char *));
	if (!res0)
		return (42);
	int		buffer_size = 2048;
	char	*buffer = calloc(buffer_size, sizeof(char));
	char	*cwd = getcwd(buffer, buffer_size);
	if (!cwd)
	{
		printf(CR"error:getcwd failed\n"CE);
		free(buffer);
		return (42);
	}
	res0[0] = calloc(strlen(cwd) + 5, 1);
	if (!res0[0])
		return (printf(CR"error:calloc failed\n"CE), 42);
	strcat(res0[0], "PWD=");
	strcat(res0[0], cwd);
	free(buffer); // cwd == buffer
	if (!res0[0])
		return (ft_free_str_array(&res0), 42);
	res0[1] = strdup("SHLVL=1");
	if (!res0[1])
		return (ft_free_str_array(&res0), 42);
	res0[2] = strdup("_=./minishell");
	if (!res0[2])
		return (ft_free_str_array(&res0), 42);
	res0[3] = NULL;
	nb_err += test_build_ev_from_envp(v0, res0);
	ft_free_str_array(&v0);
	ft_free_str_array(&res0);
	print_sep(S2);

	print_subtitle("CAS ev is the real Env-Var");
	nb_err += test_build_ev_from_envp(EV, EV);
	print_sep(S2);

	print_subtitle("Manually created ev");
	char **v1 = ft_calloc(5, sizeof(char *));
	if (!v1)
		return (42);
	v1[0] = strdup("arg1=tata");
	if (!v1[0])
		return (ft_free_str_array(&v1), 42);
	v1[1] = strdup("arg2=tete");
	if (!v1[1])
		return (ft_free_str_array(&v1), 42);
	v1[2] = strdup("arg3=titi");
	if (!v1[2])
		return (ft_free_str_array(&v1), 42);
	v1[3] = strdup("arg4=toto");
	if (!v1[3])
		return (ft_free_str_array(&v1), 42);
	nb_err += test_build_ev_from_envp(v1, v1);
	ft_free_str_array(&v1);
	print_sep(S2);
	print_sep(S1);

	return (nb_err);
}

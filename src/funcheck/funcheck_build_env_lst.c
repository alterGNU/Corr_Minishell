// =[ INCLUDE ]=================================================================
#include "minishell.h"  // build_env_lst
#include <string.h>     // strncmp
#include <stdio.h>      // printf ⚠️  Use printf, not ft_printf or write
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "build_env_lst"
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
// print node of env struct
static void print_struct_env(void *ptr)
{
	t_env *node = (t_env *)ptr;
	printf(" ⮡ {%s=%s},\n", node->name, node->value);
}

int	test_build_env_lst(char **ev)
{
	t_list	*res = build_env_lst(ev);
	int psf = printf("%s(", f_name);
	fflush(stdout);
	psf += ft_print_str_array(ev);
	psf += printf(")");
	printntime(S3, LEN - psf);
	printf("\n✴ t_list *env={\n");
	fflush(stdout);
	ft_lstiter(res, print_struct_env);
	printf(" ⮡ NULL }\n");
	fflush(stdout);
	if (!ev)
	{
		if (!res)
			return (ft_lstclear(&res, free_env), printntime(S3, LEN - 5), printf(FAIL), 1);
		return (ft_lstclear(&res, free_env), printntime(S3, LEN - 5), printf(PASS), 0);
	}
	return (ft_lstclear(&res, free_env), printntime(S3, LEN - 5), printf(PASS), 0);
}

int main(int AC, char **AV, char **EV)
{
	(void) AC;
	(void) AV;
	(void) EV;

	int	nb_err = 0;

	print_title("NULL CASES");
	print_subtitle("CAS ptr is NULL:ev-->NULL");
	char **ev0 = NULL;
	nb_err += test_build_env_lst(ev0);
	print_sep(S2);

	print_subtitle("CAS ev is an empty list:ev-->[NULL]");
	char **ev1 = ft_calloc(1, sizeof(char *));
	if (!ev1)
		return (nb_err);
	nb_err += test_build_env_lst(ev1);
	ft_free_str_array(&ev1);
	print_sep(S2);
	print_sep(S1);

	print_title("Manually created ev");
	char **ev2 = ft_calloc(5, sizeof(char *));
	if (!ev2)
		return (nb_err);
	ev2[0] = strdup("arg1=toto");
	ev2[1] = strdup("arg2=titi");
	ev2[2] = strdup("arg3=titi");
	ev2[3] = strdup("arg4=titi");

	nb_err += test_build_env_lst(ev2);
	ft_free_str_array(&ev2);
	print_sep(S1);

	print_title("Real 'char **env' use as ev");
	nb_err += test_build_env_lst(EV);
	print_sep(S1);

	//// TODO: fork cases that need to fail because panic button will exit
	//char **ev3 = ft_calloc(3, sizeof(char *));
	//ev3[0] = strdup("arg1=toto");
	//ev3[1] = strdup("arg2");
	//print_title("CAS ev-->With Wrong arguments(no '=')");
	//nb_err += test_build_env_lst(ev3);
	//ft_free_str_array(&ev3);

	return (nb_err);
}


#include "minishell.h"  // init_env
#include <string.h>     // strncmp
#include <stdio.h>      // printf

#define LEN 90
#define f_name "init_env"

int	printntime(char c, int n)
{
	for (int i = 0 ; i < n; i++)
		printf("%c", c);
	return (n);
}

void print_title(const char *title)
{
	int print_sofar = printf("=[ %s ]", title);
	printntime('=', LEN - print_sofar);
	printf("\n");
}

static void print_struct_env(void *ptr)
{
	t_env *node = (t_env *)ptr;
	printf(" ⮡ {%s=%s},\n", node->name, node->value);
}

int	test_init_env(char **ev)
{
	t_list	*res = init_env(ev);
	printf("%s(", f_name);
	fflush(stdout);
	ft_print_str_array(ev);
	printf(")\n");
	printf("✴ t_list *env={\n");
	fflush(stdout);
	ft_lstiter(res, print_struct_env);
	printf(" ⮡ NULL }\n");
	if (!ev)
	{
		if (!res)
			return (printntime('=', LEN-3), printf(" ❌\n"), 1);
		return (printntime('=', LEN-3), printf("> ✅\n"), 0);
	}
	return (printntime('=', LEN-3), printf(" ✅\n"), 0);
}

int main(int AC, char **AV, char **EV)
{
	(void) AC;
	(void) AV;
	(void) EV;
	int	nb_err = 0;
	print_title("CAS ev-->NULL");
	char **ev0 = NULL;
	nb_err += test_init_env(ev0);


	char **ev1 = ft_calloc(1, sizeof(char *));
	print_title("CAS ev-->[NULL]");
	nb_err += test_init_env(ev1);
	ft_free_str_array(&ev1);

	char **ev2 = ft_calloc(5, sizeof(char *));
	ev2[0] = strdup("arg1=toto");
	ev2[1] = strdup("arg2=titi");
	ev2[2] = strdup("arg3=titi");
	ev2[3] = strdup("arg4=titi");
	print_title("CAS ev-->OK but manually created");
	nb_err += test_init_env(ev2);
	ft_free_str_array(&ev2);

	print_title("CAS ev-->real env");
	nb_err += test_init_env(EV);

	// TODO: fork cause will fail.
	//char **ev3 = ft_calloc(3, sizeof(char *));
	//ev3[0] = strdup("arg1=toto");
	//ev3[1] = strdup("");
	//print_title("CAS ev-->With Wrong arguments(no '=')");
	//nb_err += test_init_env(ev3);
	//ft_free_str_array(&ev3),

	return (nb_err);
}

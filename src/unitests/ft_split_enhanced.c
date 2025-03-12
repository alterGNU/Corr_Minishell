#include "minishell.h"
#include <string.h>

int	compare_str_array(char **tab1, char **tab2)
{
	int	res;
	int	i;

	if (!tab1 && !tab2)
		return (0);
	if ((tab1 && !tab2) || (!tab1 && tab2))
		return (1);
	i = 0;
	while (tab1[i] && tab2[i])
	{
		if (strcmp(tab1[i], tab2[i]))
			return (1);
		i++;
	}
	if (!tab1[i] && !tab2[i])
		return (0);
	return (1);
}

int	test(char *str, char **matches, char **res)
{
/char	**ft_res = ft_split_enhanced(str, matches);
/return (compare_str_array(res, ft_res));
}

int	main()
{
	int	nb_err;

	nb_err = 0;
	char	*s1 = strdup("  coucou&&petite| perruche||!");
	char	**t1 = (char **)calloc(1, sizeof(char *)) ;  // {NULL}
	char	**t2 = (char **)calloc(4, sizeof(char *)) ;  // {"&&", "||", "|", NULL}
	t2[0] = strdup("&&");
	t2[1] = strdup("||");
	t2[2] = strdup("|");
	char	**r2 = (char **)calloc(5, sizeof(char *)) ;  // {"  coucou", "&&", "petite", "|", "perruche", "||", "!", NULL}
	r2[0] = strdup("  coucou");
	r2[1] = strdup("&&");
	r2[2] = strdup("petite");
	r2[3] = strdup("|");
	r2[4] = strdup(" perruche");
	r2[5] = strdup("||");
	r2[6] = strdup("!");
	// CAS PARTICULIERS
	nb_err += test(NULL, NULL, NULL); // ft_split_enhanced(NULL, NULL)      -->NULL
	nb_err += test(s1, NULL, NULL);   // ft_split_enhanced("...", NULL)     -->NULL
	nb_err += test(NULL, t1, NULL);   // ft_split_enhanced(NULL, {NULL})    -->NULL
	nb_err += test(s1, t1, NULL);     // ft_split_enhanced("...", NULL)     -->NULL
	nb_err += test(NULL, t2, NULL);   // ft_split_enhanced(NULL, {...,NULL})-->NULL
	// CAS CLASSICS
	nb_err += test(s1, t2, r2);
	return (nb_err);
}
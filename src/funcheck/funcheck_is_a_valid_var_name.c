// =[ INCLUDE ]=================================================================
#include "minishell.h"    // build_tok_lst_split_by_quotes,build_tok_lst_split_by_spaces,build_tok_lst_split_by_operators,set_tok_lst_type
#include <string.h>       // strcmp
#include <stdio.h>        // printf, fflush
						  // ⚠️  Some of minishell print fun. use ~write=>fflush
						  // ⚠️  Depends on libft/array/ft_print_str_array()
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "is_a_valid_var_name"
#define CE "\033[0m"      // COLOR END
#define CR "\033[0;31m"   // COLOR RED
#define CV "\033[0;32m"   // COLOR GREEN
#define CM "\033[0;33m"   // COLOR BROWN
#define CY "\033[0;93m"   // COLOR YELLOW
#define CB "\033[0;36m"   // COLOR AZURE
#define CG "\033[0;37m"   // COLOR GREY
#define CT "\033[97;100m" // COLOR GREY
#define PASS " \033[37;42m ✓ \033[0m\n"
#define	FAIL " \033[30;41m ✗ \033[0m\n"
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
 * test(char **keys, res)
 * for each k in <keys>, if is_a_valid_var_name(k) != res ==> FAIL, else PASS
 */
int	test(char **keys, int res)
{
	int	i;
	int	ft;
	int	psf;
	int	tot_err;

	tot_err = 0;
	i = -1;
	while (keys[++i])
	{
		ft = is_a_valid_var_name(keys[i]);
		psf = printf("%s(",f_name);
		printf(CB);
		psf += printf("%s",keys[i]);
		printf(CE);
		psf += printf(")=%d <=> IS %s VAR_NAME ? ", ft, res==0?"AN UN-VALID":"A VALID");
		if (res != ft)
		{
			printntime(".", LEN - 4 - psf), printf(FAIL);
			tot_err++;
		}
		else
			printntime(".", LEN - 4 - psf), printf(PASS);
	}
	return (tot_err);
}

int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	(void) ev;
	int	nb_err = 0;


	// -[ 	"A| ONLY VALID VAR_NAME" ]------------------------------------------
	print_title("A| ONLY VALID VAR_NAME");
	char *valid_keys[]		= {"_","T1","t1","to_TO1","_1","_ToTo_2",NULL};
	nb_err += test(valid_keys, 1);
	print_sep(S1);

	// -[ 	"B| ONLY UN-VALID VAR_NAME" ]---------------------------------------
	print_title("B| ONLY UNVALID VAR_NAME");
	char *unvalid_keys[]		= {"","1","1toTO","1_To_","=","Toto=tutu","tO.Ot", "'tutu'", "ta-ta", NULL};
	nb_err += test(unvalid_keys, 0);
	print_sep(S1);
	return (nb_err);
}

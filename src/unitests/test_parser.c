// =[ INCLUDE ]=================================================================
#include "minishell.h"    // build_tok_lst_split_by_quotes,build_tok_lst_split_by_spaces,build_tok_lst_split_by_operators,set_tok_lst_type
#include <string.h>       // strcmp
#include <stdio.h>        // printf, fflush
						  // ⚠️  Some of minishell print fun. use ~write=>fflush
						  // ⚠️  Depends on libft/array/ft_print_str_array()
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "parser"
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
// print_str_array
int	print_strarr(char **str)
{
	int psf = printf("tab_res=");
	fflush(stdout);
	psf += ft_print_str_array(str);
	return (psf);
}

int	compare_int(int a, int b)
{
	if (a != b)
		return (1);
	return (0);
}

int	compare_token(t_token *a, t_token *b)
{
	return (compare_int(a->type, b->type) + strcmp(a->str, b->str)+ compare_int(a->quote, b->quote) + compare_int(a->parenthesis, b->parenthesis));
}

int	compare_tdlist(t_dlist *a, t_dlist *b)
{
	t_dlist *a_act;
	t_dlist *b_act;
	int 	a_len;
	int 	b_len;
	// check null cases
	if (!a || !b)
	{
		if (!a && !b)
			return (0);
		return (1);
	}
	//check_size
	a_len = 0;
	a_act = a;
	while (a_act)
	{
		a_act = a_act->next;
		a_len++;
	}
	b_len = 0;
	b_act = b;
	while (b_act)
	{
		b_act = b_act->next;
		b_len++;
	}
	if (a_len != b_len)
		return (1);
	// Check each node are the same
	a_act = a;
	b_act = b;
	while (a_act && b_act)
	{
		if (compare_token(a_act->content, b_act->content))
			return (1);
		a_act = a_act->next;
		b_act = b_act->next;
	}
	return (0);
}

int compare_ptr(void *ptr1, void *ptr2)
{
	if (ptr1 != ptr2)
		return (1);
	return (0);
}
//typedef struct s_asn
//{
//	t_dlist	*raw;
//	int		type;
//	int		(*print_fun)(void *ptr);
//	void	(*free_fun)(void *ptr);
//	//char	**str;
//	//char	quote;
//	//int		parenthesis;
//	//char	*args;
//	//char	*file;
//}	t_asn;
int compare_asn(t_asn *a, t_asn *b)
{
	int	comp_raw;
	int	comp_type;
	int	comp_print_fun;
	int	comp_free_fun;
	if (!a || !b)
	{
		if (!a && !b)
			return (0);
		return (1);
	}
	comp_raw = compare_tdlist(a->raw, b->raw);
	comp_type = compare_int(a->type, b->type);
	comp_print_fun = compare_ptr((void *)a->print_fun, (void*)b->print_fun);
	comp_free_fun = compare_ptr((void *)a->free_fun, (void *)b->free_fun);
	return (comp_raw + comp_type + comp_print_fun + comp_free_fun);
}

// Compare two tbtree , return 0 if same, 1 else
//       A       |       A      
//   a       X   |   a       b  
// c   d   X   X | c   D   e   f 
//X X X X X X X X|X X X X X X X X
// AA -> 0
// aa -> 0
// cc -> 0
// XX -> 0
// XX -> 0
// dD -> 1
// Xb -> 1
//return (0 + 0 + 0 + 0 + 0 + 1 + 1 )
int	compare_btree(t_btree *a, t_btree *b)
{
	if (!a || !b)
	{
		if (!a && !b)
			return (0);
		return (1);
	}
	if (compare_asn(a->content, b->content))
		return (1);
	return (compare_btree(a->left, b->left) + compare_btree(a->right, b->right));
}
// This function print details only on failures.
int	test(char *str, t_btree **btree_res, char **ev)
{
	printf("btree_res=\n");
	fflush(stdout);
	ft_btreeprint(*btree_res, print_first_four_char, 4);
	t_data	*data = init_data(ev);
	if (!data)
		return (ft_btreeclear(btree_res, free_token), 1);
	data->debug_mode = 1;
	// Print test header
	int print_sofar = printf("%s(\"%s\")", f_name, str);
	if (str)
	{
		int c = count_char_in_str('\t', str);
		if (c)
			print_sofar+=c*4;
	}
	printntime(S3, LEN - print_sofar);
	printf("\n");
	// LEXING
	lexer(str, &data);
	// PARSER
	parser(&data);
	// PRINT
	printf("AFTER PARSER\ndt->ast  =\n");
	fflush(stdout);
	ft_btreeprint(data->ast, print_first_four_char, 4);
	// CHECK AFTER PARSING
	//int res = compare_btree(data->ast, *btree_res);
	//if (!res)
	//	return (ft_btreeclear(btree_res, free_token), free_data(&data), printntime(S3, LEN - 5), printf(PASS), 0);
	//return (ft_btreeclear(btree_res, free_token), free_data(&data), printntime(S3, LEN - 5), printf(FAIL), 1);
	return (0);
}

int add_dlst_node(t_dlist **raw, t_token *content)
{
	t_dlist	*new;

	new = ft_dlstnew(content);
	if (!new)
		return (ft_dlstclear(raw, free_token), 0);
	ft_dlstadd_back(raw, new);
	return (1);
}


t_token	*create_token(char *str, int type, char quote, char parenthesis)
{
	t_token *res;
	
	res = init_token();
	if (!res)
		return (NULL);
	set_token_str(res, str, 0, strlen(str));
	set_token_type(res, type);
	set_token_quote(res, quote);
	set_token_parenthesis(res, parenthesis);
	return (res);
}

t_asn *create_asn(t_token *tab)
{
	int		i;
	t_token *token;
	t_dlist *raw;
	t_asn	*res;

	raw = NULL;
	i = -1;
	while (tab[++i].str)
	{
		token = cpy_token(tab[i]);
		if (!token)
			return (ft_dlstclear(&raw, free_token), NULL);
		if (!add_dlst_node(&raw, token))
			return (free_token(token), ft_dlstclear(&raw, free_token), NULL);
	}
	res = init_asn(raw);
	if (!res)
		return (ft_dlstclear(&raw, free_token), NULL);
	return (res);
}

int	main(int ac, char **av, char **ev)
{
	(void) ac;
	(void) av;
	int	nb_err = 0;

	///TODO: lexer fails --> No parsing
	///TODO: lexer pass  --> parsing --> compare with t_btree *tree_res
	char *str0="cmd";
	t_token t0[] = {{UNSET,"cmd",0,0},{0,0,0,0}};
	t_asn *asn0 = create_asn(t0);
	t_btree *ast0 = ft_btreenew(asn0);
	nb_err += test(str0, &ast0, ev);
	//// ----------------------------------------------
	//char *str1="<f1";
	//t_token t1[] = {{RLS,"<",0,0}, {UNSET,"f1",0,0},{0,0,0,0}};
	//t_asn *asn1 = create_asn(t1);
	//t_btree *ast1 = ft_btreenew(asn1);
	//printf("btree_res=\n");
	//fflush(stdout);
	//ft_btreeprint(ast1, print_first_four_char, 4);
	//nb_err += test(str1, &ast1, ev);
	// ----------------------------------------------
	//char *str_10="cmd1&&cmd2||cmd3";
	//
	//t_token *tab_10[]={{"&&",OPA,0,0}, NULL};
	//t_asn *asn_10 = create_asn(tab_10);
	//t_btree *ast_10 = ft_btreenew(asn_10);
	//
	//t_token *tab_11[]={{"cmd1",UNSET,0,0}, NULL};
	//t_asn *asn_11 = create_asn(tab_11);
	//t_btree *ast_11 = ft_btreenew(asn_11);
	//
	//t_token *tab_12[]={{"||",OPO,0,0}, NULL};
	//t_asn *asn_12 = create_asn(tab_12);
	//t_btree *ast_12 = ft_btreenew(asn_12);
	//
	//t_token *tab_13[]={{"cmd2",UNSET,0,0}, NULL};
	//t_asn *asn_13 = create_asn(tab_13);
	//t_btree *ast_13 = ft_btreenew(asn_13);
	//
	//t_token *tab_14[]={{"cmd3",UNSET,0,0}, NULL};
	//t_asn *asn_14 = create_asn(tab_14);
	//t_btree *ast_14 = ft_btreenew(asn_14);

	//nb_err += test(str_10, &ast_00, ev);
	// ----------------------------------------------
	//char *str_10="<f1 <f2 cmd1 <f3";
	return (nb_err);
}

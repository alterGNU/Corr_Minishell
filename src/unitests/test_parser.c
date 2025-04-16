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
int	test(char *str, t_btree **add_res, char **ev)
{
	t_btree *res = NULL;
	if (add_res)
		res = *add_res;
	t_data	*data = init_data(ev);
	if (!data)
		return (ft_btreeclear(add_res, free_token), 1);
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
	fflush(stdout);
	// LEXING
	lexer(str, &data);
	// PARSER
	parser(&data);
	// PRINT
	printf("btree_res=\n");
	fflush(stdout);
	ft_btreeprint(res, print_first_four_char, 4);
	printf("data->ast=\n");
	fflush(stdout);
	ft_btreeprint(data->ast, print_first_four_char, 4);
	// CHECK AFTER PARSING
	int comp_res = compare_btree(data->ast, res);
	if (!comp_res)
		return (ft_btreeclear(add_res, free_asn), free_data(&data), printntime(S3, LEN - 5), printf(PASS), 0);
	return (ft_btreeclear(add_res, free_asn), free_data(&data), printntime(S3, LEN - 5), printf(FAIL), 1);
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

	
	////TODO can not be tested-->if null, lexer panic and exit
	//print_title("A| NULL CASES");
	//nb_err += test(NULL, NULL, ev);
	//print_sep(S1);

	print_title("A| FAIL COMMANDS-->lexing");
	nb_err += test("cmd>", NULL, ev);
	nb_err += test("()", NULL, ev);
	nb_err += test("<(cmd)", NULL, ev);
	print_sep(S1);
	
	print_title("A| SINGLE NODES:parsing");
	print_subtitle("Simple node == UNSET");
	char *str0="cmd";
	t_token t0[] = {{UNSET,"cmd",0,0},{0,0,0,0}};
	t_asn *asn0 = create_asn(t0);
	t_btree *ast0 = ft_btreenew(asn0);
	nb_err += test(str0, &ast0, ev);
	print_sep(S2);
	
	print_subtitle("Simple node == REDIR");
	char *str1="<f1";
	t_token t1[] = {{RLS,"<",0,0}, {UNSET,"f1",0,0}, {0,0,0,0}};
	t_asn *asn1 = create_asn(t1);
	t_btree *ast1 = ft_btreenew(asn1);
	nb_err += test(str1, &ast1, ev);
	print_sep(S2);
	print_sep(S1);
// -[  ]------------------------------------------------------------------------
	print_title("B| MULTIPLES NODES:parsing");
	print_subtitle("Only unset with OPA, OPO");
	char *str_2="cmd1&&cmd2||cmd3";
	// CREATE NODES
	t_token tab_10[]={{OPA,"&&",0,0}, {0,0,0,0}};
	t_asn *asn_10 = create_asn(tab_10);
	t_btree *ast_10 = ft_btreenew(asn_10);
	
	t_token tab_11[]={{UNSET,"cmd1",0,0}, {0,0,0,0}};
	t_asn *asn_11 = create_asn(tab_11);
	t_btree *ast_11 = ft_btreenew(asn_11);
	
	t_token tab_12[]={{OPO,"||",0,0}, {0,0,0,0}};
	t_asn *asn_12 = create_asn(tab_12);
	t_btree *ast_12 = ft_btreenew(asn_12);

	t_token tab_13[]={{UNSET,"cmd2",0,0}, {0,0,0,0}};
	t_asn *asn_13 = create_asn(tab_13);
	t_btree *ast_13 = ft_btreenew(asn_13);
	
	t_token tab_14[]={{UNSET,"cmd3",0,0}, {0,0,0,0}};
	t_asn *asn_14 = create_asn(tab_14);
	t_btree *ast_14 = ft_btreenew(asn_14);
	//ATTACHED NODES
	ast_12->left = ast_13;
	ast_12->right = ast_14;
	ast_10->left = ast_11;
	ast_10->right = ast_12;
	// RUN TEST
	nb_err += test(str_2, &ast_10, ev);
	print_sep(S2);
// -[  ]------------------------------------------------------------------------
	print_subtitle("Only unset with OPA, OPO");
	char *str_3="<f0 <f1 cm <f3 ar";
	// CREATE NODES
	t_token tab_20[]={{RLS,"<",0,0}, {UNSET,"f0",0,0}, {0,0,0,0}};
	t_asn *asn_20 = create_asn(tab_20);
	t_btree *ast_20 = ft_btreenew(asn_20);
	
	t_token tab_21[]={{RLS,"<",0,0}, {UNSET,"f1",0,0}, {0,0,0,0}};
	t_asn *asn_21 = create_asn(tab_21);
	t_btree *ast_21 = ft_btreenew(asn_21);
	
	t_token tab_22[]={{UNSET,"cm",0,0},{UNSET,"ar",0,0}, {0,0,0,0}};
	t_asn *asn_22 = create_asn(tab_22);
	t_btree *ast_22 = ft_btreenew(asn_22);

	t_token tab_23[]={{RLS,"<",0,0}, {UNSET,"f3",0,0}, {0,0,0,0}};
	t_asn *asn_23 = create_asn(tab_23);
	t_btree *ast_23 = ft_btreenew(asn_23);
	//ATTACHED NODES
	ast_20->left = ast_21;
	ast_21->left = ast_23;
	ast_23->left = ast_22;
	// RUN TEST
	nb_err += test(str_3, &ast_20, ev);
	print_sep(S2);
// -[  ]------------------------------------------------------------------------
	print_subtitle("Combos");
	char *str_4="c1<f1 a1|c2|c3&&c4";
	// CREATE NODES
	t_token tab_30[]={{RLS,"<",0,0}, {UNSET,"f1",0,0}, {0,0,0,0}};
	t_asn *asn_30 = create_asn(tab_30);
	t_btree *ast_30 = ft_btreenew(asn_30);
	
	t_token tab_31[]={{UNSET,"c1",0,0},{UNSET,"a1",0,0}, {0,0,0,0}};
	t_asn *asn_31 = create_asn(tab_31);
	t_btree *ast_31 = ft_btreenew(asn_31);

	t_token tab_32[]={{PIP,"|",0,0}, {0,0,0,0}};
	t_asn *asn_32 = create_asn(tab_32);
	t_btree *ast_32 = ft_btreenew(asn_32);

	t_token tab_33[]={{UNSET,"c2",0,0}, {0,0,0,0}};
	t_asn *asn_33 = create_asn(tab_33);
	t_btree *ast_33 = ft_btreenew(asn_33);

	t_token tab_34[]={{PIP,"|",0,0}, {0,0,0,0}};
	t_asn *asn_34 = create_asn(tab_34);
	t_btree *ast_34 = ft_btreenew(asn_34);

	t_token tab_35[]={{UNSET,"c3",0,0}, {0,0,0,0}};
	t_asn *asn_35 = create_asn(tab_35);
	t_btree *ast_35 = ft_btreenew(asn_35);

	t_token tab_36[]={{OPA,"&&",0,0}, {0,0,0,0}};
	t_asn *asn_36 = create_asn(tab_36);
	t_btree *ast_36 = ft_btreenew(asn_36);

	t_token tab_37[]={{UNSET,"c4",0,0}, {0,0,0,0}};
	t_asn *asn_37 = create_asn(tab_37);
	t_btree *ast_37 = ft_btreenew(asn_37);
	//ATTACHED NODES
	ast_34->left = ast_33;
	ast_34->right = ast_35;
	ast_30->left = ast_31;
	ast_32->left = ast_30;
	ast_32->right = ast_34;
	ast_36->left = ast_32;
	ast_36->right = ast_37;
	// RUN TEST
	nb_err += test(str_4, &ast_36, ev);
	print_sep(S2);
	print_sep(S1);
// -[ TODO ]--------------------------------------------------------------------
	return (nb_err);
}

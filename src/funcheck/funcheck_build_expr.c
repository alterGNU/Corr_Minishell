// =[ INCLUDE ]=================================================================
#include "minishell.h"    // build_tok_lst_split_by_quotes,build_tok_lst_split_by_spaces,build_tok_lst_split_by_operators,set_tok_lst_type
#include <string.h>       // strcmp
#include <stdio.h>        // printf, fflush
						  // ⚠️  Some of minishell print fun. use ~write=>fflush
						  // ⚠️  Depends on libft/array/ft_print_str_array()
// =[ DEFINE ]==================================================================
#define LEN 90
#define f_name "build_expr"
#define E "\033[0m"      // COLOR END
#define CR "\033[0;31m"   // COLOR RED
#define CV "\033[0;32m"   // COLOR GREEN
#define CM "\033[0;33m"   // COLOR BROWN
#define CY "\033[0;93m"   // COLOR YELLOW
#define CB "\033[0;36m"   // COLOR AZURE
#define CG "\033[0;37m"   // COLOR GREY
#define CT "\033[97;100m" // COLOR GREY
#define PASS "> \033[37;42m ✓ \033[0m\n"
#define	FAIL "> \033[30;41m ✗ \033[0m\n"
#define	S1 CT"="E
#define	S2 CB"*"E
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
	printf(E"\n");
}
// -[ PRINT_SUB_TITLE ]---------------------------------------------------------
void print_subtitle(char *subtitle)
{
	printf(S2""CB);
	int psf = printf("( %s )", subtitle);
	printntime(S2, LEN - psf - 1);
	printf(E"\n");
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
	return (compare_int(a->type, b->type) + strcmp(a->str, b->str)+ compare_int(a->parenthesis, b->parenthesis));
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
		return (ft_btreeclear(add_res, free_asn), 1);
	data->debug_mode = 1;
	data->line = strdup(str);
	if (!data->line)
		return (ft_btreeclear(add_res, free_asn), free_data(&data), 1);
	// Print test header
	int print_sofar = printf("%s(\"%s\")", f_name, data->line);
	if (data->line)
	{
		int c = count_char_in_str('\t', data->line);
		if (c)
			print_sofar+=c*4;
	}
	printntime(S3, LEN - print_sofar);
	printf("\n");
	fflush(stdout);
	// LEXING
	lexer(&data);
	if (!data->tok_lst)
		write(1, "\n", 1);
	// PARSER
	t_list *act_node = data->tok_lst;
	data->ast = build_expr(&act_node);
	if (!data->ast)
		write(1, "\n", 1);
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
		return (free_data(&data), printntime(S3, LEN - 5), printf(PASS), 0);
	return (free_data(&data), printntime(S3, LEN - 5), printf(FAIL), 1);
}

int add_dlst_node(t_dlist **raw, t_token *content)
{
	t_dlist	*new;

	new = ft_dlstnew(content);
	if (!new)
		return (ft_dlstclear(raw, free_token), 0);
	return (ft_dlstadd_back(raw, new));
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
			return (free_token(token), ft_free((void **)&token), ft_dlstclear(&raw, free_token), NULL);
	}
	res = init_asn(raw, tab[0].type);
	if (!res)
		return (ft_dlstclear(&raw, free_token), NULL);
	return (res);
}

t_btree *create_ast_node(t_token tab[])
{
	t_asn *asn;
	t_btree *res;

	if (!tab)
		return (NULL);
	asn = create_asn(tab);
	if (!asn)
		return (NULL);
	res = ft_btreenew(asn);
	if (!res)
		return (free_asn(asn), ft_free((void **)&asn), NULL);
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
	// =[  ]====================================================================
	print_title("A| FAIL COMMANDS-->lexing");
	print_subtitle("WRONG REDIR SYNTAX RULES");
	nb_err += test("cmd>", NULL, ev);
	nb_err += test("< <", NULL, ev);
	nb_err += test("<", NULL, ev);
	print_sep(S2);
	print_subtitle("WRONG PARENTHESIS SYNTAX RULES");
	nb_err += test("()", NULL, ev);
	nb_err += test("(", NULL, ev);
	nb_err += test("(cmd))", NULL, ev);
	print_sep(S2);
	print_subtitle("UNSUPPORTED OPERATOR");
	nb_err += test("<(cmd)", NULL, ev);
	nb_err += test("((cmd))", NULL, ev);
	print_sep(S2);
	print_sep(S1);
	//// =[ 	 ]==================================================================
	//print_title("B| BTREE WITH ONE NODE:parsing");
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("Simple node == UNSET:cmd");
	//t_token b0[] = {{UNSET,"cmd",0},{0,0,0}};
	//t_btree *ast_b0 = create_ast_node(b0);
	//if (!ast_b0)
	//	return (1);
	//nb_err += test("cmd", &ast_b0, ev);
	//nb_err += test("  cmd", &ast_b0, ev);
	//nb_err += test("cmd  ", &ast_b0, ev);
	//nb_err += test("  cmd  ", &ast_b0, ev);
	//ft_btreeclear(&ast_b0, free_asn);
	//print_sep(S2);
	//// -[ 	 ]------------------------------------------------------------------
	//print_subtitle("Simple node == REDIR:<f1");
	//t_token b1[] = {{RLS,"<",0}, {UNSET,"f1",0}, {0,0,0}};
	//t_btree *ast_b1 = create_ast_node(b1);
	//if (!ast_b1)
	//	return (1);
	//nb_err += test("<f1", &ast_b1, ev);
	//nb_err += test("  <f1", &ast_b1, ev);
	//nb_err += test("<f1  ", &ast_b1, ev);
	//nb_err += test("  <f1  ", &ast_b1, ev);
	//nb_err += test("  <   f1  ", &ast_b1, ev);
	//ft_btreeclear(&ast_b1, free_asn);
	//print_sep(S2);
	//// =[ 	 ]==================================================================
	print_title("C| MULTIPLE UNSET AND REDIR");
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("Multiples REDIR && ESP:<i1>o1<i2>o2<i3>o3");
	//// CREATE NODES
	//t_token tab_c1_0[]={{RLS,"<",0}, {UNSET,"i1",0}, {0,0,0}};
	//t_btree *ast_c1_0 = create_ast_node(tab_c1_0);
	//if (!ast_c1_0)
	//	return (1);
	//t_token tab_c1_1[]={{RRS,">",0}, {UNSET,"o1",0}, {0,0,0}};
	//t_btree *ast_c1_1 = create_ast_node(tab_c1_1);
	//if (!ast_c1_1)
	//	return (ft_btreedelone(&ast_c1_0, free_asn), 1);
	//t_token tab_c1_2[]={{RLS,"<",0}, {UNSET,"i2",0}, {0,0,0}};
	//t_btree *ast_c1_2 = create_ast_node(tab_c1_2);
	//if (!ast_c1_2)
	//	return (ft_btreedelone(&ast_c1_0, free_asn), ft_btreedelone(&ast_c1_1, free_asn), 1);
	//t_token tab_c1_3[]={{RRS,">",0}, {UNSET,"o2",0}, {0,0,0}};
	//t_btree *ast_c1_3 = create_ast_node(tab_c1_3);
	//if (!ast_c1_3)
	//	return (ft_btreedelone(&ast_c1_0, free_asn),ft_btreedelone(&ast_c1_1, free_asn),ft_btreedelone(&ast_c1_2, free_asn), 1);
	//t_token tab_c1_4[]={{RLS,"<",0}, {UNSET,"i3",0}, {0,0,0}};
	//t_btree *ast_c1_4 = create_ast_node(tab_c1_4);
	//if (!ast_c1_4)
	//	return (ft_btreedelone(&ast_c1_0, free_asn), ft_btreedelone(&ast_c1_1, free_asn),ft_btreedelone(&ast_c1_2, free_asn), ft_btreedelone(&ast_c1_3, free_asn), 1);
	//t_token tab_c1_5[]={{RRS,">",0}, {UNSET,"o3",0}, {0,0,0}};
	//t_btree *ast_c1_5 = create_ast_node(tab_c1_5);
	//if (!ast_c1_5)
	//	return (ft_btreedelone(&ast_c1_0, free_asn),ft_btreedelone(&ast_c1_1, free_asn),ft_btreedelone(&ast_c1_2, free_asn),ft_btreedelone(&ast_c1_3, free_asn),ft_btreedelone(&ast_c1_4, free_asn), 1);
	////ATTACHED NODES
	//ast_c1_0->left = ast_c1_1;
	//ast_c1_1->left = ast_c1_2;
	//ast_c1_2->left = ast_c1_3;
	//ast_c1_3->left = ast_c1_4;
	//ast_c1_4->left = ast_c1_5;
	//// RUN TEST
	//nb_err += test("<i1>o1<i2>o2<i3>o3", &ast_c1_0, ev);
	//nb_err += test("   <  i1 >  o1  <i2>o2<i3>o3", &ast_c1_0, ev);
	//nb_err += test("<i1>o1<i2>o2 <  i3 >  o3   ", &ast_c1_0, ev);
	//nb_err += test("  <  i1  >  o1  <i2>o2  <  i3  >  o3  ", &ast_c1_0, ev);
	//ft_btreeclear(&ast_c1_0, free_asn);
	//print_sep(S2);
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("Multiples UNSET && ESP:cmd a1 \"a2 a3\" a4");
	//// CREATE NODES
	//t_token tab_c2_0[]={{UNSET,"cmd",0},{UNSET,"a1",0},{UNSET,"\"a2 a3\"",0},{UNSET,"a4",0}, {0,0,0}};
	//t_btree *ast_c2_0 = create_ast_node(tab_c2_0);
	//if (!ast_c2_0)
	//	return (1);
	//// RUN TEST
	//nb_err += test("cmd a1 \"a2 a3\" a4", &ast_c2_0, ev);
	//nb_err += test("  cmd   a1   \"a2 a3\"   a4  ", &ast_c2_0, ev);
	//ft_btreeclear(&ast_c2_0, free_asn);
	//print_sep(S2);
	//// -[  ]--------------------------------------------------------------------
	print_subtitle("COMBOS REDIR && UNSET:a<i1 b<i2 c>o1 d>o2");
	// CREATE NODES
	t_token tab_c3_0[]={{RLS,"<",0}, {UNSET,"i1",0}, {0,0,0}};
	t_btree *ast_c3_0 = create_ast_node(tab_c3_0);
	if (!ast_c3_0)
		return (1);
	t_token tab_c3_1[]={{RLS,"<",0}, {UNSET,"i2",0}, {0,0,0}};
	t_btree *ast_c3_1 = create_ast_node(tab_c3_1);
	if (!ast_c3_1)
		return (ft_btreedelone(&ast_c3_0, free_asn), 1);
	t_token tab_c3_2[]={{RRS,">",0}, {UNSET,"o1",0}, {0,0,0}};
	t_btree *ast_c3_2 = create_ast_node(tab_c3_2);
	if (!ast_c3_2)
		return (ft_btreedelone(&ast_c3_0, free_asn), ft_btreedelone(&ast_c3_1, free_asn), 1);
	t_token tab_c3_3[]={{RRS,">",0}, {UNSET,"o2",0}, {0,0,0}};
	t_btree *ast_c3_3 = create_ast_node(tab_c3_3);
	if (!ast_c3_3)
		return (ft_btreedelone(&ast_c3_0, free_asn),ft_btreedelone(&ast_c3_1, free_asn),ft_btreedelone(&ast_c3_2, free_asn), 1);
	t_token tab_c3_4[]={{UNSET,"a",0}, {UNSET,"b",0}, {UNSET,"c",0}, {UNSET,"d",0}, {0,0,0}};
	t_btree *ast_c3_4 = create_ast_node(tab_c3_4);
	if (!ast_c3_4)
		return (ft_btreedelone(&ast_c3_0, free_asn), ft_btreedelone(&ast_c3_1, free_asn),ft_btreedelone(&ast_c3_2, free_asn), ft_btreedelone(&ast_c3_3, free_asn), 1);
	//ATTACHED NODES
	ast_c3_0->left = ast_c3_1;
	ast_c3_1->left = ast_c3_2;
	ast_c3_2->left = ast_c3_3;
	ast_c3_3->left = ast_c3_4;
	// RUN TEST
	//nb_err += test("a<i1 b<i2 c>o1 d>o2", &ast_c3_0, ev);
	//nb_err += test("  a  <  i1 b  <  i2 c>o1 d>o2", &ast_c3_0, ev);
	//nb_err += test("a<i1 b<i2 c  >  o1 d  >  o2  ", &ast_c3_0, ev);
	nb_err += test("  a  <  i1 b<i2 c>o1 d  >  o2  ", &ast_c3_0, ev);

	//nb_err += test("<i1 a<i2 b>o1 c>o2 d", &ast_c3_0, ev);
	//nb_err += test("  <  i1 a<i2 b  >  o1 c>o2 d", &ast_c3_0, ev);
	//nb_err += test("<i1 a  <  i2 b>o1 c  >  o2 d  ", &ast_c3_0, ev);
	//nb_err += test("  <  i1 a<i2 b>o1 c  >  o2 d  ", &ast_c3_0, ev);

	//nb_err += test("a b <i1<i2>o1>o2 c d", &ast_c3_0, ev);
	//nb_err += test("<i1<i2 a b>o1>o2 c d", &ast_c3_0, ev);
	//nb_err += test("a b <i1<i2 c d>o1>o2", &ast_c3_0, ev);
	//nb_err += test("a b c d<i1<i2>o1>o2", &ast_c3_0, ev);
	//nb_err += test("<i1<i2>o1>o2 a b c d", &ast_c3_0, ev);
	//ft_btreeclear(&ast_c3_0, free_asn);
	//print_sep(S1);
	//return (nb_err);
}


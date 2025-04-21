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
		return (ft_btreeclear(add_res, free_asn), 1);
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
	res = init_asn(raw);
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
	nb_err += test("cmd>", NULL, ev);
	nb_err += test("()", NULL, ev);
	nb_err += test("<(cmd)", NULL, ev);
	print_sep(S1);
	// =[ 	 ]==================================================================
	print_title("A| BTREE WITH ONE NODE:parsing");
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Simple node == UNSET");
	char *str0="cmd";
	t_token t0[] = {{UNSET,"cmd",0,0},{0,0,0,0}};
	t_btree *ast0 = create_ast_node(t0);
	if (!ast0)
		return (1);
	nb_err += test(str0, &ast0, ev);
	print_sep(S2);
	// -[ 	 ]------------------------------------------------------------------
	print_subtitle("Simple node == REDIR");
	char *str1="<f1";
	t_token t1[] = {{RLS,"<",0,0}, {UNSET,"f1",0,0}, {0,0,0,0}};
	t_btree *ast1 = create_ast_node(t1);
	if (!ast1)
		return (1);
	nb_err += test(str1, &ast1, ev);
	print_sep(S2);
	print_sep(S1);
	// =[  ]====================================================================
	print_title("B| BTREE WITH MULTIPLES NODES:parsing");
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Only UNSET and OPA, OPO");
	char *str_2="cmd1&&cmd2||cmd3";
	// CREATE NODES
	t_token tab_10[]={{OPA,"&&",0,0}, {0,0,0,0}};
	t_btree *ast_10 = create_ast_node(tab_10);
	if (!ast_10)
		return (1);
	t_token tab_11[]={{UNSET,"cmd1",0,0}, {0,0,0,0}};
	t_btree *ast_11 = create_ast_node(tab_11);
	if (!ast_11)
		return (ft_btreedelone(&ast_10, free_asn), 1);
	t_token tab_12[]={{OPO,"||",0,0}, {0,0,0,0}};
	t_btree *ast_12 = create_ast_node(tab_12);
	if (!ast_12)
		return (ft_btreedelone(&ast_10, free_asn),ft_btreedelone(&ast_11, free_asn), 1);
	t_token tab_13[]={{UNSET,"cmd2",0,0}, {0,0,0,0}};
	t_btree *ast_13 = create_ast_node(tab_13);
	if (!ast_13)
		return (ft_btreedelone(&ast_10, free_asn),ft_btreedelone(&ast_11, free_asn),ft_btreedelone(&ast_12, free_asn), 1);
	t_token tab_14[]={{UNSET,"cmd3",0,0}, {0,0,0,0}};
	t_btree *ast_14 = create_ast_node(tab_14);
	if (!ast_14)
		return (ft_btreedelone(&ast_10, free_asn),ft_btreedelone(&ast_11, free_asn),ft_btreedelone(&ast_12, free_asn),ft_btreedelone(&ast_13, free_asn), 1);
	//ATTACHED NODES
	ast_12->left = ast_13;
	ast_12->right = ast_14;
	ast_10->left = ast_11;
	ast_10->right = ast_12;
	// RUN TEST
	nb_err += test(str_2, &ast_10, ev);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Only UNSET and REDIR");
	char *str_3="<f0 <f1 cm <f3 ar";
	// CREATE NODES
	t_token tab_20[]={{RLS,"<",0,0}, {UNSET,"f0",0,0}, {0,0,0,0}};
	t_btree *ast_20 = create_ast_node(tab_20);
	if (!ast_20)
		return (1);
	t_token tab_21[]={{RLS,"<",0,0}, {UNSET,"f1",0,0}, {0,0,0,0}};
	t_btree *ast_21 = create_ast_node(tab_21);
	if (!ast_21)
		return (ft_btreedelone(&ast_20, free_asn), 1);
	t_token tab_22[]={{UNSET,"cm",0,0},{UNSET,"ar",0,0}, {0,0,0,0}};
	t_btree *ast_22 = create_ast_node(tab_22);
	if (!ast_22)
		return (ft_btreedelone(&ast_20, free_asn),ft_btreedelone(&ast_21, free_asn), 1);
	t_token tab_23[]={{RLS,"<",0,0}, {UNSET,"f3",0,0}, {0,0,0,0}};
	t_btree *ast_23 = create_ast_node(tab_23);
	if (!ast_23)
		return (ft_btreedelone(&ast_20, free_asn),ft_btreedelone(&ast_21, free_asn),ft_btreedelone(&ast_22, free_asn), 1);
	//ATTACHED NODES
	ast_20->left = ast_21;
	ast_21->left = ast_23;
	ast_23->left = ast_22;
	// RUN TEST
	nb_err += test(str_3, &ast_20, ev);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Combos");
	char *str_4="c1<f1 a1|c2|c3&&c4";
	// CREATE NODES
	t_token tab_30[]={{RLS,"<",0,0}, {UNSET,"f1",0,0}, {0,0,0,0}};
	t_btree *ast_30 = create_ast_node(tab_30);
	if (!ast_30)
		return (1);
	t_token tab_31[]={{UNSET,"c1",0,0},{UNSET,"a1",0,0}, {0,0,0,0}};
	t_btree *ast_31 = create_ast_node(tab_31);
	if (!ast_31)
		return (ft_btreedelone(&ast_30, free_asn), 1);
	t_token tab_32[]={{PIP,"|",0,0}, {0,0,0,0}};
	t_btree *ast_32 = create_ast_node(tab_32);
	if (!ast_32)
		return (ft_btreedelone(&ast_30, free_asn),ft_btreedelone(&ast_31, free_asn), 1);
	t_token tab_33[]={{UNSET,"c2",0,0}, {0,0,0,0}};
	t_btree *ast_33 = create_ast_node(tab_33);
	if (!ast_33)
		return (ft_btreedelone(&ast_30, free_asn),ft_btreedelone(&ast_31, free_asn), ft_btreedelone(&ast_32, free_asn), 1);
	t_token tab_34[]={{PIP,"|",0,0}, {0,0,0,0}};
	t_btree *ast_34 = create_ast_node(tab_34);
	if (!ast_34)
		return (ft_btreedelone(&ast_30, free_asn),ft_btreedelone(&ast_31, free_asn), ft_btreedelone(&ast_32, free_asn), ft_btreedelone(&ast_33, free_asn), 1);
	t_token tab_35[]={{UNSET,"c3",0,0}, {0,0,0,0}};
	t_btree *ast_35 = create_ast_node(tab_35);
	if (!ast_35)
		return (ft_btreedelone(&ast_30, free_asn),ft_btreedelone(&ast_31, free_asn), ft_btreedelone(&ast_32, free_asn), ft_btreedelone(&ast_33, free_asn), ft_btreedelone(&ast_34, free_asn), 1);
	t_token tab_36[]={{OPA,"&&",0,0}, {0,0,0,0}};
	t_btree *ast_36 = create_ast_node(tab_36);
	if (!ast_36)
		return (ft_btreedelone(&ast_30, free_asn),ft_btreedelone(&ast_31, free_asn), ft_btreedelone(&ast_32, free_asn), ft_btreedelone(&ast_33, free_asn), ft_btreedelone(&ast_34, free_asn), ft_btreedelone(&ast_35, free_asn), 1);
	t_token tab_37[]={{UNSET,"c4",0,0}, {0,0,0,0}};
	t_btree *ast_37 = create_ast_node(tab_37);
	if (!ast_37)
		return (ft_btreedelone(&ast_30, free_asn),ft_btreedelone(&ast_31, free_asn), ft_btreedelone(&ast_32, free_asn), ft_btreedelone(&ast_33, free_asn), ft_btreedelone(&ast_34, free_asn), ft_btreedelone(&ast_35, free_asn), ft_btreedelone(&ast_36, free_asn), 1);
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
	// =[  ]====================================================================
	print_title("C| PARENTHESIS");
	// -[ 	 ]------------------------------------------------------------------
	print_subtitle("Imbrication:NO PRIORITY CHANGES");
	char *str_5="(((c1&&c2)||c3)&&c4)";
	// CREATE NODES
	t_token tab_40[]={{UNSET,"c1",0,3}, {0,0,0,0}};
	t_btree *ast_40 = create_ast_node(tab_40);
	if (!ast_40)
		return (1);
	t_token tab_41[]={{OPA,"&&",0,3}, {0,0,0,0}};
	t_btree *ast_41 = create_ast_node(tab_41);
	if (!ast_41)
		return (ft_btreedelone(&ast_40, free_asn), 1);
	t_token tab_42[]={{UNSET,"c2",0,3}, {0,0,0,0}};
	t_btree *ast_42 = create_ast_node(tab_42);
	if (!ast_42)
		return (ft_btreedelone(&ast_40, free_asn),ft_btreedelone(&ast_41, free_asn), 1);
	t_token tab_43[]={{OPO,"||",0,2}, {0,0,0,0}};
	t_btree *ast_43 = create_ast_node(tab_43);
	if (!ast_43)
		return (ft_btreedelone(&ast_40, free_asn),ft_btreedelone(&ast_41, free_asn),ft_btreedelone(&ast_42, free_asn), 1);
	t_token tab_44[]={{UNSET,"c3",0,2}, {0,0,0,0}};
	t_btree *ast_44 = create_ast_node(tab_44);
	if (!ast_44)
		return (ft_btreedelone(&ast_40, free_asn),ft_btreedelone(&ast_41, free_asn),ft_btreedelone(&ast_42, free_asn),ft_btreedelone(&ast_43, free_asn), 1);
	t_token tab_45[]={{OPA,"&&",0,1}, {0,0,0,0}};
	t_btree *ast_45 = create_ast_node(tab_45);
	if (!ast_45)
		return (ft_btreedelone(&ast_40, free_asn),ft_btreedelone(&ast_41, free_asn),ft_btreedelone(&ast_42, free_asn),ft_btreedelone(&ast_43, free_asn),ft_btreedelone(&ast_44, free_asn), 1);
	t_token tab_46[]={{UNSET,"c4",0,1}, {0,0,0,0}};
	t_btree *ast_46 = create_ast_node(tab_46);
	if (!ast_46)
		return (ft_btreedelone(&ast_40, free_asn),ft_btreedelone(&ast_41, free_asn),ft_btreedelone(&ast_42, free_asn),ft_btreedelone(&ast_43, free_asn),ft_btreedelone(&ast_44, free_asn),ft_btreedelone(&ast_45, free_asn), 1);
	//ATTACHED NODES
	ast_41->left = ast_40;
	ast_41->right = ast_43;
	ast_43->left = ast_42;
	ast_43->right = ast_45;
	ast_45->left = ast_44;
	ast_45->right = ast_46;
	// RUN TEST
	nb_err += test(str_5, &ast_41, ev);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Simple:CHANGE PRIORITY");
	char *str_6="(c1&&c2)||(c3&&c4)";
	// CREATE NODES
	t_token tab_50[]={{UNSET,"c1",0,1}, {0,0,0,0}};
	t_btree *ast_50 = create_ast_node(tab_50);
	if (!ast_50)
		return (1);
	t_token tab_51[]={{OPA,"&&",0,1}, {0,0,0,0}};
	t_btree *ast_51 = create_ast_node(tab_51);
	if (!ast_51)
		return (ft_btreedelone(&ast_50, free_asn), 1);
	t_token tab_52[]={{UNSET,"c2",0,1}, {0,0,0,0}};
	t_btree *ast_52 = create_ast_node(tab_52);
	if (!ast_52)
		return (ft_btreedelone(&ast_50, free_asn),ft_btreedelone(&ast_51, free_asn), 1);
	t_token tab_53[]={{OPO,"||",0,0}, {0,0,0,0}};
	t_btree *ast_53 = create_ast_node(tab_53);
	if (!ast_53)
		return (ft_btreedelone(&ast_50, free_asn),ft_btreedelone(&ast_51, free_asn),ft_btreedelone(&ast_52, free_asn), 1);
	t_token tab_54[]={{UNSET,"c3",0,1}, {0,0,0,0}};
	t_btree *ast_54 = create_ast_node(tab_54);
	if (!ast_54)
		return (ft_btreedelone(&ast_50, free_asn),ft_btreedelone(&ast_51, free_asn),ft_btreedelone(&ast_52, free_asn),ft_btreedelone(&ast_53, free_asn), 1);
	t_token tab_55[]={{OPA,"&&",0,1}, {0,0,0,0}};
	t_btree *ast_55 = create_ast_node(tab_55);
	if (!ast_55)
		return (ft_btreedelone(&ast_50, free_asn),ft_btreedelone(&ast_51, free_asn),ft_btreedelone(&ast_52, free_asn),ft_btreedelone(&ast_53, free_asn),ft_btreedelone(&ast_54, free_asn), 1);
	t_token tab_56[]={{UNSET,"c4",0,1}, {0,0,0,0}};
	t_btree *ast_56 = create_ast_node(tab_56);
	if (!ast_56)
		return (ft_btreedelone(&ast_50, free_asn),ft_btreedelone(&ast_51, free_asn),ft_btreedelone(&ast_52, free_asn),ft_btreedelone(&ast_53, free_asn),ft_btreedelone(&ast_54, free_asn),ft_btreedelone(&ast_55, free_asn), 1);
	//ATTACHED NODES
	ast_53->left = ast_51;
	ast_53->right = ast_55;
	ast_51->left = ast_50;
	ast_51->right = ast_52;
	ast_55->left = ast_54;
	ast_55->right = ast_56;
	// RUN TEST
	nb_err += test(str_6, &ast_53, ev);
	print_sep(S2);
	// -[  ]--------------------------------------------------------------------
	print_subtitle("Imbrication:No Priority Changes");
	//PARENTHESIS123444444444444444444433332223444444443333321112222222210
	char *str_7="((((echo \"inside f1\")>f1)&&((<f1 cat) >f2))&&(<f2 cat))";
	/*
	 *                                                                                 60:{OPA, "&&", 0, 2}
	 *                                  61:{RRS,">"->"f1",0,3}<----------------------------------| |----------------------------->63:{OPA, "&&", 0, 1}
	 *62:{UNSET,"echo"->"\"inside f1\"",0,4}<------| |------>|XX|                                       64:{RLS,"<"->"f1",0,4}<------------| |-------->67:{RLS,"<"->"f2",0,2}
	 *|XX|<--------------| |-------------->|XX|           |XX|<>|XX|                  65:{RRS,">"->"f2",0,3}<------| |------>|XX|      68:{UNSET,"cat",0,2}<------| |------>|XX|
	 *                                                                66:{UNSET,"cat",0,4}<------| |------>|XX|           |XX|<>|XX|   |XX|<------||----->|XX|           |XX|<>|XX|
	 */
	// CREATE NODES
	t_token tab_60[]={{OPA,"&&",0,2}, {0,0,0,0}};
	t_btree *ast_60 = create_ast_node(tab_60);
	if (!ast_60)
		return (1);
	t_token tab_61[]={{RRS,">",0,3}, {UNSET,"f1",0,3}, {1,0,0,0}};
	t_btree *ast_61 = create_ast_node(tab_61);
	if (!ast_61)
		return (ft_btreedelone(&ast_60, free_asn), 1);
	t_token tab_62[]={{UNSET,"echo",0,4}, {UNSET,"\"inside f1\"",1,4}, {0,0,0,0}};
	t_btree *ast_62 = create_ast_node(tab_62);
	if (!ast_62)
		return (ft_btreedelone(&ast_60, free_asn),ft_btreedelone(&ast_61, free_asn), 1);
	t_token tab_63[]={{OPA,"&&",0,1}, {0,0,0,0}};
	t_btree *ast_63 = create_ast_node(tab_63);
	if (!ast_63)
		return (ft_btreedelone(&ast_60, free_asn),ft_btreedelone(&ast_61, free_asn),ft_btreedelone(&ast_62, free_asn), 1);
	t_token tab_64[]={{RLS,"<",0,4}, {UNSET,"f1",0,4}, {0,0,0,0}};
	t_btree *ast_64 = create_ast_node(tab_64);
	if (!ast_64)
		return (ft_btreedelone(&ast_60, free_asn),ft_btreedelone(&ast_61, free_asn),ft_btreedelone(&ast_62, free_asn),ft_btreedelone(&ast_63, free_asn), 1);
	t_token tab_65[]={{RRS,">",0,3}, {UNSET,"f2",0,3}, {0,0,0,0}};
	t_btree *ast_65 = create_ast_node(tab_65);
	if (!ast_65)
		return (ft_btreedelone(&ast_60, free_asn),ft_btreedelone(&ast_61, free_asn),ft_btreedelone(&ast_62, free_asn),ft_btreedelone(&ast_63, free_asn),ft_btreedelone(&ast_64, free_asn), 1);
	t_token tab_66[]={{UNSET,"cat",0,4}, {0,0,0,0}};
	t_btree *ast_66 = create_ast_node(tab_66);
	if (!ast_66)
		return (ft_btreedelone(&ast_60, free_asn),ft_btreedelone(&ast_61, free_asn),ft_btreedelone(&ast_62, free_asn),ft_btreedelone(&ast_63, free_asn),ft_btreedelone(&ast_64, free_asn),ft_btreedelone(&ast_65, free_asn), 1);
	t_token tab_67[]={{RLS,"<",0,2}, {UNSET,"f2",0,2}, {0,0,0,0}};
	t_btree *ast_67 = create_ast_node(tab_67);
	if (!ast_67)
		return (ft_btreedelone(&ast_60, free_asn),ft_btreedelone(&ast_61, free_asn),ft_btreedelone(&ast_62, free_asn),ft_btreedelone(&ast_63, free_asn),ft_btreedelone(&ast_64, free_asn),ft_btreedelone(&ast_65, free_asn),ft_btreedelone(&ast_66, free_asn), 1);
	t_token tab_68[]={{UNSET,"cat",0,2}, {0,0,0,0}};
	t_btree *ast_68 = create_ast_node(tab_68);
	if (!ast_68)
		return (ft_btreedelone(&ast_60, free_asn),ft_btreedelone(&ast_61, free_asn),ft_btreedelone(&ast_62, free_asn),ft_btreedelone(&ast_63, free_asn),ft_btreedelone(&ast_64, free_asn),ft_btreedelone(&ast_65, free_asn),ft_btreedelone(&ast_66, free_asn),ft_btreedelone(&ast_67, free_asn), 1);
	//ATTACHED NODES
	ast_60->left = ast_61;
	ast_60->right = ast_63;
	ast_61->left = ast_62;
	ast_63->left = ast_64;
	ast_63->right = ast_67;
	ast_64->left = ast_65;
	ast_65->left = ast_66;
	ast_67->left = ast_68;
	// RUN TEST
	nb_err += test(str_7, &ast_60, ev);
	print_sep(S2);
	print_sep(S1);
	return (nb_err);
}

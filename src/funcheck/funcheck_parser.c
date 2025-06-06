// test parser()
// CASES:
//   ⭙ : unknown
//   ✔ : pass
//   ✘ : fail
//	 - | unitest | funcheck | examples                                                                     |
//   -----------------------| A| SINGLE NODE                                                               |
//	 - |    ✔    |     ✔    | str_a0="cmd"                                                                 |
//	 - |    ✔    |     ✔    | str_a1="<f1"                                                                 |
//   -----------------------| B| MULTIPLE NODES                                                            |
//	 - |    ✔    |     ✔    | str_b0=" cmd1 &&cmd2||cmd3 "                                                 |
//	 - |    ✔    |     ✔    | str_b1=" cmd1 &&cmd2||cmd3&& cmd4 "                                          |
//	 - |    ✔    |     ✔    | str_b2="<f0 <f1 cm <f3 ar"                                                   |
//	 - |    ✔    |     ✔    | str_b3=" cmd1 | cmd2|cmd3| cmd4 "                                            |
//	 - |    ✔    |     ✔    | str_b4="c1<f1 a1|c2|c3&&c4"                                                  |
//   -----------------------| C| PARENTHESIS - LOGIC OPERATOR                                              |
//	 - |    ✔    |     ✘    | str_c0="c1&&(c2||c3)"                                                 CHANGES|
//	 - |    ✔    |     ✘    | str_c1="c1&&(c2||c3)&&c4"                                             CHANGES|
//	 - |    ✔    |     ✘    | str_c2="c1&&(c2||c3&&c4)"                                             CHANGES|
//	 - |    ✔    |     ✘    | str_c3="c1&&c2||(c3&&c4)"                                             CHANGES|
//	 - |    ✔    |     ✘    | str_c4="(c1&&c2)||(c3&&c4)"                                           CHANGES|
//   -----------------------| D| PARENTHESIS - LOGIC OPERATOR IMBRICATION                                  |
//	 - |    ✔    |     ✘    | str_d0="((c1&&c2)||c3)&&c4"                                        NO_CHANGES|
//	 - |    ✔    |     ✘    | str_d1="(((c1&&c2)||c3)&&c4)"                                      NO_CHANGES|
//	 - |    ✔    |     ✘    | str_d2="( (((c1&&c2)||c3)&&c4) )"                                  NO_CHANGES|
//	 - |    ✔    |     ✘    | str_d3="(( (((c1&&c2)||c3)&&c4)) )"                                NO_CHANGES|
//	 - |    ✔    |     ✘    | str_d4="((c1&&c2)||(c3&&c4))"                                         CHANGES|
//	 - |    ✔    |     ✘    | str_d5="((c1&&c2||c3)&&c4)||(c5&&(c6||c7&&c8))"                       CHANGES|
//	 -----------------------| E| PARENTHESIS - REDIR and UNSET                                             |
//	 - |    ✔    |     ✔    | str_e0="(c1)>f1>f2>f3                                              NO_CHANGES|
//	 - |    ✔    |     ✔    | str_e1="(c1>f1)>f2>f3                                                 CHANGES|
//	 - |    ✔    |     ✔    | str_e2="(c1>f1>f2)>f3                                                 CHANGES|
//	 -----------------------| F| PARENTHESIS - REDIR and UNSET IMBRICATION                                 |
//	 - |    ✔    |     ✔    | str_f0="((c1)>f1)>f2>f3                                               CHANGES|
//	 - |    ✔    |     ✔    | str_f1="((c1)>f1>f2)>f3                                               CHANGES|
//	 - |    ✔    |     ✔    | str_f2="((c1)>f1>f2>f3)                                            NO_CHANGES|
//	 - |    ✔    |     ✔    | str_f3="(((c1)>f1)>f2)>f3                                             CHANGES|
//	 - |    ✔    |     ✔    | str_f4="(((c1)>f1)>f2>f3)                                             CHANGES|
//	 - |    ✔    |     ✔    | str_f5="((((c1)>f1)>f2)>f3)                                           CHANGES|
//	 -----------------------| G| MULTIPLE NESTED PAR                                                       |
//   - |    ✔    |     ✘    | str_g0="( ( c2 ) )"                                                NO_CHANGES|
//   - |    ✔    |     ✘    | str_g1="(( ( c3 )) )"                                              NO_CHANGES|
//   - |    ✔    |     ✘    | str_g2="( (( c3 ) )) "                                             NO_CHANGES|
//   - |    ✔    |     ✘    | str_g3=" ( (( ( ( c5 )) ) )) "                                     NO_CHANGES|
//	 -----------------------| H| COMBOS                                                                    |
//	 - |    ✔    |     ✘    | str_h00="((((echo \"inside f1\")>f1)&&((<f1 cat) >f2))&&(<f2 cat))"NO_CHANGES|
//   - |    ✔    |     ✘    | str_h10="((((c1)>f1)&&((<f2 c2) >f3))&&(<f4 c4))"                  NO_CHANGES|
// =============================================================================
 
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
		return (0);
	return (1);
}

int	compare_token(t_token *a, t_token *b)
{
	if (!compare_int(a->type, b->type))
		return (fprintf(stdout, CR"a->type:%d != b->type:%d <<<< "CE, a->type, b->type), 0);
	if (strcmp(a->str, b->str) != 0)
		return (fprintf(stdout, CR"a->str:%s != b->str:%s <<<< "CE, a->str, b->str), 0);
	if (!compare_int(a->parenthesis, b->parenthesis))
		return (fprintf(stdout, CR"a->par:%d != b->par:%d <<<< "CE, a->parenthesis, b->parenthesis), 0);
	return (1);
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
			return (1);
		return (0);
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
		return (fprintf(stdout, CR"Diff. Size a_len=%d != b_len=%d <<<< "CE, a_len, b_len),0);
	// Check each node are the same
	int	count_node=0;
	a_act = a;
	b_act = b;
	while (a_act && b_act)
	{
		if (!compare_token(a_act->content, b_act->content))
			return (fprintf(stdout, CR"ast_node:%d->diff token <<<< "CE, count_node), 0);
		a_act = a_act->next;
		b_act = b_act->next;
		count_node++;
	}
	return (1);
}

int compare_ptr(void *ptr1, void *ptr2)
{
	if (ptr1 != ptr2)
		return (0);
	return (1);
}
int compare_asn(t_asn *a, t_asn *b)
{
	if (!a || !b)
	{
		if (!a && !b)
			return (0);
		return (1);
	}
	if (!compare_tdlist(a->raw, b->raw))
		return (fprintf(stdout, CR"Wrong Raw\n"CE), 1);
	if (!compare_int(a->type, b->type))
		return (fprintf(stdout, CR"Wrong Type:%d != %d\n"CE, a->type, b->type), 1);
	if (!compare_ptr((void *)a->print_fun, (void*)b->print_fun))
		return (fprintf(stdout, CR"Wrong print_fun\n"CE), 1);
	if (!compare_ptr((void *)a->free_fun, (void *)b->free_fun))
		return (fprintf(stdout, CR"Wrong free_fun\n"CE), 1);
	return (0);
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
	// Print test header
	int print_sofar = printf("%s(\"", f_name);
	printf(CB);
	print_sofar += printf("%s",str);
	printf(CE);
	print_sofar += printf("\")");
	if (str)
	{
		int c = count_char_in_str('\t', str);
		if (c)
			print_sofar+=c*4;
	}
	printntime(S3, LEN - print_sofar);
	printf("\n");
	// PRINT
	printf("btree_res=\n");
	fflush(stdout);
	ft_btreeprint(res, print_first_four_char, 4);
	printf("\n");
	fflush(stdout);
	// LEXING
	lexer(str, &data);
	if (!data->tok_lst)
		write(1, "\n", 1);
	// PARSER
	parser(&data);
	if (!data->ast)
		write(1, "\n", 1);
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

	// =[  ]====================================================================
	print_title("N| FAIL COMMANDS-->lexing");
	//TODO can not be tested-->if null, lexer panic and exit
	//print_title("N0| NULL CASES");
	//nb_err += test(NULL, NULL, ev);
	//print_sep(S1);
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("N1|SYNTAX ERRORS");
	//nb_err += test("cmd>", NULL, ev);
	//nb_err += test("()", NULL, ev);
	//print_sep(S2);
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("N2|NOT SUPPORTED OPERATORS");
	//nb_err += test("<(cmd)", NULL, ev);
	//nb_err += test(">(cmd)", NULL, ev);
	//nb_err += test("((((c1&&c2)||c3)&&c4))", NULL, ev);
	//print_sep(S2);
	//print_sep(S1);
	//// =[ 	 ]==================================================================
	//print_title("A| BTREE WITH ONE NODE:parsing");
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("A0|Simple node == UNSET");
	//char *str_a0="cmd";
	//t_token t0[] = {{UNSET,"cmd",0},{0,0,0}};
	//t_btree *ast0 = create_ast_node(t0);
	//if (!ast0)
	//	return (1);
	//nb_err += test(str_a0, &ast0, ev);
	//print_sep(S2);
	//// -[ 	 ]------------------------------------------------------------------
	//print_subtitle("A1|Simple node == REDIR");
	//char *str_a1="<f1";
	//t_token t1[] = {{RLS,"<",0}, {UNSET,"f1",0}, {0,0,0}};
	//t_btree *ast1 = create_ast_node(t1);
	//if (!ast1)
	//	return (1);
	//nb_err += test(str_a1, &ast1, ev);
	//print_sep(S2);
	//print_sep(S1);
	//// =[  ]====================================================================
	//print_title("B| BTREE WITH MULTIPLES NODES:parsing");
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("B0|Only UNSET and OPA, OPO");
	//char *str_b0=" cmd1 &&cmd2||cmd3 ";
	///*
	// *                                  00:{OPO,"||",0}
	// *                    01:{OPA,"&&",0}<------| |---->02:{UNSET, "cmd3", 0}                              
	// * 03:{UNSET,"cmd1",2}<------| |---->04:{UNSET, "cmd2", 0}                                              
	// */
	//// CREATE NODES
	//t_token tab_b00[]={{OPO,"||",0}, {0,0,0}};
	//t_btree *ast_b00 = create_ast_node(tab_b00);
	//if (!ast_b00)
	//	return (1);
	//t_token tab_b01[]={{OPA,"&&",0}, {0,0,0}};
	//t_btree *ast_b01 = create_ast_node(tab_b01);
	//if (!ast_b01)
	//	return (ft_btreedelone(&ast_b00, free_asn), 1);
	//t_token tab_b02[]={{UNSET,"cmd3",0}, {0,0,0}};
	//t_btree *ast_b02 = create_ast_node(tab_b02);
	//if (!ast_b02)
	//	return (ft_btreedelone(&ast_b00, free_asn),ft_btreedelone(&ast_b01, free_asn), 1);
	//t_token tab_b03[]={{UNSET,"cmd1",0}, {0,0,0}};
	//t_btree *ast_b03 = create_ast_node(tab_b03);
	//if (!ast_b03)
	//	return (ft_btreedelone(&ast_b00, free_asn),ft_btreedelone(&ast_b01, free_asn),ft_btreedelone(&ast_b02, free_asn), 1);
	//t_token tab_b04[]={{UNSET,"cmd2",0}, {0,0,0}};
	//t_btree *ast_b04 = create_ast_node(tab_b04);
	//if (!ast_b04)
	//	return (ft_btreedelone(&ast_b00, free_asn),ft_btreedelone(&ast_b01, free_asn),ft_btreedelone(&ast_b02, free_asn),ft_btreedelone(&ast_b03, free_asn), 1);
	////ATTACHED NODES
	//ast_b00->left = ast_b01;
	//ast_b00->right= ast_b02;
	//ast_b01->left = ast_b03;
	//ast_b01->right= ast_b04;
	//// RUN TEST
	//nb_err += test(str_b0, &ast_b00, ev);
	//print_sep(S2);
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("B1|Only UNSET and OPA, OPO");
	//char *str_b1=" cmd1 &&cmd2||cmd3&& cmd4 ";
	///*
	// *                                                                          10:{OPA, "&&", 0}
	// *                                  11:{OPO,"||",0}<----------------------------------| |----------------------------->12:{UNSET, "cmd4", 0}
	// *                    13:{OPA,"&&",0}<------| |---->14:{UNSET, "cmd3", 0}                              
	// * 15:{UNSET,"cmd1",2}<------| |---->16:{UNSET, "cmd2", 0}                                              
	// */
	//// CREATE NODES
	//t_token tab_b10[]={{OPA,"&&",0}, {0,0,0}};
	//t_btree *ast_b10 = create_ast_node(tab_b10);
	//if (!ast_b10)
	//	return (1);
	//t_token tab_b11[]={{OPO,"||",0}, {0,0,0}};
	//t_btree *ast_b11 = create_ast_node(tab_b11);
	//if (!ast_b11)
	//	return (ft_btreedelone(&ast_b10, free_asn), 1);
	//t_token tab_b12[]={{UNSET,"cmd4",0}, {0,0,0}};
	//t_btree *ast_b12 = create_ast_node(tab_b12);
	//if (!ast_b12)
	//	return (ft_btreedelone(&ast_b10, free_asn),ft_btreedelone(&ast_b11, free_asn), 1);
	//t_token tab_b13[]={{OPA,"&&",0}, {0,0,0}};
	//t_btree *ast_b13 = create_ast_node(tab_b13);
	//if (!ast_b13)
	//	return (ft_btreedelone(&ast_b10, free_asn),ft_btreedelone(&ast_b11, free_asn),ft_btreedelone(&ast_b12, free_asn), 1);
	//t_token tab_b14[]={{UNSET,"cmd3",0}, {0,0,0}};
	//t_btree *ast_b14 = create_ast_node(tab_b14);
	//if (!ast_b14)
	//	return (ft_btreedelone(&ast_b10, free_asn),ft_btreedelone(&ast_b11, free_asn),ft_btreedelone(&ast_b12, free_asn),ft_btreedelone(&ast_b13, free_asn), 1);
	//t_token tab_b15[]={{UNSET,"cmd1",0}, {0,0,0}};
	//t_btree *ast_b15 = create_ast_node(tab_b15);
	//if (!ast_b15)
	//	return (ft_btreedelone(&ast_b10, free_asn),ft_btreedelone(&ast_b11, free_asn),ft_btreedelone(&ast_b12, free_asn),ft_btreedelone(&ast_b13, free_asn),ft_btreedelone(&ast_b14, free_asn), 1);
	//t_token tab_b16[]={{UNSET,"cmd2",0}, {0,0,0}};
	//t_btree *ast_b16 = create_ast_node(tab_b16);
	//if (!ast_b16)
	//	return (ft_btreedelone(&ast_b10, free_asn),ft_btreedelone(&ast_b11, free_asn),ft_btreedelone(&ast_b12, free_asn),ft_btreedelone(&ast_b13, free_asn),ft_btreedelone(&ast_b14, free_asn),ft_btreedelone(&ast_b15, free_asn), 1);
	////ATTACHED NODES
	//ast_b10->left = ast_b11;
	//ast_b10->right= ast_b12;
	//ast_b11->left = ast_b13;
	//ast_b11->right= ast_b14;
	//ast_b13->left = ast_b15;
	//ast_b13->right= ast_b16;
	//// RUN TEST
	//nb_err += test(str_b1, &ast_b10, ev);
	//print_sep(S2);
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("B2|Only UNSET and REDIR");
	//char *str_b2="<f0 <f1 cm <f3 ar";
	//// CREATE NODES
	//t_token tab_b20[]={{RLS,"<",0}, {UNSET,"f0",0}, {0,0,0}};
	//t_btree *ast_b20 = create_ast_node(tab_b20);
	//if (!ast_b20)
	//	return (1);
	//t_token tab_b21[]={{RLS,"<",0}, {UNSET,"f1",0}, {0,0,0}};
	//t_btree *ast_b21 = create_ast_node(tab_b21);
	//if (!ast_b21)
	//	return (ft_btreedelone(&ast_b20, free_asn), 1);
	//t_token tab_b22[]={{UNSET,"cm",0},{UNSET,"ar",0}, {0,0,0}};
	//t_btree *ast_b22 = create_ast_node(tab_b22);
	//if (!ast_b22)
	//	return (ft_btreedelone(&ast_b20, free_asn),ft_btreedelone(&ast_b21, free_asn), 1);
	//t_token tab_b23[]={{RLS,"<",0}, {UNSET,"f3",0}, {0,0,0}};
	//t_btree *ast_b23 = create_ast_node(tab_b23);
	//if (!ast_b23)
	//	return (ft_btreedelone(&ast_b20, free_asn),ft_btreedelone(&ast_b21, free_asn),ft_btreedelone(&ast_b22, free_asn), 1);
	////ATTACHED NODES
	//ast_b20->left = ast_b21;
	//ast_b21->left = ast_b23;
	//ast_b23->left = ast_b22;
	//// RUN TEST
	//nb_err += test(str_b2, &ast_b20, ev);
	//print_sep(S2);
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("B3|Only PIP");
	///*
	// *                                                   30:{PIP, "|", 0}
    // *              31:{UNSET,"cmd1",2}----------------------------┘  └----------------------------32:{PIP,"|",0}
    // *                                                                   33:{UNSET, "cmd2", 0}------------┘  └------------34:{PIP,"|",0}
    // *                                                                                                 35:{UNSET, "cmd3", 0}----┘  └----35:{UNSET, "cmd4", 0}
	// */
	//char *str_b3=" cmd1 | cmd2|cmd3| cmd4 ";
	//// CREATE NODES
	//t_token tab_b30[]={{PIP,"|",0}, {0,0,0}};
	//t_btree *ast_b30 = create_ast_node(tab_b30);
	//if (!ast_b30)
	//	return (1);
	//t_token tab_b31[]={{UNSET,"cmd1",0}, {0,0,0}};
	//t_btree *ast_b31 = create_ast_node(tab_b31);
	//if (!ast_b31)
	//	return (ft_btreedelone(&ast_b30, free_asn), 1);
	//t_token tab_b32[]={{PIP,"|",0}, {0,0,0}};
	//t_btree *ast_b32 = create_ast_node(tab_b32);
	//if (!ast_b32)
	//	return (ft_btreedelone(&ast_b30, free_asn),ft_btreedelone(&ast_b31, free_asn), 1);
	//t_token tab_b33[]={{UNSET,"cmd2",0}, {0,0,0}};
	//t_btree *ast_b33 = create_ast_node(tab_b33);
	//if (!ast_b33)
	//	return (ft_btreedelone(&ast_b30, free_asn),ft_btreedelone(&ast_b31, free_asn),ft_btreedelone(&ast_b32, free_asn), 1);
	//t_token tab_b34[]={{PIP,"|",0}, {0,0,0}};
	//t_btree *ast_b34 = create_ast_node(tab_b34);
	//if (!ast_b34)
	//	return (ft_btreedelone(&ast_b30, free_asn),ft_btreedelone(&ast_b31, free_asn),ft_btreedelone(&ast_b33, free_asn),ft_btreedelone(&ast_b33, free_asn), 1);
	//t_token tab_b35[]={{UNSET,"cmd3",0}, {0,0,0}};
	//t_btree *ast_b35 = create_ast_node(tab_b35);
	//if (!ast_b35)
	//	return (ft_btreedelone(&ast_b30, free_asn),ft_btreedelone(&ast_b31, free_asn),ft_btreedelone(&ast_b32, free_asn),ft_btreedelone(&ast_b34, free_asn),ft_btreedelone(&ast_b34, free_asn), 1);
	//t_token tab_b36[]={{UNSET,"cmd4",0}, {0,0,0}};
	//t_btree *ast_b36 = create_ast_node(tab_b36);
	//if (!ast_b36)
	//	return (ft_btreedelone(&ast_b30, free_asn),ft_btreedelone(&ast_b31, free_asn),ft_btreedelone(&ast_b32, free_asn),ft_btreedelone(&ast_b33, free_asn),ft_btreedelone(&ast_b35, free_asn),ft_btreedelone(&ast_b35, free_asn), 1);
	////ATTACHED NODES
	//ast_b30->left = ast_b31;
	//ast_b30->right = ast_b32;
	//ast_b32->left = ast_b33;
	//ast_b32->right = ast_b34;
	//ast_b34->left = ast_b35;
	//ast_b34->right = ast_b36;
	//// RUN TEST
	//nb_err += test(str_b3, &ast_b30, ev);
	//print_sep(S2);
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("B4|Combos");
	//char *str_b4="c1<f1 a1|c2|c3&&c4";
	///*
	// *                                                                           40:{OPA, "&&", 0}
    // *                                        41:{PIP,"|",0}----------------------------┘  └----------------------------42:{UNSET, "c4", 0}
    // *                   43:{RLS,"<f1",0}------------┘  └------------44:{PIP,"|",0}
    // *   45:{UNSET,"c1a1",2}----┘  └----|XX|         46:{UNSET, "c2", 0}----┘  └----47:{UNSET, "c3", 0}
	// */
	//// CREATE NODES
	//t_token tab_b40[]={{OPA,"&&",0}, {0,0,0}};
	//t_btree *ast_b40 = create_ast_node(tab_b40);
	//if (!ast_b40)
	//	return (1);
	//t_token tab_b41[]={{PIP,"|",0}, {0,0,0}};
	//t_btree *ast_b41 = create_ast_node(tab_b41);
	//if (!ast_b41)
	//	return (ft_btreedelone(&ast_b40, free_asn), 1);
	//t_token tab_b42[]={{UNSET,"c4",0}, {0,0,0}};
	//t_btree *ast_b42 = create_ast_node(tab_b42);
	//if (!ast_b42)
	//	return (ft_btreedelone(&ast_b40, free_asn),ft_btreedelone(&ast_b41, free_asn), 1);
	//t_token tab_b43[]={{RLS,"<",0}, {UNSET,"f1",0}, {0,0,0}};
	//t_btree *ast_b43 = create_ast_node(tab_b43);
	//if (!ast_b43)
	//	return (ft_btreedelone(&ast_b40, free_asn),ft_btreedelone(&ast_b41, free_asn), ft_btreedelone(&ast_b42, free_asn), 1);
	//t_token tab_b44[]={{PIP,"|",0}, {0,0,0}};
	//t_btree *ast_b44 = create_ast_node(tab_b44);
	//if (!ast_b44)
	//	return (ft_btreedelone(&ast_b40, free_asn),ft_btreedelone(&ast_b41, free_asn), ft_btreedelone(&ast_b42, free_asn), ft_btreedelone(&ast_b43, free_asn), 1);
	//t_token tab_b45[]={{UNSET,"c1",0},{UNSET,"a1",0}, {0,0,0}};
	//t_btree *ast_b45 = create_ast_node(tab_b45);
	//if (!ast_b45)
	//	return (ft_btreedelone(&ast_b40, free_asn),ft_btreedelone(&ast_b41, free_asn), ft_btreedelone(&ast_b42, free_asn), ft_btreedelone(&ast_b43, free_asn), ft_btreedelone(&ast_b44, free_asn), 1);
	//t_token tab_b46[]={{UNSET,"c2",0}, {0,0,0}};
	//t_btree *ast_b46 = create_ast_node(tab_b46);
	//if (!ast_b46)
	//	return (ft_btreedelone(&ast_b40, free_asn),ft_btreedelone(&ast_b41, free_asn), ft_btreedelone(&ast_b42, free_asn), ft_btreedelone(&ast_b43, free_asn), ft_btreedelone(&ast_b44, free_asn), ft_btreedelone(&ast_b45, free_asn), 1);
	//t_token tab_b47[]={{UNSET,"c3",0}, {0,0,0}};
	//t_btree *ast_b47 = create_ast_node(tab_b47);
	//if (!ast_b47)
	//	return (ft_btreedelone(&ast_b40, free_asn),ft_btreedelone(&ast_b41, free_asn), ft_btreedelone(&ast_b42, free_asn), ft_btreedelone(&ast_b43, free_asn), ft_btreedelone(&ast_b44, free_asn), ft_btreedelone(&ast_b45, free_asn), ft_btreedelone(&ast_b46, free_asn), 1);
	////ATTACHED NODES
	//ast_b40->left = ast_b41;
	//ast_b40->right = ast_b42;
	//ast_b41->left = ast_b43;
	//ast_b41->right = ast_b44;
	//ast_b44->left = ast_b46;
	//ast_b44->right = ast_b47;
	//ast_b43->left = ast_b45;
	//// RUN TEST
	//nb_err += test(str_b4, &ast_b40, ev);
	//print_sep(S2);
	//print_sep(S1);
	//// =[  ]====================================================================
	//print_title("C| PARENTHESIS - NO IMBRICATION");
	//// -[ 	 ]------------------------------------------------------------------
	//print_subtitle("C0|SIMPLE:CHANGES PRIORITY");
	//char *str_c0="c1&&(c2||c3)";
	///*
	// *                               00:{OPA,"&&",0}
	// *           01:{UNSET,"c1",0}<------------| |---->02:{OPO, "||", 1}                              
	// *                                   03:{UNSET,"c2",1}<------| |---->04:{UNSET, "c3", 1}                                              
	// */
	//// CREATE NODES
	//t_token tab_c00[]={{OPA,"&&",0}, {0,0,0}};
	//t_btree *ast_c00 = create_ast_node(tab_c00);
	//if (!ast_c00)
	//	return (1);
	//t_token tab_c01[]={{UNSET,"c1",0}, {0,0,0}};
	//t_btree *ast_c01 = create_ast_node(tab_c01);
	//if (!ast_c01)
	//	return (ft_btreedelone(&ast_c00, free_asn), 1);
	//t_token tab_c02[]={{OPO,"||",1}, {0,0,0}};
	//t_btree *ast_c02 = create_ast_node(tab_c02);
	//if (!ast_c02)
	//	return (ft_btreedelone(&ast_c00, free_asn),ft_btreedelone(&ast_c01, free_asn), 1);
	//t_token tab_c03[]={{UNSET,"c2",1}, {0,0,0}};
	//t_btree *ast_c03 = create_ast_node(tab_c03);
	//if (!ast_c03)
	//	return (ft_btreedelone(&ast_c00, free_asn),ft_btreedelone(&ast_c01, free_asn),ft_btreedelone(&ast_c02, free_asn), 1);
	//t_token tab_c04[]={{UNSET,"c3",1}, {0,0,0}};
	//t_btree *ast_c04 = create_ast_node(tab_c04);
	//if (!ast_c04)
	//	return (ft_btreedelone(&ast_c00, free_asn),ft_btreedelone(&ast_c01, free_asn),ft_btreedelone(&ast_c02, free_asn),ft_btreedelone(&ast_c03, free_asn), 1);
	////ATTACHED NODES
	//ast_c00->left = ast_c01;
	//ast_c00->right = ast_c02;
	//ast_c02->left = ast_c03;
	//ast_c02->right = ast_c04;
	//// RUN TEST
	//nb_err += test(str_c0, &ast_c00, ev);

	//print_sep(S2);
	//// -[ 	 ]------------------------------------------------------------------
	//print_subtitle("C1|SIMPLE:CHANGES PRIORITY");
	//char *str_c1="c1&&(c2||c3)&&c4";
	///*
	// *                                       10:{OPA,"&&",0}
	// *                  11:{OPA,"&&",0}<------------| |---->12:{UNSET, "c4", 0}                              
	// * 13:{UNSET,"c1",0}<------| |---->14:{OPO, "||", 1}                                              
	// *                  15:{UNSET,"c2",1}<------| |---->16:{UNSET, "c3", 1}                                              
	// */
	//// CREATE NODES
	//t_token tab_c10[]={{OPA,"&&",0}, {0,0,0}};
	//t_btree *ast_c10 = create_ast_node(tab_c10);
	//if (!ast_c10)
	//	return (1);
	//t_token tab_c11[]={{OPA,"&&",0}, {0,0,0}};
	//t_btree *ast_c11 = create_ast_node(tab_c11);
	//if (!ast_c11)
	//	return (ft_btreedelone(&ast_c10, free_asn), 1);
	//t_token tab_c12[]={{UNSET,"c4",0}, {0,0,0}};
	//t_btree *ast_c12 = create_ast_node(tab_c12);
	//if (!ast_c12)
	//	return (ft_btreedelone(&ast_c10, free_asn),ft_btreedelone(&ast_c11, free_asn), 1);
	//t_token tab_c13[]={{UNSET,"c1",0}, {0,0,0}};
	//t_btree *ast_c13 = create_ast_node(tab_c13);
	//if (!ast_c13)
	//	return (ft_btreedelone(&ast_c10, free_asn),ft_btreedelone(&ast_c11, free_asn),ft_btreedelone(&ast_c12, free_asn), 1);
	//t_token tab_c14[]={{OPO,"||",1}, {0,0,0}};
	//t_btree *ast_c14 = create_ast_node(tab_c14);
	//if (!ast_c14)
	//	return (ft_btreedelone(&ast_c10, free_asn),ft_btreedelone(&ast_c11, free_asn),ft_btreedelone(&ast_c12, free_asn),ft_btreedelone(&ast_c13, free_asn), 1);
	//t_token tab_c15[]={{UNSET,"c2",1}, {0,0,0}};
	//t_btree *ast_c15 = create_ast_node(tab_c15);
	//if (!ast_c15)
	//	return (ft_btreedelone(&ast_c10, free_asn),ft_btreedelone(&ast_c11, free_asn),ft_btreedelone(&ast_c12, free_asn),ft_btreedelone(&ast_c13, free_asn),ft_btreedelone(&ast_c14, free_asn), 1);
	//t_token tab_c16[]={{UNSET,"c3",1}, {0,0,0}};
	//t_btree *ast_c16 = create_ast_node(tab_c16);
	//if (!ast_c16)
	//	return (ft_btreedelone(&ast_c10, free_asn),ft_btreedelone(&ast_c11, free_asn),ft_btreedelone(&ast_c12, free_asn),ft_btreedelone(&ast_c13, free_asn),ft_btreedelone(&ast_c14, free_asn),ft_btreedelone(&ast_c15, free_asn), 1);
	////ATTACHED NODES
	//ast_c10->left = ast_c11;
	//ast_c10->right = ast_c12;
	//ast_c11->left = ast_c13;
	//ast_c11->right = ast_c14;
	//ast_c14->left = ast_c15;
	//ast_c14->right = ast_c16;
	//// RUN TEST
	//nb_err += test(str_c1, &ast_c10, ev);
	//print_sep(S2);

	//// -[ 	 ]------------------------------------------------------------------
	//print_subtitle("C2|SIMPLE:CHANGES PRIORITY");
	//char *str_c2="c1&&(c2||c3&&c4)";
	///*
	// *                                       20:{OPA,"&&",0}
	// *                  21:{UNSET,"c1",0}<------------| |---->22:{OPA, "&&", 1}                              
	// *                                          23:{OPO,"||",1}<------| |---->24:{UNSET, "c4", 1}                                              
	// *                          25:{UNSET,"c2",1}<------| |---->26:{UNSET, "c3", 1}                                              
	// */
	//// CREATE NODES
	//t_token tab_c20[]={{OPA,"&&",0}, {0,0,0}};
	//t_btree *ast_c20 = create_ast_node(tab_c20);
	//if (!ast_c20)
	//	return (1);
	//t_token tab_c21[]={{UNSET,"c1", 0}, {0,0,0}};
	//t_btree *ast_c21 = create_ast_node(tab_c21);
	//if (!ast_c21)
	//	return (ft_btreedelone(&ast_c20, free_asn), 1);
	//t_token tab_c22[]={{OPA,"&&",1}, {0,0,0}};
	//t_btree *ast_c22 = create_ast_node(tab_c22);
	//if (!ast_c22)
	//	return (ft_btreedelone(&ast_c20, free_asn),ft_btreedelone(&ast_c21, free_asn), 1);
	//t_token tab_c23[]={{OPO,"||",1}, {0,0,0}};
	//t_btree *ast_c23 = create_ast_node(tab_c23);
	//if (!ast_c23)
	//	return (ft_btreedelone(&ast_c20, free_asn),ft_btreedelone(&ast_c21, free_asn),ft_btreedelone(&ast_c22, free_asn), 1);
	//t_token tab_c24[]={{UNSET,"c4",1}, {0,0,0}};
	//t_btree *ast_c24 = create_ast_node(tab_c24);
	//if (!ast_c24)
	//	return (ft_btreedelone(&ast_c20, free_asn),ft_btreedelone(&ast_c21, free_asn),ft_btreedelone(&ast_c22, free_asn),ft_btreedelone(&ast_c23, free_asn), 1);
	//t_token tab_c25[]={{UNSET,"c2",1}, {0,0,0}};
	//t_btree *ast_c25 = create_ast_node(tab_c25);
	//if (!ast_c25)
	//	return (ft_btreedelone(&ast_c20, free_asn),ft_btreedelone(&ast_c21, free_asn),ft_btreedelone(&ast_c22, free_asn),ft_btreedelone(&ast_c23, free_asn),ft_btreedelone(&ast_c24, free_asn), 1);
	//t_token tab_c26[]={{UNSET,"c3",1}, {0,0,0}};
	//t_btree *ast_c26 = create_ast_node(tab_c26);
	//if (!ast_c26)
	//	return (ft_btreedelone(&ast_c20, free_asn),ft_btreedelone(&ast_c21, free_asn),ft_btreedelone(&ast_c22, free_asn),ft_btreedelone(&ast_c23, free_asn),ft_btreedelone(&ast_c24, free_asn),ft_btreedelone(&ast_c25, free_asn), 1);
	////ATTACHED NODES
	//ast_c20->left = ast_c21;
	//ast_c20->right = ast_c22;
	//ast_c22->left = ast_c23;
	//ast_c22->right = ast_c24;
	//ast_c23->left = ast_c25;
	//ast_c23->right = ast_c26;
	//// RUN TEST
	//nb_err += test(str_c2, &ast_c20, ev);
	//print_sep(S2);

	//// -[ 	 ]------------------------------------------------------------------
	//print_subtitle("C3|SIMPLE:CHANGES PRIORITY");
	//char *str_c3="c1&&c2||(c3&&c4)";
	///*
	// *                                                  30:{OPO,"||",0}
	// *                  31:{OPA,"&&",0}<------------------------| |------------------------>32:{OPA, "&&", 1}                              
	// *33:{UNSET,"c1",0}<------| |---->34:{UNSET, "c2", 0}                    35:{UNSET,"c3",1}<------| |---->36:{UNSET, "c4", 1}                                              
	// *                                               
	// */
	//// CREATE NODES
	//t_token tab_c30[]={{OPO,"||",0}, {0,0,0}};
	//t_btree *ast_c30 = create_ast_node(tab_c30);
	//if (!ast_c30)
	//	return (1);
	//t_token tab_c31[]={{OPA,"&&", 0}, {0,0,0}};
	//t_btree *ast_c31 = create_ast_node(tab_c31);
	//if (!ast_c31)
	//	return (ft_btreedelone(&ast_c30, free_asn), 1);
	//t_token tab_c32[]={{OPA,"&&",1}, {0,0,0}};
	//t_btree *ast_c32 = create_ast_node(tab_c32);
	//if (!ast_c32)
	//	return (ft_btreedelone(&ast_c30, free_asn),ft_btreedelone(&ast_c31, free_asn), 1);
	//t_token tab_c33[]={{UNSET,"c1",0}, {0,0,0}};
	//t_btree *ast_c33 = create_ast_node(tab_c33);
	//if (!ast_c33)
	//	return (ft_btreedelone(&ast_c30, free_asn),ft_btreedelone(&ast_c31, free_asn),ft_btreedelone(&ast_c32, free_asn), 1);
	//t_token tab_c34[]={{UNSET,"c2",0}, {0,0,0}};
	//t_btree *ast_c34 = create_ast_node(tab_c34);
	//if (!ast_c34)
	//	return (ft_btreedelone(&ast_c30, free_asn),ft_btreedelone(&ast_c31, free_asn),ft_btreedelone(&ast_c32, free_asn),ft_btreedelone(&ast_c33, free_asn), 1);
	//t_token tab_c35[]={{UNSET,"c3",1}, {0,0,0}};
	//t_btree *ast_c35 = create_ast_node(tab_c35);
	//if (!ast_c35)
	//	return (ft_btreedelone(&ast_c30, free_asn),ft_btreedelone(&ast_c31, free_asn),ft_btreedelone(&ast_c32, free_asn),ft_btreedelone(&ast_c33, free_asn),ft_btreedelone(&ast_c34, free_asn), 1);
	//t_token tab_c36[]={{UNSET,"c4",1}, {0,0,0}};
	//t_btree *ast_c36 = create_ast_node(tab_c36);
	//if (!ast_c36)
	//	return (ft_btreedelone(&ast_c30, free_asn),ft_btreedelone(&ast_c31, free_asn),ft_btreedelone(&ast_c32, free_asn),ft_btreedelone(&ast_c33, free_asn),ft_btreedelone(&ast_c34, free_asn),ft_btreedelone(&ast_c35, free_asn), 1);
	////ATTACHED NODES
	//ast_c30->left = ast_c31;
	//ast_c30->right = ast_c32;
	//ast_c31->left = ast_c33;
	//ast_c31->right = ast_c34;
	//ast_c32->left = ast_c35;
	//ast_c32->right = ast_c36;
	//// RUN TEST
	//nb_err += test(str_c3, &ast_c30, ev);
	//print_sep(S2);

	// -[ 	 ]------------------------------------------------------------------
	print_subtitle("C4|SIMPLE:CHANGES PRIORITY");
	char *str_c4="(c1&&c2)||(c3&&c4)";
	/*
	 *                                                  40:{OPO,"||",0}
	 *                  41:{OPA,"&&",1}<------------------------| |------------------------>42:{OPA, "&&", 1}                              
	 *43:{UNSET,"c1",1}<------| |---->44:{UNSET, "c2", 1}                    45:{UNSET,"c3",1}<------| |---->46:{UNSET, "c4", 1}                                              
	 *                                               
	 */
	// CREATE NODES
	t_token tab_c40[]={{OPO,"||",0}, {0,0,0}};
	t_btree *ast_c40 = create_ast_node(tab_c40);
	if (!ast_c40)
		return (1);
	t_token tab_c41[]={{OPA,"&&", 1}, {0,0,0}};
	t_btree *ast_c41 = create_ast_node(tab_c41);
	if (!ast_c41)
		return (ft_btreedelone(&ast_c40, free_asn), 1);
	t_token tab_c42[]={{OPA,"&&",1}, {0,0,0}};
	t_btree *ast_c42 = create_ast_node(tab_c42);
	if (!ast_c42)
		return (ft_btreedelone(&ast_c40, free_asn),ft_btreedelone(&ast_c41, free_asn), 1);
	t_token tab_c43[]={{UNSET,"c1",1}, {0,0,0}};
	t_btree *ast_c43 = create_ast_node(tab_c43);
	if (!ast_c43)
		return (ft_btreedelone(&ast_c40, free_asn),ft_btreedelone(&ast_c41, free_asn),ft_btreedelone(&ast_c42, free_asn), 1);
	t_token tab_c44[]={{UNSET,"c2",1}, {0,0,0}};
	t_btree *ast_c44 = create_ast_node(tab_c44);
	if (!ast_c44)
		return (ft_btreedelone(&ast_c40, free_asn),ft_btreedelone(&ast_c41, free_asn),ft_btreedelone(&ast_c42, free_asn),ft_btreedelone(&ast_c43, free_asn), 1);
	t_token tab_c45[]={{UNSET,"c3",1}, {0,0,0}};
	t_btree *ast_c45 = create_ast_node(tab_c45);
	if (!ast_c45)
		return (ft_btreedelone(&ast_c40, free_asn),ft_btreedelone(&ast_c41, free_asn),ft_btreedelone(&ast_c42, free_asn),ft_btreedelone(&ast_c43, free_asn),ft_btreedelone(&ast_c44, free_asn), 1);
	t_token tab_c46[]={{UNSET,"c4",1}, {0,0,0}};
	t_btree *ast_c46 = create_ast_node(tab_c46);
	if (!ast_c46)
		return (ft_btreedelone(&ast_c40, free_asn),ft_btreedelone(&ast_c41, free_asn),ft_btreedelone(&ast_c42, free_asn),ft_btreedelone(&ast_c43, free_asn),ft_btreedelone(&ast_c44, free_asn),ft_btreedelone(&ast_c45, free_asn), 1);
	//ATTACHED NODES
	ast_c40->left = ast_c41;
	ast_c40->right = ast_c42;
	ast_c41->left = ast_c43;
	ast_c41->right = ast_c44;
	ast_c42->left = ast_c45;
	ast_c42->right = ast_c46;
	// RUN TEST
	nb_err += test(str_c4, &ast_c40, ev);
	print_sep(S2);
	print_sep(S1);
	//// =[  ]====================================================================
	//print_title("D| PARENTHESIS - IMBRICATION");
	//// -[ 	 ]------------------------------------------------------------------
	//print_subtitle("D0|IMBRICATION:NO PRIORITY CHANGES");
	//char *str_d0="((c1&&c2)||c3)&&c4";
	///*
	// *                                                                          00:{OPA, "&&", 0}
	// *                                  01:{OPO,"||",1}<----------------------------------| |----------------------------->02:{UNSET, "c4", 0}
	// *                    03:{OPA,"&&",2}<------| |---->04:{UNSET, "c3", 1}                              
	// * 05:{UNSET,"c1",2}<------| |---->06:{UNSET, "c2", 2}                                              
	// */
	//// CREATE NODES
	//t_token tab_d00[]={{OPA,"&&",0}, {0,0,0}};
	//t_btree *ast_d00 = create_ast_node(tab_d00);
	//if (!ast_d00)
	//	return (1);
	//t_token tab_d01[]={{OPO,"||", 1}, {0,0,0}};
	//t_btree *ast_d01 = create_ast_node(tab_d01);
	//if (!ast_d01)
	//	return (ft_btreedelone(&ast_d00, free_asn), 1);
	//t_token tab_d02[]={{UNSET,"c4",0}, {0,0,0}};
	//t_btree *ast_d02 = create_ast_node(tab_d02);
	//if (!ast_d02)
	//	return (ft_btreedelone(&ast_d00, free_asn),ft_btreedelone(&ast_d01, free_asn), 1);
	//t_token tab_d03[]={{OPA,"&&",2}, {0,0,0}};
	//t_btree *ast_d03 = create_ast_node(tab_d03);
	//if (!ast_d03)
	//	return (ft_btreedelone(&ast_d00, free_asn),ft_btreedelone(&ast_d01, free_asn),ft_btreedelone(&ast_d02, free_asn), 1);
	//t_token tab_d04[]={{UNSET,"c3",1}, {0,0,0}};
	//t_btree *ast_d04 = create_ast_node(tab_d04);
	//if (!ast_d04)
	//	return (ft_btreedelone(&ast_d00, free_asn),ft_btreedelone(&ast_d01, free_asn),ft_btreedelone(&ast_d02, free_asn),ft_btreedelone(&ast_d03, free_asn), 1);
	//t_token tab_d05[]={{UNSET,"c1",2}, {0,0,0}};
	//t_btree *ast_d05 = create_ast_node(tab_d05);
	//if (!ast_d05)
	//	return (ft_btreedelone(&ast_d00, free_asn),ft_btreedelone(&ast_d01, free_asn),ft_btreedelone(&ast_d02, free_asn),ft_btreedelone(&ast_d03, free_asn),ft_btreedelone(&ast_d04, free_asn), 1);
	//t_token tab_d06[]={{UNSET,"c2",2}, {0,0,0}};
	//t_btree *ast_d06 = create_ast_node(tab_d06);
	//if (!ast_d06)
	//	return (ft_btreedelone(&ast_d00, free_asn),ft_btreedelone(&ast_d01, free_asn),ft_btreedelone(&ast_d02, free_asn),ft_btreedelone(&ast_d03, free_asn),ft_btreedelone(&ast_d04, free_asn),ft_btreedelone(&ast_d05, free_asn), 1);
	////ATTACHED NODES
	//ast_d00->left = ast_d01;
	//ast_d00->right = ast_d02;
	//ast_d01->left = ast_d03;
	//ast_d01->right = ast_d04;
	//ast_d03->left = ast_d05;
	//ast_d03->right = ast_d06;
	//// RUN TEST
	//nb_err += test(str_d0, &ast_d00, ev);
	//print_sep(S2);

	//// -[ 	 ]------------------------------------------------------------------
	//print_subtitle("D1|IMBRICATION:NO PRIORITY CHANGES");
	//char *str_d1="(((c1&&c2)||c3)&&c4)";
	///*
	// *                                                                          10:{OPA, "&&", 1}
	// *                                  11:{OPO,"||",2}<----------------------------------| |----------------------------->12:{UNSET, "c4", 1}
	// *                    13:{OPA,"&&",3}<------| |---->14:{UNSET, "c3", 2}                              
	// * 15:{UNSET,"c1",3}<------| |---->16:{UNSET, "c2", 3}                                              
	// */
	//// CREATE NODES
	//t_token tab_d10[]={{OPA,"&&",1}, {0,0,0}};
	//t_btree *ast_d10 = create_ast_node(tab_d10);
	//if (!ast_d10)
	//	return (1);
	//t_token tab_d11[]={{OPO,"||", 2}, {0,0,0}};
	//t_btree *ast_d11 = create_ast_node(tab_d11);
	//if (!ast_d11)
	//	return (ft_btreedelone(&ast_d10, free_asn), 1);
	//t_token tab_d12[]={{UNSET,"c4",1}, {0,0,0}};
	//t_btree *ast_d12 = create_ast_node(tab_d12);
	//if (!ast_d12)
	//	return (ft_btreedelone(&ast_d10, free_asn),ft_btreedelone(&ast_d11, free_asn), 1);
	//t_token tab_d13[]={{OPA,"&&",3}, {0,0,0}};
	//t_btree *ast_d13 = create_ast_node(tab_d13);
	//if (!ast_d13)
	//	return (ft_btreedelone(&ast_d10, free_asn),ft_btreedelone(&ast_d11, free_asn),ft_btreedelone(&ast_d12, free_asn), 1);
	//t_token tab_d14[]={{UNSET,"c3",2}, {0,0,0}};
	//t_btree *ast_d14 = create_ast_node(tab_d14);
	//if (!ast_d14)
	//	return (ft_btreedelone(&ast_d10, free_asn),ft_btreedelone(&ast_d11, free_asn),ft_btreedelone(&ast_d12, free_asn),ft_btreedelone(&ast_d13, free_asn), 1);
	//t_token tab_d15[]={{UNSET,"c1",3}, {0,0,0}};
	//t_btree *ast_d15 = create_ast_node(tab_d15);
	//if (!ast_d15)
	//	return (ft_btreedelone(&ast_d10, free_asn),ft_btreedelone(&ast_d11, free_asn),ft_btreedelone(&ast_d12, free_asn),ft_btreedelone(&ast_d13, free_asn),ft_btreedelone(&ast_d14, free_asn), 1);
	//t_token tab_d16[]={{UNSET,"c2",3}, {0,0,0}};
	//t_btree *ast_d16 = create_ast_node(tab_d16);
	//if (!ast_d16)
	//	return (ft_btreedelone(&ast_d10, free_asn),ft_btreedelone(&ast_d11, free_asn),ft_btreedelone(&ast_d12, free_asn),ft_btreedelone(&ast_d13, free_asn),ft_btreedelone(&ast_d14, free_asn),ft_btreedelone(&ast_d15, free_asn), 1);
	////ATTACHED NODES
	//ast_d10->left = ast_d11;
	//ast_d10->right = ast_d12;
	//ast_d11->left = ast_d13;
	//ast_d11->right = ast_d14;
	//ast_d13->left = ast_d15;
	//ast_d13->right = ast_d16;
	//// RUN TEST
	//nb_err += test(str_d1, &ast_d10, ev);
	//print_sep(S2);

	//// -[ 	 ]------------------------------------------------------------------
	//print_subtitle("D2|IMBRICATION:NO PRIORITY CHANGES");
	//char *str_d2="( (((c1&&c2)||c3)&&c4) )";
	///*
	// *                                                                          20:{OPA, "&&", 2}
	// *                                  21:{OPO,"||",3}<----------------------------------| |----------------------------->22:{UNSET, "c4", 2}
	// *                    23:{OPA,"&&",4}<------| |---->24:{UNSET, "c3", 3}                              
	// * 25:{UNSET,"c1",4}<------| |---->26:{UNSET, "c2", 4}                                              
	// */
	//// create nodes
	//t_token tab_d20[]={{OPA,"&&",2}, {0,0,0}};
	//t_btree *ast_d20 = create_ast_node(tab_d20);
	//if (!ast_d20)
	//	return (1);
	//t_token tab_d21[]={{OPO,"||", 3}, {0,0,0}};
	//t_btree *ast_d21 = create_ast_node(tab_d21);
	//if (!ast_d21)
	//	return (ft_btreedelone(&ast_d20, free_asn), 1);
	//t_token tab_d22[]={{UNSET,"c4",2}, {0,0,0}};
	//t_btree *ast_d22 = create_ast_node(tab_d22);
	//if (!ast_d22)
	//	return (ft_btreedelone(&ast_d20, free_asn),ft_btreedelone(&ast_d21, free_asn), 1);
	//t_token tab_d23[]={{OPA,"&&",4}, {0,0,0}};
	//t_btree *ast_d23 = create_ast_node(tab_d23);
	//if (!ast_d23)
	//	return (ft_btreedelone(&ast_d20, free_asn),ft_btreedelone(&ast_d21, free_asn),ft_btreedelone(&ast_d22, free_asn), 1);
	//t_token tab_d24[]={{UNSET,"c3",3}, {0,0,0}};
	//t_btree *ast_d24 = create_ast_node(tab_d24);
	//if (!ast_d24)
	//	return (ft_btreedelone(&ast_d20, free_asn),ft_btreedelone(&ast_d21, free_asn),ft_btreedelone(&ast_d22, free_asn),ft_btreedelone(&ast_d23, free_asn), 1);
	//t_token tab_d25[]={{UNSET,"c1",4}, {0,0,0}};
	//t_btree *ast_d25 = create_ast_node(tab_d25);
	//if (!ast_d25)
	//	return (ft_btreedelone(&ast_d20, free_asn),ft_btreedelone(&ast_d21, free_asn),ft_btreedelone(&ast_d22, free_asn),ft_btreedelone(&ast_d23, free_asn),ft_btreedelone(&ast_d24, free_asn), 1);
	//t_token tab_d26[]={{UNSET,"c2",4}, {0,0,0}};
	//t_btree *ast_d26 = create_ast_node(tab_d26);
	//if (!ast_d26)
	//	return (ft_btreedelone(&ast_d20, free_asn),ft_btreedelone(&ast_d21, free_asn),ft_btreedelone(&ast_d22, free_asn),ft_btreedelone(&ast_d23, free_asn),ft_btreedelone(&ast_d24, free_asn),ft_btreedelone(&ast_d25, free_asn), 1);
	////attached nodes
	//ast_d20->left = ast_d21;
	//ast_d20->right = ast_d22;
	//ast_d21->left = ast_d23;
	//ast_d21->right = ast_d24;
	//ast_d23->left = ast_d25;
	//ast_d23->right = ast_d26;
	//// run test
	//nb_err += test(str_d2, &ast_d20, ev);
	//print_sep(S2);

	//// -[ 	 ]------------------------------------------------------------------
	//print_subtitle("D3|IMBRICATION:NO PRIORITY CHANGES");
	////            12234555555544444333332110
	//char *str_d3="(( (((c1&&c2)||c3)&&c4)) )";
	///*
	// *                                                                          30:{OPA, "&&", 3}
	// *                                  31:{OPO,"||",4}<----------------------------------| |----------------------------->32:{UNSET, "c4", 3}
	// *                    33:{OPA,"&&",5}<------| |---->34:{UNSET, "c3", 4}                              
	// * 35:{UNSET,"c1",5}<------| |---->36:{UNSET, "c2", 5}                                              
	// */
	//// create nodes
	//t_token tab_d30[]={{OPA,"&&",3}, {0,0,0}};
	//t_btree *ast_d30 = create_ast_node(tab_d30);
	//if (!ast_d30)
	//	return (1);
	//t_token tab_d31[]={{OPO,"||", 4}, {0,0,0}};
	//t_btree *ast_d31 = create_ast_node(tab_d31);
	//if (!ast_d31)
	//	return (ft_btreedelone(&ast_d30, free_asn), 1);
	//t_token tab_d32[]={{UNSET,"c4",3}, {0,0,0}};
	//t_btree *ast_d32 = create_ast_node(tab_d32);
	//if (!ast_d32)
	//	return (ft_btreedelone(&ast_d30, free_asn),ft_btreedelone(&ast_d31, free_asn), 1);
	//t_token tab_d33[]={{OPA,"&&",5}, {0,0,0}};
	//t_btree *ast_d33 = create_ast_node(tab_d33);
	//if (!ast_d33)
	//	return (ft_btreedelone(&ast_d30, free_asn),ft_btreedelone(&ast_d31, free_asn),ft_btreedelone(&ast_d32, free_asn), 1);
	//t_token tab_d34[]={{UNSET,"c3",4}, {0,0,0}};
	//t_btree *ast_d34 = create_ast_node(tab_d34);
	//if (!ast_d34)
	//	return (ft_btreedelone(&ast_d30, free_asn),ft_btreedelone(&ast_d31, free_asn),ft_btreedelone(&ast_d32, free_asn),ft_btreedelone(&ast_d33, free_asn), 1);
	//t_token tab_d35[]={{UNSET,"c1",5}, {0,0,0}};
	//t_btree *ast_d35 = create_ast_node(tab_d35);
	//if (!ast_d35)
	//	return (ft_btreedelone(&ast_d30, free_asn),ft_btreedelone(&ast_d31, free_asn),ft_btreedelone(&ast_d32, free_asn),ft_btreedelone(&ast_d33, free_asn),ft_btreedelone(&ast_d34, free_asn), 1);
	//t_token tab_d36[]={{UNSET,"c2",5}, {0,0,0}};
	//t_btree *ast_d36 = create_ast_node(tab_d36);
	//if (!ast_d36)
	//	return (ft_btreedelone(&ast_d30, free_asn),ft_btreedelone(&ast_d31, free_asn),ft_btreedelone(&ast_d32, free_asn),ft_btreedelone(&ast_d33, free_asn),ft_btreedelone(&ast_d34, free_asn),ft_btreedelone(&ast_d35, free_asn), 1);
	////attached nodes
	//ast_d30->left = ast_d31;
	//ast_d30->right = ast_d32;
	//ast_d31->left = ast_d33;
	//ast_d31->right = ast_d34;
	//ast_d33->left = ast_d35;
	//ast_d33->right = ast_d36;
	//// run test
	//nb_err += test(str_d3, &ast_d30, ev);
	//print_sep(S2);
	//// -[ 	 ]------------------------------------------------------------------
	//print_subtitle("D4|IMBRICATION:CHANGES PRIORITY");
	//char *str_d4="((c1&&c2)||(c3&&c4))";
	///*
	//*                                                  40:{OPO,"||",1}
	//*                  41:{OPA,"&&",2}<------------------------| |------------------------>42:{OPA, "&&", 2}                              
	//*43:{UNSET,"c1",2}<------| |---->44:{UNSET, "c2", 2}                    45:{UNSET,"c3",2}<------| |---->46:{UNSET, "c4", 2}                                              
	//*                                               
	//*/
	//// CREATE NODES
	//t_token tab_d40[]={{OPO,"||",1}, {0,0,0}};
	//t_btree *ast_d40 = create_ast_node(tab_d40);
	//if (!ast_d40)
	//	return (1);
	//t_token tab_d41[]={{OPA,"&&", 2}, {0,0,0}};
	//t_btree *ast_d41 = create_ast_node(tab_d41);
	//if (!ast_d41)
	//	return (ft_btreedelone(&ast_d40, free_asn), 1);
	//t_token tab_d42[]={{OPA,"&&",2}, {0,0,0}};
	//t_btree *ast_d42 = create_ast_node(tab_d42);
	//if (!ast_d42)
	//	return (ft_btreedelone(&ast_d40, free_asn),ft_btreedelone(&ast_d41, free_asn), 1);
	//t_token tab_d43[]={{UNSET,"c1",2}, {0,0,0}};
	//t_btree *ast_d43 = create_ast_node(tab_d43);
	//if (!ast_d43)
	//	return (ft_btreedelone(&ast_d40, free_asn),ft_btreedelone(&ast_d41, free_asn),ft_btreedelone(&ast_d42, free_asn), 1);
	//t_token tab_d44[]={{UNSET,"c2",2}, {0,0,0}};
	//t_btree *ast_d44 = create_ast_node(tab_d44);
	//if (!ast_d44)
	//	return (ft_btreedelone(&ast_d40, free_asn),ft_btreedelone(&ast_d41, free_asn),ft_btreedelone(&ast_d42, free_asn),ft_btreedelone(&ast_d43, free_asn), 1);
	//t_token tab_d45[]={{UNSET,"c3",2}, {0,0,0}};
	//t_btree *ast_d45 = create_ast_node(tab_d45);
	//if (!ast_d45)
	//	return (ft_btreedelone(&ast_d40, free_asn),ft_btreedelone(&ast_d41, free_asn),ft_btreedelone(&ast_d42, free_asn),ft_btreedelone(&ast_d43, free_asn),ft_btreedelone(&ast_d44, free_asn), 1);
	//t_token tab_d46[]={{UNSET,"c4",2}, {0,0,0}};
	//t_btree *ast_d46 = create_ast_node(tab_d46);
	//if (!ast_d46)
	//	return (ft_btreedelone(&ast_d40, free_asn),ft_btreedelone(&ast_d41, free_asn),ft_btreedelone(&ast_d42, free_asn),ft_btreedelone(&ast_d43, free_asn),ft_btreedelone(&ast_d44, free_asn),ft_btreedelone(&ast_d45, free_asn), 1);
	////ATTACHED NODES
	//ast_d40->left = ast_d41;
	//ast_d40->right = ast_d42;
	//ast_d41->left = ast_d43;
	//ast_d41->right = ast_d44;
	//ast_d42->left = ast_d45;
	//ast_d42->right = ast_d46;
	//// RUN TEST
	//nb_err += test(str_d4, &ast_d40, ev);
	//print_sep(S2);
	//// -[ 	 ]------------------------------------------------------------------
	//print_subtitle("D5|IMBRICATION:CHANGES PRIORITY");
    ////            12222222222211111000111112222222222210
	//char *str_d5="((c1&&c2||c3)&&c4)||(c5&&(c6||c7&&c8))";
	///*
	// *                                                                                                        5_00:{OPO, "||", 0}
	// *                                                               5_01:{OPA,"&&",1}<----------------------------------| |----------------------------->5_02:{OPA, "&&", 1}
	// *                                                5_03:{OPO,"||",2}<------| |---->5_04:{UNSET, "c4", 1}                                  5_05:{UNSET,"c5",1}<-------| |---->5_06:{OPA, "&&", 2}
	// *                               5_07:{OPA,"&&",2}<------| |---->5_08:{UNSET, "c3", 2}                                                                      5_09:{OPO,"||",2}<------| |---->5_10:{UNSET, "c8", 2}
	// *              5_11:{USNET,"c1",2}<-------| |----->5_12:{UNSET, "c2", 2}                                                                 5_13:{USNET,"c6",2}<-------| |----->5_14:{UNSET, "c7", 2}
	// */
	//// CREATE NODES
	//t_token tab_d_5_00[]={{OPO,"||",0}, {0,0,0}};
	//t_btree *ast_d_5_00 = create_ast_node(tab_d_5_00);
	//if (!ast_d_5_00)
	//	return (1);
	//t_token tab_d_5_01[]={{OPA,"&&", 1}, {0,0,0}};
	//t_btree *ast_d_5_01 = create_ast_node(tab_d_5_01);
	//if (!ast_d_5_01)
	//	return (ft_btreedelone(&ast_d_5_00, free_asn), 1);
	//t_token tab_d_5_02[]={{OPA,"&&",1}, {0,0,0}};
	//t_btree *ast_d_5_02 = create_ast_node(tab_d_5_02);
	//if (!ast_d_5_02)
	//	return (ft_btreedelone(&ast_d_5_00, free_asn),ft_btreedelone(&ast_d_5_01, free_asn), 1);
	//t_token tab_d_5_03[]={{OPO,"||",2}, {0,0,0}};
	//t_btree *ast_d_5_03 = create_ast_node(tab_d_5_03);
	//if (!ast_d_5_03)
	//	return (ft_btreedelone(&ast_d_5_00, free_asn),ft_btreedelone(&ast_d_5_01, free_asn),ft_btreedelone(&ast_d_5_02, free_asn), 1);
	//t_token tab_d_5_04[]={{UNSET,"c4",1}, {0,0,0}};
	//t_btree *ast_d_5_04 = create_ast_node(tab_d_5_04);
	//if (!ast_d_5_04)
	//	return (ft_btreedelone(&ast_d_5_00, free_asn),ft_btreedelone(&ast_d_5_01, free_asn),ft_btreedelone(&ast_d_5_02, free_asn),ft_btreedelone(&ast_d_5_03, free_asn), 1);
	//t_token tab_d_5_05[]={{UNSET,"c5",1}, {0,0,0}};
	//t_btree *ast_d_5_05 = create_ast_node(tab_d_5_05);
	//if (!ast_d_5_05)
	//	return (ft_btreedelone(&ast_d_5_00, free_asn),ft_btreedelone(&ast_d_5_01, free_asn),ft_btreedelone(&ast_d_5_02, free_asn),ft_btreedelone(&ast_d_5_03, free_asn),ft_btreedelone(&ast_d_5_04, free_asn), 1);
	//t_token tab_d_5_06[]={{OPA,"&&",2}, {0,0,0}};
	//t_btree *ast_d_5_06 = create_ast_node(tab_d_5_06);
	//if (!ast_d_5_06)
	//	return (ft_btreedelone(&ast_d_5_00, free_asn),ft_btreedelone(&ast_d_5_01, free_asn),ft_btreedelone(&ast_d_5_02, free_asn),ft_btreedelone(&ast_d_5_03, free_asn),ft_btreedelone(&ast_d_5_04, free_asn),ft_btreedelone(&ast_d_5_05, free_asn), 1);
	//t_token tab_d_5_07[]={{OPA,"&&",2}, {0,0,0}};
	//t_btree *ast_d_5_07 = create_ast_node(tab_d_5_07);
	//if (!ast_d_5_07)
	//	return (ft_btreedelone(&ast_d_5_00, free_asn),ft_btreedelone(&ast_d_5_01, free_asn),ft_btreedelone(&ast_d_5_02, free_asn),ft_btreedelone(&ast_d_5_03, free_asn),ft_btreedelone(&ast_d_5_04, free_asn),ft_btreedelone(&ast_d_5_05, free_asn),ft_btreedelone(&ast_d_5_06, free_asn), 1);
	//t_token tab_d_5_08[]={{UNSET,"c3",2}, {0,0,0}};
	//t_btree *ast_d_5_08 = create_ast_node(tab_d_5_08);
	//if (!ast_d_5_08)
	//	return (ft_btreedelone(&ast_d_5_00, free_asn),ft_btreedelone(&ast_d_5_01, free_asn),ft_btreedelone(&ast_d_5_02, free_asn),ft_btreedelone(&ast_d_5_03, free_asn),ft_btreedelone(&ast_d_5_04, free_asn),ft_btreedelone(&ast_d_5_05, free_asn),ft_btreedelone(&ast_d_5_06, free_asn),ft_btreedelone(&ast_d_5_07, free_asn), 1);
	//t_token tab_d_5_09[]={{OPO,"||",2}, {0,0,0}};
	//t_btree *ast_d_5_09 = create_ast_node(tab_d_5_09);
	//if (!ast_d_5_09)
	//	return (ft_btreedelone(&ast_d_5_00, free_asn),ft_btreedelone(&ast_d_5_01, free_asn),ft_btreedelone(&ast_d_5_02, free_asn),ft_btreedelone(&ast_d_5_03, free_asn),ft_btreedelone(&ast_d_5_04, free_asn),ft_btreedelone(&ast_d_5_05, free_asn),ft_btreedelone(&ast_d_5_06, free_asn),ft_btreedelone(&ast_d_5_07, free_asn),ft_btreedelone(&ast_d_5_08, free_asn), 1);
	//t_token tab_d_5_10[]={{UNSET,"c8",2}, {0,0,0}};
	//t_btree *ast_d_5_10 = create_ast_node(tab_d_5_10);
	//if (!ast_d_5_10)
	//	return (ft_btreedelone(&ast_d_5_00, free_asn),ft_btreedelone(&ast_d_5_01, free_asn),ft_btreedelone(&ast_d_5_02, free_asn),ft_btreedelone(&ast_d_5_03, free_asn),ft_btreedelone(&ast_d_5_04, free_asn),ft_btreedelone(&ast_d_5_05, free_asn),ft_btreedelone(&ast_d_5_06, free_asn),ft_btreedelone(&ast_d_5_07, free_asn),ft_btreedelone(&ast_d_5_08, free_asn),ft_btreedelone(&ast_d_5_09, free_asn), 1);
	//t_token tab_d_5_11[]={{UNSET,"c1",2}, {0,0,0}};
	//t_btree *ast_d_5_11 = create_ast_node(tab_d_5_11);
	//if (!ast_d_5_11)
	//	return (ft_btreedelone(&ast_d_5_00, free_asn),ft_btreedelone(&ast_d_5_01, free_asn),ft_btreedelone(&ast_d_5_02, free_asn),ft_btreedelone(&ast_d_5_03, free_asn),ft_btreedelone(&ast_d_5_04, free_asn),ft_btreedelone(&ast_d_5_05, free_asn),ft_btreedelone(&ast_d_5_06, free_asn),ft_btreedelone(&ast_d_5_07, free_asn),ft_btreedelone(&ast_d_5_08, free_asn),ft_btreedelone(&ast_d_5_09, free_asn),ft_btreedelone(&ast_d_5_10, free_asn), 1);
	//t_token tab_d_5_12[]={{UNSET,"c2",2}, {0,0,0}};
	//t_btree *ast_d_5_12 = create_ast_node(tab_d_5_12);
	//if (!ast_d_5_12)
	//	return (ft_btreedelone(&ast_d_5_00, free_asn),ft_btreedelone(&ast_d_5_01, free_asn),ft_btreedelone(&ast_d_5_02, free_asn),ft_btreedelone(&ast_d_5_03, free_asn),ft_btreedelone(&ast_d_5_04, free_asn),ft_btreedelone(&ast_d_5_05, free_asn),ft_btreedelone(&ast_d_5_06, free_asn),ft_btreedelone(&ast_d_5_07, free_asn),ft_btreedelone(&ast_d_5_08, free_asn),ft_btreedelone(&ast_d_5_09, free_asn),ft_btreedelone(&ast_d_5_10, free_asn),ft_btreedelone(&ast_d_5_11, free_asn), 1);
	//t_token tab_d_5_13[]={{UNSET,"c6",2}, {0,0,0}};
	//t_btree *ast_d_5_13 = create_ast_node(tab_d_5_13);
	//if (!ast_d_5_13)
	//	return (ft_btreedelone(&ast_d_5_00, free_asn),ft_btreedelone(&ast_d_5_01, free_asn),ft_btreedelone(&ast_d_5_02, free_asn),ft_btreedelone(&ast_d_5_03, free_asn),ft_btreedelone(&ast_d_5_04, free_asn),ft_btreedelone(&ast_d_5_05, free_asn),ft_btreedelone(&ast_d_5_06, free_asn),ft_btreedelone(&ast_d_5_07, free_asn),ft_btreedelone(&ast_d_5_08, free_asn),ft_btreedelone(&ast_d_5_09, free_asn),ft_btreedelone(&ast_d_5_10, free_asn),ft_btreedelone(&ast_d_5_11, free_asn),ft_btreedelone(&ast_d_5_12, free_asn), 1);
	//t_token tab_d_5_14[]={{UNSET,"c7",2}, {0,0,0}};
	//t_btree *ast_d_5_14 = create_ast_node(tab_d_5_14);
	//if (!ast_d_5_14)
	//	return (ft_btreedelone(&ast_d_5_00, free_asn),ft_btreedelone(&ast_d_5_01, free_asn),ft_btreedelone(&ast_d_5_02, free_asn),ft_btreedelone(&ast_d_5_03, free_asn),ft_btreedelone(&ast_d_5_04, free_asn),ft_btreedelone(&ast_d_5_05, free_asn),ft_btreedelone(&ast_d_5_06, free_asn),ft_btreedelone(&ast_d_5_07, free_asn),ft_btreedelone(&ast_d_5_08, free_asn),ft_btreedelone(&ast_d_5_09, free_asn),ft_btreedelone(&ast_d_5_10, free_asn),ft_btreedelone(&ast_d_5_11, free_asn),ft_btreedelone(&ast_d_5_12, free_asn),ft_btreedelone(&ast_d_5_13, free_asn), 1);
	////ATTACHED NODES
	//ast_d_5_00->left = ast_d_5_01;
	//ast_d_5_00->right = ast_d_5_02;
	//ast_d_5_01->left = ast_d_5_03;
	//ast_d_5_01->right = ast_d_5_04;
	//ast_d_5_02->left = ast_d_5_05;
	//ast_d_5_02->right = ast_d_5_06;
	//ast_d_5_03->left = ast_d_5_07;
	//ast_d_5_03->right = ast_d_5_08;
	//ast_d_5_06->left = ast_d_5_09;
	//ast_d_5_06->right = ast_d_5_10;
	//ast_d_5_07->left = ast_d_5_11;
	//ast_d_5_07->right = ast_d_5_12;
	//ast_d_5_09->left = ast_d_5_13;
	//ast_d_5_09->right = ast_d_5_14;
	//// RUN TEST
	//nb_err += test(str_d5, &ast_d_5_00, ev);
	//print_sep(S2);
	//print_sep(S1);
	//// =[  ]====================================================================
	//print_title("E| PARENTHESIS - REDIR and UNSET");
	//print_subtitle("E0|NO PRIORITY CHANGES");
	////            1110000000000
	//char *str_e0="(c1)>f1>f2>f3";
	///*
	// *                                      00:{RRS, ">f1", 0}
	// *                          01:{RRS,">",0},{UNSET,"f2",0}
	// *              02:{RRS,">",0},{UNSET,"f3",0}
	// * 03:{UNSET,"c1",1}
	// */
	//// CREATE NODES
	//t_token tab_e00[]={{RRS,">",0},{UNSET,"f1",0}, {0,0,0}};
	//t_btree *ast_e00 = create_ast_node(tab_e00);
	//if (!ast_e00)
	//	return (1);
	//t_token tab_e01[]={{RRS,">", 0},{UNSET,"f2", 0}, {0,0,0}};
	//t_btree *ast_e01 = create_ast_node(tab_e01);
	//if (!ast_e01)
	//	return (ft_btreedelone(&ast_e00, free_asn), 1);
	//t_token tab_e02[]={{RRS,">",0},{UNSET,"f3",0}, {0,0,0}};
	//t_btree *ast_e02 = create_ast_node(tab_e02);
	//if (!ast_e02)
	//	return (ft_btreedelone(&ast_e00, free_asn),ft_btreedelone(&ast_e01, free_asn), 1);
	//t_token tab_e03[]={{UNSET,"c1",1}, {0,0,0}};
	//t_btree *ast_e03 = create_ast_node(tab_e03);
	//if (!ast_e03)
	//	return (ft_btreedelone(&ast_e00, free_asn),ft_btreedelone(&ast_e01, free_asn),ft_btreedelone(&ast_e02, free_asn), 1);
	////ATTACHED NODES
	//ast_e00->left = ast_e01;
	//ast_e01->left = ast_e02;
	//ast_e02->left = ast_e03;
	//// RUN TEST
	//nb_err += test(str_e0, &ast_e00, ev);
	//print_sep(S2);
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("E1|CHANGES PRIORITY");
	////            1111110000000
	//char *str_e1="(c1>f1)>f2>f3";
	///*
	// *                                      10:{RRS, ">f2", 0}
	// *                          11:{RRS,">",0},{UNSET,"f3",0}
	// *              12:{RRS,">",1},{UNSET,"f1",1}
	// * 13:{UNSET,"c1",1}
	// */
	//// CREATE NODES
	//t_token tab_e10[]={{RRS,">",0},{UNSET,"f2",0}, {0,0,0}};
	//t_btree *ast_e10 = create_ast_node(tab_e10);
	//if (!ast_e10)
	//	return (1);
	//t_token tab_e11[]={{RRS,">",0},{UNSET,"f3",0}, {0,0,0}};
	//t_btree *ast_e11 = create_ast_node(tab_e11);
	//if (!ast_e11)
	//	return (ft_btreedelone(&ast_e10, free_asn), 1);
	//t_token tab_e12[]={{RRS,">",1},{UNSET,"f1",1}, {0,0,0}};
	//t_btree *ast_e12 = create_ast_node(tab_e12);
	//if (!ast_e12)
	//	return (ft_btreedelone(&ast_e10, free_asn),ft_btreedelone(&ast_e11, free_asn), 1);
	//t_token tab_e13[]={{UNSET,"c1",1}, {0,0,0}};
	//t_btree *ast_e13 = create_ast_node(tab_e13);
	//if (!ast_e13)
	//	return (ft_btreedelone(&ast_e10, free_asn),ft_btreedelone(&ast_e11, free_asn),ft_btreedelone(&ast_e12, free_asn), 1);
	////ATTACHED NODES
	//ast_e10->left = ast_e11;
	//ast_e11->left = ast_e12;
	//ast_e12->left = ast_e13;
	//// RUN TEST
	//nb_err += test(str_e1, &ast_e10, ev);
	//print_sep(S2);
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("E2|CHANGES PRIORITY");
	////            1111111110000
	//char *str_e2="(c1>f1>f2)>f3";
	///*
	// *                                      20:{RRS, ">f3", 0}
	// *                          21:{RRS,">",1},{UNSET,"f1",1}
	// *              22:{RRS,">",1},{UNSET,"f2",1}
	// * 23:{UNSET,"c1",1}
	// */
	//// CREATE NODES
	//t_token tab_e20[]={{RRS,">",0},{UNSET,"f3",0}, {0,0,0}};
	//t_btree *ast_e20 = create_ast_node(tab_e20);
	//if (!ast_e20)
	//	return (1);
	//t_token tab_e21[]={{RRS,">",1},{UNSET,"f1",1}, {0,0,0}};
	//t_btree *ast_e21 = create_ast_node(tab_e21);
	//if (!ast_e21)
	//	return (ft_btreedelone(&ast_e20, free_asn), 1);
	//t_token tab_e22[]={{RRS,">",1},{UNSET,"f2",1}, {0,0,0}};
	//t_btree *ast_e22 = create_ast_node(tab_e22);
	//if (!ast_e22)
	//	return (ft_btreedelone(&ast_e20, free_asn),ft_btreedelone(&ast_e21, free_asn), 1);
	//t_token tab_e23[]={{UNSET,"c1",1}, {0,0,0}};
	//t_btree *ast_e23 = create_ast_node(tab_e23);
	//if (!ast_e23)
	//	return (ft_btreedelone(&ast_e20, free_asn),ft_btreedelone(&ast_e21, free_asn),ft_btreedelone(&ast_e22, free_asn), 1);
	////ATTACHED NODES
	//ast_e20->left = ast_e21;
	//ast_e21->left = ast_e22;
	//ast_e22->left = ast_e23;
	//// RUN TEST
	//nb_err += test(str_e2, &ast_e20, ev);
	//print_sep(S2);
	//print_sep(S1);
	//// =[  ]====================================================================
	//print_title("F| PARENTHESIS - REDIR and UNSET IMBRICATION");
	//print_subtitle("F0|CHANGES PRIORITY");
	////            122211110000000
	//char *str_f0="((c1)>f1)>f2>f3";
	///*
	// *                                      00:{RRS, ">f2", 0}
	// *                          01:{RRS,">",0},{UNSET,"f3",0}
	// *              02:{RRS,">",1},{UNSET,"f1",1}
	// * 03:{UNSET,"c1",2}
	// */
	//// CREATE NODES
	//t_token tab_f00[]={{RRS,">",0},{UNSET,"f2",0}, {0,0,0}};
	//t_btree *ast_f00 = create_ast_node(tab_f00);
	//if (!ast_f00)
	//	return (1);
	//t_token tab_f01[]={{RRS,">",0},{UNSET,"f3",0}, {0,0,0}};
	//t_btree *ast_f01 = create_ast_node(tab_f01);
	//if (!ast_f01)
	//	return (ft_btreedelone(&ast_f00, free_asn), 1);
	//t_token tab_f02[]={{RRS,">",1},{UNSET,"f1",1}, {0,0,0}};
	//t_btree *ast_f02 = create_ast_node(tab_f02);
	//if (!ast_f02)
	//	return (ft_btreedelone(&ast_f00, free_asn),ft_btreedelone(&ast_f01, free_asn), 1);
	//t_token tab_f03[]={{UNSET,"c1",2}, {0,0,0}};
	//t_btree *ast_f03 = create_ast_node(tab_f03);
	//if (!ast_f03)
	//	return (ft_btreedelone(&ast_f00, free_asn),ft_btreedelone(&ast_f01, free_asn),ft_btreedelone(&ast_f02, free_asn), 1);
	////ATTACHED NODES
	//ast_f00->left = ast_f01;
	//ast_f01->left = ast_f02;
	//ast_f02->left = ast_f03;
	//// RUN TEST
	//nb_err += test(str_f0, &ast_f00, ev);
	//print_sep(S2);
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("F1|CHANGES PRIORITY");
	////            122211111110000
	//char *str_f1="((c1)>f1>f2)>f3";
	///*
	// *                                      10:{RRS, ">f3", 0}
	// *                          11:{RRS,">",1},{UNSET,"f1",1}
	// *              12:{RRS,">",1},{UNSET,"f2",1}
	// * 13:{UNSET,"c1",2}
	// */
	//// CREATE NODES
	//t_token tab_f10[]={{RRS,">",0},{UNSET,"f3",0}, {0,0,0}};
	//t_btree *ast_f10 = create_ast_node(tab_f10);
	//if (!ast_f10)
	//	return (1);
	//t_token tab_f11[]={{RRS,">",1},{UNSET,"f1",1}, {0,0,0}};
	//t_btree *ast_f11 = create_ast_node(tab_f11);
	//if (!ast_f11)
	//	return (ft_btreedelone(&ast_f10, free_asn), 1);
	//t_token tab_f12[]={{RRS,">",1},{UNSET,"f2",1}, {0,0,0}};
	//t_btree *ast_f12 = create_ast_node(tab_f12);
	//if (!ast_f12)
	//	return (ft_btreedelone(&ast_f10, free_asn),ft_btreedelone(&ast_f11, free_asn), 1);
	//t_token tab_f13[]={{UNSET,"c1",2}, {0,0,0}};
	//t_btree *ast_f13 = create_ast_node(tab_f13);
	//if (!ast_f13)
	//	return (ft_btreedelone(&ast_f10, free_asn),ft_btreedelone(&ast_f11, free_asn),ft_btreedelone(&ast_f12, free_asn), 1);
	////ATTACHED NODES
	//ast_f10->left = ast_f11;
	//ast_f11->left = ast_f12;
	//ast_f12->left = ast_f13;
	//// RUN TEST
	//nb_err += test(str_f1, &ast_f10, ev);
	//print_sep(S2);
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("F2|NO PRIORITY CHANGES");
	////            122211111111110
	//char *str_f2="((c1)>f1>f2>f3)";
	///*
	// *                                      20:{RRS, ">f1", 1}
	// *                          21:{RRS,">",1},{UNSET,"f2",1}
	// *              22:{RRS,">",1},{UNSET,"f3",1}
	// * 23:{UNSET,"c1",2}
	// */
	//// CREATE NODES
	//t_token tab_f20[]={{RRS,">",1},{UNSET,"f1",1}, {0,0,0}};
	//t_btree *ast_f20 = create_ast_node(tab_f20);
	//if (!ast_f20)
	//	return (1);
	//t_token tab_f21[]={{RRS,">",1},{UNSET,"f2",1}, {0,0,0}};
	//t_btree *ast_f21 = create_ast_node(tab_f21);
	//if (!ast_f21)
	//	return (ft_btreedelone(&ast_f20, free_asn), 1);
	//t_token tab_f22[]={{RRS,">",1},{UNSET,"f3",1}, {0,0,0}};
	//t_btree *ast_f22 = create_ast_node(tab_f22);
	//if (!ast_f22)
	//	return (ft_btreedelone(&ast_f20, free_asn),ft_btreedelone(&ast_f21, free_asn), 1);
	//t_token tab_f23[]={{UNSET,"c1",2}, {0,0,0}};
	//t_btree *ast_f23 = create_ast_node(tab_f23);
	//if (!ast_f23)
	//	return (ft_btreedelone(&ast_f20, free_asn),ft_btreedelone(&ast_f21, free_asn),ft_btreedelone(&ast_f22, free_asn), 1);
	////ATTACHED NODES
	//ast_f20->left = ast_f21;
	//ast_f21->left = ast_f22;
	//ast_f22->left = ast_f23;
	//// RUN TEST
	//nb_err += test(str_f2, &ast_f20, ev);
	//print_sep(S2);
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("F3|CHANGES PRIORITY");
	////            12333222211110000
	//char *str_f3="(((c1)>f1)>f2)>f3";
	///*
	// *                                      30:{RRS, ">f3", 0}
	// *                          31:{RRS,">",1},{UNSET,"f2",1}
	// *              32:{RRS,">",2},{UNSET,"f1",2}
	// * 33:{UNSET,"c1",3}
	// */
	//// CREATE NODES
	//t_token tab_f30[]={{RRS,">",0},{UNSET,"f3",0}, {0,0,0}};
	//t_btree *ast_f30 = create_ast_node(tab_f30);
	//if (!ast_f30)
	//	return (1);
	//t_token tab_f31[]={{RRS,">",1},{UNSET,"f2",1}, {0,0,0}};
	//t_btree *ast_f31 = create_ast_node(tab_f31);
	//if (!ast_f31)
	//	return (ft_btreedelone(&ast_f30, free_asn), 1);
	//t_token tab_f32[]={{RRS,">",2},{UNSET,"f1",2}, {0,0,0}};
	//t_btree *ast_f32 = create_ast_node(tab_f32);
	//if (!ast_f32)
	//	return (ft_btreedelone(&ast_f30, free_asn),ft_btreedelone(&ast_f31, free_asn), 1);
	//t_token tab_f33[]={{UNSET,"c1",3}, {0,0,0}};
	//t_btree *ast_f33 = create_ast_node(tab_f33);
	//if (!ast_f33)
	//	return (ft_btreedelone(&ast_f30, free_asn),ft_btreedelone(&ast_f31, free_asn),ft_btreedelone(&ast_f32, free_asn), 1);
	////ATTACHED NODES
	//ast_f30->left = ast_f31;
	//ast_f31->left = ast_f32;
	//ast_f32->left = ast_f33;
	//// RUN TEST
	//nb_err += test(str_f3, &ast_f30, ev);
	//print_sep(S2);
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("F4|CHANGES PRIORITY");
	////            12333222211111110
	//char *str_f4="(((c1)>f1)>f2>f3)";
	///*
	// *                                      40:{RRS, ">f2", 1}
	// *                          41:{RRS,">",1},{UNSET,"f3",1}
	// *              42:{RRS,">",2},{UNSET,"f1",2}
	// * 43:{UNSET,"c1",3}
	// */
	//// CREATE NODES
	//t_token tab_f40[]={{RRS,">",1},{UNSET,"f2",1}, {0,0,0}};
	//t_btree *ast_f40 = create_ast_node(tab_f40);
	//if (!ast_f40)
	//	return (1);
	//t_token tab_f41[]={{RRS,">",1},{UNSET,"f3",1}, {0,0,0}};
	//t_btree *ast_f41 = create_ast_node(tab_f41);
	//if (!ast_f41)
	//	return (ft_btreedelone(&ast_f40, free_asn), 1);
	//t_token tab_f42[]={{RRS,">",2},{UNSET,"f1",2}, {0,0,0}};
	//t_btree *ast_f42 = create_ast_node(tab_f42);
	//if (!ast_f42)
	//	return (ft_btreedelone(&ast_f40, free_asn),ft_btreedelone(&ast_f41, free_asn), 1);
	//t_token tab_f43[]={{UNSET,"c1",3}, {0,0,0}};
	//t_btree *ast_f43 = create_ast_node(tab_f43);
	//if (!ast_f43)
	//	return (ft_btreedelone(&ast_f40, free_asn),ft_btreedelone(&ast_f41, free_asn),ft_btreedelone(&ast_f42, free_asn), 1);
	////ATTACHED NODES
	//ast_f40->left = ast_f41;
	//ast_f41->left = ast_f42;
	//ast_f42->left = ast_f43;
	//// RUN TEST
	//nb_err += test(str_f4, &ast_f40, ev);
	//print_sep(S2);
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("F5|CHANGES PRIORITY");
	////            1234443333222211110
	//char *str_f5="((((c1)>f1)>f2)>f3)";
	///*
	// *                                      50:{RRS, ">f3", 1}
	// *                          51:{RRS,">",2},{UNSET,"f2",2}
	// *              52:{RRS,">",3},{UNSET,"f1",3}
	// * 53:{UNSET,"c1",4}
	// */
	//// CREATE NODES
	//t_token tab_f50[]={{RRS,">",1},{UNSET,"f3",1}, {0,0,0}};
	//t_btree *ast_f50 = create_ast_node(tab_f50);
	//if (!ast_f50)
	//	return (1);
	//t_token tab_f51[]={{RRS,">",2},{UNSET,"f2",2}, {0,0,0}};
	//t_btree *ast_f51 = create_ast_node(tab_f51);
	//if (!ast_f51)
	//	return (ft_btreedelone(&ast_f50, free_asn), 1);
	//t_token tab_f52[]={{RRS,">",3},{UNSET,"f1",3}, {0,0,0}};
	//t_btree *ast_f52 = create_ast_node(tab_f52);
	//if (!ast_f52)
	//	return (ft_btreedelone(&ast_f50, free_asn),ft_btreedelone(&ast_f51, free_asn), 1);
	//t_token tab_f53[]={{UNSET,"c1",4}, {0,0,0}};
	//t_btree *ast_f53 = create_ast_node(tab_f53);
	//if (!ast_f53)
	//	return (ft_btreedelone(&ast_f50, free_asn),ft_btreedelone(&ast_f51, free_asn),ft_btreedelone(&ast_f52, free_asn), 1);
	////ATTACHED NODES
	//ast_f50->left = ast_f51;
	//ast_f51->left = ast_f52;
	//ast_f52->left = ast_f53;
	//// RUN TEST
	//nb_err += test(str_f5, &ast_f50, ev);
	//print_sep(S2);
	//print_sep(S1);
	//// =[  ]====================================================================
	//print_title("G| MULTIPLE NESTED PARENTHESIS:");
	//t_token tab_g00[]={{UNSET,"c2",2}, {0,0,0}};
	//t_btree *ast_g00 = create_ast_node(tab_g00);
	//if (!ast_g00)
	//	return (1);
	//nb_err += test("( ( c2 ) )", &ast_g00, ev);

	//t_token tab_g01[]={{UNSET,"c3",3}, {0,0,0}};
	//t_btree *ast_g01 = create_ast_node(tab_g01);
	//if (!ast_g01)
	//	return (1);
	//nb_err += test("(( ( c3 )) )", &ast_g01, ev);

	//t_token tab_g02[]={{UNSET,"c3",3}, {0,0,0}};
	//t_btree *ast_g02 = create_ast_node(tab_g02);
	//if (!ast_g02)
	//	return (1);
	//nb_err += test("( (( c3 ) )) ", &ast_g02, ev);

	//t_token tab_g03[]={{UNSET,"c5",5}, {0,0,0}};
	//t_btree *ast_g03 = create_ast_node(tab_g03);
	//if (!ast_g03)
	//	return (1);
	//nb_err += test(" ( (( ( ( c5 )) ) )) ", &ast_g03, ev);
	//print_sep(S1);
	//// =[  ]====================================================================
	//print_title("H| COMBOS - REAL COMMANDS");
	//// -[  ]--------------------------------------------------------------------
	//print_subtitle("H0|PAR-IMBRICATION:NO PRIORITY CHANGES");
	////PARENTHESIS 123444444444444444444433332223444444443333321112222222210
	//char *str_h0="((((echo \"inside f1\")>f1)&&((<f1 cat) >f2))&&(<f2 cat))";
	///*
	// *                                                                                                                           00:{OPA, "&&", 1}
	// *                                                                        01:{OPA,"&&",2}<------------------------------------------| |------------------------------------------>02:{RLS,"<"->"f2",2}
	// *                                      03:{RRS,">"->"f1",3}<--------------------| |-------------------->04:{RRS,">"->"f2",3}                                05:{UNSET,"cat",2}<-------------| |--------------->|XX|
	// *06:{UNSET,"echo"->"\"inside f1\"",4}<----------| |---------->|XX|                 07:{RLS,"<"->"f1",4}<----------| |---------->|XX|
	// *                                                                  08:{UNSET,"cat",4}<-------| |------>|XX|
	// */
	//// CREATE NODES
	//t_token tab_h00[]={{OPA,"&&",1}, {0,0,0}};
	//t_btree *ast_h00 = create_ast_node(tab_h00);
	//if (!ast_h00)
	//	return (1);
	//t_token tab_h01[]={{OPA,"&&",2}, {1,0,0}};
	//t_btree *ast_h01 = create_ast_node(tab_h01);
	//if (!ast_h01)
	//	return (ft_btreedelone(&ast_h00, free_asn), 1);
	//t_token tab_h02[]={{RLS,"<",2}, {UNSET,"f2",2}, {0,0,0}};
	//t_btree *ast_h02 = create_ast_node(tab_h02);
	//if (!ast_h02)
	//	return (ft_btreedelone(&ast_h00, free_asn),ft_btreedelone(&ast_h01, free_asn), 1);
	//t_token tab_h03[]={{RRS,">",3}, {UNSET,"f1",3}, {1,0,0}};
	//t_btree *ast_h03 = create_ast_node(tab_h03);
	//if (!ast_h03)
	//	return (ft_btreedelone(&ast_h00, free_asn),ft_btreedelone(&ast_h01, free_asn),ft_btreedelone(&ast_h02, free_asn), 1);
	//t_token tab_h04[]={{RRS,">",3}, {UNSET,"f2",3}, {0,0,0}};
	//t_btree *ast_h04 = create_ast_node(tab_h04);
	//if (!ast_h04)
	//	return (ft_btreedelone(&ast_h00, free_asn),ft_btreedelone(&ast_h01, free_asn),ft_btreedelone(&ast_h02, free_asn),ft_btreedelone(&ast_h03, free_asn), 1);
	//t_token tab_h05[]={{UNSET,"cat",2}, {0,0,0}};
	//t_btree *ast_h05 = create_ast_node(tab_h05);
	//if (!ast_h05)
	//	return (ft_btreedelone(&ast_h00, free_asn),ft_btreedelone(&ast_h01, free_asn),ft_btreedelone(&ast_h02, free_asn),ft_btreedelone(&ast_h03, free_asn),ft_btreedelone(&ast_h04, free_asn), 1);
	//t_token tab_h06[]={{UNSET,"echo",4}, {UNSET,"\"inside f1\"",4}, {0,0,0}};
	//t_btree *ast_h06 = create_ast_node(tab_h06);
	//if (!ast_h06)
	//	return (ft_btreedelone(&ast_h00, free_asn),ft_btreedelone(&ast_h01, free_asn),ft_btreedelone(&ast_h02, free_asn),ft_btreedelone(&ast_h03, free_asn),ft_btreedelone(&ast_h04, free_asn),ft_btreedelone(&ast_h05, free_asn), 1);
	//t_token tab_h07[]={{RLS,"<",4}, {UNSET,"f1",4}, {0,0,0}};
	//t_btree *ast_h07 = create_ast_node(tab_h07);
	//if (!ast_h07)
	//	return (ft_btreedelone(&ast_h00, free_asn),ft_btreedelone(&ast_h01, free_asn),ft_btreedelone(&ast_h02, free_asn),ft_btreedelone(&ast_h03, free_asn),ft_btreedelone(&ast_h04, free_asn),ft_btreedelone(&ast_h05, free_asn),ft_btreedelone(&ast_h06, free_asn), 1);
	//t_token tab_h08[]={{UNSET,"cat",4}, {0,0,0}};
	//t_btree *ast_h08 = create_ast_node(tab_h08);
	//if (!ast_h08)
	//	return (ft_btreedelone(&ast_h00, free_asn),ft_btreedelone(&ast_h01, free_asn),ft_btreedelone(&ast_h02, free_asn),ft_btreedelone(&ast_h03, free_asn),ft_btreedelone(&ast_h04, free_asn),ft_btreedelone(&ast_h05, free_asn),ft_btreedelone(&ast_h06, free_asn),ft_btreedelone(&ast_h07, free_asn), 1);
	////ATTACHED NODES
	//ast_h00->left = ast_h01;
	//ast_h00->right = ast_h02;
	//ast_h02->left = ast_h05;
	//ast_h01->left = ast_h03;
	//ast_h01->right = ast_h04;
	//ast_h03->left = ast_h06;
	//ast_h04->left = ast_h07;
	//ast_h07->left = ast_h08;
	//// RUN TEST
	//nb_err += test(str_h0, &ast_h00, ev);
	//print_sep(S2);

	//print_subtitle("H0|PAR-IMBRICATION:NO PRIORITY CHANGES");
	////PARENTHESIS 123444333322234444444333332111222222210
	//char *str_h10="((((c1)>f1)&&((<f2 c2) >f3))&&(<f4 c4))";
	///*
	// *                                                                                                                           10:{OPA, "&&", 1}
	// *                                                                        11:{OPA,"&&",2}<------------------------------------------| |------------------------------------------>12:{RLS,"<"->"f4",2}
	// *                                      13:{RRS,">"->"f1",3}<--------------------| |-------------------->14:{RRS,">"->"f3",3}                                15:{UNSET,"c4",2}<-------------| |--------------->|XX|
	// *16:{UNSET,"c1",4}<----------| |---------->|XX|                 17:{RLS,"<"->"f2",4}<----------| |---------->|XX|
	// *                                                                  18:{UNSET,"c2",4}<-------| |------>|XX|
	// */
	//// CREATE NODES
	//t_token tab_h10[]={{OPA,"&&",1}, {0,0,0}};
	//t_btree *ast_h10 = create_ast_node(tab_h10);
	//if (!ast_h10)
	//	return (1);
	//t_token tab_h11[]={{OPA,"&&",2}, {1,0,0}};
	//t_btree *ast_h11 = create_ast_node(tab_h11);
	//if (!ast_h11)
	//	return (ft_btreedelone(&ast_h10, free_asn), 1);
	//t_token tab_h12[]={{RLS,"<",2}, {UNSET,"f4",2}, {0,0,0}};
	//t_btree *ast_h12 = create_ast_node(tab_h12);
	//if (!ast_h12)
	//	return (ft_btreedelone(&ast_h10, free_asn),ft_btreedelone(&ast_h11, free_asn), 1);
	//t_token tab_h13[]={{RRS,">",3}, {UNSET,"f1",3}, {1,0,0}};
	//t_btree *ast_h13 = create_ast_node(tab_h13);
	//if (!ast_h13)
	//	return (ft_btreedelone(&ast_h10, free_asn),ft_btreedelone(&ast_h11, free_asn),ft_btreedelone(&ast_h12, free_asn), 1);
	//t_token tab_h14[]={{RRS,">",3}, {UNSET,"f3",3}, {0,0,0}};
	//t_btree *ast_h14 = create_ast_node(tab_h14);
	//if (!ast_h14)
	//	return (ft_btreedelone(&ast_h10, free_asn),ft_btreedelone(&ast_h11, free_asn),ft_btreedelone(&ast_h12, free_asn),ft_btreedelone(&ast_h13, free_asn), 1);
	//t_token tab_h15[]={{UNSET,"c4",2}, {0,0,0}};
	//t_btree *ast_h15 = create_ast_node(tab_h15);
	//if (!ast_h15)
	//	return (ft_btreedelone(&ast_h10, free_asn),ft_btreedelone(&ast_h11, free_asn),ft_btreedelone(&ast_h12, free_asn),ft_btreedelone(&ast_h13, free_asn),ft_btreedelone(&ast_h14, free_asn), 1);
	//t_token tab_h16[]={{UNSET,"c1",4}, {0,0,0}};
	//t_btree *ast_h16 = create_ast_node(tab_h16);
	//if (!ast_h16)
	//	return (ft_btreedelone(&ast_h10, free_asn),ft_btreedelone(&ast_h11, free_asn),ft_btreedelone(&ast_h12, free_asn),ft_btreedelone(&ast_h13, free_asn),ft_btreedelone(&ast_h14, free_asn),ft_btreedelone(&ast_h15, free_asn), 1);
	//t_token tab_h17[]={{RLS,"<",4}, {UNSET,"f2",4}, {0,0,0}};
	//t_btree *ast_h17 = create_ast_node(tab_h17);
	//if (!ast_h17)
	//	return (ft_btreedelone(&ast_h10, free_asn),ft_btreedelone(&ast_h11, free_asn),ft_btreedelone(&ast_h12, free_asn),ft_btreedelone(&ast_h13, free_asn),ft_btreedelone(&ast_h14, free_asn),ft_btreedelone(&ast_h15, free_asn),ft_btreedelone(&ast_h16, free_asn), 1);
	//t_token tab_h18[]={{UNSET,"c2",4}, {0,0,0}};
	//t_btree *ast_h18 = create_ast_node(tab_h18);
	//if (!ast_h18)
	//	return (ft_btreedelone(&ast_h10, free_asn),ft_btreedelone(&ast_h11, free_asn),ft_btreedelone(&ast_h12, free_asn),ft_btreedelone(&ast_h13, free_asn),ft_btreedelone(&ast_h14, free_asn),ft_btreedelone(&ast_h15, free_asn),ft_btreedelone(&ast_h16, free_asn),ft_btreedelone(&ast_h17, free_asn), 1);
	////ATTACHED NODES
	//ast_h10->left = ast_h11;
	//ast_h10->right = ast_h12;
	//ast_h12->left = ast_h15;
	//ast_h11->left = ast_h13;
	//ast_h11->right = ast_h14;
	//ast_h13->left = ast_h16;
	//ast_h14->left = ast_h17;
	//ast_h17->left = ast_h18;
	//// RUN TEST
	//nb_err += test(str_h10, &ast_h10, ev);
	//print_sep(S2);
	//print_sep(S1);
	return (nb_err);
}

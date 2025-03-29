
=[ CAS:NULL ]==============================================================================
check_lexical_rules(<(null)>)-------------------------------------------------------------
[0;31mERROR:build_tok_lst_split_by_quotes():!str[0m: Success

after split_by_quote tok_lst=NULL
after split_by_spaces=NULL
after split_by_operators=NULL
after split_by_contiguous_single_quotes=NULL[0;31mERROR:set_tok_lst_type():!tok_lst[0m: Invalid argument

after set_tok_lst_type=NULL
after check_lexical_rules:[0]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<>)-------------------------------------------------------------------
[0;31mERROR:build_tok_lst_split_by_quotes():!str[0m: Invalid argument

after split_by_quote tok_lst=NULL
after split_by_spaces=NULL
after split_by_operators=NULL
after split_by_contiguous_single_quotes=NULL[0;31mERROR:set_tok_lst_type():!tok_lst[0m: Invalid argument

after set_tok_lst_type=NULL
after check_lexical_rules:[0]=NULL
---------------------------------------------------------------------------------------> ✅

=[ A| PASS COMMANDS ]======================================================================
check_lexical_rules(<< file1 cat | cat > file2>)------------------------------------------

after split_by_quote tok_lst={< file1 cat | cat > file2,-1,0}-->
after split_by_spaces={<,-1,0}-->{ ,-1,0}-->{file1,-1,0}-->{ ,-1,0}-->{cat,-1,0}-->{ ,-1,0}-->{|,-1,0}-->{ ,-1,0}-->{cat,-1,0}-->{ ,-1,0}-->{>,-1,0}-->{ ,-1,0}-->{file2,-1,0}-->
after split_by_operators={<,-1,0}-->{ ,-1,0}-->{file1,-1,0}-->{ ,-1,0}-->{cat,-1,0}-->{ ,-1,0}-->{|,-1,0}-->{ ,-1,0}-->{cat,-1,0}-->{ ,-1,0}-->{>,-1,0}-->{ ,-1,0}-->{file2,-1,0}-->
after split_by_contiguous_single_quotes={<,-1,0}-->{ ,-1,0}-->{file1,-1,0}-->{ ,-1,0}-->{cat,-1,0}-->{ ,-1,0}-->{|,-1,0}-->{ ,-1,0}-->{cat,-1,0}-->{ ,-1,0}-->{>,-1,0}-->{ ,-1,0}-->{file2,-1,0}-->
after set_tok_lst_type={<,10,0}-->{ ,0,0}-->{file1,-1,0}-->{ ,0,0}-->{cat,-1,0}-->{ ,0,0}-->{|,15,0}-->{ ,0,0}-->{cat,-1,0}-->{ ,0,0}-->{>,13,0}-->{ ,0,0}-->{file2,-1,0}-->
after check_lexical_rules:[0]={<,10,0}-->{ ,0,0}-->{file1,-1,0}-->{ ,0,0}-->{cat,-1,0}-->{ ,0,0}-->{|,15,0}-->{ ,0,0}-->{cat,-1,0}-->{ ,0,0}-->{>,13,0}-->{ ,0,0}-->{file2,-1,0}-->
tab_res=["<", " ", "file1", " ", "cat", " ", "|", " ", "cat", " ", ">", " ", "file2", NULL]
tok_lst={<,10,0}-->{ ,0,0}-->{file1,-1,0}-->{ ,0,0}-->{cat,-1,0}-->{ ,0,0}-->{|,15,0}-->{ ,0,0}-->{cat,-1,0}-->{ ,0,0}-->{>,13,0}-->{ ,0,0}-->{file2,-1,0}-->
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<'e'''cho toto>>file1>)-----------------------------------------------

after split_by_quote tok_lst={'e',-1,'}-->{'',-1,'}-->{cho toto>>file1,-1,0}-->
after split_by_spaces={'e',-1,'}-->{'',-1,'}-->{cho,-1,0}-->{ ,-1,0}-->{toto>>file1,-1,0}-->
after split_by_operators={'e',-1,'}-->{'',-1,'}-->{cho,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{>>,-1,0}-->{file1,-1,0}-->
after split_by_contiguous_single_quotes={'e'''cho,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{>>,-1,0}-->{file1,-1,0}-->
after set_tok_lst_type={'e'''cho,-1,0}-->{ ,0,0}-->{toto,-1,0}-->{>>,14,0}-->{file1,-1,0}-->
after check_lexical_rules:[0]={'e'''cho,-1,0}-->{ ,0,0}-->{toto,-1,0}-->{>>,14,0}-->{file1,-1,0}-->
tab_res=["'e'''cho", " ", "toto", ">>", "file1", NULL]
tok_lst={'e'''cho,-1,0}-->{ ,0,0}-->{toto,-1,0}-->{>>,14,0}-->{file1,-1,0}-->
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<    'e'"c"ho  toto&&echo OK||echo  KO>)------------------------------

after split_by_quote tok_lst={    ,-1,0}-->{'e',-1,'}-->{"c",-1,"}-->{ho  toto&&echo OK||echo  KO,-1,0}-->
after split_by_spaces={ ,-1,0}-->{'e',-1,'}-->{"c",-1,"}-->{ho,-1,0}-->{ ,-1,0}-->{toto&&echo,-1,0}-->{ ,-1,0}-->{OK||echo,-1,0}-->{ ,-1,0}-->{KO,-1,0}-->
after split_by_operators={ ,-1,0}-->{'e',-1,'}-->{"c",-1,"}-->{ho,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{&&,-1,0}-->{echo,-1,0}-->{ ,-1,0}-->{OK,-1,0}-->{||,-1,0}-->{echo,-1,0}-->{ ,-1,0}-->{KO,-1,0}-->
after split_by_contiguous_single_quotes={ ,-1,0}-->{'e'"c"ho,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{&&,-1,0}-->{echo,-1,0}-->{ ,-1,0}-->{OK,-1,0}-->{||,-1,0}-->{echo,-1,0}-->{ ,-1,0}-->{KO,-1,0}-->
after set_tok_lst_type={ ,0,0}-->{'e'"c"ho,-1,0}-->{ ,0,0}-->{toto,-1,0}-->{&&,21,0}-->{echo,-1,0}-->{ ,0,0}-->{OK,-1,0}-->{||,20,0}-->{echo,-1,0}-->{ ,0,0}-->{KO,-1,0}-->
after check_lexical_rules:[0]={ ,0,0}-->{'e'"c"ho,-1,0}-->{ ,0,0}-->{toto,-1,0}-->{&&,21,0}-->{echo,-1,0}-->{ ,0,0}-->{OK,-1,0}-->{||,20,0}-->{echo,-1,0}-->{ ,0,0}-->{KO,-1,0}-->
tab_res=[" ", "'e'"c"ho", " ", "toto", "&&", "echo", " ", "OK", "||", "echo", " ", "KO", NULL]
tok_lst={ ,0,0}-->{'e'"c"ho,-1,0}-->{ ,0,0}-->{toto,-1,0}-->{&&,21,0}-->{echo,-1,0}-->{ ,0,0}-->{OK,-1,0}-->{||,20,0}-->{echo,-1,0}-->{ ,0,0}-->{KO,-1,0}-->
---------------------------------------------------------------------------------------> ✅

=[ B| FAIL MULTIPLES ]=====================================================================
check_lexical_rules(<< << <<< <<<< <<<<< <<<<<<>)-----------------------------------------

after split_by_quote tok_lst={< << <<< <<<< <<<<< <<<<<<,-1,0}-->
after split_by_spaces={<,-1,0}-->{ ,-1,0}-->{<<,-1,0}-->{ ,-1,0}-->{<<<,-1,0}-->{ ,-1,0}-->{<<<<,-1,0}-->{ ,-1,0}-->{<<<<<,-1,0}-->{ ,-1,0}-->{<<<<<<,-1,0}-->
after split_by_operators={<,-1,0}-->{ ,-1,0}-->{<<,-1,0}-->{ ,-1,0}-->{<<<,-1,0}-->{ ,-1,0}-->{<<<<,-1,0}-->{ ,-1,0}-->{<<<<<,-1,0}-->{ ,-1,0}-->{<<<<<<,-1,0}-->
after split_by_contiguous_single_quotes={<,-1,0}-->{ ,-1,0}-->{<<,-1,0}-->{ ,-1,0}-->{<<<,-1,0}-->{ ,-1,0}-->{<<<<,-1,0}-->{ ,-1,0}-->{<<<<<,-1,0}-->{ ,-1,0}-->{<<<<<<,-1,0}-->
after set_tok_lst_type={<,10,0}-->{ ,0,0}-->{<<,11,0}-->{ ,0,0}-->{<<<,12,0}-->{ ,0,0}-->{<<<<,42,0}-->{ ,0,0}-->{<<<<<,42,0}-->{ ,0,0}-->{<<<<<<,42,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<> >> >>> >>>> >>>>> >>>>>>>)-----------------------------------------

after split_by_quote tok_lst={> >> >>> >>>> >>>>> >>>>>>,-1,0}-->
after split_by_spaces={>,-1,0}-->{ ,-1,0}-->{>>,-1,0}-->{ ,-1,0}-->{>>>,-1,0}-->{ ,-1,0}-->{>>>>,-1,0}-->{ ,-1,0}-->{>>>>>,-1,0}-->{ ,-1,0}-->{>>>>>>,-1,0}-->
after split_by_operators={>,-1,0}-->{ ,-1,0}-->{>>,-1,0}-->{ ,-1,0}-->{>>>,-1,0}-->{ ,-1,0}-->{>>>>,-1,0}-->{ ,-1,0}-->{>>>>>,-1,0}-->{ ,-1,0}-->{>>>>>>,-1,0}-->
after split_by_contiguous_single_quotes={>,-1,0}-->{ ,-1,0}-->{>>,-1,0}-->{ ,-1,0}-->{>>>,-1,0}-->{ ,-1,0}-->{>>>>,-1,0}-->{ ,-1,0}-->{>>>>>,-1,0}-->{ ,-1,0}-->{>>>>>>,-1,0}-->
after set_tok_lst_type={>,13,0}-->{ ,0,0}-->{>>,14,0}-->{ ,0,0}-->{>>>,42,0}-->{ ,0,0}-->{>>>>,42,0}-->{ ,0,0}-->{>>>>>,42,0}-->{ ,0,0}-->{>>>>>>,42,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<| || ||| |||| ||||| ||||||>)-----------------------------------------

after split_by_quote tok_lst={| || ||| |||| ||||| ||||||,-1,0}-->
after split_by_spaces={|,-1,0}-->{ ,-1,0}-->{||,-1,0}-->{ ,-1,0}-->{|||,-1,0}-->{ ,-1,0}-->{||||,-1,0}-->{ ,-1,0}-->{|||||,-1,0}-->{ ,-1,0}-->{||||||,-1,0}-->
after split_by_operators={|,-1,0}-->{ ,-1,0}-->{||,-1,0}-->{ ,-1,0}-->{|||,-1,0}-->{ ,-1,0}-->{||||,-1,0}-->{ ,-1,0}-->{|||||,-1,0}-->{ ,-1,0}-->{||||||,-1,0}-->
after split_by_contiguous_single_quotes={|,-1,0}-->{ ,-1,0}-->{||,-1,0}-->{ ,-1,0}-->{|||,-1,0}-->{ ,-1,0}-->{||||,-1,0}-->{ ,-1,0}-->{|||||,-1,0}-->{ ,-1,0}-->{||||||,-1,0}-->
after set_tok_lst_type={|,15,0}-->{ ,0,0}-->{||,20,0}-->{ ,0,0}-->{|||,42,0}-->{ ,0,0}-->{||||,42,0}-->{ ,0,0}-->{|||||,42,0}-->{ ,0,0}-->{||||||,42,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<& && &&& &&&& &&&&& &&&&&&>)-----------------------------------------

after split_by_quote tok_lst={& && &&& &&&& &&&&& &&&&&&,-1,0}-->
after split_by_spaces={&,-1,0}-->{ ,-1,0}-->{&&,-1,0}-->{ ,-1,0}-->{&&&,-1,0}-->{ ,-1,0}-->{&&&&,-1,0}-->{ ,-1,0}-->{&&&&&,-1,0}-->{ ,-1,0}-->{&&&&&&,-1,0}-->
after split_by_operators={&,-1,0}-->{ ,-1,0}-->{&&,-1,0}-->{ ,-1,0}-->{&&&,-1,0}-->{ ,-1,0}-->{&&&&,-1,0}-->{ ,-1,0}-->{&&&&&,-1,0}-->{ ,-1,0}-->{&&&&&&,-1,0}-->
after split_by_contiguous_single_quotes={&,-1,0}-->{ ,-1,0}-->{&&,-1,0}-->{ ,-1,0}-->{&&&,-1,0}-->{ ,-1,0}-->{&&&&,-1,0}-->{ ,-1,0}-->{&&&&&,-1,0}-->{ ,-1,0}-->{&&&&&&,-1,0}-->
after set_tok_lst_type={&,42,0}-->{ ,0,0}-->{&&,21,0}-->{ ,0,0}-->{&&&,42,0}-->{ ,0,0}-->{&&&&,42,0}-->{ ,0,0}-->{&&&&&,42,0}-->{ ,0,0}-->{&&&&&&,42,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(< <><<<< < ||| & &&&>)------------------------------------------------

after split_by_quote tok_lst={ <><<<< < ||| & &&&,-1,0}-->
after split_by_spaces={ ,-1,0}-->{<><<<<,-1,0}-->{ ,-1,0}-->{<,-1,0}-->{ ,-1,0}-->{|||,-1,0}-->{ ,-1,0}-->{&,-1,0}-->{ ,-1,0}-->{&&&,-1,0}-->
after split_by_operators={ ,-1,0}-->{<,-1,0}-->{>,-1,0}-->{<<<<,-1,0}-->{ ,-1,0}-->{<,-1,0}-->{ ,-1,0}-->{|||,-1,0}-->{ ,-1,0}-->{&,-1,0}-->{ ,-1,0}-->{&&&,-1,0}-->
after split_by_contiguous_single_quotes={ ,-1,0}-->{<,-1,0}-->{>,-1,0}-->{<<<<,-1,0}-->{ ,-1,0}-->{<,-1,0}-->{ ,-1,0}-->{|||,-1,0}-->{ ,-1,0}-->{&,-1,0}-->{ ,-1,0}-->{&&&,-1,0}-->
after set_tok_lst_type={ ,0,0}-->{<,10,0}-->{>,13,0}-->{<<<<,42,0}-->{ ,0,0}-->{<,10,0}-->{ ,0,0}-->{|||,42,0}-->{ ,0,0}-->{&,42,0}-->{ ,0,0}-->{&&&,42,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(< <><<<< < ||| & &&&>)------------------------------------------------

after split_by_quote tok_lst={ <><<<< < ||| & &&&,-1,0}-->
after split_by_spaces={ ,-1,0}-->{<><<<<,-1,0}-->{ ,-1,0}-->{<,-1,0}-->{ ,-1,0}-->{|||,-1,0}-->{ ,-1,0}-->{&,-1,0}-->{ ,-1,0}-->{&&&,-1,0}-->
after split_by_operators={ ,-1,0}-->{<,-1,0}-->{>,-1,0}-->{<<<<,-1,0}-->{ ,-1,0}-->{<,-1,0}-->{ ,-1,0}-->{|||,-1,0}-->{ ,-1,0}-->{&,-1,0}-->{ ,-1,0}-->{&&&,-1,0}-->
after split_by_contiguous_single_quotes={ ,-1,0}-->{<,-1,0}-->{>,-1,0}-->{<<<<,-1,0}-->{ ,-1,0}-->{<,-1,0}-->{ ,-1,0}-->{|||,-1,0}-->{ ,-1,0}-->{&,-1,0}-->{ ,-1,0}-->{&&&,-1,0}-->
after set_tok_lst_type={ ,0,0}-->{<,10,0}-->{>,13,0}-->{<<<<,42,0}-->{ ,0,0}-->{<,10,0}-->{ ,0,0}-->{|||,42,0}-->{ ,0,0}-->{&,42,0}-->{ ,0,0}-->{&&&,42,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅

=[ C| FAIL < ]=============================================================================
check_lexical_rules(<cat < |>)------------------------------------------------------------

after split_by_quote tok_lst={cat < |,-1,0}-->
after split_by_spaces={cat,-1,0}-->{ ,-1,0}-->{<,-1,0}-->{ ,-1,0}-->{|,-1,0}-->
after split_by_operators={cat,-1,0}-->{ ,-1,0}-->{<,-1,0}-->{ ,-1,0}-->{|,-1,0}-->
after split_by_contiguous_single_quotes={cat,-1,0}-->{ ,-1,0}-->{<,-1,0}-->{ ,-1,0}-->{|,-1,0}-->
after set_tok_lst_type={cat,-1,0}-->{ ,0,0}-->{<,10,0}-->{ ,0,0}-->{|,15,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<cat < >)-------------------------------------------------------------

after split_by_quote tok_lst={cat < ,-1,0}-->
after split_by_spaces={cat,-1,0}-->{ ,-1,0}-->{<,-1,0}-->{ ,-1,0}-->
after split_by_operators={cat,-1,0}-->{ ,-1,0}-->{<,-1,0}-->{ ,-1,0}-->
after split_by_contiguous_single_quotes={cat,-1,0}-->{ ,-1,0}-->{<,-1,0}-->{ ,-1,0}-->
after set_tok_lst_type={cat,-1,0}-->{ ,0,0}-->{<,10,0}-->{ ,0,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<cat <>)--------------------------------------------------------------

after split_by_quote tok_lst={cat <,-1,0}-->
after split_by_spaces={cat,-1,0}-->{ ,-1,0}-->{<,-1,0}-->
after split_by_operators={cat,-1,0}-->{ ,-1,0}-->{<,-1,0}-->
after split_by_contiguous_single_quotes={cat,-1,0}-->{ ,-1,0}-->{<,-1,0}-->
after set_tok_lst_type={cat,-1,0}-->{ ,0,0}-->{<,10,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅

=[ D| FAIL << ]============================================================================
check_lexical_rules(<cat << |>)-----------------------------------------------------------

after split_by_quote tok_lst={cat << |,-1,0}-->
after split_by_spaces={cat,-1,0}-->{ ,-1,0}-->{<<,-1,0}-->{ ,-1,0}-->{|,-1,0}-->
after split_by_operators={cat,-1,0}-->{ ,-1,0}-->{<<,-1,0}-->{ ,-1,0}-->{|,-1,0}-->
after split_by_contiguous_single_quotes={cat,-1,0}-->{ ,-1,0}-->{<<,-1,0}-->{ ,-1,0}-->{|,-1,0}-->
after set_tok_lst_type={cat,-1,0}-->{ ,0,0}-->{<<,11,0}-->{ ,0,0}-->{|,15,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<cat << >)------------------------------------------------------------

after split_by_quote tok_lst={cat << ,-1,0}-->
after split_by_spaces={cat,-1,0}-->{ ,-1,0}-->{<<,-1,0}-->{ ,-1,0}-->
after split_by_operators={cat,-1,0}-->{ ,-1,0}-->{<<,-1,0}-->{ ,-1,0}-->
after split_by_contiguous_single_quotes={cat,-1,0}-->{ ,-1,0}-->{<<,-1,0}-->{ ,-1,0}-->
after set_tok_lst_type={cat,-1,0}-->{ ,0,0}-->{<<,11,0}-->{ ,0,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<cat <<>)-------------------------------------------------------------

after split_by_quote tok_lst={cat <<,-1,0}-->
after split_by_spaces={cat,-1,0}-->{ ,-1,0}-->{<<,-1,0}-->
after split_by_operators={cat,-1,0}-->{ ,-1,0}-->{<<,-1,0}-->
after split_by_contiguous_single_quotes={cat,-1,0}-->{ ,-1,0}-->{<<,-1,0}-->
after set_tok_lst_type={cat,-1,0}-->{ ,0,0}-->{<<,11,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅

=[ E| FAIL <<< ]===========================================================================
check_lexical_rules(<<<< |>)--------------------------------------------------------------

after split_by_quote tok_lst={<<< |,-1,0}-->
after split_by_spaces={<<<,-1,0}-->{ ,-1,0}-->{|,-1,0}-->
after split_by_operators={<<<,-1,0}-->{ ,-1,0}-->{|,-1,0}-->
after split_by_contiguous_single_quotes={<<<,-1,0}-->{ ,-1,0}-->{|,-1,0}-->
after set_tok_lst_type={<<<,12,0}-->{ ,0,0}-->{|,15,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<<<< >)---------------------------------------------------------------

after split_by_quote tok_lst={<<< ,-1,0}-->
after split_by_spaces={<<<,-1,0}-->{ ,-1,0}-->
after split_by_operators={<<<,-1,0}-->{ ,-1,0}-->
after split_by_contiguous_single_quotes={<<<,-1,0}-->{ ,-1,0}-->
after set_tok_lst_type={<<<,12,0}-->{ ,0,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<<<<>)----------------------------------------------------------------

after split_by_quote tok_lst={<<<,-1,0}-->
after split_by_spaces={<<<,-1,0}-->
after split_by_operators={<<<,-1,0}-->
after split_by_contiguous_single_quotes={<<<,-1,0}-->
after set_tok_lst_type={<<<,12,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅

=[ E| FAIL > ]=============================================================================
check_lexical_rules(<echo toto >|>)-------------------------------------------------------

after split_by_quote tok_lst={echo toto >|,-1,0}-->
after split_by_spaces={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{ ,-1,0}-->{>|,-1,0}-->
after split_by_operators={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{ ,-1,0}-->{>,-1,0}-->{|,-1,0}-->
after split_by_contiguous_single_quotes={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{ ,-1,0}-->{>,-1,0}-->{|,-1,0}-->
after set_tok_lst_type={echo,-1,0}-->{ ,0,0}-->{toto,-1,0}-->{ ,0,0}-->{>,13,0}-->{|,15,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<echo toto >>)--------------------------------------------------------

after split_by_quote tok_lst={echo toto >,-1,0}-->
after split_by_spaces={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{ ,-1,0}-->{>,-1,0}-->
after split_by_operators={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{ ,-1,0}-->{>,-1,0}-->
after split_by_contiguous_single_quotes={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{ ,-1,0}-->{>,-1,0}-->
after set_tok_lst_type={echo,-1,0}-->{ ,0,0}-->{toto,-1,0}-->{ ,0,0}-->{>,13,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<echo toto > >)-------------------------------------------------------

after split_by_quote tok_lst={echo toto > ,-1,0}-->
after split_by_spaces={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{ ,-1,0}-->{>,-1,0}-->{ ,-1,0}-->
after split_by_operators={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{ ,-1,0}-->{>,-1,0}-->{ ,-1,0}-->
after split_by_contiguous_single_quotes={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{ ,-1,0}-->{>,-1,0}-->{ ,-1,0}-->
after set_tok_lst_type={echo,-1,0}-->{ ,0,0}-->{toto,-1,0}-->{ ,0,0}-->{>,13,0}-->{ ,0,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅

=[ G| FAIL >> ]============================================================================
check_lexical_rules(<echo toto >>|>)------------------------------------------------------

after split_by_quote tok_lst={echo toto >>|,-1,0}-->
after split_by_spaces={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{ ,-1,0}-->{>>|,-1,0}-->
after split_by_operators={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{ ,-1,0}-->{>>,-1,0}-->{|,-1,0}-->
after split_by_contiguous_single_quotes={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{ ,-1,0}-->{>>,-1,0}-->{|,-1,0}-->
after set_tok_lst_type={echo,-1,0}-->{ ,0,0}-->{toto,-1,0}-->{ ,0,0}-->{>>,14,0}-->{|,15,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<echo toto >>>)-------------------------------------------------------

after split_by_quote tok_lst={echo toto >>,-1,0}-->
after split_by_spaces={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{ ,-1,0}-->{>>,-1,0}-->
after split_by_operators={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{ ,-1,0}-->{>>,-1,0}-->
after split_by_contiguous_single_quotes={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{ ,-1,0}-->{>>,-1,0}-->
after set_tok_lst_type={echo,-1,0}-->{ ,0,0}-->{toto,-1,0}-->{ ,0,0}-->{>>,14,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<echo toto >> >)------------------------------------------------------

after split_by_quote tok_lst={echo toto >> ,-1,0}-->
after split_by_spaces={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{ ,-1,0}-->{>>,-1,0}-->{ ,-1,0}-->
after split_by_operators={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{ ,-1,0}-->{>>,-1,0}-->{ ,-1,0}-->
after split_by_contiguous_single_quotes={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{ ,-1,0}-->{>>,-1,0}-->{ ,-1,0}-->
after set_tok_lst_type={echo,-1,0}-->{ ,0,0}-->{toto,-1,0}-->{ ,0,0}-->{>>,14,0}-->{ ,0,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅

=[ H| FAIL && ]============================================================================
check_lexical_rules(<&&>)-----------------------------------------------------------------

after split_by_quote tok_lst={&&,-1,0}-->
after split_by_spaces={&&,-1,0}-->
after split_by_operators={&&,-1,0}-->
after split_by_contiguous_single_quotes={&&,-1,0}-->
after set_tok_lst_type={&&,21,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<echo toto&&>)--------------------------------------------------------

after split_by_quote tok_lst={echo toto&&,-1,0}-->
after split_by_spaces={echo,-1,0}-->{ ,-1,0}-->{toto&&,-1,0}-->
after split_by_operators={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{&&,-1,0}-->
after split_by_contiguous_single_quotes={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{&&,-1,0}-->
after set_tok_lst_type={echo,-1,0}-->{ ,0,0}-->{toto,-1,0}-->{&&,21,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<&&echo toto>)--------------------------------------------------------

after split_by_quote tok_lst={&&echo toto,-1,0}-->
after split_by_spaces={&&echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->
after split_by_operators={&&,-1,0}-->{echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->
after split_by_contiguous_single_quotes={&&,-1,0}-->{echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->
after set_tok_lst_type={&&,21,0}-->{echo,-1,0}-->{ ,0,0}-->{toto,-1,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅

=[ I| FAIL || ]============================================================================
check_lexical_rules(<||>)-----------------------------------------------------------------

after split_by_quote tok_lst={||,-1,0}-->
after split_by_spaces={||,-1,0}-->
after split_by_operators={||,-1,0}-->
after split_by_contiguous_single_quotes={||,-1,0}-->
after set_tok_lst_type={||,20,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<echo toto||>)--------------------------------------------------------

after split_by_quote tok_lst={echo toto||,-1,0}-->
after split_by_spaces={echo,-1,0}-->{ ,-1,0}-->{toto||,-1,0}-->
after split_by_operators={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{||,-1,0}-->
after split_by_contiguous_single_quotes={echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->{||,-1,0}-->
after set_tok_lst_type={echo,-1,0}-->{ ,0,0}-->{toto,-1,0}-->{||,20,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<||echo toto>)--------------------------------------------------------

after split_by_quote tok_lst={||echo toto,-1,0}-->
after split_by_spaces={||echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->
after split_by_operators={||,-1,0}-->{echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->
after split_by_contiguous_single_quotes={||,-1,0}-->{echo,-1,0}-->{ ,-1,0}-->{toto,-1,0}-->
after set_tok_lst_type={||,20,0}-->{echo,-1,0}-->{ ,0,0}-->{toto,-1,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅

=[ J| FAIL | ]=============================================================================
check_lexical_rules(<|>)------------------------------------------------------------------

after split_by_quote tok_lst={|,-1,0}-->
after split_by_spaces={|,-1,0}-->
after split_by_operators={|,-1,0}-->
after split_by_contiguous_single_quotes={|,-1,0}-->
after set_tok_lst_type={|,15,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<ls|>)----------------------------------------------------------------

after split_by_quote tok_lst={ls|,-1,0}-->
after split_by_spaces={ls|,-1,0}-->
after split_by_operators={ls,-1,0}-->{|,-1,0}-->
after split_by_contiguous_single_quotes={ls,-1,0}-->{|,-1,0}-->
after set_tok_lst_type={ls,-1,0}-->{|,15,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<|ls>)----------------------------------------------------------------

after split_by_quote tok_lst={|ls,-1,0}-->
after split_by_spaces={|ls,-1,0}-->
after split_by_operators={|,-1,0}-->{ls,-1,0}-->
after split_by_contiguous_single_quotes={|,-1,0}-->{ls,-1,0}-->
after set_tok_lst_type={|,15,0}-->{ls,-1,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅

=[ K| FAIL ERR_TYPE ]======================================================================
check_lexical_rules(<<<<<>)---------------------------------------------------------------

after split_by_quote tok_lst={<<<<,-1,0}-->
after split_by_spaces={<<<<,-1,0}-->
after split_by_operators={<<<<,-1,0}-->
after split_by_contiguous_single_quotes={<<<<,-1,0}-->
after set_tok_lst_type={<<<<,42,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<>>>>)----------------------------------------------------------------

after split_by_quote tok_lst={>>>,-1,0}-->
after split_by_spaces={>>>,-1,0}-->
after split_by_operators={>>>,-1,0}-->
after split_by_contiguous_single_quotes={>>>,-1,0}-->
after set_tok_lst_type={>>>,42,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<|||>)----------------------------------------------------------------

after split_by_quote tok_lst={|||,-1,0}-->
after split_by_spaces={|||,-1,0}-->
after split_by_operators={|||,-1,0}-->
after split_by_contiguous_single_quotes={|||,-1,0}-->
after set_tok_lst_type={|||,42,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<&&&>)----------------------------------------------------------------

after split_by_quote tok_lst={&&&,-1,0}-->
after split_by_spaces={&&&,-1,0}-->
after split_by_operators={&&&,-1,0}-->
after split_by_contiguous_single_quotes={&&&,-1,0}-->
after set_tok_lst_type={&&&,42,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<&>)------------------------------------------------------------------

after split_by_quote tok_lst={&,-1,0}-->
after split_by_spaces={&,-1,0}-->
after split_by_operators={&,-1,0}-->
after split_by_contiguous_single_quotes={&,-1,0}-->
after set_tok_lst_type={&,42,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅
check_lexical_rules(<&&&&>)---------------------------------------------------------------

after split_by_quote tok_lst={&&&&,-1,0}-->
after split_by_spaces={&&&&,-1,0}-->
after split_by_operators={&&&&,-1,0}-->
after split_by_contiguous_single_quotes={&&&&,-1,0}-->
after set_tok_lst_type={&&&&,42,0}-->syntax error: Invalid argument

after check_lexical_rules:[1]=NULL
---------------------------------------------------------------------------------------> ✅

   [33m┌[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m┐[0m
   [33m│[0m                                 [33m│[0m
   [33m│[0m   [33mfuncheck[0m -- [1m1.1.4[0m             [33m│[0m
   [33m│[0m                                 [33m│[0m
   [33m│[0m   - program: [1m./bin/test_check_lexical_rules[0m           [33m│[0m
   [33m│[0m                                 [33m│[0m
   [33m│[0m   - arguments:                  [33m│[0m
   [33m└[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m─[0m[33m┘[0m

[44m[1m INFO [0m If your program wait for stdin input, you can type here or pipe it.
[33m───────────── TTY ────────────[0m
[33m──────────────────────────────[0m
[46m[1m TASK [0m Testable functions fetching [42m[1m ✓ [0m
[44m[1m INFO [0m Functions detected count: [1m3806[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x3831)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x40a6)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2814)
      ┗━┳━━ build_tok_lst_split_by_operators at ?? (0x22b4)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
          ┗━┳━━ test at ?? (0x2c15)
            ┗━━━━ main at ?? (0x3831)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x37c5)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x40a6)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2814)
      ┗━┳━━ build_tok_lst_split_by_operators at ?? (0x22b4)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
          ┗━┳━━ test at ?? (0x2c15)
            ┗━━━━ main at ?? (0x37c5)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x3759)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x40a6)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2814)
      ┗━┳━━ build_tok_lst_split_by_operators at ?? (0x22b4)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
          ┗━┳━━ test at ?? (0x2c15)
            ┗━━━━ main at ?? (0x3759)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x37c5)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x40a6)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2814)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x2186)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
          ┗━┳━━ test at ?? (0x2bdf)
            ┗━━━━ main at ?? (0x37c5)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x3759)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x40a6)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2814)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x2186)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
          ┗━┳━━ test at ?? (0x2bdf)
            ┗━━━━ main at ?? (0x3759)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x35f6)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x40a6)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2814)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x2186)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
          ┗━┳━━ test at ?? (0x2bdf)
            ┗━━━━ main at ?? (0x35f6)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x358a)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x40a6)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2814)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x2186)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
          ┗━┳━━ test at ?? (0x2bdf)
            ┗━━━━ main at ?? (0x358a)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x351e)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x40a6)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2814)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x2186)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
          ┗━┳━━ test at ?? (0x2bdf)
            ┗━━━━ main at ?? (0x351e)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x37c5)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x40a6)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2814)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x214c)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
          ┗━┳━━ test at ?? (0x2bdf)
            ┗━━━━ main at ?? (0x37c5)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x3759)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x40a6)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2814)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x214c)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
          ┗━┳━━ test at ?? (0x2bdf)
            ┗━━━━ main at ?? (0x3759)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x3831)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x398c)
  ┗━┳━━ ft_substr at ?? (0x3ea3)
    ┗━┳━━ set_token_str at ?? (0x26df)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2858)
        ┗━┳━━ build_tok_lst_split_by_operators at ?? (0x22b4)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
            ┗━┳━━ test at ?? (0x2c15)
              ┗━━━━ main at ?? (0x3831)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x37c5)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x398c)
  ┗━┳━━ ft_substr at ?? (0x3ea3)
    ┗━┳━━ set_token_str at ?? (0x26df)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2858)
        ┗━┳━━ build_tok_lst_split_by_operators at ?? (0x22b4)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
            ┗━┳━━ test at ?? (0x2c15)
              ┗━━━━ main at ?? (0x37c5)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x3759)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x398c)
  ┗━┳━━ ft_substr at ?? (0x3ea3)
    ┗━┳━━ set_token_str at ?? (0x26df)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2858)
        ┗━┳━━ build_tok_lst_split_by_operators at ?? (0x22b4)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
            ┗━┳━━ test at ?? (0x2c15)
              ┗━━━━ main at ?? (0x3759)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x37c5)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x398c)
  ┗━┳━━ ft_substr at ?? (0x3ea3)
    ┗━┳━━ set_token_str at ?? (0x26df)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2858)
        ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x2186)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
            ┗━┳━━ test at ?? (0x2bdf)
              ┗━━━━ main at ?? (0x37c5)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x3759)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x398c)
  ┗━┳━━ ft_substr at ?? (0x3ea3)
    ┗━┳━━ set_token_str at ?? (0x26df)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2858)
        ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x2186)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
            ┗━┳━━ test at ?? (0x2bdf)
              ┗━━━━ main at ?? (0x3759)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x35f6)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x398c)
  ┗━┳━━ ft_substr at ?? (0x3ea3)
    ┗━┳━━ set_token_str at ?? (0x26df)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2858)
        ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x2186)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
            ┗━┳━━ test at ?? (0x2bdf)
              ┗━━━━ main at ?? (0x35f6)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x358a)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x398c)
  ┗━┳━━ ft_substr at ?? (0x3ea3)
    ┗━┳━━ set_token_str at ?? (0x26df)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2858)
        ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x2186)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
            ┗━┳━━ test at ?? (0x2bdf)
              ┗━━━━ main at ?? (0x358a)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x351e)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x398c)
  ┗━┳━━ ft_substr at ?? (0x3ea3)
    ┗━┳━━ set_token_str at ?? (0x26df)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2858)
        ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x2186)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
            ┗━┳━━ test at ?? (0x2bdf)
              ┗━━━━ main at ?? (0x351e)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x37c5)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x398c)
  ┗━┳━━ ft_substr at ?? (0x3ea3)
    ┗━┳━━ set_token_str at ?? (0x26df)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2858)
        ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x214c)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
            ┗━┳━━ test at ?? (0x2bdf)
              ┗━━━━ main at ?? (0x37c5)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x3759)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x398c)
  ┗━┳━━ ft_substr at ?? (0x3ea3)
    ┗━┳━━ set_token_str at ?? (0x26df)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2858)
        ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x214c)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
            ┗━┳━━ test at ?? (0x2bdf)
              ┗━━━━ main at ?? (0x3759)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x3831)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ init_token at ?? (0x2579)
  ┗━┳━━ init_tok_lst_node at ?? (0x2788)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2814)
      ┗━┳━━ build_tok_lst_split_by_operators at ?? (0x22b4)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
          ┗━┳━━ test at ?? (0x2c15)
            ┗━━━━ main at ?? (0x3831)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x37c5)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ init_token at ?? (0x2579)
  ┗━┳━━ init_tok_lst_node at ?? (0x2788)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2814)
      ┗━┳━━ build_tok_lst_split_by_operators at ?? (0x22b4)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
          ┗━┳━━ test at ?? (0x2c15)
            ┗━━━━ main at ?? (0x37c5)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x3759)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ init_token at ?? (0x2579)
  ┗━┳━━ init_tok_lst_node at ?? (0x2788)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2814)
      ┗━┳━━ build_tok_lst_split_by_operators at ?? (0x22b4)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
          ┗━┳━━ test at ?? (0x2c15)
            ┗━━━━ main at ?? (0x3759)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x37c5)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ init_token at ?? (0x2579)
  ┗━┳━━ init_tok_lst_node at ?? (0x2788)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2814)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x2186)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x153d)
          ┗━┳━━ test at ?? (0x2bdf)
            ┗━━━━ main at ?? (0x37c5)
[33m─────────── OUTPUT ───────────[0m
[33m──────────────────────────────[0m

┏[41m [1mSegmentation fault [0m
┗━┳━━ test at ?? (0x2e1c)
  ┗━━━━ main at ?? (0x3759)
┏[41m [1mmalloc [0m the crash occurred when this function failed
┗━┳━━ init_token at ?? (0x2579)
  ┗━┳━━ init_tok_lst_node at ?? (0x2788)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2814)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x
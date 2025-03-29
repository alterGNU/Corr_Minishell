➜  Minishell git:(main) ✗ funcheck tests/bin/test_lexer 

   ┌─────────────────────────────────┐
   │                                 │
   │   funcheck -- 1.1.4             │
   │                                 │
   │   - program: tests/bin/test_lexer │
   │                                 │
   │   - arguments:                  │
   └─────────────────────────────────┘

 INFO  If your program wait for stdin input, you can type here or pipe it.
───────────── TTY ────────────

=[ A| PASS COMMANDS ]======================================================================
lexer(<< file1 cat | cat > file2>)--------------------------------------------------------

after lexer:[0]={<,10,0}-->{ ,0,0}-->{file1,-1,0}-->{ ,0,0}-->{cat,-1,0}-->{ ,0,0}-->{|,15,0}-->{ ,0,0}-->{cat,-1,0}-->{ ,0,0}-->{>,13,0}-->{ ,0,0}-->{file2,-1,0}-->

EXIT 1
tab_res=["<", " ", "file1", " ", "cat", " ", "|", " ", "cat", " ", ">", " ", "file2", NULL]
tok_lst={<,10,0}-->{ ,0,0}-->{file1,-1,0}-->{ ,0,0}-->{cat,-1,0}-->{ ,0,0}-->{|,15,0}-->{ ,0,0}-->{cat,-1,0}-->{ ,0,0}-->{>,13,0}-->{ ,0,0}-->{file2,-1,0}-->
---------------------------------------------------------------------------------------> ✅
lexer(<'e'''cho toto>>file1>)-------------------------------------------------------------

after lexer:[0]={'e'''cho,-1,0}-->{ ,0,0}-->{toto,-1,0}-->{>>,14,0}-->{file1,-1,0}-->

EXIT 1
tab_res=["'e'''cho", " ", "toto", ">>", "file1", NULL]
tok_lst={'e'''cho,-1,0}-->{ ,0,0}-->{toto,-1,0}-->{>>,14,0}-->{file1,-1,0}-->
---------------------------------------------------------------------------------------> ✅
lexer(<    'e'"c"ho  toto&&echo OK||echo  KO>)--------------------------------------------

after lexer:[0]={ ,0,0}-->{'e'"c"ho,-1,0}-->{ ,0,0}-->{toto,-1,0}-->{&&,21,0}-->{echo,-1,0}-->{ ,0,0}-->{OK,-1,0}-->{||,20,0}-->{echo,-1,0}-->{ ,0,0}-->{KO,-1,0}-->

EXIT 1
tab_res=[" ", "'e'"c"ho", " ", "toto", "&&", "echo", " ", "OK", "||", "echo", " ", "KO", NULL]
tok_lst={ ,0,0}-->{'e'"c"ho,-1,0}-->{ ,0,0}-->{toto,-1,0}-->{&&,21,0}-->{echo,-1,0}-->{ ,0,0}-->{OK,-1,0}-->{||,20,0}-->{echo,-1,0}-->{ ,0,0}-->{KO,-1,0}-->
---------------------------------------------------------------------------------------> ✅

=[ B| FAIL MULTIPLES ]=====================================================================
lexer(<< << <<< <<<< <<<<< <<<<<<>)-------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<> >> >>> >>>> >>>>> >>>>>>>)-------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<| || ||| |||| ||||| ||||||>)-------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<& && &&& &&&& &&&&& &&&&&&>)-------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(< <><<<< < ||| & &&&>)--------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(< <><<<< < ||| & &&&>)--------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅

=[ C| FAIL < ]=============================================================================
lexer(<cat < |>)--------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<cat < >)---------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<cat <>)----------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅

=[ D| FAIL << ]============================================================================
lexer(<cat << |>)-------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<cat << >)--------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<cat <<>)---------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅

=[ E| FAIL <<< ]===========================================================================
lexer(<<<< |>)----------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<<<< >)-----------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<<<<>)------------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅

=[ E| FAIL > ]=============================================================================
lexer(<echo toto >|>)---------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<echo toto >>)----------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<echo toto > >)---------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅

=[ G| FAIL >> ]============================================================================
lexer(<echo toto >>|>)--------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<echo toto >>>)---------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<echo toto >> >)--------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅

=[ H| FAIL && ]============================================================================
lexer(<&&>)-------------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<echo toto&&>)----------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<&&echo toto>)----------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅

=[ I| FAIL || ]============================================================================
lexer(<||>)-------------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<echo toto||>)----------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<||echo toto>)----------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅

=[ J| FAIL | ]=============================================================================
lexer(<|>)--------------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<ls|>)------------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<|ls>)------------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅

=[ K| FAIL ERR_TYPE ]======================================================================
lexer(<<<<<>)-----------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<>>>>)------------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<|||>)------------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<&&&>)------------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<&>)--------------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
lexer(<&&&&>)-----------------------------------------------------------------------------
syntax error: Success

after lexer:[1]=NULL
---------------------------------------------------------------------------------------> ✅
──────────────────────────────
 TASK  Testable functions fetching  ✓ 
 INFO  Functions detected count: 1896

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x391d)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x41ce)
  ┗━┳━━ init_tok_lst_node at ?? (0x27c6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_operators at ?? (0x22d4)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x18a2)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x391d)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3893)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x41ce)
  ┗━┳━━ init_tok_lst_node at ?? (0x27c6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_operators at ?? (0x22d4)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x18a2)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x3893)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3809)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x41ce)
  ┗━┳━━ init_tok_lst_node at ?? (0x27c6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_operators at ?? (0x22d4)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x18a2)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x3809)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3893)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x41ce)
  ┗━┳━━ init_tok_lst_node at ?? (0x27c6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x21a6)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x188c)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x3893)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3809)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x41ce)
  ┗━┳━━ init_tok_lst_node at ?? (0x27c6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x21a6)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x188c)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x3809)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3642)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x41ce)
  ┗━┳━━ init_tok_lst_node at ?? (0x27c6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x21a6)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x188c)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x3642)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x35b8)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x41ce)
  ┗━┳━━ init_tok_lst_node at ?? (0x27c6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x21a6)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x188c)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x35b8)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x352e)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x41ce)
  ┗━┳━━ init_tok_lst_node at ?? (0x27c6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x21a6)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x188c)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x352e)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3893)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x41ce)
  ┗━┳━━ init_tok_lst_node at ?? (0x27c6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x216c)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x188c)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x3893)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3809)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_lstnew at ?? (0x41ce)
  ┗━┳━━ init_tok_lst_node at ?? (0x27c6)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x216c)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x188c)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x3809)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x391d)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x3ab4)
  ┗━┳━━ ft_substr at ?? (0x3fcb)
    ┗━┳━━ set_token_str at ?? (0x26ff)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2878)
        ┗━┳━━ build_tok_lst_split_by_operators at ?? (0x22d4)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
            ┗━┳━━ lexer at ?? (0x18a2)
              ┗━┳━━ test at ?? (0x2be4)
                ┗━━━━ main at ?? (0x391d)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3893)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x3ab4)
  ┗━┳━━ ft_substr at ?? (0x3fcb)
    ┗━┳━━ set_token_str at ?? (0x26ff)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2878)
        ┗━┳━━ build_tok_lst_split_by_operators at ?? (0x22d4)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
            ┗━┳━━ lexer at ?? (0x18a2)
              ┗━┳━━ test at ?? (0x2be4)
                ┗━━━━ main at ?? (0x3893)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3809)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x3ab4)
  ┗━┳━━ ft_substr at ?? (0x3fcb)
    ┗━┳━━ set_token_str at ?? (0x26ff)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2878)
        ┗━┳━━ build_tok_lst_split_by_operators at ?? (0x22d4)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
            ┗━┳━━ lexer at ?? (0x18a2)
              ┗━┳━━ test at ?? (0x2be4)
                ┗━━━━ main at ?? (0x3809)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3893)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x3ab4)
  ┗━┳━━ ft_substr at ?? (0x3fcb)
    ┗━┳━━ set_token_str at ?? (0x26ff)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2878)
        ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x21a6)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
            ┗━┳━━ lexer at ?? (0x188c)
              ┗━┳━━ test at ?? (0x2be4)
                ┗━━━━ main at ?? (0x3893)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3809)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x3ab4)
  ┗━┳━━ ft_substr at ?? (0x3fcb)
    ┗━┳━━ set_token_str at ?? (0x26ff)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2878)
        ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x21a6)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
            ┗━┳━━ lexer at ?? (0x188c)
              ┗━┳━━ test at ?? (0x2be4)
                ┗━━━━ main at ?? (0x3809)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3642)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x3ab4)
  ┗━┳━━ ft_substr at ?? (0x3fcb)
    ┗━┳━━ set_token_str at ?? (0x26ff)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2878)
        ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x21a6)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
            ┗━┳━━ lexer at ?? (0x188c)
              ┗━┳━━ test at ?? (0x2be4)
                ┗━━━━ main at ?? (0x3642)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x35b8)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x3ab4)
  ┗━┳━━ ft_substr at ?? (0x3fcb)
    ┗━┳━━ set_token_str at ?? (0x26ff)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2878)
        ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x21a6)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
            ┗━┳━━ lexer at ?? (0x188c)
              ┗━┳━━ test at ?? (0x2be4)
                ┗━━━━ main at ?? (0x35b8)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x352e)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x3ab4)
  ┗━┳━━ ft_substr at ?? (0x3fcb)
    ┗━┳━━ set_token_str at ?? (0x26ff)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2878)
        ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x21a6)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
            ┗━┳━━ lexer at ?? (0x188c)
              ┗━┳━━ test at ?? (0x2be4)
                ┗━━━━ main at ?? (0x352e)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3893)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x3ab4)
  ┗━┳━━ ft_substr at ?? (0x3fcb)
    ┗━┳━━ set_token_str at ?? (0x26ff)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2878)
        ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x216c)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
            ┗━┳━━ lexer at ?? (0x188c)
              ┗━┳━━ test at ?? (0x2be4)
                ┗━━━━ main at ?? (0x3893)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3809)
┏ malloc  the crash occurred when this function failed
┗━┳━━ ft_calloc at ?? (0x3ab4)
  ┗━┳━━ ft_substr at ?? (0x3fcb)
    ┗━┳━━ set_token_str at ?? (0x26ff)
      ┗━┳━━ add_new_tok_lst_node at ?? (0x2878)
        ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x216c)
          ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
            ┗━┳━━ lexer at ?? (0x188c)
              ┗━┳━━ test at ?? (0x2be4)
                ┗━━━━ main at ?? (0x3809)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x391d)
┏ malloc  the crash occurred when this function failed
┗━┳━━ init_token at ?? (0x2599)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a8)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_operators at ?? (0x22d4)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x18a2)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x391d)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3893)
┏ malloc  the crash occurred when this function failed
┗━┳━━ init_token at ?? (0x2599)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a8)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_operators at ?? (0x22d4)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x18a2)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x3893)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3809)
┏ malloc  the crash occurred when this function failed
┗━┳━━ init_token at ?? (0x2599)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a8)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_operators at ?? (0x22d4)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x18a2)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x3809)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3893)
┏ malloc  the crash occurred when this function failed
┗━┳━━ init_token at ?? (0x2599)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a8)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x21a6)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x188c)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x3893)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3809)
┏ malloc  the crash occurred when this function failed
┗━┳━━ init_token at ?? (0x2599)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a8)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x21a6)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x188c)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x3809)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3642)
┏ malloc  the crash occurred when this function failed
┗━┳━━ init_token at ?? (0x2599)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a8)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x21a6)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x188c)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x3642)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x35b8)
┏ malloc  the crash occurred when this function failed
┗━┳━━ init_token at ?? (0x2599)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a8)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x21a6)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x188c)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x35b8)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x352e)
┏ malloc  the crash occurred when this function failed
┗━┳━━ init_token at ?? (0x2599)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a8)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x21a6)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x188c)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x352e)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3893)
┏ malloc  the crash occurred when this function failed
┗━┳━━ init_token at ?? (0x2599)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a8)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x216c)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x188c)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x3893)
─────────── OUTPUT ───────────
──────────────────────────────

┏ Segmentation fault 
┗━┳━━ test at ?? (0x2da3)
  ┗━━━━ main at ?? (0x3809)
┏ malloc  the crash occurred when this function failed
┗━┳━━ init_token at ?? (0x2599)
  ┗━┳━━ init_tok_lst_node at ?? (0x27a8)
    ┗━┳━━ add_new_tok_lst_node at ?? (0x2834)
      ┗━┳━━ build_tok_lst_split_by_spaces at ?? (0x216c)
        ┗━┳━━ map_tok_lst_if_node_not_quoted at ?? (0x155d)
          ┗━┳━━ lexer at ?? (0x188c)
            ┗━┳━━ test at ?? (0x2be4)
              ┗━━━━ main at ?? (0x3809)
─────────── OUTPUT ───────────
──────────────────────────────


Function tests: 30 failed, 1866 passed, 1896 in total
Time:           89 min 28 sec
Success rate:   98 %
All tests ran


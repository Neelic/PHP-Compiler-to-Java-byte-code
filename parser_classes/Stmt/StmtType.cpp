#ifndef PHP_COMPILER_STMT_TYPE
#define PHP_COMPILER_STMT_TYPE

enum StmtType
{
    expr,
    if_stmt,
    switch_stmt,
    stmt_list,
    static_var,
    global_var,
    while_stmt,
    do_while_stmt,
    for_stmt,
    foreach_stmt,
    throw_stmt,
    try_catch_stmt,
    match_stmt,
    const_decl,
    return_stmt,
    yield_stmt,
    yield_r_arrow_stmt,
    html_stmt,
    break_stmt,
    continue_stmt,
    t_echo_stmt,
};

#endif

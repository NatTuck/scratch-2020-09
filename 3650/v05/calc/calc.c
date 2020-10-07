
#include <stdio.h>

#include "tokens.h"
#include "list.h"
#include "ast.h"
#include "parse.h"

int
main(int _ac, char* _av[])
{
    char line[100];

    while (1) {
        char* rv = fgets(line, 96, stdin);
        if (!rv) {
            break;
        }

        // tokenize
        list* toks = tokenize(line);
        //print_list(toks);

        // parse
        calc_ast* ast = parse(toks);
        //print_ast(ast);

        // eval
        int yy = ast_eval(ast);
        printf(" = %d\n", yy);
    }

    return 0;
}

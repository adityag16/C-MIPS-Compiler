#include "ast.hpp"

#include <iostream>
#include <fstream>

int main()
{
    const Expression *ast = parseAST_cin();
    ContextPtr_MIPS context_MIPS = new Context_MIPS();
    
    ast->print_MIPS(std::cout, context_MIPS);
    std::cout<<std::endl;    

    return 0;
}

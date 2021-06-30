#include "ast.hpp"

#include <iostream>
#include <fstream>

int main()
{
    const Expression *ast = parseAST_cin();
    ContextPtr context = new Context();

    ast->print_python(std::cout, context);
    std::cout<<std::endl;

    if(context->has_main()){
        std::cout << "#Boilerplate" << std::endl;
        std::cout << "if __name__ == \"__main__\":" << std::endl;
        std::cout << "    import sys" << std::endl;
        std::cout << "    ret=main()" << std::endl;
        std::cout << "    sys.exit(ret)" << std::endl;
    }

    return 0;
}

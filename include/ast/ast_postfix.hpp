#ifndef ast_postfix_hpp
#define ast_postfix_hpp

#include <string>
#include <iostream>

#include "ast_expression.hpp"

class PostfixExpression
    : public Expression
{

private:
    ExpressionPtr func_name;
    ExpressionPtr param_list;

public:
    PostfixExpression(const ExpressionPtr &func_id, const ExpressionPtr &params_id)
        : func_name(func_id), param_list(params_id)
    {}


    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        func_name->print_python(dst, context);
        dst << "(";
        if (param_list != NULL)
        {
            param_list->print_python(dst, context);
        }
        dst << ")";
    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        context->arg_reg = 4;
        if (param_list != NULL)
        {
            context->set_arg();
            param_list->print_MIPS(dst, context);
            context->set_arg();
        }

        dst << "jal ";
        context->set_func();
        func_name->print_MIPS(dst, context);
        dst << std::endl;
        dst << "nop" << std::endl;
        for(int i = context->arg_reg; i > 4; i--){
            dst << "addiu $sp,$sp,4" << std::endl;
        }
        context->set_func();
        dst << "sw $2,-4($sp)" << std::endl;
        dst << "addiu $sp,$sp,-4" << std::endl;
    }

};

#endif

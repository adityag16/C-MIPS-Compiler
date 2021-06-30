#ifndef ast_functions_hpp
#define ast_functions_hpp

#include "ast_expression.hpp"

#include <cmath>
#include <vector>
#include <iostream>

class Function
    : public Expression
{
private:
    ExpressionPtr arg;
protected:
    Function(ExpressionPtr _arg)
        : arg(_arg)
    {}
public:
    virtual ~Function()
    {
        delete arg;
    }

    virtual const char * getFunction() const =0;

    ExpressionPtr getArg() const
    { return arg; }

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        dst<<getFunction()<<"( ";
        arg->print_python(dst, context);
        dst<<" )";
    }

};

class LogFunction
    : public Function
{
public:
    LogFunction(ExpressionPtr _arg)
        : Function(_arg)
    {}

    virtual const char *getFunction() const
    { return "log"; }

};

class ExpFunction
    : public Function
{
public:
    ExpFunction(ExpressionPtr _arg)
        : Function(_arg)
    {}

    virtual const char *getFunction() const
    { return "exp"; }

};

class SqrtFunction
    : public Function
{
public:
    SqrtFunction(ExpressionPtr _arg)
        : Function(_arg)
    {}

    virtual const char *getFunction() const
    { return "sqrt"; }

};

class FunctionDec
    : public Expression
{

private:
    ExpressionPtr declaration;
    ExpressionPtr statements;

public:
    FunctionDec(const ExpressionPtr &declaration_id, const ExpressionPtr &statements_id)
        : declaration(declaration_id), statements(statements_id)
    {}


    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        context->enter_scope();
        dst << "def ";
        context->set_func();
        declaration->print_python(dst, context);
        context->set_func();
        dst << std::endl;
        std::vector<std::string> global_vars = context->get_global_vars();
        for(unsigned int i = 0; i < global_vars.size(); i++){
            context->make_indent(dst);
            dst << "global " << global_vars[i] << std::endl;
        }
        if(statements != NULL){
            statements->print_python(dst, context);
        }
        else{
            context->make_indent(dst);
            dst << "pass" << std::endl;
        }
        context->exit_scope();
    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        delete context;
        ContextPtr_MIPS new_context = new Context_MIPS();
        new_context->unset_global();

        new_context -> set_func();
        declaration->print_MIPS(dst, new_context);

        new_context -> set_func();
        if(statements!=NULL){
            statements->print_MIPS(dst, new_context);
        }
        new_context->set_global();
    }
};

class FunctionParamDec
    : public Expression
{

private:
    ExpressionPtr func_name;
    ExpressionPtr param_list;

public:
    FunctionParamDec(const ExpressionPtr &func_id, const ExpressionPtr &params_id)
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
        dst << "):";
    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        
        if(!(context->is_globl_func())){
            dst << ".globl ";
            func_name->print_MIPS(dst, context);
            dst << std::endl;
            func_name->print_MIPS(dst, context);
            dst << ":" << std::endl;
            dst << "sw $ra,-4($sp)" << std::endl;
            dst << "sw $fp,-8($sp)" << std::endl;
            dst << "move $fp, $sp" << std::endl;
            dst << "addiu $sp,$sp,-8" << std::endl;

            if (param_list != NULL)
            {
                param_list->print_MIPS(dst, context);
            }
        }
        else{
            dst << ".globl ";
            dst << func_name->get_name() << std::endl;
            context->set_globl_func();
        }
        
    }

};

#endif

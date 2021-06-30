#ifndef ast_declarations_hpp
#define ast_declarations_hpp

#include <string>
#include <iostream>

#include "ast_expression.hpp"

class Declaration
    : public Expression
{
private:
    ExpressionPtr declaration_name;

public:
    Declaration(const ExpressionPtr &declaration_id)
        : declaration_name(declaration_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        context->make_indent(dst);

        declaration_name -> print_python(dst,context);

    }
    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        declaration_name->print_MIPS(dst, context);
    }

};

class GlobalDec
    : public Expression
{
private:
    ExpressionPtr declaration_name;

public:
    GlobalDec(const ExpressionPtr &declaration_id)
        : declaration_name(declaration_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {

        declaration_name -> print_python(dst,context);

    }
    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        context->set_globl_func();
        context->set_globl_func2();
        declaration_name->print_MIPS(dst, context);
    }

};

class AssDeclaration
    : public Expression
{
private:
    ExpressionPtr declarator;
    ExpressionPtr initialiser;
public:
    AssDeclaration(const ExpressionPtr &dec_id, const ExpressionPtr &init_id)
        : declarator(dec_id), initialiser(init_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {

        declarator -> print_python(dst,context);

        if(initialiser != NULL){
            dst << " = ";
            initialiser -> print_python(dst,context);
        }
        else{
            dst << " = 0 ";
        }


    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {

        context->set_int_dec();
        context -> offset -= 4;
        declarator -> print_MIPS(dst, context);
        if(context->is_array()){
            context -> offset += 4;
        }
        context->set_int_dec();

        if(!(context->is_array())){
            if(initialiser != NULL){
                if(context->is_global()){
                    dst << initialiser->evaluate();
                    dst << std::endl;
                    dst << ".text" << std::endl;
                }
                else{
                  initialiser -> print_MIPS(dst, context);
                }
            }
            else{
                if (context->is_global()){
                    if((context->is_globl_func2())&&(context->is_globl_func())){
                        dst << "0" << std::endl;
                        dst << ".text" << std::endl;
                    }
                    else{
                        context->set_globl_func2();
                    }
                }
                else {
                    dst<<"li $2,0"<<std::endl;
                }
            }

            if (!(context->is_global())){

                dst << "sw $2,-4($sp)" << std::endl;
                dst << "addiu $sp,$sp,-4" << std::endl;
            }
        }
        else{
            context->set_array();
        }

    }
};


class DeclaratorList
    : public Expression
{
private:
    ExpressionPtr dec1_name;
    ExpressionPtr dec2_name;
public:
    DeclaratorList(const ExpressionPtr &dec1_id, const ExpressionPtr &dec2_id)
        : dec1_name(dec1_id), dec2_name(dec2_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {

        dec1_name->print_python(dst,context);

        dst << ", ";


        dec2_name->print_python(dst,context);

    }
    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        dec1_name->print_MIPS(dst, context);

        dec2_name->print_MIPS(dst, context);

    }


};

class DeclarationList
    : public Expression
{
private:
    ExpressionPtr dec1_name;
    ExpressionPtr dec2_name;
public:
    DeclarationList(const ExpressionPtr &dec1_id, const ExpressionPtr &dec2_id)
        : dec1_name(dec1_id), dec2_name(dec2_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {

        dec1_name->print_python(dst,context);

        dst << std::endl;

        dec2_name->print_python(dst,context);

    }
    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        dec1_name->print_MIPS(dst, context);

        dec2_name->print_MIPS(dst, context);

    }
};

class ParamList
    : public Expression
{
private:
    ExpressionPtr dec1_name;
    ExpressionPtr dec2_name;
public:
    ParamList(const ExpressionPtr &dec1_id, const ExpressionPtr &dec2_id)
        : dec1_name(dec1_id), dec2_name(dec2_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {

        dec1_name->print_python(dst,context);


        dst << ", ";


        dec2_name->print_python(dst,context);


    }
    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        dec1_name->print_MIPS(dst, context);

        dec2_name->print_MIPS(dst, context);

    }
};

class ParamDeclaration
    : public Expression
{
private:
    ExpressionPtr declaration_name;

public:
    ParamDeclaration(const ExpressionPtr &declaration_id)
        : declaration_name(declaration_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        declaration_name -> print_python(dst,context);

    }
    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        context -> offset -= 4;
        context -> set_param();
        declaration_name -> print_MIPS(dst, context);
        dst << "sw $2,-4($sp)" << std::endl;
        dst << "addiu $sp,$sp,-4" << std::endl;
        context -> set_param();
    }
};
#endif

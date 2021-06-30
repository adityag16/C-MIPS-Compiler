#ifndef ast_array_hpp
#define ast_array_hpp

#include "ast_expression.hpp"

class Array
    : public Expression
{
private:
    ExpressionPtr name;
    ExpressionPtr size;

public:
    Array(const ExpressionPtr& name_id,const ExpressionPtr& size_id)
        : name(name_id), size(size_id)
    {}

        virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        dst << "arrays not implimented for python" << std::endl;

    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        context->set_func();
        dst << ".data " << std::endl;
        name->print_MIPS(dst, context);
        dst << ": ";
        context->set_func();

        dst << ".space ";
        context->set_array();
        dst << size->evaluate()*4 << std::endl;
        //size->print_MIPS(dst, context);
        dst << ".text " << std::endl;
    }
};

class ArrayAccess
    : public Expression
{
private:
    ExpressionPtr name;
    ExpressionPtr index;

public:
    ArrayAccess(const ExpressionPtr& name_id,const ExpressionPtr& index_id)
        : name(name_id), index(index_id)
    {}

        virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        dst << "array accessing not implimented for python" << std::endl;

    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        dst << "la $5,";
        context->set_func();
        context->set_array();
        name->print_MIPS(dst, context);
        context->set_func();        // put address of array into $3
        dst << std::endl;
        context->set_array();

        context->set_array_access();
        index->print_MIPS(dst, context);
        context->set_array_access();
        dst << "lw $4, 0($sp)" << std::endl;    // put the index into $4
        dst << "addiu $sp,$sp,4" << std::endl;
        dst << "sll $4,$4,2" << std::endl;
        dst << "add $5, $5, $4" << std::endl;   // combine the two components of the address
        if (!(context->is_ass())){
            dst << "lw $2, 0($5)" << std::endl;       // get the value from the array cell
            dst << "sw $2, -4($sp)" << std::endl;
            dst << "addiu $sp,$sp,-4" << std::endl;
        }
        else {
            dst << "sw $10, 0($5)" << std::endl;
        }

    }
};

#endif

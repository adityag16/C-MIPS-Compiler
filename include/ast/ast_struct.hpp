#ifndef ast_struct_hpp
#define ast_struct_hpp

#include "ast_expression.hpp"

class Enum
    : public Expression
{
private: 
    ExpressionPtr enumerator_list;

public:
    Enum(const ExpressionPtr& enumerator_id)
        : enumerator_list(enumerator_id)
    {}

        virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        dst << "eumerations not implimented for python" << std::endl; 

    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        context->enum_count = -1;

        enumerator_list->print_MIPS(dst, context);

    }
};

class EnumList
    : public Expression
{
private: 
    ExpressionPtr enumerator_list;
    ExpressionPtr enumerator;

public:
    EnumList(const ExpressionPtr& enumerator_list_id, const ExpressionPtr& enumerator_id)
        : enumerator_list(enumerator_list_id), enumerator(enumerator_id)
    {}

        virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        dst << "eumerations not implimented for python" << std::endl; 

    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {

        enumerator_list->print_MIPS(dst, context);


        enumerator->print_MIPS(dst, context);
        
        
        

    }
};

class EnumAss
    : public Expression
{
private: 
    std::string name;
    ExpressionPtr value;

public:
    EnumAss(const std::string& name_id, const ExpressionPtr& value_id)
        : name(name_id), value(value_id)
    {}

        virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        dst << "eumerations not implimented for python" << std::endl; 

    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        dst << ".data" << std::endl;
        dst << name << ": .word ";

        if(value != NULL){
            context->enum_count = value->evaluate();
            dst << value->evaluate() << std::endl;
            dst << ".text" << std::endl;
        }
        else{
            context->enum_count++;
            dst << context->enum_count << std::endl;
            dst << ".text" << std::endl;
        }        

    }
};

#endif
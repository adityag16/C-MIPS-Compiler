#ifndef ast_primitives_hpp
#define ast_primitives_hpp

#include <string>
#include <iostream>
#include "ast_expression.hpp"


class Variable
    : public Expression
{
private:
    std::string id;
public:
    Variable(const std::string &_id)
        : id(_id)
    {}

    const std::string getId() const
    { return id; }

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        if(context->get_indent() == 0){
            context->add_variable(id);
        }
        if (context->is_func()&&(id == "main")){
            context->set_main();
        }
        dst<<id;
    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        if(context->is_global()){
            if(!context->is_func()){
                dst << ".data" << std::endl;
                dst << id << ": .word ";
            }
            else {
                dst<<id;
            }
        }
        else{

            if((context->is_int_dec())&&!(context->is_func())){
                context -> bindings[id] = context -> offset;

                //std::cout << id << " stored at offset " << context ->bindings[id] << std::endl;
            }

            else if (context -> is_func() && !context -> is_param()){
                dst<<id;
            }

            else if ((context->is_ass())&&!(context->is_array())&&!(context->is_array_access())) {
                if(context->bindings.find(id) != context->bindings.end()){
                    dst << "sw $10," << context->bindings[id] << "($fp)" << std::endl;
                }
                else{
                    dst << "la $2," << id << std::endl;
                    dst << "sw $10, 0($2)" << std::endl;
                }
            }

            else if(context->is_array_access()){
                if(context->bindings.find(id) != context->bindings.end()){
                    dst << "lw $2," << context->bindings[id] << "($fp)" << std::endl;
                    dst << "sw $2,-4($sp)" << std::endl;
                    dst << "addiu $sp,$sp,-4" << std::endl;
                    context->offset -= 4;
                }
                else{
                    dst << "la $2," << id << std::endl;
                    dst << "lw $2, 0($2)" << std::endl;
                    dst << "sw $2,-4($sp)" << std::endl;
                    dst << "addiu $sp,$sp,-4" << std::endl;
                    context->offset -= 4;
                }

            }

            else if ((context->is_op())||(context->is_ret())) {
                if((!(context->is_func()))&&(!(context->is_array_access()))){
                    if(context->bindings.find(id) != context->bindings.end()){
                        dst << "lw $2," << context->bindings[id] << "($fp)" << std::endl;
                        if(context -> is_op()){
                            dst << "sw $2,-4($sp)" << std::endl;
                            dst << "addiu $sp,$sp,-4" << std::endl;
                            context->offset -= 4;
                            context->unset_op();
                        }
                    }
                    else{
                        dst << "la $2," << id << std::endl;
                        dst << "lw $2, 0($2)" << std::endl;
                        if(context -> is_op()){
                            dst << "sw $2,-4($sp)" << std::endl;
                            dst << "addiu $sp,$sp,-4" << std::endl;
                            context->offset -= 4;
                            context->unset_op();
                        }
                    }
                }
            }

            else if(context -> is_param()){
                if(context -> arg_reg < 8){
                    dst << "move $2,$" << context ->arg_reg << std::endl;
                    context -> bindings[id] = context -> offset;
                    context -> arg_reg ++;
                }
                else{
                    dst << "lw $2," << (context->arg_reg - 8) * 4 << "($fp)" << std::endl;
                    context -> bindings[id] = context -> offset;
                }

            }

            else if ((context->is_arg())&&!(context->is_op())){

                dst << "lw $2," << context->bindings[id] << "($fp)" << std::endl;
                dst << "sw $2,-4($sp)" << std::endl;
                dst << "addiu $sp,$sp,-4" << std::endl;
                context->offset -= 4;

            }

            else if(context->is_switch()){
                dst << "lw $2," << context->bindings[id] << "($fp)" << std::endl;
                context->unset_switch();
            }
            else{
                if(context->bindings.find(id) != context->bindings.end()){
                    dst << "lw $2," << context->bindings[id] << "($fp)" << std::endl;
                    dst << "sw $2,-4($sp)" << std::endl;
                    dst << "addiu $sp,$sp,-4" << std::endl;
                    context->offset -= 4;
                }
                else{
                    dst << "la $2," << id << std::endl;
                    dst << "lw $2, 0($2)" << std::endl;
                    dst << "sw $2,-4($sp)" << std::endl;
                    dst << "addiu $sp,$sp,-4" << std::endl;
                    context->offset -= 4;
                }
            }
        }

    }

    virtual std::string get_name ( ) const override
    {
        return id;
    }

};

class Number
    : public Expression
{
private:
    double value;
public:
    Number(double _value)
        : value(_value)
    {}

    double getValue() const
    { return value; }

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        dst<<value;
    }
    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {

        if(context->is_array_access()){
            dst << "li $2," << value << std::endl;
            dst << "sw $2,-4($sp)" << std::endl;
            dst << "addiu $sp,$sp,-4" << std::endl;
            context->offset -= 4;
        }
        else if(context->is_case()){
            context->case_number.push_back(value);
            context->unset_case();
        }
        else{
            dst<<"li $2,"<<value<<std::endl;

            if ((context->is_arg())&&!(context->is_op())){
                dst << "sw $2,-4($sp)" << std::endl;
                dst << "addiu $sp,$sp,-4" << std::endl;
                context->offset -= 4;
            }
            else {
                if(context->is_op()){
                    dst << "sw $2,-4($sp)" << std::endl;
                    dst << "addiu $sp,$sp,-4" << std::endl;
                    context->offset -= 4;
                    context->unset_op();
                }
            }
        }
    }

    virtual int evaluate ( ) const override
    {
        return value;
    }
};


#endif

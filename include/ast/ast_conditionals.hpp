#ifndef ast_conditionals_hpp
#define ast_conditionals_hpp

#include <string>
#include <iostream>

#include "ast_expression.hpp"



class IfStatement
    : public Expression
{
private:
    ExpressionPtr condition_name;
    ExpressionPtr true_exp_name;
public:
    IfStatement(const ExpressionPtr &condition_id, const ExpressionPtr &true_exp_id)
        : condition_name(condition_id), true_exp_name(true_exp_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        context -> make_indent(dst);
        dst << "if(";
        context -> enter_scope();
        condition_name->print_python(dst,context);
        dst << "): " << std::endl;
        if(true_exp_name != NULL){
            true_exp_name->print_python(dst,context);
        }
        else{
            context -> make_indent(dst);
            dst << "pass" << std::endl;
        }
        context -> exit_scope();

    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        condition_name->print_MIPS(dst, context);
        if(context->is_op()){
            dst << "lw $9,0($sp)" << std::endl;
            dst << "addiu $sp,$sp,4" << std::endl;
            context->unset_op();
        }
        else{
            dst<<"move $9,$2" << std::endl;
        }

        std::string endifl = context->make_Label("endifl_");

        dst << "beq $9,$0," << endifl << std::endl;
        dst << "nop" << std::endl;
        if(true_exp_name!=NULL){
            true_exp_name->print_MIPS(dst, context);
        }
        dst << endifl << ":" <<  std::endl;

    }

};

class IfElseStatement
    : public Expression
{
private:
    ExpressionPtr condition_name;
    ExpressionPtr true_exp_name;
    ExpressionPtr false_exp_name;
public:
    IfElseStatement(const ExpressionPtr &condition_id, const ExpressionPtr &true_exp_id, const ExpressionPtr &false_exp_id)
        : condition_name(condition_id), true_exp_name(true_exp_id), false_exp_name(false_exp_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        context -> make_indent(dst);
        context -> enter_scope();
        dst << "if(";
        condition_name->print_python(dst, context);
        dst << "): " << std::endl;
        if(true_exp_name != NULL){
            true_exp_name->print_python(dst, context);
        }
        else{
            context -> make_indent(dst);
            dst << "pass" << std::endl;
        }
        context -> exit_scope();

        dst << std::endl;
        context -> make_indent(dst);
        context -> enter_scope();

        dst << "else: " << std::endl;
        if(false_exp_name != NULL){
            false_exp_name->print_python(dst,context);
        }
        else{
            context -> make_indent(dst);
            dst << "pass" << std::endl;
        }
        context -> exit_scope();


    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        condition_name->print_MIPS(dst, context);
        if(context->is_op()){
            dst << "lw $9,0($sp)" << std::endl;
            dst << "addiu $sp,$sp,4" << std::endl;
            context->unset_op();
        }
        else{
            dst<<"move $9,$2" << std::endl;
        }

        std::string endifl = context->make_Label("endifl_");
        std::string falsel = context->make_Label("falsel_");

        dst << "beq $9,$0," << falsel << std::endl;
        dst << "nop" << std::endl;
        if(true_exp_name!=NULL){
            true_exp_name->print_MIPS(dst, context);
        }
        dst << "beq $0,$0," << endifl << std::endl;
        dst << "nop" << std::endl;
        dst << falsel << ":" <<  std::endl;
        if(false_exp_name != NULL){
            false_exp_name->print_MIPS(dst, context);
        }
        dst << endifl << ":" <<  std::endl;

    }
};

class SwitchStatement
    : public Expression
{
private:
    ExpressionPtr condition_name;
    ExpressionPtr statement_name;
public:
    SwitchStatement(const ExpressionPtr &condition_id, const ExpressionPtr &statement_id)
        : condition_name(condition_id), statement_name(statement_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        dst << "switch not implemented for python" << std::endl;

    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        std::string endswitchl = context->make_Label("endswitchl_");
        context->scope_end_labels.push_back(endswitchl);
        std::string startswitchl = context->make_Label("startswitchl_");

        // dst << "beq $9,$0," << endifl << std::endl;
        // dst << "nop" << std::endl;
        dst << "beq $0,$0," << startswitchl << std::endl;
        dst << "nop" << std::endl;
        statement_name->print_MIPS(dst, context);

        dst << startswitchl << ":" << std::endl;
        context->set_switch();
        condition_name->print_MIPS(dst, context);
        dst<<"move $3,$2" << std::endl;
        for(uint i = 0; i < context->case_number.size(); i++){
            if((i == context->case_number.size() - 1)&&(context->is_default())){
                dst << "beq $0,$0," << context->case_start_labels[i] << std::endl;
                context->unset_default();
            }
            else {
                dst << "li $2," << context->case_number[i] << std::endl;
                dst << "beq $2,$3," << context->case_start_labels[i] << std::endl;
                //context->case_start_labels.pop_back();
                //context->case_number.pop_back();
            }
        }
        dst << endswitchl << ":" <<  std::endl;

        context->scope_end_labels.pop_back();
    }

};


#endif

#ifndef ast_iteration_hpp
#define ast_interation_hpp

#include "ast_expression.hpp"

class WhileStatement
    : public Expression
{
private:
    ExpressionPtr condition_name;
    ExpressionPtr exp_name;


public:
    WhileStatement(const ExpressionPtr &condition_id, const ExpressionPtr &exp_id)
        : condition_name(condition_id), exp_name(exp_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        context -> make_indent(dst);
        context -> enter_scope();
        dst << "while(";
        condition_name->print_python(dst,context);
        dst << "): " << std::endl;
        if (exp_name != NULL) {
            exp_name->print_python(dst,context);
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
            dst << "lw $9,0($sp)" << std::endl;
            dst << "addiu $sp,$sp,4" << std::endl;
            dst<<"move $9,$2" << std::endl;
        }

        std::string topl = context->make_Label("topl");
        context->scope_start_labels.push_back(topl);
        std::string bottoml = context->make_Label("bottoml");
        context->scope_end_labels.push_back(bottoml);

        dst << "beq $9,$0," << bottoml << std::endl;

        dst << topl << ":" << std::endl;

        if(exp_name != NULL){
            exp_name->print_MIPS(dst, context);
            dst<<"move $10,$2" << std::endl;
        }

        condition_name->print_MIPS(dst, context);
        if(context->is_op()){
            dst << "lw $9,0($sp)" << std::endl;
            dst << "addiu $sp,$sp,4" << std::endl;
            context->unset_op();
        }
        else{
            dst<<"move $9,$2" << std::endl;
        }
        dst << "bne $9,$0," << topl << std::endl;

        dst << bottoml << ":" << std::endl;
        context->scope_end_labels.pop_back();
    }

};

class ForStatement
    : public Expression
{
private:
    ExpressionPtr init_condition;
    ExpressionPtr condition;
    ExpressionPtr iteration;
    ExpressionPtr statements;


public:
    ForStatement(const ExpressionPtr &init_id, const ExpressionPtr &condition_id, const ExpressionPtr &iteration_id, const ExpressionPtr &statements_id)
        : init_condition(init_id), condition(condition_id), iteration(iteration_id), statements(statements_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        dst << "for not implimented for python" << std::endl;
    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {

        std::string topl = context->make_Label("topl");
        context->scope_start_labels.push_back(topl);
        std::string bottoml = context->make_Label("bottoml");
        context->scope_end_labels.push_back(bottoml);

        if(init_condition!=NULL){
            init_condition->print_MIPS(dst, context);
        }

        dst << topl << ":" << std::endl;

        condition->print_MIPS(dst, context);
        dst << "lw $2,0($sp)" << std::endl;
        dst << "addiu $sp,$sp,4" << std::endl;
        context->unset_op();
        dst << "beq $2,$0," << bottoml << std::endl;
        dst << "nop" << std::endl;

        if(statements != NULL){
            statements->print_MIPS(dst, context);
        }

        iteration->print_MIPS(dst, context);
        dst << "j " << topl << std::endl;
        dst << "nop" << std::endl;

        dst << bottoml << ":" << std::endl;
        context->scope_end_labels.pop_back();
    }

};

#endif

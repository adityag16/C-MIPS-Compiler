#ifndef ast_statements_hpp
#define ast_statements_hpp

#include <string>
#include <iostream>

#include "ast_expression.hpp"


class Statement
    : public Expression
{
private:
    ExpressionPtr stat_name;
public:
    Statement(const ExpressionPtr &stat_id)
        : stat_name(stat_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        context->make_indent(dst);
        stat_name->print_python(dst, context);

    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {

        stat_name->print_MIPS(dst, context);

    }
};

class StatementList
    : public Expression
{
private:
    ExpressionPtr stat1_name;
    ExpressionPtr stat2_name;
public:
    StatementList(const ExpressionPtr &stat1_id, const ExpressionPtr &stat2_id)
        : stat1_name(stat1_id), stat2_name(stat2_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {

        stat1_name->print_python(dst, context);

        dst << std::endl;

        stat2_name->print_python(dst, context);
    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {

        stat1_name->print_MIPS(dst, context);

        stat2_name->print_MIPS(dst, context);

    }
};

class ReturnStatement
    : public Expression
{
private:
    ExpressionPtr return_exp;

public:
    ReturnStatement(const ExpressionPtr &exp_id)
        : return_exp(exp_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        context->make_indent(dst);
        dst << "return ";
        if(return_exp != NULL){
            return_exp -> print_python(dst, context);
        }
    }
    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        context -> set_ret();
        return_exp -> print_MIPS(dst, context);
        context -> set_ret();

        if(context->is_op()){
            dst << "lw $2,0($sp)" << std::endl;
            dst << "addiu $sp,$sp,4" << std::endl;
        }

        dst << "move $sp,$fp" <<std::endl;
        dst << "lw $fp,-8($fp)" << std::endl;
        dst << "lw $ra,-4($sp)" << std::endl;
        dst << "jr $31" << std::endl;
        dst << "nop" << std::endl;

    }
};

class BreakStatement
    : public Expression
{
private:

public:
    BreakStatement()
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        dst << "break not implimented for python " << std::endl;
    }
    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {

        dst << "beq $0,$0," << context->scope_end_labels.back() << std::endl;

    }
};

class ContinueStatement
    : public Expression
{
private:

public:
    ContinueStatement()
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        dst << "continue not implimented for python " << std::endl;
    }
    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        dst << "beq $0,$0," << context->scope_start_labels.back() << std::endl;
    }
};

class CaseStatement
    : public Expression
{
private:
    ExpressionPtr condition;
    ExpressionPtr statement;

public:
    CaseStatement(const ExpressionPtr condition_id, const ExpressionPtr& statement_id)
        : condition(condition_id), statement(statement_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        dst << "case not implimented for python " << std::endl;
    }
    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        std::string startcasel = context->make_Label("startcasel_");
        context->case_start_labels.push_back(startcasel);
        context->set_case();

        dst << startcasel << ":" << std::endl;

        condition->print_MIPS(dst, context);
        std::vector<int> tmp_numbers;
        std::vector<std::string> tmp_labels;
        tmp_numbers = context->case_number;
        tmp_labels = context->case_start_labels;
        context->case_number.clear();
        context->case_start_labels.clear();

        statement->print_MIPS(dst, context);

        context->case_number = tmp_numbers;
        context->case_start_labels = tmp_labels;
    }
};

class DefaultStatement
    : public Expression
{
private:
    ExpressionPtr statement;

public:
    DefaultStatement(const ExpressionPtr& statement_id)
        : statement(statement_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        dst << "default not implimented for python " << std::endl;
    }
    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {

        std::string startdefaultl = context->make_Label("startdefaultl_");
        context->case_start_labels.push_back(startdefaultl);
        context->set_default();
        context->case_number.push_back(0);

        dst << startdefaultl << ":" << std::endl;

        std::vector<int> tmp_numbers;
        std::vector<std::string> tmp_labels;
        tmp_numbers = context->case_number;
        tmp_labels = context->case_start_labels;
        context->case_number.clear();
        context->case_start_labels.clear();

        statement->print_MIPS(dst, context);

        context->case_number = tmp_numbers;
        context->case_start_labels = tmp_labels;
        dst << "beq $0,$0," << context->scope_end_labels.back() << std::endl;

    }
};

class TranslationUnit
    : public Expression
{
private:
    ExpressionPtr exp1_name;
    ExpressionPtr exp2_name;
public:
    TranslationUnit(const ExpressionPtr &exp1_id, const ExpressionPtr &exp2_id)
        : exp1_name(exp1_id), exp2_name(exp2_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {

        exp1_name->print_python(dst, context);

        dst << std::endl;

        exp2_name->print_python(dst, context);
    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {

        exp1_name->print_MIPS(dst, context);

        exp2_name->print_MIPS(dst, context);
    }
};

class CompoundStatement
    : public Expression
{
private:
    ExpressionPtr declaration_list;
    ExpressionPtr statement_list;
public:
    CompoundStatement(const ExpressionPtr &declist_id, const ExpressionPtr &statlist_id)
        : declaration_list(declist_id), statement_list(statlist_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {

        declaration_list->print_python(dst, context);

        dst << std::endl;

        statement_list->print_python(dst, context);

    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {

        declaration_list->print_MIPS(dst, context);

        statement_list->print_MIPS(dst, context);

    }

};


#endif

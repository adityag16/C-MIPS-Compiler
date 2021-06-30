#ifndef ast_operators_hpp
#define ast_operators_hpp

#include <string>
#include <iostream>
#include <cmath>
#include "ast_expression.hpp"

class Operator
    : public Expression
{
private:
    ExpressionPtr left;
    ExpressionPtr right;
protected:
    Operator(ExpressionPtr _left, ExpressionPtr _right)
        : left(_left)
        , right(_right)
    {}
public:
    virtual ~Operator()
    {
        delete left;
        delete right;
    }

    virtual const std::string getOpcode() const =0;

    ExpressionPtr getLeft() const
    { return left; }

    ExpressionPtr getRight() const
    { return right; }

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        dst<<"(";
        left->print_python(dst, context);
        dst<<" ";
        dst<<getOpcode();
        dst<<" ";
        right->print_python(dst, context);
        dst<<")";
    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {

        context->set_op();
        left->print_MIPS(dst, context);

        context->set_op();
        right->print_MIPS(dst, context);

        dst << "lw $2,0($sp)" << std::endl;
        dst << "lw $3,4($sp)" << std::endl;

        if(getOpcode() == "+"){

            dst<< "add $2,$2,$3" << std::endl;

        }
        else if(getOpcode() == "-"){

            dst<< "sub $2,$3,$2" << std::endl;

        }
        else if(getOpcode() == "*"){

            dst<< "mul $2,$2,$3" << std::endl;

        }
        else if(getOpcode() == "/"){

            dst<< "div $3,$2" << std::endl;
            dst<< "mflo $2" <<std::endl;

        }
        else if(getOpcode() == "%"){

            dst<< "div $3,$2" << std::endl;
            dst<< "mfhi $2" <<std::endl;

        }
        else if(getOpcode() == "or"){

            std::string true_lbl = context->make_Label("or_true");
            std::string false_lbl = context->make_Label("or_false");

            dst << "bne $2,$0," << true_lbl << std::endl;
            dst << "nop" << std::endl;
            dst << "bne $3,$0," << true_lbl << std::endl;
            dst << "nop" << std::endl;
            dst << "li $2,0" << std::endl;
            dst << "beq $0,$0," << false_lbl << std::endl;
            dst << "nop" << std::endl;
            dst << true_lbl << ":" << std::endl;
            dst << "li $2,1" << std::endl;
            dst << false_lbl << ":" << std::endl;

        }
        else if(getOpcode() == "and"){

            std::string true_lbl = context->make_Label("and_true");
            std::string false_lbl = context->make_Label("and_false");

            dst << "beq $2,$0," << false_lbl << std::endl;
            dst << "nop" << std::endl;
            dst << "beq $3,$0," << false_lbl << std::endl;
            dst << "nop" << std::endl;
            dst << "li $2,1" << std::endl;
            dst << "beq $0,$0," << true_lbl << std::endl;
            dst << "nop" << std::endl;
            dst << false_lbl << ":" << std::endl;
            dst << "li $2,0" << std::endl;
            dst << true_lbl << ":" << std::endl;
        }
        else if(getOpcode() == "<"){

            dst << "slt $2,$3,$2" << std::endl;

        }
        else if(getOpcode() == ">>"){

            dst << "srl $2,$3,$2" << std::endl;

        }
        else if(getOpcode() == "<<"){

            dst << "sll $2,$3,$2" << std::endl;

        }
        else if(getOpcode() == "<="){

            std::string true_lbl = context->make_Label("lte_true");
            std::string false_lbl = context->make_Label("lte_false");

            dst << "beq $3,$2," << true_lbl << std::endl;
            dst << "nop" << std::endl;
            dst << "slt $2,$3,$2" << std::endl;
            dst << "beq $0,$0," << false_lbl << std::endl;
            dst << "nop" << std::endl;
            dst << true_lbl << ":" << std::endl;
            dst << "li $2,1" << std::endl;
            dst << false_lbl << ":" << std::endl;
        }
        else if(getOpcode() == ">"){

            dst << "slt $2,$2,$3" << std::endl;

        }
        else if(getOpcode() == ">="){

            std::string true_lbl = context->make_Label("gte_true");
            std::string false_lbl = context->make_Label("gte_false");

            dst << "beq $2,$3," << true_lbl << std::endl;
            dst << "nop" << std::endl;
            dst << "slt $2,$2,$3" << std::endl;
            dst << "beq $0,$0," << false_lbl << std::endl;
            dst << "nop" << std::endl;
            dst << true_lbl << ":" << std::endl;
            dst << "li $2,1" << std::endl;
            dst << false_lbl << ":" << std::endl;

        }
        else if(getOpcode() == "=="){

            std::string true_lbl = context->make_Label("eqeq_true");
            std::string false_lbl = context->make_Label("eqeq_false");

            dst << "beq $2,$3," << true_lbl << std::endl;
            dst << "nop" << std::endl;
            dst << "li $2,0" << std::endl;
            dst << "beq $0,$0," << false_lbl << std::endl;
            dst << "nop" << std::endl;
            dst << true_lbl << ":" << std::endl;
            dst << "li $2,1" << std::endl;
            dst << false_lbl << ":" << std::endl;

        }
        else if(getOpcode() == "!="){

            std::string true_lbl = context->make_Label("neeq_true");
            std::string false_lbl = context->make_Label("neeq_false");

            dst << "bne $2,$3," << true_lbl << std::endl;
            dst << "nop" << std::endl;
            dst << "li $2,0" << std::endl;
            dst << "beq $0,$0," << false_lbl << std::endl;
            dst << "nop" << std::endl;
            dst << true_lbl << ":" << std::endl;
            dst << "li $2,1" << std::endl;
            dst << false_lbl << ":" << std::endl;

        }
        else if(getOpcode() == "|"){

            dst << "or $2,$2,$3" << std::endl;

        }
        else if(getOpcode() == "&"){

            dst << "and $2,$2,$3" << std::endl;

        }
        else if(getOpcode() == "^"){

            dst << "sub $9,$0,$2" << std::endl;
            dst << "addiu $9,$9,-1" << std::endl;
            dst << "sub $10,$0,$3" << std::endl;
            dst << "addiu $10,$10,-1" << std::endl;
            dst << "or $2,$2,$3" << std::endl;
            dst << "or $3,$9,$10" <<std::endl;
            dst << "and $2,$2,$3" << std::endl;

        }

        dst << "sw $2,4($sp)" << std::endl;
        dst << "addiu $sp,$sp,4" << std::endl;
        context->offset += 4;
    }
};

class AssignmentOperator
    : public Expression
{
private:
    ExpressionPtr left;
    std::string op;
    ExpressionPtr right;

public:
    AssignmentOperator(const ExpressionPtr &left_id, const std::string &op_id, const ExpressionPtr &right_id)
        : left(left_id), op(op_id), right(right_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        left -> print_python(dst, context);
        dst << " " << op << " ";
        right -> print_python(dst, context);

    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        context->set_op();
        right->print_MIPS(dst, context);
        dst << "lw $10,0($sp)" << std::endl;

        if(op == "+="){
            context->set_op();
            left->print_MIPS(dst, context);
            dst << "lw $9,0($sp)" << std::endl;

            dst<<"add $10,$9,$10" << std::endl;
            dst << "sw $10,4($sp)" << std::endl;
            dst << "addiu $sp,$sp,4" << std::endl;
            context->offset += 4;
        }
        else if(op == "-="){
            context->set_op();
            left->print_MIPS(dst, context);
            dst << "lw $9,0($sp)" << std::endl;

            dst<<"sub $10,$9,$10" << std::endl;
            dst << "sw $10,4($sp)" << std::endl;
            dst << "addiu $sp,$sp,4" << std::endl;
            context->offset += 4;
        }
        else if(op == "*="){
            context->set_op();
            left->print_MIPS(dst, context);
            dst << "lw $9,0($sp)" << std::endl;

            dst<<"mul $10,$9,$10" << std::endl;
            dst << "sw $10,4($sp)" << std::endl;
            dst << "addiu $sp,$sp,4" << std::endl;
            context->offset += 4;
        }
        else if(op == "/="){
            context->set_op();
            left->print_MIPS(dst, context);
            dst << "lw $9,0($sp)" << std::endl;

            dst<< "div $9,$10" << std::endl;
            dst<< "mflo $10" <<std::endl;
            dst << "sw $10,4($sp)" << std::endl;
            dst << "addiu $sp,$sp,4" << std::endl;
            context->offset += 4;
        }
        else if(op == "%="){
            context->set_op();
            left->print_MIPS(dst, context);
            dst << "lw $9,0($sp)" << std::endl;

            dst<< "div $9,$10" << std::endl;
            dst<< "mfhi $10" <<std::endl;
            dst << "sw $10,4($sp)" << std::endl;
            dst << "addiu $sp,$sp,4" << std::endl;
            context->offset += 4;
        }
        else if(op == "&="){
            context->set_op();
            left->print_MIPS(dst, context);
            dst << "lw $9,0($sp)" << std::endl;

            dst << "and $10,$9,$10" << std::endl;
            dst << "sw $10,4($sp)" << std::endl;
            dst << "addiu $sp,$sp,4" << std::endl;
            context->offset += 4;
        }
        else if(op == "|="){
            context->set_op();
            left->print_MIPS(dst, context);
            dst << "lw $9,0($sp)" << std::endl;

            dst << "or $10,$9,$10" << std::endl;
            dst << "sw $10,4($sp)" << std::endl;
            dst << "addiu $sp,$sp,4" << std::endl;
            context->offset += 4;
        }
        else if(op == "^="){
            context->set_op();
            left->print_MIPS(dst, context);
            dst << "lw $9,0($sp)" << std::endl;

            dst << "xor $10,$9,$10" << std::endl;
            dst << "sw $10,4($sp)" << std::endl;
            dst << "addiu $sp,$sp,4" << std::endl;
            context->offset += 4;
        }
        else if(op == "<<="){
            context->set_op();
            left->print_MIPS(dst, context);
            dst << "lw $9,0($sp)" << std::endl;

            dst << "sll $10,$9,$10" << std::endl;
            dst << "sw $10,4($sp)" << std::endl;
            dst << "addiu $sp,$sp,4" << std::endl;
            context->offset += 4;
        }
        else if(op == ">>="){
            context->set_op();
            left->print_MIPS(dst, context);
            dst << "lw $9,0($sp)" << std::endl;

            dst << "srl $10,$9,$10" << std::endl;
            dst << "sw $10,4($sp)" << std::endl;
            dst << "addiu $sp,$sp,4" << std::endl;
            context->offset += 4;
        }

        context->set_ass();
        left->print_MIPS(dst, context);
        context->set_ass();

    }

};
class PreIncOperator
    : public Expression
{
private:
    std::string op;
    ExpressionPtr left;


public:
    PreIncOperator(const std::string& op_id, const ExpressionPtr& _left)
        : op(op_id), left(_left)
    {}

        virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        dst << "unary operator not implimented for python" << std::endl;

    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        dst << "li $10,1" << std::endl;

        if(op == "++"){
            context->set_op();
            left->print_MIPS(dst, context);
            dst << "lw $9,0($sp)" << std::endl;
            dst<<"add $10,$9,$10" << std::endl;
            dst << "sw $10,0($sp)" << std::endl;
            dst << "move $2,$10" << std::endl;
        }
        if(op == "--"){
            context->set_op();
            left->print_MIPS(dst, context);
            dst << "lw $9,0($sp)" << std::endl;
            dst<<"sub $10,$9,$10" << std::endl;
            dst << "sw $10,0($sp)" << std::endl;
            dst << "move $2,$10" << std::endl;
        }

        context->set_ass();
        left->print_MIPS(dst, context);
        context->set_ass();

    }
};

class IncOperator
    : public Expression
{
private:
    ExpressionPtr left;
    std::string op;

public:
    IncOperator(const ExpressionPtr& _left,const std::string& op_id)
        : left(_left), op(op_id)
    {}

        virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {
        dst << "unary operator not implimented for python" << std::endl;

    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        dst << "li $10,1" << std::endl;

        if(op == "++"){
            context->set_op();
            left->print_MIPS(dst, context);
            dst << "lw $9,0($sp)" << std::endl;
            dst << "move $2,$9" << std::endl;
            dst<<"add $10,$9,$10" << std::endl;
        }
        if(op == "--"){
            context->set_op();
            left->print_MIPS(dst, context);
            dst << "lw $9,0($sp)" << std::endl;
            dst << "move $2,$9" << std::endl;
            dst<<"sub $10,$9,$10" << std::endl;
        }

        context->set_ass();
        left->print_MIPS(dst, context);
        context->set_ass();

    }
};

class AddOperator
    : public Operator
{
protected:
    virtual const std::string getOpcode() const override
    { return "+"; }


public:
    AddOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

      virtual int evaluate() const override
      {

        int vl=getLeft()->evaluate();
        int vr=getRight()->evaluate();
        return vl+vr;

      }

};

class SubOperator
    : public Operator
{
protected:
    virtual const std::string getOpcode() const override
    { return "-"; }

public:
    SubOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

      virtual int evaluate() const override
      {

        int vl=getLeft()->evaluate();
        int vr=getRight()->evaluate();
        return vl-vr;

      }

};

class RightShiftOperator
    : public Operator
{
protected:
    virtual const std::string getOpcode() const override
    { return ">>"; }

public:
    RightShiftOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

      virtual int evaluate() const override
      {

        int vl=getLeft()->evaluate();
        int vr=getRight()->evaluate();
        return vl>>vr;

      }

};

class LeftShiftOperator
    : public Operator
{
protected:
    virtual const std::string getOpcode() const override
    { return "<<"; }

public:
    LeftShiftOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

      virtual int evaluate() const override
      {

        int vl=getLeft()->evaluate();
        int vr=getRight()->evaluate();
        return vl<<vr;

      }

};

class MulOperator
    : public Operator
{
protected:
    virtual const std::string getOpcode() const override
    { return "*"; }

public:
    MulOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

      virtual int evaluate() const override
      {

        int vl=getLeft()->evaluate();
        int vr=getRight()->evaluate();
        return vl*vr;

      }

};

class DivOperator
    : public Operator
{
protected:
    virtual const std::string getOpcode() const override
    { return "/"; }

public:
    DivOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

      virtual int evaluate() const override
      {

        int vl=getLeft()->evaluate();
        int vr=getRight()->evaluate();
        return vl/vr;

      }

};

class ModOperator
    : public Operator
{
protected:
    virtual const std::string getOpcode() const override
    { return "%"; }

public:
    ModOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

      virtual int evaluate() const override
      {

        int vl=getLeft()->evaluate();
        int vr=getRight()->evaluate();
        return vl%vr;

      }

};

class XOROperator
    : public Operator
{
protected:
    virtual const std::string getOpcode() const override
    { return "^"; }

public:
    XOROperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

      virtual int evaluate() const override
      {

        int vl=getLeft()->evaluate();
        int vr=getRight()->evaluate();
        return vl^vr;

      }

};

class OrOperator
    : public Operator
{
protected:
    virtual const std::string getOpcode() const override
    { return "or"; }

public:
    OrOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

      virtual int evaluate() const override
      {

        int vl=getLeft()->evaluate();
        int vr=getRight()->evaluate();
        return vl||vr;

      }

};

class AndOperator
    : public Operator
{
protected:
    virtual const std::string getOpcode() const override
    { return "and"; }

public:
    AndOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

      virtual int evaluate() const override
      {

        int vl=getLeft()->evaluate();
        int vr=getRight()->evaluate();
        return vl&&vr;

      }

};

class EqualityOperator
    : public Operator
{
protected:
    virtual const std::string getOpcode() const override
    { return "=="; }
public:
    EqualityOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

      virtual int evaluate() const override
      {

        int vl=getLeft()->evaluate();
        int vr=getRight()->evaluate();
        return vl==vr;

      }

};

class InEqualityOperator
    : public Operator
{
protected:
    virtual const std::string getOpcode() const override
    { return "!="; }
public:
    InEqualityOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

      virtual int evaluate() const override
      {

        int vl=getLeft()->evaluate();
        int vr=getRight()->evaluate();
        return vl!=vr;

      }

};

class LessThanOperator
    : public Operator
{
protected:
    virtual const std::string getOpcode() const override
    { return "<"; }
public:
    LessThanOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

      virtual int evaluate() const override
      {

        int vl=getLeft()->evaluate();
        int vr=getRight()->evaluate();
        return vl<vr;

      }

};

class LessThanEquOperator
    : public Operator
{
protected:
    virtual const std::string getOpcode() const override
    { return "<="; }
public:
    LessThanEquOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

      virtual int evaluate() const override
      {

        int vl=getLeft()->evaluate();
        int vr=getRight()->evaluate();
        return vl<=vr;

      }

};

class GreaterThanOperator
    : public Operator
{
protected:
    virtual const std::string getOpcode() const override
    { return ">"; }

public:
    GreaterThanOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

      virtual int evaluate() const override
      {

        int vl=getLeft()->evaluate();
        int vr=getRight()->evaluate();
        return vl>vr;

      }

};

class GreaterThanEquOperator
    : public Operator
{
protected:
    virtual const std::string getOpcode() const override
    { return ">="; }

public:
    GreaterThanEquOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

      virtual int evaluate() const override
      {

        int vl=getLeft()->evaluate();
        int vr=getRight()->evaluate();
        return vl>=vr;

      }

};

class BitOrOperator
    : public Operator
{
protected:
    virtual const std::string getOpcode() const override
    { return "|"; }

public:
    BitOrOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

      virtual int evaluate() const override
      {

        int vl=getLeft()->evaluate();
        int vr=getRight()->evaluate();
        return vl|vr;

      }

};

class BitAndOperator
    : public Operator
{
protected:
    virtual const std::string getOpcode() const override
    { return "&"; }

public:
    BitAndOperator(ExpressionPtr _left, ExpressionPtr _right)
        : Operator(_left, _right)
    {}

      virtual int evaluate() const override
      {

        int vl=getLeft()->evaluate();
        int vr=getRight()->evaluate();
        return vl&vr;

      }

};

class UnaryOperator
    : public Expression
{
private:
    std::string unary_op;
    ExpressionPtr exp_name;
public:
    UnaryOperator(const std::string &op_id , const ExpressionPtr &exp_id)
        : unary_op(op_id), exp_name(exp_id)
    {}

    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {

        dst << unary_op;

        exp_name->print_python(dst, context);
    }
    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {
        context->set_op();
        exp_name -> print_MIPS(dst, context);

        if(unary_op == "!"){
            std::string true_lbl = context->make_Label("not_true");
            std::string false_lbl = context->make_Label("not_false");

            dst << "lw $2,0($sp)" << std::endl;
            dst << "beq $2,$0," << false_lbl << std::endl;
            dst << "addiu $2,$2,-1" <<std::endl;
            dst << "beq $2,$2," << true_lbl << std::endl;
            dst << false_lbl << ":" << std::endl;
            dst << "addiu $2,$2,1" << std::endl;
            dst << true_lbl << ":" << std::endl;
            dst << "sw $2, 0($sp)" << std::endl;

        }
        else if(unary_op == "-"){
            dst << "lw $2,0($sp)" << std::endl;
            dst << "sub $2,$0,$2" << std::endl;
            dst << "sw $2, 0($sp)" << std::endl;
        }
        else if(unary_op == "~"){
            dst << "lw $2,0($sp)" << std::endl;
            dst << "sub $2,$0,$2" << std::endl;
            dst << "addiu $2,$2,-1" << std::endl;
            dst << "sw $2, 0($sp)" << std::endl;

        }
    }
};


#endif

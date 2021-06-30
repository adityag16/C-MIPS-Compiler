#ifndef ast_arguements_hpp
#define ast_arguements_hpp

#include <string>
#include <iostream>

#include "ast_expression.hpp"


class ArguementList
    : public Expression
{

private:
    ExpressionPtr arg1_name;
    ExpressionPtr arg2_name;

public:
    ArguementList(const ExpressionPtr &arg1_id, const ExpressionPtr &arg2_id)
        : arg1_name(arg1_id), arg2_name(arg2_id)
    {}


    virtual void print_python(std::ostream &dst, ContextPtr& context) const override
    {

        if(arg1_name!=NULL){
            arg1_name->print_python(dst, context);
            dst << ", ";
        }

        arg2_name->print_python(dst, context);

    }

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context) const override
    {

      if (arg1_name!=NULL) {
        arg1_name->print_MIPS(dst, context);
      }

      arg2_name->print_MIPS(dst, context);
      if (context->arg_reg < 8){
          dst << "lw $2,0($sp)" << std::endl;
          context->offset -= 4;
          dst << "move $" << context->arg_reg << ",$2" << std::endl;
          context->arg_reg++;
          
      }
      else{
          context->arg_reg++;
      }

  }


};

#endif

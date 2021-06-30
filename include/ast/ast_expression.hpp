#ifndef ast_expression_hpp
#define ast_expression_hpp

#include <string>
#include <iostream>
#include <map>

#include <memory>


class Expression;

typedef const Expression *ExpressionPtr;

class Expression
{
public:
    virtual ~Expression()
    {}

    //! Tell and expression to print itself to the given stream
    virtual void print_python(std::ostream &dst, ContextPtr& context) const =0;

    virtual void print_MIPS(std::ostream &dst, ContextPtr_MIPS& context_MIPS) const {};

    //! Evaluate the tree using the given mapping of variables to numbers
    virtual int evaluate( ) const
    { throw std::runtime_error("Not implemented."); }

    virtual std::string get_name( ) const
    { throw std::runtime_error("Not implemented."); }
};


#endif

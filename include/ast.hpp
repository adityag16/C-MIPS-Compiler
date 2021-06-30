#ifndef ast_hpp
#define ast_hpp

#include "context.hpp"
#include "context_MIPS.hpp"
#include "ast/ast_expression.hpp"
#include "ast/ast_postfix.hpp"
#include "ast/ast_arguements.hpp"
#include "ast/ast_declaration.hpp"
#include "ast/ast_conditionals.hpp"
#include "ast/ast_iteration.hpp"
#include "ast/ast_statements.hpp"
#include "ast/ast_primitives.hpp"
#include "ast/ast_operators.hpp"
#include "ast/ast_unary.hpp"
#include "ast/ast_functions.hpp"
#include "ast/ast_array.hpp"
#include "ast/ast_struct.hpp"

extern const Expression *parseAST_cin();
//extern const Expression *parseAST_file(std::string in_file);

#endif

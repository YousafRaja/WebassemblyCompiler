#pragma once

#include <fstream>

#include "AST.h"
#include "semantic_check.h"

extern void code_gen(semantic_context& ctx,
                     yy::node* ast,
                     std::ostream& output);

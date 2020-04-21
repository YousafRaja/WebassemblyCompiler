#include "semantic_check.h"

#include <cassert>
#include <sstream>

#include "location.hh"
#include "symtab.h"

bool globals_pre(semantic_context& ctx, yy::node* node);
void globals_post(semantic_context& ctx, yy::node* node);

bool decls_pre(semantic_context& ctx, yy::node* node);
void decls_post(semantic_context& ctx, yy::node* node);

bool type_pre(semantic_context& ctx, yy::node* node);
void type_post(semantic_context& ctx, yy::node* node);


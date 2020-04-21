#pragma once

#include <unordered_map>

#include "AST.h"
#include "symtab.h"

struct semantic_context {
    std::unordered_map<void*, int> assoc = {};
    symbol_table symtab = {};

std::unordered_map<int, int> *memMap;
std::unordered_map<int, std::vector<std::string>> *typeMap;
std::unordered_map<int, std::string> *nameMap;
std::unordered_map<std::string, bool> *gMap;
    std::string mainName="";
    int current_func_type = -1;
    int main_count = 0;
};

extern void print_annotated(semantic_context& ctx, yy::node* node);

extern semantic_context semantic_check(yy::node* node);

#pragma once
#include <string>
#include <vector>
#include <iostream>
#include <functional>



struct ASTNode {
	std::string val;
	std::vector<ASTNode*> children;
};

inline void printAstNode (std::ostream& os, ASTNode const& node, int tabDepth){
	for(int i = 0; i < tabDepth; ++i)
		os << "|\t";

	os << "| " << node.val << "\n";
	
	for(auto* n : node.children) {
		printAstNode(os, *n, tabDepth + 1);
	}
}
inline std::ostream& operator<<(std::ostream& os, ASTNode const& node) {
	printAstNode(os, node, 0);
	return os;
}





// Macros to generate the names of the different types of nodes quickly
#define NODE_TYPES()\
	X(NODE_SCOPE)\
	X(NODE_START)\
	X(NODE_TYPE)\
	X(NODE_DECL)\
	X(NODE_FDECL)\
	X(NODE_ASSN)\
	X(NODE_STMT)\
	X(NODE_LITR)\
	X(NODE_MAIN)\
	X(NODE_EMPTY)\
	X(NODE_BREAK)\
	X(NODE_RETURN)\
	X(NODE_IF)\
	X(NODE_IFELSE)\
	X(NODE_BCOND)\
	X(NODE_WHILE)\
	X(NODE_WHILE_END)\
	X(NODE_ACTUALS)\
	X(NODE_FCALL)\
	X(NODE_UNARY)\
	X(NODE_NOTUNARY)\
	X(NODE_STAR)\
	X(NODE_SLASH)\
	X(NODE_PERCT)\
	X(NODE_ADD)\
	X(NODE_SUB)\
	X(NODE_GT)\
	X(NODE_LT)\
	X(NODE_LE)\
	X(NODE_GE)\
	X(NODE_QUANT)\
	X(NODE_QUANTU)\
	X(NODE_QUANTB)\
	X(NODE_EQUALITY)\
	X(NODE_AND)\
	X(NODE_OR)\
	X(NODE_LOGIC)\
	X(NODE_BLOCK)\
	X(NODE_PARAM)\
	X(NODE_PARAM_LIST)\
	X(NODE_FHEADER)\
	X(NODE_ID)

enum ast_node_types {

#define X(NAME) NAME,
	NODE_TYPES()
#undef X
	TOTAL_NODES
};

inline char const* getName(int val)  {
	switch(val) {
#define X(NAME) case NAME: return #NAME;
		NODE_TYPES()
#undef X
		default: return "";
	}
}

#undef NODE_TYPES

enum prog_value_types {
	INT,
	BOOL,
	VOID
};

// A type to store all the information about a declaration in a node
// Covers three cases of a declaration
// 0: no declaration
// 1: an id in isolation
// 2: a declaration with a type
struct Decl {
	Decl() : valueType(0), name(), type() {}
	Decl(std::string name) : valueType(1), name(name), type() {}
	Decl(std::string name, std::vector<std::string> type) : valueType(2), name(name), type(type) {}


	std::string name;

	int valueType;
	
	std::vector<std::string> type;

	bool isGlobal;
	
};
// Function to print declarations, used in the generic function printAst
inline std::ostream& operator<<(std::ostream& os, Decl const& decl) {
	if(decl.valueType == 0)
		return os;

	os << "name=" << decl.name;
	if(decl.valueType == 2){
		os << ", type=";
		for(int i = 0;i<decl.type.size(); i++){
		 os<< decl.type[i];
		}
	}

	return os;
}

// Templated node type with some data as it's child type
template<class Data>
struct node_impl {
	int type;
	Data data;
	std::vector<node_impl<Data>*> children;
	unsigned int lineNumber;
	

};


// As node is being used in the parser, it requires them to be in the namespace yy
namespace yy {
// alias node_impl<Decl> as node
using node = node_impl<Decl>;
}

// Generic function to print ast information
template<class T>
inline void printAst(node_impl<T>* n, int depth = 0) {
	for(int i = 0; i < depth; ++i)
		std::cout << "    ";
	std::cout << getName(n->type) << "{ ";
	std::cout << n->data;
	std::cout << " }\n";

	for(auto* c : n->children) {
		printAst(c, depth + 1);
	}
}


// return value is only used during the pre-traversal to break out early!
// when pre returns false, stop traversal
// when pre returns true, continue traversal
template<class Data>
bool pre_post_traversal	(node_impl<Data>* node
			, std::function<bool(node_impl<Data>*)> pre
			, std::function<void(node_impl<Data>*)> post) {
	if(!pre(node)) 
		return false;

	for(auto* c : node->children) {
		if(!pre_post_traversal(c, pre, post))
			return false;
	}

	post(node);
	return true;
}


// implement other traversals in terms of more general traversal
template<class Data>
bool pre_traversal(node_impl<Data>* node, std::function<bool(node_impl<Data>*)> const& pre) {
	return pre_post_traversal(node, pre, [](auto*) {});
}
template<class Data>
void post_traversal(node_impl<Data>* node, std::function<void(node_impl<Data>*)> const& post) {
	pre_post_traversal(node, [](auto*) { return true; }, post);
}
	

// return value is only used during the pre-traversal to break out early!
// when pre returns false, stop traversal
// when pre returns true, continue traversal
template <class Data, class PreFunc, class PostFunc>
bool pre_post_traversal(node_impl<Data>* node, PreFunc pre, PostFunc post) {

    if (!pre(node))
        return false;

    for (auto* c : node->children) {
        if (!pre_post_traversal(c, pre, post))
            return false;
    }

    post(node);
    return true;
}

// implement other traversals in terms of more general traversal
template <class Data, class Func>
bool pre_traversal(node_impl<Data>* node, Func pre) {
    return pre_post_traversal(node, pre, [](auto*) {});
}
template <class Data, class Func>
void post_traversal(node_impl<Data>* node, Func post) {
    pre_post_traversal(
        node, [](auto*) { return true; }, post);
}










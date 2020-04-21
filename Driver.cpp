#include "Driver.h"
#include <string>
#include <fstream>
#include <streambuf>
#include "symtab.h"
#include "code_gen.h"
#include "code_gen.cpp"
#include "semantic_check.h"

bool globals_pre(semantic_context& ctx, yy::node* node);
void globals_post(semantic_context& ctx, yy::node* node);

bool decls_pre(semantic_context& ctx, yy::node* node);
void decls_post(semantic_context& ctx, yy::node* node);

bool type_pre(semantic_context& ctx, yy::node* node);
void type_post(semantic_context& ctx, yy::node* node);

#ifdef DEBUG 
#define D(x) (x)
#else 
#define D(x) do{}while(0)
#endif










namespace yy {
node* Driver::parse(std::istream* is) {
	m_ast = nullptr;
	n_ast = nullptr;
	m_lexer = std::make_unique<Lexer>(is);
	m_parser = std::make_unique<Parser>(*this);
	m_parser->parse();
	return n_ast;
}

}







// State for storing the renaming options
struct {
	int cnum = 0;
	int mnum = 100;
	std::string mainFunctionName = "";
	std::vector<std::string> etypes;
	std::string returned="";
	std::string input_file = "";
	symbol_table symtab;
} renameState;



bool renamePre(yy::node* n) {
	switch(n->type) {
		case NODE_SCOPE:
			D(std::cout << "Entering scope. symbol table contents: \n");
			renameState.symtab.push_scope();
			if(n->children[0]->data.type.size()!=1){
			D(std::cout << "Setting up parameters: \n");
			}
			break;
		default: break;
	}
	return true;
}

std::vector<std::string> getType(yy::node* n){
		D(std::cout<<"gettingType");
		D(std::cout<<"getting type for ");
		D(std::cout<<n->data.name<<"\n");	
	if(n->type==NODE_LITR){
		return {n->data.type};
	}else if(n->type==NODE_EQUALITY and n->data.name==" ="){
		D(std::cout<<"DEBUG3\n");
		D(std::cout<<"found id "<<n->children[0]->data.name<<"\n");
		D(std::cout<<"name "<<typeMap[std::stoi(n->children[0]->data.name)][0]<<"\n");
		return {typeMap[std::stoi(n->children[0]->data.name)][0]};
	}else if(n->type==NODE_LOGIC||n->type==NODE_EQUALITY||n->type==NODE_QUANTB){
		return {"boolean"};
	}else if(n->type==NODE_QUANT||n->type==NODE_QUANTU){
		return {"int"};
	}else if(n->type==NODE_FCALL){	
		D(std::cout<<"checking type map\n");	
		D(std::cout<<"at index "<<n->children[0]->data.name<<"\n");
		D(std::cout<<"which is of return type "<<typeMap[std::stoi(n->children[0]->data.name)][0]<<"\n");	
		auto res = {typeMap[std::stoi(n->children[0]->data.name)][0]}; //node's are renamed with their index id, search for "renamed";
		D(std::cout<<"returning result"<<"\n");	
		return res; //node's are renamed with their index id, search for "renamed"

	}else{
		int index = std::stoi(n->data.name);
		if(typeMap.count(index)){
			return typeMap[index];
		} else{
			std::cerr<<"Error: entry not found in typeMap for index "<<index<<"\n";
			std::cerr << "At line " << n->lineNumber << "\n";
			std::cerr << "In file " << renameState.input_file<< "\n";
			exit(1);
		}
	}
}

std::string rget(int index){
return renameState.symtab.reverseGet(index);
}

std::vector<std::string> extractTypes(std::vector<std::string> ts){
	if(ts.size()<=1)return ts;
	std::vector<std::string> r;
	r.push_back(ts[0]);
	for(int i = 0; i<ts[1].size()-1; i+=1){
		if(ts[1][i]=='b')r.push_back("boolean");
		if(ts[1][i]=='i' and ts[1][i+1]=='n')r.push_back("int");
		if(ts[1][i]=='i' and ts[1][i+1]=='d')r.push_back("void");
		if(ts[1][i]=='s'){
			r.push_back("string");
			i+=5;
		}
	}
	return r;
}

std::string preprocess(std::string s){
	std::string r = "";
	for(int i = 0; i<s.length();i++){
		if(s[i]=='\\'){
			if(i==s.length()){
			std::cerr << "Error, cannot escape last quotes of a string\n";
			exit(1);

			}
			if(s[i+1]=='b')r+='\b';
			if(s[i+1]=='t')r+='\t';
			if(s[i+1]=='n')r+='\n';
			if(s[i+1]=='f')r+='\f';
			if(s[i+1]=='r')r+='\r';
			if(s[i+1]=='\"')r+='\"';
			if(s[i+1]=='\'')r+='\'';
			if(s[i+1]=='\\')r+='\\';
			i +=1;
		} else {
			r+=s[i];
		}		
	}
	D(std::cout<<"processed string "<<r<<" \n");
	return r;
}

void declareNode(yy::node* n, bool asGlobal){
	D(std::cout<<"CNUM before: "<< renameState.cnum<<"\n");
	auto num = renameState.cnum++; 
	if(renameState.symtab.has(n->data.name)){
		if(renameState.symtab.inSameScope(n->data.name)){ //add exception: redefining only an issue within same scope
			// Should do better error handling than exiting without line numbers
			std::cerr << "Error, symbol " << n->data.name << " redefined\n";
			std::cerr << "At line " << n->lineNumber << "\n";
			std::cerr << "In file " << renameState.input_file<< "\n";
			exit(1);
		}		
	}
	else if(!renameState.symtab.insert(n->data.name, num)){		
		// Should do better error handling than exiting without line numbers
		std::cerr << "Error, symbol " << n->data.name << " unable to be inserted in symbol table\n";
		std::cerr << "At line " << n->lineNumber << "\n";
		std::cerr << "In file " << renameState.input_file<< "\n";
		exit(1);		
	}
	typeMap[num] = extractTypes(n->data.type);
	D(std::cout<<n->data.name<<" has type size of "<<typeMap[num].size()<<"\n");
	memMap[num] = -1;
	nameMap[num] = preprocess(n->data.name);
	if(gMap.count(n->data.name)==0)gMap[n->data.name] = asGlobal; 
	if(asGlobal){
	//std::cout<<n->data.name<<" IS GLOBAL*******************************************\n"; 
	}else{
	//std::cout<<n->data.name<<" IS LOCAL////////////////////////////////////////////\n"; 
	}
	D(std::cout<<"CNUM after: "<< renameState.cnum<<"\n");
}



void saveGlobals_helper(yy::node* n, std::vector<yy::node*> &gList){
	for(auto* c : n->children) {
		if(c->type==NODE_SCOPE){
			auto* child = c->children[0];//first child should be the global function or var
			declareNode(child, true);
			c->data.isGlobal = true;
			gList.push_back(child);
			
		} else if(c->type == NODE_DECL){
			declareNode(c, true);
		}
		
	}
}

void loadPredefined(){
	declareNode(new yy::node{NODE_DECL,{"id ('getchar')",{"int","void"}},{}}, true);
	declareNode(new yy::node{NODE_DECL,{"id ('halt')",{"void","void"}},{}}, true);
	declareNode(new yy::node{NODE_DECL,{"id ('printb')",{"void","boolean"}},{}}, true);
	declareNode(new yy::node{NODE_DECL,{"id ('printc')",{"void","int"}},{}}, true);
	declareNode(new yy::node{NODE_DECL,{"id ('printi')",{"void","int"}},{}}, true);
	declareNode(new yy::node{NODE_DECL,{"id ('prints')",{"void","string"}},{}}, true);

}

std::vector<yy::node*> saveGlobals(yy::node* n){
	renameState.symtab.push_scope();
	std::vector<yy::node*> gList;
	saveGlobals_helper(n, gList);
	return gList;
	
}

void checkBreaks_helper(yy::node *n, int wcount){
	for(auto* c : n->children) {
		if(c->type==NODE_BREAK){
			if(!wcount){
				std::cerr<<"Error, Break must be within a whilte statement\n";
				std::cerr << "At line " << c->lineNumber << "\n";
				std::cerr << "In file " << renameState.input_file<< "\n";
				exit(1);
			}
			checkBreaks_helper(c, wcount-1);			
		} else if(c->type == NODE_BCOND && c->data.name == "while" ){
			checkBreaks_helper(c, wcount+1);
		} else if(c->type == NODE_WHILE_END){
			checkBreaks_helper(c, wcount-1);
		} else {
			checkBreaks_helper(c, wcount);
		}
		
	}	
}

void checkBreaks(yy::node *n){
	checkBreaks_helper(n, 0);
}




void getMainBlock_helper(yy::node* n, yy::node* &t){
	if(n && n->type==NODE_SCOPE){
		if(n->data.name=="mainDecl"){
			if(n->data.type.size()!=0){
			std::cerr<<"Error, main should not have any parameters and should not return anything\n";
			std::cerr << "At line " << n->lineNumber << "\n";
			std::cerr << "In file " << renameState.input_file<< "\n";
			exit(1);
			}
			if(t!=NULL){
			std::cerr<<"Error, multiple main declarations found\n";
			std::cerr << "At line " << n->lineNumber << "\n";
			std::cerr << "In file " << renameState.input_file<< "\n";
			exit(1);
			}
			t=n;
			renameState.mainFunctionName = extractName(n->children[0]->data.name);
		}
	}
	for(yy::node* c : n->children) {
		getMainBlock_helper(c, t);
	}

}

yy::node* getMainBlock(yy::node* n){
	yy::node* m = NULL;
	getMainBlock_helper(n, m);
	if(m==NULL){
		std::cerr<<"Error, no main declaration found\n";
		std::cerr << "At line " << n->lineNumber << "\n";
		std::cerr << "In file " << renameState.input_file<< "\n";
		exit(1);
	}
	auto c = m->children[0]->children[0];
	if(c->data.name=="nullStmt"){
		std::cerr<<"Error, main declaration cannot be empty\n";
		std::cerr << "At line " << c->lineNumber << "\n";
		std::cerr << "In file " << renameState.input_file<< "\n";
		exit(1);
	}
	return c;
}

void nonvoidCheck(yy::node* n){
	if(n->children.size()==0){
		if(n->data.type[0]!="void"){
			std::cerr << "Error, non-void function missing a return type\n";
			std::cerr << "At line " << n->lineNumber << "\n";
			std::cerr << "In file " << renameState.input_file<< "\n";
			exit(1);
		}else{
			return;
		}
	}
	if(n->data.type[0]!="void" && n->children[0]->type!=NODE_RETURN){
		auto block = n->children[0];		
		int stmts = block->children.size();

		if(stmts==0 || block->children[stmts-1]->type!=NODE_RETURN){
			if(	block->children[stmts-1]->type==NODE_STMT	
	//			&& block->children[stmts-1]->children[0]->type==NODE_FCALL
	//			&& block->children[stmts-1]->children[0]->children[0]->type==NODE_ID
	//			&& block->children[stmts-1]->children[0]->children[0]->data.name=="halt"){
				){
				return;

			}
				std::cerr << "Error, the last statement executed in a non-void function must be a return statement\n";
				std::cerr << "Found "<<block->children[stmts-1]->data.name<<"\n";
				std::cerr << "At line " << n->children[0]->lineNumber << "\n";
				std::cerr << "In file " << renameState.input_file<< "\n";
				exit(1);
		}
	}
}

void renamePost(yy::node* n) {
D(std::cout << "DEBUG4\n");	
	switch(n->type) {	

		case NODE_DECL: {
			D(std::cout<<"NODE_DECL\n");
			int t = renameState.cnum;
			declareNode(n, false);
			n->data.name = std::to_string(t); // rename this node 						
		} break;


		case NODE_LITR: {
			D(std::cout<<"NODE_LITR\n");
			if(n->data.type[0]=="string"){
				int I = renameState.cnum++;
				nameMap[I] = preprocess(extractName(n->data.name)); //save name before rename
				n->data.name = std::to_string(I); // rename this node 						
				memMap[I] = renameState.mnum;
				renameState.mnum+=nameMap[I].length();
			}
		} break;



		case NODE_ID:{
			// check if symbol table has name
			D(std::cout<<"NODE_ID\n");
			if(!renameState.symtab.has(n->data.name)) {
				// Should do better error handling than exiting without line numbers
				
				std::cerr << "Error, undefined symbol " << n->data.name << "\n";
				std::cerr << "At line " << n->lineNumber << "\n";
				std::cerr << "In file " << renameState.input_file<< "\n";
				exit(1);
			} else {
				int newName = renameState.symtab.get(n->data.name);
				n->data.name = std::to_string(newName); // rename this node
			}
		}break;

		case NODE_RETURN: {
			D(std::cout<<"NODE_RETURN\n");
			if(renameState.returned==""){
			if(n->children.size()==0){
				//std::cerr << "Error, a non-void function must return a value\n";
				//std::cerr << "At line " << n->lineNumber << "\n";
				//std::cerr << "In file " << renameState.input_file<< "\n";
				//exit(1);
			}
			if(n->children.size()==0){
			renameState.returned = "void";
			}else{
			renameState.returned = getType(n->children[0])[0];
			}

			}else{
				//std::cerr << "Error, redefining return type within the same scope not allowed\n";
				//std::cerr << "At line " << n->lineNumber << "\n";
				//std::cerr << "In file " << renameState.input_file<< "\n";
				//exit(1);
			}
		} break;

		case NODE_BCOND: {
			D(std::cout<<"NODE_BCOND\n");
			if(getType(n->children[0])[0]!="boolean"){
				std::cerr<<"Error on evaluting "<<n->data.name<<" expression, only boolean types allowed\n";
				std::cerr << "At line " << n->lineNumber << "\n";
				std::cerr << "In file " << renameState.input_file<< "\n";
				exit(1);
			}
		} break;

		case NODE_LOGIC:{
			D(std::cout<<"NODE_LOGIC\n");
			if(n->data.name=="!"){
				yy::node* child = n->children[0];
				auto ctype = getType(child);
				if(ctype[0]!="boolean"){
					std::cerr<<"Error on evaluting "<<n->data.name<<" expression, only boolean types allowed\n";
					std::cerr << "At line " << n->lineNumber << "\n";
					std::cerr << "In file " << renameState.input_file<< "\n";
					exit(1);
				}
			}else{
				yy::node* left = n->children[0];
				auto ltype = getType(left);
				yy::node* right = n->children[1];
				auto rtype = getType(right);
				if(ltype!=rtype or ltype[0]!="boolean"){
					std::cerr<<"Error on evaluting "<<n->data.name<<" expression, only boolean types allowed\n";
					std::cerr << "At line " << n->lineNumber << "\n";
					std::cerr << "In file " << renameState.input_file<< "\n";
					exit(1);
				}
			}

		}break;

		case NODE_QUANTU:{
			D(std::cout<<"NODE_QUANTU\n");
			D(std::cout<<n->data.name<<"\n");
			yy::node* left = n->children[0];
			auto ltype = getType(left);
			D(std::cout<<"Left type "<<ltype[0]<<"\n");
			if(ltype[0]!="int"){
				std::cerr<<"Error on evaluting "<<n->data.name<<" expression, only int types allowed\n";
				std::cerr << "At line " << n->lineNumber << "\n";
				std::cerr << "In file " << renameState.input_file<< "\n";
				exit(1);
			}

		}break;

		case NODE_QUANT:{
			D(std::cout<<"NODE_QUANT\n");
			D(std::cout<<n->data.name<<"\n");
			yy::node* left = n->children[0];
			auto ltype = getType(left);
			D(std::cout<<"Left type "<<ltype[0]<<"\n");
			yy::node* right = n->children[1];
			auto rtype = getType(right);
			D(std::cout<<"Right type "<<rtype[0]<<"\n");
			if(ltype!=rtype or ltype[0]!="int"){
				std::cerr<<"Error on evaluting "<<n->data.name<<" expression, only int types allowed\n";
				std::cerr << "At line " << n->lineNumber << "\n";
				std::cerr << "In file " << renameState.input_file<< "\n";
				exit(1);
			}

		}break;

		case NODE_QUANTB:{
			D(std::cout<<"NODE_QUANTB\n");
			yy::node* left = n->children[0];
			auto ltype = getType(left);
			yy::node* right = n->children[1];
			auto rtype = getType(right);
			if(ltype!=rtype or ltype[0]!="int"){
				std::cerr<<"Error on evaluting "<<n->data.name<<" expression, only boolean types allowed\n";
				std::cerr << "At line " << n->lineNumber << "\n";
				std::cerr << "In file " << renameState.input_file<< "\n";
				exit(1);
			}

		}break;

		case NODE_EQUALITY:{
			D(std::cout<<"NODE_EQUALITY\n");
			yy::node* left = n->children[0];
			auto ltype = getType(left);
			yy::node* right = n->children[1];
			auto rtype = getType(right);
			if(ltype!=rtype){
				std::cerr<<"Error on evaluting "<<n->data.name<<" expression, only identical types allowed\n";
				std::cerr<<"left type : "<<ltype[0]<<"\n";
				std::cerr<<"right type : "<<rtype[0]<<"\n";
				std::cerr << "At line " << n->lineNumber << "\n";
				std::cerr << "In file " << renameState.input_file<< "\n";
				exit(1);
			}

		}break;




		case NODE_FCALL:{
			D(std::cout<<"NODE_FCALL\n");
			yy::node* fID = n->children[0];
			int index = std::stoi(fID->data.name);
			auto ep = getType(fID); //expected params
			D(std::cout<<"DEBUG5\n");
			if(ep.size()==0){
				std::cout<<"Error, main function can't be called\n";
				std::cerr << "At line " << n->lineNumber << "\n";
				std::cerr << "In file " << renameState.input_file<< "\n";
				exit(1);
			}
			yy::node* args = n->children[1];
			std::vector<std::string> vargs;
			for(auto a : args->children){
				D(std::cout<<"arg: "<<a->data.name<<"\n");
				D(std::cout<<"arg type:"<<getType(a)[0]<<"\n");
				vargs.push_back(getType(a)[0]);
			}
			int expected = ep.size()-1 - (ep[1]=="void"?1:0);

			if(expected!=vargs.size()){
				std::cerr<<"Error when making function call to "<<rget(std::stoi(fID->data.name))<<", number of arguments mis-match\n";
				std::cerr<<"Function type size: "<<ep.size()<<"\n";
				std::cerr<<"node name: "<<n->children[0]->data.name<<"\n";
				std::cerr<<"type size: "<<typeMap[std::stoi(n->children[0]->data.name)].size()<<"\n";
				std::cerr<<"Expected "<<expected<<"\n";
				std::cerr<<"Actual "<<vargs.size()<<"\n";
				std::cerr << "At line " << n->lineNumber << "\n";
				std::cerr << "In file " << renameState.input_file<< "\n";
				exit(1);
			}
			for(int i = 1;i<ep.size() && ep[1]!="void";i++){
				if(ep[i]!=vargs[i-1]){
				std::cerr<<"Error when making function call to "<<rget(std::stoi(fID->data.name))<< ", type of argument mis-match\n";
				std::cerr<<"Expected "<<ep[i]<<"\n";
				std::cerr<<"Actual "<<vargs[i-1]<<"\n";
				std::cerr << "At line " << n->lineNumber << "\n";
				std::cerr << "In file " << renameState.input_file<< "\n";
				exit(1);
				}
			}

		}break;

		case NODE_SCOPE:
			D(std::cout << "About to leave scope, symbol table contents: \n");
			D(renameState.symtab.print(std::cout));
			renameState.symtab.pop_scope();
			break;

		default: break;
	}
}





int main(int argv, char** argc) {
	if(argv != 2){
		std::cerr << "Error, only 1 argument expected, received "<<argv-1<<"\ni"; 
		return 1;
	}
	std::ifstream fis;
	fis.open(argc[1]);
	if(!fis.is_open()){
		std::cerr <<"ERROR: File not found\n";
		return 1;
	}
	renameState.input_file = argc[1];
	yy::Driver driver{};
	if(auto* ast = driver.parse(&fis)) {
		D(std::cout << "Success\n");
		D(printAst(driver.n_ast));
		loadPredefined();
		
		checkBreaks(driver.n_ast);	
		
			auto gList = saveGlobals(driver.n_ast);
		bool mainFound = false;
		for(auto c : gList) {	
D(std::cout << "DEBUG2\n");		
D(std::cout<<c->data.name<<"\n");
			renameState.symtab.push_scope();
			D(renameState.symtab.print(std::cout));
			if(c->data.type.size()!=0){		
				auto* child = c->children[0];//first child should be the global function or var
				renameState.returned = "";
				renameState.etypes = c->data.type;

				nonvoidCheck(c);

				
				for (auto subchild : c->children){
					if(subchild->type==NODE_PARAM_LIST){
						for (auto param : subchild->children){
							int t = renameState.cnum;
							declareNode(param, false);
							param->data.name = std::to_string(t); // rename this node
						}
					} 
				}
				pre_post_traversal(c->children[0], {&renamePre}, {&renamePost});

				if(renameState.etypes[0]=="void"){
					if(renameState.returned!="" && renameState.returned!="void"){
						std::cerr<<"Error, void function should not have a return\n";
						std::cerr << "At line " << c->lineNumber << "\n";
						std::cerr << "In file " << renameState.input_file<< "\n";
						return(1);
					}
				}
				if(renameState.returned=="")renameState.returned="void";
				if(renameState.returned!=renameState.etypes[0]){
					std::cerr<<"Error, function return type mis-match\n";
					std::cerr<<"Expected: "<<renameState.etypes[0]<<"\n";
					std::cerr<<"Actual: "<<renameState.returned<<"\n";
					std::cerr << "At line " << c->lineNumber << "\n";
					std::cerr << "In file " << renameState.input_file<< "\n";
					return(1);
				}
				


			}else{
D(std::cout << "DEBUG1\n");	
				mainFound = true;
				auto* child = c->children[0];//first child should be the first block
				renameState.returned="";
				pre_post_traversal(getMainBlock(driver.n_ast), {&renamePre}, {&renamePost});
				if(renameState.returned!=""){
					std::cerr<<"Error, main declaration should not have any returns\n";
					std::cerr << "At line " << c->lineNumber << "\n";
					std::cerr << "In file " << renameState.input_file<< "\n";
					return(1);
				}


			} 
			D(std::cout<<"Final states before popping\n");
			D(renameState.symtab.print(std::cout));
			renameState.symtab.pop_scope();

		}
				if(mainFound==false){
					std::cerr<<"Error, no main declaration found\n";
					std::cerr << "In file " << renameState.input_file<< "\n";
					return(1);
				}
		

		D(std::cout << "Final states\n");
		D(renameState.symtab.print(std::cout));
		D(std::cout << "\nRenamed tree\n");
		D(printAst(driver.n_ast));

	} else {
		std::cerr << "Failed parsing input file : "<<argc[1]<<"\n";
		return 1;
	}

	semantic_context ctx;
	ctx.memMap = &memMap;
	ctx.typeMap = &typeMap;
	ctx.nameMap = &nameMap;
	ctx.gMap = &gMap;
	ctx.mainName = 	renameState.mainFunctionName;

	for(auto elem : nameMap)
	{
	   D(std::cout << elem.first << " " << elem.second  << "\n");
	}

	for(auto elem : typeMap)
	{
				std::string type="";
				for (auto t : typeMap[elem.first]){
					type += t;
				}
	   D(std::cout << elem.first << " " << type  << "\n");
	}

	for(auto elem : memMap)
	{
	   D(std::cout << elem.first << " " << elem.second  << "\n");
	}


	for(auto elem : gMap)
	{
	   D(std::cout << elem.first << " " << elem.second  << "\n");
	}


	code_gen(ctx, driver.n_ast, std::cout);

  std::streambuf *psbuf, *backup;
  std::ofstream filestr;
  filestr.open ("test.txt");

  backup = std::cout.rdbuf();     // back up cout's streambuf

  psbuf = filestr.rdbuf();        // get file's streambuf
  std::cout.rdbuf(psbuf);         // assign streambuf to cout

  code_gen(ctx, driver.n_ast, std::cout);

  std::cout.rdbuf(backup);        // restore cout's original streambuf

  filestr.close();




	return 0;
}

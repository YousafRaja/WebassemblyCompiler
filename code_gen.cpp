#include "code_gen.h"
#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>

#include <cassert>
#include <sstream>
#include <unordered_set>

#include <string>  
#include <iostream> 
#include <sstream>  
#include <iomanip>
#include <ios>


#ifdef DEBUG 
#define D(x) (x)
#else 
#define D(x) do{}while(0)
#endif


std::string rtfile = "runtimeLibrary.txt";
void printRuntime(){
	std::cout << "\n";
	std::cout << std::ifstream(rtfile).rdbuf();
	std::cout << "\n";
}


void printDataTable(semantic_context& sc){
//	(data 0 (i32.const 0) "fbcdefg")
	std::cout << "\n";

	for(auto elem : (*sc.memMap)){
		if(elem.second!=-1){		
		std::cout << "(data 0 (i32.const "<<elem.second << ") \"";
			for(auto c : (*sc.nameMap)[elem.first]){
				std::ios oldState(nullptr);
				oldState.copyfmt(std::cout);
				std::cout<<"\\"<<std::setw(2) <<std::setfill('0')<<std::hex<<int(c);
				std::cout.copyfmt(oldState);
			}
		std::cout<< "\")\n";	
		}
	}


	std::cout << "\n";
}


void insert_tabs(int depth, std::ostream& os) {
	for (int i = 0; i < depth; ++i)
	        os << "    ";
}
struct decorate {
    std::function<void(yy::node*)> pre;
    std::function<void(yy::node*)> post;
};

bool isId(std:: string name){
	return (name.rfind("id ('", 0) == 0);
}



std::string extractName(std::string id){
	//if (id.rfind("id ('", 0) == 0) {
		int last = id.find_last_of("'");
		int first = id.find_first_of("'");
		int length = last-first;	
		return id.substr(first+1, length-1);
	//} else{
	//	return id;
	//}
}

bool is_number(const std::string& s)
{
    std::string::const_iterator it = s.begin();
    while (it != s.end() && std::isdigit(*it)) ++it;
    return !s.empty() && it == s.end();
}

std::string nameLookUp(semantic_context& sc,yy::node* node){
	std::string name = node->data.name;
	name = isId(name)?extractName(name):name;
	name = is_number(name)?extractName((*sc.nameMap)[std::stoi(node->data.name)]):name;
	if(name==""){
		std::cerr<<"Error:no name found for "<<node->data.name<<"\n";
		exit(1);
	}
	return name;
}

bool isGlobal(semantic_context& sc,yy::node* node){
	return (*sc.gMap)["id ('"+nameLookUp(sc,node)+"')"];
}

struct gen_context {
    struct tc_impl {};
    struct line_impl {
        int tab_depth;
        std::string message;
    };
    struct add_impl {
        std::string message;
    };
    int tab_depth = 0;
    int callDepth = 0;

    int loopTags = 0;
    std::unordered_set<std::string> ignoreGlobals; 
    std::unordered_map<yy::node*, decorate> decorations;


    add_impl add(std::string const& message, bool firstSpace = true) {
        if (firstSpace)
            return add_impl{" " + message};
        return add_impl{message};
    }

    add_impl add_name(std::string const& name) { return add("$" + name); }
    add_impl add_iconst(int val) {
        std::stringstream ss;
        ss << val;
        return add(ss.str());
    }
    add_impl add_bconst(bool val) {
        std::stringstream ss;
        ss << val;
        return add(ss.str());
    }

    add_impl add_param(std::string const& name) {
        std::stringstream ss;
        ss << "(param $" << name << " i32)";
        return add(ss.str());
    }
    add_impl add_local(std::string const& name) {
        std::stringstream ss;
        ss << "(local $" << name << " i32)";
        return add(ss.str());
    }

    tc_impl indent() {
        ++tab_depth;
        return {};
    }
    tc_impl dedent() {
        --tab_depth;
        return {};
    }

    // generates a new line tabbed in
    line_impl line(std::string const& content) { return {tab_depth, content}; }
};

std::ostream& operator<<(std::ostream& os, gen_context::line_impl const& gen) {
    os << "\n";
    insert_tabs(gen.tab_depth, os);
    return os << gen.message;
}
std::ostream& operator<<(std::ostream& os, gen_context::add_impl const& gen) {
    return os << gen.message;
}
std::ostream& operator<<(std::ostream& os, gen_context::tc_impl const& gen) {
    return os;
}

bool code_pre(gen_context& gc,
              semantic_context& ctx,
              yy::node* node,
              std::ostream& output);
void code_post(gen_context& gc,
               semantic_context& ctx,
               yy::node* node,
               std::ostream& output);

void code_gen(semantic_context& sc, yy::node* ast, std::ostream& output) {
    gen_context gc;

    pre_post_traversal(
        ast,
        [&](yy::node* node) -> bool { return code_pre(gc, sc, node, output); },
        [&](yy::node* node) { code_post(gc, sc, node, output); });
}


yy::node* findSubNode(yy::node* start, int targetType){
	for(auto* c : start->children)if(c->type==targetType)return c;
	std::cerr << "Error, findSubNode did not find the target node\n";
	exit(1);	
}

void pushIDNode(gen_context& gc,
              semantic_context& sc,
              yy::node* node,
              std::ostream& os){
		if(isGlobal(sc,node)){
			os << gc.line("") << "global.get" << gc.add_name(nameLookUp(sc,node));
		} else {
			os << gc.line("") << "local.get" << gc.add_name(nameLookUp(sc,node));
		}
}

void getFromEqualityNode(gen_context& gc,
              semantic_context& sc,
              yy::node* node,
              std::ostream& os){
	if(node->data.name==" =" and node->children[0]->type==NODE_ID){
		if(isGlobal(sc,node->children[0])){
		os << gc.line("") << "global.get" << gc.add_name(nameLookUp(sc,node->children[0]));
		} else {
		os << gc.line("") << "local.get" << gc.add_name(nameLookUp(sc,node->children[0]));
		}		
	}
}

std::string compressUnary(std::string number){
	int leadingMinus=0;
	int startNum;
	std::string r = "";
	for(int i = 0; i<number.size();i+=1){
		if(number[i]!='-'){
			startNum = i;
			break;
		}else{
			leadingMinus +=1;
		}				
	}	
	if(leadingMinus==0)return number;
	r += (leadingMinus%2==0)?"":"-";
	r += number.substr(startNum);
//	std::cout<<"FOUND "<<leadingMinus<<" leadingMinuses in "<<number<<"\n";
//	std::cout<<"COMPRESSED RESULT "<<r<<"\n";
	return r;

}

bool code_pre(gen_context& gc,
              semantic_context& sc,
              yy::node* node,
              std::ostream& os) {
	auto iter = gc.decorations.find(node);
    if (iter != gc.decorations.end()) {
        iter->second.pre(node);
    }

	if (node->type==NODE_START) {
		os << gc.add("(module", false) << gc.indent();
		os << gc.line(
		    R"((import "host" "exit" (func $exit)))");
		os << gc.line(
		    R"((import "host" "putchar" (func $putchar (param i32))))");
		os << gc.line(
		    R"((import "host" "getchar" (func $getchar (result i32))))");
	}else if (node->type==NODE_DECL && node->data.type.size()!=1) {
		std::stringstream ss;
		ss << "(func $" << extractName(node->data.name);
		os << gc.line(ss.str());
		if(node->data.type.size()>1 && node->data.type[1]!="void"){
			for(auto*p : (findSubNode(node, NODE_PARAM_LIST))->children){
				os << gc.add_param(nameLookUp(sc,p));
			}
		}
		if(node->data.type.size()>1 && node->data.type[0]!="void"){
			/*
			yy::node * rNode;
			if(node->children[0]->type==NODE_RETURN){
				rNode = node->children[0];
			} else if(node->children[0]->type==NODE_BLOCK){
				rNode =findSubNode(node->children[0], NODE_RETURN);				
			} else{
			std::cerr << "Error, expected first child of function to be a return or code block, found neither.\n";
			exit(1);
			}
			*/
			os << gc.add("(result i32)");
		}
	
		if(node->children[0]->type==NODE_BLOCK){
			for(auto*s : (findSubNode(node, NODE_BLOCK))->children){
				if(s->type==NODE_DECL){
					os << gc.add_local(nameLookUp(sc,s));
				}
			}
		} 
		int t = node->children.size();
		if(node->children[t-1]->type==NODE_PARAM_LIST){
			for(auto c : node->children[t-1]->children){
				if(isGlobal(sc,c)){
					gc.ignoreGlobals.insert(c->data.name);
					(*sc.gMap)["id ('"+nameLookUp(sc,c)+"')"] = false;
				}				
			}
		}

		os << gc.indent();
	}	else if(node->type==NODE_DECL && node->data.type.size()==1 && isGlobal(sc,node)){
			os << gc.line("(global") << gc.add_name(nameLookUp(sc,node))
			<< gc.add("(mut i32)") << gc.add("(i32.const 0)") << gc.add(")");
	}	else if(node->type==NODE_BCOND && node->data.name=="if"){
			os << gc.line("(if") << gc.indent();
			gc.decorations[node->children[0]] = {
			    [&os, &gc](yy::node*) {
				os << gc.line("(block (result i32)") << gc.indent();
			    },
			    [&os, &gc](yy::node*) { os << gc.dedent() << gc.line(")"); }};

			gc.decorations[node->children[1]] = {
			    [&os, &gc](yy::node*) { os << gc.line("(then ") << gc.indent(); },
			    [&os, &gc](yy::node*) { os << gc.dedent() << gc.line(")"); }};

	}	else if(node->type==NODE_BCOND && node->data.name=="ifElse"){
				os << gc.line("(if") << gc.indent();
				gc.decorations[node->children[0]] = {
				    [&os, &gc](yy::node*) {
					os << gc.line("(block (result i32)") << gc.indent();
				    },
				    [&os, &gc](yy::node*) { os << gc.dedent() << gc.line(")"); }};

				gc.decorations[node->children[1]] = {
				    [&os, &gc](yy::node*) { os << gc.line("(then ") << gc.indent(); },
				    [&os, &gc](yy::node*) { os << gc.dedent() << gc.line(")"); }};

				gc.decorations[node->children[2]] = {
				    [&os, &gc](yy::node*) { os << gc.line("(else ") << gc.indent(); },
				    [&os, &gc](yy::node*) { os << gc.dedent() << gc.line(")"); }};

	}	else if(node->type==NODE_BCOND && node->data.name=="while"){
			gc.loopTags +=2;
			std::string L1 = std::to_string(gc.loopTags);
			std::string L2 = std::to_string(gc.loopTags+1);
			
			os << gc.line("(block $L" +(L2)) << gc.indent();
			os << gc.line("(loop $L"+(L1)) << gc.indent();
			gc.decorations[node->children[0]] = {
			    [&os, &gc](yy::node*) {
				os << gc.line("") << gc.indent();
			    },
			    [&os, &gc](yy::node*) { os << gc.dedent() << gc.line(""); }};

			gc.decorations[node->children[1]] = {
			    [&os, &gc](yy::node*) { 
				os << gc.line("i32.eqz ")
				<< gc.line("br_if $L"+std::to_string(gc.loopTags+1))				
				<< gc.indent(); },
			    [&os, &gc](yy::node*) { 
				os << gc.line("br $L"+std::to_string(gc.loopTags))	
				<< gc.dedent() 
				<< gc.line(")"); }};




	}	else if(node->type==NODE_BREAK){
			os << gc.line("br $L"+std::to_string(gc.loopTags+1));
	}	else if(node->type==NODE_FCALL){
			gc.callDepth += 1;
	}	else if(node->type==NODE_EQUALITY){

	}	else if(node->type==NODE_ID){

	}	else if(node->type==NODE_ACTUALS){


	}		

    return true;
}



void generalComparisionCheck(gen_context& gc,
               semantic_context& sc,
               yy::node* node,
               std::ostream& os){

			if(node->children[0]->type==NODE_EQUALITY && node->children[0]->children[0]->type==NODE_ID){

				   if(isGlobal(sc, node->children[0]->children[0])){

			   		 os << gc.line("") << "global.get" << gc.add_name(nameLookUp(sc, node->children[0]->children[0]));
				}else{

					    os << gc.line("") << "local.get" << gc.add_name(nameLookUp(sc, node->children[0]->children[0]));
					}
			}

}


void code_post(gen_context& gc,
               semantic_context& sc,
               yy::node* node,
               std::ostream& os) {

	if (node->type==NODE_START) {
		os << gc.line("(start $" + sc.mainName+")") << gc.dedent();		
		printRuntime();
		printDataTable(sc);
		os << gc.line("")<<"(memory 1)";
		os << gc.dedent() << gc.line(")");
	} else if(node->type==NODE_DECL && node->data.type.size()==0){
		os << gc.dedent() << gc.line(")");
	} else if(node->type==NODE_DECL && node->data.type.size()>=2){
		if(node->data.type[0]!="void"){
			os << gc.dedent() << gc.line("(i32.const 12345))");
		} else{		
			os << gc.dedent() << gc.line(")");
		}
		int t = node->children.size();
		if(node->children[t-1]->type==NODE_PARAM_LIST){
			for(auto c : node->children[t-1]->children){
				if(gc.ignoreGlobals.find(c->data.name)!=gc.ignoreGlobals.end()){
					gc.ignoreGlobals.erase(c->data.name);
					(*sc.gMap)["id ('"+nameLookUp(sc,c)+"')"] = true;
				}						
			}
		}

	}  else if(node->type==NODE_EQUALITY && node->data.name==" ="){
				//std::cout<<"\n***EQUALITY-SET = \n";

			if(node->children[1]->type==NODE_EQUALITY){
				if(isGlobal(sc, node->children[1]->children[0])){						
			   		os << gc.line("") << "global.get" << gc.add_name(nameLookUp(sc, node->children[1]->children[0]));
				}else{
					os << gc.line("") << "local.get" << gc.add_name(nameLookUp(sc, node->children[1]->children[0]));
				}	
			}

			if(node->children[1]->type==NODE_FCALL && node->children[1]->children[0]->children.size()==0){
				
			   		os << gc.line("") << "call " << gc.add_name(nameLookUp(sc, node->children[1]->children[0]));
			}



			if(isGlobal(sc, node->children[0])){
		   		 os << gc.line("") << "global.set" << gc.add_name(nameLookUp(sc, node->children[0]));
			}else{
				    os << gc.line("") << "local.set" << gc.add_name(nameLookUp(sc, node->children[0]));
			}	


	} else if(node->type==NODE_BCOND && node->data.name=="if"){
		os << gc.dedent() << gc.line(")");
	} else if(node->type==NODE_BCOND && node->data.name=="ifElse"){
		os << gc.dedent() << gc.line(")");
	} else if(node->type==NODE_BCOND && node->data.name=="while"){
		gc.loopTags -=2;
		os << gc.dedent() << gc.line(")");
	} else if(node->type==NODE_LITR && node->data.type[0]=="int"){
	        os << gc.line("") << "i32.const" << gc.add_iconst(std::stol(compressUnary(extractName(node->data.name))));
	} else if(node->type==NODE_LITR && node->data.type[0]=="boolean"){
	        os << gc.line("") << "i32.const" << gc.add_bconst(("false"== extractName(node->data.name))? 0 : 1);
	} else if(node->type==NODE_QUANT && node->data.name=="+"){
	        os << gc.line("") << "i32.add";
	} else if(node->type==NODE_QUANT && node->data.name=="-"){
	        os << gc.line("") << "i32.sub";
	} else if(node->type==NODE_QUANT && node->data.name=="*"){
	        os << gc.line("") << "i32.mul";
	} else if(node->type==NODE_QUANT && node->data.name=="/"){
	        os << gc.line("") << "i32.div_s";
	} else if(node->type==NODE_QUANT && node->data.name=="%"){
	        os << gc.line("") << "i32.rem_s";
	} else if(node->type==NODE_QUANTB && node->data.name=="<="){
	        os << gc.line("") << "i32.le_s"; 
	} else if(node->type==NODE_QUANTB && node->data.name=="<"){
	        os << gc.line("") << "i32.lt_s"; 
	} else if(node->type==NODE_QUANTB && node->data.name==">"){
	        os << gc.line("") << "i32.gt_s"; 
	} else if(node->type==NODE_QUANTB && node->data.name==">="){
	        os << gc.line("") << "i32.ge_s"; 
	} else if(node->type==NODE_EQUALITY && node->data.name=="=="){
		generalComparisionCheck(gc, sc, node, os);
	        os << gc.line("") << "i32.eq";
	} else if(node->type==NODE_EQUALITY && node->data.name=="!="){
		generalComparisionCheck(gc, sc, node, os);
	        os << gc.line("") << "i32.ne";
	} else if(node->type==NODE_ID){	
				//std::cout<<"\n***ID-GET = \n";
				//std::cout<<"name = "<<nameLookUp(sc,node)<<"\n";


		if(node->children.size()==0 ){	
				
			if(isGlobal(sc,node)){
					os << gc.line("") << "global.get" << gc.add_name(nameLookUp(sc, node));
			} else {
				os << gc.line("") << "local.get" << gc.add_name(nameLookUp(sc, node));
			}

		} 

	} else if(node->type==NODE_FCALL){

		if(nameLookUp(sc, node->children[0])=="prints"){
			//int I = stoi(node->children[1]->children[0]->data.name);
			//for(auto c : 

			
			int I = stoi(node->children[1]->children[0]->data.name);
			int s_mI = (*sc.memMap)[I]; 
			int e_mI = s_mI + (*sc.nameMap)[I].size(); 
			 os << gc.line("") << "i32.const " << s_mI;
			 os << gc.line("") << "i32.const " << e_mI;
			
			
		} 
		os << gc.line("") << "call " << gc.add_name(nameLookUp(sc, node->children[0]));
		if(nameLookUp(sc, node->children[0])=="halt"){
			 os << gc.line("") << "unreachable";
			
		} 
		if((*sc.typeMap)[stoi(node->children[0]->data.name)][0]!="void" ){//&& gc.callDepth==1 TO-DO : Handle getchar() 
			//os << gc.line("") << "drop"; 
		} else {
			//std::cout<<(*sc.typeMap)[stoi(node->children[0]->data.name)][0]<<" IS NOT VOID\n";
		}
		gc.callDepth -= 1;
	} else if(node->type==NODE_IF){
		os << gc.dedent() << gc.line(")");
	} else if(node->type==NODE_ACTUALS){
		for(auto c : node->children){
			if(c->type==NODE_EQUALITY){
				getFromEqualityNode(gc, sc, c, os);
			}
			if(c->type==NODE_QUANT && c->data.name=="-"){
				//std::cout<<"DEBUG\n";
	        		//os << gc.line("") << "i32.const " << gc.add_iconst(std::stol(compressUnary(extractName(c->children[1]->data.name))));
			       // os << gc.line("") << "i32.sub";				
			}
		}	
	} else if(node->type==NODE_RETURN){
		if(node->children.size()!=0){
			if(node->children[0]->type==NODE_EQUALITY && node->children[0]->data.name==" ="){
				if(node->children[0]->children[0]->type==NODE_ID){
					if(isGlobal(sc,node->children[0]->children[0])){
					os << gc.line("") << "global.get" << gc.add_name(nameLookUp(sc,node->children[0]->children[0]));
					} else {
					os << gc.line("") << "local.get" << gc.add_name(nameLookUp(sc,node->children[0]->children[0]));
					}		
				}
			}
		}
			os << gc.line("return");
	} else if(node->type==NODE_LOGIC && node->data.name=="&&"){
			os << gc.line("i32.and");
	} else if(node->type==NODE_SCOPE && node->data.name=="fcnDecl"){
			/*
			std::string r = node->children[0]->data.type[0];
			if(r!="" and r!="void"){
				os << gc.line("i32.const 0");
				os << gc.line("return");
			}
			*/
	} else if(node->type==NODE_LOGIC && node->data.name=="||"){
			os << gc.line("i32.or");
	} else if(node->type==NODE_LOGIC && node->data.name=="!"){
			os << gc.line("i32.const 1");
			os << gc.line("i32.xor");
	} else if(node->type==NODE_STMT){
		if(node->children[0]->type==NODE_FCALL){
			if((*sc.typeMap)[stoi(node->children[0]->children[0]->data.name)][0]!="void"){
				os << gc.line("drop");
			}
		}
	}	


    
    auto iter = gc.decorations.find(node);
    if (iter != gc.decorations.end()) {
        iter->second.post(node);
    }
}

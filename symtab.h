#pragma once
#include <iostream>

#include <unordered_map>
#include <vector>


std::unordered_map<int, int> memMap;
std::unordered_map<int, std::vector<std::string>> typeMap;
std::unordered_map<int, std::string> nameMap;
std::unordered_map<std::string, bool> gMap;

struct symbol_table {
	symbol_table() : m_tables() { push_scope(); }

	bool has(std::string const& name) {
		for(int i = m_tables.size() - 1; i >= 0; --i) {
			if(m_tables[i].find(name) != m_tables[i].end()){
				//std::cout<<"Earlier definition in "<<(i==1?"global":"local")<<" scope"<<"\n";
				return true;
				}
		}
		return false;
	}

	bool inSameScope(std::string const& name) {
		std::vector<int> scopes;
		for(int i = m_tables.size() - 1; i >= 0; --i) {
			if(m_tables[i].find(name) != m_tables[i].end() && i!=0){
				scopes.push_back(i);
				}
		}
		return scopes[0]==scopes[1];
	}

	int get(std::string const& name) {
		for(int i = m_tables.size() - 1; i >= 0; --i) {
			auto iter = m_tables[i].find(name);
			if(iter != m_tables[i].end())
				return iter->second;
		}
		std::cerr <<"Error, "<< name << " was not in symbol table\n";
		exit(8);
	}

	std::string reverseGet(int index){
		for(int i = m_tables.size() - 1; i >= 0; --i) {
			std::unordered_map<std::string, int> m = m_tables[i];
			for(auto pair : m){
				if(m[pair.first]==index)return pair.first;
			}
		}
		std::cerr << index << " was not in symbol table\n";
		exit(8);
	}

	bool insert(std::string const& name, int val) {
		auto& current = m_tables.back(); 
		return current.try_emplace(name, val).second;
	}

	bool set(std::string const& name, int val) {
		for(int i = m_tables.size() - 1; i >= 0; --i) {
			auto iter = m_tables[i].find(name);
			if(iter != m_tables[i].end())
				return iter->second = val;
		}
		std::cerr << name << " was not in symbol table\n";
		exit(8);
	}
	
	void push_scope() { m_tables.push_back({}); }
	void pop_scope() { m_tables.pop_back(); }

	void print(std::ostream& os) const{
		int scopeNum = m_tables.size() - 1;
		for(auto i = m_tables.crbegin(); i != m_tables.crend(); ++i) {
			os << "Scope " << scopeNum << "\n";
			int numelems = 0;
			for(auto& e : *i)  {
				std::string type="";
				for (auto t : typeMap[e.second]){
					type += t;
				}
				os << "\t(" << e.first << ", " << e.second << ","<<type<<","<<memMap[e.second]<<")\n";
				++numelems;
			}
			if(numelems == 0)
				os << "\t<< SCOPE " << scopeNum << " EMPTY  >>\n";
			--scopeNum;
		}
	}


	std::vector<std::unordered_map<std::string, int>> m_tables;
};



std::ostream& operator<<(std::ostream& os, symbol_table const& table) {
	table.print(os);
	return os;
}

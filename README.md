# WebassemblyCompiler

## Description

Compiles JMinusMinus code to WAT code which can then be run through a WASM interpretor.

## WAT

WAT stands for WebAssembly Text Format. For more information, see https://developer.mozilla.org/en-US/docs/WebAssembly

## JMinusMinus

A subset of Java. For more information, see J--LanguageSpec.txt.

## How to run 

1. Make sure you have the correct version of Bison and Flex installed, run make all. 
2. Run ./compiler.out and pass in a file with J-- code and redirect the output to another file. For example, 
./compiler.out input.txt > output 
3. The output file should now contain WAT code and can be sent to a WASM interpretor. 

## How it works

###### Lexical Analysis 

The input file goes through a lexical analysis which is implemented in lex.l using the Flex library. 

###### Defining the Grammar 

After passing lexical analysis it is sent to the parser which constructs the AST as per the J-- specs, this is handled in parser.yy.

###### Semantic Checking

Driver.cpp handles the semantic checking of the AST. It also annotates the AST and defines data structures which will be referenced during code generation.

###### Code Generation 

code_gen.cpp is where the actual WAT code is generated by traversing the AST and using the data structures previously defined.

###### Runtime Library.

runtimeLibrary.txt contains functions which are added in to the final WAT output during code generation.




  

## Requirements

Ubuntu 18.04

Bison 3.0.4

Flex 2.6.1

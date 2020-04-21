all: compiler.out

parser.source: parser.yy
	bison parser.yy
	bison -d parser.yy

lex.yy.cc: parser.source lex.l
	flex -o lex.yy.cc lex.l

compiler.out: Driver.cpp Driver.h lex.yy.cc parser.source semantic_check.cpp code_gen.cpp
	g++ -std=c++17 -o compiler.out Driver.cpp lex.yy.cc parser.tab.cc

clean:
	rm *.cc *.hh *.out
	
testall: testset1 testset2 testset3

testset1: test1 test2 test3 test4 test5 test6 test7 test8 test9 test10 test11 test12 test13 test14
       
testset2: test15 test16 
	
testset3: test17 test18 test19 test20

test: compiler.out
	@echo "\-----STARTING TEST t:-----\n"
	./compiler.out gen.t22 > input1
	~aycock/411/bin/wat2wasm input1
	~aycock/411/bin/wasm-interp --411 input1.wasm
	@echo "-----DONE-----"
	
testb: compiler.out
	@echo "\-----STARTING TEST tB:-----\n"		
	~aycock/411/bin/wat2wasm input1
	~aycock/411/bin/wasm-interp --411 input1.wasm
	@echo "-----DONE-----"	

test1: compiler.out
	@echo "\-----STARTING TEST t1:-----\n"
	./compiler.out gen.t1 > t1
	~aycock/411/bin/wat2wasm t1
	~aycock/411/bin/wasm-interp --411 t1.wasm
	@echo "-----DONE-----"

test2: compiler.out
	@echo "\nmakefile:-----STARTING TEST t5:-----\n" 
	./compiler.out gen.t5 > t5	
	~aycock/411/bin/wat2wasm t5
	~aycock/411/bin/wasm-interp --411 t5.wasm
	@echo "-----DONE-----"

test3: compiler.out
	@echo "\nmakefile:-----STARTING TEST t10:-----\n" 
	./compiler.out gen.t10 > t10	
	~aycock/411/bin/wat2wasm t10
	~aycock/411/bin/wasm-interp --411 t10.wasm
	@echo "-----DONE-----"

test4: compiler.out
	@echo "\nmakefile:-----STARTING TEST t11:-----\n" 
	./compiler.out gen.t11 > t11	
	~aycock/411/bin/wat2wasm t11
	~aycock/411/bin/wasm-interp --411 t11.wasm
	@echo "-----DONE-----"

test5: compiler.out
	@echo "\nmakefile:-----STARTING TEST t12:-----\n" 
	./compiler.out gen.t12 > t12	
	~aycock/411/bin/wat2wasm t12
	~aycock/411/bin/wasm-interp --411 t12.wasm
	@echo "-----DONE-----"

test6: compiler.out
	@echo "\nmakefile:-----STARTING TEST t13:-----\n"
	./compiler.out gen.t13 > t13	
	~aycock/411/bin/wat2wasm t13
	~aycock/411/bin/wasm-interp --411 t13.wasm
	@echo "-----DONE-----"

test7: compiler.out
	@echo "\nmakefile:-----STARTING TEST t14:-----\n" 
	./compiler.out gen.t14 > t14	
	~aycock/411/bin/wat2wasm t14
	~aycock/411/bin/wasm-interp --411 t14.wasm
	@echo "-----DONE-----"

test8: compiler.out
	@echo "\nmakefile:-----STARTING TEST t15:-----\n" 
	./compiler.out gen.t15 > t15	
	~aycock/411/bin/wat2wasm t15
	~aycock/411/bin/wasm-interp --411 t15.wasm
	@echo "-----DONE-----"

test9: compiler.out
	@echo "\nmakefile:-----STARTING TEST t18:-----\n" 
	./compiler.out gen.t18 > t18	
	~aycock/411/bin/wat2wasm t18
	~aycock/411/bin/wasm-interp --411 t18.wasm
	@echo "-----DONE-----"

test10: compiler.out
	@echo "\nmakefile:-----STARTING TEST t22:-----\n" 
	./compiler.out gen.t22 > t22	
	~aycock/411/bin/wat2wasm t22
	~aycock/411/bin/wasm-interp --411 t22.wasm
	@echo "-----DONE-----"

test11: compiler.out
	@echo "\nmakefile:-----STARTING TEST t26:-----\n"
	./compiler.out gen.t26 > t26	
	~aycock/411/bin/wat2wasm t26
	~aycock/411/bin/wasm-interp --411 t26.wasm
	@echo "-----DONE-----"

test12: compiler.out
	@echo "\nmakefile:-----STARTING TEST t29:-----\n" 
	./compiler.out gen.t29 > t29	
	~aycock/411/bin/wat2wasm t29
	~aycock/411/bin/wasm-interp --411 t29.wasm
	@echo "-----DONE-----"

test13: compiler.out
	@echo "\nmakefile:-----STARTING TEST t30:-----\n" 
	./compiler.out gen.t30 > t30	
	~aycock/411/bin/wat2wasm t30
	~aycock/411/bin/wasm-interp --411 t30.wasm
	@echo "-----DONE-----"

test14: compiler.out
	@echo "\nmakefile:-----STARTING TEST t31:-----\n" 
	./compiler.out gen.t31 > t31	
	~aycock/411/bin/wat2wasm t31
	~aycock/411/bin/wasm-interp --411 t31.wasm
	@echo "-----DONE-----"

test15: compiler.out
	@echo "\nmakefile:-----STARTING TEST t32:-----\n" 
	./compiler.out gen.t32 > t32	
	~aycock/411/bin/wat2wasm t32
	~aycock/411/bin/wasm-interp --411 t32.wasm
	@echo "-----DONE-----"
	
test16: compiler.out
	@echo "\nmakefile:-----STARTING TEST t33:-----\n" 
	./compiler.out gen.t33 > t33	
	~aycock/411/bin/wat2wasm t33
	~aycock/411/bin/wasm-interp --411 t33.wasm	
	@echo "-----DONE-----"
	
test17: compiler.out
	@echo "\nmakefile:-----STARTING TEST t34:-----\n" 
	./compiler.out gen.t34 > t34	
	~aycock/411/bin/wat2wasm t34
	~aycock/411/bin/wasm-interp --411 t34.wasm	
	@echo "-----DONE-----"
	
test18: compiler.out
	@echo "\nmakefile:-----STARTING TEST art-life:-----\n" 
	./compiler.out art-life.j-- > art-life	
	~aycock/411/bin/wat2wasm art-life
	~aycock/411/bin/wasm-interp --411 art-life.wasm		
	@echo "-----DONE-----"
	
test19: compiler.out
	@echo "\nmakefile:-----STARTING TEST art-select:-----\n" 
	./compiler.out art-select.j-- > art-select	
	~aycock/411/bin/wat2wasm art-select
	~aycock/411/bin/wasm-interp --411 art-select.wasm			
	@echo "-----DONE-----"
	
test20: compiler.out
	@echo "\nmakefile:-----STARTING TEST art-sieve:-----\n" 
	./compiler.out art-sieve.j-- > art-sieve	
	~aycock/411/bin/wat2wasm art-sieve
	~aycock/411/bin/wasm-interp --411 art-sieve.wasm				
	@echo "-----DONE-----"

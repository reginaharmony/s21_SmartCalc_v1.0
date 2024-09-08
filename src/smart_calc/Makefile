# ======================= GLOSSARY ⊂(｡•́‿•̀｡⊃)

GCC = gcc -Wall -Werror -Wextra -std=c11 -pedantic -g 
GCOV= -fprofile-arcs -ftest-coverage
LC = -lcheck
ifeq ($(shell uname), Linux)
	LC += -lpthread -lrt -lsubunit -lm
endif

LIB = s21_calc.a
TESTS = tests.c
TESTN = test
CLANG = clang-format -style=Google

APP = smart_calc
BKEND = calculate.c
BKEND_O = calculate.o

# ======================= TARGETS ⊂(｡•́‿•̀｡⊃)

all: install

build:
	mkdir build && cd ./build/ && qmake ../ && make

install: build
	mv build/$(APP).app $(HOME)/Desktop/

uninstall:
	rm -rf $(HOME)/Desktop/$(APP).app && make clean

dvi:
	cd ../../ && open README.md

dist:
	rm -rf Distribut_SmartCalc_v1.0/
	mkdir Distribut_SmartCalc_v1.0/
	mkdir Distribut_SmartCalc_v1.0/src
	cp Makefile *.c *.h *.pro *.cpp *.ui Distribut_SmartCalc_v1.0/src/
	tar czf Distribut_SmartCalc_v1.0.tgz Distribut_SmartCalc_v1.0/
	mv Distribut_SmartCalc_v1.0.tgz $(HOME)/Desktop/
	rm -rf Distribut_SmartCalc_v1.0/

clean:
	rm -rf report *.o *.a *.gcda *.gcno *.info *.log *.dSYM
	rm -rf s21_* build $(TESTN) $(TESTN)_html
	rm -rf *.pro.user 

rebuild: clean all


# ======================= CHECKS ⊂(｡•́‿•̀｡⊃)

$(LIB):
	$(GCC) $(BKEND) -c && ar rc $(LIB) $(BKEND_O) && rm *.o

test: $(LIB)
	$(GCC) $(TESTS) $(LIB) $(LC) -o test -I/opt/homebrew/include 
	./$(TESTN)

gcov_report: $(LIB) test
	$(GCC) $(TESTS) $(BKEND) $(LIB) $(LC) $(GCOV) -o $(TESTN) -I/opt/homebrew/include && ./$(TESTN)
	lcov -t $(TESTS) -o $(TESTN).info -c -d .
	genhtml -o $(TESTN)_html $(TESTN).info
	open ./$(TESTN)_html/index.html

style:
	$(CLANG) -n *.c *.h *.cpp && $(CLANG) -i *.c *.h *.cpp

leaks: clean test
	CK_FORK=no leaks -atExit -- ./$(TESTN) $t > $(TESTN)leaks.log
	open $(TESTN)leaks.log

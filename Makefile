CC = gcc -std=c11
C_LIBS = -lm -lcheck -lpthread
CFLAGS = -Wall -Wextra -Werror -D_GNU_SOURCE
SOURCES = $(wildcard s21_*.c)
OBJECTS = $(SOURCES:.c = .o)
APP = build/3DViewer_v1.app
# LOL = /Applications/Qt/6.2.4/macos/bin/qmake6

# ifeq ($(shell uname -s),Linux)
# 	TEST_FLAGS += -lrt -lsubunit
# else ifeq ($(shell uname -s),Darwin)
# 	C_LIBS += $(shell pkg-config --libs check)
# 	CFLAGS += $(shell pkg-config --cflags check)
# endif

all: clean s21_3dviewer.a

install: uninstall
	mkdir build
	make && cd build && qmake ../3DViewer_v1 && make
	@make open_app

open_app:
	open $(APP)

uninstall: clean
	rm -rf build

dvi:
	open ./html/index.html

dist: clean
	mkdir s21_3dviewer_archive
	cp -r Makefile $(SOURCES) include tests 3DViewer_v1 s21_3dviewer_archive/
	tar cvzf s21_3dviewer_archive.tgz s21_3dviewer_archive/

tests: all
	$(CC) $(CFLAGS) ./tests/*.c s21_3dviewer.a -Linclude -ls21_matrix $(C_LIBS) -o test
	./test
	-rm -rf *.o ./tests/*.o test *.a

s21_3dviewer.a:
	$(CC) $(CFLAGS) -c $(SOURCES)
	ar rcs s21_3dviewer.a *.o
	ranlib s21_3dviewer.a

gcov_flag:
	$(eval CFLAGS += --coverage)

gcov_report: clean gcov_flag tests
	mkdir -p gcov
	lcov --capture --directory . --output-file coverage.info
	genhtml coverage.info --output-directory gcov
	rm -rf *.gcno *.gcda *.gcov
	open ./gcov/index.html

style:
	clang-format -i $(SOURCES) tests/*.c ./include/*.h --style=google

clean:
	rm -rf *.o ./tests/*.o test *.gcno *.gcda *.gcov *.info *.tgz *.a
	-rm -rf s21_3dviewer_archive
	-rm -rf gcov

rebuild: clean all

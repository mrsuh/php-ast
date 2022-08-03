UNAME := $(shell uname -s)
COMMAND := @echo Invalid operation system: $(UNAME)
HFOLDERS := -I php-src/Zend -I php-src  -I php-src/ext -I php-src/main -I php-src/TSRM -I library
HICONV :=
LIB :=

ifeq ($(UNAME), Linux)
	COMMAND := gcc -fPIC -shared
	LIB := library/ast_linux.so
endif

ifeq ($(UNAME), Darwin)
	COMMAND := clang -shared -undefined dynamic_lookup -Wattributes
	LIB := library/ast_darwin.dylib
	HICONV := --with-iconv=$(shell brew --prefix libiconv)
endif

all: clean
	$(COMMAND) $(HFOLDERS) -o $(LIB) library/ast.c

debug: clean
	$(COMMAND) $(HFOLDERS) -g -D DEBUG -o $(LIB) library/ast.c

.PHONY: clean
clean:
	rm -rf $(LIB)

.PHONY: php-src
php-src:
	cd php-src && ./buildconf --force
	cd php-src && ./configure --disable-all $(HICONV)


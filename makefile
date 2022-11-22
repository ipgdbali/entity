.PHONY : clean

DIR_DEST = bin
DIR_INCLUDE = src iface 

FILES =	test #start feature_01

FILES_TARGET = $(foreach FILE,$(FILES),$(addprefix $(DIR_DEST)/debug/,$(FILE).exe) $(addprefix $(DIR_DEST)/release/,$(FILE).exe))

CPPFLAGS = $(patsubst %,-I%,$(DIR_INCLUDE)) -Wall

all : $(FILES_TARGET)
	@for f in $^; do echo -n Executing ./$$f && ./$$f && echo " : Done"; done;

bin/debug/%.exe : test/%.cpp | bin/debug
	g++ $(CPPFLAGS) -g -o $@ $<

bin/release/%.exe : test/%.cpp | bin/release
	g++ $(CPPFLAGS) -O3 -o $@ $<
	
bin/debug :
	@mkdir -p bin/debug

bin/release :
	@mkdir -p bin/release

clean :
	@rm bin/debug/* 
	@rm bin/release/* 
	@rmdir bin/debug 
	@rmdir bin/release 
	@rmdir bin


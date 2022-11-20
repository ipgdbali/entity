.PHONY : clean

DIR_DEST = bin
DIR_INCLUDE = src iface 

FILES =	test #start feature_01

FILES_TARGET = $(foreach FILE,$(FILES),$(addprefix $(DIR_DEST)/debug/,$(FILE)) $(addprefix $(DIR_DEST)/release/,$(FILE)))

CPPFLAGS = $(patsubst %,-I%,$(DIR_INCLUDE)) -Wall

all : $(FILES_TARGET)

bin/debug/% : test/%.cpp | bin/debug
	g++ $(CPPFLAGS) -g -o $@ $<
	$@

bin/release/% : test/%.cpp | bin/release
	g++ $(CPPFLAGS) -O3 -o $@ $<
	$@
	
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


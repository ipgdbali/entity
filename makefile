.PHONY : clean

all : 	bin/CAttrInfo \
	bin/CEntityInfo \
	bin/CEntity \
	bin/model \
	bin/CEntities \
	bin/CEntitiesCursor \
	bin/CCTStaticPrimitive \
	bin/CCTStaticCString

INCLUDE = src iface ../ipgdlib

CPPFLAGS = $(patsubst %,-I%,$(INCLUDE)) -g

bin/% : test/%.cpp | bin
	g++ $(CPPFLAGS) -o $@ $<
	$@

bin :
	mkdir bin

clean :
	rm bin/*
	rmdir bin


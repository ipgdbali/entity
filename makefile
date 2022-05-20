all : bin/CAttrInfo bin/CEntityInfo bin/CEntity bin/model bin/CEntities bin/CEntitiesCursor

clean :
	rm bin/*

INCLUDE = src iface ../ipgdlib

COMPILER_ARGUMENT = $(patsubst %,-I%,$(INCLUDE)) -g

bin/CAttrInfo : test/CAttrInfo.cpp
	g++ $(COMPILER_ARGUMENT) -o bin/CAttrInfo test/CAttrInfo.cpp
	bin/CAttrInfo

bin/CEntityInfo : test/CEntityInfo.cpp
	g++ $(COMPILER_ARGUMENT) -o bin/CEntityInfo test/CEntityInfo.cpp
	bin/CEntityInfo

bin/CEntity : test/CEntity.cpp
	g++ $(COMPILER_ARGUMENT) -o bin/CEntity test/CEntity.cpp
	bin/CEntity

bin/model : test/model.cpp
	g++ $(COMPILER_ARGUMENT) -o bin/model test/model.cpp
	bin/model

bin/CEntities : test/CEntities.cpp
	g++ $(COMPILER_ARGUMENT) -o bin/CEntities test/CEntities.cpp
	bin/CEntities

bin/CEntitiesCursor : test/CEntitiesCursor.cpp
	g++ $(COMPILER_ARGUMENT) -o bin/CEntitiesCursor test/CEntitiesCursor.cpp
	bin/CEntitiesCursor

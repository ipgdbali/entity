all : bin/CAttrInfo bin/CEntityInfo bin/CEntity bin/model bin/CEntities bin/CEntitiesCursor

bin/CAttrInfo : test/CAttrInfo.cpp
	g++ -Isrc -Iinterface -o bin/CAttrInfo test/CAttrInfo.cpp
	bin/CAttrInfo

bin/CEntityInfo : test/CEntityInfo.cpp
	g++ -Isrc -Iinterface -g -o bin/CEntityInfo test/CEntityInfo.cpp
	bin/CEntityInfo

bin/CEntity : test/CEntity.cpp
	g++ -Isrc -Iinterface -g -o bin/CEntity test/CEntity.cpp
	bin/CEntity

bin/model : test/model.cpp
	g++ -Isrc -Iinterface -g -o bin/model test/model.cpp
	bin/model

bin/CEntities : test/CEntities.cpp
	g++ -Isrc -Iinterface -g -o bin/CEntities test/CEntities.cpp
	bin/CEntities

bin/CEntitiesCursor : test/CEntitiesCursor.cpp
	g++ -Isrc -Iinterface -g -o bin/CEntitiesCursor test/CEntitiesCursor.cpp
	bin/CEntitiesCursor

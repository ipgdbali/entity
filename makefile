all : bin/CAttrInfo bin/CEntityInfo

bin/CAttrInfo : test/CAttrInfo.cpp
	g++ -Isrc -Iinterface -o bin/CAttrInfo test/CAttrInfo.cpp
	bin/CAttrInfo

bin/CEntityInfo : test/CEntityInfo.cpp
	g++ -Isrc -Iinterface -g -o bin/CEntityInfo test/CEntityInfo.cpp
	bin/CEntityInfo

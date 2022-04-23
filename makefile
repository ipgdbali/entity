all : bin/test/test_01 bin/test/CAttrInfo

bin/test/test_01 : test/test_01.cpp
	g++ -Isrc -o bin/test_01 test/test_01.cpp

bin/test/CAttrInfo : test/CAttrInfo.cpp
	g++ -Isrc -o bin/CAttrInfo test/CAttrInfo.cpp

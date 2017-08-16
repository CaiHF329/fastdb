#ifndef __TESTFASTDB__H__
#define __TESTFASTDB__H__
#include <string>
#include "fastdb/fastdb.h"
using namespace std;
class test
{
public:
	int a;
	int b;
	TYPE_DESCRIPTOR( (KEY(a, INDEXED),
					    FIELD(b)));

};
#endif

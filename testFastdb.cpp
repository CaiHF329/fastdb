#include <fstream>
#include <sstream>
#include <istream>
#include <iostream>
//#include "fastdb.h"
//#include <string>
#include "testFastdb.hpp"
#include <boost/date_time/posix_time/posix_time.hpp>
#include <map>
using namespace std;

USE_FASTDB_NAMESPACE


REGISTER(test);
dbDatabase db;
dbFileTransactionLogger tl;

std::map<int, int> id_crew_map; 

static void insertData()
{
	bool bOpenStatus = db.open(_T("TestFastDB"));
    assert(bOpenStatus == true);

    for(int i =0 ; i< 100*1000; i++) {
          char buf =  i%('Z' - 'A') + 'A';
          test c;
          c.a = i;
          c.b = buf;
          id_crew_map[i]=  buf;
		  insert(c);
	}	
     db.commit();

//	db.close();
    std::cout << "data insert done \n";
	//tl.close();
}


int  update(int id1, int id2)
{
    int sum = 0;
//	db.open(_T("TestFastDB"));
	dbCursor<test> cursor;
	dbQuery q;
	//q = "value=key order by value";
    q = "a>=",id1, "and a <= ", id2;
    if (cursor.select(q) > 0) {
        do {
            sum += cursor->b;
         //   cout<<cursor->a<<", "<<cursor->b<<endl;
        }while(cursor.next());
    }
//	db.close();

    return sum;
}

int  updateMap(int id1, int id2)
{
    int sum = 0;
    for (int i = id1; i <= id2; ++i)
    {
        sum += id_crew_map[i];
       // cout<<i<<", "<<id_crew_map[i]<<endl;
    }
    return sum;
}

int main()
{
    test c1;
    insertData();
    boost::posix_time::ptime t1 = boost::posix_time::microsec_clock::local_time();
    cout<<update(10*1000, 11*1000)<<endl;
    std::cout << (boost::posix_time::microsec_clock::local_time() - t1)  << "\n";

    boost::posix_time::ptime t2 = boost::posix_time::microsec_clock::local_time();
    cout<<updateMap(10*1000, 11*1000)<<endl;
    std::cout << (boost::posix_time::microsec_clock::local_time() - t2)  << "\n";

   return 0;
}

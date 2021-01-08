#include "lrucache.h"

namespace lru
{
	typedef std::string String;
	void test()
	{
		lru::Cache<String, String> cache(3,0);
		cache.insert("hello", "world");
		cache.insert("foo", "bar");
		cache.dumpDebug(std::cout<<"--> After 2 inserts"<<std::endl);
		
		std::cout<<"checking refresh : "<<cache.get("hello")<<std::endl;
		cache.dumpDebug(std::cout<<"--> After refeshing oldest key"<<std::endl);
		
		cache.insert("hello1", "world1");
		cache.insert("foo1", "bar1");
		cache.dumpDebug(std::cout<<"--> After adding two more"<<std::endl);
	}
}

int main(int argc, char **argv)
{
	lru::test();
	return 0;
}
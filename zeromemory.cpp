#include <cerrno>
#include <cstring>
#include <iostream>
#include <fstream>
#include <unistd.h>
#include <sys/sysinfo.h>
#include <sys/mman.h>

using namespace std;

size_t alloc = 0;
void* addr = MAP_FAILED;

int main() try {
	sync();
	if(!(ofstream("/proc/sys/vm/drop_caches")<<"3"<<endl)) cerr<<"Cannot drop caches: "<<strerror(errno)<<endl;
	struct sysinfo info;
	if(sysinfo(&info)) throw "Cannot get free memory";
	alloc = info.freeram + info.bufferram;
	auto pagesize = sysconf(_SC_PAGESIZE);
	do alloc = (alloc * 99) / 100, alloc = (alloc / pagesize) * pagesize;
	while((addr = mmap(0, alloc, PROT_READ | PROT_WRITE, MAP_PRIVATE | MAP_ANONYMOUS | MAP_POPULATE | MAP_LOCKED, -1, 0)) == MAP_FAILED && alloc >= 1024 * 1024 * 1024);
	if(addr == MAP_FAILED) throw "Cannot map pages";
	if(mlockall(MCL_CURRENT)) throw "Cannot lock memory";
	munmap(addr, alloc);
	cerr<<"Zeroed "<<alloc<<" bytes"<<endl;
} catch(const char* f) {
	if(addr != MAP_FAILED) munmap(addr, alloc);
	cerr<<f<<": "<<strerror(errno)<<endl;
	return 1;
}

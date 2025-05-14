#include <fstream>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
//
#include <base/log.h>

int main(int argc, char * argv[])
{
	if (argc != 2) {
		char const *progname = argv[0];
		Genode::error("Usage: ", progname, " /path/to/file");
		return -1;
	}

	std::string const filename = argv[1];
	std::ofstream logfile;

	logfile.open(filename, std::ios::app);

	for (int i = 0; i < 100; ++i) {
		logfile << "Wrote log number: " << i << std::endl;
		std::this_thread::sleep_for(std::chrono::milliseconds(1000));
	}

	return 0;
}

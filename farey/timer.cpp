#include "timer.h"

timer::timer(std::ostream& os, const std::string& mess) : out(os), message(mess)
{
	begin = std::chrono::steady_clock::now();
}

timer::~timer()
{
	auto end = std::chrono::steady_clock::now();

	auto elapsed_ms = std::chrono::duration_cast<std::chrono::milliseconds>(end - begin);
	out << message << ": \n" << elapsed_ms.count() << " ms\n";
}

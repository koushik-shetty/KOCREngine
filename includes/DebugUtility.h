#ifndef WRAP_UTIL
#define WRAP_UTIL
#include <string>
#include <iostream>
#include <ostream>
#include <utility>

template<typename T>
void PRINT_DBG(std::ostream& os, T arg) {
	os << arg << "\n";
}

template<typename T, typename... Args>
void PRINT_DBG(std::ostream& os, T arg, Args... args) {
	os << arg ;
	PRINT_DBG(os, std::forward<Args>(args)...);
}

template<typename... T>
void ConsLog(T... args) {
	PRINT_DBG(std::cout, std::forward<T>(args)...);
}

#endif // WRAP_UTIL

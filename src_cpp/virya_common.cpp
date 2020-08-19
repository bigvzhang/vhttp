//
// Copyright (c) 2019-2020 Vic Zhang(VicBig at qq dot com)
//
// Distributed under the GNU General Public License, Version 3.(Please see
// more information at https://www.gnu.org/licenses/)
//
// Official repository: https://github.com/bigvzhang/vhttp
//

#include <string>
#include <stdarg.h>  
#include <memory>


namespace virya{

using namespace std;

#if defined(_WIN32)
void inline vformat(string& s, const char* fmt, va_list  args){
	size_t len = _vscprintf( fmt, args ) // _vscprintf doesn't count
		+1								// terminating '\0'
		;
	s.resize(len);
	vsprintf_s((char*)s.c_str(), s.size(), fmt, args);
	if(s[s.size() - 1] == '\0'){
		s.resize(len -1);
	}
}

string inline vformat(const char* fmt, va_list  args){
	string s;
	size_t len = _vscprintf( fmt, args ) // _vscprintf doesn't count
		+ 1                              // terminating '\0'
		;
	s.resize(len);
	vsprintf_s((char*)s.c_str(), s.size(), fmt, args);
	if(s[s.size() - 1] == '\0'){
		s.resize(len -1);
	}
	return s;
}

char* vbuffer_format(const char* fmt, va_list  args);


#else
#if defined(__CYGWIN__) && ! __GNU_VISIBLE
inline void vasprintf(char** buffer, const char* fmt, va_list  arg_ptr){
	#define  VASPRINTF_BUFFER 16
	*buffer = (char*) malloc(VASPRINTF_BUFFER);
	if(!(*buffer)){
		return;
	}
	int len = vsnprintf(*buffer, VASPRINTF_BUFFER, fmt, arg_ptr);
	if(len >=  VASPRINTF_BUFFER){                  // must be ge(greator or equal)
		len += 1;                                  // must plus 1
		*buffer = (char*)realloc(*buffer, len);	
		if(!(*buffer)){
			return;
		}
		vsnprintf(*buffer, len, fmt, arg_ptr);	
	}
	#undef  VASPRINTF_BUFFER
}
#endif

#define xfree_ptr(TAG,p)              {if(p != nullptr) { free(p); p = nullptr;}}
void inline vformat(string& s, const char* fmt, va_list  args){
	char* ptr = nullptr;
	vasprintf (&ptr, fmt, args);
	if(ptr !=nullptr){
		s = ptr;
		xfree_ptr(CHAR_STR, ptr);
	}else{
		s.resize(0);
	}
}

string inline vformat(const char* fmt, va_list  args){
	char* ptr = nullptr;
	vasprintf (&ptr, fmt, args);
	if(ptr !=nullptr){
		string s = ptr;
		xfree_ptr(CHAR_STR, ptr);
		return s;
	}else{
		return string();
	}
}

inline char* vbuffer_format(const char* fmt, va_list  args){
	char* ptr = nullptr;
	vasprintf (&ptr, fmt, args);
	if(ptr !=nullptr){
	}
	return ptr;
}
#undef xfree_ptr
#endif


inline char* buffer_format(const char* fmt, ...){
	va_list args;
	va_start (args, fmt);
	char* s = vbuffer_format(fmt, args);
	va_end (args);
	return s;
}

// Return a std::string with formatted data
string format(const char* fmt, ...){
	string s;
	va_list args;
	va_start (args, fmt);
	vformat(s, fmt, args);
	va_end (args);
	return s;
}


// Write formatted data to std::string
void format(string& s, const char* fmt, ...){
	va_list args;
	va_start (args, fmt);
	vformat(s, fmt, args);
	va_end (args);
}

} // end namespace virya

#define TIME_FMT_USING_BOOST_DATETIME
#ifdef TIME_FMT_USING_BOOST_DATETIME
#include <boost/date_time/local_time/local_time.hpp>
#else
#define BOOST_CHRONO_VERSION 2
#include <boost/chrono/config.hpp>
#include <boost/chrono/chrono_io.hpp>
#include <boost/chrono/system_clocks.hpp>
#include <boost/chrono/thread_clock.hpp>
#include <boost/chrono/process_cpu_clocks.hpp>
#endif

namespace virya{

/** converts time_t to string
 *     Notice
 *       1. For windows, implement by using gmtime_s
 *       2. For others, gmtime_s is not available in CentOS6 and gmtime is not thread safe.
 *          So try to use boost library as following:
 *            (1) If using boost::chrono::time_fmt, we need to set BOOST_CHRONO_VERSION to 2
 *                and it will generate warnings like "header is deprecated" when compiling.
 *            (2) If using boost::date_time, it won't generate warnings when compiling.
 */
std::string time_fmt(std::time_t  t) {
#ifdef _WIN32
	struct tm the_tm;
	gmtime_s(&the_tm, &t);

	//std::cout << std::put_time(&the_tm, "%D, %d %m %Y %T %Z") << std::endl;
	#define BUFSIZE1 48
	char buf[BUFSIZE1];
	auto len = std::strftime(buf, BUFSIZE1, "%a, %d %b %Y %T GMT", &the_tm);
	//std::cout << "len:" << len << "Time ==>" << buf << std::endl;
	return buf;
	#undef BUFSIZE1
#elif defined(TIME_FMT_USING_BOOST_DATETIME)
	using namespace boost::gregorian;
	using namespace boost::posix_time;
	using namespace boost::local_time;
	std::ostringstream oss;
	time_facet* output_facet = new time_facet("%a, %d %b %Y %T GMT"); //TODO: verify whether to free it
	oss.imbue(locale(locale::classic(), output_facet));
	oss << from_time_t(t);
	return oss.str();
#else
	auto tp = boost::chrono::system_clock::from_time_t(t); // tp => time point
	std::ostringstream oss;
	oss << boost::chrono::time_fmt(boost::chrono::timezone::utc, "%a, %d %b %Y %T GMT") << tp;
	return oss.str();
#endif
}

} // end namespace virya

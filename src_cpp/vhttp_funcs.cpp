//
// Copyright (c) 2019-2020 Vic Zhang(VicBig at qq dot com)
//
// Distributed under the GNU General Public License, Version 3.(Please see
// more information at https://www.gnu.org/licenses/)
//
// Official repository: https://github.com/bigvzhang/vhttp
//

#include <functional>
#include <boost/spirit/include/qi.hpp>
#include <boost/beast/core/string.hpp>

#include "vhttp_common.h"
#include "vhttp_funcs.h"


namespace bsc{

void parse_cookie(string_view& content, PARSE_FUNC_2 func){
	auto len = content.length();
	string_size_t b1 = std::string::npos;
	string_size_t l1 = 0;
	bool              m1 = false;
	string_size_t b2 = std::string::npos;
	string_size_t l2 = 0;
	//bool            m2 = false;
	string_size_t lspace = 0;
	int cnt = 0;
#define is_valid_pos(pos) (pos != std::string::npos)
	auto handle_result =[&](){
		if(m1){
			if(is_valid_pos(b2)){
				l2 -= lspace;
				string_view f1 = content.substr(b1, l1);
				string_view f2 = content.substr(b2, l2);
				//printf("name:%s value:%s\n", 
				//	f1.to_string().c_str(),
				//	f2.to_string().c_str()
				//	);
				func(f1, f2);
			} else {
				l1 -= lspace;
				string_view f1 = content.substr(b1, l1);
				string_view f2; // empty
				func(f1,f2);
			}
		} else{// invalid/empty

		}
	};
	for(string_size_t i = 0; i < len; i++){
		switch(content[i]){
		case ';' :
		{
			handle_result();
			b1 = std::string::npos;
			l1 = 0;
			m1 = false;
			b2 = std::string::npos;
			l2 = 0;
			lspace = 0;
		}
		break;
		case ' ':
		case '\t':
		case '\r':
		case '\n':
			if(is_valid_pos(b2)){
				l2++;
			}else if(is_valid_pos(b1)&& !m1){
				l1++;
			}
			lspace++;
			break;
		case '=':
			if(!is_valid_pos(b2)){
				l1 -= lspace;
				m1 = true;
				break;
			}else{
				//Notice, don't break, value could have char =
			}
		default:
			lspace = 0;
			if(is_valid_pos(b2)){
				l2++;
			}else {
				if(is_valid_pos(b1)){
					if(!m1){
						l1++;
					}else{
						b2 = i;
						l2++;
					}
				}else{
					b1 = i;
					l1++;
				}
			}
		}
	}
	handle_result();
}


uint64_t atouint64(const string_view sv){
	namespace qi = boost::spirit::qi;
	uint64_t value;
	if(qi::parse(std::cbegin(sv), std::cend(sv), qi::ulong_long, value)){
		return value;
	}else{
		return _UI64_MAX; // always return max as failure
	}
}

}// end namespace bsc


//
// Copyright (c) 2019-2020 Vic Zhang(VicBig at qq dot com)
//
// Distributed under the GNU General Public License, Version 3.(Please see
// more information at https://www.gnu.org/licenses/)
//
// Official repository: https://github.com/bigvzhang/vhttp
//

#ifndef VIRYA_COMMON_H
#define VIRYA_COMMON_H


#include <string>
#include <ctime>

namespace virya{


void format(std::string& s, const char* format, ...); // Write formatted data to std::string
std::string format(const char* format, ...);          // Return a std::string with formatted data

std::string time_fmt(std::time_t  t);                 // convets time_t to string

}


#endif // namespace VIRYA_COMMON_H

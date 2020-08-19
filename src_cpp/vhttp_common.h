//
// Copyright (c) 2019-2020 Vic Zhang(VicBig at qq dot com)
//
// Distributed under the GNU General Public License, Version 3.(Please see
// more information at https://www.gnu.org/licenses/)
//
// Official repository: https://github.com/bigvzhang/vhttp
//

#ifndef VIRYA_VHTTP_COMMON_H
#define VIRYA_VHTTP_COMMON_H

#ifndef _UI64_MAX
#include <limits> 
#define _UI64_MAX std::numeric_limits<std::uint64_t>::max()
#endif

#include "virya_common.h"

namespace bsc{

using virya::format;   // format string
using virya::time_fmt; // format time_t


typedef boost::beast::string_view string_view;
typedef std::string::size_type    string_size_t; // invalid string size type


}

#endif //namespace VIRYA_VHTTP_COMMON_H 


//
// Copyright (c) 2019-2020 Vic Zhang(VicBig at qq dot com)
//
// Distributed under the GNU General Public License, Version 3.(Please see
// more information at https://www.gnu.org/licenses/)
//
// Official repository: https://github.com/bigvzhang/vhttp
//

#ifndef VIRYA_VHTTP_FUNCS_H
#define VIRYA_VHTTP_FUNCS_H


namespace bsc{ // basic

typedef  std::function<void(string_view&, string_view&)> PARSE_FUNC_2;
void     parse_cookie(string_view& content, PARSE_FUNC_2 func);

uint64_t atouint64(const string_view sv);

}// end namespace bsc

#endif // namespace VIRYA_VHTTP_FUNCS_H

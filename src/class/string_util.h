#ifndef STRING_UTIL_H
#define STRING_UTIL_H


#include "wx/wx.h"

#ifdef __WXMSW__
#include <unicode/unistr.h>
#include <unicode/ustream.h>
#endif

struct StringUtil
{
	static void WxStringToStdString(const wxString& wx_str, std::string* str_p){
#ifdef __WXMSW__
		icu_69::UnicodeString us(wx_str.wc_str());
		us.toUTF8String(*str_p);
#else
		std::wstring ws(wx_str.ToStdWstring());
		std::ostringstream stringStream;
		stringStream << ws;
		*str_p = stringStream.str();
#endif
	}
	 
	static void StdStringFindAndReplace(std::string& str, const std::string& from_str,  const std::string& to_str){
		 
		std::string::size_type pos = 0u;
		 
		while((pos = str.find(from_str, pos)) != std::string::npos){
			str.replace(pos, from_str.length(), to_str);
			pos += to_str.length();
		} 
		 
	}
	 
};

#endif


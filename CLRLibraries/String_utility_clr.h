#pragma once
#include <string>
#include <msclr/marshal_cppstd.h>

using namespace System;

#ifndef end_
#define end_ '\n'
#endif // !end_


namespace msStr {

	std::string to_std_string_(String^ string) {
		return msclr::interop::marshal_context().marshal_as<std::string>(string);
	}

	template<typename CharT>
	std::basic_string<CharT> to_std_string(String^ string) {

		std::basic_string<CharT> str;

		for (int i = 0; i < string->Length; ++i)
			str.push_back(string[i]);

		return str;
	}


}
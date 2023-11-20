#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <MyLib/Console_Library/escape_code.h>
#include <MyLib/stringfunctionhelper.h>

namespace xml {

	// functions declaration
	bool is_xml_tag_has_attribute(const std::string& xml_tag);

	struct Snippet_strut {
		std::string _name;
		std::string _prefix;
		std::string _body;
		std::string _description;
	};

	struct Element {
		std::string _attribute;
		std::string _value;
	};

	struct Code_Snippet {
		std::string _tag;
		std::vector<Element>   _vElements;
	};

	struct Code_Snippet1 {
		std::string _tag;
		Element     _element;
	};

	void trait_xml_string_removeblanks(std::string& text) {
		size_t pos{};
		while (1) {
			// |0|1|2|3|4|5|6|7|8|9|10|11|12|13|14|15||||||
			size_t bpos = text.find('<', pos);  //  h e l l o . . . w o  r  l  d
			size_t epos = text.find('>', pos);  //  from 1 to 5 there 5 char 5 - 1 + 1.

			size_t first_alpha{};

			if (bpos != std::string::npos && epos != std::string::npos) {
				std::string _str = text.substr(bpos, epos - bpos + 1);

				first_alpha = _str.find_last_of("\\ ", bpos, epos - bpos);

				if (!xml::is_xml_tag_has_attribute(_str) &&
					_str.find("CDATA") == std::string::npos)
				{
					_str = Str::remove_char(_str, 0, _str.size() - 1, ' ');
					text.erase(text.begin() + bpos, text.begin() + epos + 1);
					text.insert(text.begin() + bpos, _str.begin(), _str.end());
				}

				pos = text.find('>', bpos) + 1;
			}
			else {
				break;
			}
		}
	}


	std::string get_string_quoted(const std::string& text, const std::string& first, const std::string last) {

		auto pos_first = text.find(first);
		auto pos_last = text.find(last);

		if (pos_first > pos_last) std::swap(pos_first, pos_last);
		pos_first += first.size();
		return text.substr(pos_first, pos_last - pos_first);
	}

	bool is_xml_tag(std::string xml_word) {
		// xml of type <...> alphabed .
		char b = '<';
		char e = '>';
		// remove any blank char
		Str::removeBlank(xml_word);
		// check if there any other than alphabet return false;

		if (xml_word[0] == b && xml_word[xml_word.size() - 1] == e) {
			bool slash = xml_word[1] == '\\';
			xml_word = xml_word.substr(slash + 1, xml_word.size() - 2 - slash);
			if (!Str::isStringalpbabet(xml_word)) return false;
			//bool is_there_any = xml_word.find_first_of("<>") != std::string::npos;

			//if (is_there_any) return false; else return true;
		}

		return true;
	}


	vecString get_all_xml_tags(const std::string& text) {

		char b = '<';
		char e = '>';
		vecString vec_str;
		//get first one in string.
		size_t pos{};
		while (1) {

			size_t b_pos = text.find(b, pos);
			if (b_pos == std::string::npos) break;
			size_t e_pos = text.find(e, pos);
			if (e_pos == std::string::npos) break;

			std::string tag = text.substr(b_pos, e_pos - b_pos + 1);
			pos = e_pos + 1;
			vec_str.push_back(tag);
		}



		return vec_str;
	}

	std::string make_end_tag(const std::string& xml_tag);

	bool is_xml_tag_has_attribute(const std::string& xml_tag) {

		return xml_tag.find('=') != std::string::npos;
	}

	int number_attribute_in_xml_tag(const std::string& xml_tag) {
		// caculate how much = is there.
		int k{};
		size_t pos{};
		while (1) {
			pos = xml_tag.find('=', pos);
			if (pos != std::string::npos) {
				++k;
				++pos;
			}
			else {
				return k;
			}
		}
	}

	Code_Snippet1  get_attribute_tag(std::string xml_tag) {

		if (!is_xml_tag_has_attribute(xml_tag)) return{};

		xml_tag = xml_tag.substr(1, xml_tag.size() - 2);
		std::stringstream ss(xml_tag);
		Code_Snippet1 snippet;
		std::getline(ss, snippet._tag, ' ');
		std::getline(ss, snippet._element._attribute, '=');
		std::getline(ss, snippet._element._value, '>');

		return snippet;
	}

	void print_snippet_attr(const Code_Snippet1& snippet) {
		Print_(color::Green, snippet._tag) << " : \n           ";
		Print_(color::Red, snippet._element._attribute) << " | " << snippet._element._value << end_;
	}

	//void remove_comment_json(std::string& text) {
	//	std::stack<char> symbol;
	//
	//	get_string_quoted(text);
	//}

}
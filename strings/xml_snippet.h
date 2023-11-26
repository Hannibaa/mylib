/*
 *****************************************************************************
 *                                                                           *
 *                                                                           *
 *                  Snippet xml for visual studio  Library                   *
 *                                                                           *
 * Author: KADDA Aoues - haoues_k@yahoo.fr - 2023                            *
 * Date : 20 / 11 / 2023                                                     *
 *                                                                           *
 * Copyright notice:                                                         *
 * Free use of the Library CFile                                             *
 * is permitted under the guidelines and in accordance with the most current *
 * version of the MIT License.                                               *
 * http://www.opensource.org/licenses/MIT                                    *
 *                                                                           *
 *****************************************************************************
 * 
 *   use only this function to generate files from json file taken from 
 *   Lewis Lepton
 *    https://lewislepton.com
 *    glsl programming code.
 *
 *   void generate_snippet_files_from_json(const fs::path json_file, const fs::path& folder)
 * 
*/


#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <MyLib/Console_Library/escape_code.h>
#include <MyLib/stringfunctionhelper.h>
#include <MyLib/CFile.h>

#define _String(text)  const  std::string text("<"#text">")
#define __String(name, text)     std::string name{#text}
#define _endString(text) const std::string e##text("</"#text">")

#define _Snippet_Code(name)   const xml_element name("<"#name">", "</"#name">")

namespace xml {

	 // declare all string element of snippet xml
     namespace code {
		_String(Assembly);     _endString(Assembly);
		_String(Author);       _endString(Author);
		_String(Code);         _endString(Code);
		_String(CodeSnippet);  _endString(CodeSnippet);
		_String(CodeSnippets); _endString(CodeSnippets);
		_String(Declarations); _endString(Declarations);
		_String(Default);      _endString(Default);
		_String(Description);  _endString(Description);
		_String(Function);     _endString(Function);
		_String(Header);       _endString(Header);
		_String(HelpUrl);      _endString(HelpUrl);
		_String(ID);           _endString(ID);
		_String(Import);       _endString(Import);
		_String(Imports);      _endString(Imports);
		_String(Keyword);      _endString(Keyword);
		_String(Keywords);     _endString(Keywords);
		_String(Literal);      _endString(Literal);
		_String(Namespace);    _endString(Namespace);
		_String(Object);       _endString(Object);
		_String(Reference);    _endString(Reference);
		_String(References);   _endString(References);
		_String(Shortcut);     _endString(Shortcut);
		_String(Snippet);      _endString(Snippet);
		_String(SnippetType);  _endString(SnippetType);
		_String(SnippetTypes); _endString(SnippetTypes);
		_String(Title);        _endString(Title);
		_String(ToolTip);      _endString(ToolTip);
		_String(Type);         _endString(Type);
		_String(Url);          _endString(Url);
	}

	struct xml_element {
		std::string begin;
		std::string end;

		xml_element(const std::string& _begin, const std::string& _end)
			: begin(_begin)
			, end(_end)
		{}
		~xml_element() = default;
	 };


	 namespace element {
		 _Snippet_Code(Assembly);
		 _Snippet_Code(Author);
		 _Snippet_Code(Code);
		 _Snippet_Code(CodeSnippet);
		 _Snippet_Code(CodeSnippets);
		 _Snippet_Code(Declarations);
		 _Snippet_Code(Default);
		 _Snippet_Code(Description);
		 _Snippet_Code(Function);
		 _Snippet_Code(Header);
		 _Snippet_Code(HelpUrl);
		 _Snippet_Code(ID);
		 _Snippet_Code(Import);
		 _Snippet_Code(Imports);
		 _Snippet_Code(Keyword);
		 _Snippet_Code(Keywords);
		 _Snippet_Code(Literal);
		 _Snippet_Code(Namespace);
		 _Snippet_Code(Object);
		 _Snippet_Code(Reference);
		 _Snippet_Code(References);
		 _Snippet_Code(Shortcut);
		 _Snippet_Code(Snippet);
		 _Snippet_Code(SnippetType);
		 _Snippet_Code(SnippetTypes);
		 _Snippet_Code(Title);
		 _Snippet_Code(ToolTip);
		 _Snippet_Code(Type);
		 _Snippet_Code(Url);

		 xml_element Body{ "<![CDATA[" , "]]>" };
	 }

	// functions declaration
	bool is_xml_tag_has_attribute(const std::string& xml_tag);

	struct Snippet_info {
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

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    PRINTING
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	void print_snippet_attr(const Code_Snippet1& snippet) {
		Print_(color::Green, snippet._tag) << " : \n           ";
		Print_(color::Red, snippet._element._attribute) << " | " << snippet._element._value << end_;
	}

	void print_xml_tags(vecString vec) {

		print_ << "size vec : " << vec.size() << end_;
		int k{};
		for (auto& s : vec) {
			print_ << "tag n " << ++k << " : [" << s << "] ";
			bool attr = xml::is_xml_tag_has_attribute(s);
			print_ << "has attribute : " << "FT"[attr];
			Print_(color::Green, " number of attributes : ") <<
				COLOR(color::Red, xml::number_attribute_in_xml_tag(s));
			if (attr) xml::print_snippet_attr(xml::get_attribute_tag(s));
			print_ << end_;
			if (k % 10 == 0) wait_;
		}
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    METHODE AND FUNCTION TO SET TEXT AND VALUE INSIDE SNIPPET FILE
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string get_string_quoted(const std::string& text, const std::string& first, const std::string last) {

		auto pos_first = text.find(first);
		auto pos_last = text.find(last);
		if (pos_first == _npos || pos_last == _npos) {
			Print_(color::Red, "no tag exist") << end_;
			return{};
		}

		if (pos_first > pos_last) std::swap(pos_first, pos_last);
		pos_first += first.size();
		return text.substr(pos_first, pos_last - pos_first);
	}

	std::string get_xml_string_value(const std::string& text, const xml::xml_element& _element) {
		return xml::get_string_quoted(text, _element.begin, _element.end);
	}

	void set_xml_string_value(std::string& text,
		const xml::xml_element& _element,
		const std::string& _value)
	{
		auto pos_first = text.find(_element.begin);
		auto pos_last = text.find(_element.end);
		if (pos_first == _npos || pos_last == _npos) return;

		if (pos_first > pos_last) std::swap(pos_first, pos_last);
		pos_first += _element.begin.size();

		text.erase(text.begin() + pos_first, text.begin() + pos_last);
		text.insert(text.begin() + pos_first, _value.begin(), _value.end());
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    MAKE QUICK SNIPPET CODE 
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string make_quicksnippet_code(const std::string& _title,
		const std::string& _shortcut,
		const std::string& _description,
		const std::string& _body)
	{
		// this only easiest snippet code
		// author : KADDA Aoues

		std::string text(R"(<?xml version="1.0" encoding="utf-8" ?>
<CodeSnippets  xmlns="http://schemas.microsoft.com/VisualStudio/2005/CodeSnippet">
	<CodeSnippet Format="1.0.0">
		
		<Header>
			<Title>exemple for snippets</Title>
			<Shortcut>test</Shortcut>
			<Description>minimum code to write program</Description>
			<Author>Aoues Kadda</Author>
			<SnippetTypes>
				<SnippetType>Expansion</SnippetType>
				<SnippetType>SurroundsWith</SnippetType>
			</SnippetTypes>
		</Header>
		
		<Snippet>

			<Code Language="cpp">
				<![CDATA[cout << "hello world \n";]]>
			</Code>
		</Snippet>
	</CodeSnippet>
</CodeSnippets>)");


		xml::set_xml_string_value(text, xml::element::Title, _title);
		xml::set_xml_string_value(text, xml::element::Description, _description);
		xml::set_xml_string_value(text, xml::element::Shortcut, _shortcut);
		xml::set_xml_string_value(text, xml::element::Body, _body);

		return text;
	}

	std::string make_quicksnippet_code(const Snippet_info& si) {
		return make_quicksnippet_code(si._name, si._prefix, si._description, si._body);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    MAKE SNIPPET CODE FROM EXISTING ONE.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string make_snippet_code(std::string text,
		const std::string& _title,
		const std::string& _shortcut,
		const std::string& _description,
		const std::string& _body)
	{
		xml::set_xml_string_value(text, xml::element::Title, _title);
		xml::set_xml_string_value(text, xml::element::Description, _description);
		xml::set_xml_string_value(text, xml::element::Shortcut, _shortcut);
		xml::set_xml_string_value(text, xml::element::Body, _body);

		return text;

	}

	std::string make_snippet_code(const std::string& text, const Snippet_info& si) {
		return make_snippet_code(text, si._name, si._prefix, si._description, si._body);
	}
    
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    EXTRACT ELEMENT OF XML FROM JSON FILE
	//    1. TITLE 
	//    2. SHORTCUT
	//    3. BODY
	//    4. DESCRIPTION
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	// process body to get it in one string
	std::string snippet_process_body_(const std::string& _body) {
		
		std::string str;
		size_t pos{};
		//print_ << "size|" << _body.size() << end_;
		while (1) {
			if (_body.find('"', pos) == _npos) break;

			str += Str::get_quoted(_body, pos) + "\n";
			//print_ << "str|" << str << "|\n"; wait_;
			if ( pos == 0 ) break;
			++pos;
			//print_ << "pos|" << pos << end_;
			if (pos > _body.size() - 1 ) break;
		}
		//print_ << "str|" << str.size() << end_;
		str = Str::removeUnusefullCharEnd(str, '\n');
		Str::removeBlank(str);
		return str;
	}

	// process string string info 
	xml::Snippet_info json_process_string(const std::string& str) {

		size_t pos{};
		xml::Snippet_info si;

		si._name = Str::get_quoted(str, pos);

		++pos;
		if (Str::get_quoted(str, pos) == "prefix") {
			++pos;
			si._prefix = Str::get_quoted(str, pos);
		}

		++pos;
		if (Str::get_quoted(str, pos) == "body") {
			++pos;
			if (str.find('[', pos) < str.find('"', pos)) {
				si._body = Str::get_quoted(str, pos, '[', ']');
			    si._body = snippet_process_body_(si._body);
			}
			else si._body = Str::get_quoted(str, pos);

		}

		++pos;
		if (Str::get_quoted(str, pos) == "description") {
			++pos;
			si._description = Str::get_quoted(str, pos);
		}

		return si;
	}


	// we get all snippet json portion string from json
	std::vector<Snippet_info> json_get_SnippetInfo(const std::string& json)
	{
		// first ignore all comment and 
		size_t pos_0 = json.find('{');
		// vector
		//vecString vec;
		std::vector<Snippet_info> vSI;

		while (1) {

			size_t pos_b = json.find('"', pos_0);
			//print_ << "pos_b " << pos_b << end_;

			size_t pos_d = json.find("description", pos_0);
			pos_d = json.find('\n', pos_d);
			size_t pos_e = json.find('}', pos_d);

			//print_ << "pos_e " << pos_e << "|" << json[pos_e] << end_;

			if (pos_b == _npos || pos_e == _npos) {
				// end of file
				Print_(color::Red, "end of file ....") << end_;
				break;
			}
			auto s = json.substr(pos_b, pos_e - pos_b);
			//print_ << s << end_;
			//wait_;
			Snippet_info si;
		    si = json_process_string(s);
			//vec.push_back(json.substr(pos_b, pos_e - pos_b));
			vSI.push_back(si);
			
			pos_0 = pos_e;
		}

		return vSI;
	}

	// print the structure snippet_info
	void print_snippetInfo(const xml::Snippet_info& si) {
		Print_(color::Green, "{") << end_;
		Print_(color::Red, "Title       = [") << si._name << "]\n";
		Print_(color::Red, "Shortcut    = [") << si._prefix << "]\n";
		Print_(color::Red, "Body        = [") << si._body << "]\n";
		Print_(color::Red, "Description = [") << si._description << "]\n";
		Print_(color::Green, "}") << end_;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//       GENERATING SNIPPET FILES FROM JSON FILE.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	void generate_snippet_files_from_json(const fs::path json_file, const fs::path& folder) {

		std::string json = File::loadFileToString(json_file);
		auto v_si = xml::json_get_SnippetInfo(json);

		std::string ext = ".snippet";

		for (auto& si : v_si) {
			fs::path file = folder.string() + "\\" + si._name + ext;
			auto text = xml::make_quicksnippet_code(si);
			File::saveStringToFile(text, file);
			Print_(color::Green, "generate file : ") << COLOR(color::Yellow, file.string()) << end_;
		}

	}

}


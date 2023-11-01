/*
 *****************************************************************************
 *                                                                           *
 *                          Platform Independent                             *
 *                    Files  Reader  and Loader  Library                     *
 *                                                                           *
 * Author: KADDA Aoues - haoues_k@yahoo.fr - 2023                            *
 * URL :                                                                     *
 *                                                                           *
 *                                                                           *
 * Copyright notice:                                                         *
 * Free use of the                                                           *
 * is permitted under the guidelines and in accordance with the most current *
 * version of the MIT License.                                               *
 * http://www.opensource.org/licenses/MIT                                    *
 *                                                                           *
 *****************************************************************************
*/


#pragma once
#include <filesystem>
#include <MyLib/operation_files.h>

#define NOT_IMPL    std::cout << "not implemented yet\n"

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//                  FILE CLASS LIBRARY AND FUNCTIONAL LIBRARY THAT SUPORT LOADING FILE 
//                  IN MEMORY FOR MANIPULATION DIVERS.
//                  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////

namespace fs = std::filesystem;

namespace File {

	class CFile {

		using CharType = char;

	public:
		//CFile() 
		//	:file_name_{""}
		//	,file_size_{0}
		//	,key_{""}
		//{}

		CFile(const  fs::path& filename)
			:file_name_{filename}
			,key_{""}
		{
			get_file_data();
		}

		template<typename Tchar>
		CFile(const std::basic_string<Tchar>& file_name)
			:file_name_{file_name}
			,key_{""}
		{
			// check if is right name in string path file
			get_file_data();
		}

		CFile(size_t file_size)
			:file_name_{}
			,file_size_{file_size}
			, name_file_{}
			, path_file_{}
			, ext_file_{}
			,key_{""}
		{
			create_file();
		}

		template<typename Iter>
		requires std::same_as<Iter,std::vector<CharType>::iterator>
		CFile(Iter IterBegin, Iter IterEnd)            // to > from and to < size.
			: CFile(static_cast<size_t>(std::distance(IterBegin,IterEnd)))
		{
			std::copy(IterBegin,IterEnd, data_.begin());
		}

		CFile(CFile& file, size_t size, size_t position = 0i64)
			:CFile(file.begin()+position, file.begin()+position + size - 1)
		{}

		// define iterator for CFile is better !!!
		std::vector<CharType>::iterator begin() noexcept {
			return data_.begin();
		}

		std::vector<CharType>::iterator end() noexcept {
			return data_.end();
		}

		std::string name() const {
			return name_file_;
		}

		void setName(const std::string_view name_file) {
			name_file_ = name_file;
		}

		void setExtension(const std::string_view extension) {
			ext_file_ = extension;
		}

		void setPath(const fs::path& path) {
			if (fs::exists(path))
			path_file_ = path.string();
		}

		std::string extension() const {
			return ext_file_;
		}

		std::string path() const {
			return path_file_;
		}


		bool empty() const {
			return data_.empty();
		}

		size_t size() const {
			return data_.size();
		}

		CharType read(size_t position) {
			return data_[position];
		}

		void write(CharType C, size_t position) {
			if (position < data_.size())
				data_[position] = C;
		}

		void setByte(size_t position, CharType _byte) {
			if (position < file_size_)
				data_[position] = _byte;
		}

		std::vector<unsigned char> readRegion(size_t position, size_t size) {
			NOT_IMPL;
			return {};
		}

		void writeRegion(const std::vector<CharType>& vec_char, size_t position) {
			NOT_IMPL;
		}

		void writeRegion(size_t position, size_t size, char* buffer) { // unsafe function.
			NOT_IMPL;
		}

		void remove(size_t position, size_t size) {
			NOT_IMPL;
		}

		void add(size_t position, char* buffer) {
			NOT_IMPL;
		}

		void encrypt() {
			NOT_IMPL;
			if (key_ == "") return;

		}

		void decrypt() {
			NOT_IMPL;
			if (key_ == "") return;

		}

		void setKey(const std::string& key) {
			NOT_IMPL;
			key_ = key;
		}

		template<typename CharT>
		void save_file(const std::basic_string<CharT>& file_name) const {

			std::ofstream ofs{ file_name, std::ios::binary};

			if (!ofs) {
				std::cout << "error in opening file or creating file\n";
				return;
			}

			ofs.write(reinterpret_cast<const char*>(data_.data()), data_.size() * sizeof(CharType));

			ofs.close();
		}

		template<typename NType>
		std::vector<NType> getdataAs() {
			static_assert(std::is_trivially_copyable_v<NType>, "NType should be copyable(POD) data type");

			size_t residual_byte = file_size_ % sizeof(NType);

			std::vector<NType> data_type;

			if (residual_byte != 0) {
				Print_(color::Red, "There are residual byte take on considuration ") << residual_byte << end_;
			}
			else {
				Print_(color::Green, "Perfect.No data loss.") << end_;
			}

			NType* ptr = (NType*)data_.data();

			for (size_t i = 0; i < data_.size() / sizeof(NType); ++i)
				data_type.emplace_back(*(ptr + i));

			return data_type;
		}
		
		template<>
		std::vector<CharType> getdataAs<CharType>() {
			return data_;
		}

		template<typename NType>
		std::vector<CharType> getRestAs() {
			static_assert(std::is_trivially_copyable_v<NType>, "NType should be copyable(POD) data type");
			size_t sz_ = file_size_ % sizeof(NType);

			std::vector<CharType> vec_;

			for (int i = 0; i < sz_; ++i) vec_.push_back(data_[data_.size() + i - sz_]);

			return vec_;
		}

		template<typename CharT = CharType>
		std::basic_string<CharT> String() {    // extract file in one as string.

			std::basic_string<CharT> text_data_;

			text_data_.reserve(file_size_+1);

			for (auto& element : data_) text_data_.push_back(static_cast<CharT>(element));

			return text_data_;

		}

		template<typename CharT = CharType>
		std::basic_string<CharT> String(size_t position, size_t size) {

			std::basic_string<CharT> text_data_;

			text_data_.reserve(size + 1);

			for (size_t t = position; t < position + size; ++t) {
				text_data_.push_back(static_cast<CharT>(data_[t]));
			}

			return text_data_;
		}

		
		void String(std::string& text) {
			text.clear();
			text.reserve(file_size_ + 1);
			for (auto& element : data_) text.push_back(static_cast<char>(element));
		}

	private:
		
		fs::path              file_name_;
		std::string           name_file_;
		std::string           path_file_;
		std::string           ext_file_ ;
		bool                  file_exist_;  

		std::string           key_;
		size_t                file_size_;

		std::vector<CharType> data_;

		void get_file_data() {

			// check file if exist :

			if (!fs::exists(file_name_)) {
				Print_(color::Green, "File not exist ") << end_;
				file_size_ = 0;
				file_exist_ = false;
				return;
			}

			// existence of file :
			file_exist_ = true;
			// file already exist : 
			name_file_ = file_name_.filename().string();
			// path file :
			path_file_ = file_name_.parent_path().string();
			// file size :
			file_size_ = fs::file_size(file_name_);
			// file extension :
			ext_file_ = file_name_.extension().string();
			// load the data :
			load_data();
		}

		void load_data() {

			std::ifstream ifs{ file_name_, std::ios::binary };

			if (!ifs.is_open()) {
				std::cout << "Error in opening file " << file_name_ << end_;
				return;
			}

			CharType* buffer = new CharType[file_size_];

			ifs.read(reinterpret_cast<char*>(buffer), file_size_);
			ifs.close();

			data_.insert(data_.begin(),buffer,buffer + file_size_);

			delete[] buffer;
		}

		void create_file() {

			data_.resize(file_size_ + 1);

		}
	};

} 
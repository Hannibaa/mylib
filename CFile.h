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
 * Free use of the Library CFile                                             *
 * is permitted under the guidelines and in accordance with the most current *
 * version of the MIT License.                                               *
 * http://www.opensource.org/licenses/MIT                                    *
 *                                                                           *
 *****************************************************************************
*/


#pragma once
#include <filesystem>
#include <fstream>
#include <MyLib/chrono/to_day.h>

#define NOT_IMPL    std::cout << "not implemented yet\n"

namespace fs = std::filesystem;

using byte = unsigned char;
using uchar = unsigned char;

using vecString = std::vector<std::string>;
using vecPath   = std::vector<fs::path>;

//////////////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//                  FILE CLASS LIBRARY AND FUNCTIONAL LIBRARY THAT SUPORT LOADING FILE 
//                  IN MEMORY FOR MANIPULATION DIVERS.
//                  
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////


namespace File {

	template<typename T>
	void save_to_file(const std::vector<T>&, const fs::path& );

	template<typename Iter>
	void save_to_file(Iter Itbegin, Iter Itend, const fs::path& file_name);

	class CFile {

		using CharType = char;

	public:
		CFile() 
			:file_name_{}
			, name_file_{}
			, path_file_{}
			, ext_file_{}
			, file_exist_{false}
			, file_size_{0}
			, key_{}
		{}
		
		CFile(size_t _size) 
			:file_name_{}
			, name_file_{}
			, path_file_{}
			, ext_file_{}
			, file_exist_{false}
			, file_size_{_size}
			, key_{}
		{
			create_file();
		}

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

		CFile(const fs::path& file_name, size_t file_size)
			:file_name_{file_name}
			,file_size_{file_size}
			, name_file_{}
			, path_file_{}
			, ext_file_{}
			,key_{""}
		{
			if (fs::exists(file_name)) {
			     get_file_data();
			}
			else {
			     create_file();
			}
		}

		template<typename Iter>
		requires std::same_as<Iter,std::vector<CharType>::iterator>
		CFile(const fs::path& file_name,Iter IterBegin, Iter IterEnd)            // to > from and to < size.
			: CFile(file_name, static_cast<size_t>(std::distance(IterBegin,IterEnd)))
		{
			std::copy(IterBegin,IterEnd, data_.begin());
		}

		CFile(CFile& file, size_t size, size_t position = 0i64)
			:CFile(file.name(), file.begin() + position, file.begin() + position + size - 1)
		{}

		~CFile() {

			if (is_modified_) {

				Print_(color::Green, "do you like to save file that modified (y/n) : ");
				// we should add new variable bool is_modified = true ;
				// and we have file name valide call save(); call save_file(../).
				char yn{};
				std::cin >> yn;
				if (yn == 'y' || yn == 'Y') {
					yn = 0;
					print_ << "save to file : " << file_name_.string() << end_;
					print_ << "do you like to change save file (y/n) : ";
					std::cin >> yn;

					if (yn == 'y' || yn == 'Y') {
						std::string new_file{};
						print_ << "enter new file name distination : ";
						std::cin >> new_file;
						save_file(new_file);
					}
					else {
						if (!file_name_.empty()) save();
						else Print_(color::Red, "no file name exist...\n");
					}
				}
				else {
					print_ << "file not saved ..." << end_;
					// if future we added to save it in temperary file.
				}

			}
		}


		// define iterator for CFile is better !!!
		std::vector<CharType>::iterator begin() noexcept {
			return data_.begin();
		}

		std::vector<CharType>::iterator end() noexcept {
			return data_.end();
		}

		fs::path name() const {
			return file_name_;
		}

		void setName(const std::string& name_file) {
			if (file_name_.empty()) file_name_ = name_file;
			else Error_("Use member function rename(fs::path)");
		}

		void setExtension(const std::string_view extension) {
			ext_file_ = extension;
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

		constexpr size_t size() const {
			return data_.size();
		}

		CharType read(size_t position) const {
			return data_[position];
		}

		void write(CharType C, size_t position) {
			if (position < data_.size())
				data_[position] = C;
			is_modified_ = true;
		}

		void setByte(size_t position, CharType _byte) {
			if (position < file_size_) {
				data_[position] = _byte;
				is_modified_ = true;
			}
		}

		std::vector<CharType> readRegion(size_t position, size_t size) const {
			
			if (position + size > data_.size()) {
				Print_(color::Red, "check parameter position and size out off range") << end_;
				return{};
			}

			std::vector<CharType> vec_region{};

			std::copy(data_.begin() + position, data_.begin() + position + size, vec_region.begin());

			return vec_region;
		}

		void writeRegion(const std::vector<CharType>& vec_char, size_t position) {
			
			size_t buffer_size = vec_char.size();
			// check overflow :
			if ( buffer_size + position > data_.size() ) {
				Print_(color::Red, "Overflow in data, will treated") << end_;
				buffer_size = data_.size() - position;
			}

			std::copy(vec_char.begin(), vec_char.begin() + buffer_size, data_.begin() + position);
			is_modified_ = true;
		}

		void remove(size_t position, size_t size) {
			
			if (position + size > data_.size()) {
				Print_(color::Red, "posibly overflow check position and size") << end_;
				return;
			}
			
			data_.erase(data_.begin() + position, data_.begin() + position + size);

			file_size_ = data_.size();
			is_modified_ = true;
		}

		void add(const std::vector<CharType>& vec_char ,size_t position) {
			
			// check position and size not too much
			if (position > data_.size()) {
				Print_(color::Red, "check the position, over range.") << end_;
				return;
			}

			data_.insert(data_.begin() + position, vec_char.begin(), vec_char.end());
			file_size_ = data_.size();
			is_modified_ = true;
		}

		void add(const std::vector<CharType>& vec_char) {
			data_.insert(data_.end(), vec_char.begin(), vec_char.end());
			is_modified_ = true;
		}

		template<typename T>
		void add(const std::vector<T>& vec, size_t position) {		
			static_assert(std::is_trivially_copyable_v<T>, "T is POD type");

			if (position > data_.size()) {
				Print_(color::Red, "Check argument position, overflow") << end_;
				return;
			}

			if ( vec.size() == 0) return;

			CharType* ptr_char = (CharType*)vec.data();

			data_.insert(data_.begin() + position, ptr_char, ptr_char + (vec.size() * sizeof(T)));
			file_size_ = data_.size();
			is_modified_ = true;
		}

		/*
		     std::random_device rd{}
			 std::mt199 mt{rd()};
			 std::uniform_int_distribution<> ud{1,23}
			 std::vector<int> v(5)
			 std::generate(v.begin(), v.end(), [&ud, &mt]{return 
			 */

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

		//////////////////////////////// save file functions /////////////////////////////////////////
		void save() {
			//check the file name is not empty;
			
			std::ofstream ofs{ file_name_, std::ios::binary};

			if (!ofs.is_open()) {
				Print_(color::Red, "fail!! to save file") << end_;
				return;
			}

			ofs.write(reinterpret_cast<const char*>(data_.data()), data_.size() * sizeof(CharType));

			ofs.close();
			is_modified_ = false;
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

		// save a region of files to new created file
		void save_region(const fs::path& file_name, size_t _position, size_t _size) const {

			// check size and _position
			if (_position + _size > data_.size()) {
				Print_(color::Red, "check position and size") << end_;
				return;
			}

			// save data to file.
			save_to_file(data_.begin()+_position, data_.begin()+_position+_size, file_name);

		}


		///////////////////////// extract data out of class function //////////////////////////////////
		template<typename NType = CharType>
		std::vector<NType>    getDataAs() {
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
		std::vector<CharType> getDataAs<CharType>() {
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


		////////////////////////////////////  String() function ////////////////////////////////////
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
	
		void                     String(std::string& text) {
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
		bool                  is_modified_{ false };

		std::string           key_;
		size_t                file_size_;

		std::vector<CharType> data_;

		// trait of file name
		std::string get_full_path_name() {
			NOT_IMPL;
			return{};
		}

		void get_file_data() {

			// check file if exist :

			if (!fs::exists(file_name_)) {
				Print_(color::Green, "File not exist ") << end_;
				file_size_ = 0;
				file_exist_ = false;
				create_file();
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
			data_.reserve(file_size_ + 10);
			data_.resize(file_size_);
			file_exist_ = false;
		}

	};

} 



//////////////////////////////////////////////////////////////////////////////////////////////////////////
// 
//             FILE OPERATION FUNCTIONS 
// 
//////////////////////////////////////////////////////////////////////////////////////////////////////////


namespace File {

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    FUNCTION SAVE TO FILE save_to_file(), IT CREATE NEW FILE AND 
	//    IF FILE EXIST THEY DO NOTHING 
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////


	template<typename T>
	void save_to_file(const std::vector<T>& data, const fs::path& file_name) {

		static_assert(std::is_trivially_copyable_v<T>, "type T should be POD type");

		if (fs::exists(file_name) || data.empty()) {
			Print_(color::Red, "Need to create new file Or data is empty") << end_;
			return;
		}

		std::ofstream ofs{ file_name, std::ios::binary };

		if (!ofs.is_open()) {
			Print_(color::Red, "Fail! to open file") << end_;
			return;
		}

		ofs.write(reinterpret_cast<const char*>(data.data()), data.size() * sizeof(T));
	}

	template<typename Iter>
	void save_to_file(Iter Itbegin, Iter Itend, const fs::path& file_name) {

		std::vector<typename Iter::value_type> temp_vec(Itbegin, Itend);

		save_to_file(temp_vec, file_name);

	}


	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    FUNCTION OF PRINTING ALL PROPERIERTY OF FILE
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	bool file_propierty(const fs::path& file_name) {

		// check if file exist :
		if (fs::exists(file_name)) print_ << "file exist in drive. " << end_;
		else return false;

		// full path of file
		print_ << "file                : " << file_name.string() << end_;

		// size of file 
		print_ << "file size           : " << fs::file_size(file_name) << end_;

		// path of file 
		print_ << "file path directory : " << file_name.parent_path().string() << end_;

		// only file name :
		print_ << "file name           : " << file_name.filename().string() << end_;

		// only extension of file : 
		print_ << "file extension      : " << file_name.extension().string() << end_;

		return true;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    SPLITE FILE TO FILES -- NEED TO CHECK FILE AND DIRECTORY GAVE BY DEFAULT --
	//                         -- RETURN IS VECTOR TO PATHS OF FILES --
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	
	const size_t MAX_FILES_GEN = 20 ;  // maximum files that allowed to generate.

	vecPath splite_file(const fs::path& file_name, size_t Size, fs::path folder = std::string{}) {

		File::CFile file{ file_name };

		vecPath vec_files{};

		// will create folder at file position if there are no one:
		if (folder.empty()) {
			folder = file_name.parent_path().string() + "\\" + file_name.filename().string() + "_"
				+ Time::get_serial_at_time();
			fs::create_directory(folder);
		}
		print_ << "directory is : " << folder.string() << end_;
		// calculate number of file will be generated 
		// and rest file :
		size_t n_files = file.size() / Size;
		size_t rest_file = file.size() - n_files * Size;

		// make exception if number of file is too much : 
		if (n_files > MAX_FILES_GEN) {
			Print_(color::Red, "too much much file output ...") << end_;
			return {};
		}
		// create a files in folder.

		std::string file_ = folder.string() + "\\"
			+ "_";

		for (size_t t = 0; t < n_files; ++t) {
			print_ << "file n : " << file_ << " " << t << end_;
			file.save_region(file_ + "_" + std::to_string(t), t * Size, Size);
			vec_files.emplace_back(file_ + "_" + std::to_string(t));
		}

		if (rest_file != 0) {
			print_ << "file n : " << file_ << " " << n_files << end_;
			file.save_region(file_ + "_" + std::to_string(n_files), n_files * Size, rest_file);
			vec_files.emplace_back(file_ + "_" + std::to_string(n_files));
		}

		return vec_files;
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    CONCATE A FILES
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	void concate_files(const vecPath& vec_paths,const fs::path& destination) {
		 
		CFile dest(destination);

		for (auto& p : vec_paths) {
			CFile file(p);
			dest.add(file.getDataAs());
		}

		dest.save();
	}


	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//               GENERATE RANDOM FILE OF SIZE FILE_SIZE 
	//               1. RANDOM TXT FILE
	//               2. RANDOM BIN FILE
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	void makeRandomFile(const fs::path& filename, size_t filesize) {

		if (filesize > 10'000'000ull) {
			std::cout << "Over capacity of disk \n";
			return;
		}

		std::ofstream ofs{ filename, std::ios::binary };

		RNG::RG<char> rByte;

		for (size_t i = 0; i < filesize; ++i) {

			ofs.put(rByte());

		}

		ofs.close();
	}

	////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//          MAKE RANDOM TEXT FILE 
	//          1. SPECIFIY NUMBER OF WORDS
	//          2. SPECIFY MAXIMUM LENGTH FO WORDS.
	//          3. SPECIFY GENERATIVE FUNCTION OF STRING.
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename...Ts>
	void makeRandomTextFile(const fs::path& filename, 
		size_t number_words, size_t max_length_word, size_t max_line,
		std::string (*gen)(Ts...), Ts...args) {

		if ((number_words + 1) * max_length_word > 10'000'000ull) {
			Print_(color::Red, "Over Capacity of disk") << end_;
			return;
		}

		std::ofstream ofs{ filename };

		size_t count{};

		for (int i = 0; i != number_words; ++i) {

			auto word = gen(args...);

			if (word.length() > max_length_word) word = word.substr(0, max_length_word);

			count += word.length();
			++count;

			ofs << word << " ";

			if (count > max_line) {
				ofs << '\n';
				count = 0;
			}

		}

		ofs.close();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//        1. GET ONLY ALL FILES IN DIRECTORY WITHOUT GO TO SUB DIRECTORY FILES.
	//        2. GET ONLY DIRECTORIES OF DIRECTORY.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	vecPath get_files_directory(const fs::path& folder_name) {

		vecPath vec_paths{};

		for (auto& p : fs::directory_iterator(folder_name)) {
			if (fs::is_regular_file(p.path())) {
				vec_paths.emplace_back(p.path());
			}
		}

		return vec_paths;
	}

	std::pair<vecPath, vecPath> get_FilesAndDirectories_directory(const fs::path& directory)
	{
		vecPath vec_files, vec_dirs;

		for (auto& p : fs::directory_iterator(directory)) {
			if (fs::is_regular_file(p.path())) 	vec_files.emplace_back(p.path());
			if (fs::is_directory(p.path()))     vec_dirs.emplace_back(p.path());
		}

		return std::pair<vecPath, vecPath>(vec_files, vec_dirs);
	}

	vecPath get_Any_directory(const fs::path& directory, bool(*is_any)(const fs::path&))
	{
		vecPath vec_paths{};

		for (auto& p : fs::directory_iterator(directory)) {
			if (is_any(p.path())) {
				vec_paths.emplace_back(p.path());
			}
		}

		return vec_paths;
	}

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//                   LOAD FILE IN ARRAY OF TYPE 'T' OF SIZE 'N' AS MAXIMUM, RESIDUAL BYTE 
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	std::pair<std::vector<T>, std::vector<byte>>
		LoadFileToMemory(const fs::path& filename) {

		static_assert(std::is_trivially_copyable_v<T>, "should be pod type");

		size_t sz_file = fs::file_size(filename);

		if (sz_file == -1) {
			std::cout << "Error on file " << filename << "\n";
			return {};
		}

		size_t sz_T = sizeof(T);

		size_t sz_Array = sz_file / sz_T; // should be sz_T > sz_file

		size_t sz_rest = sz_file - sz_Array * sz_T;


		std::ifstream ifs{ filename };

		T* buffer = new T[sz_Array];

		ifs.read(reinterpret_cast<char*>(buffer), sz_Array * sz_T * sizeof(char));
		std::vector<T> vec(buffer, buffer + sz_Array);
		std::vector<byte> vec_rest;

		if (sz_rest != 0) {
		    byte* buf_char = new byte[sz_rest];
			ifs.read(reinterpret_cast<char*>(buf_char), sz_rest * sizeof(char));
		    vec_rest.insert(vec_rest.end(),buf_char, buf_char + sz_rest);
		    delete[] buf_char;
		}


		ifs.close();

		delete[] buffer;

		return std::make_pair(vec, vec_rest);
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    LOAD FILE IN STRING, AND SAVE STRING IN FILE.
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////

	std::string loadFileToString(const fs::path& filename) {

		std::ifstream ifs{ filename };

		if (!ifs.is_open()) {
			std::cout << "error in Opening file " << filename << '\n';
			return {};
		}

		size_t size = fs::file_size(filename);

		char* buffer = new char[size] {};

		ifs.read(reinterpret_cast<char*>(buffer), size * sizeof(char));

		std::string temp{ buffer };
		delete[] buffer;

		ifs.close();

		return temp;
	}

	void saveStringToFile(const std::string& text, const fs::path filename) {
		std::ofstream ofs{ filename };

		if (!ofs.is_open()) {
			std::cout << "Error in Opening file " << filename << '\n';
			return;
		}

		ofs << text;

		ofs.close();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	//    WE WANT GET PATH NAME OF FILE SAME FIRST FILE OPEN
	// 
	//////////////////////////////////////////////////////////////////////////////////////////////////////////
	// 
	fs::path name_same_path_extension(const fs::path& old_file, const std::string& name_file) {
		// get folder + \\ + name_file + extension.
		return old_file.parent_path().string() + "\\" + name_file + old_file.extension().string();
	}

}
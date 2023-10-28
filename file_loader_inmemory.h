#pragma once
#include <filesystem>
#include <memory>
#include <utility>
#include <vector>
#include <fstream>
#include "C:\Users\Acer\source\MyLib\random_generator.h"
#include "C:\Users\Acer\source\MyLib\stringfunctionhelper.h"

using byte = unsigned char;

const char* str_numeric = "0123456789";
const char* str_Alpha   = "abcdefghijklmnopqrstuvwxyz";
const char* str_alpha   = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";

namespace File {

	///////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//                   LOAD FILE IN ARRAY OF TYPE 'T' OF SIZE 'N' AS MAXIMUM, RESIDUAL BYTE 
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T, typename Tchar = char>
	std::pair<std::shared_ptr<T[]>, size_t> LoadToMemory(const std::basic_string<Tchar>& filename) {

		//static_assert(std::is_pod<T>::value, "should be pod type");

		size_t sz_file = std::filesystem::file_size(filename);

		if (sz_file == -1) {
			std::cout << "Error in file " << filename << "\n";
			return {};
		}

		size_t sz_T = sizeof(T);

		size_t sz_Array = sz_file / sz_T; // should be sz_T > sz_file

		size_t sz_rest = sz_file - sz_Array * sz_T;


		std::basic_ifstream<Tchar> ifs{ filename };

		T* buffer = new T[sz_Array];

		ifs.read(reinterpret_cast<char*>(buffer), sz_Array*sz_T*sizeof(char));

		std::shared_ptr<T[]> Buffer{ buffer };

		ifs.close();

		return std::make_pair(Buffer, sz_Array);
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //            LOAD FILE IN ARRAY OF TYPE 'T', SIZE , VECTOR OF REST OF FILE
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T, typename Tchar>
	std::tuple<std::shared_ptr<T[]>,size_t,std::vector<::byte>> 
		LoadToMemory2(const std::basic_string<Tchar>& filename) {
		
		//static_assert(std::is_pod<T>::value, "should be pod type");

		size_t sz_file = std::filesystem::file_size(filename);

		std::vector<::byte> vRest;

		if (sz_file == -1) {
			std::cout << "Error in file " << filename << "\n";
			return {};
		}

		size_t sz_T = sizeof(T);

		size_t sz_Array = sz_file / sz_T; // should be sz_T > sz_file

		size_t sz_rest = sz_file - sz_Array * sz_T;

		std::cout << "bytes rest is : " << sz_rest << std::endl;

		std::basic_ifstream<Tchar> ifs{ filename }; 

		T* buffer = new T[sz_Array];

		ifs.read(reinterpret_cast<char*>(buffer), sz_Array * sz_T * sizeof(char));
		ifs.close();


		ifs.open(filename);

		ifs.seekg(sz_Array * sz_T);

		while (1) {
			char ch{};
			ifs.get(ch);

			if ( ifs.eof() ) break;

			vRest.push_back(ch);
		}

		std::shared_ptr<T[]> Buffer{ buffer };

		ifs.close();


		return std::make_tuple(Buffer, sz_Array,vRest);
	}


	///////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //            LOAD FILE IN ARRAY OF TYPE 'T' IN TWO VECTORS OF TYPE 'T' AND TYPE 'BYTE' OF REST.
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////

	template<typename T>
	std::pair<std::vector<T>, std::vector<::byte>> 
	LoadFileToMemoryVec(const std::filesystem::path& filename)
	{

		//static_assert(std::is_pod<T>::value, "should be pod type");

		size_t sz_file = std::filesystem::file_size(filename);

		std::cout << "size of file :" << sz_file << std::endl;

		if (sz_file == -1) {
			std::cout << "Error in file " << filename << "\n";
			return {};
		}

		size_t sz_T = sizeof(T);

		size_t sz_Array = sz_file / sz_T; // should be sz_T > sz_file

		size_t sz_rest = sz_file - sz_Array * sz_T;

		std::cout << "bytes rest is : " << sz_rest << std::endl;

		std::ifstream ifs{ filename };

		std::vector<T> Vec;
		Vec.reserve(sz_Array + 2);
		std::vector<::byte> vBytes;
		vBytes.reserve(sz_rest + 1);

		for (size_t i = 0; i != sz_Array; ++i) {
			T value{};
			ifs.read(reinterpret_cast<char*>(&value), sizeof(T));
			Vec.push_back(value);
		}

		ifs.close();

		ifs.open(filename);

		ifs.seekg(sz_Array * sz_T);

		while (1) {
			char ch{};
			ifs.get(ch);

			if (ifs.eof()) break;

			vBytes.push_back(ch);
		}

		ifs.close();


		return std::make_pair(Vec,vBytes);


	}

	/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//               GENERATE RANDOM FILE OF SIZE FILE_SIZE 
	//               1. RANDOM TXT FILE
	//               2. RANDOM BIN FILE
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////

	void makeRandomFile(const std::string filename, size_t filesize) {
		
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
	//
	///////////////////////////////////////////////////////////////////////////////////////////////////////

	void makeRandomTextFile(const std::string& filename, size_t number_words, size_t max_length_word) {

		std::ofstream ofs{ filename };
		
		RNG::RG<int> rand(0, (int)max_length_word);

		for (int i = 0; i != number_words; ++i) {

			ofs << Str::getRandomString(rand()) << " ";

			if (i % 7 == 1) ofs << '\n'; 

		}

		ofs.close();
	}

	//////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //      LOAD TEXT FILE TO AN VECTOR OF WORDS
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

	auto loadTextFileToVectorWords(const std::filesystem::path& filename) {
		namespace fs = std::filesystem;
		std::vector<std::string> vString;
		if (fs::file_size(filename) == -1) return vString;

		auto X = LoadFileToMemoryVec<char>(filename);

		std::cout << "size 1 " << X.first.size() << " size 2 " << X.second.size() << '\n';

		std::string text{ X.first.data() };

		vString = Str::putTextInVectorWords(text, +[](int C)->bool {return bool(std::isalnum(C)); });

		return vString;
	}
}

/*
                 1/) Aoues Kadda File Byte Manipulation
                     Created by data 01 MAY 2023

                 2/) Revision add some function from other header file 
                     1. makeGraphicalFile;
                     2. makeRandomFile;
                     3. makeRandomTextFile;
                     4. loadFileToMemory;

                 3/) OPERATION ON FILES
                     1. Compare two file, create log file hase all equall bytes
                     2. Concat two file
                     3. Extract bytes from file from any position
                     4. Create C++ array from file
                        4.1 bytes array
                        4.2 short array
                        4.3 uint array
                        4.4 r,g,b array 
                        4.5 under anny structure.

*/


#pragma once

#include <fstream>
#include <iostream>
#include <string>
#include <filesystem>
#include <chrono>
#include <memory>
#include <map>
#include "C:\Users\Acer\source\MyLib\stringfunctionhelper.h"
#include "C:\Users\Acer\source\MyLib\random_generator.h"
#include "C:\Users\Acer\source\MyLib\pathfile_utility.h"
#include "C:\Users\Acer\source\MyLib\Bits_operation.h"

#define print    std::cout 
#define end_     '\n'

using byte = unsigned char;



namespace File {

const char* str_numeric = "0123456789";
const char* str_Alpha = "abcdefghijklmnopqrstuvwxyz";
const char* str_alpha = "ABCDEFGHIJKLMNOPQRSTUVWXYZ";
const char* str_printable = "abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ0123456789";

    ////////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //                   CHECK FILE IF EXIST
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    template<typename Tchar>
    bool isFileExist(const std::basic_string<Tchar>& filename) {

        std::basic_ifstream<Tchar> ifs{ filename, std::ios::binary };

        if (ifs.is_open()) { ifs.close(); return true; }

        return false;
    }

    ////////////////////////////////////////// Compare two file ///////////////////////////////////////////////////

    size_t compareFiles(const std::string& file1, const std::string& file2, const std::string& filelog = "") {

        size_t size1 = std::filesystem::file_size(file1);
        size_t size2 = std::filesystem::file_size(file2);


        print << "file " << file1 << " size " << size1 << end_;
        print << "file " << file2 << " size " << size2 << end_;

        // check the size and path of files
        if (size1 == -1 || size2 == -1) {
            print << "Error in check size of files, check path names \n";
            return -1;
        }

        std::ifstream ifs1{ file1,std::ios::binary };

        //checking of file 1
        if (!ifs1.is_open()) {
            print << "Error in opening a file " << file1 << end_;
            return -1;
        }

        std::ifstream ifs2{ file2,std::ios::binary };

        //checking of file 2
        if (!ifs2.is_open()) {
            print << "Error in opening a file " << file2 << end_;
            ifs1.close();
            return -1;
        }


        //create log file named file1file2.log
        auto filename1 = path::getFilenamNoextension(file1);
        auto filename2 = path::getFilenamNoextension(file2);
        auto logfile = filename1 + filename2 + ".log";

        if (filelog != "") {
            logfile.clear();
            logfile = filelog + ".log";
        }

        //open file log for writing
        std::ofstream log{ logfile,std::ios::binary };
        if (!log.is_open()) {
            print << "error in opening log file \n";
            ifs1.close();
            ifs2.close();
            return -1;
        }
        size_t count{};
        // loop for comparing files
        while (true) {
            char c{};
            ifs1.get(c);
            if (ifs1.eof()) {
                break;
            }

            // comparaison to ifs2
            if (ifs2.get() == c) {
                log.put(c); ++count;
            }

            if (ifs2.eof()) break;
        }

        print << "End of comparaison ...\n";

        log.close();
        ifs2.close();
        ifs1.close();
        return count;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //      CONCAT TWO FILE TO END OF ANOTHER FILE 
    //      WILL size byte FROM POSITION pos.
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    void concatFiles(const std::string& file1, const std::string& file2, size_t size = -1, size_t pos = -1) {

        size_t size1 = std::filesystem::file_size(file1);
        size_t size2 = std::filesystem::file_size(file2);

        // check the size and path of files
        if (size1 == -1 || size2 == -1) {
            print << "Error in check size of files, check path names \n";
            return;
        }

        std::ofstream ofs1{ file1,std::ios::binary | std::ios::app };

        //checking of file 1
        if (!ofs1.is_open()) {
            print << "Error in opening a file " << file1 << end_;
            return;
        }

        std::ifstream ifs2{ file2,std::ios::binary };

        //checking of file 2
        if (!ifs2.is_open()) {
            print << "Error in opening a file " << file2 << end_;
            ofs1.close();
            return;
        }

        // check position of file2 en reading
        if (pos != -1 && pos < size2) {
            ifs2.seekg(pos, std::ios_base::beg);
        }

        for (size_t i = 0; i < size; i++) {
            char c{};
            ifs2.get(c);

            if (ifs2.eof()) {
                break;
            }

            ofs1.put(c);
        }

        print << "concat two files finished\n";

        ofs1.close();
        ifs2.close();
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //                          Extract byte from file
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////

    void extractFromFile(const std::string& filename, size_t size, size_t position,const std::string& extfile) {

        // check timing for any call of these function
        auto tp = std::chrono::steady_clock::now();

        size_t sz = std::filesystem::file_size(filename);

        if (sz == -1) {
            print << "error in file " << filename << end_;
            return;
        }
        else if (sz < position) {
            print << "error in position value, greater than size of file \n";
            return;
        }
        else if (sz < size) {
            print << "error in size to be extracted, greater than size of file\n";
            return;
        }

        std::ifstream ifs{ filename, std::ios::binary };
        // check is open
        if (!ifs.is_open()) {
            print << "Error in opening file ...\n";
            return;
        }

        std::string tofile = path::getFilenamNoextension(filename);

        tofile = tofile + ".extr";

        std::ofstream ofs{ tofile, std::ios::binary };

        if (!ofs.is_open()) {
            print << "error in opening or creating " << tofile << end_;
            ifs.close();
            return;
        }

        ifs.seekg(position, std::ios_base::beg);

        // iterate all size of input file
        for (size_t t = 0; t < size; t++) {
            char c{};
            ifs.get(c);
            if (ifs.eof()) {
                print << "file finished \n";
                break;
            }

            ofs.put(c);
        }

        print << "process is finished\n";

        //extfile = tofile;

        ofs.close();
        ifs.close();

        auto d = std::chrono::duration<float>{ std::chrono::steady_clock::now() - tp };
        print << "duration is seconds : " << d.count() << end_;
    }

    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //              file to array cpp file type 
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////

    void file2array(const std::string& filename, const std::string arrayfile, size_t size, size_t pos = 0) {

        int N = 10;

        // check size of file with size and pos
        size_t file_size = std::filesystem::file_size(filename);
        if (file_size == -1) {
            print << "Error in opening file " << filename << " check \n";
            return;
        }

        if (size > file_size) {
            print << "Check size to be extracted in array \n";
            return;
        }

        if (pos + size > file_size) {
            print << "Check a position to start extrac data to array \n";
            return;
        }

        // open the files 

        std::ifstream ifs{ filename };

        if (!ifs.is_open()) {
            print << "Error in opening of file " << filename << end_;
            return;
        }

        // write naming for file array
        std::string iarray{ arrayfile };

        if (arrayfile == "") iarray = filename;

        iarray = iarray + ".cpp";

        std::ofstream ofs{ iarray };

        if (!ofs.is_open()) {
            print << "Error in creation of file " << iarray << end_;
            ifs.close();
            return;
        }

        // take size bytes from position pos to a pointer ptr

        char* ptr = new char[size] {};

        ifs.seekg(pos);

        ifs.read(reinterpret_cast<char*>(ptr), size * sizeof(char));

        ifs.close();

        // write like file in cpp file

        ofs << "// array from file " << path::getFilenamNoextension(filename) << " size  " << size << end_;
        ofs << "// from position   " << pos << end_ << end_ << end_;

        ofs << "char arrayFile[" << size << "] = \n { ";

        for (size_t i = 0; i < size - 1; i++) {
            ofs << bop::toHex(ptr[i]) << " , ";
            if ((i + 1) % N == 0) ofs << end_;
        }

        ofs << bop::toHex(ptr[size - 1]) << " };\n";

        delete[] ptr;
        ofs.close();
    }


    //////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //              STATISTIC OF CHAR IN FILE -> DATA FILE STATISTIC 
    //
    //////////////////////////////////////////////////////////////////////////////////////////////////////


    void charStatistic(const std::string& filename, const std::string& charSeries, const std::string& filestat = "")
    {
        // Check if file exist 
        size_t file_size = std::filesystem::file_size(filename);

        if (file_size == -1) {
            print << "Error in opening file " << filename << end_;
            return;
        }

        // Prepare file for output data 
        std::string datafile{ filestat };
        if (datafile == "") {
            datafile = filename + ".txt";
        }

        std::ifstream ifs{ filename,std::ios::binary };

        if (!ifs.is_open()) {
            print << "Error in opening file ... check path \n";
            return;
        }

        std::ofstream ofs{ datafile };

        if (!ofs.is_open()) {
            print << "Error in opening file ... \n";
            ifs.close();
            return;
        }
        // Construct Map for char in string

        std::map<char, size_t> mapChar;

        // Process data file;
        while (true) {
            char c{};
            ifs.get(c);

            if (ifs.eof()) {
                break;
            }

            if (charSeries.find(c) != -1)   mapChar[c]++;

        }

        // Head file :
        ofs << "Statistic of char : " << charSeries << end_;
        ofs << "File : " << filename << end_;
        ofs << end_;

        for (auto& c : charSeries) {

            ofs << "Character " << c << "[" << (int)c << "] : " << mapChar[c] << end_;

        }

        print << "Process end ...\n";

        ofs.close();
        ifs.close();
    }

       //////////////////////////////////////////////////////////////////////////////////////////////////////
       //
       //              HISTORIC FILE < OPEN FILE -- SAVED FILE -- TIME -- DATE > 
       //
       //////////////////////////////////////////////////////////////////////////////////////////////////////

    void makeHistoric(const std::string& url, const std::string& OperationCode, const std::string& historicfile)
    {
        // We don't need to check if these two file
        // Need time.library
        // C++20 time chrono and anothers
        /* 
               header:
               historic : {title} { reason of historic }{first date created} { last date access }
               1.url --- operation --- '\n'
               2.
               ...
               n. 
               
        */
        
        // Create if not created file 

        static uint32_t records = 0;

        if (!isFileExist(historicfile)) {
            print << "file not existed " << end_;

            // make one new; need header historic :{date}
            std::ofstream ofs{ historicfile };

            ofs << "historic[ "<< records << " ]: {title} { reason of historic } {first date created} { last date access }";
            ofs << "\n                       \n";
            ofs.close();
        }

        // Record historic event ...

        std::fstream fstr{ historicfile, std::ios::in | std::ios::out };
        /*char line[255]{};
        fstr.getline(line,255);
        print << "first line \n" << line << end_;*/

        std::string historic{};
        uint32_t number= 233;

        fstr >> historic;
        fstr >> number;

        records = number;

        print << historic << " records " << number << end_;

        fstr.seekp(0,std::ios::end);
        ++records;
        fstr << std::setw(6) << std::left <<  records ;
        fstr << std::setw(28) << std::left << url;
        fstr << std::setw(6) << std::left << " --- ";
        fstr << std::setw(10) << std::right << OperationCode << end_;

        fstr.seekp(0, std::ios::beg);
        fstr << "historic[ " << records << " ]: {title} { reason of historic } {first date created} { last date access }\n";

        fstr.close();
    }

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

        ifs.read(reinterpret_cast<char*>(buffer), sz_Array * sz_T * sizeof(char));

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
    std::tuple<std::shared_ptr<T[]>, size_t, std::vector<::byte>>
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

            if (ifs.eof()) break;

            vRest.push_back(ch);
        }

        std::shared_ptr<T[]> Buffer{ buffer };

        ifs.close();


        return std::make_tuple(Buffer, sz_Array, vRest);
    }

    ///////////////////////////////////////////////////////////////////////////////////////////////////////
    //
    //            LOAD FILE IN ARRAY OF TYPE 'T' IN TWO VECTORS OF TYPE 'T' AND TYPE 'BYTE' OF REST.
    //
    ///////////////////////////////////////////////////////////////////////////////////////////////////////

    template<typename T, typename Tchar>
    std::pair<std::vector<T>, std::vector<::byte>>
        LoadFileToMemoryVec(const std::basic_string<Tchar>& filename)
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

        std::basic_ifstream<Tchar> ifs{ filename };

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


        return std::make_pair(Vec, vBytes);


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


    //////////////////////////////////////////////////////////////////////////////////////////////////////////////
    // 
    //      USING FILE AS DATA 
    //      USING ANY FILE AND LOADED IT IN DATA TYPE AS FUNCTION OR GRAPH OR COORDINATE 
    // 
    //////////////////////////////////////////////////////////////////////////////////////////////////////////////


    template<typename T>
    std::vector<std::pair<T, T>>
        makeGraphicalFile(const std::string& filename, T Xscal, T Yscal) {

        static_assert(std::is_scalar<T>::value, "T type should be scalar type");

        auto v = File::LoadFileToMemoryVec<T>(filename).first;

        auto minmax = std::minmax_element(v.begin(), v.end());

        std::cout << *minmax.first << " " << *minmax.second << std::endl;

        T cx = Xscal / T(v.size());
        T cy = Yscal / (*minmax.second - *minmax.first);

        std::cout << " cy " << cy << std::endl;

        std::vector<std::pair<T, T>> vPoint;

        for (size_t i = 0; i < v.size(); ++i) {
            vPoint.emplace_back(cx * T(i), cy * v[i]);
        }

        return vPoint;
    }

}

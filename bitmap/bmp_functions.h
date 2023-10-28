#pragma once

#include <string>
#include <fstream>
#include <filesystem>
#include <algorithm>
#include <numbers>
#include "bitmap_utility.h"
#include "C:\Users\Acer\source\MyLib\bitmap\bitmap_image.hpp"
#include "C:\Users\Acer\source\MyLib\bitmap\BMPStructures.h"
#include "..\..\..\MyLib\pathfile_utility.h"
#include "C:\Users\Acer\source\MyLib\Bits_operation.h"



namespace bmpf {

	// some constant

	constexpr int White = rgb2int(rgb_t{ 255,255,255 });
	constexpr int Black = 0;


	int read_only_rgb(bitmap_image& image, const bitmap_image::rgb_t& rgb) {
		// read all (x,y) pixel and set pixel not equal to rgb to (0,0,0);
		int count = 0;
		for (uint i = 0; i < image.width(); i++)
			for (uint j = 0; j < image.height(); j++)
			{
				if (image.get_pixel(i, j) < rgb) {
					image.set_pixel(i, j, _rgb{ 0,0,0 });

					count++;
				}
			}

		return count;
	}


	/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//                                 CONVERT ANY FILE TO IMAGE BITMAP
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////*/


	void transform2img(const std::string& filename, const std::string& outfile = "") {

		// check the source filename
		size_t size_file = std::filesystem::file_size(filename);
		if (size_file == -1) {
			print << "Error in file " << filename << end_;
			print << "End...\n";
			return;
		}

		size_t length_rgb = size_file / 3;
		int rest = size_file % 3;

		auto pair = get_width_height(length_rgb);
		int width = pair.first;
		int height = pair.second;

		// calculate residual byte left in file
		auto residual = 3 * (length_rgb - width * height);

		// residuat byte
		int residual_bytes = rest + residual;

		// new length of array of rgb 
		length_rgb = width * height;

		// extension
		auto extension = '%' + path::getFileextension(filename) + '%';

		print << "file size is         " << size_file << end_;
		print << "length of rgb vector " << length_rgb << end_;
		print << "residual byte is     " << rest << end_;
		print << "residual from calcul " << residual << end_;
		print << "total rest bytes     " << rest + residual << end_;
		print << "width                " << width << end_;
		print << "height               " << height << end_;
		print << "extension file       " << extension << end_;

		std::ifstream ifs{ filename, std::ios::binary };

		//check file is open
		if (!ifs.is_open()) {
			print << "Error in opening file " << filename << end_;
			print << "End ...\n";
			return;
		}

		// read the data and place it in image vector;

		bitmap_image::rgb_t* ptr = new bitmap_image::rgb_t[length_rgb]{};

		ifs.read(reinterpret_cast<char*>(ptr), 3 * length_rgb * sizeof(char));

		// make bitmap image
		bitmap_image image(width, height);

		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
			{
				image.set_pixel(i, j, ptr[i + width * j]);
			}

		// saving file 
		std::string outfilename{ outfile };
		if (outfile == "") {
			outfilename = filename + ".trs.bmp";
		}

		image.save_image(outfilename);

		delete[] ptr;

		print << "file name saved to " << outfilename << end_;

		print << "reader pointed at :" << ifs.tellg() << end_;

		// complete remaining bytes to end of outfile:

		// read file header and write new information aboute residual byte.

		auto bfh = getBmpfileheader(outfilename);

		auto rev = bop::uint2u2short(residual_bytes);

		bfh.reserved1 = rev.first;
		bfh.reserved2 = rev.second;

		setBmpfileheader(outfilename, bfh);
		printBmpfileheader(bfh);

		// Reopen file outfilename to write at end
		std::ofstream ofs{ outfilename, std::ios::binary | std::ios::app };

		print << "position of file writing is : " << ofs.tellp() << end_;

		// writing 5 byte that identify %EXT%(ention)
		char cstr[6];
		cstr[5] = 0;
		std::copy(extension.begin(), extension.begin() + 5, cstr);

		// signator for starting recording data [[ ]] 
		char begin[] = "[[";
		char end[] = "]]";

		ofs.write(reinterpret_cast<char*>(begin), 2 * sizeof(char));

		// writing the rest of file
		while (true) {
			char c{};
			ifs.get(c);

			if (ifs.eof()) break;

			ofs.put(c);
		}
		// close signator end ]] data
		ofs.write(reinterpret_cast<char*>(end), 2 * sizeof(char));
		// extension %ext% 
		ofs.write(reinterpret_cast<char*>(cstr), 5 * sizeof(char));

		print << "residuat byte is add " << end_;

		ofs.close();
		ifs.close();// close file after reading the data
	}


	/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//                          RECONVERT IMAGE TO IT'S ORIGINAL FORM
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////*/


	void image2file(const std::string& filename) {  //, const std::string& outfile) {

		// check the source filename
		size_t size_file = std::filesystem::file_size(filename);
		if (size_file == -1) {
			print << "Error in file " << filename << end_;
			print << "End...\n";
			return;
		}

		// Extracte information about file header file structure 
		auto bh = bmpf::getBmpheaders(filename);

		// check if it is bitmap 
		if (bh.first.file_type == BMsign) {
			print << "imager of type bitmap ...continue\n";
		}
		else {
			print << "image isn't bitmap type ...exit \n";
			return;
		}

		uint logical_size = bh.first.file_size;
		uint residual_bytes = bop::u2short2uint(bh.first.reserved1, bh.first.reserved2);
		// get extension
		char extension[6]{};
		char word_confirm[10]{};
		std::ifstream ifs{ filename,std::ios::binary };
		if (ifs.is_open()) {
			ifs.seekg(-4, std::ios::end);
			ifs.read(reinterpret_cast<char*>(extension), 3);
			ifs.seekg(logical_size + 2u, std::ios::beg);
			ifs.read(reinterpret_cast<char*>(word_confirm), 9);
			ifs.close();
		}
		else {
			print << "error in opening file for reading ... check error\n";
			return;
		}

		// print all data collected;
		print << "physical size file ................." << size_file << end_;
		print << "logical size image ................." << logical_size << end_;
		print << "residual bytes ....................." << residual_bytes << end_;
		print << "extension .........................." << extension << end_;
		print << "confirmation of begining of data ..." << word_confirm << end_;

		// open new file writing
		std::string outfile = filename + '.' + extension[0] + extension[1] + extension[2];

		std::ofstream ofs{ outfile, std::ios::binary };

		if (!ofs.is_open()) {
			print << "Error in open file " << outfile << end_;
			return;
		}

		// process with first image data
		{
			bitmap_image image(filename);

			uint width = image.width();
			uint height = image.height();

			rgb_t* ptr = new rgb_t[width * height]{};

			for (uint i = 0; i < width; i++)
				for (uint j = 0; j < height; j++)
				{
					ptr[i + j * width] = image.get_pixel(i, j);
				}

			// write all block of ptr to ofs file
			ofs.write(reinterpret_cast<char*>(ptr), 3 * width * height * sizeof(char));

			delete[] ptr;
		}

		// reopen file 
		ifs.open(filename, std::ios::binary);
		if (!ifs.is_open()) {
			print << "Error!!\n";
			ofs.close();
			return;
		}

		// seek to the data
		ifs.seekg(logical_size + 2u, std::ios::beg);

		// process copy of data
		for (uint i = 0; i < residual_bytes; i++) {
			char c{};
			ifs.get(c);
			if (ifs.eof()) break;
			ofs.put(c);
		}
		char c[2]{};
		ifs.read(reinterpret_cast<char*>(c), 2);

		if (c[0] == ']' && c[1] == ']') {
			print << "Good .... transfer of data\n";
		}
		else {
			print << "Bad ..... data!!!\n";
		}

		print << "last : |" << c[0] << c[1] << "|\n";
		print << "End of process.................................... \n";

		ifs.close();
		ofs.close();
	}


	/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//          SORT IMAGE PIXEL AND SAVED IN ANOTHER IMAGE
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////*/


	bool comp(rgb_t& c1, rgb_t& c2) {
		return rgb_to_int(c1) > rgb_to_int(c2);
	}

	void sort_image(const std::string& filename, const std::string& outfile = "", bool (*Comp)(rgb_t&, rgb_t&) = comp)
	{
		// check file if exist by read there size
		size_t size = std::filesystem::file_size(filename);
		if (size == -1) {
			print << "Error in opening or existing of file " << filename << end_;
			return;
		}

		bitmap_image image(filename);

		int width = image.width();
		int height = image.height();

		bitmap_image::rgb_t* ptr = new bitmap_image::rgb_t[width]{};

		auto fill_ptr = [&](int j)->void {

			for (int i = 0; i < width; i++) {
				ptr[i] = image.get_pixel(i, j);
			}

		};

		auto fill_image = [&](int j)->void {

			for (int i = 0; i < width; i++) {
				image.set_pixel(i, j, ptr[i]);
			}
		};

		for (int j = 0; j < height; j++) {
			// fill ptr from image by raw
			fill_ptr(j);
			// sort the raw
			std::sort(ptr, ptr + width, Comp);
			// change image raw by new sorted raw
			fill_image(j);
		}

		std::string save_file{ outfile };

		if (save_file == "") {
			save_file = filename + ".to.bmp";
		}

		delete[] ptr;
		image.save_image(save_file);
	}


	/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//          SORT IMAGE PIXEL AND SAVED IN ANOTHER IMAGE
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////*/


	rgb_t f1_rgb(const rgb_t& color, uchar c) {// just example of function 

		return rgb_t{ uchar(color.red + c),uchar(color.green + c),uchar(color.blue + c) };
	}

	template<typename...Ts>
	void TransformPixel(const std::string& filename, const std::string& suffix
		, rgb_t(*f)(const rgb_t&, Ts...), Ts...args) {

		size_t size_file = std::filesystem::file_size(filename);

		if (size_file == -1) {
			print << "Error in reading file \n";
			return;
		}

		print << "size of file " << filename << " is : " << size_file << end_;

		bitmap_image image(filename);

		int width = image.width();
		int height = image.height();

		for (int i = 0; i < width; i++)
			for (int j = 0; j < height; j++)
			{
				image.set_pixel(i, j, f(image.get_pixel(i, j), args...));
			}

		std::string outfilename = filename + suffix + "2.bmp";
		image.save_image(outfilename);
		print << "Transformation finish ..." << end_;
	}


	/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//                          IMAGE PIXEL OF LINEAR FUNCTION X---->F(X)
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////*/


	void image_function1d(const std::string& filename, uint width, uint height, float (*f)(float)) {

		bitmap_image image(width, height);

		rgb_t color{};

		for (uint i = 0; i < width; i++)
			for (uint j = 0; j < height; j++)
			{
				int val = static_cast<int>(f(float(i + j * width)));

				color = bop::int2rgb<rgb_t>(val);

				image.set_pixel(i, j, color);
			}
		auto _filename = filename + ".bmp";
		image.save_image(filename);

		print << "finish processing image function\n";
	}


	/*/////////////////////////////////////////////////////////////////////////////////////////////////////////
	//
	//                         IMAGE PIXEL OF LINEAR FUNCTION (X,Y)---->F(X,Y)
	//
	/////////////////////////////////////////////////////////////////////////////////////////////////////////*/


	void image_function2d(const std::string& filename, uint width, uint height, float (*f)(float, float)) {

		bitmap_image image(width, height);

		rgb_t color{};

		for (uint i = 0; i < width; i++)
			for (uint j = 0; j < height; j++)
			{
				int val = static_cast<int>(f(float(i), float(j)));

				color = bop::int2rgb<rgb_t>(val);

				image.set_pixel(i, j, color);
			}

		auto _filename = filename + ".bmp";
		image.save_image(filename);

		print << "finish processing image function\n";
	}


///////////////////////////////////////////////////////////////////////////////////////////////////////////
//
//                 FRACTAL FUNCTIONS, FRACTAL TRANSFORMATION IN               
//
///////////////////////////////////////////////////////////////////////////////////////////////////////////


	void create_fractal1(const std::string& filename, uint width, uint height, uint it_max,
		double x1, double x2, double y1, double y2)
	{

		bitmap_image image(width, height);

	//	double dw = double(width), dh = double(height);

		double dw = double(width), dh = double(height);

		for (uint i = 0; i < uint(dw); i++)
			for (uint j = 0; j < uint(dh); j++)
			{
				std::complex<double> c(x1 + (i * (x2 - x1) / dw), y1 + (j * (y2 - y1) / dh));

				std::complex<double> z{};

				uint I = i * width / (dw - 1);
				uint J = j * height / (dh - 1);

				for (int k = 0; k < it_max; ++k) {
					z = z * z + c;

					if (std::abs(z) > std::numbers::sqrt2_v<double>) {
						//image.set_pixel(i, j, bop::int2rgb<rgb_t>(100*k));
						if(I < width && J < height)
						image.set_pixel(I, J, palette_colormap[palette_name::e_white]);
						break;
					}
				}

			}


		image.save_image(filename);
	}
}
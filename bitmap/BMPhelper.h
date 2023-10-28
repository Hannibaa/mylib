#pragma once
#include "BMPStructures.h"
#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>

#define print   std::cout 
#define end_    '\n'
#define wait    std::cin.get()
#define Line    std::cout << "---------------------------------------------\n"

// Get information from bmp file 
// write on and read from file bmp
// getpixel and setpixel , coord , color
// make bmp file with matrix of pixel

// rgb structure

using uchar = unsigned char;

using  _rgb = _RGB;


// create empty image with width and hight and fill it with color;

void create_bmp(const std::string bmpfile, uint32_t width, uint32_t height, RGB color) {


}

std::size_t sizeofFile(const std::string& file_name)
{
    std::ifstream file(file_name.c_str(), std::ios::binary);
    if (!file.is_open()) return 0;
    file.seekg(0, std::ios::end);
    return static_cast<std::size_t>(file.tellg());
}

std::vector<unsigned char> load_bmp(std::string file_name) {

	return std::vector<uchar>{};
}

void read_bmp(const std::string& bmpfile, bool creat_data = false, const std::string& datafile = "")
{
	// check file size
	size_t sizefile = sizeofFile(bmpfile);
	if (sizefile == -1) {
		print << "Error in opening file, check file path or name \n";
		return;
	}

	Line; print << "File " << bmpfile << " size : " << sizefile << end_; Line;

	BMPFileHeader file_header;
	BMPInfoHeader file_info;

	std::ifstream ibmp{ bmpfile,std::ios::binary };

	if (!ibmp.is_open()) {
		print << "Error opening file" << bmpfile << end_; 
		return; 
	}

	// Read information from fileheader
	ibmp.read((char*)(&file_header) , sizeof(file_header));

	// check if it bmp file
	if (file_header.file_type != BMsign) {
		print << "File " << bmpfile << " is not bitmap file \n";
		print << "Following data is not correct \n";
		creat_data = false;
	}

	// Print info of header file bmp
	print << "File Type          : " << file_header.file_type << end_
		  << "File Size          : " << file_header.file_size << end_
		  << "Offset_data        : " << file_header.offset_data << end_
		  << "Size of Fileheader : " << sizeof(BMPFileHeader) << end_;
	// Read information from fileinfoheader v4 v5 ...
	Line;
	ibmp.read((char*)&file_info, sizeof(file_info));
	int width = file_info.width;
	int height = file_info.height;
	int padding = (width * sizeof(_RGB)) % 4;
	int rawSize = width * sizeof(_RGB) + padding;

	print << "Size info header   : " << file_info.size << end_
		<< "Image Width        : " << file_info.width << end_
		<< "Image Height       : " << file_info.height << end_
		<< "Planes             : " << file_info.planes << end_
		<< "Bits per Pixel     : " << file_info.bit_count << end_
		<< "Compression        : " << file_info.compression << end_
		<< "Image Size         : " << file_info.size_image << end_
		<< "X pixel per meter  : " << file_info.x_pixel_per_meter << end_
		<< "Y pixel per meter  : " << file_info.y_pixel_per_meter << end_
		<< "Colors in table    : " << file_info.colors_used << end_
		<< "Import color count : " << file_info.colors_important << end_
		<< "Size of infoheader : " << sizeof(BMPInfoHeader) << end_
		<< "Padding multiple 4 : " << padding << end_
		<< "Raw size           : " << rawSize << end_;
	Line;
	wait;

	if (!creat_data) { ibmp.close(); return; }

	// Creat file for data bmp image
	// examine the name of out data file

	std::string filepixel;
	if (datafile == "") {
	       filepixel = bmpfile + ".pixel";
	}
	else {
		filepixel = datafile;
	}

	std::ofstream obmp{ filepixel, std::ios::out };

	if (!obmp.is_open()) {
		print << "Error in open data file " << filepixel << end_;
		ibmp.close();
		return;
	}



	_RGB rgb;
	auto tp1 = std::chrono::steady_clock::now();
	ibmp.seekg(file_header.offset_data, ibmp.beg); // set pointer to offset data image

	for (int i = file_info.height - 1; i >= 0; i--)
	{
		for (int j = 0; j < file_info.width; j++)
		{
			if (ibmp.eof()) break;
			rgb.red = ibmp.get();
			rgb.green = ibmp.get();
			rgb.blue = ibmp.get();
			obmp << "( " << j << " , " << i << ")" << "[" << (int)rgb.red << "]"
				<< "[" << (int)rgb.green << "]"
				<< "[" << (int)rgb.blue << "]" << end_;
		}
		//padding system
		for (int k = 0; k < padding; k++)
		{
			obmp << "Pading" << ibmp.get() << end_;
		}
	}
	auto tp2 = std::chrono::steady_clock::now();
	float f = std::chrono::duration<float>{ tp2 - tp1 }.count();
	print << end_ << "Elapsed Time in seconds " << f << "s" << end_;

	obmp.close();
	ibmp.close();
}

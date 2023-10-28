#pragma once
#include <filesystem>
#include <fstream>

#define print   std::cout 
#define wprint  std::wcout
#define end_    '\n'
#define wait    std::cin.get()
#define Line    std::cout << "---------------------------------------------\n"

	
const uint16_t BMsign = 0x4D42;

using uchar = unsigned char;
using uint = unsigned int;

#pragma pack(push, 1)
struct BMPFileHeader {
	uint16_t file_type{ 0x4D42 };   // WORD = uint16_t
	uint32_t file_size{ 0 };        // DWORD = uint32_t
	uint16_t reserved1{ 0 };        //  always 0;
	uint16_t reserved2{ 0 };        //  always 0;
	uint32_t offset_data{ 0 };      //  start position of pixel data (bytes from begining of the file)
};
#pragma pack(pop)

#pragma pack(push,1)
struct mBMPFileHeader {
	uint16_t file_type{ 0x4D42 };   // WORD = uint16_t
	uint32_t file_size{ 0 };        // DWORD = uint32_t
	union {
		   uint32_t rest_size{0};     // just used for stock information about residual byte size.
		struct {
	       uint16_t reserved1;        //  always 0;
	       uint16_t reserved2;        //  always 0;
		};
	};
	uint32_t offset_data{ 0 };      //  start position of pixel data (bytes from begining of the file)
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BMPInfoHeader {                       // BMP INFO HEADER
	uint32_t size{ 0 };                      
	int32_t width{ 0 };                        // Image width in pixel
	int32_t height{ 0 };                       // Image height in pixel

	uint16_t planes{ 1 };						// number of color plane
	uint16_t bit_count{ 0 };					// number of bits per pixel
	uint32_t compression{ 0 };					// compression methode used
	uint32_t size_image{ 0 };					// size of bitmap in bytes
	int32_t x_pixel_per_meter{ 0 };				// Horizotal resolution 
	int32_t y_pixel_per_meter{ 0 };				// Vertical resolution
	uint32_t colors_used{ 0 };					// number of color in image
	uint32_t colors_important{ 0 };				// Minimum number of important colors
};
#pragma pack(pop)

#pragma pack(push, 1)
struct BMPColorHeader {
	uint32_t red_mask{ 0x00ff0000 };             // Mask identifying bits of red  component
	uint32_t green_mask{ 0x0000ff00 };			 // Mask identifying bits of green  component
	uint32_t blue_mask{ 0x000000ff };			 // Mask identifying bits of blue  component
	uint32_t alpha_mask{ 0xff000000 };			 // Mask identifying bits of alpha  component
	uint32_t color_space_type{ 0x73524742 };	 // Color space type
	uint32_t unused[16]{ 0 };                    // detailed below
	/*
	int32_t RedX                ;               // X coordinate of red endpoint                           
	int32_t RedY	            ;               // Y coordinate of red endpoint
	int32_t RedZ	            ;               // Z coordinate of red endpoint
	int32_t GreenX 	            ;               // X coordinate of green endpoint
	int32_t GreenY 	            ;               // Y coordinate of green endpoint
	int32_t GreenZ	            ;               // Z coordinate of green endpoint
	int32_t BlueX	            ;               // X coordinate of blue endpoint
	int32_t BlueY	            ;               // Y coordinate of blue endpoint
	int32_t BlueZ	            ;               // Z coordinate of blue endpoint
	uint32_t GammaRed			;               // Gamma red coordinate scale value
	uint32_t GammaGreen			;               // Gamma green coordinate scale value
	uint32_t GammaBlue			;               // Gamma blue coordinate scale value
	*/
};
#pragma pack(pop)

struct QColor {
	unsigned char r, g, b, junk;
};

#pragma pack(push,1)
struct _RGB {
	union {
		struct {
			unsigned char red;
			unsigned char green;
			unsigned char blue;
		};
		struct {
			unsigned char r;
			unsigned char g;
			unsigned char b;
		};
	};

	_RGB() = default;
	_RGB(uchar _r, uchar _g, uchar _b) : r{ _r }, g{ _g }, b{ _b } {}
};
#pragma pack(pop)

template<typename TRGB>
struct Pixel_ {
	uint32_t x;
	uint32_t y;
	TRGB rgb;
};

namespace bmpf {

	//   extract information of bitmap file head from file image

	BMPFileHeader getBmpfileheader(const std::string& filename) {

		// check file size
		size_t sizefile = std::filesystem::file_size(filename);
		if (sizefile == -1) {
			print << "Error in opening file, check file path or name \n";
			return BMPFileHeader{};
		}

		Line; print << "File " << filename << " size : " << sizefile << end_; Line;

		BMPFileHeader bfh;

		std::ifstream ifs{ filename,std::ios::binary };

		if (!ifs.is_open()) {
			print << "Error will open file, check file name" << end_;
			return BMPFileHeader{};
		}

		// read info file header

		ifs.read(reinterpret_cast<char*>(&bfh), sizeof(bfh));

		ifs.close();
		return bfh;
	}

	BMPFileHeader getBmpfileheader(std::ifstream& stream) {

		// check if stream is available
		if (!stream.is_open()) {
			print << "Error in stream " << end_;
			return BMPFileHeader{};
		}

		BMPFileHeader bfh;

		stream.read(reinterpret_cast<char*>(&bfh), sizeof(bfh));

		return bfh;
	}

	//////////////////////////////////// Info header BMP image ///////////////////////////////////////////
	// we take both 

	using BMPheader = std::pair<BMPFileHeader, BMPInfoHeader>;

	BMPheader getBmpheaders(const std::string& filename) {

		// check file size
		size_t sizefile = std::filesystem::file_size(filename);
		if (sizefile == -1) {
			print << "Error in opening file, check file path or name \n";
			return BMPheader{};
		}

		Line; print << "File " << filename << " size : " << sizefile << end_; Line;

		BMPheader bh;

		std::ifstream ifs{ filename,std::ios::binary };

		if (!ifs.is_open()) {
			print << "Error will open file, check file name" << end_;
			return BMPheader{};
		}

		// read info file header

		ifs.read(reinterpret_cast<char*>(&bh.first), sizeof(bh.first));

		// read info info header

		ifs.read(reinterpret_cast<char*>(&bh.second), sizeof(bh.second));

		ifs.close();
		return bh;
	}

	void setBmpfileheader(const std::string& filename, const BMPFileHeader& bfh) {

		std::fstream ofs{ filename, std::ios::binary | std::ios::in | std::ios::out };

		if (!ofs.is_open()) {
			print << "Error while open file, check file " << filename << end_;
			return;
		}


		ofs.write((char*)(&bfh), sizeof(bfh));

		ofs.close();
	}

	void setBmpfileheader(std::ofstream& ofs, const BMPFileHeader& bfh) {

		ofs.write((char*)&bfh, sizeof(bfh));

	}


	void printBmpfileheader(const BMPFileHeader& bfh) {
		Line;
		print << "File Header Info \n";
		Line;
		print << "File type              : " << bfh.file_type << end_;
		print << "File syze              : " << bfh.file_size << end_;
		print << "reserved               : " << bfh.reserved1 << end_;
		print << "reserved               : " << bfh.reserved2 << end_;
		print << "Offset data            : " << bfh.offset_data << end_;
	}

	void printBmpinfoheader(const BMPInfoHeader& bih) {
		Line;
		print << "Info Header File \n";
		Line;
		print << "header size              : " << bih.size << end_;
		print << "image width              : " << bih.width << end_;
		print << "image height             : " << bih.height << end_;
		print << "number of color plane    : " << bih.planes << end_;
		print << "number of bits per pixel : " << bih.bit_count << end_;
		print << "compression methode used : " << bih.compression << end_;
		print << "size of bitmap in bytes  : " << bih.size_image << end_;
		print << "horizontal resolution    : " << bih.x_pixel_per_meter << end_;
		print << "vertical resolution      : " << bih.y_pixel_per_meter << end_;
		print << "number of color in image : " << bih.colors_used << end_;
		print << "important colors count   : " << bih.colors_important << end_;
		Line;
	}


}



std::pair<uint16_t,uint16_t> uint_to_2ushort(uint32_t size) {

	uint16_t* rev;

	rev = (uint16_t*)&size;

	return std::make_pair(*rev,*(rev+1));
}

uint32_t u2short_to_uint(uint16_t rev1, uint16_t rev2) {

	uint16_t rev[2]{ rev1,rev2 };

	uint32_t* puint = (uint32_t*)rev;

	return *puint;
}
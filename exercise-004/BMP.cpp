#include "CLI/CLI.hpp"
#include "config.h.in"
#include <fmt/format.h>

#include <fstream>
#include <iostream>

#include "BMP.h"

template <typename T>
static void read_value(std::fstream& file, T* value){
    file.read(reinterpret_cast<char*>(value), sizeof(T));
}

void BMP::BitmapFileHeader::print(){

    fmt::println("======= The Bitmap File Header =======");
    fmt::println("   > The start: {}{}", bfType[0], bfType[1]);
    fmt::println("   > The size in bytes: {}", bfSize);
    fmt::println("   > The offset in bytes: {}", bfOffBits);

}

void BMP::BitmapInfoHeader::print(){

    fmt::println("======= The Bitmap Info Header =======");
    fmt::println("   > The Size: {}", biSize);
    fmt::println("   > The Width: {}", biWidth);
    fmt::println("   > The Height: {}", biHeight);

}

BMP::BMP(){
    fmt::println("BMP CTOR");
}

BMP::~BMP(){
    fmt::println("BMP DTOR");
}

bool BMP::read(const std::string&  filename){

    auto ret = false;

    std::fstream input_file(filename, std::ios::binary | std::ios::in);
    if(!input_file.is_open()){
        fmt::println("Error trying open the file!");
        return ret;
    }

    read_value(input_file, &m_fileHeader.bfType);
    read_value(input_file, &m_fileHeader.bfSize);
    read_value(input_file, &m_fileHeader.bfReserved);
    read_value(input_file, &m_fileHeader.bfOffBits);
    m_fileHeader.print();

    read_value(input_file, &m_infoHeader.biSize);
    read_value(input_file, &m_infoHeader.biWidth);
    read_value(input_file, &m_infoHeader.biHeight);
    read_value(input_file, &m_infoHeader.biPlanes);
    read_value(input_file, &m_infoHeader.biBitCount);
    read_value(input_file, &m_infoHeader.biCompression);
    read_value(input_file, &m_infoHeader.biSizeImage);
    read_value(input_file, &m_infoHeader.biXPelsPerMeter);
    read_value(input_file, &m_infoHeader.biYPelsPerMeter);
    read_value(input_file, &m_infoHeader.biClrUsed);
    read_value(input_file, &m_infoHeader.biClrImportant);
    m_infoHeader.print();

    pixel_buffer = std::vector<RGBA>(m_infoHeader.biWidth * m_infoHeader.biHeight);

    return ret;
}
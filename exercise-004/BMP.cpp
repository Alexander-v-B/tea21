#include "CLI/CLI.hpp"
#include "config.h.in"
#include <fmt/format.h>

#include <fstream>
#include <iostream>
#include <vector>

#include "BMP.h"

template <typename T>
static void read_value(std::fstream& file, T* value){
    file.read(reinterpret_cast<char*>(value), sizeof(T));
}

template <typename T>
static void write_value(std::fstream& file, T* value){
    file.write(reinterpret_cast<char*>(value), sizeof(T));
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

    int vecSize = m_infoHeader.biWidth * m_infoHeader.biHeight;
    pixel_buffer = std::vector<RGBA>(vecSize);

    int padding = (m_infoHeader.biWidth * 3) % 4;
    if(padding != 0) padding = 4 - padding;
    uint8_t dummy = 0;

    for(int y = 0; y < m_infoHeader.biHeight; y++){
        for(int x = 0; x < m_infoHeader.biWidth; x++){
            RGBA rgba;
            read_value(input_file, &rgba.red);
            read_value(input_file, &rgba.green);
            read_value(input_file, &rgba.blue);
            rgba.alpha = (rgba.red + rgba.green + rgba.blue) / 3;
            pixel_buffer[y * m_infoHeader.biWidth + x] = rgba;
        }
        for(int p = 0; p < padding; p++){
            read_value(input_file, &dummy);
        }
    }

    printImg();

    return ret;
}

bool BMP::write(const std::string&  filename){

    auto ret = false;

    std::fstream output_file(filename + "gray.bmp", std::ios::binary | std::ios::out);
    if(!output_file.is_open()){
        return ret;
    }

    write_value(output_file, &m_fileHeader.bfType[0]);
    write_value(output_file, &m_fileHeader.bfType[1]);
    write_value(output_file, &m_fileHeader.bfSize);
    write_value(output_file, &m_fileHeader.bfReserved);
    write_value(output_file, &m_fileHeader.bfOffBits);

    write_value(output_file, &m_infoHeader.biSize);
    write_value(output_file, &m_infoHeader.biWidth);
    write_value(output_file, &m_infoHeader.biHeight);
    write_value(output_file, &m_infoHeader.biPlanes);
    write_value(output_file, &m_infoHeader.biBitCount);
    write_value(output_file, &m_infoHeader.biCompression);
    write_value(output_file, &m_infoHeader.biSizeImage);
    write_value(output_file, &m_infoHeader.biXPelsPerMeter);
    write_value(output_file, &m_infoHeader.biYPelsPerMeter);
    write_value(output_file, &m_infoHeader.biClrUsed);
    write_value(output_file, &m_infoHeader.biClrImportant);

    int padding = (m_infoHeader.biWidth * 3) % 4;
    if(padding != 0) padding = 4 - padding;
    uint8_t dummy = 0;

    for(int y = 0; y < m_infoHeader.biHeight; y++){
        for(int x = 0; x < m_infoHeader.biWidth; x++){
            write_value(output_file, &pixel_buffer.at(y * m_infoHeader.biWidth + x).alpha);
            write_value(output_file, &pixel_buffer.at(y * m_infoHeader.biWidth + x).alpha);
            write_value(output_file, &pixel_buffer.at(y * m_infoHeader.biWidth + x).alpha);
        }
        if(y != m_infoHeader.biHeight -1){
            for(int p = 0; p < padding; p++){
                write_value(output_file, &dummy);
            }
        }
    }

    return ret;

}

void BMP::printImg(){

    for(int i = 0; i < pixel_buffer.size(); i++){
        fmt::println("r: {}, g: {}, b: {}, a: {}", pixel_buffer[i].red, pixel_buffer[i].green, pixel_buffer[i].blue, pixel_buffer[i].alpha);
    }

}
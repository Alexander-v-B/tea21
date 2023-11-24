#ifndef BMP_H
#define BMP_H

#include <string.h>

class BMP{

    public:

    BMP();
    ~BMP();
    bool read(const std::string&  filename);
    bool write(const std::string&  filename);


    private:

    struct BitmapFileHeader{
        uint8_t bfType[2] = {'X', 'X'};
        uint32_t bfSize = 0;
        uint32_t bfReserved = 0;
        uint32_t bfOffBits = 0;
        void print();
    };

    struct BitmapInfoHeader{

        uint32_t biSize = 0;
        uint32_t biWidth = 0;
        uint32_t biHeight = 0;
        uint16_t biPlanes = 0;
        uint16_t biBitCount = 0;
        uint32_t biCompression = 0;
        uint32_t biSizeImage = 0;
        uint32_t biXPelsPerMeter = 0;
        uint32_t biYPelsPerMeter = 0;
        uint32_t biClrUsed = 0;
        uint32_t biClrImportant = 0;
        void print();

    };

    struct RGBA{
        uint8_t red = 0;
        uint8_t green = 0;
        uint8_t blue = 0;
        uint8_t alpha = 0;
    };

    public:
    
    BitmapFileHeader m_fileHeader;
    BitmapInfoHeader m_infoHeader;

    std::vector<RGBA> pixel_buffer;

    void printImg();
};

#endif
#include "CLI/CLI.hpp"
#include "config.h.in"

class BMP{

    public:

    BMP(){

    }

    ~BMP(){

    }

    char raw_data[200];

    bool read(const std::string&  filename){

        std::ifstream infile; 
        infile.open(filename); 
 
        std::cout << "Reading from the file" << std::endl; 
        infile >> raw_data; 

        std::cout << raw_data << std::endl;

    }



};
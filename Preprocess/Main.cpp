#include "Main.h"

int main()
{
    std::ifstream casfile = openCasFile();   //功能在OpenFile.cpp中
    casData casdata = readCase(casfile);   //功能在ReadFile.cpp中
    geoData casgeo = casdata2geoData(casdata);//读取几何信息，并进行处理，返回一些几何信息的数据结构
    WriteMsh(casgeo); //将几何信息写入msh文件
    //ReadMsh(); //读取msh文件，并进行处理，返回一些数据结构
    //UseMetis(); //使用METIS对网格进行划分，并返回一些数据结构
    //WriteDat(); //将划分后的网格信息写入dat文件
    return 0;
}


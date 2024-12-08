#include "Main.h"

int main()
{
    ////使用cas文件
    ////step1.打开文件
    //std::ifstream casfile = openCasFile();   //功能在OpenFile.cpp中实现
    ////step2.读取文件
    //casData casdata = readCas(casfile);   //功能在ReadFile.cpp中实现
    ////step3.处理数据 
    //geoData geodata = casdata2geoData(casdata);  //功能在ReadGeometry.cpp中实现

    //使用neu文件
    //step1.打开文件
    std::ifstream neufile = openNeuFile();   //功能在OpenFile.cpp中实现
    //step2.读取文件
    neuData neudata = readNeu(neufile);   //功能在ReadFile.cpp中实现
    //step3.处理数据
    geoData geodata = neudata2geoData(neudata);  //功能在ReadGeometry.cpp中实现

    //step4.输出数据到.msh文件,dat文件
    WriteMsh(geodata); //将几何信息写入msh文件
    //WriteDat(geodata); //将几何信息写入dat文件,用于可视化


    //ReadMsh(); //读取msh文件，并进行处理，返回一些数据结构
    //UseMetis(); //使用METIS对网格进行划分，并返回一些数据结构
    //WriteDats(); //将划分后的网格信息写入dat文件
    return 0;
}
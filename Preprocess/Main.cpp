#include "Main.h"

int main()
{
    //step1.打开文件
    std::ifstream casfile = openCasFile();   //功能在OpenFile.cpp中实现
    //std::ifstream neufile = openneuFile();   

    //step2.读取文件
    casData casdata = readCase(casfile);   //功能在ReadFile.cpp中实现
    //neuData neudata = readneuData(neufile);
    
    //step3.处理数据 
    geoData geodata = casdata2geoData(casdata);//读取几何信息，并进行处理，返回一些几何信息的数据结构
    //neugeoData geodata = neudata2geoData(neudata);
   
    //step4.输出数据到.msh文件,dat文件
    WriteMsh(geodata); //将几何信息写入msh文件
    //WriteDat(geodata); //将几何信息写入dat文件,用于可视化


    //ReadMsh(); //读取msh文件，并进行处理，返回一些数据结构
    //UseMetis(); //使用METIS对网格进行划分，并返回一些数据结构
    //WriteDats(); //将划分后的网格信息写入dat文件
    return 0;
}
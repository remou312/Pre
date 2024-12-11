#include "Main.h"

int main()
{
    ////使用cas文件
    ////step1.打开文件
    //std::ifstream casfile = openCasFile();   //功能在OpenFile.cpp中实现
    ////step2.读取文件
    //casData casdata = readCas(casfile);   //功能在ReadFile.cpp中实现
    ////step3.处理数据 
    //geoData geodata = casData2geoData(casdata);  //功能在ReadGeometry.cpp中实现

    //使用neu文件
    //step1.打开文件
    std::ifstream neufile = openNeuFile();   //功能在OpenFile.cpp中实现
    //step2.读取文件
    neuData neudata = readNeu(neufile);   //功能在ReadFile.cpp中实现
    //step3.处理数据
    geoData geodata = neuData2geoData(neudata);  //功能在ReadGeometry.cpp中实现
    //step4.输出数据到.msh文件,dat文件（可选）
    //writeMsh(geodata); //将几何信息写入msh文件，用于检查geodata的正确性
    //writeDat(geodata); //将几何信息写入dat文件,用于可视化
    //step5.网格读取
    gridData griddata = geoData2gridData(geodata);
    //step6.网格划分
    datData datdata = useMetis(griddata); //使用METIS对网格进行划分，并返回一些数据结构
    writeDats(datdata); //将划分后的网格信息写入dat文件
    return 0;
}
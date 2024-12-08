#include "WriteMsh.h"

void WriteMsh(const geoData& data)
{
	//创建文件
	std::string meshfilename = filename.substr(0, filename.find_last_of(".")) + ".msh";
	std::ofstream ofs(meshfilename, std::ios::out);
	//读取geoData内容写入.msh文件












}

#include "WriteMsh.h"

void WriteMsh(const geoData& data)
{
	//�����ļ�
	std::string meshfilename = filename.substr(0, filename.find_last_of(".")) + ".msh";
	std::ofstream ofs(meshfilename, std::ios::out);
	//��ȡgeoData����д��.msh�ļ�












}

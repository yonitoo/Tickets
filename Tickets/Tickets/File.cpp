//#include "File.h"
//#include <iostream>
//
//File::File() : path("")
//{
//}
//
//File::File(const std::string& path) : path(path)
//{
//
//}
//
//void File::open(const std::string& path)
//{
//	this->path = path;
//	this->file.open(path);
//}
//
//void File::close()
//{
//	this->file.close();
//}
//
//void File::save()
//{
//	std::cout << "Successfully saved " << path << std::endl;
//}
//
//void File::saveAs(const std::string& path)
//{
//	File newFile(path);
//	newFile.open(path);
//	this->file >> newFile.file;
//	std::cout << "Successfully saved " << path << std::endl;
//	newFile.close();
//}
//
//void File::setPath(const std::string& path)
//{
//	this->path = path;
//}

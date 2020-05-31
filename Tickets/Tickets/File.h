#ifndef FILE_H
#define FILE_H

#include <string>
#include <fstream>
///open, close, save, save as, help, exit
class File
{
	private:
		std::string path;
		std::fstream file;
	public:
		File();
		File(const std::string&);
		void open(const std::string& path);
		void close();
		void save();
		void saveAs(const std::string& path);
		void setPath(const std::string& path);
		bool isOpened();
};

#endif // FILE_H

///TODO da go izmislq kak shte stane
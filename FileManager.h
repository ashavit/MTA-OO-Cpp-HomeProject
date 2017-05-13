#pragma once

#include <stdio.h>
#include <vector>
#include <list>

class FileManager
{
	FileManager() {};
	~FileManager() {};

	std::string regulatedPath;
	std::list<std::string> boardFiles;

	void regulatePath(const std::string path);
	void parseFileNames(std::string& data);
	int filesLeft = 0;

public:

	static FileManager& sharedInstance();

	FileManager(FileManager const&) = delete;
	void operator=(FileManager const&) = delete;

	void loadAvailableFiles(const std::string& path);
	const std::string nextFileName();
	bool hasMoreBoards() const;

	const std::string fileNameWithPath(const std::string fileName) const;
};

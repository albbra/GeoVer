//
// Created by Sebastian Michel (seb9621s) on 17.04.20.
//

#include <cogra/tools/NormalizeFilename.h>
//not working with current project compiler
/*
#if __cplusplus > 201402L
#include <filesystem>
std::string normalizeFilename(const std::string& fileName) {
	return fs::absolute(fileName);
}
#else
 */

#if WIN32
#include <stdio.h>
#include <stdlib.h>
#include <windows.h>

#ifndef PATH_MAX
    #define PATH_MAX                _MAX_PATH

std::string normalizeFilename(const std::string& fileName) {
	CHAR full_path[MAX_PATH];
	DWORD string_len = GetFullPathNameA(fileName.c_str(),
		MAX_PATH,
		full_path,
		NULL);

	return full_path;
}
#endif
#else
#include <climits>
#include <cassert>
#include <errno.h>

std::string normalizeFilename(const std::string& fileName) {
	char resolved_path[PATH_MAX];
	auto ret = realpath(fileName.c_str(), resolved_path);
	return resolved_path;
}
#endif
//#endif


#pragma once
#ifndef COGRA_UI_FILEDIALOG_H
#define COGRA_UI_FILEDIALOG_H
#include <string>
namespace cogra
{
namespace ui
{
class FileDialog
{
public:
    static std::string openFile(const char* filters);
    static std::string saveFile(const char* filters);

};
}
}
#endif
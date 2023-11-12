#include <cogra/system.h>
#include <cogra/ui/FileDialog.h>

/*#ifdef COGRA_WINDOWS
#include <windows.h>
#include <commdlg.h>
#else
//#error Please pick NOC_FILE_DIALOG_* depending on your system!
#endif*/

#include <tinyfd/tinyfiledialogs.h>

namespace cogra
{
namespace ui
{

std::string FileDialog::openFile(const char* filters)
{
	(void*)filters;
/*#ifdef WIN32
    OPENFILENAMEA ofn;       // common dialog box structure
    char szFile[260];       // buffer for file name
    int ret;

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = filters;
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST | OFN_FILEMUSTEXIST;

    ret = GetOpenFileNameA(&ofn);
    if(ret)
    {
        return std::string(ofn.lpstrFile);
    }
    else
    {
        return "";
    }
    
#else
    
    return "";
#endif*/
	const char * path = tinyfd_openFileDialog(	"Open File",		// Title
									NULL,			// Default Folder/Filepath
									0,				// Number of Filter Patterns
									NULL,			// Filter Patterns {"*.jpg","*.png"}
									NULL,			// Single Filter Desctiption
									0);				// Multiselect
	
	if(path)
	{
		return path;
	}
	return "";
}

std::string FileDialog::saveFile(const char* filters)
{
	(void*)filters;
/*#ifdef WIN32
    OPENFILENAMEA ofn;       // common dialog box structure
    char szFile[260];       // buffer for file name
    int ret;

    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(ofn);
    ofn.lpstrFile = szFile;
    ofn.lpstrFile[0] = '\0';
    ofn.nMaxFile = sizeof(szFile);
    ofn.lpstrFilter = filters;
    ofn.nFilterIndex = 1;
    ofn.lpstrFileTitle = NULL;
    ofn.nMaxFileTitle = 0;
    ofn.lpstrInitialDir = NULL;
    ofn.Flags = OFN_PATHMUSTEXIST;

    ret = GetSaveFileNameA(&ofn);

    return std::string(ofn.lpstrFile);
#else

    return "";
#endif */
	const char * path = tinyfd_saveFileDialog(	"Save File",		// Title
								NULL,			// Default Folder/Filepath
								0,				// Number of Filter Patterns
								NULL,			// Filter Patterns {"*.jpg","*.png"}
								NULL);			// Single Filter Desctiption
	if(path)
	{
		return path;
	}
	return "";
}

}
}
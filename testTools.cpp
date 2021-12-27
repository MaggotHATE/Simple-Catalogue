#include <windows.h>
#include <shobjidl.h>
#include <shellapi.h>
#include <iostream>
#include <filesystem>
#include "jsonTools.h"
#include <stdio.h>
#include <locale>
#include <codecvt>
#include <atlstr.h>
#include <tchar.h>
#include <wchar.h>


namespace fs = std::experimental::filesystem;

char* getPathExe() {
    char myPath[_MAX_PATH + 1];
    GetModuleFileNameA(NULL, myPath, _MAX_PATH);
    return myPath;
}

void copyChars(char copy[64], char paste[64]) {
    memset(&(copy[0]), 0, 64);
    int i;
    int n = strlen(paste);

    for (i = 0; i < n; i++) {
        copy[i] = paste[i];
    }
}

void copyChars2(char copy[64], char paste[64]) {
    std::cout << __FUNCTION__ << " 1= \n " << copy << " \n " << paste << "\n";
    memset(&copy[0], 0, sizeof(copy));
    std::cout << __FUNCTION__ << " 2= \n " << copy << " \n " << paste << "\n";
    //std::string tmp = paste;
    strncpy(copy, paste, 64);
    std::cout << __FUNCTION__ << " 3= \n " << copy << " \n " << paste << "\n";
}

wchar_t* convStr2W(std::string& pathT) {
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring buffrT = converter.from_bytes(pathT);
    wchar_t* buffCT = destrW(buffrT);
    std::wcout << "Converted: " << buffCT << "\n";
    return buffCT;
}


void openFileFolder(char* path)
{
    std::cout << __FUNCTION__ << " < " << path << "\n";
    //char complPath[256] = "";
    //strcat(complPath, path);
    //strcat(complPath, "userdata/");
    //std::cout << "complPath = " << complPath << "\n";
    ShellExecuteA(NULL, "open", path, NULL, NULL, SW_SHOWDEFAULT);
}

void openFileFolderW(wchar_t* path)
{
    //strcat(complPath, "userdata/");
    std::wcout << path << "\n";
    ShellExecuteW(NULL, L"open", path, NULL, NULL, SW_SHOWDEFAULT);
}

void openFile(char* filename, char* path)
{
    char complPath[256] = "";
    strcat(complPath, path);
    strcat(complPath, "userdata/");
    strcat(complPath, filename);
    std::cout << complPath << "\n";
    ShellExecuteA(NULL, "open", complPath, NULL, NULL, SW_SHOWDEFAULT);
}

void openFile1(char* path)
{
 
    ShellExecuteA(NULL, "open", path, NULL, NULL, SW_SHOWDEFAULT);
}

void openFile1W(wchar_t* path)
{

    ShellExecuteW(NULL, L"open", path, NULL, NULL, SW_SHOWDEFAULT);
}

std::wstring charLocaleSwitch(char* input) {
    std::wstringstream ss;
    ss.imbue(std::locale("Russian"));
    ss << input;
    std::wcout << "charLocaleSwitch = " << ss.str() << "\n";
    return ss.str();
}

std::vector<std::string> getMapKeys(std::map<std::string, std::string> inMap)
{
    std::vector<std::string> outVec;
    for (auto const& imap : inMap) outVec.push_back(imap.first);
    return outVec;
}


std::string filePathFull(std::string filename) {
    std::string filepath = filename;
    const size_t last_slash_idx = filepath.find_last_of("\\/") + 1;
    const size_t last_dot_idx = filepath.find_last_of(".") + 1;
    if (isdebug == true) std::cout << " last_dot_idx =" << last_dot_idx << "\n";

    if (std::string::npos != last_slash_idx && last_dot_idx != 0)
    {
        filepath.erase(last_slash_idx);
    }

    if (isdebug == true) std::cout << "filePathFull: " << filepath << " VS filename: " << filename << "\n";
    return filepath;
}

std::string fileNameFull(std::string filename) {
    std::string filepath = filename;
    const size_t last_slash_idx = filepath.find_last_of("\\/");
    if (std::string::npos != last_slash_idx)
    {
        filepath.erase(0,last_slash_idx+1);
    }

    //std::cout << "Path: " << filepath << "\n";
    return filepath;
}

std::vector<std::string> funcFilesInFolder(std::string path) {
    std::vector<std::string> fileList;
    for (const auto& file : fs::directory_iterator(path))
        fileList.push_back(file.path().string());

    return fileList;
}

std::vector<char*> funcFilesTypeInFolder(std::string path, std::string type) {
    std::vector<char*> fileList;
    for (const auto& file : fs::directory_iterator(path)) {
        std::string name = file.path().filename().string();
        if (name.find(type) != name.npos) {
            fileList.push_back( destr( file.path().string() ) );
        }
    }
    return fileList;
}

std::vector<std::string> funcValidFilesInFolder(std::string path) {
    std::vector<std::string> fileList;
    for (const auto& file : fs::directory_iterator(path)) {
        std::string filePath = file.path().string();
        std::cout << "Checking " << filePath << "\n";
        if (funcHasTags(destr(filePath)) != "NULL") {
            
            fileList.push_back(filePath);
            std::cout << filePath << " is valid" << "\n";
        }
    }

    return fileList;
}

std::vector<std::string> funcValidFilesInFolderTags(std::string path) {
    std::vector<std::string> fileList;
    for (const auto& file : fs::directory_iterator(path)) {
        char* fpath = destr(file.path().string());
        //char fpath[64] = "userdata/";
        // strcat(fpath, destr(file.path().filename().string()));
        if ( funcHasTags(fpath) != "NULL") {
            std::string filetags;
            filetags.assign(funcGetTags(fpath));
            std::cout << fpath << ": Tags: " << funcGetTags(fpath) << "\n";
            fileList.push_back(filetags);
        }
    }

    return fileList;
}

int funcValidFilesProcess(std::string path, std::vector<std::string> & names, std::vector<std::string> & tags, std::vector<std::string> & info, std::vector<std::string> & paths) {
    int status = 0;
    
    for (const auto& file : fs::directory_iterator(path)) {
        std::string filenamepath = file.path().string();
        std::string filename = file.path().filename().string();
        std::cout << " STARTING " << filename << "\n";

        char* fpath = destr(filenamepath);
        const char* hasTags = funcHasTags(fpath);
        

        if (hasTags != "NULL") {
            ////////////////////////////// TAGS
            char* realTags = funcGetTags(fpath);
            std::string filetags;
            filetags.assign(realTags);
            tags.push_back(filetags);

            ////////////////////////////// NAMES
            names.push_back(filenamepath);

            status = 1;

            /////////////////////////////// FILE PATH
            std::string fileFolder = funcGetDataPath(destr(filenamepath));
            if (fileFolder == "NULL") {
                paths.push_back(path);
                status += 2;
            }
            else {
                paths.push_back(fileFolder);
                status += 3;
            }


            char* fpath = destr(filenamepath);
            std::cout << " TAGS FINISHED " << realTags << "\n";

            //////////////////////////////// INFO
            if (funcHasName(fpath, "info") != "NULL") {
                std::string filetags;
                filetags.assign(funcGetInfo(fpath));

                info.push_back(filetags);
            }
            std::cout << " INFO FINISHED " << filename << "\n";
            std::cout << " NAMES CHECK " << names[names.size() - 1] << "TAGS: " << tags[tags.size() - 1] << "INFO: " << info[info.size() - 1] << "\n";
        }
        else {
            std::cout << " INVALID FILE " << filename << "\n";
        }
    }

    //std::cout << " NAMES CHECK " << names[0] << "\n";

    return status;
}

int funcValidFilesProcessMaps(std::string path, std::vector<std::string>& names, std::map<std::string, std::map<std::string, std::string>>& tagsANDinfo) {
    int status = 0;
    //std::vector<std::vector<std::map<std::string, std::string>>>
    //std::map<std::string, std::vector<std::string>>
    //std::map<std::string, std::map<std::string, std::string>>
    for (const auto& file : fs::directory_iterator(path)) {
        std::string filenamepath = file.path().string();
        std::string filename = file.path().filename().string();
        //std::vector<std::string> tagsANDinfo;
        std::cout << " STARTING " << filename << "\n";


        char* fpath = destr(filenamepath);
        std::cout << " FPATH " << fpath << "\n";
        const char* hasTags = funcHasTags(fpath);
       // std::cout << " HAS TAGS " << hasTags << "\n";


        if (hasTags != "NULL") {
            ////////////////////////////// TAGS
            char* realTags = funcGetTags(fpath);
            std::string filetags;
            filetags.assign(realTags);
            tagsANDinfo[filenamepath]["tags"]=filetags;
            

            ////////////////////////////// NAMES
            names.push_back(filenamepath);
            //tagsANDinfo[filename]["name"] = filenamepath;

            status = 1;

            /////////////////////////////// FILE PATH
            std::string fileFolder = funcGetDataPathNew(destr(filenamepath));
            if (fileFolder == "NULL") {
                tagsANDinfo[filenamepath]["path"] = path;
                //funcFixPath(destr(filenamepath));
                status += 2;
            }
            else {
                tagsANDinfo[filenamepath]["path"] = fileFolder;
                //funcFixPath(destr(filenamepath));
                status += 3;
            }


            char* fpath = destr(filenamepath);
            std::cout << " TAGS FINISHED " << realTags << "\n";

            //////////////////////////////// INFO
            if (funcHasName(fpath, "info") != "NULL") {
                std::string fileInfo;
                fileInfo.assign(funcGetInfo(fpath));

                tagsANDinfo[filenamepath]["info"] = fileInfo;
            }
            //tags[filename] = tagsANDinfo;
            //std::cout << " INFO FINISHED " << filename << "\n";
           // std::cout << "NAMES CHECK " << names[names.size() - 1] << "\n" << "TAGS: " << tagsANDinfo[filenamepath]["tags"] << "\n" << "INFO: " << tagsANDinfo[filenamepath]["info"] << "\n";
        }
        else {
            std::cout << " INVALID FILE " << filename << "\n";
        }
    }

    //std::cout << " NAMES CHECK " << names[0] << "\n";

    return status;
}

int funcValidFilesProcessClass(std::string path, std::vector<libCard>& libCards) {
    int status = 0;
    //std::vector<std::string> names;
    //std::map<std::string, std::map<std::string, std::string>> tagsANDinfo;
    //std::vector<std::vector<std::map<std::string, std::string>>>
    //std::map<std::string, std::vector<std::string>>
    //std::map<std::string, std::map<std::string, std::string>>
    char* nameG;
    char* tagsG;
    char* pathG;
    std::map<char*, char*> infoMapG;

    for (const auto& file : fs::directory_iterator(path)) {
        std::string filenamepath = file.path().string();
        std::string filename = file.path().filename().string();
        //std::vector<std::string> tagsANDinfo;
        if (isdebug == true) std::cout << " STARTING " << filename << "\n";


        char* fpath = destr(filenamepath);
        if (isdebug == true) std::cout << " FPATH " << fpath << "\n";
        const char* hasTags = funcHasTags(fpath);
        //std::cout << " HAS TAGS " << hasTags << "\n";


        if (hasTags != "NULL") {
            ////////////////////////////// TAGS
            //char* realTags = funcGetTags(fpath);
            //std::string filetags;
            //filetags.assign(realTags);
            //tagsG = destr(filetags);
            tagsG = funcGetTags(fpath);


            ////////////////////////////// NAMES
            nameG = destr(filenamepath);
            //tagsANDinfo[filename]["name"] = filenamepath;

            //status = 1;

            /////////////////////////////// FILE PATH
            std::string fileFolder = funcGetDataPathNew(destr(filenamepath));
            if (fileFolder == "NULL") {
                pathG = destr(path);
                //funcFixPath(destr(filenamepath));
                //status += 2;
            }
            else {
                pathG = destr(fileFolder);
                //funcFixPath(destr(filenamepath));
                //status += 3;
            }


            //char* fpath = destr(filenamepath);
            //std::cout << " TAGS FINISHED " << realTags << "\n";

            //////////////////////////////// INFO
            if (funcHasName(nameG, "info") != "NULL") {
                std::string fileInfo;
                infoMapG = funcGetInfoMap(nameG);
            }
            //tags[filename] = tagsANDinfo;
           // std::cout << " INFO FINISHED " << filename << "\n";
          //  std::cout << "NAMES CHECK " << nameG << "\n" << "TAGS: " << tagsG << "\n" << "PATH: " << pathG << "\n";
            libCard libCardX(nameG, tagsG, pathG, infoMapG);
            libCards.push_back(libCardX);

        }
        else {
            if (isdebug == true) std::cout << " INVALID FILE " << filename << "\n";
        }
    }

    //std::cout << " NAMES CHECK " << names[0] << "\n";

    return status;
}


char* WINAPI winOpenAndProcessFl(char* filename)
{
    char* buffer1 = "NULL";
    
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
        COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileOpenDialog* pFileOpen;

        // Create the FileOpenDialog object.
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
            IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

        if (SUCCEEDED(hr))
        {
            // Show the Open dialog box.
            hr = pFileOpen->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr))
            {
                IShellItem* pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    LPWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    // Display the file name to the user.
                    if (SUCCEEDED(hr))
                    {
                        //std::wcout << "PATH = " << pszFilePath << "\n";
                        //MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
                        size_t i;
                        char* buffer;
                        //wcstombs(buffer, pszFilePath, 500);
                        //WideCharToMultiByte(CP_OEMCP,
                        //    0,
                        //    pszFilePath,
                        //    -1,
                        //    buffer,
                        //    0, NULL, NULL);
                        //CharToOem(pszFilePath, buffer);
                        //WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, pszFilePath, -1, buffer, wcslen(pszFilePath), NULL, NULL);
                        //_wcstombs_l(buffer, pszFilePath, 5000, _create_locale(LC_ALL, "Russian"));
                        //WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, pszFilePath, -1, buffer, 500, NULL, NULL);

                        //wsprintfA(buffer, "%S", pszFilePath);
                        //wcstombs_s(&i, buffer, 500, pszFilePath, 1000);
                       
                        //AnsiToOem(buffer, buffer);

                        //std::wstring ws(pszFilePath);
                        //std::string myVarS = std::string(ws.begin(), ws.end());
                        //buffer = destr(myVarS);
                        

                        wsprintfA(buffer, "%S", pszFilePath);
                        

                        //std::wcout << "WPATH = " << ws << " VS " << pszFilePath << "\n";
                        //std::cout << "PATH = " << myVarS << " VS " << buffer << "\n";

                        //funcWriteJsonSimpleData2("path", buffer, filename);
                        //std::string newStr = CW2A(pszFilePath);
                        //funcWriteJsonSimpleData3("path", newStr, filename);
                        buffer1 = destr(stringConvert(buffer, CP_THREAD_ACP, 0, CP_UTF8, 0));
                        funcWriteJsonSimpleData2("path", buffer1, filename);

                        //iconv_t newConv = iconv_open("UTF−8", "CP1251");
                        //size_t* buffSize;
                        //const char* buffer1[500];

                        //iconv(newConv, buffer1, buffSize,&buffer,buffSize+1);

                        
                        //MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
                        /*std::fstream fs;
                        fs.open(buffer, std::fstream::in | std::fstream::out | std::fstream::app);
                        Json::Value root;
                        fs >> root;
                        winOpenResult = strdup(root["testread1"]["warrior1"][0].asCString());
                        CoTaskMemFree(pszFilePath);*/
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }
    return buffer1;
}

char* WINAPI winOpenFl()
{
    char* winOpenResult = "./userdata/";
    HRESULT hr = CoInitializeEx(NULL, COINIT_APARTMENTTHREADED |
        COINIT_DISABLE_OLE1DDE);
    if (SUCCEEDED(hr))
    {
        IFileOpenDialog* pFileOpen;

        // Create the FileOpenDialog object.
        hr = CoCreateInstance(CLSID_FileOpenDialog, NULL, CLSCTX_ALL,
            IID_IFileOpenDialog, reinterpret_cast<void**>(&pFileOpen));

        if (SUCCEEDED(hr))
        {
            // Show the Open dialog box.
            hr = pFileOpen->Show(NULL);

            // Get the file name from the dialog box.
            if (SUCCEEDED(hr))
            {
                IShellItem* pItem;
                hr = pFileOpen->GetResult(&pItem);
                if (SUCCEEDED(hr))
                {
                    LPWSTR pszFilePath;
                    hr = pItem->GetDisplayName(SIGDN_FILESYSPATH, &pszFilePath);

                    // Display the file name to the user.
                    if (SUCCEEDED(hr))
                    {
                        //std::wcout << "PATH = " << pszFilePath << "\n";
                        //MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
                        size_t i;
                        char* buffer;
                        //wcstombs(buffer, pszFilePath, 500);
                        //WideCharToMultiByte(CP_OEMCP,
                        //    0,
                        //    pszFilePath,
                        //    -1,
                        //    buffer,
                        //    0, NULL, NULL);
                        //CharToOem(pszFilePath, buffer);
                        //WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, pszFilePath, -1, buffer, wcslen(pszFilePath), NULL, NULL);
                        //_wcstombs_l(buffer, pszFilePath, 500, _create_locale(LC_ALL, "ru_RU.UTF8"));
                        //WideCharToMultiByte(CP_UTF8, WC_COMPOSITECHECK, pszFilePath, -1, buffer, 500, NULL, NULL);


                        //wsprintfA(buffer, "%S", pszFilePath);
                        //std::wcout << "PATH = " << buffer << "\n";
                        //AnsiToOem(buffer, buffer);
                        //buffer1 =
                        wsprintfA(buffer, "%S", pszFilePath);
                        winOpenResult = destr(stringConvert(buffer, CP_THREAD_ACP, 0, CP_UTF8, 0));


                        //MessageBoxW(NULL, pszFilePath, L"File Path", MB_OK);
                        //std::fstream fs;
                        //fs.open(buffer, std::fstream::in | std::fstream::out | std::fstream::app);
                        //Json::Value root;
                        //fs >> root;
                        //winOpenResult = strdup(root["testread1"]["warrior1"][0].asCString());
                        //CoTaskMemFree(pszFilePath);
                    }
                    pItem->Release();
                }
            }
            pFileOpen->Release();
        }
        CoUninitialize();
    }

    return winOpenResult;
}

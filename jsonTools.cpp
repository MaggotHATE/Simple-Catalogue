#include <fstream>
#include <iostream> 
#include "jsonTools.h"
#include <filesystem>
#include <windows.h>

//#define UNICODE

namespace fs = std::experimental::filesystem;
bool isdebug;


char* wchar_to_char(const wchar_t* pwchar)
{
    // get the number of characters in the string.
    int currentCharIndex = 0;
    char currentChar = pwchar[currentCharIndex];

    while (currentChar != '\0')
    {
        currentCharIndex++;
        currentChar = pwchar[currentCharIndex];
    }

    const int charCount = currentCharIndex + 1;

    // allocate a new block of memory size char (1 byte) instead of wide char (2 bytes)
    char* filePathC = (char*)malloc(sizeof(char) * charCount);

    for (int i = 0; i < charCount; i++)
    {
        // convert to char (1 byte)
        char character = pwchar[i];

        *filePathC = character;

        filePathC += sizeof(char);

    }
    filePathC += '\0';

    filePathC -= (sizeof(char) * charCount);

    return filePathC;
}

char* wide_to_char1(const WCHAR* source)
{
    const auto wide_char_file_path_length = wcslen(source);
    char* destination_buffer;

    auto array_index = 0;
    while (source[array_index] != '\0') {
        destination_buffer[array_index] = static_cast<CHAR>(source[array_index]);
        array_index++;
    }

    destination_buffer[array_index] = '\0';
    return destination_buffer;
}

wchar_t* convertCharArrayToLPCWSTR(const char* charArray)
{
    wchar_t* wString = new wchar_t[4096];
    MultiByteToWideChar(CP_UTF8, 0, charArray, -1, wString, 4096);
    return wString;
}

std::string stringConvert(const std::string s, int baseCP, DWORD bFlags, int needCP, DWORD nFlags)
{
    if (isdebug == true) std::cout << "INITIAL " << s << std::endl;
    //constexpr DWORD kFlags = MB_ERR_INVALID_CHARS;

    std::wstring internal(s.size()*2, '\0');
    MultiByteToWideChar(
        baseCP,       // Source string is in UTF-8
        bFlags,        // Conversion flags
        s.data(),   // Source UTF-8 string pointer
        s.size(),    // Length of source UTF-8 string, in chars
        &internal[0],     // Pointer to destination buffer
        internal.size()    // Size of destination buffer, in wchar_ts          
    );

    std::string result(internal.size(), '\0');
    char* result1;
    WideCharToMultiByte(needCP, nFlags, internal.data(), internal.size(), &result[0], result.size(), NULL, NULL);
    //WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, internal.data(), internal.size(), result1, 2100, NULL, NULL);
    result1 = destr(result);


    if (isdebug == true) std::wcout << L"wConverted " << internal << std::endl;
    if (isdebug == true) std::cout << "Converted " << result << std::endl;
    if (isdebug == true) std::cout << "Converted TEST " << result1 << std::endl;

    return result;
}

std::string stringConvertBack(const std::string s)
{

    constexpr DWORD kFlags = MB_ERR_INVALID_CHARS;

    std::wstring internal(s.size(), '\0');
    MultiByteToWideChar(
        CP_ACP,       // Source string is in UTF-8
        WC_COMPOSITECHECK,        // Conversion flags
        s.data(),   // Source UTF-8 string pointer
        s.size(),    // Length of source UTF-8 string, in chars
        &internal[0],     // Pointer to destination buffer
        internal.size()    // Size of destination buffer, in wchar_ts          
    );

    std::string result(internal.size(), '\0');
    char* result1;
    WideCharToMultiByte(CP_UTF8, MB_ERR_INVALID_CHARS, internal.data(), internal.size(), &result[0], result.size(), NULL, NULL);
    //WideCharToMultiByte(CP_ACP, WC_COMPOSITECHECK, internal.data(), internal.size(), result1, 2100, NULL, NULL);
    result1 = destr(result);


    std::wcout << L"wConverted " << internal << std::endl;
    std::cout << "Converted " << result << std::endl;
    std::cout << "Converted TEST " << result1 << std::endl;

    return result;
}

char* convToChar(char* chr) {
    typedef std::codecvt<char, char, std::mbstate_t> facet_type;

    std::locale mylocale = std::locale("English");

    std::cout << __FUNCTION__ << "\n";
    const facet_type& myfacet = std::use_facet<facet_type>(mylocale);

    char* mystr;

    // prepare objects to be filled by codecvt::in :
    std::mbstate_t mystate = std::mbstate_t(); // the shift state object
    const char* pc;                            // from_next

    // translate characters:
    //facet_type::result myresult = myfacet.in(mystate, & s, & s + sizeof(mystr), pc, mystr, mystr + sizeof(mystr), mystr);
    facet_type::result myresult = myfacet.in(mystate, mystr , mystr + sizeof(mystr), pc, chr, chr + sizeof(mystr), chr);
    if (myresult == facet_type::ok)
    {
        std::cout << "Translation successful: ";
        std::cout << mystr << std::endl;
    }
    return 0;
}



bool is_file_exist(const char* fileName)
{
    std::ifstream infile(fileName);
    return infile.good();
}

int exist(const char* name)
{
    struct stat   buffer;
    return (stat(name, &buffer) == 0);
}

int exist2(const char* name)
{
    struct stat   buffer;
    char nameuserFld[128] = "userdata/";
    strcat(nameuserFld, name);
    return (stat(nameuserFld, &buffer) == 0);
}

char* destr(const std::string s) {
    if (!s.empty()) {
        return _strdup(s.c_str());
    }
    else {
        return "";
    }
}

wchar_t* destrW(const std::wstring s) {
    if (!s.empty()) {
        return _wcsdup(s.c_str());
    }
    else {
        return L"";
    }
}

char* destrC(const std::string s) {
    std::string ss = stringConvertBack(s);
    if (!s.empty()) {
        return _strdup(ss.c_str());
    }
    else {
        return "";
    }
}

//char* destrw(const std::wstring s) {
//    if (!s.empty()) {
//        return std::wcstombs(64,s.c_str(),64);
//    }
//    else {
//        return "";
//    }
//}

int funcCloseFileOpened() {
    std::fstream fs;
    if (fs.is_open()) {
        fs.close();
        //checkOpened = 0;
        return 1;
    }

    return 0;
}

Json::Value funcGetJson(char*& filename)
{
    std::fstream fs;
    Json::Value root;
    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    std::locale loc = std::locale("Russian");
    fs.imbue(loc);
    Json::CharReaderBuilder rbuilder;
    rbuilder["collectComments"] = false;
    std::string errs;
    Json::parseFromStream(rbuilder, fs, &root, &errs);

    fs.close();
    return root;
}

void jsonRewriteFile(Json::Value root, char* filename, bool isUTF8 = true)
{
    std::fstream fs;
    fs.open(filename, std::ios::binary | std::fstream::in | std::ofstream::out | std::ofstream::trunc);
    
    //std::locale loc = std::locale("Russian_Russia.1251");
    std::locale loc = std::locale("Russian");
    fs.imbue(loc);
    std::cout << "Locale = " << fs.getloc().c_str() << "\n";
    std::cout << "PATH = " << root[root.getMemberNames()[0]]["path"].asCString() << "\n";
    Json::StreamWriterBuilder builder;
    if (isUTF8 == true) {
        builder["emitUTF8"] = true;
    }
    else {
        builder["emitUTF8"] = false;
    }
    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(root, &fs);
}

int funcFixPath2(char* filename)
{
    int done = 0;
    Json::Value root = funcGetJson(filename);


    std::string sub = root.getMemberNames()[0];
    //std::cout << "Adding " << key << ":" << value << " to " << root.getMemberNames()[0] << "\n";
    if (root[sub]["path"]) {
        char* pathVal = destr(root[sub]["path"].asCString());
        wchar_t* pszFilePath;
        MultiByteToWideChar(1251, WC_COMPOSITECHECK, pathVal, -1, pszFilePath, 500);
        std::wcout << "W = " << pszFilePath << "  ; ";
        WideCharToMultiByte(1251, WC_COMPOSITECHECK, pszFilePath, -1, pathVal, 500, NULL, NULL);
        std::cout << "C = " << pathVal << "  ; ";



        root[sub]["path"] = pathVal;
    }

    //std::fstream fs1;
    jsonRewriteFile(root, filename);
    //fs.swap(fs1);

    return done;
}

int funcFixPath3(Json::Value root, char* filename)
{
    int done = 0;

    std::string sub = root.getMemberNames()[0];
    //std::cout << "Adding " << key << ":" << value << " to " << root.getMemberNames()[0] << "\n";
    if (root[sub]["path"]) {
        std::string pathVal = root[sub]["path"].asString();
        pathVal = stringConvert(pathVal, CTRY_RUSSIA, WC_COMPOSITECHECK, CP_UTF8, MB_ERR_INVALID_CHARS);
        std::cout << "C = " << pathVal << "  ; " << std::endl;
        

        root[sub]["path"] = pathVal;
    }

    //std::fstream fs1;
    jsonRewriteFile(root, filename);
    //fs.swap(fs1);

    return done;
}


char* funcGetIdxName(char*& filename, int idx)
{
    std::fstream fs;
    Json::Value root;
    Json::ArrayIndex starter;

    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);

    fs >> root;
    if (root != NULL && root.getMemberNames().size() > 0 && root.getMemberNames()[idx] != "") {
        char* memberX = _strdup(root.getMemberNames()[idx].c_str());
        //std::cout << "funcGetIdxName has root: #" << idx << " is " << memberX << "\n";

        return memberX;
    }
    else {
        return "NULL_NAME";
    }
}


char* funcParseJsonTest(char* category, char* windowX, int idx, char* filename)
{
    char* testName = new char;
    std::fstream fs;
    Json::Value root;
    //funcLoadJson(fs, "userdata/test.json");
    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    //checkOpened = 1;
    fs >> root;
    if (root[category][windowX][idx]) {
        testName = _strdup(root[category][windowX][idx].asCString());
    }
    else {
        testName = "NULL_JSON";
    }
    return testName;
}

//book,classic
std::vector<std::string> funcProcessTags(char* tags) {
    std::vector<std::string> arr;
    char* arr1[] = { "" };
    int len = strlen(tags);
    if (isdebug == true) std::cout << len << "\n";
    int x = 0;
    int y = 0;
    int yy = 1;
    arr.push_back("");
    for (int i = 0; i < len; i++) {

        if (tags[i] == ',') {
            y += 1;
            arr.push_back("");
        }
        else {
            arr[y] += tags[i];
            if (isdebug == true) std::cout << i << " in " << y << " = " << arr[y] << "\n";
        }
    }

    //std::cout << "Result 0 = " << arr[0] << "\n";

    return arr;
}

int funcWriteJson_tags(char* tags, char* filename)
{
    int done = 0;

    Json::Value root = funcGetJson(filename);

    char* name = _strdup(root.getMemberNames()[0].c_str());


    char* tagsProcessed[] = { "" };
    if (isdebug == true) std::cout << "Starting funcWriteJson_tags...";
    std::vector<std::string> arr = funcProcessTags(tags);
    if (isdebug == true) std::cout << "Result Write 0 = " << arr[0] << " in " << arr.size() << "\n";
    root[name].removeMember("tags");

    for (int i = 0; i < arr.size(); i++) {
        if (isdebug == true) std::cout << i << " has " << _strdup(arr[i].c_str()) << "\n";
        root[name]["tags"][i] = _strdup(arr[i].c_str());
    }

    jsonRewriteFile(root, filename);

    return done;
}

int funcWriteJson(char* newItemInfoBuffer[], char* filename)
{
    int done = 0;

    std::fstream fs;
    Json::Value root;
    char* name = newItemInfoBuffer[0];
    char* tags = newItemInfoBuffer[1];

    //fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    //fs >> root;
    char* tagsProcessed[] = { "" };
    std::cout << "Starting funcProcessTags...";
    std::vector<std::string> arr = funcProcessTags(tags);
    std::cout << "Result Write 0 = " << arr[0] << " in " << arr.size() << "\n";
    //std::copy(std::begin(arr), std::end(arr), std::begin(tagsProcessed));


    for (int i = 0; i < arr.size(); i++) {
        std::cout << i << " has " << _strdup(arr[i].c_str()) << "\n";
        root[name]["tags"][i] = _strdup(arr[i].c_str());
    }

    std::map<char*, char*> infoJ;
    int len = 6;//sizeof(newItemInfoBuffer);

    for (int i = 2; i < len; i+=2) {
        //infoJ[newItemInfoBuffer[i]] = newItemInfoBuffer[i + 1];
        root[name]["info"][newItemInfoBuffer[i]] = newItemInfoBuffer[i + 1];
        std::cout << len << " total " << newItemInfoBuffer[i] << "\n";
    }

    root[name]["path"] = newItemInfoBuffer[6];

    wchar_t* nameW = convertCharArrayToLPCWSTR(filename);
    std::wcout << u8"ФАЙЛ = " << nameW << "\n";

    std::fstream outfile(nameW, std::fstream::in | std::fstream::out | std::fstream::app);

    //std::locale wLoc = (outfile.getloc(), new std::codecvt_utf8<unsigned char>);

    //outfile.imbue(wLoc);

    std::cout << "Locale is " << outfile.getloc().name() << "\n";


    //outfile.imbue(loc);

    Json::StreamWriterBuilder builder;
    builder["emitUTF8"] = true;
    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(root, &outfile);;

    //root >> outfile;
    //fs.close();
    outfile.close();

    return done;
}

int funcWriteJsonSimpleData(char* key, char* value, char* filename)
{
    int done = 0;
    Json::Value root;
    //root = funcGetJson(filename);
    std::fstream fs;
    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    fs >> root;
    fs.close();
    fs.open(filename, std::fstream::in | std::ofstream::out | std::ofstream::trunc);

    std::cout << "Adding " << key << ":" << value << " to " << root.getMemberNames()[0] << "\n";
    root[key] = value;
    //std::fstream fs1;
    Json::StreamWriterBuilder builder;
    builder["emitUTF8"] = true;
    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(root, &fs);;
    //fs.swap(fs1);

    return done;
}

int funcWriteJsonSimpleData2(char* key, char* value, char* filename)
{
    int done = 0;
    Json::Value root = funcGetJson(filename);
    
    //std::wbuffer_convert<std::codecvt_utf8<wchar_t>> conv(fs.rdbuf());
    //fs.open(filename, std::fstream::in | std::ofstream::out | std::ofstream::trunc);

    std::string name = root.getMemberNames()[0];

    //CharToOemA(value, value);
    //char* value1 = destr(stringConvert(value, CP_OEMCP, MB_USEGLYPHCHARS, CP_UTF8, WC_COMPOSITECHECK));
    //std::cout << "value1 " << value1  << "\n";
    
    //std::cout << "value2 " << value2 << "\n";
    //char* value3 = destr(stringConvert(value, CP_ACP, 0, CP_UTF8, 0));
    //std::cout << "value3 " << value3 << "\n";
    //char* value4 = destr(stringConvert(value, CP_UTF8, MB_ERR_INVALID_CHARS, CP_OEMCP, WC_COMPOSITECHECK));
    //std::cout << "value4 " << value4 << "\n";

    std::cout << __FUNCTION__ << ": Adding " << key << " : " << value << " to " << name << " and "  << "\n";
    if (value != "") {
        root[name][key] = value;
    }
    else {
        root[name][key] = "NULL";
    }
    //std::fstream fs1;

    //jsonRewriteFile(root, filename);
    //fs.swap(fs1);
    //funcFixPath3(root, filename);
    jsonRewriteFile(root, filename);

    return done;
}

int funcWriteJsonSimpleData3(char* key, std::string value, char* filename)
{
    int done = 0;
    Json::Value root = funcGetJson(filename);

    std::string name = root.getMemberNames()[0];

    //CharToOemA(value, value);
    std::cout << "Adding " << key << ":" << value << " to " << name << " and " << "\n";
    root[name][key] = value;
    //std::fstream fs1;

    jsonRewriteFile(root, filename);
    //fs.swap(fs1);
    funcFixPath2(filename);


    return done;
}

int funcWriteJsonSimpleData2W(char* key, wchar_t* value, char* filename)
{
    int done = 0;
    Json::Value root;
    //root = funcGetJson(filename);
    std::fstream fs;
    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    fs >> root;
    fs.close();

    std::string name = root.getMemberNames()[0];
    MessageBoxW(NULL, value, L"File Path", MB_OK);
        //std::wcout << "Input: " << key << ":" << value << "\n";

    //auto valC = wide_to_char1(value);
    //wcstombs(valC, value,500);
    std::cout << "Adding " << key << ":" << value << " to " << name << "\n";
    
    root[name][key] = value;
    //std::fstream fs1;

    jsonRewriteFile(root, filename);

    funcFixPath2(filename);
    //fs.swap(fs1);

    return done;
}

int funcFixPath(char* filename)
{
    int done = 0;
    Json::Value root;
    //root = funcGetJson(filename);
    std::fstream fs;
    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    fs >> root;
    fs.close();
    //fs.open(filename, std::fstream::in | std::ofstream::out | std::ofstream::trunc);


    //std::cout << "Adding " << key << ":" << value << " to " << root.getMemberNames()[0] << "\n";
    if (root["path"]) {
        std::string pathVal = root["path"].asString();
        //root.removeMember("path");
        std::string sub = root.getMemberNames()[0];
        root[sub]["path"] = pathVal;
    }
    
    //std::fstream fs1;
    jsonRewriteFile(root, filename);
    //fs.swap(fs1);

    return done;
}

int funcWriteJsonSimpleSubData(int buf, char* key[], char* value[], char*& filename)
{
    int done = 0;


    std::fstream fs;
    Json::Value root;
    //std::locale loc;
    //loc = std::locale("en_US.UTF8");
    //fs.imbue(std::locale("UTF8"));
    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    std::cout << "Opened " << "\n";
    fs >> root;
    std::cout << "Got root " << "\n";
    char* name = _strdup(root.getMemberNames()[0].c_str());
    std::cout << "Got name " << "\n";
    fs.close();
    std::cout << "Closed " << "\n";
    fs.open(filename, std::fstream::in | std::ofstream::out | std::ofstream::trunc);
    std::cout << "Cleared with " << fs.getloc().c_str() << "\n";

    std::cout << "Adding " << key[0] << ":" << value[0] << " to " << name << "\n";
    root[name].removeMember("info");

    for (int i = 0; i < buf; i++) {
        if (key[i][0] != '\0' && value[i][0] != '\0') {
            std::cout << i << " has " << key[i] << ":" << value[i] << "out of" << buf << "\n";
            root[name]["info"][key[i]] = value[i];
        }
        //Json::StyledWriter styledWriter;
        //fs << styledWriter.write(root);

    }
    Json::StreamWriterBuilder builder;
    builder["emitUTF8"] = true;
    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(root, &fs);

    //fs << builder;


    return done;
}

int funcWriteJsonSimpleSubDataStr(int buf, std::string key[], std::string value[], char*& filename)
{
    int done = 0;


    std::fstream fs;
    Json::Value root;
    //std::locale loc;
    //loc = std::locale("en_US.UTF8");
    fs.imbue(std::locale("C"));
    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    std::cout << "Opened " << "\n";
    fs >> root;
    std::cout << "Got root " << "\n";
    char* name = _strdup(root.getMemberNames()[0].c_str());
    std::cout << "Got name " << "\n";
    fs.close();
    std::cout << "Closed " << "\n";
    fs.open(filename, std::fstream::in | std::ofstream::out | std::ofstream::trunc);
    std::cout << "Cleared with " << fs.getloc().c_str() << "\n";

    //std::cout << "Adding " << key[0] << ":" << value[0] << " to " << name << "\n";
    root[name].removeMember("info");


    for (int i = 0; i < buf; i++) {
        if (key[i][0] != '\0' && value[i][0] != '\0') {
            std::cout << i << " has " << key[i] << ":" << value[i] << " out of " << buf << "\n";
            root[name]["info"][key[i]] = value[i];
        }
    }
    Json::StreamWriterBuilder builder;
    builder["emitUTF8"] = true;
    std::unique_ptr<Json::StreamWriter> writer(builder.newStreamWriter());
    writer->write(root, &fs);;


    return done;
}

int funcWriteJsonWriterData(char* key, char* value, char* filename)
{
    int done = 0;
    Json::Value root;
    //root = funcGetJson(filename);
    Json::StreamWriterBuilder wbuilder;
    wbuilder["indentation"] = "\t";

    
    std::fstream fs;
    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    fs >> root;

    std::cout << "Adding " << key << ":" << value << " to " << root.getMemberNames()[0] << "\n";
    root[key] = value;

    std::string document = Json::writeString(wbuilder, root);

    //Json::writeString(wbuilder,root);
    /*std::unique_ptr<Json::StreamWriter> writer(
        wbuilder.newStreamWriter());
    writer->write(value, &fs);*/
    //std::fstream fs1;
    //fs.swap(fs1);

    return done;
}

const char* funcHasTags(char* filename)
{
    const char* testName = "NULL";
    std::fstream fs;
    Json::Value root;

    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);

    //std::cout << "funcHasTags Opened " << fs.fail() << "\n";
    Json::CharReaderBuilder rbuilder;
    rbuilder["collectComments"] = false;
    std::string errs;
    Json::parseFromStream(rbuilder, fs, &root, &errs);

    //try {
    //    fs >> root;
    //}
    //catch (const char* message) {

    //    std::cout << message << "\n";
    //}


   // std::cout << "funcHasTags To Root " << "\n";

    if (root) {
       // std::cout << "funcHasTags Has Root " << "\n";
        char* tmpName = funcGetIdxName(filename, 0);
        Json::Value subPart = root[tmpName];
        //std::cout << "funcHasTags subpart " << "\n";
        if (subPart["tags"]) {
            testName = subPart["tags"][0].asCString();
        }
    }

    return testName;
}

const char* funcHasName(char* filename, char* namename)
{
    const char* testName = "NULL";
    std::fstream fs;
    Json::Value root;

    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);

    fs >> root;
    Json::Value subPart = root[funcGetIdxName(filename, 0)];
    //std::cout << " is subPart " << "\n";
    if (subPart[namename]) {
        //std::cout << " is namename " << subPart[namename].getMemberNames()[0] << "\n";

        if (subPart[namename].getMemberNames()[0] != "") {
            //std::cout << " is info0 " << "\n";
            testName = subPart[namename].getMemberNames()[0].c_str();
        }
        /*else {
            std::cout << " is info " << "\n";
            testName = subPart[namename].getMemberNames()[0].c_str();
        }*/
    }

    if (isdebug == true) std::cout << __FUNCTION__ << " FINISHED " << "\n";

    return testName;
}

char* funcGetTags(char* filename)
{
    char* testName = "NULL";
    Json::Value root;
    root = funcGetJson(filename);
    Json::Value subPart = root[funcGetIdxName(filename, 0)];
    std::string tmpTags;
    //std::cout << " tmpTags" << tmpTags << "\n";
    if (subPart["tags"]) {
        int len = (subPart["tags"]).size();
        
       // std::cout << filename << " len = " << len << "\n";
        for (int i = 0; i < len; i++) {
            tmpTags += subPart["tags"][i].asString();
            if (i < (len - 1)) {
                tmpTags += ",";
            }
            //tmpTags = stringConvert(tmpTags, CP_UTF8, MB_ERR_INVALID_CHARS, CP_ACP, WC_COMPOSITECHECK);
            //std::cout << i << " : " << tmpTags << "\n";
        }
    }
    testName = _strdup(tmpTags.c_str());

    //std::cout << filename << " got tags: " << testName << "\n";
    if (isdebug == true) std::cout << __FUNCTION__ << " got tags: " << testName << "\n";
    //std::cout << __FUNCTION__ << "\n";
    return testName;
}

char* funcGetInfo(char* filename)
{
    std::cout << __FUNCTION__  << "\n";
    char* testName = "NULL";
    std::fstream fs;
    Json::Value root;
    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    fs >> root;
    Json::Value subPart = root[funcGetIdxName(filename, 0)];
    //std::cout << testName << " subPart = " << "\n";
    Json::Value subPart1 = subPart["info"];
    
    std::string tmpTags;
    //char* infoNames = _strdup(.c_str());
    if (subPart1) {
        // std::cout << filename << " subPart = " << subPart1[0] << "\n";

        int len = (subPart1).size();

        std::cout << "subPart1 len = " << len << "\n";

        for (int i = 0; i < len; i++) {
            tmpTags += subPart1.getMemberNames()[i];
            //std::cout << tmpTags << " +Name " << "\n";
            tmpTags += ":";
            tmpTags += subPart1[subPart1.getMemberNames()[i]].asString();
            std::cout << tmpTags << " Name:Value " << "\n";
            if (i < (len - 1)) {
                tmpTags += ",";
            }
            //std::cout << tmpTags << "\n";
        }
    }
    testName = _strdup(tmpTags.c_str());

    //std::cout << filename << " got info: " << testName << "\n";
    return testName;
}

std::map<char*, char*> funcGetInfoMap(char* filename)
{
    //std::cout << __FUNCTION__ << "\n";
    std::map<char*, char*> testName;
    std::fstream fs;
    Json::Value root;
    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    fs >> root;
    Json::Value subPart = root[funcGetIdxName(filename, 0)];
    //std::cout << testName << " subPart = " << "\n";
    Json::Value subPart1 = subPart["info"];

    std::string tmpTags;
    //char* infoNames = _strdup(.c_str());
    if (subPart1) {
        // std::cout << filename << " subPart = " << subPart1[0] << "\n";

        int len = (subPart1).size();

        //std::cout << "subPart1 len = " << len << "\n";

        for (int i = 0; i < len; i++) {
            char* tmpName = destr(subPart1.getMemberNames()[i]);
            testName[tmpName] = destr(subPart1[tmpName].asString());
            //std::cout << tmpTags << " +Name " << "\n";
            //std::cout << tmpTags << "\n";
        }
    }

    if (isdebug == true) std::cout << __FUNCTION__ << "\n";
    //std::cout << filename << " got info: " << testName << "\n";
    return testName;
}

std::vector<std::map<std::string, std::string>> funcGetInfoPairs(char* filename)
{
    std::cout << __FUNCTION__ << "\n";
    std::vector<std::map<std::string, std::string>> testName;
    std::fstream fs;
    Json::Value root;
    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    fs >> root;
    Json::Value subPart = root[funcGetIdxName(filename, 0)];
    //std::cout << testName << " subPart = " << "\n";
    Json::Value subPart1 = subPart["info"];

    //std::string tmpTags;
    //char* infoNames = _strdup(.c_str());
    if (subPart1) {
        // std::cout << filename << " subPart = " << subPart1[0] << "\n";

        int len = (subPart1).size();

        std::cout << "subPart1 len = " << len << "\n";
        int x = 0;
        for (int i = 0; i < len; i++) {
            std::map<std::string, std::string> tmpMap;
            std::string key = subPart1.getMemberNames()[i];
            tmpMap["key"] = key;
            tmpMap["val"] = subPart1[key].asString();
            testName.push_back(tmpMap);
            //std::cout << tmpTags << " +Name " << "\n";
            std::cout << key << " : " << tmpMap[key] << " Name:Value " << "\n";
        }
    }

    return testName;
}

std::string funcGetDataPath(char* filename)
{
    std::string testName = "NULL";

    std::cout << filename << " funcGetDataPath: " << testName << "\n";
    std::fstream fs;
    Json::Value root;
    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    fs >> root;

    //Json::Value subPart = root[funcGetIdxName(filename, 0)];
    
    if (root["path"]) {
        testName = root["path"].asString();
    }

    return testName;
}

std::string funcGetDataPathNew(char* filename)
{
    std::string testName = "NULL";

    
    std::fstream fs;
    Json::Value root;
    
    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
    std::locale loc = std::locale("Russian");
    fs.imbue(loc);
    fs >> root;

    std::string name = root.getMemberNames()[0];

    //std::cout << __FUNCTION__ << " : " << name << "\n";

    if (root[name]["path"]) {
        testName = root[name]["path"].asString();
    }

    //std::cout << filename << " funcGetDataPath: " << testName << "\n";
    if (isdebug == true) std::cout << __FUNCTION__ << "\n";

    return testName;
}

char* getFirstCategoryOnly(char* filename)
{
    char* testName = "NULL_JSON";


    if (exist(filename) == 0) {
        return testName;
    }
    else {
        std::fstream fs;
        Json::Value root;
        Json::ArrayIndex starter;
        starter = 0;
        int idx = 0;

        Json::PathArgument starter1;

        fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);
        //checkOpened = 1;
        fs >> root;
        if (root != NULL) {
            //testName = _strdup(root.get(starter,"NULL_JSON").asCString());

            std::vector<std::string> testMembers;
            Json::Value::Members getMemberNames(testMembers);
            //Json::ValueType tempSTR = root.type();
            //std::string tstSTR = Json::valueToString(tempSTR);
            //std::string tstSTR = typeid(testMembers[0u][0u]).name();
            testName = _strdup(root.getMemberNames()[0].c_str());
            //testName = "";
            //testName = _strdup(testMembers[0][0].c_str());
            //std::string tstSTR;
            //tstSTR.assign(testName1);

        }
        return testName;
    }
}

std::string funcGetIdxNameStr(std::string filename, int idx)
{
    std::fstream fs;
    Json::Value root;
    Json::ArrayIndex starter;


    Json::PathArgument starter1;

    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);

    fs >> root;
    if (root != NULL ) {
        if (root.getMemberNames()[idx] != "") {
            std::string memberX = root.getMemberNames()[idx];
            //std::cout << "funcGetIdxName has root: first is " << memberX << "\n";
            return memberX;
        }
        else {
            return "NULL_NAME";
        }
    }
    else {
        return "NULL_NAME";
    }
}

std::string funcBaseGetFromJson(std::string key, std::string& filename)
{
    std::fstream fs;
    Json::Value root;
    Json::ArrayIndex starter;


    Json::PathArgument starter1;

    fs.open(filename, std::fstream::in | std::fstream::out | std::fstream::app);

    fs >> root;

    if (root[key]) {
        return root[key].asString();
    }
    else {
        return "NULL";
    }
}

char* funcAssembleFromMap(CharMap& charMap) {

    //std::cout << __FUNCTION__ << "\n";
    std::string tmpStr;
    char* separ = " : ";

    CharMap::iterator it = charMap.begin();
    // Iterate over the map using Iterator till end.
    while (it != charMap.end())
    {

        char* key = it->first;
        if (key && key != "NULL") {

            char* val = it->second;

            tmpStr += key;
            tmpStr += separ;
            tmpStr += val;
            
        }
        it++;
        if (it != charMap.end() && key && key != "NULL") tmpStr += "; ";
    }
    //std::cout << tmpStr << "\n";
    return destr(tmpStr);
}



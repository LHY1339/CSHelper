#pragma once
#include <Windows.h>
#include <easyx.h>
#include <vector>

#include "Define.h"
#include "Canvas.h"
#include "Button.h"
#include "Text.h"
#include "Image.h"
#include "ScrollBox.h"

enum EMenu
{
	Home,
	Basic,
	Fake,
	Game,
};

HWND hwnd;
ExMessage msg;
bool IsFocus = false;
EMenu Menu = EMenu::Home;
std::vector<std::string> OutputLog;
bool IsAutoAccept = false;
bool IsAutoReact = false;
int FocusID = -1;
std::string FakeItem;
std::string FakeSkin;
std::string FakeChannel;
std::string FakeItemCommand;

//Defaults
CCanvas Canvas_Background;
CCanvas Canvas_Menu;
CButton Button_Home;
CButton Button_Basic;
CButton Button_Fake;
CButton Button_Game;
CButton Button_Quit;

//Console
CCanvas Canvas_Console;
CText Text_Console;

//Home
CText Text_Profile;
CCanvas Canvas_Profile;
CImage Image_Profile;
CButton Button_Github;

//Basic
CButton Button_KillCS2;
CButton Button_KillSteam;
CButton Button_KillWanmei;
CButton Button_KillNet;
CButton Button_AutoAccept;
CButton Button_AutoReact;
CButton Button_SetCS2;
CButton Button_ClearSet;

//Fake
CScrollBox ScrollBox_Item;
CScrollBox ScrollBox_Skin;
CScrollBox ScrollBox_Channel;
CText Text_Fake;
CButton Button_Copy;

int main(void);

MAIN_EVENT ME_Init();
MAIN_EVENT ME_Block();

THREAD_EVENT TE_Logic();
THREAD_EVENT TE_Render();
THREAD_EVENT TE_Accept();
THREAD_EVENT TE_React();

CUSTOM_EVENT CE_InitWindow();
CUSTOM_EVENT CE_InitComponent();

CUSTOM_EVENT CE_MouseMessage();

CUSTOM_EVENT CE_RenderDefaults();
CUSTOM_EVENT CE_LogicDefaults();

CUSTOM_EVENT CE_RenderConsole();
CUSTOM_EVENT CE_LogicConsole();

CUSTOM_EVENT CE_RenderHome();
CUSTOM_EVENT CE_LogicHome();

CUSTOM_EVENT CE_RenderBasic();
CUSTOM_EVENT CE_LogicBasic();

CUSTOM_EVENT CE_RenderFake();
CUSTOM_EVENT CE_LogicFake();

BIND_EVENT BE_Button_Home();
BIND_EVENT BE_Button_Basic();
BIND_EVENT BE_Button_Fake();
BIND_EVENT BE_Button_Game();
BIND_EVENT BE_Button_Quit();

BIND_EVENT BE_Button_Github();

BIND_EVENT BE_Button_KillCS2();
BIND_EVENT BE_Button_KillSteam();
BIND_EVENT BE_Button_KillWanmei();
BIND_EVENT BE_Button_KillNet();
BIND_EVENT BE_Button_AutoAccept();
BIND_EVENT BE_Button_AutoReact();
BIND_EVENT BE_Button_SetCS2();
BIND_EVENT BE_Button_ClearSet();

BIND_EVENT BE_ScrollBox_Item();
BIND_EVENT BE_ScrollBox_Skin();
BIND_EVENT BE_ScrollBox_Channel();
BIND_EVENT BE_Button_Copy();

void FlushMenu(CButton* Button);
void AddOutputLog(std::string newlog, std::string category = "LogApplication");
std::string GetWindowTitle(HWND hwnd);
bool CopyFolder(const std::string src, const std::string dst);
std::vector<std::string> GetDirectories(const std::string path);
std::string ReadRegistryValue(HKEY hKeyRoot, std::string subKey, std::string valueName);
void DeleteFilesInDirectory(const std::string directoryPath);
void FlushFakeText();
std::vector<std::string> GetDataFileNames(const std::string directory_path);
std::vector<std::string> ReadFileLines(const std::string file_path);
void SetClipboardText(std::string text);
#include "Main.h"
#include <thread>
#include <Windows.h>
#include <easyx.h>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <codecvt>
#include <locale>

namespace fs = std::filesystem;

int main(void)
{
	ME_Init();

	std::thread th_Logic(TE_Logic);
	th_Logic.detach();

	std::thread th_Render(TE_Render);
	th_Render.detach();

	std::thread th_Accept(TE_Accept);
	th_Accept.detach();

	std::thread th_React(TE_React);
	th_React.detach();

	ME_Block();

	return 0;
}

MAIN_EVENT ME_Init()
{
	CE_InitWindow();
	CE_InitComponent();
}

MAIN_EVENT ME_Block()
{
	CE_MouseMessage();
}

THREAD_EVENT TE_Logic()
{
	while (1)
	{
		if (IsFocus)
		{
			peekmessage(&msg, EX_MOUSE);
			CE_LogicDefaults();
			CE_LogicConsole();

			switch (Menu)
			{
			case EMenu::Home:
				CE_LogicHome();
				break;
			case EMenu::Basic:
				CE_LogicBasic();
				break;
			case EMenu::Fake:
				CE_LogicFake();
				break;
			}
		}
		else
		{
			Sleep(SLEEP_TIME);
		}
	}
}

THREAD_EVENT TE_Render()
{
	while (1)
	{
		if (IsFocus)
		{
			cleardevice();
			CE_RenderDefaults();
			CE_RenderConsole();

			switch (Menu)
			{
			case EMenu::Home:
				CE_RenderHome();
				break;
			case EMenu::Basic:
				CE_RenderBasic();
				break;
			case EMenu::Fake:
				CE_RenderFake();
				break;
			}

			FlushBatchDraw();
		}
		else
		{
			Sleep(SLEEP_TIME);
		}
	}
}

THREAD_EVENT TE_Accept()
{
	HWND hwnd;
	RECT rect;
	HDC hdc;
	while (1)
	{
		if (IsAutoAccept)
		{
			hwnd = GetForegroundWindow();
			if (hwnd != NULL)
			{
				if (GetWindowTitle(hwnd) == "完美世界竞技平台" && IsWindowVisible(hwnd))
				{
					GetWindowRect(hwnd, &rect);
					hdc = GetDC(NULL);
					int width = (rect.right - rect.left) / 2;
					int height = (rect.bottom - rect.top) / 2;

					for (int i = 0; i < 10; i++)
					{
						int yvalue = height + i * 20;
						int xvalue = width - 20;
						COLORREF color = GetPixel(hdc, rect.left + xvalue, rect.top + yvalue);
						if (GetBValue(color) >= 200)
						{
							LPARAM lParam = MAKELPARAM(xvalue, yvalue);
							SendMessageA(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
							SendMessageA(hwnd, WM_LBUTTONUP, 0, lParam);
						}
					}
				}
			}
			Sleep(500);
		}
		else
		{
			Sleep(1000);
		}
	}
}

THREAD_EVENT TE_React()
{
	HWND hwnd;
	RECT rect;
	HDC hdc;
	COLORREF LastColor = RGB(0, 0, 0);
	while (1)
	{
		if (IsAutoReact)
		{
			hwnd = GetForegroundWindow();
			if (hwnd != NULL)
			{
				if (GetWindowTitle(hwnd) == "完美世界竞技平台" && IsWindowVisible(hwnd))
				{
					GetWindowRect(hwnd, &rect);
					hdc = GetDC(NULL);
					int width = (rect.right - rect.left) / 2 + 5;
					int height = (rect.bottom - rect.top) / 2 + 5;
					COLORREF color = GetPixel(hdc, rect.left + width, rect.top + height);
					if (LastColor != color)
					{
						if (LastColor == RGB(0, 0, 0))
						{
							LastColor = color;
						}
						else
						{
							Sleep(1);
							LPARAM lParam = MAKELPARAM(width, height);
							SendMessage(hwnd, WM_LBUTTONDOWN, MK_LBUTTON, lParam);
							SendMessage(hwnd, WM_LBUTTONUP, 0, lParam);
							LastColor = color;
						}
					}
				}
			}
		}
		else
		{
			LastColor = RGB(0, 0, 0);
			Sleep(200);
		}
	}
}

CUSTOM_EVENT CE_InitWindow()
{
	hwnd = initgraph(HWND_W, HWND_H, 0);
	SetWindowLong(
		hwnd,
		GWL_STYLE,
		GetWindowLong(hwnd, GWL_STYLE) - WS_CAPTION
	);
	SetWindowPos(
		hwnd,
		HWND_NOTOPMOST,
		(GetSystemMetrics(SM_CXSCREEN) - HWND_W) / 2,
		(GetSystemMetrics(SM_CYSCREEN) - HWND_H) / 2,
		HWND_W,
		HWND_H,
		SWP_SHOWWINDOW
	);
	setbkmode(1);
	BeginBatchDraw();
}

CUSTOM_EVENT CE_InitComponent()
{
	AddFontResourceExA("./Resource/font.ttf", FR_PRIVATE, NULL);

	//Defaults
	Canvas_Background.Rect = { 0,0,HWND_W,HWND_H ,0 };
	Canvas_Background.LineThick = 0;
	Canvas_Background.FillColor = RGB(20, 20, 20);

	Canvas_Menu.Rect = { 0,0,BAR_W,HWND_H ,0 };
	Canvas_Menu.LineThick = 0;
	Canvas_Menu.FillColor = RGB(40, 40, 40);

	Button_Home.Rect = { 0,0,BAR_W,50 ,0 };
	Button_Home.LineThick = 0;
	Button_Home.Text = "软件首页";
	Button_Home.TextSize = 25;
	Button_Home.NormalColor = RGB(40, 40, 40);
	Button_Home.HoverColor = RGB(50, 50, 50);
	Button_Home.PressColor = RGB(60, 60, 60);

	Button_Basic.Rect = { 0,50,BAR_W,50 ,0 };
	Button_Basic.LineThick = 0;
	Button_Basic.Text = "主要功能";
	Button_Basic.TextSize = 25;
	Button_Basic.NormalColor = RGB(40, 40, 40);
	Button_Basic.HoverColor = RGB(50, 50, 50);
	Button_Basic.PressColor = RGB(60, 60, 60);

	Button_Fake.Rect = { 0,100,BAR_W,50 ,0 };
	Button_Fake.LineThick = 0;
	Button_Fake.Text = "假入库命令";
	Button_Fake.TextSize = 25;
	Button_Fake.NormalColor = RGB(40, 40, 40);
	Button_Fake.HoverColor = RGB(50, 50, 50);
	Button_Fake.PressColor = RGB(60, 60, 60);

	Button_Game.Rect = { 0,150,BAR_W,50 ,0 };
	Button_Game.LineThick = 0;
	Button_Game.Text = "游戏相关";
	Button_Game.TextSize = 25;
	Button_Game.NormalColor = RGB(40, 40, 40);
	Button_Game.HoverColor = RGB(50, 50, 50);
	Button_Game.PressColor = RGB(60, 60, 60);

	Button_Quit.Rect = { 0,HWND_H - 50,BAR_W,50 ,0 };
	Button_Quit.LineThick = 0;
	Button_Quit.Text = "退出软件";
	Button_Quit.TextSize = 25;
	Button_Quit.NormalColor = RGB(40, 40, 40);
	Button_Quit.HoverColor = RGB(50, 50, 50);
	Button_Quit.PressColor = RGB(60, 60, 60);

	//Console
	Canvas_Console.Rect = { BAR_W + 20,HWND_H - 220,HWND_W - BAR_W - 40,200,0 };
	Canvas_Console.FillColor = RGB(10, 10, 10);

	Text_Console.Rect = { BAR_W + 30,HWND_H - 210,HWND_W - BAR_W - 60,180,0 };
	Text_Console.TextSize = 20;
	Text_Console.Text = "";

	//Profile
	Text_Profile.Rect = { 220,20,300,280,0 };
	Text_Profile.Text = HOME_PROFILE;
	Text_Profile.TextSize = 25;

	Canvas_Profile.Rect = { HWND_W - 270,20,250,350,0 };

	Image_Profile.Rect = { HWND_W - 269,21,249,349,0 };
	Image_Profile.Init("./Resource/Mitsuha.png");

	Button_Github.Rect = { 220,320,300,50,0 };
	Button_Github.Text = "Github源码";
	Button_Github.TextSize = 25;
	Button_Github.NormalColor = RGB(40, 40, 40);
	Button_Github.HoverColor = RGB(50, 50, 50);
	Button_Github.PressColor = RGB(60, 60, 60);

	//Basic
	Button_KillCS2.Rect = { 220,20,160,50 ,0 };
	Button_KillCS2.Text = "关闭CS2";
	Button_KillCS2.TextSize = 25;
	Button_KillCS2.NormalColor = RGB(40, 40, 40);
	Button_KillCS2.HoverColor = RGB(50, 50, 50);
	Button_KillCS2.PressColor = RGB(60, 60, 60);

	Button_KillSteam.Rect = { 220,80,160,50 ,0 };
	Button_KillSteam.Text = "关闭Steam";
	Button_KillSteam.TextSize = 25;
	Button_KillSteam.NormalColor = RGB(40, 40, 40);
	Button_KillSteam.HoverColor = RGB(50, 50, 50);
	Button_KillSteam.PressColor = RGB(60, 60, 60);

	Button_KillWanmei.Rect = { 220,140,160,50 ,0 };
	Button_KillWanmei.Text = "关闭完美平台";
	Button_KillWanmei.TextSize = 25;
	Button_KillWanmei.NormalColor = RGB(40, 40, 40);
	Button_KillWanmei.HoverColor = RGB(50, 50, 50);
	Button_KillWanmei.PressColor = RGB(60, 60, 60);

	Button_KillNet.Rect = { 220,200,160,50 ,0 };
	Button_KillNet.Text = "关闭网络";
	Button_KillNet.TextSize = 25;
	Button_KillNet.NormalColor = RGB(40, 40, 40);
	Button_KillNet.HoverColor = RGB(50, 50, 50);
	Button_KillNet.PressColor = RGB(60, 60, 60);

	Button_AutoAccept.Rect = { 400,20,160,50 ,0 };
	Button_AutoAccept.Text = "完美自动准备";
	Button_AutoAccept.TextSize = 25;
	Button_AutoAccept.NormalColor = RGB(40, 40, 40);
	Button_AutoAccept.HoverColor = RGB(50, 50, 50);
	Button_AutoAccept.PressColor = RGB(60, 60, 60);

	Button_AutoReact.Rect = { 400,80,160,50 ,0 };
	Button_AutoReact.Text = "完美反应测试";
	Button_AutoReact.TextSize = 25;
	Button_AutoReact.NormalColor = RGB(40, 40, 40);
	Button_AutoReact.HoverColor = RGB(50, 50, 50);
	Button_AutoReact.PressColor = RGB(60, 60, 60);

	Button_SetCS2.Rect = { 580,20,160,50 ,0 };
	Button_SetCS2.Text = "一键设置CS2";
	Button_SetCS2.TextSize = 25;
	Button_SetCS2.NormalColor = RGB(40, 40, 40);
	Button_SetCS2.HoverColor = RGB(50, 50, 50);
	Button_SetCS2.PressColor = RGB(60, 60, 60);

	Button_ClearSet.Rect = { 580,80,160,50 ,0 };
	Button_ClearSet.Text = "清除所有用户";
	Button_ClearSet.TextSize = 25;
	Button_ClearSet.NormalColor = RGB(40, 40, 40);
	Button_ClearSet.HoverColor = RGB(50, 50, 50);
	Button_ClearSet.PressColor = RGB(60, 60, 60);

	//Fake
	ScrollBox_Item.Rect = { 220,20,160,40 };
	ScrollBox_Item.NormalColor = RGB(40, 40, 40);
	ScrollBox_Item.HoverColor = RGB(50, 50, 50);
	ScrollBox_Item.PressColor = RGB(60, 60, 60);
	ScrollBox_Item.ShowIndex = 8;

	ScrollBox_Skin.Rect = { 400,20,160,40 };
	ScrollBox_Skin.NormalColor = RGB(40, 40, 40);
	ScrollBox_Skin.HoverColor = RGB(50, 50, 50);
	ScrollBox_Skin.PressColor = RGB(60, 60, 60);
	ScrollBox_Skin.ShowIndex = 8;
	ScrollBox_Skin.ArrayText = { "请选择物品" };

	ScrollBox_Channel.Rect = { 580,20,200,40 };
	ScrollBox_Channel.NormalColor = RGB(40, 40, 40);
	ScrollBox_Channel.HoverColor = RGB(50, 50, 50);
	ScrollBox_Channel.PressColor = RGB(60, 60, 60);
	ScrollBox_Channel.ShowIndex = 2;
	ScrollBox_Channel.ArrayText = { "交易","开箱" };

	Text_Fake = { 580,HWND_H-440,200,120,0 };
	Text_Fake.TextSize = 30;

	Button_Copy.Rect = { 580,HWND_H - 310,200,50 ,0 };
	Button_Copy.Text = "复制命令";
	Button_Copy.TextSize = 25;
	Button_Copy.NormalColor = RGB(40, 40, 40);
	Button_Copy.HoverColor = RGB(50, 50, 50);
	Button_Copy.PressColor = RGB(60, 60, 60);



	FlushFakeText();
	BE_Button_Home();
}

CUSTOM_EVENT CE_MouseMessage()
{
	while (1)
	{
		if (GetForegroundWindow() == hwnd)
		{
			IsFocus = true;
			PostMessage(hwnd, WM_NCLBUTTONDOWN, HTCAPTION, MAKELPARAM(msg.x, msg.y));
		}
		else
		{
			IsFocus = false;
		}
		Sleep(1);
	}
}

CUSTOM_EVENT CE_RenderDefaults()
{
	Canvas_Background.Render();
	Canvas_Menu.Render();

	Button_Home.Render();
	Button_Basic.Render();
	Button_Fake.Render();
	Button_Quit.Render();
	Button_Game.Render();
}

CUSTOM_EVENT CE_LogicDefaults()
{
	Button_Home.Logic(&msg);
	switch (Button_Home.State)
	{
	case EButtonState::Click:
		BE_Button_Home();
		break;
	}

	Button_Basic.Logic(&msg);
	switch (Button_Basic.State)
	{
	case EButtonState::Click:
		BE_Button_Basic();
		break;
	}

	Button_Fake.Logic(&msg);
	switch (Button_Fake.State)
	{
	case EButtonState::Click:
		BE_Button_Fake();
		break;
	}

	Button_Game.Logic(&msg);
	switch (Button_Game.State)
	{
	case EButtonState::Click:
		BE_Button_Game();
		break;
	}

	Button_Quit.Logic(&msg);
	switch (Button_Quit.State)
	{
	case EButtonState::Click:
		BE_Button_Quit();
		break;
	}
}

CUSTOM_EVENT CE_RenderConsole()
{
	Canvas_Console.Render();
	Text_Console.Render();
}

CUSTOM_EVENT CE_LogicConsole()
{

}

CUSTOM_EVENT CE_RenderHome()
{
	Text_Profile.Render();
	Canvas_Profile.Render();
	Image_Profile.Render();
	Button_Github.Render();
}

CUSTOM_EVENT CE_LogicHome()
{
	Button_Github.Logic(&msg);
	switch (Button_Github.State)
	{
	case EButtonState::Click:
		BE_Button_Github();
		break;
	}
}

CUSTOM_EVENT CE_RenderBasic()
{
	Button_KillCS2.Render();
	Button_KillSteam.Render();
	Button_KillWanmei.Render();
	Button_KillNet.Render();
	Button_AutoAccept.Render();
	Button_AutoReact.Render();
	Button_SetCS2.Render();
	Button_ClearSet.Render();
}

CUSTOM_EVENT CE_LogicBasic()
{
	Button_KillCS2.Logic(&msg);
	switch (Button_KillCS2.State)
	{
	case EButtonState::Click:
		BE_Button_KillCS2();
		break;
	}

	Button_KillSteam.Logic(&msg);
	switch (Button_KillSteam.State)
	{
	case EButtonState::Click:
		BE_Button_KillSteam();
		break;
	}

	Button_KillWanmei.Logic(&msg);
	switch (Button_KillWanmei.State)
	{
	case EButtonState::Click:
		BE_Button_KillWanmei();
		break;
	}

	Button_KillNet.Logic(&msg);
	switch (Button_KillNet.State)
	{
	case EButtonState::Click:
		BE_Button_KillNet();
		break;
	}

	Button_AutoAccept.Logic(&msg);
	switch (Button_AutoAccept.State)
	{
	case EButtonState::Click:
		BE_Button_AutoAccept();
		break;
	}

	Button_AutoReact.Logic(&msg);
	switch (Button_AutoReact.State)
	{
	case EButtonState::Click:
		BE_Button_AutoReact();
		break;
	}

	Button_SetCS2.Logic(&msg);
	switch (Button_SetCS2.State)
	{
	case EButtonState::Click:
		BE_Button_SetCS2();
		break;
	}

	Button_ClearSet.Logic(&msg);
	switch (Button_ClearSet.State)
	{
	case EButtonState::Click:
		BE_Button_ClearSet();
		break;
	}

}

CUSTOM_EVENT CE_RenderFake()
{
	ScrollBox_Item.Render();
	ScrollBox_Skin.Render();
	ScrollBox_Channel.Render();
	Text_Fake.Render();
	Button_Copy.Render();
}

CUSTOM_EVENT CE_LogicFake()
{
	ScrollBox_Item.Logic(&msg);
	switch (ScrollBox_Item.State)
	{
	case EScrollBoxState::ScrollClick:
		BE_ScrollBox_Item();
		break;
	}

	ScrollBox_Skin.Logic(&msg);
	switch (ScrollBox_Skin.State)
	{
	case EScrollBoxState::ScrollClick:
		BE_ScrollBox_Skin();
		break;
	}

	ScrollBox_Channel.Logic(&msg);
	switch (ScrollBox_Channel.State)
	{
	case EScrollBoxState::ScrollClick:
		BE_ScrollBox_Channel();
		break;
	}

	Button_Copy.Logic(&msg);
	switch (Button_Copy.State)
	{
	case EButtonState::Click:
		BE_Button_Copy();
		break;
	}
}

BIND_EVENT BE_Button_Home()
{
	AddOutputLog("BIND_EVENT BE_Button_Home() Called");
	Menu = EMenu::Home;
	FlushMenu(&Button_Home);
}

BIND_EVENT BE_Button_Basic()
{
	AddOutputLog("BIND_EVENT BE_Button_Basic() Called");
	Menu = EMenu::Basic;
	FlushMenu(&Button_Basic);
}

BIND_EVENT BE_Button_Fake()
{
	AddOutputLog("BIND_EVENT BE_Button_Fake() Called");
	Menu = EMenu::Fake;
	FlushMenu(&Button_Fake);

	std::vector<std::string> data_file_names = GetDataFileNames("./Resource/Data/");
	ScrollBox_Item.ArrayText = data_file_names;
	ScrollBox_Item.StartIndex = 0;
}

BIND_EVENT BE_Button_Game()
{
	AddOutputLog("BIND_EVENT BE_Button_Game() Called");
	Menu = EMenu::Game;
	FlushMenu(&Button_Game);
}

BIND_EVENT BE_Button_Quit()
{
	exit(0);
}

BIND_EVENT BE_Button_Github()
{
	AddOutputLog("BIND_EVENT BE_Button_Github() Called");
	system("start https://github.com/LHY1339/CSHelper");
}

BIND_EVENT BE_Button_KillCS2()
{
	AddOutputLog("BIND_EVENT BE_Button_KillCS2() Called");
	system("taskkill /f /im cs2.exe");
}

BIND_EVENT BE_Button_KillSteam()
{
	AddOutputLog("BIND_EVENT BE_Button_KillSteam() Called");
	system("taskkill /f /im Steam.exe");
}

BIND_EVENT BE_Button_KillWanmei()
{
	AddOutputLog("BIND_EVENT BE_Button_KillWanmei() Called");
	system("taskkill /f /im 完美世界竞技平台.exe");
}

BIND_EVENT BE_Button_KillNet()
{
	AddOutputLog("BIND_EVENT BE_Button_KillNet() Called");
	system("ipconfig /release");
}

BIND_EVENT BE_Button_AutoAccept()
{
	AddOutputLog("BIND_EVENT BE_Button_AutoAccept() Called");
	IsAutoAccept = !IsAutoAccept;
	if (IsAutoAccept)
	{
		Button_AutoAccept.NormalColor = RGB(150, 40, 0);
		Button_AutoAccept.HoverColor = RGB(150, 50, 0);
		Button_AutoAccept.PressColor = RGB(150, 60, 0);
		AddOutputLog("IsAutoAccept true", "LogEvent");
	}
	else
	{
		Button_AutoAccept.NormalColor = RGB(40, 40, 40);
		Button_AutoAccept.HoverColor = RGB(50, 50, 50);
		Button_AutoAccept.PressColor = RGB(60, 60, 60);
		AddOutputLog("IsAutoAccept false", "LogEvent");
	}
}

BIND_EVENT BE_Button_AutoReact()
{
	AddOutputLog("BIND_EVENT BE_Button_AutoReact() Called");
	IsAutoReact = !IsAutoReact;
	if (IsAutoReact)
	{
		Button_AutoReact.NormalColor = RGB(150, 40, 0);
		Button_AutoReact.HoverColor = RGB(150, 50, 0);
		Button_AutoReact.PressColor = RGB(150, 60, 0);
		AddOutputLog("IsAutoReact true", "LogEvent");
	}
	else
	{
		Button_AutoReact.NormalColor = RGB(40, 40, 40);
		Button_AutoReact.HoverColor = RGB(50, 50, 50);
		Button_AutoReact.PressColor = RGB(60, 60, 60);
		AddOutputLog("IsAutoReact false", "LogEvent");
	}
}

BIND_EVENT BE_Button_SetCS2()
{
	AddOutputLog("BIND_EVENT BE_Button_SetCS2() Called");

	std::string steamRegistryKey = "SOFTWARE\\WOW6432Node\\Valve\\Steam";
	std::string valueName = "InstallPath";

	std::string steamPath = ReadRegistryValue(HKEY_LOCAL_MACHINE, steamRegistryKey, valueName);

	if (steamPath.empty()) {
		AddOutputLog("Cant Find Steam Install Path", "LogError");
		return;
	}

	std::string path = steamPath + "/userdata/";
	std::vector<std::string> subfolders = GetDirectories(path);
	for (int i = 0; i < subfolders.size(); i++)
	{
		std::string path = subfolders[i] + "/730/";
		if (CopyFolder("./730", path)) {
			std::string log = path + " ->Folder moved successfully!";
			AddOutputLog(log,"LogEvent");
		}
		else
		{
			std::string log = subfolders[i] + " ->Folder moved faild!";
			AddOutputLog(log, "LogError");
		}
	}
}

BIND_EVENT BE_Button_ClearSet()
{
	AddOutputLog("BIND_EVENT BE_Button_ClearSet() Called");

	int msgboxID = MessageBox(
		NULL,
		"该操作会将你所有在本机登录过的账户的设置清空，其中可能有一些重要数据，你确认执行此操作吗？（云存档不受影响）",
		"确认对话框",
		MB_ICONQUESTION | MB_YESNO
	);

	switch (msgboxID) {
	case IDYES:
		break;
	case IDNO:
		return;
		break;
	}

	std::string steamRegistryKey = "SOFTWARE\\WOW6432Node\\Valve\\Steam";
	std::string valueName = "InstallPath";
	std::string steamPath = ReadRegistryValue(HKEY_LOCAL_MACHINE, steamRegistryKey, valueName);

	if (steamPath.empty()) {
		AddOutputLog("Cant Find Steam Install Path", "LogError");
		return;
	}
	std::string path = steamPath + "\\userdata\\";
	DeleteFilesInDirectory(path);
	std::string log = path + " ->delete[]";
	AddOutputLog(log, "LogError");
}

BIND_EVENT BE_ScrollBox_Item()
{
	AddOutputLog("BIND_EVENT BE_ScrollBox_Item() Called");
	FakeItem = ScrollBox_Item.FocusText;
	FlushFakeText();

	std::vector<std::string> lines = ReadFileLines("./Resource/Data/" + FakeItem + ".data");
	FakeItemCommand = lines[0];
	lines.erase(lines.begin());
	ScrollBox_Skin.ArrayText = lines;
	ScrollBox_Skin.StartIndex = 0;
}

BIND_EVENT BE_ScrollBox_Skin()
{
	AddOutputLog("BIND_EVENT BE_ScrollBox_Skin() Called");
	FakeSkin = ScrollBox_Skin.FocusText;
	FlushFakeText();
}

BIND_EVENT BE_ScrollBox_Channel()
{
	AddOutputLog("BIND_EVENT BE_ScrollBox_Channel() Called");
	FakeChannel = ScrollBox_Channel.FocusText;
	FlushFakeText();
}

BIND_EVENT BE_Button_Copy()
{
	AddOutputLog("BIND_EVENT BE_Button_Copy() Called");

	std::string chan;
	if (FakeChannel=="开箱")
	{
		chan = "从武器箱中获得了：";
	}
	else
	{
		chan = "通过交易获得：";
	}

	std::string target = "playerchatwheel CW.IFixBomb \"" + chan + FakeItemCommand + "| " + FakeSkin + "\"";
	AddOutputLog(target, "LogEvent");
	SetClipboardText(target);
}

void FlushMenu(CButton* Button)
{
	Button_Home.SetNormal();
	Button_Basic.SetNormal();
	Button_Fake.SetNormal();
	Button_Game.SetNormal();
	Button->SetChose(RGB(20, 20, 20));
}

void AddOutputLog(std::string newlog, std::string category)
{
	if (OutputLog.size() > 10)
	{
		OutputLog.erase(OutputLog.begin() + 10);
	}
	newlog = "<" + category + "> " + newlog;
	OutputLog.insert(OutputLog.begin(), newlog);
	std::string output;
	for (int i = 0; i < OutputLog.size(); i++)
	{
		std::string addout = OutputLog[i] + "\n";
		output.append(addout);
	}
	Text_Console.Text = output;
}

std::string GetWindowTitle(HWND hwnd)
{
	if (hwnd != NULL) {
		int length = GetWindowTextLengthA(hwnd);
		if (length > 0) {
			char* windowTitle = new char[length + 1];
			GetWindowTextA(hwnd, windowTitle, length + 1);
			std::string title(windowTitle);
			delete[] windowTitle;
			return title;
		}
	}
}

bool CopyFolder(const std::string src, const std::string dst)
{
	// 创建目标目录（如果不存在）
	if (!CreateDirectoryA(dst.c_str(), NULL)) {
		DWORD err = GetLastError();
		if (err != ERROR_ALREADY_EXISTS) {
			std::cerr << "无法创建目录: " << dst << " 错误代码: " << err << std::endl;
			return false;
		}
	}

	// 构造搜索路径（例如：C:\Parent\*）
	std::string searchPath = src + "\\*";

	WIN32_FIND_DATAA findData;
	HANDLE hFind = FindFirstFileA(searchPath.c_str(), &findData);

	if (hFind == INVALID_HANDLE_VALUE) {
		std::cerr << "无法遍历目录: " << src << " 错误代码: " << GetLastError() << std::endl;
		return false;
	}

	bool success = true;
	do {
		const std::string name = findData.cFileName;
		if (name == "." || name == "..") continue;

		const std::string srcPath = src + "\\" + name;
		const std::string dstPath = dst + "\\" + name;

		// 处理子目录
		if (findData.dwFileAttributes & FILE_ATTRIBUTE_DIRECTORY) {
			if (!CopyFolder(srcPath, dstPath)) {
				success = false;
				break;
			}
		}
		// 处理文件
		else {
			if (!CopyFileA(srcPath.c_str(), dstPath.c_str(), FALSE)) { // FALSE = 覆盖目标文件
				DWORD err = GetLastError();
				std::cerr << "无法复制文件: " << srcPath << " -> " << dstPath
					<< " 错误代码: " << err << std::endl;
				success = false;
				break;
			}
		}
	} while (FindNextFileA(hFind, &findData));

	FindClose(hFind);
	return success;
}

std::vector<std::string> GetDirectories(const std::string path)
{
	std::vector<std::string> directories;
	for (const auto& entry : fs::directory_iterator(path)) {
		if (entry.is_directory()) {
			std::string dirPath = entry.path().string();
			std::replace(dirPath.begin(), dirPath.end(), '\\', '/');
			directories.push_back(dirPath);
		}
	}
	return directories;
}

std::string ReadRegistryValue(HKEY hKeyRoot, std::string subKey, std::string valueName)
{
	HKEY hKey;
	char value[1024];
	DWORD valueLength = sizeof(value);
	DWORD valueType;

	// Open the registry key
	if (RegOpenKeyExA(hKeyRoot, subKey.c_str(), 0, KEY_READ, &hKey) != ERROR_SUCCESS) {
		return ""; // Return empty string if the key cannot be opened
	}

	// Query the value
	if (RegQueryValueExA(hKey, valueName.c_str(), nullptr, &valueType, (LPBYTE)value, &valueLength) == ERROR_SUCCESS) {
		if (valueType == REG_SZ) { // Ensure it's a string value
			RegCloseKey(hKey);
			return std::string(value);
		}
	}

	// Close the registry key and return empty string on failure
	RegCloseKey(hKey);
	return "";
}

void DeleteFilesInDirectory(const std::string directoryPath) {
	try {
		// 检查目录是否存在
		if (!fs::exists(directoryPath) || !fs::is_directory(directoryPath)) {
			std::cerr << "目录不存在或不是一个有效的目录: " << directoryPath << std::endl;
			return;
		}

		// 遍历目录下的所有文件和目录
		for (const auto& entry : fs::directory_iterator(directoryPath)) {
			// 删除文件或子目录
			fs::remove_all(entry); // 如果是文件则删除文件，如果是子目录则递归删除
		}

		std::cout << "已删除目录 " << directoryPath << " 下的所有文件和子目录。" << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "删除文件时出错: " << e.what() << std::endl;
	}
}

void FlushFakeText()
{
	Text_Fake.Text = "物品：" + FakeItem + "\n皮肤：" + FakeSkin + "\n渠道：" + FakeChannel;
}

std::vector<std::string> GetDataFileNames(const std::string directory_path)
{
	std::vector<std::string> data_file_names;

	try {
		for (const auto& entry : fs::directory_iterator(directory_path)) {
			if (entry.is_regular_file() && entry.path().extension() == ".data") {
				data_file_names.push_back(entry.path().stem().string());
			}
		}
	}
	catch (const fs::filesystem_error& e) {
		std::cerr << "Filesystem error: " << e.what() << std::endl;
	}
	catch (const std::exception& e) {
		std::cerr << "Error: " << e.what() << std::endl;
	}

	return data_file_names;
}

std::vector<std::string> ReadFileLines(const std::string file_path)
{
	std::vector<std::string> lines;
	std::ifstream file(file_path);

	if (!file.is_open()) {
		std::cerr << "Error: Could not open file " << file_path << std::endl;
		return lines;
	}

	std::string line;
	while (std::getline(file, line)) {
		lines.push_back(line); // 将每一行添加到数组中
	}

	file.close(); // 关闭文件
	return lines;
}

void SetClipboardText(std::string text)
{
	// 打开剪切板
	if (!OpenClipboard(nullptr)) {
		std::cerr << "Could not open clipboard." << std::endl;
		return;
	}

	// Empty the clipboard
	EmptyClipboard();

	// 创建一个全局字符串
	HGLOBAL hGlobal = GlobalAlloc(GMEM_MOVEABLE, text.size() + 1);
	if (hGlobal == nullptr) {
		std::cerr << "GlobalAlloc failed." << std::endl;
		CloseClipboard();
		return;
	}

	// 将字符串复制到全局内存
	memcpy(GlobalLock(hGlobal), text.c_str(), text.size() + 1);
	GlobalUnlock(hGlobal);

	// 设置剪切板数据
	if (SetClipboardData(CF_TEXT, hGlobal) == nullptr) {
		std::cerr << "SetClipboardData failed." << std::endl;
		GlobalFree(hGlobal);
	}

	// 关闭剪切板
	CloseClipboard();
}

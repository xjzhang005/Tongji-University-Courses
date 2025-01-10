#pragma once
#include "gas.h"
#include "engine.h"
#include "graphics.h"
#include <chrono>
#include <list>
#include <string>
#include <codecvt>

using namespace std;

// 按钮结构体
struct Button {
	int x, y, width, height; // 按钮的位置和大小
	wstring text;       // 按钮上的文字
	bool isPressed = false; // 按钮是否被按下
};

// 文本框结构体
struct TextBox {
	int x, y, width, height; // 文本框的位置和大小
	wstring text;       // 文本框中的文本
	wstring label;      // 文本框标签
	bool focus = false;      // 文本框是否获得焦点
};

// 扇形结构体
struct Sector {
	int x, y, radius; // 扇形的圆心和半径
	double maxValue;  // 最大值
	double value;    // 扇形的值
	wstring text; // 扇形文本
};

// 绘制按钮的函数
void DrawButton(Button& button, COLORREF rgb, int fontSize = 40);
void DrawERRButtonBox(const Button& button, COLORREF rgbBg, COLORREF rgbText, int fontSize = 20);

// 检查鼠标点击是否在按钮区域内
bool IsClickInButton(int mx, int my, Button& button);
// 检查鼠标点击是否在文本框区域内
bool IsClickInTextBox(int mx, int my, TextBox& textbox);

// 绘制输入框的函数
void DrawTextBox(const TextBox& textBox, COLORREF rgbBg, COLORREF rgbText, int fontSize = 20);
void DrawERRTextBox(const TextBox& textBox, COLORREF rgbBg, COLORREF rgbText, int fontSize = 20);

// 绘制扇形的函数
void DrawSector(const Sector& sector, COLORREF rgb, int fontSize = 20);

class Plane {
private:
	Engine leftEng; // 左发动机
	Engine rightEng; // 右发动机
	Gas gas; // 油箱

	PALNESTATUS status; // 状态

	// 绘图相关变量
	Button startButton; // 开始按钮
	Button stopButton;  // 停止按钮
	Button runButton;   // 运行按钮
	Button addForce;   // 加推力按钮
	Button subForce;   // 减推力按钮
	
	TextBox fuelFlowBox; // 燃油流速文本框
	TextBox fuelFlowValueBox; // 燃油流速文本框
	TextBox fuelBox; // 燃油流速文本框
	TextBox fuelValueBox; // 燃油流速文本框
	TextBox messageBox; // 消息本文框

	Sector leftN1; // 左发动机N1扇形
	Sector rightN1; // 右发动机N1扇形
	Sector leftEGT; // 左发动机egt扇形
	Sector rightEGT; // 右发动机egt扇形

	// 各个异常状态的 box
	vector<Button> errButtons;
	/*
	Button leftEngSpeed1Fail;
	Button leftEngSpeed2Fail;
	Button leftEngEGT1Fail;
	Button leftEngEGT2Fail;

	Button rightEngSpeed1Fail;
	Button rightEngSpeed2Fail;
	Button rightEngEGT1Fail;
	Button rightEngEGT2Fail;

	Button fuelLow;
	Button fuelFail;
	Button fuelFlowOver;

	Button leftEngN1Over;
	Button rightEngN1Over;

	Button leftEngTOver;
	Button rightEngTOver;
	*/

	// 告警信息
	struct errMsg {
		long long timeStamp;
		int type;
		wstring text;
		errMsg(const long long& t, int tp, const wstring& txt) {
			timeStamp = t;
			type = tp;
			text = txt;
		}
		bool operator==(const errMsg& em) {
			return text == em.text;
		}
	};
	list<errMsg> errmsgs;

	// 添加警告信息, 同类型 5s 一次
	void AddWarningMsg(const long long& t, int tp, const wstring& txt) {
		errMsg newMsg = { t, tp, txt };
		auto iter = errmsgs.rbegin();
		for (; iter != errmsgs.rend(); ++iter) {
			if (*iter == newMsg) {
				break;
			}
		}
		if (iter != errmsgs.rend()) {
			if (newMsg.timeStamp - iter->timeStamp <= 5000) {
				// 还没到 5s
				return;
			}
		}
		errmsgs.push_back(newMsg);
	}


	ofstream ofs;

	long long systemTime;
	bool exitFlag;
private:
	// 处理鼠标点击事件
	void HandleClikedEvent();
	// 更新状态
	void UpdateState(USEROP userOp);
	// 处理告警事件
	void HandleWarningEvent();
	// 绘图函数
	void Draw();
public:
	Plane();
	~Plane();
	// 开始函数
	void Simulate();

};
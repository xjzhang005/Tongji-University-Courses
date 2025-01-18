#include "plane.h"

using namespace std;

string wstringToString(const wstring& wstr) {
    wstring_convert<codecvt_utf8_utf16<wchar_t>> converter;
    return converter.to_bytes(wstr);
}

// 绘制按钮的函数
void DrawButton(Button& button, COLORREF rgb, int fontSize) {
    setfillcolor(rgb); // 设置填充颜色
    bar(button.x, button.y, button.x + button.width, button.y + button.height); // 绘制矩形
    settextcolor(BLUE); // 设置文字颜色
    setbkmode(TRANSPARENT); // 设置背景模式为透明
    settextstyle(fontSize, 0, L"微软雅黑 bold"); // 设置字体样式和大小
    outtextxy(button.x + (button.width - textwidth(button.text.c_str())) / 2, button.y + (button.height - textheight(button.text.c_str())) / 2, button.text.c_str()); // 绘制文字
}

// 检查鼠标点击是否在按钮区域内
bool IsClickInButton(int mx, int my, Button& button) {
    return mx >= button.x && mx <= button.x + button.width && my >= button.y && my <= button.y + button.height;
}
bool IsClickInTextBox(int mx, int my, TextBox& textbox) {
    return mx >= textbox.x && mx <= textbox.x + textbox.width && my >= textbox.y && my <= textbox.y + textbox.height;
}

// 绘制输入框的函数
void DrawTextBox(const TextBox& textBox, COLORREF rgbBg, COLORREF rgbText, int fontSize) {
    setfillcolor(rgbBg); // 设置填充颜色为白色
    setlinecolor(GREEN); // 设置边框颜色为绿色
    setlinestyle(PS_SOLID, 3); // 设置边框线条粗细
    fillrectangle(textBox.x, textBox.y, textBox.x + textBox.width, textBox.y + textBox.height); // 绘制矩形
    settextcolor(rgbText); // 设置文字颜色为黑色
    setbkmode(TRANSPARENT); // 设置背景模式为透明
    settextstyle(fontSize, 0, L"微软雅黑"); // 设置字体样式和大小
    outtextxy(textBox.x + 5, textBox.y + 9, textBox.text.c_str()); // 绘制文字
}

// 绘制输入框的函数
void DrawERRButtonBox(const Button& button, COLORREF rgbBg, COLORREF rgbText, int fontSize) {
    setfillcolor(rgbBg); // 设置填充颜色
    setlinecolor(BLACK); // 设置边框颜色为黑色
    setlinestyle(PS_SOLID, 1); // 设置边框线条粗细
    fillrectangle(button.x, button.y, button.x + button.width, button.y + button.height); // 绘制矩形
    settextcolor(rgbText); // 设置文字颜色
    setbkmode(TRANSPARENT); // 设置背景模式为透明
    settextstyle(fontSize, 0, L"微软雅黑"); // 设置字体样式和大小
    outtextxy(button.x + 5, button.y + 1, button.text.c_str()); // 绘制文字
}

// 绘制输入框的函数
void DrawERRTextBox(const TextBox& textBox, COLORREF rgbBg, COLORREF rgbText, int fontSize) {
    setfillcolor(rgbBg); // 设置填充颜色为白色
    setlinecolor(BLACK); // 设置边框颜色为黑色
    setlinestyle(PS_SOLID, 1); // 设置边框线条粗细
    fillrectangle(textBox.x, textBox.y, textBox.x + textBox.width, textBox.y + textBox.height); // 绘制矩形
    settextcolor(rgbText); // 设置文字颜色
    setbkmode(TRANSPARENT); // 设置背景模式为透明
    settextstyle(fontSize, 0, L"微软雅黑"); // 设置字体样式和大小
    outtextxy(textBox.x + 5, textBox.y + 1, textBox.text.c_str()); // 绘制文字
}


void DrawSector(const Sector& sector, COLORREF rgb, int fontSize) {
    setfillcolor(rgb);  // 设置填充颜色
    setlinecolor(BLACK);  // 设置线条颜色为黑色
    // 绘制扇形
    double startAngle = 150.0 + 210.0 * (sector.maxValue - sector.value) / sector.maxValue;
    if (startAngle >= 360.0) {
        startAngle = -1.0;
    }
    double endAngle = 0.0;
    fillpie(sector.x - sector.radius, sector.y - sector.radius, sector.x + sector.radius, sector.y + sector.radius, startAngle * 3.14 / 180.0, endAngle * 3.14 / 180.0);
    settextcolor(WHITE); // 设置文字颜色为白色
    setbkmode(TRANSPARENT); // 设置背景模式为透明
    settextstyle(fontSize, 0, L"微软雅黑"); // 设置字体样式和大小
    if (sector.value >= 0.0) {
        outtextxy(sector.x + 10, sector.y - 20, std::to_wstring((int)std::round(sector.value)).c_str()); // 绘制文字
    }
    else {
        outtextxy(sector.x + 10, sector.y - 20, L"--"); // 绘制文字
    }
    
    outtextxy(sector.x -20, sector.y + sector.radius + 10, sector.text.c_str()); // 绘制文字
    setlinecolor(GREEN);  // 设置线条颜色为绿色
    circle(sector.x, sector.y, sector.radius);
}




/*-------------------*/
Plane::Plane(): leftEng("left"), rightEng("right"), gas() {
    status = PALNESTATUS::Stop;
    systemTime = 0;
    exitFlag = false;


    startButton = {50, 400, 100, 50, L"start"};
    runButton = { 200, 400, 100, 50, L"run" };
    stopButton = { 350, 400, 100, 50, L"stop" };

    leftN1 = { 150, 100, 60, 150.0, 0.0, L"leftN1" };
    rightN1 = { 350, 100, 60, 150.0, 0.0, L"rightN1" };
    leftEGT = { 150, 280, 60, 1200.0, 0.0, L"leftEGT" };
    rightEGT = { 350, 280, 60, 1200.0, 0.0, L"rightEGT" };

    addForce = { 550, 50, 200, 50, L"ADD" };
    subForce = { 550, 120, 200, 50, L"SUB" };

    fuelFlowBox = { 550, 190, 200, 50, L"Fuel Flow:"};
    fuelFlowValueBox = { 550, 250, 200, 50, L"" };
    fuelBox = { 550, 320, 200, 50, L"Fuel Value:" };
    fuelValueBox = { 550, 380, 200, 50, L"" };
    messageBox = { 50, 650, 700, 230, L"" };

    // 异常状态 box 的位置
    errButtons = {
        { 50, 480, 120, 20, L"lEngS1Fail"}, // [0]leftEngSpeed1Fail
        { 220, 480, 120, 20, L"lEngS2Fail" }, // [1]leftEngSpeed2Fail
        { 390, 480, 120, 20, L"lEngEGT1Fail" }, // [2]leftEngEGT1Fail
        { 560, 480, 120, 20, L"lEngEGT2Fail" }, // [3]leftEngEGT2Fail

        { 50, 510, 120, 20, L"rEngS1Fail" }, // [4]rightEngSpeed1Fail
        { 220, 510, 120, 20, L"rEngS2Fail" }, // [5]rightEngSpeed2Fail
        { 390, 510, 120, 20, L"rEngEGT1Fail" }, // [6]rightEngEGT1Fail
        { 560, 510, 120, 20, L"rEngEGT2Fail" }, // [7]rightEngEGT2Fail

        { 50, 540, 120, 20, L"lowFuel" }, // [8]fuelLow
        { 220, 540, 120, 20, L"fuelFail" }, // [9]fuelFail
        { 390, 540, 120, 20, L"fuelFlowOver" }, // [10]fuelFlowOver

        { 50, 570, 120, 20, L"lEngN1-warn" }, // [11]leftEngN1-warn
        { 220, 570, 120, 20, L"lEngN1-red" }, // [12]leftEngN1-red
        { 390, 570, 120, 20, L"rEngN1-warn" }, // [13]rightEngN1-warn
        { 560, 570, 120, 20, L"rEngN1-red" }, // [14]rightEngN1-red

        { 50, 600, 120, 20, L"lEngT-warn" },  // [15]leftEngT-warn
        { 220, 600, 120, 20, L"lEngT-red" },  // [16]leftEngT-red
        { 390, 600, 120, 20, L"rEngT-warn" }, // [17]rightEngT-warn
        { 560, 600, 120, 20, L"rEngT-red" }  // [18]rightEngT-red
    };
    /*
    leftEngSpeed1Fail = { 50, 480, 120, 20, L"leftEngS1Fail"};
    leftEngSpeed2Fail = { 220, 480, 120, 20, L"leftEngS2Fail" };
    leftEngEGT1Fail = { 390, 480, 120, 20, L"leftEngEGT1Fail" };
    leftEngEGT2Fail = { 560, 480, 120, 20, L"leftEngEGT2Fail" };

    rightEngSpeed1Fail = { 50, 520, 120, 20, L"rightEngS1Fail" };
    rightEngSpeed2Fail = { 220, 520, 120, 20, L"rightEngS2Fail" };
    rightEngEGT1Fail = { 390, 520, 120, 20, L"rightEngEGT1Fail" };
    rightEngEGT2Fail = { 560, 520, 120, 20, L"rightEngEGT2Fail" };

    fuelLow = { 50, 560, 120, 20, L"lowFuel" };
    fuelFail = { 220, 560, 120, 20, L"fuelFail" };
    fuelFlowOver = { 390, 560, 120, 20, L"fuelFlowOver" };

    leftEngN1Over = { 50, 600, 120, 20, L"leftEngN1Over" };
    rightEngN1Over = { 220, 600, 120, 20, L"rightEngN1Over" };
    leftEngTOver = { 390, 600, 120, 20, L"leftEngTOver" };
    rightEngTOver = { 560, 600, 120, 20, L"rightEngTOver" };
    */
    ofs.open("warnings.log");
}

Plane::~Plane() {
    if (ofs.is_open()) {
        ofs.close();
    }
}

void Plane::HandleClikedEvent() {
    ExMessage msg;
    bool hasClicked = false;

    if (peekmessage(&msg, EX_MOUSE)) {
        hasClicked = true;
    }

    USEROP userOp = USEROP::None;
    if (hasClicked && msg.lbutton) {
        // 左键被按下
        if (status == PALNESTATUS::Stop && IsClickInButton(msg.x, msg.y, startButton)) {
            // 停止状态按下了 start 键
            status = PALNESTATUS::Starting; // 切换状态
            gas.SetStartTime();
            leftEng.SetStartTime();
            rightEng.SetStartTime();
        }
        else if (status == PALNESTATUS::Stable && (IsClickInButton(msg.x, msg.y, addForce) || IsClickInButton(msg.x, msg.y, subForce))) {
            if (IsClickInButton(msg.x, msg.y, addForce)) {
                // 增加推力
                userOp = USEROP::Add;
            }
            else if (IsClickInButton(msg.x, msg.y, subForce)) {
                // 减少推力
                userOp = USEROP::Sub;
            }
        }
        else if ((status == PALNESTATUS::Starting || status == PALNESTATUS::Stable) && IsClickInButton(msg.x, msg.y, stopButton)) {
            // 运行中按下了 stop 键
            leftEng.SetStopTime();
            rightEng.SetStopTime();
            status = PALNESTATUS::Stoping; // 切换状态
        }
        else if (IsClickInButton(msg.x, msg.y, errButtons[0])) {
            // leftEngSpeed1Fail 点击
            // 如已按下再次点击为取消
            leftEng.SetSpeedSensor1InvalidData();
            errButtons[0].isPressed = !errButtons[0].isPressed;
        }
        else if (IsClickInButton(msg.x, msg.y, errButtons[1])) {
            // leftEngSpeed2Fail 点击
            // 如已按下再次点击为取消
            leftEng.SetSpeedSensor2InvalidData();
            errButtons[1].isPressed = !errButtons[1].isPressed;
        }
        else if (IsClickInButton(msg.x, msg.y, errButtons[2])) {
            // leftEngEGT1Fail 点击
            // 如已按下再次点击为取消
            leftEng.SetEGTSensor1InvalidData();
            errButtons[2].isPressed = !errButtons[2].isPressed;
        }
        else if (IsClickInButton(msg.x, msg.y, errButtons[3])) {
            // leftEngEGT2Fail 点击
            // 如已按下再次点击为取消
            leftEng.SetEGTSensor2InvalidData();
            errButtons[3].isPressed = !errButtons[3].isPressed;
        }
        else if (IsClickInButton(msg.x, msg.y, errButtons[4])) {
            // rightEngSpeed1Fail 点击
            // 如已按下再次点击为取消
            rightEng.SetSpeedSensor1InvalidData();
            errButtons[4].isPressed = !errButtons[4].isPressed;
        }
        else if (IsClickInButton(msg.x, msg.y, errButtons[5])) {
            // rightEngSpeed2Fail 点击
            // 如已按下再次点击为取消
            rightEng.SetSpeedSensor2InvalidData();
            errButtons[5].isPressed = !errButtons[5].isPressed;
        }
        else if (IsClickInButton(msg.x, msg.y, errButtons[6])) {
            // rightEngEGT1Fail 点击
            // 如已按下再次点击为取消
            rightEng.SetEGTSensor1InvalidData();
            errButtons[6].isPressed = !errButtons[6].isPressed;
        }
        else if (IsClickInButton(msg.x, msg.y, errButtons[7])) {
            // rightEngEGT2Fail 点击
            // 如已按下再次点击为取消
            rightEng.SetEGTSensor2InvalidData();
            errButtons[7].isPressed = !errButtons[7].isPressed;
        }
        else if (IsClickInButton(msg.x, msg.y, errButtons[8])) {
            // fuelLow 点击
            // 如已按下再次点击为取消
            if (!errButtons[8].isPressed) {
                gas.SetErrDataC(900.0);
            }
            else {
                gas.SetErrDataC(-1.0);
            }
            errButtons[8].isPressed = !errButtons[8].isPressed;
        }
        else if (IsClickInButton(msg.x, msg.y, errButtons[9])) {
            // fuelFail 点击
            // 如已按下再次点击为取消
            gas.SetInvalidDataC();
            errButtons[9].isPressed = !errButtons[9].isPressed;
        }
        else if (IsClickInButton(msg.x, msg.y, errButtons[10])) {
            // fuelFlowOver 点击
            // 如已按下再次点击为取消
            if (!errButtons[10].isPressed) {
                gas.SetErrDataV(55);
            }
            else {
                gas.SetErrDataV(-1.0);
            }
            errButtons[10].isPressed = !errButtons[10].isPressed;
        }
        else if (IsClickInButton(msg.x, msg.y, errButtons[11])) {
            // leftEngN1-warn 点击
            // 如已按下再次点击为取消
            if (!errButtons[11].isPressed) {
                leftEng.SetSpeedSensor1ErrData(1.08 * 40000.0);
                leftEng.SetSpeedSensor2ErrData(1.08 * 40000.0);

                errButtons[12].isPressed = false; // 互斥
            }
            else {
                leftEng.SetSpeedSensor1ErrData(-1.0);
                leftEng.SetSpeedSensor2ErrData(-1.0);
            }
            errButtons[11].isPressed = !errButtons[11].isPressed;
        }
        else if (IsClickInButton(msg.x, msg.y, errButtons[12])) {
            // leftEngN1-red 点击
            // 如已按下再次点击为取消
            if (!errButtons[12].isPressed) {
                leftEng.SetSpeedSensor1ErrData(1.23 * 40000.0);
                leftEng.SetSpeedSensor2ErrData(1.23 * 40000.0);
                errButtons[11].isPressed = false; // 互斥
            }
            else {
                leftEng.SetSpeedSensor1ErrData(-1.0);
                leftEng.SetSpeedSensor2ErrData(-1.0);
            }
            errButtons[12].isPressed = !errButtons[12].isPressed;
        }
        else if (IsClickInButton(msg.x, msg.y, errButtons[13])) {
            // rightEngN1-warn 点击
            // 如已按下再次点击为取消
            if (!errButtons[13].isPressed) {
                rightEng.SetSpeedSensor1ErrData(1.08 * 40000.0);
                rightEng.SetSpeedSensor2ErrData(1.08 * 40000.0);
                errButtons[14].isPressed = false; // 互斥
            }
            else {
                rightEng.SetSpeedSensor1ErrData(-1.0);
                rightEng.SetSpeedSensor2ErrData(-1.0);
            }
            errButtons[13].isPressed = !errButtons[13].isPressed;
        }
        else if (IsClickInButton(msg.x, msg.y, errButtons[14])) {
            // rightEngN1-red 点击
            // 如已按下再次点击为取消
            if (!errButtons[14].isPressed) {
                rightEng.SetSpeedSensor1ErrData(1.23 * 40000.0);
                rightEng.SetSpeedSensor2ErrData(1.23 * 40000.0);
                errButtons[13].isPressed = false; // 互斥
            }
            else {
                rightEng.SetSpeedSensor1ErrData(-1.0);
                rightEng.SetSpeedSensor2ErrData(-1.0);
            }
            errButtons[14].isPressed = !errButtons[14].isPressed;
        }
        else if (IsClickInButton(msg.x, msg.y, errButtons[15])) {
            // leftEngT-warn 点击
            // 如已按下再次点击为取消
            if (!errButtons[15].isPressed) {
                leftEng.SetEGTSensor1ErrData(960.0);
                leftEng.SetEGTSensor2ErrData(960.0);
                errButtons[16].isPressed = false; // 互斥
            }
            else {
                leftEng.SetEGTSensor1ErrData(-1.0);
                leftEng.SetEGTSensor2ErrData(-1.0);
            }
            errButtons[15].isPressed = !errButtons[15].isPressed;
        }
        else if (IsClickInButton(msg.x, msg.y, errButtons[16])) {
            // leftEngT-red 点击
            // 如已按下再次点击为取消
            if (!errButtons[16].isPressed) {
                leftEng.SetEGTSensor1ErrData(1150.0);
                leftEng.SetEGTSensor2ErrData(1150.0);
                errButtons[15].isPressed = false; // 互斥
            }
            else {
                leftEng.SetEGTSensor1ErrData(-1.0);
                leftEng.SetEGTSensor2ErrData(-1.0);
            }
            errButtons[16].isPressed = !errButtons[16].isPressed;
        }
        else if (IsClickInButton(msg.x, msg.y, errButtons[17])) {
            // rightEngT-warn 点击
            // 如已按下再次点击为取消
            if (!errButtons[17].isPressed) {
                rightEng.SetEGTSensor1ErrData(960.0);
                rightEng.SetEGTSensor2ErrData(960.0);
                errButtons[18].isPressed = false; // 互斥
            }
            else {
                rightEng.SetEGTSensor1ErrData(-1.0);
                rightEng.SetEGTSensor2ErrData(-1.0);
            }
            errButtons[17].isPressed = !errButtons[17].isPressed;
        }
        else if (IsClickInButton(msg.x, msg.y, errButtons[18])) {
            // rightEngT-red 点击
            // 如已按下再次点击为取消
            if (!errButtons[18].isPressed) {
                rightEng.SetEGTSensor1ErrData(1150.0);
                rightEng.SetEGTSensor2ErrData(1150.0);
                errButtons[17].isPressed = false; // 互斥
            }
            else {
                rightEng.SetEGTSensor1ErrData(-1.0);
                rightEng.SetEGTSensor2ErrData(-1.0);
            }
            errButtons[18].isPressed = !errButtons[18].isPressed;
        }
    }
    else if (hasClicked && msg.rbutton) {
        exitFlag = true;
    }
    UpdateState(userOp);
}

void Plane::UpdateState(USEROP userOp) {
    switch (status)
    {
    case Stop:
    {
        DrawButton(startButton, WHITE);
        DrawButton(stopButton, WHITE);
        DrawButton(runButton, WHITE);
        gas.UpdateStop(5);
        leftEng.UpdateStop(5);
        rightEng.UpdateStop(5);
    } break;
    case Starting:
    {
        DrawButton(startButton, RED); // start亮起
        DrawButton(stopButton, WHITE);
        DrawButton(runButton, WHITE);

        // 更新
        gas.UpdateStarting(5);
        bool flag = leftEng.UpdateStarting(5);
        flag = rightEng.UpdateStarting(5) || flag;
        //std::cout << "starting..: " << systemTime << std::endl;
        if (flag) {
            // 结束启动阶段
            status = PALNESTATUS::Stable;
            // 设置稳态值
            leftEng.SetStableN(leftEng.GetN());
            rightEng.SetStableN(rightEng.GetN());
            leftEng.SetStableT(leftEng.GetT());
            rightEng.SetStableT(rightEng.GetT());
            gas.SetStableV(gas.GetV());
        }

    } break;
    case Stable:
    {
        DrawButton(startButton, WHITE);
        DrawButton(stopButton, WHITE);
        
        // 更新
        gas.UpdateStable(5, userOp);
        leftEng.UpdateStable(5, userOp);
        rightEng.UpdateStable(5, userOp);
        //std::cout << "Stable..: " << systemTime << std::endl;
        if (std::round(leftEng.GetN1()) < 95.0 && std::round(rightEng.GetN1()) < 95.0) {
            DrawButton(runButton, WHITE); // run变暗
        }
        else {
            DrawButton(runButton, RED); // run亮起
        }
    } break;
    case Stoping:
    {
        DrawButton(startButton, WHITE);
        DrawButton(stopButton, RED);  // stop亮起
        DrawButton(runButton, WHITE);
        // 更新
        gas.UpdateStoping(5);
        bool flag = leftEng.UpdateStoping(5);
        flag = rightEng.UpdateStoping(5) || flag;
        //std::cout << "Stoping..: " << systemTime << std::endl;

        if (flag) {
            status = PALNESTATUS::Stop;
        }
    }
    break;
    default:
        break;
    }

    // 获取值
    if (leftEng.GetSpeedSensorStatus() == TwoLose) {
        leftN1.value = -1.0;
    }
    else {
        leftN1.value = leftEng.GetN1();
    }
    if (leftEng.GetEGTSensorStatus() == TwoLose) {
        leftEGT.value = -1.0;
    }
    else {
        leftEGT.value = leftEng.GetT();
    }

    if (rightEng.GetSpeedSensorStatus() == TwoLose) {
        rightN1.value = -1.0;
    }
    else {
        rightN1.value = rightEng.GetN1();
    }
    if (rightEng.GetEGTSensorStatus() == TwoLose) {
        rightEGT.value = -1.0;
    }
    else {
        rightEGT.value = rightEng.GetT();
    }
    
    fuelFlowValueBox.text = std::to_wstring((int)gas.GetV());
    fuelValueBox.text = std::to_wstring((int)gas.GetC());
}

void Plane::HandleWarningEvent() {
    // 发动机转速故障告警
    SENSOR_STATUS leftEngSpeed = leftEng.GetSpeedSensorStatus();
    SENSOR_STATUS rightEngSpeed = rightEng.GetSpeedSensorStatus();
    if (leftEngSpeed == TwoLose && rightEngSpeed == TwoLose) {
        AddWarningMsg(systemTime, 2, L"All speed fail");
        if (status != Stoping && status != Stop) {
            status = PALNESTATUS::Stoping; // 切换状态
        }
    }
    else {
        if (leftEngSpeed == TwoLose) {
            AddWarningMsg(systemTime, 1, L"leftEng all speed fail");
        }
        else if (leftEngSpeed == One1Lose) {
            AddWarningMsg(systemTime, 0, L"leftEng speed1 fail");
        }
        else if (leftEngSpeed == One2Lose) {
            AddWarningMsg(systemTime, 0, L"leftEng speed2 fail");
        }

        if (rightEngSpeed == TwoLose) {
            AddWarningMsg(systemTime, 1, L"rightEng all speed fail");
        }
        else if (rightEngSpeed == One1Lose) {
            AddWarningMsg(systemTime, 0, L"rightEng speed1 fail");
        }
        else if (rightEngSpeed == One2Lose) {
            AddWarningMsg(systemTime, 0, L"rightEng speed2 fail");
        }
    }

    // egt传感器故障告警
    SENSOR_STATUS leftEngEGT = leftEng.GetEGTSensorStatus();
    SENSOR_STATUS rightEngEGT= rightEng.GetEGTSensorStatus();
    if (leftEngEGT == TwoLose && rightEngEGT == TwoLose) {
        AddWarningMsg(systemTime, 2, L"All egt fail");
        if (status != Stoping && status != Stop) {
            status = PALNESTATUS::Stoping; // 切换状态
        }
    }
    else {
        if (leftEngEGT == TwoLose) {
            AddWarningMsg(systemTime, 1, L"leftEng all egt fail");
        }
        else if (leftEngEGT == One1Lose) {
            AddWarningMsg(systemTime, 0, L"leftEng egt1 fail");
        }
        else if (leftEngEGT == One2Lose) {
            AddWarningMsg(systemTime, 0, L"leftEng egt2 fail");
        }

        if (rightEngEGT == TwoLose) {
            AddWarningMsg(systemTime, 1, L"rightEng all egt fail");
        }
        else if (rightEngEGT == One1Lose) {
            AddWarningMsg(systemTime, 0, L"rightEng egt1 fail");
        }
        else if (rightEngEGT == One2Lose) {
            AddWarningMsg(systemTime, 0, L"rightEng egt2 fail");
        }
    }

    // 燃油异常告警
    if (gas.GetCValueERR(status) == REDERR) {
        AddWarningMsg(systemTime, 2, L"fuel stock fail");
    }
    else if (gas.GetCValueERR(status) == HUPOERR) {
        AddWarningMsg(systemTime, 1, L"fuel stock low warning");
    }
    
    if (gas.GetVValueERR() == HUPOERR) {
        AddWarningMsg(systemTime, 1, L"fuel flow over warning");
    }

    // 转速异常告警
    if (leftEng.GetSpeedValueERR() == HUPOERR) {
        AddWarningMsg(systemTime, 1, L"leftEng speed over warning");
    }
    else if (leftEng.GetSpeedValueERR() == REDERR) {
        AddWarningMsg(systemTime, 2, L"leftEng speed over error");
        if (status != Stoping && status != Stop) {
            status = PALNESTATUS::Stoping; // 切换状态
        }
    }
    if (rightEng.GetSpeedValueERR() == HUPOERR) {
        AddWarningMsg(systemTime, 1, L"rightEng speed over warning");
    }
    else if (rightEng.GetSpeedValueERR() == REDERR) {
        AddWarningMsg(systemTime, 2, L"rightEng speed over error");
        if (status != Stoping && status != Stop) {
            status = PALNESTATUS::Stoping; // 切换状态
        }
    }

    // 温度异常告警
    if (leftEng.GetTValueERR(status) == HUPOERR) {
        AddWarningMsg(systemTime, 1, L"leftEng T over warning");
    }
    else if (leftEng.GetTValueERR(status) == REDERR) {
        AddWarningMsg(systemTime, 1, L"leftEng T over error");
        if (status != Stoping && status != Stop) {
            status = PALNESTATUS::Stoping; // 切换状态
        }
    }
    if (rightEng.GetTValueERR(status) == HUPOERR) {
        AddWarningMsg(systemTime, 1, L"rightEng T over warning");
    }
    else if (rightEng.GetTValueERR(status) == REDERR) {
        AddWarningMsg(systemTime, 1, L"rightEng T over error");
        if (status != Stoping && status != Stop) {
            status = PALNESTATUS::Stoping; // 切换状态
        }
    }
}

void Plane::Draw() {
    // 异常生成按钮 
    for (int i = 0; i < errButtons.size(); i++) {
        if (errButtons[i].isPressed) {
            DrawERRButtonBox(errButtons[i], RED, WHITE);
        }
        else {
            DrawERRButtonBox(errButtons[i], DARKGRAY, WHITE);
        }
    }

    // 加减力按钮
    DrawButton(addForce, DARKGRAY);
    DrawButton(subForce, DARKGRAY);

    // 燃油流速显示
    DrawTextBox(fuelFlowBox, LIGHTGRAY, WHITE, 40);
    if (gas.GetVValueERR() == HUPOERR) {
        DrawTextBox(fuelFlowValueBox, WHITE, HUPOCOLOR, 40);
    }
    else {
        DrawTextBox(fuelFlowValueBox, WHITE, BLACK, 40);
    }
    // 燃油余量显示
    DrawTextBox(fuelBox, LIGHTGRAY, WHITE, 40);
    if (gas.GetCValueERR(status) == REDERR) {
        fuelValueBox.text = L"--";
        DrawTextBox(fuelValueBox, WHITE, RED, 40);
    }
    else if (gas.GetCValueERR(status) == HUPOERR) {
        DrawTextBox(fuelValueBox, WHITE, HUPOCOLOR, 40);
    }
    else {
        DrawTextBox(fuelValueBox, WHITE, BLACK, 40);
    }

    // 仪表显示 
    // 转速表
    if (leftEng.GetSpeedValueERR() == REDERR) {
        DrawSector(leftN1, RED, 20);
    }
    else if (leftEng.GetSpeedValueERR() == HUPOERR) {
        DrawSector(leftN1, HUPOCOLOR, 20);
    }
    else {
        DrawSector(leftN1, WHITE, 20);
    }
    if (rightEng.GetSpeedValueERR() == REDERR) {
        DrawSector(rightN1, RED, 20);
    }
    else if (rightEng.GetSpeedValueERR() == HUPOERR) {
        DrawSector(rightN1, HUPOCOLOR, 20);
    }
    else {
        DrawSector(rightN1, WHITE, 20);
    }
    // 温度表
    if (leftEng.GetTValueERR(status) == REDERR) {
        DrawSector(leftEGT, RED, 20);
    }
    else if (leftEng.GetTValueERR(status) == HUPOERR) {
        DrawSector(leftEGT, HUPOCOLOR, 20);
    }
    else {
        DrawSector(leftEGT, WHITE, 20);
    }
    if (rightEng.GetTValueERR(status) == REDERR) {
        DrawSector(rightEGT, RED, 20);
    }
    else if (rightEng.GetTValueERR(status) == HUPOERR) {
        DrawSector(rightEGT, HUPOCOLOR, 20);
    }
    else {
        DrawSector(rightEGT, WHITE, 20);
    }
}

void Plane::Simulate() {
	initgraph(800, 900);
	cleardevice();
    setbkcolor(BLACK);
    settextstyle(40, 0, L"Gill Sans");
    flushmessage();
    
    while (true) {
        systemTime += 5;
        
        BeginBatchDraw();
        cleardevice();
        // 处理鼠标事件
        HandleClikedEvent();
        // 处理告警事件
        HandleWarningEvent();
        // 画图
        Draw();
        // 告警消息框
        DrawTextBox(messageBox, BLACK, BLACK);
        int idx = 0;
        int arrY[10] = {652, 672, 692, 712, 732, 752, 772, 792, 812, 832 };
        for (auto iter = errmsgs.begin(); iter != errmsgs.end(); ) {
            if (systemTime - iter->timeStamp >= 5000) {
                // 5s不再显示
                ofs << iter->timeStamp << " " << iter->type << " " << wstringToString(iter->text).c_str() << std::endl;
                iter = errmsgs.erase(iter);
            }
            else {
                TextBox tb = { 55, arrY[idx], 400, 20, std::to_wstring(iter->timeStamp) + L", " + iter->text};
                if (iter->type == 0) {
                    DrawERRTextBox(tb, BLACK, WHITE, 20);
                }
                else if (iter->type == 1) {
                    DrawERRTextBox(tb, BLACK, HUPOCOLOR, 20);
                }
                else {
                    DrawERRTextBox(tb, BLACK, RED, 20);
                }
                idx++;
                iter++;
                if (idx >= 10) {
                    break;
                }
            }
        }
        
        Sleep(5);
        FlushBatchDraw();

        if (exitFlag) {
            break;
        }
    }
    EndBatchDraw();
    closegraph();
}
#undef UNICODE
#include <graphics.h>
#include <cmath>
#include <iostream>
#include <fstream>
#include <thread>
#include <chrono>
#include <conio.h>
#include <string>
#include <random>
#include <vector>
#include <ctime>
#define PI 3.1415926//���峣������Բ����ΪPI

using namespace std;

double maxC = 20000;
double maxV = 50;
double maxN = 40000;
double maxN1 = 125;
double maxT = 1200;
double minT = -5;
double originT = 20;
bool isRunning = false;  // �����Ƿ�������
bool isStable = false;   // �Ƿ�����̬
double savetime = 0;
double currenttime = 0;
bool hasmark = false;
double stop_n = 0;
double stop_t = 0;
double stoptime = 0;
double real_t = 0;
double real_t1 = 0;
bool Stop = true;
bool isStarting = false;
bool isStopping = false;
bool stable_slow = false;
bool stable_fast = false;
bool hasBegun = false;
int selectEngine = 0;
int refreshCounter = 0;
bool s_oh1 = false;
bool s_oh2 = false;

enum AlarmColor {
	W,		 // ����ֵ����ɫ
	R,       // ����ֵ����ɫ
	A,       // ����ֵ������ɫ
};

enum AlarmCode {
	// �������쳣
	SENSOR_FAULT_N1_SINGLE_L,
	SENSOR_FAULT_N1_SINGLE_R,
	SENSOR_FAULT_N1_ENGINE1,
	SENSOR_FAULT_N1_ENGINE2,
	SENSOR_FAULT_EGT_SINGLE_L,
	SENSOR_FAULT_EGT_SINGLE_R,
	SENSOR_FAULT_EGT_ENGINE1,
	SENSOR_FAULT_EGT_ENGINE2,
	SENSOR_FAULT_CRITICAL,

	// ȼ���쳣
	FUEL_WARNING_LOW,
	FUEL_SENSOR_FAULT,
	FUEL_FLOW_WARNING,

	// ת���쳣
	RPM_OVERSPEED_105,
	RPM_OVERSPEED_CRITICAL,

	// �¶��쳣
	EGT_OVERSTART_850,
	EGT_OVERSTART_CRITICAL,
	EGT_OVERSTEADY_950,
	EGT_OVERSTEADY_CRITICAL
};

struct Alarm {
	double startTime;    // �澯��ʼʱ��
	AlarmCode message;   // �澯����
	AlarmColor color;    // �澯��ɫ
};

vector<Alarm> alarms;

ofstream LogFile("engine_data.csv", ios::app);

int getColorCode(AlarmColor color) {
	switch (color) {
	case W: return RGB(255, 255, 255); // ��ɫ
	case A: return RGB(255, 191, 0);  // ����ɫ
	case R: return RGB(255, 0, 0);      // ��ɫ
	default: return RGB(255, 255, 255);   // Ĭ�ϰ�ɫ
	}
}

// ���ݸ澯���뷵�ظ澯��Ϣ
string getAlarmMessage(AlarmCode code) {
	switch (code) {
		// �������쳣
	case SENSOR_FAULT_N1_SINGLE_L:
		return "N1 Sensor Fault: RPM sensor 1 failure. System operating normally.";
	case SENSOR_FAULT_N1_SINGLE_R:
		return "N1 Sensor Fault: RPM sensor 2 failure. System operating normally.";
	case SENSOR_FAULT_N1_ENGINE1:
		return "N1 Sensor Fault: RPM sensor 1 failed on Engine. Monitor N1 status.";
	case SENSOR_FAULT_N1_ENGINE2:
		return "N1 Sensor Fault: RPM sensor 2 failed on Engine. Monitor N1 status.";
	case SENSOR_FAULT_EGT_SINGLE_L:
		return "EGT Sensor Fault: EGT sensor 1 failure. System operating normally.";
	case SENSOR_FAULT_EGT_SINGLE_R:
		return "EGT Sensor Fault: EGT sensor 2 failure. System operating normally.";
	case SENSOR_FAULT_EGT_ENGINE1:
		return "EGT Sensor Fault: EGT sensor 1 failed on Engine. Monitor EGT status.";
	case SENSOR_FAULT_EGT_ENGINE2:
		return "EGT Sensor Fault: EGT sensor 2 failed on Engine. Monitor EGT status.";
	case SENSOR_FAULT_CRITICAL:
		return "Critical Sensor Fault: RPM/EGT sensor failures on both engines. Engine shutdown initiated.";

		// ȼ���쳣
	case FUEL_WARNING_LOW:
		return "Fuel Warning: Remaining fuel below 1000 units. Monitor fuel level.";
	case FUEL_SENSOR_FAULT:
		return "Fuel Sensor Fault: Invalid fuel quantity reading. Immediate attention required.";
	case FUEL_FLOW_WARNING:
		return "Fuel Flow Warning: Fuel flow exceeds 50 units/second. Check for system anomalies.";

		// ת���쳣
	case RPM_OVERSPEED_105:
		return "RPM Overspeed: N1 > 105%. Reduce engine power.";
	case RPM_OVERSPEED_CRITICAL:
		return "Critical RPM Overspeed: N1 > 120%. Engine shutdown initiated.";

		// �¶��쳣
	case EGT_OVERSTART_850:
		return "EGT Overtemperature: EGT > 850��C during start. Monitor engine status.";
	case EGT_OVERSTART_CRITICAL:
		return "Critical EGT Overtemperature: EGT > 1000��C during start. Engine shutdown initiated.";
	case EGT_OVERSTEADY_950:
		return "EGT Overtemperature: EGT > 950��C in steady state. Monitor engine status.";
	case EGT_OVERSTEADY_CRITICAL:
		return "Critical EGT Overtemperature: EGT > 1100��C in steady state. Engine shutdown initiated.";

	default:
		return "Unknown Alarm Code.";
	}
}



double c = 20000;
double v = 0;
double n = 0;
double n1 = 0;
double t = 20;

void drawUI() {
	line(600, 0, 600, 800);

	setbkmode(TRANSPARENT); // ���ñ���Ϊ͸��
	pie(50, 0, 200, 150, 5 * PI / 6, 0);
	pie(250, 0, 400, 150, 5 * PI / 6, 0);
	settextstyle(20, 0, "Arial");
	outtextxy(220, 170, "N1");

	pie(50, 150, 200, 300, 5 * PI / 6, 0);
	pie(250, 150, 400, 300, 5 * PI / 6, 0);
	settextstyle(20, 0, "Arial");
	outtextxy(215, 320, "EGT");

	rectangle(425, 240, 585, 285);
	settextstyle(30, 0, "Arial");
	outtextxy(450, 250, "Fuel Flow:");
	fillrectangle(425, 300, 585, 345);

	rectangle(30, 365, 170, 415);
	setfillcolor(RGB(128, 128, 128));
	fillroundrect(230, 365, 370, 415, 10, 10);
	fillroundrect(430, 365, 570, 415, 10, 10);
	settextstyle(40, 0, "Arial");
	outtextxy(260, 370, "Start");
	outtextxy(465, 370, "Stop");

	rectangle(125, 45, 200, 75);
	rectangle(325, 45, 400, 75);
	rectangle(125, 195, 200, 225);
	rectangle(325, 195, 400, 225);

	setfillcolor(RGB(173, 216, 230));
	POINT pts_up[] = { {500, 110}, {570, 110}, {535, 50} };
	fillpolygon(pts_up, 3);
	POINT pts_down[] = { {500, 130}, {570, 130}, {535, 190} };
	fillpolygon(pts_down, 3);
	setfillcolor(RGB(128, 128, 128));

	roundrect(30, 435, 570, 785, 20, 20);

	rectangle(445, 30, 470, 185);
	settextstyle(20, 0, "Arial");
	outtextxy(452, 200, "C");

	settextstyle(40, 0, "Arial");
	outtextxy(622, 20, "Simulation");
	setfillcolor(RGB(128, 128, 128));
	for (int i = 0; i < 16; i++) {
		fillroundrect(620, 80 + 44 * i, 780, 115 + 44 * i, 5, 5);
	}
	settextstyle(30, 0, "Arial");
	outtextxy(650, 85, "N1_SF_L");
	outtextxy(650, 129, "N1_SF_R");
	outtextxy(640, 173, "EGT_SF_L");
	outtextxy(640, 217, "EGT_SF_R");
	outtextxy(650, 261, "S_EF_L");
	outtextxy(650, 305, "S_EF_R");
	outtextxy(650, 349, "SEN_CF");
	outtextxy(640, 393, "FUEL_LW");
	outtextxy(640, 437, "FUEL_SF");
	outtextxy(640, 481, "FUEL_FW");
	outtextxy(630, 525, "RPM_O105");
	outtextxy(650, 569, "RPM_OC");
	outtextxy(630, 613, "EGT_OS85");
	outtextxy(650, 657, "EGT_OC");
	outtextxy(630, 701, "EGT_SS95");
	outtextxy(650, 745, "EGT_SC");
}

void drawData(vector<Alarm>& alarms) {
	static double randomValue1 = 0.0; // ���浱ǰ���ֵ
	static double randomValue2 = 0.0;
	static double randomValue3 = 0.0;
	static double randomValue4 = 0.0;
	static double randomValue5 = 0.0;

	char text1[50];
	char text2[50];
	char text3[50];
	char text4[50];
	char text5[50];

	// �趨�����ˢ��Ƶ�ʣ�ÿ0.1�루20��5msˢ�£�
	const int REFRESH_INTERVAL = 20;

	// ÿ��ˢ�����Ӽ�����
	refreshCounter++;
	if (refreshCounter >= REFRESH_INTERVAL) {
		// ʹ��C++11 <random>�����µ������
		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<double> dist(-0.03, 0.03);

		randomValue1 = dist(gen);
		randomValue2 = dist(gen);
		randomValue3 = dist(gen);
		randomValue4 = dist(gen);
		randomValue5 = dist(gen);

		refreshCounter = 0; // ���ü�����
	}

	// ������ʾ����
	sprintf_s(text1, "%.2f", n1 * (1 + randomValue1));
	sprintf_s(text2, "%.2f", n1 * (1 + randomValue2));
	sprintf_s(text3, "%.2f", t * (1 + randomValue3));
	sprintf_s(text4, "%.2f", t * (1 + randomValue4));
	sprintf_s(text5, "%.2f", v * (1 + randomValue5));
	setbkmode(TRANSPARENT);
	settextstyle(20, 0, "Arial");

	double angle = -(n1 / 125) * 7 * PI / 6;
	if (fabs(angle) < 0.01) { // ��ֹ�Ƕȹ�С
		angle = -0.01; // ��һ����С���ӻ��Ƕ�
	}

	if (std::any_of(alarms.begin(), alarms.end(), [](const Alarm& alarm) {
		return alarm.message == SENSOR_FAULT_N1_SINGLE_L || alarm.message == SENSOR_FAULT_N1_ENGINE1 || alarm.message == SENSOR_FAULT_CRITICAL;
		})) {
		settextcolor(WHITE);
		setfillcolor(RGB(128, 128, 128));
		outtextxy(135, 50, "---");
	}
	else if (std::any_of(alarms.begin(), alarms.end(), [](const Alarm& alarm) {
		return alarm.message == RPM_OVERSPEED_CRITICAL;
		})) {
		settextcolor(RGB(255, 0, 0));
		setfillcolor(RGB(255, 0, 0));
		outtextxy(135, 50, text1);
		fillpie(50, 0, 200, 150, angle, 0);
		settextcolor(WHITE);
		setfillcolor(RGB(128, 128, 128));
	}
	else if (std::any_of(alarms.begin(), alarms.end(), [](const Alarm& alarm) {
		return alarm.message == RPM_OVERSPEED_105;
		})) {
		settextcolor(RGB(255, 191, 0));
		setfillcolor(RGB(255, 191, 0));
		outtextxy(135, 50, text1);
		fillpie(50, 0, 200, 150, angle, 0);
		settextcolor(WHITE);
		setfillcolor(RGB(128, 128, 128));
	}
	else {
		settextcolor(WHITE);
		setfillcolor(RGB(128, 128, 128));
		outtextxy(135, 50, text1);
		fillpie(50, 0, 200, 150, angle, 0);
	}

	if (std::any_of(alarms.begin(), alarms.end(), [](const Alarm& alarm) {
		return alarm.message == SENSOR_FAULT_N1_SINGLE_R || alarm.message == SENSOR_FAULT_N1_ENGINE2 || alarm.message == SENSOR_FAULT_CRITICAL;
		})) {
		settextcolor(WHITE);
		setfillcolor(RGB(128, 128, 128));
		outtextxy(335, 50, "---");
	}
	else if (std::any_of(alarms.begin(), alarms.end(), [](const Alarm& alarm) {
		return alarm.message == RPM_OVERSPEED_CRITICAL;
		})) {
		settextcolor(RGB(255, 0, 0));
		setfillcolor(RGB(255, 0, 0));
		outtextxy(335, 50, text2);
		fillpie(250, 0, 400, 150, angle, 0);
		settextcolor(WHITE);
		setfillcolor(RGB(128, 128, 128));
	}
	else if (std::any_of(alarms.begin(), alarms.end(), [](const Alarm& alarm) {
		return alarm.message == RPM_OVERSPEED_105;
		})) {
		settextcolor(RGB(255, 191, 0));
		setfillcolor(RGB(255, 191, 0));
		outtextxy(335, 50, text2);
		fillpie(250, 0, 400, 150, angle, 0);
		settextcolor(WHITE);
		setfillcolor(RGB(128, 128, 128));
	}
	else {
		setfillcolor(WHITE);
		setfillcolor(RGB(128, 128, 128));
		outtextxy(335, 50, text2);
		fillpie(250, 0, 400, 150, angle, 0);
	}

	if (std::any_of(alarms.begin(), alarms.end(), [](const Alarm& alarm) {
		return alarm.message == SENSOR_FAULT_EGT_SINGLE_L || alarm.message == SENSOR_FAULT_EGT_ENGINE1 || alarm.message == SENSOR_FAULT_CRITICAL;
		})) {
		settextcolor(WHITE);
		setfillcolor(RGB(128, 128, 128));
		outtextxy(135, 200, "---");
	}
	else if (std::any_of(alarms.begin(), alarms.end(), [](const Alarm& alarm) {
		return alarm.message == EGT_OVERSTART_CRITICAL || alarm.message == EGT_OVERSTEADY_CRITICAL;
		})) {
		settextcolor(RGB(255, 0, 0));
		setfillcolor(RGB(255, 0, 0));
		outtextxy(135, 200, text3);
		fillpie(50, 150, 200, 300, -((t + 5) / 1205) * 7 * PI / 6, 0);
		settextcolor(WHITE);
		setfillcolor(RGB(128, 128, 128));
	}
	else if (std::any_of(alarms.begin(), alarms.end(), [](const Alarm& alarm) {
		return alarm.message == EGT_OVERSTART_850 || alarm.message == EGT_OVERSTEADY_950;
		})) {
		settextcolor(RGB(255, 191, 0));
		setfillcolor(RGB(255, 191, 0));
		outtextxy(135, 200, text3);
		fillpie(50, 150, 200, 300, -((t + 5) / 1205) * 7 * PI / 6, 0);
		settextcolor(WHITE);
		setfillcolor(RGB(128, 128, 128));
	}
	else {
		settextcolor(WHITE);
		setfillcolor(RGB(128, 128, 128));
		outtextxy(135, 200, text3);
		fillpie(50, 150, 200, 300, -((t + 5) / 1205) * 7 * PI / 6, 0);
	}

	if (std::any_of(alarms.begin(), alarms.end(), [](const Alarm& alarm) {
		return alarm.message == SENSOR_FAULT_EGT_SINGLE_R || alarm.message == SENSOR_FAULT_EGT_ENGINE2 || alarm.message == SENSOR_FAULT_CRITICAL;
		})) {
		settextcolor(WHITE);
		setfillcolor(RGB(128, 128, 128));
		outtextxy(335, 200, "---");
	}
	else if (std::any_of(alarms.begin(), alarms.end(), [](const Alarm& alarm) {
		return alarm.message == EGT_OVERSTART_CRITICAL || alarm.message == EGT_OVERSTEADY_CRITICAL;
		})) {
		settextcolor(RGB(255, 0, 0));
		setfillcolor(RGB(255, 0, 0));
		outtextxy(335, 200, text4);
		fillpie(250, 150, 400, 300, -((t + 5) / 1205) * 7 * PI / 6, 0);
		settextcolor(WHITE);
		setfillcolor(RGB(128, 128, 128));
	}
	else if (std::any_of(alarms.begin(), alarms.end(), [](const Alarm& alarm) {
		return alarm.message == EGT_OVERSTART_850 || alarm.message == EGT_OVERSTEADY_950;
		})) {
		settextcolor(RGB(255, 191, 0));
		setfillcolor(RGB(255, 191, 0));
		outtextxy(335, 200, text4);
		fillpie(250, 150, 400, 300, -((t + 5) / 1205) * 7 * PI / 6, 0);
		settextcolor(WHITE);
		setfillcolor(RGB(128, 128, 128));
	}
	else {
		setfillcolor(WHITE);
		setfillcolor(RGB(128, 128, 128));
		outtextxy(335, 200, text4);
		fillpie(250, 150, 400, 300, -((t + 5) / 1205) * 7 * PI / 6, 0);
	}

	if (std::any_of(alarms.begin(), alarms.end(), [](const Alarm& alarm) {
		return alarm.message == FUEL_SENSOR_FAULT;
		})) {
		settextcolor(WHITE);
		setfillcolor(RGB(128, 128, 128));
		settextstyle(30, 0, "Arial");
		outtextxy(445, 307.5, "---");
	}
	else if (std::any_of(alarms.begin(), alarms.end(), [](const Alarm& alarm) {
		return alarm.message == FUEL_WARNING_LOW;
		})) {
		settextstyle(30, 0, "Arial");
		settextcolor(RGB(255, 0, 0));
		setfillcolor(RGB(255, 0, 0));
		outtextxy(445, 307.5, text5);
		fillrectangle(445, 185 - (c / 20000) * 155, 470, 185);
		settextcolor(WHITE);
		setfillcolor(RGB(128, 128, 128));

	}
	else {
		settextcolor(WHITE);
		settextstyle(30, 0, "Arial");
		outtextxy(470, 308, text5);
		fillrectangle(445, 185 - (c / 20000) * 155, 470, 185);
	}

	if (!Stop) {
		if (isStable) {
			settextcolor(WHITE);
			settextstyle(40, 0, "Arial");
			outtextxy(70, 370, "Run");
		}
		if (!isStable) {
			settextcolor(WHITE);
			settextstyle(40, 0, "Arial");
			outtextxy(65, 370, "Start");
		}
	}
	pie(50, 0, 200, 150, -7 * PI / 6, 0);
	pie(250, 0, 400, 150, -7 * PI / 6, 0);
	pie(50, 150, 200, 300, -7 * PI / 6, 0);
	pie(250, 150, 400, 300, -7 * PI / 6, 0);

}

void startEngine() {
	hasBegun = true;
	isRunning = true;
	isStable = false;
	if (isRunning == true && n1 < 95) {
		if (real_t <= 2) {
			n += 10000 * 0.005;
			n1 = n * 100 / maxN;
			v += 5 * 0.005;
			c -= v * 0.005;
		}
		else {
			n = 23000 * log10(real_t - 1) + 20000;
			n1 = n * 100 / maxN;
			v = 42 * log10(real_t - 1) + 10;
			c -= v * 0.005;
			t = 900 * log10(real_t1 - 1) + 20;
		}
	}
	LogFile << real_t << "," << n1 << "," << t << "," << c << "," << v << endl;
	if (n1 >= 95) {
		isStable = true;
		isStarting = false;
	}
	if (c <= 0) {
		isStopping = true;
	}
}

void stopEngine() {
	if (hasmark == false) {
		stop_n = n;
		stop_t = t;
		stoptime = real_t;
		hasmark = true;
	}
	if (hasmark == true) {
		isStable = false;
		if (isRunning == true) {
			v = 0;
			n = stop_n * pow(0.4, real_t - stoptime);
			n1 = n * 100 / maxN;
			t = (stop_t - 20) * pow(0.5, real_t - stoptime);
		}
		if (n1 <= 0.01) {
			isRunning = false;
			n = 0;
			n1 = 0;
			Stop = true;
		}
		if ((t - 20) <= 0.01) {
			t = 20;
		}
	}
	LogFile << currenttime << "," << n1 << "," << t << "," << c << "," << v << endl;
}

void stableEngine() {
	if (n1 <= 0.01) {
		isRunning = false;
		n = 0;
		n1 = 0;
		Stop = true;
	}
	if ((t - 20) <= 0.01) {
		t = 20;
	}
	if (v <= 0.01) {
		v = 0;
		isStable = false;
		isStopping = true;
	}
	if (n1 >= 95) {
		stable_slow = false;
		stable_fast = true;
	}
	if (n1 < 95) {
		stable_slow = true;
		stable_fast = false;
	}
	if (c <= 0) {
		isStopping = true;
	}
	LogFile << currenttime << "," << n1 << "," << t << "," << c << "," << v << endl;
}

void addAlarm(vector<Alarm>& alarms, AlarmCode code, AlarmColor color) {
	// ����Ƿ�������ͬ�澯
	for (const auto& alarm : alarms) {
		if (alarm.message == code && alarm.color == color) {
			return; // ���ظ����
		}
	}

	// ����¸澯
	Alarm alarm;
	alarm.startTime = currenttime;
	alarm.message = code;
	alarm.color = color;
	alarms.push_back(alarm);

	// ��ʱ�򿪸澯��־�ļ���д��
	ofstream alarmFile("alarm.txt", ios::app); // ���ļ���׷��ģʽ
	if (alarmFile.is_open()) {
		alarmFile << "Time=" << currenttime << "  " << getAlarmMessage(code) << endl;
		alarmFile.close(); // д�������ر�
	}
}

void removeExpiredAlarms(vector<Alarm>& alarms) {
	for (auto it = alarms.begin(); it != alarms.end(); ) {
		// ʹ��ȫ�ֱ��� currenttime ������澯�Ƿ񳬹� 5 ��
		if (difftime(currenttime, it->startTime) > 5) {
			// ɾ�����ڵĸ澯
			it = alarms.erase(it);
		}
		else {
			++it;
		}
	}
}

void printAlarms(vector<Alarm>& alarms) {

	int y = 455;
	for (const auto& alarm : alarms) {
		settextstyle(15.5, 0, "Arial");
		settextcolor(getColorCode(alarm.color));
		outtextxy(50, y, getAlarmMessage(alarm.message).c_str());
		y += 22;
	}
}

void detectAlarm(vector<Alarm>& alarms) {
	if (selectEngine == 1) {
		if (std::none_of(alarms.begin(), alarms.end(), [](const Alarm& a) { return a.message == SENSOR_FAULT_N1_ENGINE1 || a.message == SENSOR_FAULT_CRITICAL; })) {
			addAlarm(alarms, SENSOR_FAULT_N1_SINGLE_L, W);
		}
	}
	if (selectEngine == 2) {
		if (std::none_of(alarms.begin(), alarms.end(), [](const Alarm& a) { return a.message == SENSOR_FAULT_N1_ENGINE2 || a.message == SENSOR_FAULT_CRITICAL; })) {
			addAlarm(alarms, SENSOR_FAULT_N1_SINGLE_R, W);

		}
	}
	if (selectEngine == 3) {
		if (std::none_of(alarms.begin(), alarms.end(), [](const Alarm& a) { return a.message == SENSOR_FAULT_EGT_ENGINE1 || a.message == SENSOR_FAULT_CRITICAL; })) {
			addAlarm(alarms, SENSOR_FAULT_EGT_SINGLE_L, W);
		}
	}
	if (selectEngine == 4) {
		if (std::none_of(alarms.begin(), alarms.end(), [](const Alarm& a) { return a.message == SENSOR_FAULT_EGT_ENGINE2 || a.message == SENSOR_FAULT_CRITICAL; })) {
			addAlarm(alarms, SENSOR_FAULT_EGT_SINGLE_R, W);
		}
	}

	if (selectEngine == 5 || selectEngine == 6 || selectEngine == 7) {
		if (std::none_of(alarms.begin(), alarms.end(), [](const Alarm& a) { return a.message == SENSOR_FAULT_CRITICAL; })) {
			if (selectEngine == 5) {
				addAlarm(alarms, SENSOR_FAULT_EGT_ENGINE1, A);
				addAlarm(alarms, SENSOR_FAULT_N1_ENGINE1, A);
				for (auto it = alarms.begin(); it != alarms.end(); ) {
					if (it->message == SENSOR_FAULT_N1_SINGLE_L || it->message == SENSOR_FAULT_EGT_SINGLE_L) {
						it = alarms.erase(it);
					}
					else {
						++it;
					}
				}
			}
			if (selectEngine == 6) {
				addAlarm(alarms, SENSOR_FAULT_EGT_ENGINE2, A);
				addAlarm(alarms, SENSOR_FAULT_N1_ENGINE2, A);
				for (auto it = alarms.begin(); it != alarms.end(); ) {
					if (it->message == SENSOR_FAULT_N1_SINGLE_R || it->message == SENSOR_FAULT_EGT_SINGLE_R) {
						it = alarms.erase(it);
					}
					else {
						++it;
					}
				}
			}
		}
		if (selectEngine == 7) {
			addAlarm(alarms, SENSOR_FAULT_CRITICAL, R);
			isStopping = true;
			for (auto it = alarms.begin(); it != alarms.end(); ) {
				if (it->message == SENSOR_FAULT_N1_SINGLE_L
					|| it->message == SENSOR_FAULT_N1_SINGLE_R
					|| it->message == SENSOR_FAULT_EGT_SINGLE_L
					|| it->message == SENSOR_FAULT_EGT_SINGLE_L
					|| it->message == SENSOR_FAULT_EGT_SINGLE_R
					|| it->message == SENSOR_FAULT_EGT_ENGINE1
					|| it->message == SENSOR_FAULT_N1_ENGINE1
					|| it->message == SENSOR_FAULT_EGT_ENGINE2
					|| it->message == SENSOR_FAULT_N1_ENGINE2) {
					it = alarms.erase(it);
				}
				else {
					++it;
				}
			}
		}
	}

	if (Stop == false && isStopping == false && c < 1000) {
		addAlarm(alarms, FUEL_WARNING_LOW, A);
	}
	if (selectEngine == 8) {
		addAlarm(alarms, FUEL_SENSOR_FAULT, R);
	}
	if (v > 50) {
		addAlarm(alarms, FUEL_FLOW_WARNING, A);
	}

	if (n1 > 105) {
		// ֻ�е��ߵȼ�����û�г���ʱ����ӵͼ�����
		if (std::none_of(alarms.begin(), alarms.end(), [](const Alarm& a) { return a.message == RPM_OVERSPEED_CRITICAL; })) {
			addAlarm(alarms, RPM_OVERSPEED_105, A);
		}
	}
	if (n1 > 120) {
		addAlarm(alarms, RPM_OVERSPEED_CRITICAL, R);
		isStopping = true;
		for (auto it = alarms.begin(); it != alarms.end(); ) {
			if (it->message == RPM_OVERSPEED_105) {
				it = alarms.erase(it);
			}
			else {
				++it;
			}
		}
	}

	if (isStarting == true && t > 850) {
		// ֻ�е��ߵȼ�����û�г���ʱ����ӵͼ�����
		if (std::none_of(alarms.begin(), alarms.end(), [](const Alarm& a) { return a.message == EGT_OVERSTART_CRITICAL; })) {
			addAlarm(alarms, EGT_OVERSTART_850, A);
		}
	}
	if (isStarting == true && t > 1000) {
		addAlarm(alarms, EGT_OVERSTART_CRITICAL, R);
		isStopping = true;
		for (auto it = alarms.begin(); it != alarms.end(); ) {
			if (it->message == EGT_OVERSTART_850) {
				it = alarms.erase(it);
			}
			else {
				++it;
			}
		}
	}

	if (isStable == true && t > 950) {
		// ֻ�е��ߵȼ�����û�г���ʱ����ӵͼ�����
		if (std::none_of(alarms.begin(), alarms.end(), [](const Alarm& a) { return a.message == EGT_OVERSTEADY_CRITICAL; })) {
			addAlarm(alarms, EGT_OVERSTEADY_950, A);
		}
	}
	if (isStable == true && t > 1100) {
		addAlarm(alarms, EGT_OVERSTEADY_CRITICAL, R);
		isStable = false;
		isStopping = true;
		for (auto it = alarms.begin(); it != alarms.end(); ) {
			if (it->message == EGT_OVERSTEADY_950) {
				it = alarms.erase(it);
			}
			else {
				++it;
			}
		}
	}
}

void initialize() {
	// �������б���Ϊ��ʼֵ
	maxC = 20000;
	maxV = 50;
	maxN = 40000;
	maxN1 = 125;
	maxT = 1200;
	minT = -5;
	originT = 20;
	isRunning = false;
	isStable = false;
	savetime = 0;
	currenttime = 0;
	hasmark = false;
	stop_n = 0;
	stop_t = 0;
	stoptime = 0;
	real_t = 0;
	real_t1 = 0;
	Stop = true;
	isStarting = false;
	isStopping = false;
	stable_slow = false;
	stable_fast = false;
	hasBegun = false;
	selectEngine = 0;
	refreshCounter = 0;
	s_oh1 = false;
	s_oh2 = false;
	alarms.clear();
}


int main()
{
	LogFile << "Time,N1,EGT,Fuel,FuelFlow" << endl;

	initgraph(800, 800);

	// ����˫����
	BeginBatchDraw();

	RECT startButton = { 230, 365, 370, 415 };
	RECT stopButton = { 430, 365, 570, 415 };
	RECT upButton = { 500, 50, 570, 110 };
	RECT downButton = { 500, 130, 570, 190 };

	while (true) {
		cleardevice();  // ����
		drawUI();       // ����UI

		std::random_device rd;
		std::mt19937 gen(rd());
		std::uniform_real_distribution<> dis(0.03, 0.05);

		if (MouseHit()) {
			MOUSEMSG msg = GetMouseMsg();
			if (msg.uMsg == WM_LBUTTONDOWN) {
				if (msg.x >= startButton.left && msg.x <= startButton.right && msg.y >= startButton.top && msg.y <= startButton.bottom && (Stop == true || stable_slow == true)) {
					if (stable_slow == true) {
						isStable = false;
						if (n >= 20000) {
							real_t = pow(10, (n - 20000) / 23000.0) + 1;
						}
						if (n < 20000) {
							real_t = n / 10000;
						}
						real_t1 = pow(10, (t - 20) / 900.0) + 1;
					}
					Stop = false;
					isStarting = true;
					isStopping = false;
				}
				if (msg.x >= stopButton.left && msg.x <= stopButton.right && msg.y >= stopButton.top && msg.y <= stopButton.bottom && Stop == false) {
					isStopping = true;
					isStarting = false;
				}
				if (isStable == true) {
					if (msg.x >= upButton.left && msg.x <= upButton.right && msg.y >= upButton.top && msg.y <= upButton.bottom && v <= maxV && n1 <= maxN1 && t <= maxT) {
						v = v + 1;
						n = n * (1 + dis(gen));
						n1 = n * 100 / maxN;
						t = (t - 20) * (1 + dis(gen)) + 20;
					}
					if (msg.x >= downButton.left && msg.x <= downButton.right && msg.y >= downButton.top && msg.y <= downButton.bottom && v > 0) {
						v = v - 1;
						n = n * (1 - dis(gen));
						n1 = n * 100 / maxN;
						t = (t - 20) * (1 - dis(gen)) + 20;
					}
				}
				if (msg.x >= 620 && msg.x <= 780 && msg.y >= 80 && msg.y <= 115) {
					selectEngine = 1;
				}
				if (msg.x >= 620 && msg.x <= 780 && msg.y >= 124 && msg.y <= 159) {
					selectEngine = 2;
				}
				if (msg.x >= 620 && msg.x <= 780 && msg.y >= 168 && msg.y <= 203) {
					selectEngine = 3;
				}
				if (msg.x >= 620 && msg.x <= 780 && msg.y >= 212 && msg.y <= 247) {
					selectEngine = 4;
				}
				if (msg.x >= 620 && msg.x <= 780 && msg.y >= 256 && msg.y <= 291) {
					selectEngine = 5;
				}
				if (msg.x >= 620 && msg.x <= 780 && msg.y >= 300 && msg.y <= 335) {
					selectEngine = 6;
				}
				if (msg.x >= 620 && msg.x <= 780 && msg.y >= 344 && msg.y <= 379) {
					selectEngine = 7;
				}
				if (msg.x >= 620 && msg.x <= 780 && msg.y >= 388 && msg.y <= 423) {
					c = 999;
				}
				if (msg.x >= 620 && msg.x <= 780 && msg.y >= 432 && msg.y <= 467) {
					selectEngine = 8;
				}
				if (msg.x >= 620 && msg.x <= 780 && msg.y >= 476 && msg.y <= 511) {
					initialize();
					v = 51;
					isStarting = true;
					isRunning == true;
					Stop = false;
				}
				if (msg.x >= 620 && msg.x <= 780 && msg.y >= 520 && msg.y <= 555) {
					initialize();
					n = 42001;
					n1 = n * 100 / maxN;
					real_t = pow(10, (n - 20000) / 23000.0) + 1;
					t = 200;
					real_t1 = pow(10, (200 - 20) / 900.0) + 1;
					v = 30;
					isRunning == true;
					isStarting = true;
					Stop = false;
				}
				if (msg.x >= 620 && msg.x <= 780 && msg.y >= 564 && msg.y <= 599) {
					initialize();
					n = 50001;
					n1 = n * 100 / maxN;
					real_t = pow(10, (n - 20000) / 23000.0) + 1;
					isRunning == true;
					isStarting = true;
					Stop = false;
				}
				if (msg.x >= 620 && msg.x <= 780 && msg.y >= 608 && msg.y <= 643) {
					initialize();
					real_t = 3;
					real_t1 = pow(10, (860 - 20) / 900.0) + 1;
					isRunning == true;
					isStarting = true;
					Stop = false;
				}
				if (msg.x >= 620 && msg.x <= 780 && msg.y >= 652 && msg.y <= 687) {
					initialize();
					real_t = 4;
					real_t1 = pow(10, (1050 - 20) / 900.0) + 1;
					isRunning == true;
					isStarting = true;
					Stop = false;
				}
				if (msg.x >= 620 && msg.x <= 780 && msg.y >= 696 && msg.y <= 731) {
					initialize();
					t = 951;  // ����950��C������EGT_OVERSTEADY_950
					n = 40000;
					v = 30;
					n1 = n * 100 / maxN;
					real_t = pow(10, (n - 20000) / 23000.0) + 1;
					real_t1 = pow(10, (t - 20) / 900.0) + 1;
					isRunning = true;
					isStable = true;
					Stop = false;

					// ���EGT_OVERSTEADY_950����
					addAlarm(alarms, EGT_OVERSTEADY_950, A);
				}

				if (msg.x >= 620 && msg.x <= 780 && msg.y >= 740 && msg.y <= 775) {
					initialize();
					hasBegun = true;
					t = 1101; // ģ���¶ȳ��� 1100 ���ٽ�ֵ
					n = 40000;
					v = 30;
					n1 = n * 100 / maxN;
					real_t = pow(10, (n - 20000) / 23000.0) + 1;
					real_t1 = pow(10, (t - 20) / 900.0) + 1;
					isStable = false;  // ����Ϊ����̬
					isStopping = true; // ȷ������ֹͣ����
					isRunning = true;  // �����Դ�������״̬
					Stop = false;      // ����δ��ȫֹͣ
					// ��������
					addAlarm(alarms, EGT_OVERSTEADY_CRITICAL, R);
				}


			}
		}

		detectAlarm(alarms);
		removeExpiredAlarms(alarms);
		printAlarms(alarms);
		drawData(alarms); // ��������
		settextcolor(WHITE);


		if (isStarting) {
			startEngine();
		}
		if (isStopping) {
			stopEngine();
		}
		if (isStable) {
			stableEngine();
		}

		if (hasBegun) {
			real_t += 0.005;
			real_t1 += 0.005;
		}
		if (Stop) {
			real_t = 0;
			real_t1 = 0;
		}

		currenttime += 0.005;
		FlushBatchDraw(); // ˢ�»���������Ļ
		refreshCounter++;
		selectEngine = 0;
		Sleep(5); // �ӳ٣�ģ��ʱ������
	}

	EndBatchDraw(); // ����˫����ģʽ
	LogFile.close();
	closegraph();

	return 0;
}

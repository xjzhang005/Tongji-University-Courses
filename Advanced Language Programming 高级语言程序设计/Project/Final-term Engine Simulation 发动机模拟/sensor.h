#pragma once
#include <vector>
#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include "mydefine.h"

using namespace std;

// 传感器定义

// 写数据函数
void WriteDataToFile(const vector<pair<double, double>>& data, const string& filename);

// 用户操作枚举
enum USEROP {
	None,	// 无操作
	Add,	// 增加推力
	Sub		// 减少推力
};

// 传感器状态枚举
enum SENSOR_STATUS {
	NormalSENSOR,	// 正常
	One1Lose,		// 单发的一个传感器失效
	One2Lose,		// 单发的两个传感器失效
	TwoLose			// 双发传感器失效
};

// 数值异常
enum VALUE_ERR {
	NormalVALUE,
	HUPOERR,		// 琥珀色异常
	REDERR			// 红色异常
};

// 飞机状态
enum PALNESTATUS
{
	Stop,
	Starting,
	Stable,
	Stoping
};

// 转速传感器
class RotSpeedSensor {
private:
	double N; // 转速
	double errN; // 异常值
	double invalidN; // 无效值
	double stableN; // 稳态转速(用作波动基准)
	double stopTime; // 停止时间戳
	double startTime; // 启动时间戳
	vector<pair<double, double>> historyN; // 转速记录
	int timeStamp;
	const double ratedSpeed;
	const string filename;


public:
	RotSpeedSensor(const string& fname);
	~RotSpeedSensor();

	// 设置稳态转速
	void SetStableN(double sn) {
		stableN = sn;
	}
	// 设置传感器停止的时间戳
	void SetStopTime() {
		double dTime = static_cast<double>(timeStamp) / 1000.0;
		stopTime = dTime;
	}
	// 设置传感器启动的时间戳
	void SetStartTime() {
		double dTime = static_cast<double>(timeStamp) / 1000.0;
		startTime = dTime;
	}
	// 获取稳态转速
	double GetStableN() const {
		return stableN;
	}
	// 获取当前转速
	double GetN() const {
		return N;
	}
	// 设置异常值
	void SetErrData(double errData) {
		errN = errData;
	}
	// 获取异常值
	double GetErrData() const {
		return errN;
	}
	// 设置无效值
	void SetInvalidData() {
		invalidN = invalidN > 0.0 ? -1.0 : 1.0;
	}
	// 获取无效值
	double GetInvalidData() const {
		return invalidN;
	}

	// 启动阶段更新
	bool UpdateStarting(int dt);
	// 稳定阶段更新
	void UpdateStable(int dt, USEROP op);
	// 停车阶段更新
	bool UpdateStoping(int dt);
	// 未启动阶段更新
	void UpdateStop(int dt);

	// 数据写入函数
	void WriteData();
};


// EGT 传感器, 检测温度
class EGTSensor {
private:
	double T; // 温度
	double errT; // 异常值
	double invalidT; // 无效值
	double stableT; // 稳态温度
	double stopTime; // 停止时间戳
	double startTime; // 开始时间戳
	vector<pair<double, double>> historyT; // 温度记录
	int timeStamp;
	const string filename;
public:
	EGTSensor(const string& fname);
	~EGTSensor();

	double GetT() const {
		return T;
	}
	double GetStableT() const {
		return stableT;
	}
	void SetStableT(double st) {
		stableT = st;
	}
	void SetStopTime() {
		double dTime = static_cast<double>(timeStamp) / 1000.0;
		stopTime = dTime;
	}
	void SetStartTime() {
		double dTime = static_cast<double>(timeStamp) / 1000.0;
		startTime = dTime;
	}
	void SetErrData(double errData) {
		errT = errData;
	}
	double GetErrData() const {
		return errT;
	}
	void SetInvalidData() {
		invalidT = invalidT > 0.0 ? -1.0 : 1.0;
	}
	double GetInvalidData() const {
		return invalidT;
	}

	bool UpdateStarting(int dt);
	void UpdateStable(int dt, USEROP op);
	bool UpdateStoping(int dt);
	void UpdateStop(int dt);
	
	void WriteData();
};


// 燃油传感器
class GasSensor {
private:
	double C; // 燃油剩余量
	double errC; // 异常值
	double invalidC; // 无效值
	vector<pair<double, double>> historyC; // 燃油剩余量记录
	double V; // 燃油流速
	double errV; // 异常值
	double stableV; // 稳态流速
	vector<pair<double, double>> historyV; // 燃油流速记录
	int timeStamp;
	double startTime;
	const string filenameC;
	const string filenameV;

public:
	GasSensor(const string& fnameC, const string& fnameV);
	~GasSensor();
	
	double GetV() const {
		return V;
	}
	double GetC() const {
		return C;
	}
	double GetStableV() const {
		return stableV;
	}
	void SetStartTime() {
		double dTime = static_cast<double>(timeStamp) / 1000.0;
		startTime = dTime;
	}

	void SetStableV(double sv) {
		stableV = sv;
	}
	void SetErrDataC(double errData) {
		errC = errData;
	}
	double GetErrDataC() const {
		return errC;
	}
	void SetInvalidDataC() {
		invalidC = invalidC > 0.0 ? -1.0 : 1.0;
	}
	double GetInvalidDataC() const {
		return invalidC;
	}
	void SetErrDataV(double errData) {
		errV = errData;
	}
	double GetErrDataV() const {
		return errV;
	}

	bool UpdateStarting(int dt);
	void UpdateStable(int dt, USEROP op);
	bool UpdateStoping(int dt);
	void UpdateStop(int dt);


	void WriteData();
};
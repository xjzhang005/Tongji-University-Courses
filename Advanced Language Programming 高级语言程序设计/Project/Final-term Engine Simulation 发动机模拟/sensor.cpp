#include "sensor.h"

using namespace std;

// 写数据函数
void WriteDataToFile(const vector<pair<double, double>>& data, const string& filename) {
	ofstream ofs(filename, ios::app); // 往后添加的方式
	if (!ofs.is_open()) {
		cerr << filename << "file not open." << endl;
		return;
	}

	for (auto& item : data) {
		ofs << item.first << "," << item.second << endl;
	}

	ofs.close();
}


/* 转速传感器 */
RotSpeedSensor::RotSpeedSensor(const string& fname): ratedSpeed(40000.0), filename(fname) {
	N = 0.0;
	timeStamp = 0;
	stableN = 0.0;
	stopTime = 0.0;
	startTime = 0.0;
	errN = -1.0;
	invalidN = -1.0;
	// 打开一下文件, 清空作用
	ofstream ofs(filename);
	if (ofs.is_open()) {
		ofs.close();
	}
}
RotSpeedSensor::~RotSpeedSensor() {
	WriteDataToFile(historyN, filename);
}

bool RotSpeedSensor::UpdateStarting(int dt) {
	timeStamp += dt;
	double dTime = static_cast<double>(timeStamp) / 1000.0;
	// +-5
	double noise = (static_cast<double>(rand() % 100) - 50.0) / 100.0 * 10.0;
	if (dTime - startTime <= 2.0) {
		// 启动前两秒线性增加 10000/s
		N = (dTime - startTime) * 10000 +  noise;
	}
	else {
		// 两秒后对数增加
		N = 23000.0 * log10(dTime - startTime - 1.0) + 20000.0 + noise;
	}

	
	if (invalidN > 0.0) {
		// 无效值
		historyN.emplace_back(dTime, 0.0);
	}
	else if (errN >= 0.0) {
		// 异常值
		historyN.emplace_back(dTime, errN);
	}
	else {
		historyN.emplace_back(dTime, N);
	}

	WriteData();
	if (errN < 0.0 && invalidN < 0.0 && N > ratedSpeed * 0.95) {
		// 启动阶段结束
		SetStableN(N);
		return true;
	}

	return false;
}

// 达到1000条的时候写一次
void RotSpeedSensor::WriteData() {
	if (historyN.size() > 1000) {
		WriteDataToFile(historyN, filename);
		historyN.clear();
	}
}

void RotSpeedSensor::UpdateStable(int dt, USEROP op) {
	timeStamp += dt;
	double dTime = static_cast<double>(timeStamp) / 1000.0;
	switch (op)
	{
	case None:
	{
		// 用户无操作, +-3% 随机波动
		//double percent = (static_cast<double>(rand() % 7) - 3.0) / 100.0;
		double percent = 0.0;
		N = stableN * (1.0 + percent);
	}break;
	case Add:
	{
		// 用户加推力, 3-5% 随机波动
		double percent = (static_cast<double>(rand() % 3) + 3.0) / 100.0;
		N = stableN * (1.0 + percent);
		if (errN > 0.0) {
			errN = errN * (1.0 + percent);
		}
		SetStableN(N); // 注意更新稳态值
	} break;
	case Sub:
	{
		// 用户减推力, 3-5% 随机波动
		double percent = (static_cast<double>(rand() % 3) + 3.0) / 100.0;
		N = stableN * (1.0 - percent);
		if (errN > 0.0) {
			errN = errN * (1.0 - percent);
		}
		SetStableN(N); // 注意更新稳态值
	} break;
	default:
		break;
	}

	if (invalidN > 0.0) {
		// 无效值
		historyN.emplace_back(dTime, 0.0);
	}
	else if (errN >= 0.0) {
		// 异常值
		historyN.emplace_back(dTime, errN);
	}
	else {
		historyN.emplace_back(dTime, N);
	}
	WriteData();
}

bool RotSpeedSensor::UpdateStoping(int dt) {
	timeStamp += dt;
	double dTime = static_cast<double>(timeStamp) / 1000.0;
	// 以底数函数递减
	
	N = N + 5000.0 * (log(dTime - stopTime + 1.0) / log(0.35));
	if (N <= 0.0) {
		N = 0.0;
	}
	if (errN > 0.0) {
		errN = errN + 5000.0 * (log(dTime - stopTime + 1.0) / log(0.35));
		if (errN <= 0.0) {
			errN = 0.0;
		}
	}

	if (invalidN > 0.0 ) {
		// 无效值
		historyN.emplace_back(dTime, 0.0);
		if (N == 0.0) {
			return true;
		}
	}
	else if (errN >= 0.0) {
		// 异常值
		historyN.emplace_back(dTime, errN);
		WriteData();
		if (errN == 0.0) {
			return true;
		}
	}
	else {
		historyN.emplace_back(dTime, N);
		WriteData();
		if (N == 0.0) {
			return true;
		}
	}

	WriteData();
	return false;
}

void RotSpeedSensor::UpdateStop(int dt) {
	timeStamp += dt;
	double dTime = static_cast<double>(timeStamp) / 1000.0;
	N = 0.0;
	if (errN > 0.0) {
		errN = 0.0;
	}
	historyN.emplace_back(dTime, N);
	WriteData();
}


/* EGT 传感器 */
EGTSensor::EGTSensor(const std::string& fname): filename(fname) {
	T = 20.0;
	timeStamp = 0;
	stableT = 0.0;
	stopTime = 0.0;
	startTime = 0.0;
	errT = -1.0;
	invalidT = -1.0;
	// 打开一下文件, 清空作用
	ofstream ofs(filename);
	if (ofs.is_open()) {
		ofs.close();
	}
}

EGTSensor::~EGTSensor() {
	WriteDataToFile(historyT, filename);
}

bool EGTSensor::UpdateStarting(int dt) {
	timeStamp += dt;
	double dTime = static_cast<double>(timeStamp) / 1000.0;
	// +-1
	double noise = (static_cast<double>(rand() % 100) - 50.0) / 100.0 * 2.0;
	if (dTime - startTime <= 2.0) {
		// 前2秒温度不变化
		T = std::max(20.0 + noise, T);
	}
	else {
		// 两秒后对数增加
		T = std::max(900.0 * log10(dTime - startTime - 1.0) + 20.0 + noise, T);
	}

	if (invalidT > 0.0) {
		// 无效值
		historyT.emplace_back(dTime, 0.0);
	}
	else if (errT >= 0.0) {
		// 异常值
		historyT.emplace_back(dTime, errT);
	}
	else {
		historyT.emplace_back(dTime, T);
	}
	
	WriteData();
	return false;
}

// 达到1000条的时候写一次
void EGTSensor::WriteData() {
	if (historyT.size() > 1000) {
		WriteDataToFile(historyT, filename);
		historyT.clear();
	}
}

void EGTSensor::UpdateStable(int dt, USEROP op) {
	timeStamp += dt;
	double dTime = static_cast<double>(timeStamp) / 1000.0;
	switch (op)
	{
	case None:
	{
		// 用户无操作, +-3% 随机波动
		//double percent = (static_cast<double>(rand() % 7) - 3.0) / 100.0;
		double percent = 0.0;
		T = stableT * (1.0 + percent);
	}break;
	case Add:
	{
		// 用户减推力, 3-5% 随机波动
		double percent = (static_cast<double>(rand() % 3) + 3.0) / 100.0;
		T = stableT * (1.0 + percent);
		if (errT > 0.0) {
			errT = errT * (1.0 + percent);
		}
		SetStableT(T); // 注意更新稳态值	
	} break;
	case Sub:
	{
		// 用户减推力, 3-5% 随机波动
		double percent = (static_cast<double>(rand() % 3) + 3.0) / 100.0;
		T = stableT * (1.0 - percent);
		if (errT > 0.0) {
			errT = errT * (1.0 - percent);
		}
		SetStableT(T); // 注意更新稳态值	
	} break;
	default:
		break;
	}

	if (invalidT > 0.0) {
		// 无效值
		historyT.emplace_back(dTime, 0.0);
	}
	else if (errT >= 0.0) {
		// 异常值
		historyT.emplace_back(dTime, errT);
	}
	else {
		historyT.emplace_back(dTime, T);
	}
	WriteData();
}

bool EGTSensor::UpdateStoping(int dt) {
	timeStamp += dt;
	double dTime = static_cast<double>(timeStamp) / 1000.0;
	// 以底数函数递减
	T = T + 10.0 * (log(dTime - stopTime + 1.0) / log(0.35));
	if (T <= 20.0) {
		T = 20.0;
	}
	if (errT > 0.0) {
		errT = errT + 10.0 * (log(dTime - stopTime + 1.0) / log(0.35));
		if (errT <= 20.0) {
			errT = 20.0;
		}
	}
	
	if (invalidT > 0.0) {
		// 无效值
		historyT.emplace_back(dTime, 0.0);
	}
	else if (errT >= 0.0) {
		// 异常值
		historyT.emplace_back(dTime, errT);
		if (abs(errT - 20.0) < 0.001) {
			WriteData();
			return true;
		}
	}
	else {
		historyT.emplace_back(dTime, T);
		if (abs(T - 20.0) < 0.001) {
			WriteData();
			return true;
		}
	}

	WriteData();
	return false;
}
void EGTSensor::UpdateStop(int dt) {
	timeStamp += dt;
	double dTime = static_cast<double>(timeStamp) / 1000.0;
	// 以底数函数递减
	T = T + 10.0 * (log(dTime - stopTime + 1.0) / log(0.35));
	if (T <= 20.0) {
		T = 20.0;
	}
	if (errT > 0.0) {
		errT = errT + 10.0 * (log(dTime - stopTime + 1.0) / log(0.35));
		if (errT <= 20.0) {
			errT = 20.0;
		}
	}
	
	if (invalidT > 0.0) {
		// 无效值
		historyT.emplace_back(dTime, 0.0);
	}
	else if (errT >= 0.0) {
		// 异常值
		historyT.emplace_back(dTime, errT);
	}
	else {
		historyT.emplace_back(dTime, T);
	}
	WriteData();
}

/* 燃油传感器 */
GasSensor::GasSensor(const string& fnameC, const string& fnameV): filenameC(fnameC), filenameV(fnameV) {
	C = 20000.0;
	V = 0.0;
	timeStamp = 0;
	startTime = 0.0;
	stableV = 0.0;
	errC = -1.0;
	invalidC = -1.0;
	errV = -1.0;
	// 打开一下文件, 清空作用
	ofstream ofs1(filenameC);
	if (ofs1.is_open()) {
		ofs1.close();
	}
	ofstream ofs2(filenameV);
	if (ofs2.is_open()) {
		ofs2.close();
	}
}

GasSensor::~GasSensor() {
	WriteDataToFile(historyC, filenameC);
	WriteDataToFile(historyV, filenameV);
}

bool GasSensor::UpdateStarting(int dt) {
	timeStamp += dt;
	double dTime = static_cast<double>(timeStamp) / 1000.0;
	// +-1
	double noiseV = (static_cast<double>(rand() % 100) - 50.0) / 100.0 * 2.0;
	if (dTime - startTime <= 2.0) {
		// 前2秒线性增加
		V = (dTime - startTime) * 5 + noiseV;
	}
	else {
		// 两秒后对数增加
		V = 42.0 * log10(dTime - startTime - 1.0) + 10.0 + noiseV;
	}

	if (errV >= 0.0) {
		C -= errV * dt / 1000.0;
		if (errC > 0.0) {
			errC -= errV * dt / 1000.0;
		}
		historyV.emplace_back(dTime, errV);
	}
	else {
		C -= V * dt / 1000.0;
		if (errC > 0.0) {
			errC -= V * dt / 1000.0;
		}
		historyV.emplace_back(dTime, V);
	}

	if (invalidC > 0.0) {
		historyC.emplace_back(dTime, 0.0);
	}
	else if (errC >= 0.0) {
		historyC.emplace_back(dTime, errC);
	}
	else {
		historyC.emplace_back(dTime, C);
	}
	WriteData();
	return false;
}

// 达到1000条的时候写一次
void GasSensor::WriteData() {
	if (historyV.size() > 1000) {
		WriteDataToFile(historyV, filenameV);
		historyV.clear();
		WriteDataToFile(historyC, filenameC);
		historyC.clear();
	}
}

void GasSensor::UpdateStable(int dt, USEROP op) {
	timeStamp += dt;
	double dTime = static_cast<double>(timeStamp) / 1000.0;
	switch (op)
	{
	case None:
	{
		// 用户无操作, +-3% 随机波动
		double percent = (static_cast<double>(rand() % 7) - 3.0) / 100.0;
		V = stableV * (1.0 + percent);
	} break;
	case Add:
	{
		// 用户加推力, +1
		V = stableV + 1;
		if (errV > 0.0) {
			errV = errV + 1;
		}
	} break;
	case Sub:
	{
		// 用户加推力, +1
		V = stableV - 1;
		if (errV > 0.0) {
			errV = errV - 1;
		}
	} break;
	default:
		break;
	}
	
	if (errV >= 0.0) {
		C -= errV * dt / 1000.0;
		if (errC > 0.0) {
			errC -= errV * dt / 1000.0;
		}
		historyV.emplace_back(dTime, errV);
	}
	else {
		C -= V * dt / 1000.0;
		if (errC > 0.0) {
			errC -= V * dt / 1000.0;
		}
		historyV.emplace_back(dTime, V);
	}

	if (invalidC > 0.0) {
		historyC.emplace_back(dTime, 0.0);
	}
	else if (errC >= 0.0) {
		historyC.emplace_back(dTime, errC);
	}
	else {
		historyC.emplace_back(dTime, C);
	}
	
	WriteData();
}

bool GasSensor::UpdateStoping(int dt) {
	timeStamp += dt;
	double dTime = static_cast<double>(timeStamp) / 1000.0;
	// 立即降到 0
	V = 0.0;
	if (errV > 0.0) {
		errV = 0.0;
	}
	historyV.emplace_back(dTime, V);
	if (invalidC > 0.0) {
		historyC.emplace_back(dTime, 0.0);
	}
	else if (errC >= 0.0) {
		historyC.emplace_back(dTime, errC);
	}
	else {
		historyC.emplace_back(dTime, C);
	}
	
	WriteData();
	return false;
}

void GasSensor::UpdateStop(int dt) {
	timeStamp += dt;
	double dTime = static_cast<double>(timeStamp) / 1000.0;
	// 立即降到 0
	V = 0.0;
	if (errV > 0.0) {
		errV = 0.0;
	}
	historyV.emplace_back(dTime, V);

	if (invalidC > 0.0) {
		historyC.emplace_back(dTime, 0.0);
	}
	else if (errC >= 0.0) {
		historyC.emplace_back(dTime, errC);
	}
	else {
		historyC.emplace_back(dTime, C);
	}
	WriteData();
}
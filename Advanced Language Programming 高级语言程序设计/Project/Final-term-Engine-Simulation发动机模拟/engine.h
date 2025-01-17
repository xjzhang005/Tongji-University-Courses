#pragma once
#include "sensor.h"

using namespace std;

#define HUPOCOLOR RGB(255, 191, 0)

class Engine {
private:
	RotSpeedSensor rotSpeedSensor1; // 一个发动机有两个转速传感器
	RotSpeedSensor rotSpeedSensor2;
	EGTSensor egtSensor1; // 一个发动机有两个egt传感器
	EGTSensor egtSensor2;

public:
	Engine(const string& engineName);
	
	double GetT() const {
		// 取有效值，两者都有效取平均
		if (egtSensor1.GetInvalidData() > 0.0 && egtSensor2.GetInvalidData() > 0.0) {
			// 无效值
			return 0.0;
		}
		else if (egtSensor1.GetInvalidData() > 0.0) {
			if (egtSensor2.GetErrData() > 0.0) {
				return egtSensor2.GetErrData();
			}
			else {
				return egtSensor2.GetT();
			}
		}
		else if (egtSensor2.GetInvalidData() > 0.0) {
			if (egtSensor1.GetErrData() > 0.0) {
				return egtSensor1.GetErrData();
			}
			else {
				return egtSensor1.GetT();
			}
		}
		else {
			if (egtSensor1.GetErrData() > 0.0 && egtSensor2.GetErrData() > 0.0) {
				return (egtSensor1.GetErrData() + egtSensor2.GetErrData()) / 2.0;
			}
			else if (egtSensor1.GetErrData() > 0.0) {
				return egtSensor2.GetT();
			}
			else if (egtSensor2.GetErrData() > 0.0) {
				return egtSensor1.GetT();
			}
			else {
				return (egtSensor1.GetT() + egtSensor2.GetT()) / 2.0;
			}
		}
	}
	double GetN() const {
		// 取有效值，两者都有效取平均
		if (rotSpeedSensor1.GetInvalidData() > 0.0 && rotSpeedSensor2.GetInvalidData() > 0.0) {
			// 无效值
			return 0.0;
		}
		else if (rotSpeedSensor1.GetInvalidData() > 0.0) {
			if (rotSpeedSensor2.GetErrData() > 0.0) {
				return rotSpeedSensor2.GetErrData();
			}
			else {
				return rotSpeedSensor2.GetN();
			}
		}
		else if (rotSpeedSensor2.GetInvalidData() > 0.0) {
			if (rotSpeedSensor1.GetErrData() > 0.0) {
				return rotSpeedSensor1.GetErrData();
			}
			else {
				return rotSpeedSensor1.GetN();
			}
		}
		else {
			if (rotSpeedSensor1.GetErrData() > 0.0 && rotSpeedSensor2.GetErrData() > 0.0) {
				return (rotSpeedSensor1.GetErrData() + rotSpeedSensor2.GetErrData()) / 2.0;
			}
			else if (rotSpeedSensor1.GetErrData() > 0.0) {
				return rotSpeedSensor2.GetN();
			}
			else if (rotSpeedSensor2.GetErrData() > 0.0) {
				return rotSpeedSensor1.GetN();
			}
			else {
				return (rotSpeedSensor1.GetN() + rotSpeedSensor2.GetN()) / 2.0;
			}
		}
	}
	// N / 额定转速 = N1
	double GetN1() const {
		return GetN() / 40000.0 * 100.0;
	}

	// 确保时间戳和双发传感器大家都相同
	void SetStableT(double st) {
		egtSensor1.SetStableT(st);
		egtSensor2.SetStableT(st);
	}
	void SetStableN(double sn) {
		rotSpeedSensor1.SetStableN(sn);
		rotSpeedSensor2.SetStableN(sn);
	}
	void SetStopTime() {
		rotSpeedSensor1.SetStopTime();
		rotSpeedSensor2.SetStopTime();
		egtSensor1.SetStopTime();
		egtSensor2.SetStopTime();
	}
	void SetStartTime() {
		rotSpeedSensor1.SetStartTime();
		rotSpeedSensor2.SetStartTime();
		egtSensor1.SetStartTime();
		egtSensor2.SetStartTime();
	}

	SENSOR_STATUS GetSpeedSensorStatus() const {
		// 两个传感器工作状态
		if (rotSpeedSensor1.GetInvalidData() > 0.0 && rotSpeedSensor2.GetInvalidData() > 0.0) {
			// 无效值
			return TwoLose;
		}
		else if (rotSpeedSensor1.GetInvalidData() > 0.0) {
			return One1Lose;
		}
		else if (rotSpeedSensor2.GetInvalidData() > 0.0) {
			return One2Lose;
		}
		else {
			return NormalSENSOR;
		}
	}

	// 检测传感器状态
	SENSOR_STATUS GetEGTSensorStatus() const {
		// 两个传感器工作状态
		if (egtSensor1.GetInvalidData() > 0.0 && egtSensor2.GetInvalidData() > 0.0) {
			// 无效值
			return TwoLose;
		}
		else if (egtSensor1.GetInvalidData() > 0.0) {
			return One1Lose;
		}
		else if (egtSensor2.GetInvalidData() > 0.0) {
			return One2Lose;
		}
		else {
			return NormalSENSOR;
		}
	}

	// 获取转速异常
	VALUE_ERR GetSpeedValueERR() const {
		if (GetN1() > 120.0) {
			return REDERR;
		}
		else if (GetN1() > 105.0) {
			return HUPOERR;
		}
		return NormalVALUE;
	}

	// 获取温度异常
	VALUE_ERR GetTValueERR(PALNESTATUS curStatus) const {
		if (curStatus == PALNESTATUS::Starting) {
			if (GetT() > 1000.0) {
				return REDERR;
			}
			else if (GetT() > 850.0) {
				return HUPOERR;
			}
		}
		else if (curStatus == PALNESTATUS::Stable) {
			if (GetT() > 1100.0) {
				return REDERR;
			}
			else if (GetT() > 950) {
				return HUPOERR;
			}
		}
		return NormalVALUE;
	}

	// 设置异常值
	// 转速传感器1
	void SetSpeedSensor1ErrData(double errData) {
		rotSpeedSensor1.SetErrData(errData);
	}
	void SetSpeedSensor1InvalidData() {
		rotSpeedSensor1.SetInvalidData();
	}
	// 转速传感器2
	void SetSpeedSensor2ErrData(double errData) {
		rotSpeedSensor2.SetErrData(errData);
	}
	void SetSpeedSensor2InvalidData() {
		rotSpeedSensor2.SetInvalidData();
	}
	// 温度传感器1
	void SetEGTSensor1ErrData(double errData) {
		egtSensor1.SetErrData(errData);
	}
	void SetEGTSensor1InvalidData() {
		egtSensor1.SetInvalidData();
	}
	// 温度传感器2
	void SetEGTSensor2ErrData(double errData) {
		egtSensor2.SetErrData(errData);
	}
	void SetEGTSensor2InvalidData() {
		egtSensor2.SetInvalidData();
	}


	bool UpdateStarting(int dt);
	void UpdateStable(int dt, USEROP op);
	bool UpdateStoping(int dt);
	void UpdateStop(int dt);
};
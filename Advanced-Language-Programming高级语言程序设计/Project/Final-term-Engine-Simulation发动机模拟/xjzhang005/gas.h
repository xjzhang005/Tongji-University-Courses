#pragma once
// 油箱类

#include "sensor.h"

using namespace std;

class Gas {
private:
	GasSensor gasSensor; // 一个油箱只有一个余量传感器
public:
	Gas();
	double GetV() const {
		if (gasSensor.GetErrDataV() >= 0.0) {
			return gasSensor.GetErrDataV();
		}
		return gasSensor.GetV();
	}
	double GetC() const {
		if (gasSensor.GetInvalidDataC() > 0.0) {
			return 0.0;
		}
		else if (gasSensor.GetErrDataC() >= 0.0) {
			return gasSensor.GetErrDataC();
		}
		return gasSensor.GetC();
	}
	void SetStableV(double sv) {
		gasSensor.SetStableV(sv);
	}

	// 开放接口修改数据
	void SetErrDataC(double errData) {
		gasSensor.SetErrDataC(errData);
	}
	void SetInvalidDataC() {
		gasSensor.SetInvalidDataC();
	}
	void SetErrDataV(double errData) {
		gasSensor.SetErrDataV(errData);
	}

	// 获取余量数值是否合理
	VALUE_ERR GetCValueERR(PALNESTATUS s) {
		if (gasSensor.GetInvalidDataC() > 0.0) {
			// 无效值
			return REDERR;
		}

		if (s == Stoping || s == Stop) {
			return NormalVALUE;
		}
		if (GetC() < 1000.0) {
			return HUPOERR;
		}
		return NormalVALUE;
	}

	// 获取余量数值是否合理
	VALUE_ERR GetVValueERR() {
		if (GetV() > 50.0) {
			return HUPOERR;
		}
		return NormalVALUE;
	}

	void SetStartTime() {
		gasSensor.SetStartTime();
	}

	bool UpdateStarting(int dt);
	void UpdateStable(int dt, USEROP op);
	bool UpdateStoping(int dt);
	void UpdateStop(int dt);
};
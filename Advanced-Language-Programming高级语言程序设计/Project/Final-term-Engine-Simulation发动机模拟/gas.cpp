#include "gas.h"

using namespace std;

Gas::Gas(): gasSensor("table\\gasC.csv", "table\\gasV.csv") {
	
}

// 直接调用 GasSensor 的函数
bool Gas::UpdateStarting(int dt) {
	return gasSensor.UpdateStarting(dt);
}

void Gas::UpdateStable(int dt, USEROP op) {
	gasSensor.UpdateStable(dt, op);
}

bool Gas::UpdateStoping(int dt) {
	return gasSensor.UpdateStoping(dt);
}

void Gas::UpdateStop(int dt) {
	gasSensor.UpdateStop(dt);
}
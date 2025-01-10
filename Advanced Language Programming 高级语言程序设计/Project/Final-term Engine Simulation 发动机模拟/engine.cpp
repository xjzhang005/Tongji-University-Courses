#include "engine.h"

using namespace std;

Engine::Engine(const string& engineName):
	rotSpeedSensor1("table\\" + engineName + "Rotspeed1.csv"),
	rotSpeedSensor2("table\\" + engineName + "Rotspeed2.csv"),
	egtSensor1("table\\" + engineName + "Egt1.csv"),
	egtSensor2("table\\" + engineName + "Egt2.csv")
{
}

bool Engine::UpdateStarting(int dt) {
	egtSensor1.UpdateStarting(dt);
	egtSensor2.UpdateStarting(dt);

	// 检测到稳态就算结束启动阶段
	bool flag = rotSpeedSensor1.UpdateStarting(dt);
	flag = rotSpeedSensor2.UpdateStarting(dt) || flag;
	return flag;
}
void Engine::UpdateStable(int dt, USEROP op) {
	egtSensor1.UpdateStable(dt, op);
	egtSensor2.UpdateStable(dt, op);
	rotSpeedSensor1.UpdateStable(dt, op);
	rotSpeedSensor2.UpdateStable(dt, op);
}
bool Engine::UpdateStoping(int dt) {
	egtSensor1.UpdateStoping(dt);
	egtSensor2.UpdateStoping(dt);

	// 检测到停止就算停止
	bool flag = rotSpeedSensor1.UpdateStoping(dt);
	flag = rotSpeedSensor2.UpdateStoping(dt) || flag;
	return flag;
}

void Engine::UpdateStop(int dt) {
	egtSensor1.UpdateStop(dt);
	egtSensor2.UpdateStop(dt);
	rotSpeedSensor1.UpdateStop(dt);
	rotSpeedSensor2.UpdateStop(dt);
}
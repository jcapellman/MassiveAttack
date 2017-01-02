#include "../MassiveAttack.Client.Engine/Main.h"
#include "../MassiveAttack.Client.Engine/MainExport.h"

#pragma comment(lib, "../Debug/MassiveAttack.Client.Engine.lib")

int main(int argc, char *argv[])
{
	MassiveAttackClientEngine::MainEngine engine;

	engine.RunEngine();

	return 0;
}
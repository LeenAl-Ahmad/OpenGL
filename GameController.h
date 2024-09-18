
#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

#include "StandardInclude.h"
#include "Shader.h"
#include "Mesh.h"

class GameController : public Singleton< GameController>
{
public:
	GameController();
	virtual ~GameController() = default;

	void Initialize();
	void RunGame();

private:
	Shader shader = {};
	Mesh mesh = {};
};

#endif // !GAME_CONTROLLER_H





#include "round.h"

typedef struct Game Game;

Game* GameCreate(int _realPlayers, int _machinePlayers);

void GameDestroy(Game** _game);

Round* GetRound(Game* _game);

void PlayGame(Game* _game);
#include <stdlib.h>
#include <stdio.h>

#include "player.h"
#include "round.h"
#include "game.h"

struct Game {
    Player** m_players;
    int* m_score;
    Round* m_round;
    int m_totalPlayers;
};

static void freePlayerArray(Game* _game, int _lastPlayer);
static void PrintAllPlayers(Player** _players, int* _scoreTable, int _totalPlayers);

Game* GameCreate(int _realPlayers, int _machinePlayers) {

    int totalPlayers = _realPlayers + _machinePlayers;
    int index;

    if(_realPlayers == 0) {
        return NULL;
    }

    Game* gptr = (Game*)malloc(sizeof(Game));

    if(gptr == NULL) {
        return NULL;
    }

    gptr->m_players = (Player**)malloc(totalPlayers*sizeof(Player*));

    if(gptr->m_players == NULL) {
        free(gptr);
        return NULL;
    }

    gptr->m_score = (int*)calloc(totalPlayers, sizeof(int));

    if(gptr->m_score == NULL) {
        free(gptr->m_players);
        free(gptr->m_score);
        return NULL;
    }

    for(index = 0; index < _realPlayers; ++index) {
        gptr->m_players[index] = PlayerCreate(1, index);

        if(gptr->m_players[index] == NULL) {
            freePlayerArray(gptr, index);
            return NULL;
        }
    }

    for(; index < totalPlayers; ++index) {
        gptr->m_players[index] = PlayerCreate(0, index);

        if(gptr->m_players[index] == NULL) {
            freePlayerArray(gptr, index);
            return NULL;
        }
    }

    gptr->m_totalPlayers = totalPlayers;

    gptr->m_round = RoundCreate(gptr->m_players, totalPlayers);

    return gptr;
}

void GameDestroy(Game** _game) {

    int index;

    if(_game == NULL || *_game == NULL) {
        return;
    }

    Game* gptr = *_game;

    for(index = 0; index < gptr->m_totalPlayers; ++index) {
        PlayerDestroy(&gptr->m_players[index]);
    }
    RoundDestroy(&gptr->m_round);
    free(gptr->m_round);
    free(gptr->m_players);
    free(gptr->m_score);
    free(gptr);

    *_game = NULL;
}

static void freePlayerArray(Game* _game, int _lastPlayer) {

    int index;

    for(index = 0; index < _lastPlayer; ++index) {
        PlayerDestroy(&_game->m_players[index]);
    }

    free(_game->m_players);
    free(_game->m_score);
    free(_game);
}

void PlayGame(Game* _game) {

    int gameStatus = -1;

    while(gameStatus == -1) {

        gameStatus = RunRound(_game->m_round, _game->m_score, 1);

    }

    if(gameStatus == -2) {

    }

    PrintAllPlayers(_game->m_players, _game->m_score, _game->m_totalPlayers);

}

Round* GetRound(Game* _game) {

    return _game->m_round;
}

static void PrintAllPlayers(Player** _players, int* _scoreTable, int _totalPlayers) {

    int index;

    printf("\n");
    printf("---------------\n");
    
    for(index = 0; index < _totalPlayers; ++index) {
        printf("Player ID: %d\t", index);
    }
    printf("\n");
    for(index = 0; index < _totalPlayers; ++index) {
        printf("Score: %d\t", _scoreTable[index]);
    }
    printf("\n");
}


#ifndef GOAT_STATE
#define GOAT_STATE

enum ModeKind {
	Title,
	Overview,
	Inspect,
	MiniGame
};

enum MiniGameKind {
    None,
	Game1,
    Game2,
    Game3,
    Game4
};

typedef struct {
    enum ModeKind mode;
    enum MiniGameKind miniGame;

    double overviewZoomRadius;
    int overviewTurnDeg;

    bool miniGameSolvedState[4];
} GAME_MainState;

#endif
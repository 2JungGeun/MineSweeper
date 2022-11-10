#include "Screen.h"
#include "Utils.h"
#include "Player.h"
#include "Mine.h"
#include "InputSystem.h"
using namespace std;

// Utils.h에 COLS, ROWS 정의
int main()
{
    srand((unsigned int)time(NULL));
    InputSystem input;
    Player player(5, 5, input);
    Screen screen(COLS, ROWS, input);
    Mine mine(COLS, ROWS, &screen, input);

    while (1)
    {
        screen.render();
        player.render();
        mine.render();
        if ((mine.getIsGameClear() || mine.getIsGameover()))
            break;
        Sleep(50);
        input.readEveryFrame();
        player.playerControl();
        screen.screenContol(player.getPos());
        mine.mineControl(player.getPos());
    }

    if (mine.getIsGameover())
    {
        Borland::GotoXY(0, COLS * 2 + 7);
        printf("GameOver");
    }

    if (mine.getIsGameClear())
    {
        Borland::GotoXY(0, COLS * 2 + 7);
        printf("GameClear");
    }
    return 0;
}

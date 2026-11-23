#include <genesis.h>
#include <stdio.h>

// Jorge the Truck Driver - edicao Mega Drive (SGDK).
// O jogo de navegador permanece independente na branch main.
// Tela: 40 x 28 caracteres. Controle: Mega Drive de 3 ou 6 botoes.

#define PLAYER_X 5
#define LANES 3
#define OBJECTS 6

typedef struct {
    s16 x;
    u8 lane;
    u8 kind;  // 0 = caixa, 1 = obstaculo
    u8 active;
} Object;

static Object objects[OBJECTS];
static const u16 laneY[LANES] = {9, 13, 17};
static u16 randomSeed = 0x2567;
static u16 frame = 0;
static u16 lastButtons = 0;
static s16 score = 0;
static s16 lives = 5;
static u8 lane = 1;
static u8 speed = 2;
static u8 gameState = 0; // 0 = menu, 1 = jogando, 2 = pausa, 3 = fim

static u16 randomNumber(void)
{
    randomSeed = (u16) (randomSeed * 109u + 1021u);
    return randomSeed;
}

static void resetGame(void)
{
    u16 i;
    score = 0;
    lives = 5;
    lane = 1;
    speed = 2;
    frame = 0;
    randomSeed += 31;
    gameState = 1;
    for (i = 0; i < OBJECTS; i++) objects[i].active = 0;
}

static void spawnObject(void)
{
    u16 i;
    for (i = 0; i < OBJECTS; i++)
    {
        if (!objects[i].active)
        {
            objects[i].active = 1;
            objects[i].x = 36;
            objects[i].lane = (u8) (randomNumber() % LANES);
            // Mais caixas que obstaculos, para continuar competitivo e viavel.
            objects[i].kind = ((randomNumber() & 3) == 0) ? 1 : 0;
            break;
        }
    }
}

static void stepGame(void)
{
    u16 i;
    for (i = 0; i < OBJECTS; i++)
    {
        Object *o = &objects[i];
        if (!o->active) continue;
        o->x--;

        // A faixa do caminhao determina se a caixa foi coletada.
        if (o->lane == lane && o->x >= PLAYER_X && o->x <= PLAYER_X + 3)
        {
            if (o->kind == 0) score++;
            else if (lives > 0) lives--;
            o->active = 0;
        }
        else if (o->x < 1)
        {
            // Perder uma caixa custa 3 pontos.
            if (o->kind == 0) score -= 3;
            if (score < 0) score = 0;
            o->active = 0;
        }
    }
    if (lives == 0) gameState = 3;
}

static void drawLayout(void)
{
    VDP_clearPlane(BG_A, TRUE);
    VDP_drawText("JORGE THE TRUCK DRIVER   MEGA DRIVE", 2, 1);
    VDP_drawText("RIO DE JANEIRO - ENTREGA DE CAIXAS", 2, 3);
    VDP_drawText("--------------------------------------", 1, 7);
    VDP_drawText("- - - - - - - - - - - - - - - - - -", 2, 11);
    VDP_drawText("- - - - - - - - - - - - - - - - - -", 2, 15);
    VDP_drawText("--------------------------------------", 1, 20);
    VDP_drawText("[] CAIXA +1    XX OBSTACULO -1 VIDA", 2, 22);
    VDP_drawText("C/A GAS  B FREIO  UP/DOWN FAIXA", 2, 24);
    VDP_drawText("START INICIAR / PAUSAR", 2, 25);
}

static void drawGame(void)
{
    u16 i;
    char hud[40];

    // Limpa apenas o centro das faixas, preservando a pista.
    for (i = 0; i < LANES; i++)
        VDP_drawText("                                    ", 2, laneY[i]);

    for (i = 0; i < OBJECTS; i++)
        if (objects[i].active && objects[i].x < 38)
            VDP_drawText(objects[i].kind ? "XX" : "[]",
                         (u16) objects[i].x, laneY[objects[i].lane]);

    VDP_drawText("[=]>", PLAYER_X, laneY[lane]);
    sprintf(hud, "PONTOS:%5d   VIDAS:%d  GAS:%d", score, lives, speed);
    VDP_drawText("                                    ", 2, 5);
    VDP_drawText(hud, 2, 5);

    VDP_drawText("                                    ", 2, 26);
    if (gameState == 0) VDP_drawText("APERTE START OU A PARA JOGAR", 4, 26);
    else if (gameState == 2) VDP_drawText("PAUSADO - START PARA VOLTAR", 4, 26);
    else if (gameState == 3) VDP_drawText("FIM! START PARA REINICIAR", 4, 26);
    else VDP_drawText("PEGUE CAIXAS E DESVIE DAS PEDRAS", 3, 26);
}

int main(bool hard)
{
    u16 buttons;
    u16 pressed;
    u16 tick = 0;
    u16 spawnTick = 0;

    (void) hard;
    JOY_init();
    VDP_setScreenWidth320();
    drawLayout();
    drawGame();

    while (1)
    {
        buttons = JOY_readJoypad(JOY_1);
        pressed = buttons & (u16) ~lastButtons;
        lastButtons = buttons;

        if (gameState == 0 || gameState == 3)
        {
            if (pressed & (BUTTON_START | BUTTON_A))
            {
                resetGame();
                tick = 0;
                spawnTick = 0;
            }
        }
        else if (gameState == 2)
        {
            if (pressed & BUTTON_START) gameState = 1;
        }
        else
        {
            if (pressed & BUTTON_START) gameState = 2;
            else
            {
                if ((pressed & BUTTON_UP) && lane > 0) lane--;
                if ((pressed & BUTTON_DOWN) && lane < LANES - 1) lane++;

                // Opcional: usa A/C para acelerar, B para reduzir.
                if ((buttons & (BUTTON_A | BUTTON_C)) && speed < 4) speed++;
                if ((buttons & BUTTON_B) && speed > 1) speed--;
                if ((buttons & (BUTTON_A | BUTTON_B | BUTTON_C)) == 0) speed = 2;

                tick++;
                if (tick >= (u16) (11 - speed * 2))
                {
                    tick = 0;
                    frame++;
                    spawnTick++;
                    stepGame();
                    if (gameState == 1 && spawnTick >= 7)
                    {
                        spawnTick = 0;
                        spawnObject();
                    }
                }
            }
        }

        // Atualizacao moderada para funcionar bem em emuladores simples.
        if ((frame & 1) == 0 || gameState != 1) drawGame();
        SYS_doVBlankProcess();
    }
    return 0;
}

#include <iostream>
#include "raylib-cpp.hpp"
#include <string>

bool gameOver, canTurn;
int x, y, fruitX, fruitY, score, snakeX, snakeY;
int tailX[400], tailY[400];
int ntail;
int screenWidth = 800;
int screenHeight = 800;
float timer;
float timeDelay = 0.3;

enum eDirection
{
    STOP = 0,
    LEFT,
    RIGHT,
    UP,
    DOWN
};
eDirection dir;

void Setup() // establishes base values before the game starts
{
    gameOver = false;
    dir = STOP;
    x = 20 / 2;
    y = 20 / 2;
    fruitX = rand() % 19 + 1;
    fruitY = rand() % 19 + 1;
    score = 0;
    while (fruitX == 10 && fruitY == 10)
    {
        fruitX = rand() % 19 + 1;
        fruitY = rand() % 19 + 1; 
    }
}
void Input() // checks for wasd inputs
{
    if (IsKeyPressed(KEY_W))
    {
        if (ntail < 1)
        {
            dir = UP;
        }
        else if (dir == DOWN)
        {

        }
        else
        {
            dir = UP;
        }
        
    }
    if (IsKeyPressed(KEY_S))
    {
        if (ntail < 1)
        {
            dir = DOWN;
        }
        else if (dir == UP)
        {

        }
        else
        {
            dir = DOWN;
        }
    }
    if (IsKeyPressed(KEY_A))
    {
        if (ntail < 1)
        {
            dir = LEFT;
        }
        else if (dir == RIGHT)
        {

        }
        else
        {
            dir = LEFT;
        }
    }
    if (IsKeyPressed(KEY_D))
    {
        if (ntail < 1)
        {
            dir = RIGHT;
        }
        else if (dir == LEFT)
        {

        }
        else
        {
            dir = RIGHT;
        }
    }
}
void Logic()
{
    int prevX = tailX[0];
    int prevY = tailY[0];
    int prev2X, prev2Y;
    tailX[0] = x;
    tailY[0] = y;

    for(int i = 1; i < ntail; i++)// sets the tail to be the prevX and Y of tail[i] so each time a tail is added itll take the prev X and Y values
    {
        prev2X = tailX[i];
        prev2Y = tailY[i];
        tailX[i] = prevX;
        tailY[i] = prevY;
        prevX = prev2X;
        prevY = prev2Y;
    }
    
        switch (dir) // sets direction and moves in that direction
        {
        case LEFT:
            x--;
            break;
        case RIGHT:
            x++;
            break;
        case UP:
            y--;
            break;
        case DOWN:
            y++;
            break;
        default:
            break;
        }
    
   
    if (x < 1) // check if snake head outside the 19x19 grid
    {
        gameOver = true;
    }
    else if (y < 1)
    {
        gameOver = true;
    }
    else if (x > 19)
    {
        gameOver = true;
    }
    else if (y > 19)
    {
        gameOver = true;
    }

    for(int i = 0; i < ntail; i++) // if snake head hits body gameover
    {
        if (tailX[i] == x && tailY[i] == y)
        {
            gameOver = true;
        }
    }
    if (x == fruitX && y == fruitY)
    {
        score += 10;
        bool valid = false;
        while (!valid)
        {
            fruitX = rand() % 19 + 1;
            fruitY = rand() % 19 + 1;
            // check if not in head or tail then set invalid to false
            valid = true;
            if (x == fruitX && y == fruitY)
            {
                valid = false;
                continue;
            }
            for (int i = 0; i < ntail; i++)
            {
                if (fruitX == tailX[i] && fruitY == tailY[i])
                {
                    valid = false;
                    break;
                }
            }
        }
        ntail++;
        if (score > 100 && score < 200) // lowers the input delay making the snake move faster
        {
            timeDelay = 0.25;
        }
        else if (score >= 200 && score < 300)
        {
            timeDelay = 0.2;
        }
        else if (score >= 300)
        {
            timeDelay = 0.15;
        }
    }
}
void Draw()
{
    int top = 0;
    int bottom = 0;
    int left = 0;
    int right = 0;
    int posY1 = 0;
    int posY2 = 0;
    int counterX = 10;
    int counterY = 10;
    int timer = 0;
    
        for (int i = 0; i < 22; i++) // draws top border
        {
            DrawRectangle(top, 0, screenWidth / 21, screenHeight / 21, BLACK);
            top += screenWidth / 21;
        }
        for (int i = 0; i < 21; i++)
        {
            counterY += 38.09;
            counterX = 15;
            for (int j = 0; j < 21; j++)
            {
                if (j == 0)  // draws left border
                {
                    posY1 += screenHeight / 21;
                    DrawRectangle(0, posY1, screenHeight / 21, screenHeight / 21, BLACK);
                }
                if (j > 0 && j < 20) 
                {
                    counterX += 38.09;
                    DrawText("x", counterX, counterY, 20, WHITE); // draws a grid to help identify where the playable area is. *CAN COMMENT / UNCOMMENT THIS OUT* 
                }
                if (!gameOver)
                {
                    if (i == y && j == x) // draws snake and its eyes
                    {
                        snakeX = (j * 38.09) + 19;
                        snakeY = (i * 38.09) + 19;
                        DrawCircle(snakeX, snakeY, 15, DARKGREEN);
                        if (dir == UP)
                        {
                            DrawCircle(snakeX - 6, snakeY - 5, 3, BLACK);
                            DrawCircle(snakeX + 6, snakeY - 5, 3, BLACK);
                        }
                        else if (dir == RIGHT)
                        {
                            DrawCircle(snakeX + 6, snakeY - 5, 3, BLACK);
                            DrawCircle(snakeX + 6, snakeY + 5, 3, BLACK);
                        }
                        else if (dir == LEFT)
                        {
                            DrawCircle(snakeX - 6, snakeY - 5, 3, BLACK);
                            DrawCircle(snakeX - 6, snakeY + 5, 3, BLACK);
                        }
                        else if (dir == DOWN)
                        {
                            DrawCircle(snakeX - 6, snakeY + 5, 3, BLACK);
                            DrawCircle(snakeX + 6, snakeY + 5, 3, BLACK);
                        }
                        else if (dir == STOP)
                        {
                            DrawCircle(snakeX - 6, snakeY - 5, 3, BLACK);
                            DrawCircle(snakeX + 6, snakeY - 5, 3, BLACK);
                        }
                    }
                    else if (i == fruitY && j == fruitX) // draws fruit
                    {
                        DrawCircle((j * 38.09) + 19, (i * 38.09) + 19, 15, RED);
                    }
                    else
                    {
                        for (int k = 0; k < ntail; k++)
                        {
                            if (tailX[k] == j && tailY[k] == i) // draws tail
                            {
                                DrawCircle((j * 38.09) + 19, (i * 38.09) + 19, 15, DARKGREEN);
                            }
                        }
                    }
                }
                if (j == 21 - 1) // draws right border
                {
                    posY2 += screenHeight / 21;
                    DrawRectangle(762, posY2, screenHeight / 21, screenHeight / 21, BLACK);
                }
            }
        }
        for (int i = 0; i < 21; i++) // draws bottom border
        {
            DrawRectangle(bottom, 762, screenHeight / 21, screenHeight / 21, BLACK);
            bottom += screenHeight / 21;
        }
}

int main() 
{
    raylib::Window window(screenWidth, screenHeight, "Snake Game");
    SetTargetFPS(60);
    Setup();
    while (!window.ShouldClose())
    {
        timer += GetFrameTime();
        BeginDrawing();
        Draw();
        Input();
        if (timer > timeDelay && !gameOver) // adds delay to the logic so the snake will move after the set time delay
        {
            Logic();
            timer = 0;
        }
        
        window.ClearBackground(GRAY);
        DrawFPS(10, 10);
        DrawText("Snake by Blake", screenWidth / 3 + 50, 10, 20, WHITE);
        std::string scored = std::to_string(score);
        DrawText("Score: ", 680, 10, 20, WHITE);
        DrawText(scored.c_str(), 760, 10, 20, WHITE);
        EndDrawing();
        if (gameOver) // draws score
        {
            DrawText("Final Score: ", screenWidth / 3 - 70, screenHeight / 3, 60, WHITE);
            DrawText(scored.c_str(), screenWidth / 2 + 180, screenHeight / 3, 60, WHITE);
            DrawText("Press Esc to Close", screenWidth / 3 + 40, screenWidth / 3 + 80, 20, WHITE);
        }
        if (IsKeyPressed(KEY_ESCAPE)) // closes the program
        {
            EndDrawing();
        }
    }
    
    // UnloadTexture() and CloseWindow() are called automatically.

    return 0;
}


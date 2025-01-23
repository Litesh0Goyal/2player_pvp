#include <iostream>
#include <vector>
#include "Headers\Map_Editor.h"
#include "Headers\Player_Obj.h"
#include "Headers\Colliders.h"
#include "Headers\Timers.h"
#include "raylib.h"
using std::vector;
int main(void)
{
    
    // Initialization
    //--------------------------------------------------------------------------------------

    
    const int Grid_Size_x = 20;//Grid parramiter x
    const int Grid_Size_y = 10;//Grid parramiter y
    const int Block_Size = 30;//Grid parramiter  size
    
    const int screenWidth = 800;//Window parramiter 
    const int screenHeight = 450;//Window parramiter 
    
    const Rectangle Play_button = {screenWidth/2.0f-100,screenHeight/2.0f-25,200,50};//Main menu parramiter
    
    InitWindow(screenWidth, screenHeight, "PvP_GAME");
    Texture2D P1 = LoadTexture("Sprite_Sheets/player1.png");
    Texture2D P2 = LoadTexture("Sprite_Sheets/player2.png");
    Texture2D FB = LoadTexture("Sprite_Sheets/FireBall.png");
    SetTargetFPS(60);
    
    int Player1Type = 0;
    int Player2Type = 0;
    int screen = 1; //current screen being displayed (Main menu parramiter)
    int main_menu = 1;//Main menu parramiter
    int play = 2;//Main menu parramiter
    
    bool P1Atk = true;
    bool P2Atk = true;
    
    float DeltaTime = 0.00f;
    
    Time Tm;
    
    MapEditor ME((float)screenWidth, (float)screenHeight, (float)Block_Size, (float)Grid_Size_x, (float)Grid_Size_y);//Map object
    
    vector<Rectangle> Player1Attack;
    //Rectangle Player2Attack[Grid_Size_y] = {0};
    
    PlayerObj Pl(0,0,(Rectangle){0,0,0,0});//player object
    PlayerObj Player1(1,1,(Rectangle){0,0,Block_Size,Block_Size});//Player object 1
    PlayerObj Player2(1,1,(Rectangle){570,270,Block_Size,Block_Size});//Player object 2
    
    // definig camera object 
    Camera2D camera = { 0 };
    camera.target = (Vector2){(Grid_Size_x*Block_Size)/2.0f,(Grid_Size_y*Block_Size)/2.0f};
    camera.offset = (Vector2){screenWidth/2.0f,screenHeight/2.0f};
    camera.rotation = 0.0f;
    camera.zoom = 1.0f;
     
    while (!WindowShouldClose())        // Detect window close button or ESC key
    {
        
        
        while( (screen==play) and (!WindowShouldClose()) )
        {
            DeltaTime = GetFrameTime();
            // Update
            //---------------------------------------------------------------------------------
            
            
            Pl.GetMovement(&Player1,&Player2);  // MOVEMENT SCRIPT
            
            //---------------------------------------------------------------------------------
            
            // Prevent Movement Over Borders and over lap
            Pl.FixMovemet(&Player1,&Player2,Grid_Size_x,Grid_Size_y,Block_Size);


            //----------------------------------------------------------------------------------
            // check player health if below 0
            if (Player1.Hp <= 0) Pl.SetMovement(false);
            else if (Player2.Hp <= 0) Pl.SetMovement(false);
            //----------------------------------------------------------------------------------
            
            if ((CheckCollisionPointRec(GetMousePosition(), Play_button)) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                screen = 1;
            }
            if(P1Atk){
                if (IsKeyPressed(KEY_Q)){
                    Player1Type = 1;
                    Player1Attack = {};
                    vector<int> Pattern = {1}; 
                    Tm.StartTimer(1.5);
                    ME.AttackLine(Player1.Pos, Player1Attack, Pattern);
                }
            }
            // Draw
            //----------------------------------------------------------------------------------
            
            
            BeginDrawing();
            ClearBackground(RAYWHITE);
                BeginMode2D(camera);
                // Draw a agrid of size "Grid_Size_x*Block_Size" and "Grid_Size_y*Block_Size" 
                //------------------------------------------------------------------------------
                    // X axis
                    for(int x=0; x<=Block_Size*Grid_Size_x; x+=Block_Size){
                        DrawLine(x,0,x,Grid_Size_y*Block_Size,BLACK);
                    }
                    // Y axis 
                    for(int y=0; y<=Block_Size*Grid_Size_y; y+=Block_Size){ 
                        DrawLine(0,y,Grid_Size_x*Block_Size,y,BLACK);
                    }
                //------------------------------------------------------------------------------
                    DrawTexture(P1,Player1.Pos.x,Player1.Pos.y,WHITE);
                    DrawTexture(P2,Player2.Pos.x,Player2.Pos.y,WHITE);
                    
                    if ( not Tm.IsTimerUp()){  
                        if(Player1Type == 1){
                            float TimeStamp = 0.20f;
                            P1Atk = false;
                            P2Atk = false;
                            int Time = (int)((Tm.CurrentTime()/TimeStamp));// how to fix? This is in reverse ?????!!!???11!???!?!?!?!?!?!?!?!?
                            if(Time<(int)Player1Attack.size()){
                                DrawTexture(FB,Player1Attack.at(Time).x,Player1Attack.at(Time).y,WHITE);
                            }
                        }
                    }
                    else{
                        P1Atk = true;
                        P2Atk = true;
                        Player1Attack = {};
                    }
                
                EndMode2D();
                
                ME.DeathScreen(&Player1, &Player2, Play_button);
            

            EndDrawing();
            Tm.UpdateTimer();
            //----------------------------------------------------------------------------------
        }
        
        
        //MAIN MENU ==================================================================================================================
        while( (screen==main_menu) and (!WindowShouldClose()) )
        {
            // Update
            //----------------------------------------------------------------------------------
            if ((CheckCollisionPointRec(GetMousePosition(), Play_button)) and IsMouseButtonPressed(MOUSE_LEFT_BUTTON)){
                screen = 2;
            }
            
            
            //----------------------------------------------------------------------------------
            
            // Draw
            //----------------------------------------------------------------------------------
            BeginDrawing();
            
                ClearBackground(RAYWHITE);
                // Draw the play button on the screen and turn black when pressed
                DrawRectangleRec(Play_button,(Color) {225,225,225,225});
                // Draw Text on the Main Menu screen 
                DrawText("PLAY", screenWidth/2.0f-25, screenHeight/2.0f-12, 20.0f, BLACK);
                

    
            EndDrawing();
            
            //----------------------------------------------------------------------------------
        }
        
        
        
    }

    // De-Initialization
    //--------------------------------------------------------------------------------------
    UnloadTexture(FB);
    UnloadTexture(P1);
    UnloadTexture(P2);
    CloseWindow();     // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
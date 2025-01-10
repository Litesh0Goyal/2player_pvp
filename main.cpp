#include <iostream>
#include "Headers\Map_Editor.h"
#include "Headers\Player_Obj.h"
#include "Headers\Colliders.h"
#include "Headers\NPO.h"
#include "Headers\Timers.h"
#include "raylib.h"
using namespace std;
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
    
    SetTargetFPS(60);
    
    int screen = 1; //current screen being displayed (Main menu parramiter)
    int main_menu = 1;//Main menu parramiter
    int play = 2;//Main menu parramiter
    
    Time Tm;
    
    MapEditor ME;//Map object
    
    Rectangle Player1Attack[Grid_Size_x] = {0};
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
        int P1Attack=0;
        int P2Attack=0;
        
        while( (screen==play) and (!WindowShouldClose()) )
        {
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
            
            if (IsKeyPressed(KEY_Q)){
                P1Attack = Grid_Size_x;
                Tm.StartTimer(2);
                ME.AttackHorizontal(Player1.Pos, Grid_Size_x, Block_Size,Player1Attack);
            }
            else if(IsKeyPressed(KEY_E)){
                P1Attack = Grid_Size_y;
                Tm.StartTimer(2);
                ME.AttackVertical(Player1.Pos, Grid_Size_y, Block_Size,Player1Attack);
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
                    DrawRectangleRec( Player1.Pos , RED);
                    DrawRectangleRec( Player2.Pos , BLUE);
                    
                    if ( not Tm.IsTimerUp()){                          
                        for(int x=0; x<P1Attack; x++){
                            DrawRectangleRec( Player1Attack[x] , RED);
                        }
                    }
                
                EndMode2D();
                
                ME.DeathScreen(&Player1, &Player2, screenWidth, screenHeight, Play_button);
            

            EndDrawing();
            Tm.UpdateTimer();
            //----------------------------------------------------------------------------------
        }
        
        
        
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
    CloseWindow();        // Close window and OpenGL context
    //--------------------------------------------------------------------------------------

    return 0;
}
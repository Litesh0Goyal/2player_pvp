#include "raylib.h"
#ifndef Player_Obj
#define Player_Obj
class PlayerObj
{
    private:
    bool Player_Movement = true;
    Rectangle Temp1  = {0.0f};
    Rectangle Temp2  = {0.0f};
    
    public:
    float Hp;
    float Mp;
    Rectangle Pos;
    
    PlayerObj(float hp,float mp,Rectangle pos){
    Hp = hp;
    Mp = mp;
    Pos = pos;
    }
    
    //enable and disable player movement
    void SetMovement(bool player_movement){
        Player_Movement = player_movement;
        return;
    }
    
    //decides player movement
    void GetMovement(PlayerObj *Player1,PlayerObj *Player2){
        Temp1  = Player1->Pos;
        Temp2  = Player2->Pos;
        if (Player_Movement == true){    // Player Movemnt Enable
                DisableCursor();
                // Playe1 Movement
                if (IsKeyPressed(KEY_A)) Player1->Pos.x -= 30;
                else if (IsKeyPressed(KEY_D)) Player1->Pos.x += 30;
                else if (IsKeyPressed(KEY_W)) Player1->Pos.y -= 30;
                else if (IsKeyPressed(KEY_S)) Player1->Pos.y += 30;
                // Player2 Movement
                if (IsKeyPressed(KEY_LEFT)) Player2->Pos.x -= 30;
                else if (IsKeyPressed(KEY_RIGHT)) Player2->Pos.x += 30;
                else if (IsKeyPressed(KEY_UP)) Player2->Pos.y -= 30;
                else if (IsKeyPressed(KEY_DOWN)) Player2->Pos.y += 30;
            }
        return;
    }
    
    void FixMovemet(PlayerObj *Player1, PlayerObj *Player2, int Grid_Size_x, int Grid_Size_y, int Block_Size){
            //Player1 collision
        if(Player1->Pos.x >= Grid_Size_x*Block_Size ) Player1->Pos.x -= 30;
        else if (Player1->Pos.x <= -30 ) Player1->Pos.x += 30;
        else if(Player1->Pos.y >= Grid_Size_y*Block_Size ) Player1->Pos.y -= 30;
        else if (Player1->Pos.y <= -30 ) Player1->Pos.y += 30;
            // Player2 collision
        if(Player2->Pos.x >= Grid_Size_x*Block_Size ) Player2->Pos.x -= 30;
        else if (Player2->Pos.x <= -30 ) Player2->Pos.x += 30;
        else if(Player2->Pos.y >= Grid_Size_y*Block_Size ) Player2->Pos.y -= 30;
        else if (Player2->Pos.y <= -30 ) Player2->Pos.y += 30;
            //Prevent Wall Collision
        if ((Player1->Pos.x == Player2->Pos.x)and(Player1->Pos.y == Player2->Pos.y)){
                Player1->Pos = Temp1;
                Player2->Pos = Temp2;
            }
    }
    
    //void DrawPlayerStat(){
    //    DrawText("Main Menu", screenWidth/2.0f-50, screenHeight/2.0f-12, 20.0f, BLACK);
    //}
};

#endif //Player_Obj
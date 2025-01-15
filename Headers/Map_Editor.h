#include <iostream>
#include "Player_Obj.h"
#include "raylib.h"
#ifndef Map_Editor
#define Map_Editor
using namespace std;
class MapEditor
{
    int screenWidth;
    int screenHeight;
    int Block_Size;
    int Grid_Size_x;
    int Grid_Size_y; 
    
    public:
        
    MapEditor(int SW, int SH, int BS, int Gx, int Gy){
    screenWidth = SW;
    screenHeight= SH;
    Block_Size  = BS;
    Grid_Size_x = Gx;
    Grid_Size_y = Gy;
    }
    void DeathScreen(PlayerObj *Player1, PlayerObj *Player2, Rectangle Play_button){
        if ((Player1->Hp <= 0)or(Player2->Hp <= 0)){// Death Screen
                    if (IsCursorHidden()) EnableCursor();//check if the curssor is on the screen
                    //change bg and print all the rectangles
                    DrawRectangle(0, 0, screenWidth, screenHeight, (Color){0,0,0,80});
                    DrawRectangle(screenWidth/2.0f-200,screenHeight/2.0f-100,400,200, (Color){200,200,200,200});
                    
                    // Button color change 
                    DrawRectangleRec(Play_button,(Color) {225,225,225,225});
                    
                    // player death text 
                    if (Player1->Hp <= 0)DrawText("PLAYER 2 WON", screenWidth/2.0f-80, screenHeight/2.0f-50, 20.0f, BLACK);
                    else if (Player2->Hp <= 0) DrawText("PLAYER 1 WON", screenWidth/2.0f-80, screenHeight/2.0f-50, 20.0f, BLACK);
                    DrawText("Main Menu", screenWidth/2.0f-50, screenHeight/2.0f-12, 20.0f, BLACK);
                }
        return;
    }
    
    // angels are(1,2,3,4,5,6,7,8) starting from ^ direction moving 45* each incriment  3 is > and 5 is V 7  is <.
    void AttackHorizontal(Rectangle pos, vector<Rectangle>& list, vector<int> angles){
        for(int angle : angles ){
            if(angle==1){//^^^
                for(int y=pos.y+1; y>=0; y--){
                    lsit[y] = (Rectangle){pos.x, y, Block_Size, Block_Size};
                }
            }
            else if(angle==2){
                int x = pos.x, y = pos.y, temp=0;
                while((x>(pos.x+pos.y))and(y>0)){
                    lsit[temp] = (Rectangle){x, y, Block_Size, Block_Size};
                    x--;
                    y--;
                    temp++;
                }
            }
            else if(angle==3){// >>>
                for(int x=pos.x+1; x<Grid_Size_x; x++){
                    lsit[x] = (Rectangle){x,pos.y, Block_Size, Block_Size};
                }
            }
            else if(angle==4){
                
            }
            else if(angle==5){// VVV
                for(int y=pos.y+1; y<Grid_Size_y; y++){
                    lsit[y] = (Rectangle){pos.x, y, Block_Size, Block_Size};
                }
            }
            else if(angle==6){
                
            }
            else if(angle==7){// <<<
                for(int x=pos.x+1; x>=0; x--){
                    lsit[x] = (Rectangle){x,pos.y, Block_Size, Block_Size};
                }
            }
            else if(angle==8){
                
            }
        }
    }

};

#endif //Map_Editor
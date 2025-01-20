#include <iostream>
#include <vector>
#include "Player_Obj.h"
#include "raylib.h"
#ifndef Map_Editor
#define Map_Editor
using std::vector;
class MapEditor
{
    float screenWidth;
    float screenHeight;
    float Block_Size;
    float Grid_Size_x;
    float Grid_Size_y; 
    
    public:
        
    MapEditor(float SW, float SH, float BS, float Gx, float Gy){
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
    void AttackLine(Rectangle pos, vector<Rectangle>& list, vector<int> angles){
        pos.y = pos.y/Block_Size;
        pos.x = pos.x/Block_Size;
        for(int i=0; i < (int)angles.size(); i++ ){
            if(angles.at(i)==1){//^^^ N
                int temp=0;
                for(float y=pos.y; y>=0; y--){
                    list.push_back((Rectangle){pos.x*Block_Size, y*Block_Size, Block_Size, Block_Size});
                    temp++;
                }
            }
            else if(angles.at(i)==2){//NE
                float x = pos.x, y = pos.y, temp=0;
                std::cout<<x<<y<<std::endl;
                while((x<=(pos.x+pos.y))and(y>=0)){
                    list.push_back((Rectangle){x*Block_Size, y*Block_Size, Block_Size, Block_Size});
                    x++;
                    y--;
                    temp++;
                }
            }
            else if(angles.at(i)==3){// >>> E
                int temp=0;
                for(float x=pos.x+1; x<Grid_Size_x; x++){
                    list.push_back((Rectangle){x*Block_Size,pos.y*Block_Size, Block_Size, Block_Size});
                    temp++;
                }
            }
            else if(angles.at(i)==4){//SE
                float x = pos.x, y = pos.y, temp=0;
                while((x<=pos.x+(Grid_Size_y-pos.y))and(y<Grid_Size_y)){
                    list.push_back((Rectangle){x*Block_Size, y*Block_Size, Block_Size, Block_Size});
                    x++;
                    y++;
                    temp++;
                }
            }
            else if(angles.at(i)==5){// VVV S
                int temp=0;
                for(float y=pos.y+1; y<Grid_Size_y; y++){
                    list.push_back((Rectangle){pos.x*Block_Size, y*Block_Size, Block_Size, Block_Size});
                    temp++;
                }
            }
            else if(angles.at(i)==6){//SW
                float x = pos.x, y = pos.y, temp=0;
                while((x>=(pos.x-(Grid_Size_y-pos.y)))and(y<Grid_Size_y)){
                    list.push_back((Rectangle){x*Block_Size, y*Block_Size, Block_Size, Block_Size});
                    x--;
                    y++;
                    temp++;
                }
            }
            else if(angles.at(i)==7){// <<< W
                int temp=0;
                for(float x=pos.x+1; x>=0; x--){
                    list.push_back((Rectangle){x*Block_Size,pos.y*Block_Size, Block_Size, Block_Size});
                    temp++;
                }
            }
            else if(angles.at(i)==8){//NW
                float x = pos.x, y = pos.y, temp=0;
                while((x>=(pos.x-pos.y))and(y>=0)){
                    list.push_back((Rectangle){x*Block_Size, y*Block_Size, Block_Size, Block_Size});
                    x--;
                    y--;
                    temp++;
                }
            }
        }
    }

};

#endif //Map_Editor
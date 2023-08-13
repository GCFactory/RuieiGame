#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <vector>
#include <cmath>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

using namespace std;

class Position{
protected:
    int ver_pos;
    int hor_pos;
public:
    Position(int init_hor_pos,int init_ver_pos){
        if ((init_hor_pos<0)||(init_ver_pos<0))
            return;
        ver_pos=init_ver_pos;
        hor_pos=init_hor_pos;
    }
    ~Position(){}
    void SetHorPos(int new_hor_pos){
        if (new_hor_pos<0){
            cout<<"The value of horizontal position is negative ("<<new_hor_pos<<")! Position wasn't set!\n";
            return;
        }
        hor_pos=new_hor_pos;
    }
    void SetVerPos(int new_ver_pos){
        if (new_ver_pos<0){
            cout<<"The value of vertical position is negative ("<<new_ver_pos<<")! Position wasn't set!\n";
            return;
        }
        ver_pos=new_ver_pos;
    }
    int GetHorPos(){
        return hor_pos;
    }
    int GetVerPos(){
        return ver_pos;
    }
    void PrintPosition(){
        cout<<"Horizontal position: "<<hor_pos<<";\nVertical position: "<<ver_pos<<";\n";
    }
};

class Object{
protected:
    int id;
public:
    Object(int init_id){
        if (init_id<0){
            cout<<"Id is negative ("<<init_id<<")! Id wasn't set!\n";
            return;
        }
        id=init_id;
    }
    ~Object(){}
    void SetId(int new_id){
        if (new_id<0){
            cout<<"New id is negative ("<<new_id<<")! Id wasn't set!\n";
            return;
        }
        id=new_id;
    }
    int GetId(){
        return id;
    }
    void PrintObject(){
        cout<<"Id: "<<id<<";\n";
    }
};

class Room: public Object, public Position{
public:
    Room(int init_id,int init_hor_pos,int init_ver_pos):Object(init_id),Position(init_hor_pos,init_ver_pos){}
    ~Room(){}
    void PrintRoom(){
        cout<<"Room:\n";
        this->PrintObject();
        this->PrintPosition();
    }
};

class Tunel: public Object,public Position{
private:
    string available_direction[2]={"VERTICAL","HORIZONTAL"};
protected:
    string direction;
public:
    Tunel(int init_id,int init_hor_pos,int init_ver_pos,string init_direction):Object(init_id),Position(init_hor_pos,init_ver_pos){
        SetDirection(init_direction);
    }
    ~Tunel(){}
    void SetDirection(string new_direction){
        if (CheckDirection(new_direction)!=true){
            cout<<"Direction isn't available ("<<new_direction<<")! Direction wasn't set!\n";
            return;
        }
        direction=new_direction;
    }
    string GetDirection(){
        return direction;
    }
    bool CheckDirection(string new_direction){
        if (new_direction=="")
            return false;
        for (int i=0;i<sizeof(available_direction)/sizeof(available_direction[0]);i++)
            if (new_direction.compare(available_direction[i])==0)
                return true;
        return false;
    }
    void PrintTunel(){
        cout<<"Tunel:\n";
        this->PrintObject();
        this->PrintPosition();
        cout<<"Direction: "<<direction<<";\n";
    }
    bool CheckDirectionSide(int neighbor_hor_pos,int neighbor_ver_pos){
        if (((hor_pos==neighbor_hor_pos+1)&&(ver_pos==neighbor_ver_pos+1))||((hor_pos==neighbor_hor_pos-1)&&(ver_pos==neighbor_ver_pos-1))||((hor_pos==neighbor_hor_pos)&&(ver_pos==neighbor_ver_pos))){
            cout<<"Tunel can't has neigbour with this coordinates ("<<neighbor_hor_pos<<";"<<neighbor_ver_pos<<")!\n Direction side wasn't check!\n";
            return false;
        }
        if(((hor_pos==neighbor_hor_pos)&&((ver_pos==neighbor_ver_pos+1)||(ver_pos==neighbor_ver_pos-1))&&(direction!=available_direction[0]))||((ver_pos==neighbor_ver_pos)&&((hor_pos==neighbor_hor_pos-1)||(hor_pos==neighbor_hor_pos+1))&&(direction!=available_direction[1]))){
            cout<<"Tunel has uncorrect side of direction!\n";
            return false;
        }
        return true;
    }
};

class Dungeon{
protected:
    int size_of_dungeon;
    int** map=NULL;//0-available for build,1-room,2-tunel,-1-fog of war,-2-blocked,-3-border,-4-atack,-5-closed
    vector<Room> rooms{};
    vector<Tunel> tunels{};
    int radius;
public:
    Dungeon(int init_size_of_dungeon){
        if (init_size_of_dungeon<=0){
            cout<<"Size of dungeon is negative or equal zero! Dungeon wasn't create!\n";
            size_of_dungeon=0;
            return;
        }
        size_of_dungeon=init_size_of_dungeon*2+1;
        map=CreateMap(size_of_dungeon);
        if (map!=NULL){
            SetRadius(0);
            SetClosedTerritory();
            SetBorder();
            SetFogOfWar();
            SetBlockedTunels();
            AddRoom(init_size_of_dungeon,init_size_of_dungeon);
        }
    }
    ~Dungeon(){
        if (map!=NULL){
            for (int i=0;i<size_of_dungeon;i++)
                delete[] map[i];
            delete[] map;
        }
        if (rooms.size()>0){
            while (rooms.size()>0)
                rooms.pop_back();
        }
    }

    int** CreateMap(int size_of_dungeon){
        if (size_of_dungeon<=0){
            cout<<"Size of dungeon is negative or equal zero! Map wasn't create!\n";
            return NULL;
        }
        int** new_map=new int*[size_of_dungeon];
        for (int i=0;i<size_of_dungeon;i++){
            new_map[i]=new int[size_of_dungeon];
            for (int j=0;j<size_of_dungeon;j++)
                new_map[i][j]=0;
        }
        return new_map;
    }
    int** GetMap(){
        return map;
    }
    void SetMap(int** new_map){
        map=new_map;
    }

    void SetSizeOfDungeon(int new_size_of_dungeon){
        size_of_dungeon=new_size_of_dungeon;
    }
    int GetSizeOfDungeon(){
        return size_of_dungeon;
    }

    int GetRandom(int min,int max){
        return min+rand()%(max-min+1);
    }

    void SetRadius(int new_radius){
        if ((new_radius<0)||((size_of_dungeon-1)/2)<new_radius){
            cout<<"Radius has uncorrect value!Radius wasn't set!\n";
            return;
        }
        radius=new_radius;
    }
    int GetRadius(){
        return radius;
    }
    void ExpandRadius(){
        if (CheckPosibilityOfExpandRadius()==false)
            return;
        SetClosedTerritory();
        SetBorder();
        SetFogOfWar();
        SetBlockedRoom();
        SetBlockedTunels();
    }
    bool CheckPosibilityOfExpandRadius(){
        int new_radius=radius+1;
        int number_of_rooms=1;
        if (new_radius>1){
            for (int i=1;i<=radius;i++)
                number_of_rooms+=(2*i+1)*2+(2*(i-1)+1)*2;
            cout<<"number_of_rooms:"<<number_of_rooms<<endl;
            if (rooms.size()!=number_of_rooms){
                cout<<"All roons wasn't unlocked! Expand can't be maked!\n";
                return false;
            }
        }   
        SetRadius(new_radius);
        return true;
    }

    void SetBlockedRoom(){
        int choice=GetRandom(0,3);
        if (choice==0)
            map[(size_of_dungeon-1)/2-2*radius][(size_of_dungeon-1)/2-2*radius]=-2;
        else if (choice==1)
            map[(size_of_dungeon-1)/2-2*radius][(size_of_dungeon-1)/2+2*radius]=-2;
        else if (choice==2)
            map[(size_of_dungeon-1)/2+2*radius][(size_of_dungeon-1)/2-2*radius]=-2;
        else
            map[(size_of_dungeon-1)/2+2*radius][(size_of_dungeon-1)/2+2*radius]=-2;
    }

    void SetFogOfWar(){
        for (int i=(size_of_dungeon-1)/2-2*radius;i<=(size_of_dungeon-1)/2+2*radius;i++)
            for(int j=(size_of_dungeon-1)/2-2*radius;j<=(size_of_dungeon-1)/2+2*radius;j++)
                if ((map[j][i]<=0)&&(map[j][i]!=-2))
                    map[j][i]=-1;
    }
    void SetBorder(){
        for (int i=(size_of_dungeon-1)/2-1-2*radius;i<=(size_of_dungeon-1)/2+1+2*radius;i++)
            for(int j=(size_of_dungeon-1)/2-1-2*radius;j<=(size_of_dungeon-1)/2+1+2*radius;j++)
                if (map[j][i]<=0)
                    map[j][i]=-3;
    }
    void SetClosedTerritory(){
        for (int i=0;i<size_of_dungeon;i++)
            for(int j=0;j<size_of_dungeon;j++)
                if (map[j][i]<1)
                    map[j][i]=-5;
    }
    bool CheckPosibilityOfBlockingTunel(int hor_pos,int ver_pos){
        map[hor_pos][ver_pos]=-2;
        if (hor_pos%2==1){
            if ((CheckRoomReachability(hor_pos,ver_pos-1,hor_pos,ver_pos)==false)||(CheckRoomReachability(hor_pos,ver_pos+1,hor_pos,ver_pos)==false)){
                map[hor_pos][ver_pos]=-1;
                return false;
            }
        }
        else{
            if ((CheckRoomReachability(hor_pos-1,ver_pos,hor_pos,ver_pos)==false)||(CheckRoomReachability(hor_pos+1,ver_pos,hor_pos,ver_pos)==false)){
                map[hor_pos][ver_pos]=-1;
                return false;
            }
        }
        return true;
    }
    bool CheckRoomReachability(int room_hor_pos,int room_ver_pos,int tunel_hor_pos,int tunel_ver_pos){
        if (((map[room_hor_pos-1][room_ver_pos]==-2)||(map[room_hor_pos-1][room_ver_pos]==-3))
            &&((map[room_hor_pos+1][room_ver_pos]==-2)||(map[room_hor_pos+1][room_ver_pos]==-3))
            &&((map[room_hor_pos][room_ver_pos-1]==-2)||(map[room_hor_pos][room_ver_pos-1]==-3))
            &&((map[room_hor_pos][room_ver_pos+1]==-2)||(map[room_hor_pos][room_ver_pos+1]==-3)))
            return false;
        if ((map[room_hor_pos-1][room_ver_pos]==-1)&&((((room_hor_pos-1)!=tunel_hor_pos)&&(room_ver_pos==tunel_ver_pos))||(room_ver_pos!=tunel_ver_pos))){
            if (map[room_hor_pos-2][room_ver_pos]==1)
                return true;
            else if (CheckRoomReachability(room_hor_pos-2,room_ver_pos,room_hor_pos-1,room_ver_pos)==true)
                return true;
        }
        if ((map[room_hor_pos+1][room_ver_pos]==-1)&&(((room_hor_pos+1)!=tunel_hor_pos)&&(room_ver_pos==tunel_ver_pos)||(room_ver_pos!=tunel_ver_pos))){
            if (map[room_hor_pos+2][room_ver_pos]==1)
                return true;
            else if (CheckRoomReachability(room_hor_pos+2,room_ver_pos,room_hor_pos+1,room_ver_pos)==true)
                return true;
        }
        if ((map[room_hor_pos][room_ver_pos-1]==-1)&&((room_hor_pos==tunel_hor_pos)&&((room_ver_pos-1)!=tunel_ver_pos)||(room_hor_pos!=tunel_hor_pos))){
            if (map[room_hor_pos][room_ver_pos-2]==1)
                return true;
            else if (CheckRoomReachability(room_hor_pos,room_ver_pos-2,room_hor_pos,room_ver_pos-1)==true)
                return true;
        }
        if ((map[room_hor_pos][room_ver_pos+1]==-1)&&((room_hor_pos==tunel_hor_pos)&&((room_ver_pos+1)!=tunel_ver_pos)||(room_hor_pos!=tunel_hor_pos))){
            if (map[room_hor_pos][room_ver_pos+2]==1)
                return true;
            else if (CheckRoomReachability(room_hor_pos,room_ver_pos+2,room_hor_pos,room_ver_pos+1)==true)
                return true;
        }
        return false;
    }
    void SetBlockedTunels(){
        srand(time(NULL));
        SetBlockedTunelsInner();
        SetBlockedTunelsOuter();
    }
    void SetBlockedTunelsOuter(){
        int max_blocked=GetRandom(int(floor((radius*2+1)/4)),int(floor((radius*2+1)/2))*2);
        int number_of_blocked_horizontal_tunles=max_blocked;
        int number_of_blocked_vertical_tunles=max_blocked;

        int number_of_tunels=4*radius;
        while (number_of_blocked_horizontal_tunles>0){
            if(GetRandom(0,1)==1){
                for (int i=(size_of_dungeon-1)/2-2*radius+1;i<=(size_of_dungeon-1)/2+2*radius-1;i+=2)
                    if ((GetRandom(0,1)==1)&&(number_of_blocked_horizontal_tunles>0)&&(map[i][(size_of_dungeon-1)/2-2*radius]!=-2)&&(CheckPosibilityOfBlockingTunel(i,(size_of_dungeon-1)/2-2*radius)==true)){
                        map[i][(size_of_dungeon-1)/2-2*radius]=-2;
                        number_of_blocked_horizontal_tunles--;
                    }
                }
            else{
                for (int i=(size_of_dungeon-1)/2-2*radius+1;i<=(size_of_dungeon-1)/2+2*radius-1;i+=2)
                    if ((GetRandom(0,1)==1)&&(number_of_blocked_horizontal_tunles>0)&&(map[i][(size_of_dungeon-1)/2+2*radius]!=-2)&&(CheckPosibilityOfBlockingTunel(i,(size_of_dungeon-1)/2+2*radius)==true)){
                        map[i][(size_of_dungeon-1)/2+2*radius]=-2;
                        number_of_blocked_horizontal_tunles--;
                    }
                }
        }
        while(number_of_blocked_vertical_tunles>0){
            if (GetRandom(0,1)==1){
                for (int i=(size_of_dungeon-1)/2-2*radius+1;i<=(size_of_dungeon-1)/2+2*radius-1;i+=2)
                    if ((GetRandom(0,1)==1)&&(number_of_blocked_vertical_tunles>0)&&(map[(size_of_dungeon-1)/2-2*radius][i]!=-2)&&(CheckPosibilityOfBlockingTunel((size_of_dungeon-1)/2-2*radius,i)==true)){
                        map[(size_of_dungeon-1)/2-2*radius][i]=-2;
                        number_of_blocked_vertical_tunles--;
                    }
                }
            else{
                for (int i=(size_of_dungeon-1)/2-2*radius+1;i<=(size_of_dungeon-1)/2+2*radius-1;i+=2)
                    if ((GetRandom(0,1)==1)&&(number_of_blocked_vertical_tunles>0)&&(map[(size_of_dungeon-1)/2+2*radius][i]!=-2)&&(CheckPosibilityOfBlockingTunel((size_of_dungeon-1)/2+2*radius,i)==true)){
                        map[int((size_of_dungeon-1)/2+2*radius)][i]=-2;
                        number_of_blocked_vertical_tunles--;
                    }
                }
        }
    }
    void SetBlockedTunelsInner(){
        int max_blocked;
        if (radius>0)
            max_blocked=GetRandom(radius-1,(radius-1)*2);
        else
            max_blocked=GetRandom(0,(radius-1)*2);
        int number_of_blocked_horizontal_tunles=max_blocked;
        int number_of_blocked_vertical_tunles=max_blocked;

        int number_of_tunels=1+radius*2;
        while(number_of_blocked_horizontal_tunles>0){
            if (GetRandom(0,1)==1){
                for(int i=(size_of_dungeon-1)/2-2*radius+2;i<=(size_of_dungeon-1)/2+2*radius-2;i+=2)
                    if ((GetRandom(0,1)==1)&&(number_of_blocked_horizontal_tunles>0)&&(map[i][(size_of_dungeon-1)/2-2*radius+1]!=-2)&&(CheckPosibilityOfBlockingTunel(i,(size_of_dungeon-1)/2-2*radius+1)==true)){
                        map[i][(size_of_dungeon-1)/2-2*radius+1]=-2;
                        number_of_blocked_horizontal_tunles--;
                    }
                }
            else{
                for(int i=(size_of_dungeon-1)/2-2*radius+2;i<=(size_of_dungeon-1)/2+2*radius-2;i+=2)
                    if ((GetRandom(0,1)==1)&&(number_of_blocked_horizontal_tunles>0)&&(map[i][(size_of_dungeon-1)/2+2*radius+1]!=-2)&&(CheckPosibilityOfBlockingTunel(i,(size_of_dungeon-1)/2+2*radius-1)==true)){
                        map[i][(size_of_dungeon-1)/2+2*radius-1]=-2;
                        number_of_blocked_horizontal_tunles--;
                    }
                }
        }
        while (number_of_blocked_vertical_tunles>0){
            if (GetRandom(0,1)==1){
                for(int i=(size_of_dungeon-1)/2-2*radius+2;i<=(size_of_dungeon-1)/2+2*radius-2;i+=2)
                    if ((GetRandom(0,1)==1)&&(number_of_blocked_vertical_tunles>0)&&(map[(size_of_dungeon-1)/2-2*radius+1][i]!=-2)&&(CheckPosibilityOfBlockingTunel((size_of_dungeon-1)/2-2*radius+1,i)==true)){
                        map[(size_of_dungeon-1)/2-2*radius+1][i]=-2;
                        number_of_blocked_vertical_tunles--;
                    }
                }
            else{
                for(int i=(size_of_dungeon-1)/2-2*radius+2;i<=(size_of_dungeon-1)/2+2*radius-2;i+=2)
                    if ((GetRandom(0,1)==1)&&(number_of_blocked_vertical_tunles>0)&&(map[(size_of_dungeon-1)/2+2*radius+1][i]!=-2)&&(CheckPosibilityOfBlockingTunel((size_of_dungeon-1)/2+2*radius-1,i)==true)){
                        map[(size_of_dungeon-1)/2+2*radius-1][i]=-2;
                        number_of_blocked_vertical_tunles--;
                    }
                }   
        }
    }

    void SetBuildResume(){
        for (int i=(size_of_dungeon-1)/2-radius*2;i<=(size_of_dungeon-1)/2+radius*2;i++)
            for(int j=(size_of_dungeon-1)/2-radius*2;j<=(size_of_dungeon-1)/2+radius*2;j++)
                if ((map[i][j]==-1)&&(((map[i-1][j]==1)||(map[i+1][j]==1)||(map[i][j-1]==1)||(map[i][j+1]==1))||
                    (((map[i-1][j]==2)&&(FindTunel(i-1,j)->GetDirection()=="HORIZONTAL")))||
                    ((map[i+1][j]==2)&&(FindTunel(i+1,j)->GetDirection()=="HORIZONTAL"))||
                    ((map[i][j-1]==2)&&(FindTunel(i,j-1)->GetDirection()=="VERTICAL"))||
                    ((map[i][j+1]==2)&&(FindTunel(i,j+1)->GetDirection()=="VERTICAL"))))
                    map[i][j]=0;
    }
    bool CheckRoomForExternal(int hor_pos,int ver_pos){
        if ((map[hor_pos-1][ver_pos]>0)&&(map[hor_pos+1][ver_pos]>0)&&(map[hor_pos][ver_pos-1]>0)&&(map[hor_pos][ver_pos+1]>0))
            return false;
        return true;
    }
    void SetAtackPortals(){
        //-4 - атаки
        srand(time(NULL));
        int number_of_atack=0;
        for (int i=(size_of_dungeon-1)/2-2*radius;i<(size_of_dungeon-1)/2+2*radius;i+=2)
            for (int j=(size_of_dungeon-1)/2-2*radius;j<(size_of_dungeon-1)/2+2*radius;j+=2)
                if ((CheckRoomForExternal(i,j)==true)&&(map[i][j]==1))
                    number_of_atack++;
        number_of_atack=floor(number_of_atack/2)+radius+1;
        while(number_of_atack>0){
            for (int i=(size_of_dungeon-1)/2-2*radius;i<=(size_of_dungeon-1)/2+2*radius;i++){
                for (int j=(size_of_dungeon-1)/2-2*radius;j<=(size_of_dungeon-1)/2+2*radius;j++){
                    if ((map[i][j]==1)&&(CheckRoomForExternal(i,j)==true)){
                        if ((map[i-1][j]==-1)||(map[i-1][j]==-3)){
                            bool flag=false;
                            for (int k=i-1;k>=(size_of_dungeon-1)/2-2*radius-1;k--){
                                if(map[k][j]==-3){
                                    flag=true;
                                    break;
                                }
                                else if ((map[k][j]==-2)||(map[k][j]==1)||(map[k][j]==2)||(map[k][j]==-4))
                                    break;
                            }
                            if ((flag==true)&&(number_of_atack>0)&&(GetRandom(0,number_of_atack)==number_of_atack)){
                                number_of_atack--;
                                map[i-1][j]=-4;
                            }
                        }
                        if ((map[i+1][j]==-1)||(map[i+1][j]==-3)){
                            bool flag=false;
                            for (int k=i+1;k<=(size_of_dungeon-1)/2+2*radius+1;k++){
                                if(map[k][j]==-3){
                                    flag=true;
                                    break;
                                }
                                else if ((map[k][j]==-2)||(map[k][j]==1)||(map[k][j]==2)||(map[k][j]==-4))
                                    break;
                            }
                            if ((flag==true)&&(number_of_atack>0)&&(GetRandom(0,number_of_atack)==number_of_atack)){
                                number_of_atack--;
                                map[i+1][j]=-4;
                            }
                        }
                        if ((map[i][j-1]==-1)||(map[i][j-1]==-3)){
                            bool flag=false;
                            for (int k=j-1;k>=(size_of_dungeon-1)/2-2*radius-1;k--){
                                if(map[i][k]==-3){
                                    flag=true;
                                    break;
                                }
                                else if ((map[i][k]==-2)||(map[i][k]==1)||(map[i][k]==2)||(map[i][k]==-4))
                                    break;
                            }
                            if ((flag==true)&&(number_of_atack>0)&&(GetRandom(0,number_of_atack)==number_of_atack)){
                                number_of_atack--;
                                map[i][j-1]=-4;
                            }
                        }
                        if ((map[i][j-1]==-1)||(map[i][j-1]==-3)){
                            bool flag=false;
                            for (int k=j+1;k<=(size_of_dungeon-1)/2+2*radius+1;k++){
                                if(map[i][k]==-3){
                                    flag=true;
                                    break;
                                }
                                else if ((map[i][k]==-2)||(map[i][k]==1)||(map[i][k]==2)||(map[i][k]==-4))
                                    break;
                            }
                            if ((flag==true)&&(number_of_atack>0)&&(GetRandom(0,number_of_atack)==number_of_atack)){
                                number_of_atack--;
                                map[i][j+1]=-4;
                            }
                        }
                    }
                    if (map[i][j]==2){
                        if (FindTunel(i,j)->GetDirection()=="HORIZONTAL"){
                            if (map[i-1][j]==-1){
                                bool flag=false;
                                for (int k=i-1;k>=(size_of_dungeon-1)/2-2*radius-1;k--){
                                    if(map[k][j]==-3){
                                        flag=true;
                                        break;
                                    }
                                    else if ((map[k][j]==-2)||(map[k][j]==1)||(map[k][j]==2)||(map[k][j]==-4))
                                        break;
                                }
                                if ((flag==true)&&(number_of_atack>0)&&(GetRandom(0,number_of_atack)==number_of_atack)){
                                    number_of_atack--;
                                    map[i-1][j]=-4;
                                }
                            }
                            if (map[i+1][j]==-1){
                                bool flag=false;
                                for (int k=i+1;k<=(size_of_dungeon-1)/2+2*radius+1;k++){
                                    if(map[k][j]==-3){
                                        flag=true;
                                        break;
                                    }
                                    else if ((map[k][j]==-2)||(map[k][j]==1)||(map[k][j]==2)||(map[k][j]==-4))
                                        break;
                                }
                                if ((flag==true)&&(number_of_atack>0)&&(GetRandom(0,number_of_atack)==number_of_atack)){
                                    number_of_atack--;
                                    map[i+1][j]=-4;
                                }   
                            }
                        }
                        if (FindTunel(i,j)->GetDirection()=="VERTICAL"){
                            if (map[i][j-1]==-1){
                                bool flag=false;
                                for (int k=j+1;k<=(size_of_dungeon-1)/2+2*radius+1;k++){
                                    if(map[i][k]==-3){
                                        flag=true;
                                        break;
                                    }
                                    else if ((map[i][k]==-2)||(map[i][k]==1)||(map[i][k]==2)||(map[i][k]==-4))
                                        break;
                                }
                                if ((flag==true)&&(number_of_atack>0)&&(GetRandom(0,number_of_atack)==number_of_atack)){
                                    number_of_atack--;
                                    map[i][j+1]=-4;
                                }
                            }
                            if (map[i][j+1]==-1){
                                bool flag=false;
                                for (int k=j-1;k>=(size_of_dungeon-1)/2-2*radius-1;k--){
                                    if(map[i][k]==-3){
                                        flag=true;
                                        break;
                                    }
                                    else if ((map[i][k]==-2)||(map[i][k]==1)||(map[i][k]==2)||(map[i][k]==-4))
                                        break;
                                }
                                if ((flag==true)&&(number_of_atack>0)&&(GetRandom(0,number_of_atack)==number_of_atack)){
                                    number_of_atack--;
                                    map[i][j-1]=-4;
                                }
                            }
                        }
                    }                        
                }
            }
        }
    }

    int GetMaxRoomId(){
        int max_id=0;
        for (int i=0;i<rooms.size();i++)
            if (rooms[i].GetId()>max_id)
                max_id=rooms[i].GetId();
        return max_id;
    }
    Room* FindRoom(int hor_pos,int ver_pos){
        for (int i=0;i<rooms.size();i++)
            if ((rooms[i].GetHorPos()==hor_pos)&&(rooms[i].GetVerPos()==ver_pos))
                return &rooms[i];
        return NULL;
    }
    Room* FindRoom(int room_id){
        for (int i=0;i<rooms.size();i++)
            if (rooms[i].GetId()==room_id)
                return &rooms[i];
        return NULL;
    }
    bool CheckRoomExisting(int hor_pos,int ver_pos){
        if ((hor_pos<0)||(ver_pos<0)){
            cout<<"Room has uncorrect coordinates! Room wasn't create and add!\n";
            return true;
        }
        if (FindRoom(hor_pos,ver_pos)!=NULL){
            cout<<"Room with this coordinates is exist! New room wasn't create and add!\n";
            return true;
        }
        return false;
    }
    bool CheckRoomCoordinates(int hor_pos,int ver_pos){
        if ((hor_pos%2==0)||(ver_pos%2==0)){
            cout<<"Room can't be plaised with this coordinates ("<<hor_pos<<";"<<ver_pos<<")!Coordinates should be odd!\n";
            return false;
        }
        if ((rooms.size()>0)&&((CheckRoomNeighbors(hor_pos,ver_pos)==false)||(map[hor_pos][ver_pos]!=0))){
            cout<<"Room hasn't got neigbours! It can't be plaised on this coordinates!\n";
            return false;
        }
        if (map[hor_pos][ver_pos]==-2){
            cout<<"Room is blocked!\n";
            return false;
        }
        return true;
    }
    bool CheckRoomNeighbors(int hor_pos,int ver_pos){
        if ((FindTunel(hor_pos-1,ver_pos)!=NULL)||(FindTunel(hor_pos+1,ver_pos)!=NULL)||(FindTunel(hor_pos,ver_pos-1)!=NULL)||(FindTunel(hor_pos,ver_pos+1)!=NULL))
            return true;
        return false;
    }
    bool CheckOfPosibilityOfUnlockingRoom(){
        int number_of_rooms=1;
        for (int i=1;i<=radius;i++)
            number_of_rooms+=(2*i+1)*2+(2*(i-1)+1)*2;
        if (rooms.size()+1==number_of_rooms)
            return true;
        return false;
    }
    void UnlockingBlocedRoom(){
        if (map[(size_of_dungeon-1)/2-2*radius][(size_of_dungeon-1)/2-2*radius]==-2)
            map[(size_of_dungeon-1)/2-2*radius][(size_of_dungeon-1)/2-2*radius]=-1;
        else if (map[(size_of_dungeon-1)/2-2*radius][(size_of_dungeon-1)/2+2*radius]==-2)
            map[(size_of_dungeon-1)/2-2*radius][(size_of_dungeon-1)/2+2*radius]=-1;
        else if (map[(size_of_dungeon-1)/2+2*radius][(size_of_dungeon-1)/2-2*radius]==-2)
            map[(size_of_dungeon-1)/2+2*radius][(size_of_dungeon-1)/2-2*radius]=-1;
        else if (map[(size_of_dungeon-1)/2+2*radius][(size_of_dungeon-1)/2+2*radius]==-2)
            map[(size_of_dungeon-1)/2+2*radius][(size_of_dungeon-1)/2+2*radius]=-1;
    }
    void AddRoom(int hor_pos,int ver_pos){
        if (CheckRoomExisting(hor_pos,ver_pos)==true){
            cout<<"Room wasn't create and add!\n";
            return;
        }
        if (CheckRoomCoordinates(hor_pos,ver_pos)==false){
            cout<<"Room try to set on uncorrect place! Room wasn't create and add!\n";
            return;
        }
        Room new_room(GetMaxRoomId()+1,hor_pos,ver_pos);
        rooms.push_back(new_room);
        map[hor_pos][ver_pos]=1;
        if (CheckOfPosibilityOfUnlockingRoom()==true)
            UnlockingBlocedRoom();
        SetFogOfWar();
    }
    void AddRoom(int id,int hor_pos,int ver_pos){
        if (id<0){
            cout<<"Room has uncorrect id! Room wasn't create and add!\n";
            return;
        }
        if (CheckRoomExisting(hor_pos,ver_pos)==true){
            cout<<"Room wasn't create and add!\n";
            return;
        }
        if (FindRoom(id)!=NULL){
            cout<<"Room with this id is exist! Room wasn't create and add!\n";
            return;
        }
        if (CheckRoomCoordinates(hor_pos,ver_pos)==false){
            cout<<"Room try to set on uncorrect place! Room wasn't create and add!\n";
            return;
        }

        Room new_room(id,hor_pos,ver_pos);
        rooms.push_back(new_room);
        map[hor_pos][ver_pos]=1;
        if (CheckOfPosibilityOfUnlockingRoom()==true)
            UnlockingBlocedRoom();
        SetFogOfWar();
    }
    
    int GetMaxTunelId(){
        int max_id=0;
        for (int i=0;i<tunels.size();i++)
            if (tunels[i].GetId()>max_id)
                max_id=tunels[i].GetId();
        return max_id;
    }
    Tunel* FindTunel(int id){
        for (int i=0;i<tunels.size();i++)
            if (tunels[i].GetId()==id)
                return &tunels[i];
        return NULL;
    }
    Tunel* FindTunel(int hor_pos,int ver_pos){
        for (int i=0;i<tunels.size();i++)
            if((tunels[i].GetHorPos()==hor_pos)&&(tunels[i].GetVerPos()==ver_pos))
                return &tunels[i];
        return NULL;
    }
    bool CheckTunelExisting(int hor_pos,int ver_pos){
        if ((hor_pos<0)||(ver_pos<0)){
            cout<<"Tunel has uncorrect position! Tunel wasn't create and add!\n";
            return false;
        }
        if (FindTunel(hor_pos,ver_pos)!=NULL){
            cout<<"Tunel with this coordinates is exist! Tunel wasn't create and add!\n";
            return false;
        }
        if (CheckTunelCoordinates(hor_pos,ver_pos)==false){
            cout<<"Tunel wasn't create and add!\n";
            return false;
        }
        return true;
    }
    bool CheckTunelCoordinates(int hor_pos,int ver_pos){
        if (((hor_pos%2==0)&&(ver_pos%2==0))||((hor_pos%2==1)&&(ver_pos%2==1))){
            cout<<"Tunel can't be plaised with this coordinates ("<<hor_pos<<";"<<ver_pos<<")!One coordinate should be odd, another should be even!\n";
            return false;
        }
        if (CheckTunelNeighbours(hor_pos,ver_pos)==false){
            cout<<"Tunel hasn't got neigbours! It can't be plaised on this coordinates ("<<hor_pos<<";"<<ver_pos<<")!\n";
            return false;
        }
        return true;
    }
    bool CheckTunelNeighbours(int hor_pos,int ver_pos){
        if ((FindRoom(hor_pos-1,ver_pos)!=NULL)||(FindRoom(hor_pos+1,ver_pos)!=NULL)||(FindRoom(hor_pos,ver_pos-1)!=NULL)||(FindRoom(hor_pos,ver_pos+1)!=NULL))
            return true;
        return false;
    }
    vector<Room> GetTunelNeighbours(int hor_pos,int ver_pos){
        vector<Room> tunel_neigbours{};
        for (int i=0;i<rooms.size();i++)
            if (((hor_pos==rooms[i].GetHorPos())&&((ver_pos==rooms[i].GetVerPos()+1)||(ver_pos==rooms[i].GetVerPos()-1)))||((ver_pos==rooms[i].GetVerPos())&&((hor_pos==rooms[i].GetHorPos()-1)||(hor_pos==rooms[i].GetHorPos()+1))))
                tunel_neigbours.push_back(rooms[i]);
        return tunel_neigbours;
    }
    void AddTunel(int hor_pos,int ver_pos,string direction){
        if (CheckTunelExisting(hor_pos,ver_pos)==false)
            return;
        if (map[hor_pos][ver_pos]!=0){
            cout<<"Tunel try to set on uncorrect place! Tunel wasn't create and add!\n";
            return;
        }
        Tunel new_tunel(GetMaxTunelId()+1,hor_pos,ver_pos,direction);
        if ((new_tunel.CheckDirection(direction)==false)||(new_tunel.CheckDirectionSide(GetTunelNeighbours(hor_pos,ver_pos)[0].GetHorPos(),GetTunelNeighbours(hor_pos,ver_pos)[0].GetVerPos())==false)){
            cout<<"Tunel has uncorrect direction! Tunel wasn't create and add!\n";
            return;
        }
        tunels.push_back(new_tunel);
        map[hor_pos][ver_pos]=2;
        SetFogOfWar();
    }
    void AddTunel(int id,int hor_pos,int ver_pos,string direction){
        if (id<0){
            cout<<"Tunel has uncorrect id! Tunel wasn't create and add!\n";
            return;
        }
        if (FindTunel(id)!=NULL){
            cout<<"Tunel with this id is exist! Tunel wasn't create and add!\n";
            return;
        }
        if (CheckTunelExisting(hor_pos,ver_pos)==false)
            return;
        
        if (map[hor_pos][ver_pos]!=0){
            cout<<"Tunel try to set on uncorrect place! Tunel wasn't create and add!\n";
            return;
        }
        Tunel new_tunel(id,hor_pos,ver_pos,direction);
        if ((new_tunel.CheckDirection(direction)==false)||(new_tunel.CheckDirectionSide(GetTunelNeighbours(hor_pos,ver_pos)[0].GetHorPos(),GetTunelNeighbours(hor_pos,ver_pos)[0].GetVerPos())==false)){
            cout<<"Tunel has uncorrect direction! Tunel wasn't create and add!\n";
            return;
        }
        tunels.push_back(new_tunel);
        map[hor_pos][ver_pos]=2;
        SetFogOfWar();
    }
    
    void PrintMap(){
        if (map==NULL){
            cout<<"Map was not exist!\n";
            return;
        }
        for (int i=0;i<size_of_dungeon;i++){
            for (int j=0;j<size_of_dungeon;j++){
                if (map[j][i]>=0)
                    cout<<" ";
                cout<<map[j][i]<<" ";
            }
            cout<<"\n";
        }
    }
    void PrintRooms(){
        for (int i=0;i<rooms.size();i++)
            rooms[i].PrintRoom();
    }
    void PrintTunels(){
        for (int i=0;i<tunels.size();i++)
            tunels[i].PrintTunel();
    }
};

int main(){
    Dungeon D1(7);
    D1.ExpandRadius();
    D1.SetBuildResume();
    D1.AddTunel(6,7,"HORIZONTAL");
    D1.SetBuildResume();
    D1.AddRoom(5,7);
    D1.SetBuildResume();
    D1.AddTunel(7,6,"VERTICAL");
    D1.SetBuildResume();
    D1.AddRoom(7,5);
    D1.SetBuildResume();
    D1.AddTunel(5,6,"VERTICAL");
    D1.SetBuildResume();
    D1.AddTunel(5,8,"VERTICAL");
    D1.SetBuildResume();
    D1.AddRoom(5,5);
    D1.SetBuildResume();
    D1.AddRoom(5,9);
    D1.SetBuildResume();
    D1.AddTunel(8,5,"HORIZONTAL");
    D1.SetBuildResume();
    D1.AddRoom(9,5);
    D1.SetBuildResume();
    D1.AddTunel(9,6,"VERTICAL");
    D1.SetBuildResume();
    D1.AddRoom(9,7);
    D1.SetBuildResume();
    D1.AddTunel(9,8,"VERTICAL");
    D1.SetBuildResume();
    D1.AddRoom(9,9);
    D1.SetBuildResume();
    D1.AddTunel(8,9,"HORIZONTAL");
    D1.SetBuildResume();
    D1.AddRoom(7,9);
    D1.ExpandRadius();
    //D1.SetBuildResume();
    D1.SetAtackPortals();
    /*while (true){
        int choice;
        cout<<"You can do:\n0 - print map\n1 - set build resume\n2 - add room\n3 - add tunel\n4 - turn off build resume\n5 - set atack\n6 - clear atack\n7 - expand dungeon\n8 - print all elements\nAnother number - exit\nYour choice:";
        cin>>choice;
        switch (choice){
            case 0:{
                D1.PrintMap();
                break;
            }
            case 1:{
                D1.SetBuildResume();
                break;
            }
            case 2:{
                int hor_coordinate,ver_coordinate;
                cout<<"Enter room coordinate:\nHorizontal coordinate:";
                cin>>hor_coordinate;
                cout<<"Vertical coordinate:";
                cin>>ver_coordinate;
                D1.AddRoom(hor_coordinate,ver_coordinate);
                break;
            }
            case 3:{
                int hor_coordinate,ver_coordinate;
                cout<<"Enter tune; coordinate:\nHorizontal coordinate:";
                cin>>choice;
                hor_coordinate=int(choice);
                cout<<"Vertical coordinate:";
                cin>>choice;
                ver_coordinate=int(choice);
                D1.AddTunel(hor_coordinate,ver_coordinate,"HORIZONTAL");
                D1.AddTunel(hor_coordinate,ver_coordinate,"VERTICAL");  
                break; 
            }
            case 4:{
                D1.SetFogOfWar();
                break;
            }
            case 5:{
                D1.SetAtackPortals();
                break;
            }
            case 6:{
                D1.SetFogOfWar();
                D1.SetBorder();
                break;
            }
            case 7:{
                D1.ExpandRadius();
                break;
            }
            case 8:{
                D1.PrintRooms();
                D1.PrintTunels();
                break;
            }
            default:
                return 0;
        }
    }
    */
    sf::VideoMode DesktopScreen=sf::VideoMode::getDesktopMode();//получили параметры экрана
    sf::RenderWindow MainWindow(sf::VideoMode(DesktopScreen.width,DesktopScreen.height,DesktopScreen.bitsPerPixel),"Game",sf::Style::Fullscreen);

    MainWindow.setFramerateLimit(60);//установили частоту обновления экрана=60FPS
    
    //int width_of_room=floor(DesktopScreen.width()/D1.GetSizeOfDungeon());
    //int height_of_room=width_of_room;
    
    while(MainWindow.isOpen()){
        sf::Event event;
        while(MainWindow.pollEvent(event)){//забираем событие из очереди событий окна, если такие есть, НЕ БЛОКИРУЕТ ДОБРО
            switch (event.type){
            case sf::Event::Closed:
                MainWindow.close();
                break;
            default:
                break;
            }
        }
        MainWindow.clear();//очищаем окно перед рендером очередного кадра
        sf::Texture texture_of_opened_room;
        if (!texture_of_opened_room.loadFromFile("Opened room.png")){
            cout<<"Problem with loading texture of opened room from file!\n";
            MainWindow.close();
            return 1;
        }
        texture_of_opened_room.setSmooth(true);
        sf::Texture texture_of_fog;
        if (!texture_of_fog.loadFromFile("Fog of war.png")){
            cout<<"Problem with loading texture of fog of war from file!\n";
            MainWindow.close();
            return 2;
        }
        texture_of_fog.setSmooth(true);
        sf::Texture texture_of_blocked_tunel;
        if (!texture_of_blocked_tunel.loadFromFile("Blocked tunels.png")){
            cout<<"Problem with loading texture of blocked tunel!\n";
            MainWindow.close();
            return 3;
        }
        texture_of_blocked_tunel.setSmooth(true);
        sf::Texture texture_of_borders;
        if (!texture_of_borders.loadFromFile("borders.png")){
            cout<<"Problem with loading texture of borders!\n";
            MainWindow.close();
            return 4;
        }
        texture_of_borders.setSmooth(true);
        sf::Texture texture_of_atack_portals;
        if (!texture_of_atack_portals.loadFromFile("attack_portals.png")){
            cout<<"Problem with loading texture of atack portals!\n";
            MainWindow.close();
            return 5;
        }
        texture_of_atack_portals.setSmooth(true);
        sf::Texture texture_of_dark_territory;
        if (!texture_of_dark_territory.loadFromFile("Dark territory.png")){
            cout<<"Problem with loading texture of dark territory!\n";
            MainWindow.close();
            return 6;
        }
        texture_of_dark_territory.setSmooth(true);
        sf::Texture texture_of_available_buldings;
        if (!texture_of_available_buldings.loadFromFile("Build resume.png")){
            cout<<"Problem with loading texture of available buildings!\n";
            MainWindow.close();
            return 7;
        }
        texture_of_available_buldings.setSmooth(true);
        vector<sf::Sprite>list_of_sprites;
        int room_width=floor(DesktopScreen.width/D1.GetSizeOfDungeon());
        int room_height=floor(DesktopScreen.height/D1.GetSizeOfDungeon());
        for (int i=0;i<D1.GetSizeOfDungeon();i++){
            for (int j=0;j<D1.GetSizeOfDungeon();j++){
                switch (D1.GetMap()[i][j]){
                    case -5:{
                        sf::Sprite sprite_of_dark_territory;
                        sprite_of_dark_territory.setTexture(texture_of_dark_territory);
                        sprite_of_dark_territory.setPosition(sf::Vector2f(i*room_width,j*room_height));
                        if ((i==0)||(j==0)||((i+1)==D1.GetSizeOfDungeon())||((j+1)==D1.GetSizeOfDungeon()))
                            sprite_of_dark_territory.setScale(room_width/sprite_of_dark_territory.getLocalBounds().width,room_height/sprite_of_dark_territory.getLocalBounds().height);
                        else if ((i%2==1)&&(j%2==0)){
                            sprite_of_dark_territory.setScale(room_width/sprite_of_dark_territory.getLocalBounds().width/3,room_height/sprite_of_dark_territory.getLocalBounds().height);
                            sprite_of_dark_territory.move(sf::Vector2f(room_width/3,0));
                        }
                        else if ((i%2==0)&&(j%2==1)){
                            sprite_of_dark_territory.setScale(room_width/sprite_of_dark_territory.getLocalBounds().width,room_height/sprite_of_dark_territory.getLocalBounds().height/3);                    
                            sprite_of_dark_territory.move(sf::Vector2f(0,room_height/3));
                        }
                        else
                            sprite_of_dark_territory.setScale(room_width/sprite_of_dark_territory.getLocalBounds().width,room_height/sprite_of_dark_territory.getLocalBounds().height);
                        list_of_sprites.push_back(sprite_of_dark_territory);
                        break;
                    }
                    case -4:{
                        sf::Sprite sprite_of_atack_portals;
                        sprite_of_atack_portals.setTexture(texture_of_atack_portals);
                        sprite_of_atack_portals.setPosition(sf::Vector2f(i*room_width,j*room_height));
                        if ((i%2==1)&&(j%2==1))
                            sprite_of_atack_portals.setScale(room_width/sprite_of_atack_portals.getLocalBounds().width,room_height/sprite_of_atack_portals.getLocalBounds().height);
                        else if ((i%2==1)&&(j%2==0)){
                            sprite_of_atack_portals.setScale(room_width/sprite_of_atack_portals.getLocalBounds().width/3,room_height/sprite_of_atack_portals.getLocalBounds().height);
                            sprite_of_atack_portals.move(sf::Vector2f(room_width/3,0));
                        }
                        else if ((i%2==0)&&(j%2==1)){
                            sprite_of_atack_portals.setScale(room_width/sprite_of_atack_portals.getLocalBounds().width,room_height/sprite_of_atack_portals.getLocalBounds().height/3);                    
                            sprite_of_atack_portals.move(sf::Vector2f(0,room_height/3));
                        }
                        list_of_sprites.push_back(sprite_of_atack_portals);
                        break;
                    }
                    case -3:{
                        sf::Sprite sprite_of_border;
                        sprite_of_border.setTexture(texture_of_borders);
                        sprite_of_border.setPosition(sf::Vector2f(i*room_width,j*room_height));
                        sprite_of_border.setScale((float)room_width/sprite_of_border.getLocalBounds().width,room_height/sprite_of_border.getLocalBounds().height);
                        list_of_sprites.push_back(sprite_of_border);
                        break;
                    }
                    case -2:{
                        sf::Sprite sprite_of_blocked_tunel;
                        sprite_of_blocked_tunel.setTexture(texture_of_blocked_tunel);
                        sprite_of_blocked_tunel.setPosition(sf::Vector2f(i*room_width,j*room_height));
                        if ((i%2==1)&&(j%2==0)){
                            sprite_of_blocked_tunel.setScale(room_width/sprite_of_blocked_tunel.getLocalBounds().width/3,room_height/sprite_of_blocked_tunel.getLocalBounds().height);
                            sprite_of_blocked_tunel.move(sf::Vector2f(room_width/3,0));
                        }
                        else if ((i%2==0)&&(j%2==1)){
                            sprite_of_blocked_tunel.setScale(room_width/sprite_of_blocked_tunel.getLocalBounds().width,room_height/sprite_of_blocked_tunel.getLocalBounds().height/3);                    
                            sprite_of_blocked_tunel.move(sf::Vector2f(0,room_height/3));
                        }
                        else
                            sprite_of_blocked_tunel.setScale(room_width/sprite_of_blocked_tunel.getLocalBounds().width,room_height/sprite_of_blocked_tunel.getLocalBounds().height);
                        list_of_sprites.push_back(sprite_of_blocked_tunel);
                        break;
                    }
                    case -1:{
                        sf::Sprite sprite_of_fog_war;
                        sprite_of_fog_war.setTexture(texture_of_fog);
                        sprite_of_fog_war.setPosition(sf::Vector2f(i*room_width,j*room_height));
                        if ((i%2==1)&&(j%2==0)){
                            sprite_of_fog_war.setScale(room_width/sprite_of_fog_war.getLocalBounds().width/3,room_height/sprite_of_fog_war.getLocalBounds().height);
                            sprite_of_fog_war.move(sf::Vector2f(room_width/3,0));
                        }
                        else if ((i%2==0)&&(j%2==1)){
                            sprite_of_fog_war.setScale(room_width/sprite_of_fog_war.getLocalBounds().width,room_height/sprite_of_fog_war.getLocalBounds().height/3);                    
                            sprite_of_fog_war.move(sf::Vector2f(0,room_height/3));
                        }
                        else
                            sprite_of_fog_war.setScale(room_width/sprite_of_fog_war.getLocalBounds().width,room_height/sprite_of_fog_war.getLocalBounds().height);
                        list_of_sprites.push_back(sprite_of_fog_war);
                        break;
                    }
                    case 0:{
                        sf::Sprite sprite_of_available_buildings;
                        sprite_of_available_buildings.setTexture(texture_of_available_buldings);
                        sprite_of_available_buildings.setPosition(sf::Vector2f(i*room_width,j*room_height));
                        if ((i%2==1)&&(j%2==0)){
                            sprite_of_available_buildings.setScale(room_width/sprite_of_available_buildings.getLocalBounds().width/3,room_height/sprite_of_available_buildings.getLocalBounds().height);
                            sprite_of_available_buildings.move(sf::Vector2f(room_width/3,0));
                        }
                        else if ((i%2==0)&&(j%2==1)){
                            sprite_of_available_buildings.setScale(room_width/sprite_of_available_buildings.getLocalBounds().width,room_height/sprite_of_available_buildings.getLocalBounds().height/3);                    
                            sprite_of_available_buildings.move(sf::Vector2f(0,room_height/3));
                        }
                        else
                            sprite_of_available_buildings.setScale(room_width/sprite_of_available_buildings.getLocalBounds().width,room_height/sprite_of_available_buildings.getLocalBounds().height);
                        list_of_sprites.push_back(sprite_of_available_buildings);
                        break;
                    }
                    case 1:{
                        sf::Sprite sprite_of_opened_room;
                        sprite_of_opened_room.setTexture(texture_of_opened_room);
                        sprite_of_opened_room.setPosition(sf::Vector2f(i*room_width,j*room_height));
                        sprite_of_opened_room.setScale((float)room_width/sprite_of_opened_room.getLocalBounds().width,room_height/sprite_of_opened_room.getLocalBounds().height);
                        list_of_sprites.push_back(sprite_of_opened_room);
                        break;
                    }
                    case 2:{
                        sf::Sprite sprite_of_opened_tunel;
                        sprite_of_opened_tunel.setTexture(texture_of_opened_room);
                        sprite_of_opened_tunel.setPosition(sf::Vector2f(i*room_width,j*room_height));
                        if ((i%2==1)&&(j%2==0)){
                            sprite_of_opened_tunel.setScale(room_width/sprite_of_opened_tunel.getLocalBounds().width/3,room_height/sprite_of_opened_tunel.getLocalBounds().height);
                            sprite_of_opened_tunel.move(sf::Vector2f(room_width/3,0));
                        }
                        else if ((i%2==0)&&(j%2==1)){
                            sprite_of_opened_tunel.setScale(room_width/sprite_of_opened_tunel.getLocalBounds().width,room_height/sprite_of_opened_tunel.getLocalBounds().height/3);                    
                            sprite_of_opened_tunel.move(sf::Vector2f(0,room_height/3));
                        }
                        list_of_sprites.push_back(sprite_of_opened_tunel);
                        break;
                    }
                    default:
                        break;
                }
            }
        }
        for (int i=0;i<list_of_sprites.size();i++)
            MainWindow.draw(list_of_sprites[i]);
        MainWindow.display();//отрисовывание окна на экране
    }

    return 0;
}
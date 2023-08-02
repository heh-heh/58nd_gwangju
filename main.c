#include<stdio.h>
#define MR 6
#define MC 6
#define X -9
#define rr return
#define swap(x,y) temp=x; x=y; y=temp; 
int  map[6][6]={
    {X,X,X,X,X,X},
    {X,2,0,3,0,X},
    {X,3,2,1,0,X},
    {X,0,3,1,2,X},
    {X,0,1,0,0,X},
    {X,X,X,X,X,X}
};

int smt_map[6][6]={
    {X,X,X,X,X,X},
    {X,0,1,0,0,X},
    {X,0,0,-9,0,X},
    {X,0,0,-9,999,X},
    {X,0,-9,0,0,X},
    {X,X,X,X,X,X}
};

int a_arry[4][3]={0};//x,t,c
int path[50], mptr = 0, mptr2 = 0, quit = 0, quit2 = 0;
int sdir1[5] = { 0,-MC,1,MC,-1}; // 앞 오른 뒤 왼
int temp,sdir=0;

void func(int i, int index);
int smt(int n, int* dat);

int main(void){
    for(int i=0; i<4; i++) scanf("%d %d %d", &a_arry[i][1],&a_arry[i][0],&a_arry[i][2]);

    for(int i=0; i<4; i++){
        for(int j=0; j<3; j++){
            if(a_arry[j][1]<a_arry[j+1][1]){
                swap(a_arry[j][0],a_arry[j+1][0]);
                swap(a_arry[j][1],a_arry[j+1][1]);
                swap(a_arry[j][2],a_arry[j+1][2]);
            }
        }
    }
    for(int i=0; i<4; i++){for(int j=0; j<3; j++)printf("%d ",a_arry[i][j]); printf("\n");}
    getchar();
    func(0,4);
    // for(int i=0; i<6; i++){for(int j=0; j<6; j++)printf("%5d ", smt_map[i][j]); printf("\n\n");}
    // printf("%d\n", smt(1,&smt_map[0][0]));
    // for(int ii=0; ii<=mptr; ii++){ printf("%d ", path[ii]);}printf("\n");
    // for(int i=0; i<6; i++){for(int j=0; j<6; j++)printf("%5d ", smt_map[i][j]); printf("\n\n");}
}
void func(int i, int index){
    if(i >= index) rr;
    int temp_map[6][6]={0};
    int temp_map2[6][6]={0};
    
    while(1){
        for(int y=0; y<6; y++){for(int x=0; x<6; x++){
            if(map[y][x]==X)temp_map[y][x]=X;
            if(map[y][x] == a_arry[i][2])temp_map[y][x]=-9;
        }}
        temp_map[a_arry[i][0]][a_arry[i][1]]=999;temp_map[1][2]=1;
        for(int ii=0; ii<6; ii++){for(int j=0; j<6; j++)printf("%5d ",temp_map[ii][j]); printf("\n\n");}getchar();
        if(smt(1,&temp_map[0][0])) break;
    }
    for(int ii=mptr-1; ii>=0; ii--){ printf("%d ", path[ii]);}printf("\n"); mptr=0;//퍽 물고 놓는 무빙
    map[a_arry[i][0]][a_arry[i][1]]=-9;//퍽을 넣었으니 고정 시킴
    while(1){
        for(int y=0; y<6; y++){for(int x=0; x<6; x++){
            if(map[y][x]==X)temp_map2[y][x]=X;
            if(map[y][x] == a_arry[i][2])temp_map2[y][x]=-9;
        }}
        temp_map2[a_arry[i][0]][a_arry[i][1]]=1;temp_map2[1][2]=999;
        //for(int ii=0; ii<6; ii++){for(int j=0; j<6; j++)printf("%5d ",temp_map2[ii][j]); printf("\n\n");}getchar();
        if(smt(1,&temp_map2[0][0])) break;
    }
    for(int ii=mptr-1; ii>=0; ii--){ printf("%d ", path[ii]);}//퍽 놓고 돌아 오는 무빙

    mptr=0;
    getchar();
    func(i+1, index);
}


int smt(int n, int* dat) {  // smt는 디코로 다시 설명 함
    int i, j, * p, dir;
    do {
        j = 0;
        for (i = MC; i < (MR - 1) * MC; i++) if (*(dat + i) == n) {
            j++;
            for (dir = 1; dir < 5; dir++) {
                p = (dat + i) + sdir1[dir];
                if (!*p)*p = n + 1;
                else if (*p == 999) {
                    if (!quit) quit = i + sdir1[dir];
                    if (quit && mptr == 0) quit2 = i; // 도착지-1
                    else if (quit && !quit2) quit2 = i + sdir1[dir]; // 도착지-1
                    path[mptr++] = dir;
                    *(dat + i) = 999;
                    rr 1;
                }
            }
        }
    } while (j && smt(n + 1, dat));
    rr 0;
}
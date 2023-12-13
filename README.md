
# 2023전국 기능경기 경기대회
모바일로보틱스 직종
2,3과제 알고리즘(출제 예상 문제)

(결국 이문제가 출제는 되지 않았지만 알고리즘 을 짯다는 것에 대해 만족)

사용 언어
-------
![Static Badge](https://img.shields.io/badge/C%EC%96%B8%EC%96%B4-%23808080?logo=C)


소스 설명
-------

## define & 기본적인 라이브러리 불러오기
 - MR,MC : 맵 배열 크기
 - X : 종료 지점
-  swap : 배열 값 교환
  
``` cpp

#include<stdio.h>
#define MR 6
#define MC 6
#define X -9
#define rr return
#define swap(x,y) temp=x; x=y; y=temp; 
```


## 배열 선언
(map 들의 경우 기본적으로 전부 0 으로 초기화)
 -  map : 기본 적으로 로봇이 스캔한맵
 -  smt_map : 로봇이 스캔한 맵을 바탕으로 정렬을 진행할 맵  
 - a_arry : 로봇이 정렬 해야될 값을 스캔 하여 넣음
  
```cpp
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

int a_arry[4][3]={
    {3,4,1},
    {2,1,2},
    {4,3,1},
    {4,2,3}
};//x,y,c
```


## 길찾기 함수를 위한 변수 선언

  - path[] : 길찾기 함수 사용후 로봇이 진행할 방향 저장
  - mptr : 로봇이 움직일 횟수 저장
  - sdir : 로봇이 바라볼 방향을 1차원 값으로 지정(포인터)
  - now : 로봇의 위치를 2차원 값을 1차원 값으로 저장(포인터)

```cpp
int path[50], mptr = 0, mptr2 = 0, quit = 0, quit2 = 0;
int sdir1[5] = { 0,-MC,1,MC,-1}; // 앞 오른 뒤 왼
int temp,sdir=0;
int now = 8;
```

## 함수 선언
  - func : 메인 정렬 함수(i : 정령 시작 할 a_arry[i]의 배열, index : 무한 재귀를 방지할 변수)
  - smt : 길찾기 함수(n : 시작 위치에 들어갈 숫자, dat : 맵배열)
  - move : 로봇을 움직일 함수(dir1 : 로봇의 방향, p : 퍽을 놓을때 (1) 아닐때 (0)
```cpp
void func(int i, int index);
int smt(int n, int* dat);
void move(int dir1, int p);
```

## main 함수
``` cpp 
int main(void){

    for(int i=0; i<4; i++){ //입력 받은 a_arry 를 정렬 하기 편한 순서로 정렬
        for(int j=0; j<3; j++){
            if(a_arry[j][0]<a_arry[j+1][0]){
                swap(a_arry[j][0],a_arry[j+1][0]);
                swap(a_arry[j][1],a_arry[j+1][1]);
                swap(a_arry[j][2],a_arry[j+1][2]);
            }
            else if(a_arry[j][0]==a_arry[j+1][0]){
                if(a_arry[j][1]>a_arry[j+1][1]){
                    swap(a_arry[j][0],a_arry[j+1][0]);
                    swap(a_arry[j][1],a_arry[j+1][1]);
                    swap(a_arry[j][2],a_arry[j+1][2]);
                }
            }
        }
    }
    for(int i=0; i<4; i++){for(int j=0; j<3; j++)printf("%d ",a_arry[i][j]); printf("\n");} //출력
    int iii=0;
    for(int i=0; i<6; i++){for(int j=0; j<6; j++)printf("%3d", iii++); printf("\n\n");} //출력
    getchar(); 
    func(0,1);//정렬 시작(한개만 정렬) 여러개 정렬시 ex)func(0,3)
}
```
## func함수


```cpp
void func(int i, int index){
    if(i >= index) rr;//무한 재귀 방지
    int temp_map[6][6]={0}; //정렬한 임시 배열
    int temp_map2[6][6]={0};//임시 배열 2
    
    while(1){
        for(int y=0; y<6; y++){for(int x=0; x<6; x++){//임시 배열 1 을 정렬 하기 위한 형태로 지정
            if(map[y][x]==X)temp_map[y][x]=X;
            if(map[y][x] == a_arry[i][2])temp_map[y][x]=-9;
        }}
        temp_map[a_arry[i][0]][a_arry[i][1]]=999;temp_map[1][2]=1;
        for(int ii=0; ii<6; ii++){for(int j=0; j<6; j++)printf("%5d ",temp_map[ii][j]); printf("\n\n");}getchar();//출력
        if(smt(1,&temp_map[0][0])) break;//길찾기 함수를 사용해 결로 지정
    }
    for(int ii=mptr-1; ii>=0; ii--){//움직인 경로만큼 move 함수 실행
        if(ii==0)move(path[ii],1);
        else move(path[ii],0);
    }printf("\n"); mptr=0;//움직인 횟수 초기화
    map[a_arry[i][0]][a_arry[i][1]]=-9;//퍽을 넣었으니 고정 시킴
    while(1){//출구 로 나가기 위해 다시 임시 배열 지정
        for(int y=0; y<6; y++){for(int x=0; x<6; x++){
            if(map[y][x]==X)temp_map2[y][x]=X;
            if(map[y][x] == a_arry[i][2])temp_map2[y][x]=-9;
        }}
        *(&temp_map2[0][0]+now)=1;temp_map2[1][2]=999;
        //for(int ii=0; ii<6; ii++){for(int j=0; j<6; j++)printf("%5d ",temp_map2[ii][j]); printf("\n\n");}getchar();//출력
        if(smt(1,&temp_map2[0][0])) break;//길찾기 함수 실행
    }
    for(int ii=mptr-1; ii>=0; ii--){//위와 마찬가지로 move 함수 실행
        move(path[ii],0);

    }//퍽 놓고 돌아 오는 무빙

    mptr=0;
    getchar();
    func(i+1, index);//재귀 함수
}
```
## move 함수
무브의 경우 로봇에 넣기 위한 것과 많이 다름
```cpp
void move(int dir1, int p){
    if(p){
        printf("%d %d\n", dir1, now);getchar;
    }
    else{
        now += sdir1[dir1];
        printf("%d %d\n", dir1, now);getchar;
    }
}
```

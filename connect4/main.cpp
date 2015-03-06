//
//  main.cpp
//  connect4
//
//  Created by Krish Furia on 3/5/15.
//  Copyright (c) 2015 Krish Furia. All rights reserved.
//

#include <iostream>
#include <cstdio>
#include <algorithm>
#define N 8
using namespace std;

//Global declarations
int matrix[N][N] = {0};
int score_cpu [N][N] = {0};
int score_player [N][N] = {0};
int row = 0 ;
int col = 0;
int state;
int row_count[N] = {7,7,7,7,7,7,7,7};
bool firstPlay = true;
int winningRow = 0;
int winningCol = 0;
int winningDia = 0;

void check(int x, int p);
void check_col(int x, int p);
void check_row(int x, int p);
void check_diag(int x, int p);
void score_row(int x, int p);
void score_col(int x, int p);
void score_diagonal(int x,int p);
//Initilize -99 as tokens for CPU and player score array
void score(int x, int p)
{
    int temp_row = row_count[x];
    //CPU is -1 always
    score_cpu[temp_row][x] = p;
    score_player[temp_row][x] = p;
    
    
    //Row score
    score_row(x, p);
    score_col(x, p);
    score_diagonal(x,p);
}

void score_diagonal(int x,int p)
{
    int i,j;
    int temp_plus =0;
    int temp_minus = 0;
    bool stop_upper_plus = false;
    bool stop_upper_minus = false;
    bool stop_lower_plus = false;
    bool stop_lower_minus = false;
    
    //player scoring
    if(p == 99)
    {
        /* Checking immediate negihbours for other player and value <2
         and then replacing with 0*/
        temp_plus = x + 1;
        temp_minus = x - 1;
        //upper right other player
        if(score_player[(row_count[x]-1)][temp_plus] == (p*-1) && row_count[x]+1<N && temp_minus>=0)
        {
            if(score_cpu[(row_count[x]+1)][temp_minus] <= 3 && score_cpu[(row_count[x]+1)][temp_minus]!= p && score_cpu[(row_count[x]+1)][temp_minus]!= (p*-1))
            {
                score_cpu[(row_count[x]+1)][temp_minus] -= 2;
            }
            if(score_cpu[(row_count[x]+2)][temp_minus-1] <=3 && score_cpu[(row_count[x]+2)][temp_minus-1]!= p && score_cpu[(row_count[x]+2)][temp_minus-1]!= (p*-1) && row_count[x]+2<N && temp_minus-1>=0)
            {
                score_cpu[(row_count[x]+2)][temp_minus-1] -= 1;
            }
        }
        //upper left other player
        if(score_player[(row_count[x]-1)][temp_minus] == (p*-1)&& row_count[x]+1<N && temp_plus<N)
        {
            if(score_cpu[(row_count[x]+1)][temp_plus] <= 3 && score_cpu[(row_count[x]+1)][temp_plus]!= p && score_cpu[(row_count[x]+1)][temp_plus]!= (p*-1))
            {
                score_cpu[(row_count[x]+1)][temp_plus] -= 2;
            }
            if(score_cpu[(row_count[x]+2)][temp_plus+1] <=3 && score_cpu[(row_count[x]+2)][temp_plus+1]!= p && score_cpu[(row_count[x]+2)][temp_plus+1]!= (p*-1)&& row_count[x]+2<N && temp_plus+1<N)
            {
                score_cpu[(row_count[x]+2)][temp_plus+1] -= 1;
            }
        }
        //lower right other player
        if(score_player[(row_count[x]+1)][temp_plus] == (p*-1) && row_count[x]-1>=0 && temp_minus>=0)
        {
            if(score_cpu[(row_count[x]-1)][temp_minus] <= 3 && score_cpu[(row_count[x]-1)][temp_minus]!= p && score_cpu[(row_count[x]-1)][temp_minus]!= (p*-1))
            {
                score_cpu[(row_count[x]-1)][temp_minus] -= 2;
            }
            if(score_cpu[(row_count[x]-2)][temp_minus-1] <=3 && score_cpu[(row_count[x]-2)][temp_minus-1]!= p && score_cpu[(row_count[x]-2)][temp_minus-1]!= (p*-1) && row_count[x]-2>0 && temp_minus-1>=0)
            {
                score_cpu[(row_count[x]-2)][temp_minus-1] -= 1;
            }
        }
        //lower left other player
        if(score_player[(row_count[x]+1)][temp_minus] == (p*-1)&& row_count[x]-1>=0 && temp_plus<N)
        {
            if(score_cpu[(row_count[x]-1)][temp_plus] <= 3 && score_cpu[(row_count[x]-1)][temp_plus]!= p && score_cpu[(row_count[x]-1)][temp_plus]!= (p*-1))
            {
                score_cpu[(row_count[x]-1)][temp_plus] -= 2;
            }
            if(score_cpu[(row_count[x]-2)][temp_plus+1] <=3 && score_cpu[(row_count[x]-2)][temp_plus+1]!= p && score_cpu[(row_count[x]-2)][temp_plus+1]!= (p*-1)&& row_count[x]-2>0 && temp_plus+1<N)
            {
                score_cpu[(row_count[x]-2)][temp_plus+1] -= 1;
            }
        }
        temp_plus = x + 2;
        temp_minus = x - 2;
        //upper right other player
        if(score_player[(row_count[x]-2)][temp_plus] == (p*-1) && row_count[x]+1<N && temp_minus+1>=0)
        {
            if(score_cpu[(row_count[x]+1)][temp_minus+1] <=3 && score_cpu[(row_count[x]+1)][temp_minus+1]!= p && score_cpu[(row_count[x]+1)][temp_minus+1]!= (p*-1))
            {
                score_cpu[(row_count[x]+1)][temp_minus+1] -= 1;
            }
        }
        //upper left other player
        if(score_player[(row_count[x]-2)][temp_minus] == (p*-1)&& row_count[x]+1<N && temp_plus-1<N)
        {
            if(score_cpu[(row_count[x]+1)][temp_plus-1] <=3 && score_cpu[(row_count[x]+2)][temp_plus-1]!= p && score_cpu[(row_count[x]+2)][temp_plus-1]!= (p*-1))
            {
                score_cpu[(row_count[x]+1)][temp_plus-1] -= 1;
            }
        }
        //lower right other player
        if(score_player[(row_count[x]+2)][temp_plus] == (p*-1) && row_count[x]-1>=0 && temp_minus+1>=0)
        {
            if(score_cpu[(row_count[x]-1)][temp_minus+1] <=3 && score_cpu[(row_count[x]-1)][temp_minus+1]!= p && score_cpu[(row_count[x]-1)][temp_minus+1]!= (p*-1))
            {
                score_cpu[(row_count[x]-1)][temp_minus+1] -= 1;
            }
        }
        //lower left other player
        if(score_player[(row_count[x]+2)][temp_minus] == (p*-1)&& row_count[x]-1>=0 && temp_plus-1<N)
        {
            if(score_cpu[(row_count[x]-1)][temp_plus-1] <=3 && score_cpu[(row_count[x]-1)][temp_plus-1]!= p && score_cpu[(row_count[x]-1)][temp_plus-1]!= (p*-1))
            {
                score_cpu[(row_count[x]-1)][temp_plus-1] -= 1;
            }
        }
        for(i=1,j=3 ; i<4 ; i++,j--)
        {
            temp_plus = x + i;
            temp_minus = x - i;
            //upper right diag - == (p*-1) - to stop if other player
            if (score_player[((row_count[x])-i)][temp_plus] == (p*-1))
            {
                stop_upper_plus=true;
            }
            //upper left diag
            if (score_player[((row_count[x])-i)][temp_minus] == (p*-1))
            {
                stop_upper_minus=true;
            }
            // for lower right diag
            if (score_player[((row_count[x])+i)][temp_plus] == (p*-1))
            {
                stop_lower_plus=true;
            }
            //lower left diag
            
            if (score_player[((row_count[x])+i)][temp_minus] == (p*-1))
            {
                stop_lower_minus=true;
            }
            
            //skip if same player and continue
            // upper right
            if (score_player[((row_count[x])-i)][temp_plus] == p)
            {
                if(score_player[(row_count[x]-i)][temp_minus] != p && score_player[(row_count[x]-i)][temp_minus] != (p*-1) && temp_minus>=0 && row_count[x]-i>=0) //upper left
                    score_player[(row_count[x]-i)][temp_minus] += j;
                if(score_player[(row_count[x]+i)][temp_minus] != p && score_player[(row_count[x]+i)][temp_minus] != (p*-1) && temp_minus>=0 && row_count[x]+i<N) //lower left
                    score_player[(row_count[x]+i)][temp_minus] += j;
                if(score_player[(row_count[x]+i)][temp_plus] != p && score_player[(row_count[x]+i)][temp_plus] != (p*-1) && temp_plus<N && row_count[x]+i<N) //lower right
                    score_player[(row_count[x]+i)][temp_plus] += j;
                continue;
            }
            // Upper left
            if(score_player[((row_count[x])-i)][temp_minus] ==p )
            {
                if(score_player[(row_count[x]-i)][temp_plus] != p && score_player[(row_count[x]-i)][temp_plus] != (p*-1)&&temp_plus<N && row_count[x]-i>=0)//upper right
                    score_player[(row_count[x]-i)][temp_plus] += j;
                if(score_player[(row_count[x]+i)][temp_minus] != p && score_player[(row_count[x]+i)][temp_minus] != (p*-1)&&temp_minus>=0&& row_count[x]+i<N) //lower left
                    score_player[(row_count[x]+i)][temp_minus] += j;
                if(score_player[(row_count[x]+i)][temp_plus] != p && score_player[(row_count[x]+i)][temp_plus] != (p*-1)&&temp_plus<N&& row_count[x]+i<N) //lower right
                    score_player[(row_count[x]+i)][temp_plus] += j;
                continue;
            }
            
            // Lower right
            if (score_player[((row_count[x])+i)][temp_plus] == p)
            {
                if(score_player[(row_count[x]+i)][temp_minus] != p && score_player[(row_count[x]+i)][temp_minus] != (p*-1)&&temp_minus>=0 && row_count[x]+i<N) //lower left
                    score_player[(row_count[x]+i)][temp_minus] += j;
                if(score_player[(row_count[x]-i)][temp_minus] != p && score_player[(row_count[x]-i)][temp_minus] != (p*-1)&&temp_minus>=0 && row_count[x]-i>=0) //upper left
                    score_player[(row_count[x]-i)][temp_minus] += j;
                if(score_player[(row_count[x]-i)][temp_plus] != p && score_player[(row_count[x]-i)][temp_plus] != (p*-1)&&temp_plus<N && row_count[x]-i>=0)  //upper right
                    score_player[(row_count[x]-i)][temp_plus] += j;
                continue;
            }
            
            // Lower left
            if(score_player[((row_count[x])+i)][temp_minus] ==p )
            {
                if(score_player[(row_count[x]+i)][temp_plus] != p && score_player[(row_count[x]+i)][temp_plus] != (p*-1)&&temp_plus<N && row_count[x]+i<N)  //lower right
                    score_player[(row_count[x]+i)][temp_plus] += j;
                if(score_player[(row_count[x]-i)][temp_minus] != p && score_player[(row_count[x]-i)][temp_minus] != (p*-1)&&temp_minus>=0 && row_count[x]-i>=0) //upper left
                    score_player[(row_count[x]-i)][temp_minus] += j;
                if(score_player[(row_count[x]-i)][temp_plus] != p && score_player[(row_count[x]-i)][temp_plus] != (p*-1)&&temp_plus<N && row_count[x]-i>=0)  //upper right
                    score_player[(row_count[x]-i)][temp_plus] += j;
                continue;
            }
            
            
            
            //upper right
            if(temp_plus<N && !stop_upper_plus && row_count[x]-i>=0)
            {
                score_player[((row_count[x])-i)][temp_plus] += j;
            }
            
            //upper left diag
            if(temp_minus>=0 && !stop_upper_minus && row_count[x]-i>=0)
            {
                score_player[((row_count[x])-i)][temp_minus] += j;
            }
            //lower right
            if(temp_plus<N  && !stop_lower_plus && row_count[x]+i<N)
            {
                score_player[((row_count[x])+i)][temp_plus] += j;
            }
            
            //lower left diag
            if(temp_minus>=0 && !stop_lower_minus && row_count[x]+i<N)
            {
                score_player[((row_count[x])+i)][temp_minus] += j;
            }
        }//end of for
    }//end of player 99 if
    
    /*-----------------------------cpu left-------------------------------*/
    
    
    if(p == -99)
    {
        /* Checking immediate negihbours for other player and value <2
         and then replacing with 0*/
        temp_plus = x + 1;
        temp_minus = x - 1;
        //upper right other player
        if(score_cpu[(row_count[x]-1)][temp_plus] == (p*-1) && row_count[x]+1<N && temp_minus>=0)
        {
            if(score_player[(row_count[x]+1)][temp_minus] <= 3 && score_player[(row_count[x]+1)][temp_minus]!= p && score_player[(row_count[x]+1)][temp_minus]!= (p*-1))
            {
                score_player[(row_count[x]+1)][temp_minus] -= 2;
            }
            if(score_player[(row_count[x]+2)][temp_minus-1] <=3 && score_player[(row_count[x]+2)][temp_minus-1]!= p && score_player[(row_count[x]+2)][temp_minus-1]!= (p*-1) && row_count[x]+2<N && temp_minus-1>=0)
            {
                score_player[(row_count[x]+2)][temp_minus-1] -= 1;
            }
        }
        //upper left other player
        if(score_cpu[(row_count[x]-1)][temp_minus] == (p*-1)&& row_count[x]+1<N && temp_plus<N)
        {
            if(score_player[(row_count[x]+1)][temp_plus] <= 3 && score_player[(row_count[x]+1)][temp_plus]!= p && score_player[(row_count[x]+1)][temp_plus]!= (p*-1))
            {
                score_player[(row_count[x]+1)][temp_plus] -= 2;
            }
            if(score_player[(row_count[x]+2)][temp_plus+1] <=3 && score_player[(row_count[x]+2)][temp_plus+1]!= p && score_player[(row_count[x]+2)][temp_plus+1]!= (p*-1)&& row_count[x]+2<N && temp_plus<N)
            {
                score_player[(row_count[x]+2)][temp_plus+1] -= 1;
            }
        }
        //lower right other player
        if(score_cpu[(row_count[x]+1)][temp_plus] == (p*-1) && row_count[x]-1>=0 && temp_minus>=0)
        {
            if(score_player[(row_count[x]-1)][temp_minus] <= 3 && score_player[(row_count[x]-1)][temp_minus]!= p && score_player[(row_count[x]-1)][temp_minus]!= (p*-1))
            {
                score_player[(row_count[x]-1)][temp_minus] -= 2;
            }
            if(score_player[(row_count[x]-2)][temp_minus-1] <=3 && score_player[(row_count[x]-2)][temp_minus-1]!= p && score_player[(row_count[x]-2)][temp_minus-1]!= (p*-1) && row_count[x]-2>=0 && temp_minus-1>=0)
            {
                score_player[(row_count[x]-2)][temp_minus-1] -= 1;
            }
        }
        //lower left other player
        if(score_cpu[(row_count[x]+1)][temp_minus] == (p*-1)&& row_count[x]-1>=0 && temp_plus<N)
        {
            if(score_player[(row_count[x]-1)][temp_plus] <= 3 && score_player[(row_count[x]-1)][temp_plus]!= p && score_player[(row_count[x]-1)][temp_plus]!= (p*-1))
            {
                score_player[(row_count[x]-1)][temp_plus] -= 2;
            }
            if(score_player[(row_count[x]-2)][temp_plus+1] <=3 && score_player[(row_count[x]-2)][temp_plus+1]!= p && score_player[(row_count[x]-2)][temp_plus+1]!= (p*-1)&& row_count[x]-2>=0 && temp_plus<N)
            {
                score_player[(row_count[x]-2)][temp_plus+1] -= 1;
            }
        }
        temp_plus = x + 2;
        temp_minus = x - 2;
        //upper right other player
        if(score_cpu[(row_count[x]-2)][temp_plus] == (p*-1) && row_count[x]+1<N && temp_minus+1<N)
        {
            if(score_player[(row_count[x]+1)][temp_minus+1] <=3 && score_player[(row_count[x]+1)][temp_minus+1]!= p && score_player[(row_count[x]+1)][temp_minus+1]!= (p*-1))
            {
                score_player[(row_count[x]+1)][temp_minus+1] -= 1;
            }
        }
        //upper left other player
        if(score_cpu[(row_count[x]-2)][temp_minus] == (p*-1)&& row_count[x]+1<N && temp_plus-1>=0)
        {
            if(score_player[(row_count[x]+1)][temp_plus-1] <=3 && score_player[(row_count[x]+2)][temp_plus-1]!= p && score_player[(row_count[x]+2)][temp_plus-1]!= (p*-1))
            {
                score_player[(row_count[x]+1)][temp_plus-1] -= 1;
            }
        }
        //lower right other player
        if(score_cpu[(row_count[x]+2)][temp_plus] == (p*-1) && row_count[x]-1>=0 && temp_minus>=0)
        {
            if(score_player[(row_count[x]-1)][temp_minus+1] <=3 && score_player[(row_count[x]-1)][temp_minus+1]!= p && score_player[(row_count[x]-1)][temp_minus+1]!= (p*-1))
            {
                score_player[(row_count[x]-1)][temp_minus+1] -= 1;
            }
        }
        //lower left other player
        if(score_cpu[(row_count[x]+2)][temp_minus] == (p*-1)&& row_count[x]-1>=0 && temp_plus<N)
        {
            if(score_player[(row_count[x]-1)][temp_plus-1] <=3 && score_player[(row_count[x]-1)][temp_plus-1]!= p && score_player[(row_count[x]-1)][temp_plus-1]!= (p*-1))
            {
                score_player[(row_count[x]-1)][temp_plus-1] -= 1;
            }
        }
        for(i=1,j=3 ; i<4 ; i++,j--)
        {
            temp_plus = x + i;
            temp_minus = x - i;
            //upper right diag - == (p*-1) - to stop if other player
            if (score_cpu[((row_count[x])-i)][temp_plus] == (p*-1))
            {
                stop_upper_plus=true;
            }
            //upper left diag
            if (score_cpu[((row_count[x])-i)][temp_minus] == (p*-1))
            {
                stop_upper_minus=true;
            }
            // for lower right diag
            if (score_cpu[((row_count[x])+i)][temp_plus] == (p*-1))
            {
                stop_lower_plus=true;
            }
            //lower left diag
            
            if (score_cpu[((row_count[x])+i)][temp_minus] == (p*-1))
            {
                stop_lower_minus=true;
            }
            
            //skip if same player and continue
            // upper right
            if (score_cpu[((row_count[x])-i)][temp_plus] == p)
            {
                if(score_cpu[(row_count[x]-i)][temp_minus] != p && score_cpu[(row_count[x]-i)][temp_minus] != (p*-1) && temp_minus>=0 && row_count[x]-i>=0) //upper left
                    score_cpu[(row_count[x]-i)][temp_minus] += j;
                if(score_cpu[(row_count[x]+i)][temp_minus] != p && score_cpu[(row_count[x]+i)][temp_minus] != (p*-1) && temp_minus>=0 && (row_count[x]+i)<N) //lower left
                    score_cpu[(row_count[x]+i)][temp_minus] += j;
                if(score_cpu[(row_count[x]+i)][temp_plus] != p && score_cpu[(row_count[x]+i)][temp_plus] != (p*-1) && temp_plus<N && (row_count[x]+i)<N) //lower right
                    score_cpu[(row_count[x]+i)][temp_plus] += j;
                continue;
            }
            // Upper left
            if(score_cpu[((row_count[x])-i)][temp_minus] ==p )
            {
                if(score_cpu[(row_count[x]-i)][temp_plus] != p && score_cpu[(row_count[x]-i)][temp_plus] != (p*-1) && temp_plus<N && row_count[x]-i>=0)//upper right
                    score_cpu[(row_count[x]-i)][temp_plus] += j;
                if(score_cpu[(row_count[x]+i)][temp_minus] != p && score_cpu[(row_count[x]+i)][temp_minus] != (p*-1) && temp_minus>=0 && (row_count[x]+i)<N) //lower left
                    score_cpu[(row_count[x]+i)][temp_minus] += j;
                if(score_cpu[(row_count[x]+i)][temp_plus] != p && score_cpu[(row_count[x]+i)][temp_plus] != (p*-1) && temp_plus<N && (row_count[x]+i)<N) //lower right
                    score_cpu[(row_count[x]+i)][temp_plus] += j;
                continue;
            }
            
            // Lower right
            if (score_cpu[((row_count[x])+i)][temp_plus] == p)
            {
                if(score_cpu[(row_count[x]+i)][temp_minus] != p && score_cpu[(row_count[x]+i)][temp_minus] != (p*-1) && temp_minus>=0 && (row_count[x]+i)<N) //lower left
                    score_cpu[(row_count[x]+i)][temp_minus] += j;
                if(score_cpu[(row_count[x]-i)][temp_minus] != p && score_cpu[(row_count[x]-i)][temp_minus] != (p*-1) && temp_minus>=0 && row_count[x]-i>=0) //upper left
                    score_cpu[(row_count[x]-i)][temp_minus] += j;
                if(score_cpu[(row_count[x]-i)][temp_plus] != p && score_cpu[(row_count[x]-i)][temp_plus] != (p*-1) && temp_plus<N && row_count[x]-i>=0)  //upper right
                    score_cpu[(row_count[x]-i)][temp_plus] += j;
                continue;
            }
            
            // Lower left
            if(score_cpu[((row_count[x])+i)][temp_minus] ==p )
            {
                if(score_cpu[(row_count[x]+i)][temp_plus] != p && score_cpu[(row_count[x]+i)][temp_plus] != (p*-1) && temp_plus<N && (row_count[x]+i)<N)  //lower right
                    score_cpu[(row_count[x]+i)][temp_plus] += j;
                if(score_cpu[(row_count[x]-i)][temp_minus] != p && score_cpu[(row_count[x]-i)][temp_minus] != (p*-1) && temp_minus>=0 && row_count[x]-i>=0) //upper left
                    score_cpu[(row_count[x]-i)][temp_minus] += j;
                if(score_cpu[(row_count[x]-i)][temp_plus] != p && score_cpu[(row_count[x]-i)][temp_plus] != (p*-1) && temp_plus<N && row_count[x]-i>=0)  //upper right
                    score_cpu[(row_count[x]-i)][temp_plus] += j;
                continue;
            }
            
            
            //upper right
            if(temp_plus<N && !stop_upper_plus && row_count[x]-i>=0)
            {
                score_cpu[((row_count[x])-i)][temp_plus] += j;
            }
            
            //upper left diag
            if(temp_minus>=0 && !stop_upper_minus && row_count[x]-i>=0)
            {
                score_cpu[((row_count[x])-i)][temp_minus] += j;
            }
            //lower right
            if(temp_plus<N  && !stop_lower_plus && (row_count[x]+i)<N)
            {
                score_cpu[((row_count[x])+i)][temp_plus] += j;
            }
            
            //lower left diag
            if(temp_minus>=0 && !stop_lower_minus && (row_count[x] +i)<N)
            {
                score_cpu[((row_count[x])+i)][temp_minus] += j;
            }
        }//end of for
    }// END OF CPU IF
    
    
}



void score_row(int x, int p)
{
    int i,j;
    int temp_plus =0;
    int temp_minus = 0;
    bool stop_plus = false;
    bool stop_minus = false;
    
    
    //Scoring for player
    if(p == 99)
    {
        /* Checking immediate negihbours for other player and value <2
         and then replacing with 0*/
        temp_plus = x + 1;
        temp_minus = x - 1;
        if(score_player[(row_count[x])][temp_plus] == (p*-1) && temp_minus>=0)
        {
            if(score_cpu[(row_count[x])][temp_minus] <= 7 && score_cpu[(row_count[x])][temp_minus]!= p && score_cpu[(row_count[x])][temp_minus]!= (p*-1))
            {
                score_cpu[(row_count[x])][temp_minus] -= 4;
            }
            if(score_cpu[(row_count[x])][temp_minus-1] <=3 && score_cpu[(row_count[x])][temp_minus-1]!= p && score_cpu[(row_count[x])][temp_minus-1]!= (p*-1)&&temp_minus-1>=0)
            {
                score_cpu[(row_count[x])][temp_minus-1] -= 1;
            }
        }
        if(score_player[(row_count[x])][temp_minus] == (p*-1) && temp_plus<N)
        {
            if(score_cpu[(row_count[x])][temp_plus] <= 7 && score_cpu[(row_count[x])][temp_plus]!= p && score_cpu[(row_count[x])][temp_plus]!= (p*-1))
            {
                score_cpu[(row_count[x])][temp_plus] -= 4;
            }
            if(score_cpu[(row_count[x])][temp_plus+1] <=3 && score_cpu[(row_count[x])][temp_plus+1]!= p && score_cpu[(row_count[x])][temp_plus+1]!= (p*-1)&&temp_plus+1<N)
            {
                score_cpu[(row_count[x])][temp_plus+1] -= 1;
            }
        }
        temp_plus = x + 2;
        temp_minus = x - 2;
        if(score_player[(row_count[x])][temp_plus] == (p*-1) && temp_minus+1>=0)
        {
            if(score_cpu[(row_count[x])][temp_minus+1] <=4 && score_cpu[(row_count[x])][temp_minus+1]!= p && score_cpu[(row_count[x])][temp_minus+1]!= (p*-1))
            {
                score_cpu[(row_count[x])][temp_minus+1] -= 1;
            }
        }
        if(score_player[(row_count[x])][temp_minus] == (p*-1) && temp_plus-1<N)
        {
            if(score_cpu[(row_count[x])][temp_plus-1] <=4 && score_cpu[(row_count[x])][temp_plus-1]!= p && score_cpu[(row_count[x])][temp_plus-1]!= (p*-1))
            {
                score_cpu[(row_count[x])][temp_plus-1] -= 1;
            }
        }
        
        for(i=1,j=7 ; i<4 ; i++,j-=3)
        {
            temp_plus = x + i;
            temp_minus = x - i;
            if (score_player[(row_count[x])][temp_plus] == (p*-1) )
            {
                stop_plus=true;
            }
            if (score_player[(row_count[x])][temp_minus] == (p*-1))
            {
                stop_minus=true;
            }
            //code for skipping same player element while scoring
            if (score_player[(row_count[x])][temp_plus] == p)
            {
                if(score_player[(row_count[x])][temp_minus] != p && score_player[(row_count[x])][temp_minus] != (p*-1) && temp_minus>=0)
                    score_player[(row_count[x])][temp_minus] += j;
                continue;
            }
            
            if(score_player[(row_count[x])][temp_minus] ==p )
            {
                if(score_player[(row_count[x])][temp_plus] != p && score_player[(row_count[x])][temp_plus] != (p*-1) && temp_plus<N)
                {
                    score_player[(row_count[x])][temp_plus] += j;
                }
                continue;
            }
            
            if(temp_plus<N && !stop_plus)
            {
                score_player[(row_count[x])][temp_plus] += j;
            }
            
            if(temp_minus>=0 && !stop_minus)
            {
                score_player[(row_count[x])][temp_minus] += j;
            }
            
            
        }
    }
    
    //CPU score
    if(p == -99)
    {
        /* Checking immediate negihbours for other player and value <2
         and then replacing with 0*/
        temp_plus = x + 1;
        temp_minus = x - 1;
        if(score_cpu[(row_count[x])][temp_plus] == (p*-1) && temp_minus>=0)
        {
            if(score_player[(row_count[x])][temp_minus] <= 7 && score_player[(row_count[x])][temp_minus]!= p && score_player[(row_count[x])][temp_minus]!= (p*-1))
            {
                score_player[(row_count[x])][temp_minus] -= 4;
            }
            if(score_player[(row_count[x])][temp_minus-1] <=3 && score_player[(row_count[x])][temp_minus-1]!= p && score_player[(row_count[x])][temp_minus-1]!= (p*-1) && temp_minus-1>=0)
            {
                score_player[(row_count[x])][temp_minus-1] -= 1;
            }
        }
        if(score_cpu[(row_count[x])][temp_minus] == (p*-1) && temp_plus<N)
        {
            if(score_player[(row_count[x])][temp_plus] <= 7 && score_player[(row_count[x])][temp_plus]!= p && score_player[(row_count[x])][temp_plus]!= (p*-1))
            {
                score_player[(row_count[x])][temp_plus] -= 4;
            }
            if(score_player[(row_count[x])][temp_plus+1] <=3 && score_player[(row_count[x])][temp_plus+1]!= p && score_player[(row_count[x])][temp_plus+1]!= (p*-1) && temp_plus+1<N)
            {
                score_player[(row_count[x])][temp_plus+1] -= 1;
            }
        }
        temp_plus = x + 2;
        temp_minus = x - 2;
        if(score_cpu[(row_count[x])][temp_plus] == (p*-1) && temp_minus+1>=0)
        {
            if(score_player[(row_count[x])][temp_minus+1] <=4 && score_player[(row_count[x])][temp_minus+1]!= p && score_player[(row_count[x])][temp_minus+1]!= (p*-1))
            {
                score_player[(row_count[x])][temp_minus+1] -= 1;
            }
        }
        if(score_cpu[(row_count[x])][temp_minus] == (p*-1)&&temp_plus-1<N)
        {
            if(score_player[(row_count[x])][temp_plus-1] <=4 && score_player[(row_count[x])][temp_plus-1]!= p && score_player[(row_count[x])][temp_plus-1]!= (p*-1))
            {
                score_player[(row_count[x])][temp_plus-1] -= 1;
            }
        }
        
        for(i=1,j=7 ; i<4 ; i++,j-=3)
        {
            temp_plus = x + i;
            temp_minus = x - i;
            if (score_cpu[(row_count[x])][temp_plus] == (p*-1) )
            {
                stop_plus=true;
            }
            if (score_cpu[(row_count[x])][temp_minus] == (p*-1))
            {
                stop_minus=true;
            }
            if (score_cpu[(row_count[x])][temp_plus] == p)
            {
                if(score_cpu[(row_count[x])][temp_minus] != p && score_cpu[(row_count[x])][temp_minus] != (p*-1)&&temp_minus>=0)
                    score_cpu[(row_count[x])][temp_minus] += j;
                continue;
            }
            
            if(score_cpu[(row_count[x])][temp_minus] ==p )
            {
                if(score_cpu[(row_count[x])][temp_plus] != p && score_cpu[(row_count[x])][temp_plus] != (p*-1) && temp_plus<N)
                {
                    score_cpu[(row_count[x])][temp_plus] += j;
                }
                continue;
            }
            
            if(temp_plus<N && !stop_plus)
            {
                score_cpu[(row_count[x])][temp_plus] += j;
            }
            
            if(temp_minus>=0 && !stop_minus)
            {
                score_cpu[(row_count[x])][temp_minus] += j;
            }
        }
    }
}

void score_col(int x, int p)
{
    //Scoring for player
    int i,j;
    int temp_plus =0;
    bool stop_plus = false;
    int temp_row = row_count[x];
    // Player score
    if (p == 99)
    {
        if(score_player[temp_row+1][x]==(p*-1) && temp_row-1>=0)
        {
            score_cpu[temp_row-1][x]-= 3;
            if(temp_row-2>=0)
            {
                score_cpu[temp_row-2][x]-= 1;
            }
        }
        for(i=1,j=5 ; i<4 ; i++,j-=2)
        {
            temp_plus = temp_row - i;
            if (score_player[temp_plus][x] == (p*-1))
            {
                stop_plus=true;
            }
            if(score_player[temp_plus][x] == p)
                continue;
            if(temp_plus<N && !stop_plus)
            {
                score_player[temp_plus][x] += j;
            }
        }
    }
    //Score for CPU
    if(p == -99)
    {
        if(score_cpu[temp_row+1][x]==(p*-1) && temp_row-1>=0)
        {
            score_player[temp_row-1][x]-= 3;
            if(temp_row-2>=0)
            {
                score_player[temp_row-2][x]-= 1;
            }
        }
        for(i=1,j=5 ; i<4 ; i++,j-=2)
        {
            temp_plus = temp_row - i;
            if (score_cpu[temp_plus][x] == (p*-1))
            {
                stop_plus=true;
            }
            if(score_cpu[temp_plus][x] == p)
                continue;
            if(temp_plus<N && !stop_plus)
            {
                score_cpu[temp_plus][x] += j;
            }
        }
    }
}






void display()
{
    int i,j;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            cout<< score_player[i][j]<<"	";
        }
        cout<<endl;
    }
    cout<<endl<<endl<<endl<<"--------------------CPU SCORE-----------------"<<endl<<endl<<endl;
    for(i=0;i<N;i++)
    {
        for(j=0;j<N;j++)
        {
            cout<< score_cpu[i][j]<<"	";
        }
        cout<<endl;
    }
    
}

void input(int p)
{
    int x;
    
    while(1)
    {
        cout<<"Enter the COLOUMN : ";
        cin>>x;
        
        if(x<N)
        {
            break;
        }
        else
        {
            cout<<"error:out of bounds"<<endl;
        }
    }
    
    matrix[(row_count[x])][x] = p;
    score(x,p);
    check(x,p);
    row_count[x]--;
    cout<<"--------------------------------------"<<endl;
    
}

void check(int x, int p)
{
    check_row(x,p);
    check_col(x,p);
    check_diag(x,p);
    
}

void check_col(int x, int p)
{
    int i;
    int temp_plus =0;
    bool stop_plus = false;
    int win_count = 0;
    int temp_row = row_count[x];
    for(i=1;i<5;i++)
    {
        temp_plus = temp_row + i;
        if (matrix[temp_plus][x] != p)
        {
            stop_plus=true;
        }
        if(temp_plus<N && matrix[temp_plus][x] == p && !stop_plus)
        {
            win_count++;
        }
    }
    /*-------------------------------------------------*/
    if (win_count >= 3)
    {
        cout<<endl<<"Player " <<p<<" WINS - column"<<endl;
        winningCol = x;
        
    }
}

void check_diag(int x, int p)
{
    int i;
    int temp_plus =0;
    int temp_minus = 0;
    bool stop_upper_plus = false;
    bool stop_upper_minus = false;
    bool stop_lower_plus = false;
    bool stop_lower_minus = false;
    int win_count_left = 0;
    int win_count_right = 0;
    
    for(i=1;i<5;i++)
    {
        temp_plus = x + i;
        temp_minus = x - i;
        //upper right diag
        if (matrix[((row_count[x])-i)][temp_plus] != p)
        {
            stop_upper_plus=true;
        }
        //upper left diag
        if (matrix[((row_count[x])-i)][temp_minus]!=p)
        {
            stop_upper_minus=true;
        }
        // for lower right diag
        if (matrix[((row_count[x])+i)][temp_plus] != p)
        {
            stop_lower_plus=true;
        }
        //lower left diag
        if (matrix[((row_count[x])+i)][temp_minus]!=p)
        {
            stop_lower_minus=true;
        }
        //upper right 
        if(temp_plus<N && matrix[((row_count[x])-i)][temp_plus] == p && !stop_upper_plus)
        {
            win_count_right++;
        }
        
        //upper left diag
        if(temp_minus>0 && matrix[((row_count[x])-i)][temp_minus] == p && !stop_upper_minus)
        {
            win_count_left++;
        }
        //lower right 
        if(temp_plus<N && matrix[((row_count[x])+i)][temp_plus] == p && !stop_lower_plus)
        {
            win_count_right++;
        }
        
        //lower left diag
        if(temp_minus>0 && matrix[((row_count[x])+i)][temp_minus] == p && !stop_lower_minus)
        {
            win_count_left++;
        }
    }
    
    
    /*---------------------------------------------------------------*/
    
    if (win_count_left >= 3 || win_count_right >= 3 )
    {
        cout<<endl<<"Player " <<p<<" WINS"<<endl;
        winningDia = x;
    }
}


void check_row(int x, int p)
{
    int i;
    int temp_plus =0;
    int temp_minus = 0;
    bool stop_plus = false;
    bool stop_minus = false;
    int win_count = 0;
    for(i=1;i<5;i++)
    {
        temp_plus = x + i;
        temp_minus = x - i;
        if (matrix[(row_count[x])][temp_plus] != p)
        {
            stop_plus=true;
        }
        if (matrix[(row_count[x])][temp_minus]!=p)
        {
            stop_minus=true;
        }
        if(temp_plus<N && matrix[(row_count[x])][temp_plus] == p && !stop_plus)
        {
            win_count++;
        }
        
        if(temp_minus>0 && matrix[(row_count[x])][temp_minus] == p && !stop_minus)
        {
            win_count++;
        }
    }
    
    
    /*---------------------------------------------------------------*/
    
    if (win_count >= 3)
    {
        cout<<endl<<"Player " <<p<<" WINS"<<endl;
        winningRow = x;
    }
}

/*------------------------------------------------------------------------------------------------------------*/
int check_playerRowCount()
{
    int max=0;
    for (int i=0; i<N; i++) {
        //max = std::max(score_player[row_count[i]][i],max);
        if (score_player[row_count[i]][i]>score_player[row_count[max]][max]) {
            max =i;
        }
    }
    return max;
}
int check_cpuRowCount()
{
    int max=0;
    for (int i=0; i<N; i++) {
        //max = std::max(score_cpu[row_count[i]][i],max);
        if (score_cpu[row_count[i]][i]>score_cpu[row_count[max]][max]) {
            max =i;
        }
    }
    return max;
}
int CPU_play()
{
    int randnum;
    winningCol =0;
    winningDia =0;
    winningRow =0;
    //First move random
    if (firstPlay){
        //random assignment
        randnum = (rand() % 4)+2;
        firstPlay = false;
        return randnum;
    }
    else{
        for (int i=0; i<N; i++) {
            check(i, 99);
        }
        if (winningCol==0 && winningDia==0 && winningRow==0) {
            int pmax = check_playerRowCount();
            int cmax = check_cpuRowCount();
            if (score_player[row_count[pmax]][pmax]>4) {
                return pmax;
            }
            else{
                return cmax;
            }
        }
        else{
            if (winningDia!=0) {
                return winningDia;
            }
            else if (winningRow!=0){
                return winningRow;
            }
            else return winningCol;
        }
        
    }
    // Check row_count
}

int main(int argc, const char * argv[]) {
    int player = 99;
    display();
    int i=0;
    // Win function call has been commented - test for scoring
    while(i<30)
    {
        input(player);
        player*=-1;
        if (player==-99) {
            cout<<CPU_play()<<" is the predicted col number"<<endl;
        }
        display();
        i++;
    }
    
    return 0;
}

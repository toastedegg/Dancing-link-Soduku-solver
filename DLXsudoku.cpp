#include<algorithm>
#include<vector>
#include<iostream>
#include<string>
#include<chrono>
#include "DLXsudoku.h"

using namespace std;
using namespace std::chrono;

void input(int (*gird)[LENGTH], vector<vector<string>> data) {
	for(int i = 0; i < (int)data.size(); ++ i) {
		for(int j = 0; j < (int)data[i].size(); ++ j) {
			string s = data[i][j];
			long n = stoi(s,nullptr,16);
                        //cout << n << endl;
                        gird[i][j] = n;
		}
	}
}

void print()
{
    for(int i=0;i<LENGTH;i++)
    {
        for(int j=0;j<LENGTH;j++)
        {
            printf("%x ",ans[i][j]);
        }
        cout << endl;
    }
}
int main(int argc,char** argv)
{          
    node_counter = 0;
    freopen(argv[1],"r",stdin);
    DLX solver;
    int board[LENGTH][LENGTH];
    vector<vector<string>> data(LENGTH, vector<string>(LENGTH));
   
    for(int i = 0; i < LENGTH; ++ i) {
		for(int j = 0; j < LENGTH; ++j) { 
			cin >> data[i][j];
		}
	}
   input(board, data);
   
    for(int i = 0; i < LENGTH; ++ i) {
        for(int j = 0; j < LENGTH; ++ j) {
            cout << board[i][j] << " ";
        }
        cout << endl;
    }
    
    for(int i = 0; i < LENGTH; ++i)
    {
      for(int j = 0; j < LENGTH; ++j) 
      {
         ans[i][j] = -1;
      }
    }
    solver.pre_fill(board);
    high_resolution_clock::time_point t1 = high_resolution_clock::now();
    solver.search();
    high_resolution_clock::time_point t2 = high_resolution_clock::now();
    duration<double> time_span = duration_cast<duration<double>>(t2 - t1);
    cout << endl;
    print();
    printf("it took DLX %f seconds to finish input sudoku, the number of searched node is:%d \n",time_span.count(),node_counter);
  
    return 0;

}



















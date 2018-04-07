#include<algorithm>
#include<vector>
#include<iostream>
#include<string>
#include<chrono>

#ifndef DLX_SUDOKU_H
#define DLX_SUDOKU_H
#define SIZE 4

const int LENGTH = SIZE * SIZE;
const int CELL = LENGTH * LENGTH;
const int COL_NUM = CELL * 4;
int counter;
int node_counter;
int ans[LENGTH][LENGTH];
class DLX
{
  public:
  class node
  { 
    public:
    node()
    {
      top = this;
      bottom = this;
      left = this;
      right = this;
      header = this;
      row = 0;
      column = 0;
      value = 0;
    }
    node* top;
    node* bottom;
    node* left;
    node* right;
    node* header;
    int row;
    int column;
    int value;
    void connect(node* previous, node* head)   
    {
      if(previous != nullptr)
      {
         right = previous->right;
         left = previous;
         previous->right->left = this;
         previous->right = this;
      }
      bottom = head;
      top =  head->top;
      head->top->bottom = this;
      head->top = this;
      header = head;
    } 
    
    void cover()
    {
       right->left =  left;
       left->right = right;
       for(node* i = bottom; i != this;i = i->bottom)
       {
         for(node* j = i->right; j != i; j = j->right)
         {
            j->top->bottom = j->bottom; 
            j->bottom->top = j->top;
         }
       }
    }
   
    void uncover() 
    {
       right->left = this;
       left->right = this;
       for(node* i = bottom; i != this;i = i->bottom)
       {
         for(node* j = i->right; j != i; j = j->right)
         {
            j->top->bottom = j; 
            j->bottom->top = j;
         }
       }
    }
  
    
  };
  
  DLX(){
     counter = 0;
     for(int i = 0; i < CELL * LENGTH * 10; ++i)
     {
       garbage_col[i] = new node();
     } 
     
     head = garbage_col[counter++];
     for(int i = 0; i < COL_NUM;++i)   
     {
       header_list[i] = garbage_col[counter++]; 
     }
     for(int i = 0; i < COL_NUM;++i)
     {
       if(i != 0 && i != COL_NUM - 1)
       {
         header_list[i]->left = header_list[i-1]; 
         header_list[i]->right = header_list[i+1];
       }
       head->right = header_list[0];
       header_list[0]->left = head;
       header_list[0]->right = header_list[1];
       head->left = header_list[COL_NUM-1];
       header_list[COL_NUM-1]->right = head;
       header_list[COL_NUM-1]->left = header_list[COL_NUM-2];
     }
    
     for(int i = 0; i < LENGTH; ++i)
     {
       for(int j = 0; j < LENGTH;++j)
       {
          for(int k = 0; k < LENGTH; ++k)
          {
             node *temp1 = garbage_col[counter++];
             temp1->connect(nullptr,header_list[j * LENGTH + CELL * 2 + k]);
             temp1->row = i;
             temp1->column = j;
             temp1->value = k;
             node *temp2 = garbage_col[counter++];
             temp2->connect(temp1,header_list[(i/SIZE*SIZE+j/SIZE)*LENGTH+3*CELL+k]);
             temp2->row = i;
             temp2->column = j;
             temp2->value = k;
             temp1 = garbage_col[counter++];
             temp1->connect(temp2,header_list[i*LENGTH+j]);
             temp1->row = i;
             temp1->column = j;
             temp1->value = k;
             temp2 = garbage_col[counter++];
             temp2->connect(temp1,header_list[i*LENGTH+k+CELL]);
             temp2->row = i;
             temp2->column = j;
             temp2->value = k;
             row_index[i][j][k] = temp2;
          }
       }
     }
   
  }

  void pre_fill(int (&board)[LENGTH][LENGTH])
  {
    for(int i=0;i<LENGTH;i++)
    {
        for(int j=0;j<LENGTH;j++)
        {
            if(board[i][j] != -1)
            {
               node* cur = row_index[i][j][board[i][j]];  
               ans[i][j] = board[i][j];
               cur->header->cover();
               for(node *i = cur->right; i != cur;i = i->right)
               {
                 i->header->cover();
               }
            }
        }
    }
  }

  void deletion(node* cur)
  {
    ans[cur->row][cur->column] = cur->value;
    cur->header->cover();
    for(node *i= cur->right; i != cur;i = i->right)
    {
       i->header->cover();
    }
  }
  void undelete(node* cur)
  {
    ans[cur->row][cur->column] = -1;
    cur->header->uncover();
    for(node *i= cur->right; i != cur;i = i->right)
    {
       i->header->uncover();
    }
  }

  bool search()
  {
    node *min =NULL;
    int cur_num;
    int max =0x7fffffff,now;
    if(head->right == head)
    {
        return 1;
    }
    for(node *i=head->right;i != head;i=i->right)
    {
        cur_num=0;
        for(node *j = i->bottom;j != i;j = j->bottom)
        {
            cur_num++;
        }
        if(cur_num < max)
        {
            min = i;
            max = cur_num;
        }
    }
    for(node *i = min->bottom;i != min;i = i->bottom)
    {
        deletion(i);
        node_counter++;
        if(search())
            return 1;
        undelete(i);
    }
    return 0;
  }
  
  ~DLX()
  {
    for(int i = 0; i < CELL * LENGTH * 10; ++i)
    {
       delete garbage_col[i];
    } 
  }
  node* head;
  node* row_index[LENGTH][LENGTH][LENGTH];
  node* header_list[COL_NUM];
  node* garbage_col[CELL*LENGTH*10]; //this is made for c-style array, becuase it is so hard to do the garbage collection with C style array, we pre-allocate space and collect garbage at once to avoid all the hassles

};


#endif

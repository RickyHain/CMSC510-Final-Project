#include <iostream>
#include <vector>
#include <algorithm> 
using namespace std;

void printVec(vector<char>& vec){
    for(int i = 0; i <vec.size(); i++){
        cout<< vec[i] << " ";
    }
    cout<<endl;
}

void printBoard(vector<vector<char>>& board){
    for(int i = 0; i <9; i++){
        for (int j = 0; j < 9; j++)
        {
            cout << board[i][j]<< "  ";
        }
        cout << endl;
    }
}

vector<char> checkValidSolutions(vector<vector<char>>& board, int r, int c){
    //a vector of all possible values it could be (will be widdled down)
    vector<char> possible = {'1','2','3','4','5','6','7','8','9'};
    
    //Check row
    for (int i = 0; i < 9; i++)
    {
        if (board[r][i]!='.')//logic to avoid empty values
        {
            possible.erase(remove(possible.begin(), possible.end(), board[r][i]), possible.end()); //removes the value found in the row from the possible values index
        }
    }

    
    //Check Column
    for (int i = 0; i < 9; i++)
    {
        if (board[i][c]!='.')
        {
            possible.erase(remove(possible.begin(), possible.end(), board[i][c]), possible.end()); ////removes the value found in the column from the possible values index
        }
    }

    //Check square 

    //together these are used to find the top left corner of the box the given index is in
    int firstRow = ((r)/3)*3; //Find the index of the top of the box it's in 
    int firstCol = ((c)/3)*3; //Find the index of the left most point of the box it's in 

    for(int i = firstRow; i < firstRow+3; i++){
        for(int j = firstCol; j < firstCol+3; j++){
            if (board[i][j]!='.')
            {
                possible.erase(remove(possible.begin(), possible.end(), board[i][j]), possible.end()); //removes the value found in the box from the possible values index
            }
        }
    }

    return possible;
}

void solveSudoku(vector<vector<char>> board){
    vector<char> allPosibilities = {};
    int row; //tracks row of earliest empty cell
    int col; //tracks column of earliest empty cell
    bool found = false; //checks if there are any empty cells

    //this nested loop checks every index untill it finds a '.'
    for (int r = 0; r < 9; r++)
    {
        if (found)
        {
            break; //exits the loop once we find an empty cell
        }
        
        for (int c = 0; c < 9; c++)
        {
            if (board[r][c]=='.')
            {
                //once an empty cell is found we find the possible values it can be and exit the loop
                allPosibilities = checkValidSolutions(board, r, c);
                col = c;
                row = r;
                found=true;
                break;
            }    
        }
    }

    if(found && allPosibilities.size()!=0){ //checks if an empty cell is found and if there are any possible values it can be
        for (int i = 0; i < allPosibilities.size(); i++)
        {
            board[row][col] = allPosibilities[i];
            solveSudoku(board); //tries every possible value for the given cell
        }
    }
    if(!found){//if there are no empty cells, we have solved the problem
        printBoard(board);
    }
    
}
    


int main(){
    vector<vector<char>> board = {
    {'5', '3', '.', '.', '7', '.', '.', '.', '.'},
    {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
    {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
    {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
    {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
    {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
    {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
    {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
    {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

    printBoard(board);
    cout<<endl;

    solveSudoku(board);

    return 0;
}
#include<bits/stdc++.h>
using namespace std;

void print(vector<vector<int> > &board)
{
	// This prints the board. 1 means player who goes 1st. 2 means player who starts second. 0 means unfilled space.
	int rows = board.size();
	int cols = board[0].size();
	
	for(int i=0;i<cols;i++)cout<<i+1<<" ";
	cout<<endl;
	for(int i=0;i<cols;i++)cout<<"--";
	cout<<endl;

		for(int i=0;i<rows;i++)
		{
			for(int j=0;j<cols;j++)cout<<board[i][j]<<" " ;
			cout<<endl;
		}
	for(int i=0;i<cols;i++)cout<<"--";
	cout<<endl;
}

int checkWin(vector<vector<int> > &board,int col,int row,int turn)
{ 
	// This is the most important logic. This function check in all the directions of combination of 4 connection
	int val=-1;
	int rows = board.size();
	int cols = board[0].size();
	if(turn%2 == 0) val = 2;
	else if(turn%2 ==1) val = 1;

	
	for(int i=3;i>=0;i--) // iteration that makes sure all positions of last coin is captured
{
	//case1 |
	//		|
	//		|

	if(row-i >=0)
	{
		if(row - i +3 < rows)
		{
			if(board[row-i][col]==val and board[row-i+1][col]==val and board[row-i+2][col]==val and board[row-i+3][col]==val ) return val;
		}
	}


	//case2 <----->
	if(col+i<cols)
	{
		if(col+i-3 >=0)
		{
			if(board[row][col+i]==val and board[row][col+i-1]==val and board[row][col+i-2]==val and board[row][col+i-3]==val) return val;
		}
	}


	//  case3   /
	//         /

	if(col+i<cols)
	{
		if(col+i-3 >=0)
		{
			if(row-i>=0)
			{
				if(row-i+3 < rows)
				{
					if(board[row-i][col+i]==val and board[row-i+1][col+i-1]==val and board[row-i+2][col+i-2]==val and board[row-i+3][col+i-3]==val) return val;

				}
			}
		}
	}


	//	        \
	//   case4   \
	if(col-i>=0)
	{
		if(col-i+3 <cols)
		{
			if(row-i>=0)
			{
				if(row-i+3 < rows)
				{
					if(board[row-i][col-i]==val and board[row-i+1][col-i+1]==val and board[row-i+2][col-i+2]==val and board[row-i+3][col-i+3]==val) return val;

				}
			}
		}
	}
	//case4
}
	return 0;
	
}

int place(vector<vector<int> > &board,vector<int> &isFull,int turn , int col)
{
	// This function places the coin in the lowest gap of the provided column.
	// Topmost row is row 0. bottomost row is the variable names "rows"

	int i;
	int val=-1;
	
	if(turn%2 ==0) val = 2;
	if(turn%2 ==1) val = 1;
	int rows = board.size();
	
	for( i=rows-1;i>=0;i--)
	{
		
		if(board[i][col]==0)
			{
				board[i][col] = val;
				break;
			} 
	}
	if(i==0)isFull[col]=1; 
	
	return i;
}

int decideCol(vector<int> &isFull)
{		

// This function verifies the correctness of the Column input given by the player. It also
// checks if the column is already full.

		int col;
		int cols = isFull.size();
		
		while(1)
		{
			cin>>col;
			
			while(col<=0 or col>cols )
			{
				cout<<"Enter a valid column"<<endl;
				cin>>col;
			}
			col--;
			
			if(isFull[col]) cout<<"Enter new column as this one is full"<<endl;
			
			else return col;
		}
		return 0;
}

int play(vector<vector<int> > &board,vector<int> &isFull,int turn, char robo)
{

// Driver function that simulates the game.
	int cols = board[0].size();
	int count = 0,col,row;

	for(int i=0;i<cols;i++)
	{
		if(isFull[i])count++;
		else break;
	} 
	if(count==cols) return 3; // Case of TIE
	
	cout<<"Enter valid column"<<endl;
	
	if(robo=='N')
	{
		col = decideCol(isFull);
		row = place(board,isFull,turn,col); // placement of the coinby player
	}
	else // Logic by which computer decides its column. 
	{
		for(int i=0;i<cols;i++) 
			if(!isFull[i])
			{
				
				col=i;
				row = place(board,isFull,turn,i); // placement of the coin by computer
				break;
			} 
	} 

	int winStat = checkWin(board,col,row,turn); // Checks if the player wins after his move.
	return winStat;

}

bool isNum(char number[])
{
    int i = 0;

    //checking for negative numbers
    if (number[0] == '-')
    {

        return false;
    }
    for (; number[i] != 0; i++)
    {
        //if (number[i] > '9' || number[i] < '0')
        if (!isdigit(number[i]))
            return false;
    }
    return true;
}

int main(int argc, char *argv[])
{

	if(argc<4) 
	{
		cout<<"insufficient parameters passed. Program ends. "<<endl;
		return 0;
	}

		int players,cols,rows;
		
		if(isNum(argv[1]) and  isNum(argv[2]) and isNum(argv[3]))
		{
			 players = atoi(argv[1]);
			 cols = atoi(argv[2]);
			 rows = atoi(argv[3]);
		}
		else
		{
			cout<<"The Command line paramenters are not in Domain. Program ends."<<endl;
			return 0;
		}

		char cont = 'Y';
		while(cont=='Y' or cont=='y') // Loop to play game again and again
	  {

		vector<vector<int> > board(rows,vector<int>(cols,0)); 

		vector<int>isFull(cols,0); // shows if the column is full or not

		if(players == 2)
		{
			int win = 0;
			int turn = 1;
			int val;
			
			while(win==0)
			{
				if(turn%2) val = 1;
				else val = 2;
				print(board);
				cout<<"player "<<val<<"'s turn"<<endl;
			    win = play(board,isFull,val,'N');
				turn++;
			}

			if(win==1)cout<<"Player 1 wins"<<endl;
			else if(win==2)cout<<"Player 2 wins"<<endl;
			else if(win == 3)cout<<"The game is TIE"<<endl;

			
		} // end of 2 players if

		else
		{
			int win = 0,choice=1;
			cout<<"Do you wanna go first? 1 = Yes , 2 = No "<<endl;
			cin>>choice;
			if(choice==1)
			{
				int turn = 1;
				while(win==0)
				{
					print(board);
					if(turn%2)
					{

						cout<<"player's "<<"turn"<<endl;
					    win = play(board,isFull,turn%2,'N');
						turn++;
					}
					else
					{
						cout<<"Computer's turn"<<endl;
						win = play(board,isFull,turn%2,'Y');
						turn++;
					}
					
				}

				if(win==1) cout<<"Player 1 wins"<<endl;
				else if(win==2) cout<<"Computer wins"<<endl;
				else if(win==3) cout<<"The game is TIE"<<endl;

			
			} // end of player goes first
			else
			{
				int turn = 1;
				while(win==0)
				{
					print(board);
					if(turn%2)
					{
						
						cout<<"Computer's turn"<<endl;
						win = play(board,isFull,turn%2,'Y');
						turn++;
					}
					else
					{
						cout<<"player "<<turn%2<<"'s turn"<<endl;
					    win = play(board,isFull,turn%2,'N');
						turn++;
					}	
				}
				if(win==1) cout<<"Computer wins"<<endl;
				else if(win==2) cout<<"Player wins"<<endl;
				else if(win==3) cout<<"The game is TIE"<<endl;

				
			} // end of comp goes first
			
			
		} // end of single player else

		cout<<"---------------------------------"<<endl;
		cout<<"Wanna play again? Y == yes, N == No"<<endl;
		cin>>cont;

	}//end of while 
}
	

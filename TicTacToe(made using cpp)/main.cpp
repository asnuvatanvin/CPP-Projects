#include<bits/stdc++.h>
using namespace std;
char game[9]= {'1','2','3','4','5','6','7','8','9'};
char mark[9]= {'n','n','n','n','n','n','n','n','n'};
void board()
{
    system("cls");//refreshes the screen
    cout<<"\t\tTic Tac Toe"<<endl;
    cout<<"      Player One : X"<<"  "<<"Player Two : O"<<endl;
    cout<<"     Press the number you want to put X/0 in"<<endl;
    cout<<"\t ________ ________ ________"<<endl;
    cout<<"\t|        |        |        |"<<endl;
    cout<<"\t|   "<<game[0]<<"    |   "<<game[1]<<"    |   "<<game[2]<<"    |"<<endl;
    cout<<"\t|________|________|________|"<<endl;
    cout<<"\t|        |        |        |"<<endl;
    cout<<"\t|   "<<game[3]<<"    |   "<<game[4]<<"    |   "<<game[5]<<"    |"<<endl;
    cout<<"\t|________|________|________|"<<endl;
    cout<<"\t|        |        |        |"<<endl;
    cout<<"\t|   "<<game[6]<<"    |   "<<game[7]<<"    |   "<<game[8]<<"    |"<<endl;
    cout<<"\t|________|________|________|"<<endl;

}
bool check()
{
    if(game[0]==game[1] && game[1]==game[2])
        return true;
    else if(game[3]==game[4] && game[4]==game[5])
        return true;
    else if(game[6]==game[7] && game[7]==game[8])
        return true;
    else if(game[0]==game[3] && game[3]==game[6])
        return true;
    else if(game[1]==game[4] && game[4]==game[7])
        return true;
    else if(game[2]==game[5] && game[5]==game[8])
        return true;
    else if(game[0]==game[4] && game[4]==game[8])
        return true;
    else if(game[2]==game[4] && game[4]==game[6])
        return true;
    else
        return false;
}
int main()
{
    board();
    int n=9,i=0;
    while(n--)
    {

        if(i%2==0)
        {
            int turn,a=0;
            while(1)
            {
                cout<<"\n\tPlayer One: ";
                cin>>turn;
                if(mark[turn-1]!='n' || turn<0 || turn>9)
                {
                    cout<<"\tInvalid Move";
                    cout<<"\tTry Again"<<endl;
                    a++;
                    if(a==3)
                    {
                        return 0;
                    }
                    continue;
                }
                else{
                    break;
                }

            }
            mark[turn-1]=turn;
            if(turn==1)
                game[0]='X';
            else if(turn==2)
                game[1]='X';
            else if(turn==3)
                game[2]='X';
            else if(turn==4)
                game[3]='X';
            else if(turn==5)
                game[4]='X';
            else if(turn==6)
                game[5]='X';
            else if(turn==7)
                game[6]='X';
            else if(turn==8)
                game[7]='X';
            else if(turn==9)
                game[8]='X';
            else
            {
                cout<<"\tInvalid Move";
                cout<<"\tTry Again"<<endl;
            }
            cin.get(); //takes string with spaces as input
            board();
            if(check())
            {
                cout<<"\n\tPlayer One Wins!!"<<endl;
                return 0;
            }
            i++;
        }
        else
        {
            int turn,a=0;
            while(1)
            {
                cout<<"\n\tPlayer Two: ";
                cin>>turn;
                if(mark[turn-1]!='n' || turn>9 || turn<0)
                {
                   cout<<"\tInvalid Move";
                   cout<<"\tTry Again"<<endl;
                   a++;
                   if(a==3)
                   {
                       return 0;
                   }
                }
                else{
                    break;
                }
            }
            mark[turn-1]=turn;
            if(turn==1)
                game[0]='O';
            else if(turn==2)
                game[1]='O';
            else if(turn==3)
                game[2]='O';
            else if(turn==4)
                game[3]='O';
            else if(turn==5)
                game[4]='O';
            else if(turn==6)
                game[5]='O';
            else if(turn==7)
                game[6]='O';
            else if(turn==8)
                game[7]='O';
            else if(turn==9)
                game[8]='O';
            else
            {
                cout<<"\tInvalid Move";
                cout<<"\tTry Again"<<endl;
            }
            cin.get();
            board();
            if(check())
            {
                cout<<"\n\tPlayer Two Wins!!"<<endl;
                return 0;
            }
            i++;

        }

    }
    cout<<"\n\tIt's a TIE"<<endl;
    return 0;
}

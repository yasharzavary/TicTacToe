//yashar zavary rezaie
#include<iostream>
#include<fstream>
#include<conio.h>
using namespace std;

struct player{
	char Name[40];
	int Won_Time = 0;
	int Lose_Time = 0;
	int draw = 0;
};
//a func for show our scoreboard
void Score_Board_Show(int);

// a func for order the list by score(my standard is : diff beetwen won and lose)
void Order_The_Players(int);

//same name control
bool Same_Name(int, player, player);

//calculate number of charcacter
int C_Calcualtor(player);

//show our game board
void Game_Board_Show(char[]);

//winner controller
int Win_Control(char[]);

//game assitance that work with players
void Game_Asistance(player,player,char[]);

//
int Win_Returner(char[], int);
void Write_In_File(player);

int Diff_Finder(string);

int Find_Lengh(string);

int main()
{
	player P1;
	player P2;
	int Play_Again_Option;
	int Option;
	int Player_Counter = 0;
	char Game_Board[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
	char support[9] = {'1', '2', '3', '4', '5', '6', '7', '8', '9'};
	while(true){
		cout<<"1.Start game\n2.Scoreboard\n3.Exit\n";
		cin>>Option;
		switch(Option){
			case 1:
				cout<<"Player one's name : ";
				Player_Counter += 1;
				cin.getline(P1.Name, 40);
				cin.getline(P1.Name, 40);
				cout<<"Player two's name : ";
				cin.getline(P2.Name, 40);
				if(Same_Name(Player_Counter, P1, P2)){
					/* TODO (#1#): change name 2 */
					int t = C_Calcualtor(P2);
					P2.Name[C_Calcualtor(P2)] = '-';
					P2.Name[C_Calcualtor(P2) + 1] = '1';
					P2.Name[C_Calcualtor(P2) + 2] = '\0';
				}
				while(true){
				for(int i = 0; i < 9; i++){
					Game_Board[i] = support[i];
				}
				Game_Asistance(P1, P2, Game_Board);
				cout<<"play again?(1 for yes and 2 for no): ";
				cin>>Play_Again_Option;
				if(Play_Again_Option != 1){
					break;
				}
				for(int i = 0; i < 9; i++){ 
					Game_Board[i] = support[i];
				}
			}
				break;
			case 2:
				Order_The_Players(Player_Counter);
				Score_Board_Show(Player_Counter);
				break;
			case 3:
				exit(0);
				break;
		
	}
}

	return 0;
}


void Score_Board_Show(int x){
	string Stext;
	cout<<"name W L D"<<endl;
	ifstream SScore_Board("score.txt");
	if(!SScore_Board){
		cout<<"past players is empty!";
		return;
	}
	while(getline(SScore_Board, Stext)){
		cout<<Stext<<endl;
	}
	SScore_Board.close();
	
}

int Diff_Finder(string x){
	int count;     
	count = 0;
	for(int j = 0;;j++){
		if(count == 1){
			return x[j] - x[j + 2];	
		}
		if(x[j] == ' '){
			count += 1;
		}
		}
	}



void Order_The_Players(int x){
	/* TODO (#3#): open file, read it and order it by score */
	string Keeper_For_Order[40];
	string OString;
	ifstream OScore_Board("score.txt");
	int OT = 0;
	while(getline(OScore_Board, OString)){
		Keeper_For_Order[OT] = OString;
		OT += 1;
	}
	OScore_Board.close();
	
	for(int i = 0; i < OT - 1; i++){
		for(int j = 0; j < OT - i - 1; j++){
			if(Diff_Finder(Keeper_For_Order[j]) > Diff_Finder(Keeper_For_Order[j + 1])){
				swap(Keeper_For_Order[j], Keeper_For_Order[j + 1]);
			}
		}
	}
	
	ofstream BScore_Board("score.txt");
	for(int i = OT - 1; i >= 0; i--){
		BScore_Board<<Keeper_For_Order[i];
		BScore_Board<<"\n";
	}
	BScore_Board.close();
	
	
	
}


int C_Calcualtor(player a){
	int t = 0;
	for(int i = 0 ; a.Name[i]; i++){
		t += 1;
	}
	return t;
		
}


bool Same_Name(int x, player a, player b){
	if(C_Calcualtor(a) != C_Calcualtor(b)){
		return false;
	}
	for(int i = 0; i < C_Calcualtor(a); i++){
		if(a.Name[i] != b.Name[i]){
			return false;
		}
	}
	return true;
	
}

void Game_Board_Show(char x[]){
	cout<<"------------------------------------";
	for(int i = 0; i < 9; i++){
		if(i % 3 == 0){
			cout<<endl<<"|";
			}
		cout<<x[i]<<"|";
		
	}
	cout<<endl;
}
int Win_Returner(char x[], int y){
		if(x[y] == 'X'){
			return 1;
		}
		else{
			return -1;
		}
}
int Win_Control(char x[]){
	int t;
	// i look and see that this places must controlled
	//now because just 1 and 3 have unic func...i do it unic
	int Find_ArrayA[3] = {0, 3, 6};
	if(x[0]==x[4]&&x[0]==x[8]){
		return Win_Returner(x, 0);
	}
	if(x[2]==x[4]&&x[2]==x[6]){
		return Win_Returner(x, 2);
	}
	for(int i = 0; i < 3; i++){
		t = Find_ArrayA[i];
		if(x[t]==x[t+1]&&x[t]==x[t+2]){
			return Win_Returner(x,t);
		}
	}
	for(int i = 0; i < 3; i++){
		if(x[i]==x[i+3]&&x[i]==x[i+6]){
			return Win_Returner(x,i);
		}
	}

	return 0;
	
}
					//X             O      
void Game_Asistance(player a,player b,char x[]){
	int counter = 0;
	int t = 0;
	while(true){
		Game_Board_Show(x);
		if(counter >= 5){
			int temp;
			temp = Win_Control(x);
			switch(temp){
				case 1:
					cout<<a.Name<<" win the game!\n";
					a.Won_Time += 1;
					b.Lose_Time += 1;
					Write_In_File(a);
					Write_In_File(b);
					return;          

				case -1:
					cout<<b.Name<<" win the game!\n";
					b.Won_Time += 1;
					a.Lose_Time += 1;
					Write_In_File(a);
				    Write_In_File(b);
					return;          
			}
		}
		if(counter == 9){
			cout<<"Draw!\n";
			a.draw += 1;
			b.draw += 1;
			Write_In_File(a);
			Write_In_File(b);
			return;     

		}
		int control = 0;
		while(true){
			if(control == 0){
			if(counter % 2 == 0){
				cout<<a.Name<<"'s turn"<<endl;
			}
			else{
				cout<<b.Name<<"'s turn"<<endl;
			}
		}
			control = 0;
			t = getch() - 49;
			if(x[t] == 'X' || x[t] == 'O'){
				cout<<"you can fill that place!...try again"<<endl;
				control = 1;
				continue;
			}
			if(counter % 2 == 0){
				x[t] = 'X';
				break;
			}
			else{
				x[t] = 'O';
				break;
			}

	}
		counter += 1;
}

}

int Find_Lengh(char x[]){
	int temp = 0;
	for(int i = 0; x[i];i++){	
		temp += 1;
	}
	return temp;
}


void Write_In_File(player x){
	string Keeper_For_Write[40];
	string Wtext;
	int WT = 0;
	ifstream Save_Data_For_Write("score.txt");
	if(!Save_Data_For_Write){
		Save_Data_For_Write.close();
	}
	else{
		while(getline(Save_Data_For_Write, Wtext)){
			Keeper_For_Write[WT] = Wtext;
			WT += 1;
		}
		Save_Data_For_Write.close();
	}
	
	int ass, j, writeass = 0;
	int Lengh = Find_Lengh(x.Name);
	for(int i = 0; i < WT; i++){
		if(!Keeper_For_Write[i].find(x.Name)){
			writeass = -1;
			Keeper_For_Write[i][Find_Lengh(x.Name) + 1] += x.Won_Time;
			Keeper_For_Write[i][Find_Lengh(x.Name) + 3] += x.Lose_Time;
			Keeper_For_Write[i][Find_Lengh(x.Name) + 5] += x.draw;
		}
	}

	ofstream Write_New("score.txt");
	if(writeass == 0){
		Write_New<<x.Name<<" "<<x.Won_Time<<" "<<x.Lose_Time<<" "<<x.draw<<"\n";
}
	for(int i = 0; i < WT; i++){
		Write_New<<Keeper_For_Write[i]<<"\n";
	}
	Write_New.close();
}


















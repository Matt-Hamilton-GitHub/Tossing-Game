 //                                            ********* Writer: Matt Hamilton    *********
 //                                             ******** Class: CS 136            ******** 
 //                                              ******* Professor: Brian Dauzat  *******
 //                                                ***** Test 1 Problem 1         *****
 //                                                 **** ======================== ****
 //                                                   **  *** *** *** *** *** *** **

//Write a program that simulates the following coin tossing game.
//
// 
//
//At the beginning of the game, N players each has M points.
//Each players tosses one unbiased coin into the air and the players count the number of heads 
//and the number of tails that appear when the coins fall to the ground. 

//If the number of heads is greater than the number of tails, 
//then the players who tossed heads each adds a positive integer P to their points and the players who tossed tails each subtracts 
//the same positive integer P from their points. 

//The players perform the opposite actions when the number tails are greater than the 
//number of heads. 
//If the number of heads equals the number of tails no player gains any points and no player loses any points.
//If any player’s points fall below than one, then the player is removed from the game.
//P’s initial value is one. After each set of coin tosses, the game adds one to P.
//
//The players continue to toss coins until a certain minimum number of players remains. 
//The players with the greatest number of points wins.
//
//The players have names and points.
//
//Display all the players points.
//
//Display the final value of P
//
//Display the names of the winning players
//
//Display the outcome of each coin toss
//
//Display the number of coin tosses
//



#include <iostream>
#include <random>
#include <string>
#include <vector> 
#include <map>

using namespace std;

class CoinTossingGame {
private:

	string _player_name;
//as a player gets eliminated from the game, boolean eliminated sets to true and the game shows the player's status
	bool _eliminated {false};

//the program also keeps the track of all points for each player
	int _points{0};

		
public: 


//getters
	int getPoints(){return _points;}
	string getName(){return _player_name;}

	bool getStatus(){return _eliminated;}
	
//setters
	
	void eliminate(){_eliminated = true;}
	void setPoints(int p){_points = p;}
	void setName(string name){_player_name = name;}
	
//custom methods
	void inc_point(int num){_points+= num;}
	void dec_point(int num){_points-=num;}

	
};



 random_device rdevice{};
 

void setPlayersNames(CoinTossingGame *players, int num);//sets default name for each player, max number of names it has - 20
unsigned int genNum();//generates a random number from 0 to 1
void tossTheCoin(CoinTossingGame *players,int num, int &heads, int &tails,  map<int, int> &res);//
void setDefPoints(CoinTossingGame *players, int num, int points_num, map<int, int> &res);//sets default pointsfor each player
void displayPoints(CoinTossingGame *players, int num);
void displayCurrentPlayers(CoinTossingGame *players, int num);//display players who are not eliminated 
void assignPoints(CoinTossingGame *players, int heads, int tails,  map<int, int> &res, int p);//the algorithm of assigning points after each tossing
void getTheWinner(CoinTossingGame *players, int num, vector<int> participants);//show the winners of the game / max number of winners is 2



int main()
{
	
	int MAX_PLAYERS{20};
	unsigned int MAX_WINNERS{2};
	
	cout << "\tWelcome to The Tossing Game\n";
	cout << "\t***************************\n";
	
	
	int players_num{0};
	int points_num{0};
	int p{1};
	int round{1};
	int numOfHead{0};
	int numOfTails{0};
	

       
	vector<int> participants;//the vector stores the players who are not eliminated 
	map<int, int> results;
	
//At the beginning of the game, N players each has M points.
//user sets the number of points and players 

	bool gameOver{false};//defines the end of the game
	
	
	cout << "Number of players [less than " << MAX_PLAYERS + 1 << " ]: ";
	cin >> players_num;
	cout << "Number of points: ";
	cin >> points_num;
	
	CoinTossingGame players[players_num];//here we create an array of classes for each user to store number of points and names
	
	//below we store all the players who are not eliminated yet to the vector
	for(int index{0}; index < players_num; index++){
			if(players[index].getStatus() != true)
			 participants.push_back(index);
		}
		
	//-------------------------------

	//set names
	setPlayersNames(players, players_num);


//below we call a function that sets the initial amount of points for all participants and create an empty map 
//that will store the results [index - points] for each round
   
   setDefPoints(players, players_num, points_num, results);
	
	//-------------------------------
	
		
//and before the program starts the game, it displays the initial amount of points for each player


	displayPoints(players, players_num);
	
		
//---------------		
	
	while(gameOver != true){//the game starts and runs till gameOver equals to true
		
		cout << "\n\tRound " << round << endl;//display each round
		cout << "\t------ \n" << endl;
		
		tossTheCoin(players, players_num, numOfHead, numOfTails, results);
		assignPoints(players,numOfHead, numOfTails, results, p);
								
			
	//------------show points of players that are not eliminated (after the round)
		
		displayPoints(players, players_num);	
		
  //--------------------------------------------------------------------------
  
  // ----------Display the Eliminated players who have 0 or less points
  displayCurrentPlayers(players, players_num);
		
		
		results.clear();//claer results
		numOfHead = 0;//clear number of heads for the next round
		numOfTails = 0;//clear number of tails for the next round
		
		
	// update the vector with the participants 
	
	participants.clear();// clear the vector with the participants
	
		for(int index{0}; index < players_num; index++){
			if(players[index].getStatus() != true)
			 participants.push_back(index);
	
		}
		
	//------------------------------------------
	
	//finally if the number of remaining participants is less or equal to 2 then the game is over
	//and also lets set the max number of rounds to be 25
	
		if(participants.size() <= MAX_WINNERS){
			gameOver = true;
			
		}
		else{
		p+=p;//increase p 
		round++;
		}
			
	};
	

	
	//dipsaly the winners
	
	getTheWinner(players, players_num, participants);
	cout<< "-----------------------------\n";
	cout << "The final value of P = " << p << " ****" << endl;
	cout << "The coin has been tossed " << round << " times ****" << endl;
	
	
	system("pause");
	return 0;
}




  unsigned int genNum(){
	default_random_engine num{rdevice()};
	uniform_int_distribution< unsigned int> randomNum{0,1};
	
	
	return randomNum(num);
	
}

void setPlayersNames(CoinTossingGame *players, int num){
	
	string def_players_names[20] = {"Liam","Olivia","Noah","Emma","Oliver","Ava","William","Sophia","Elijah", "Isabella",
	"James","Charlotte","Benjamin","Amelia","Lucas","Mia","Mason","Harper","Ethan","Evelyn"};
	
	for(int count{0}; count  < num; count++){
		players[count].setName(def_players_names[count]);
	}
	
};


void setDefPoints(CoinTossingGame *players, int num, int points_num, map<int, int> &res){
	
	for(int index{0}; index < num; index++){
			 players[index].setPoints(points_num);
			 res.insert({index, 0});
	
		}
	
}

void displayPoints(CoinTossingGame *players, int num){
	cout<< "\t------------------------------\n";
	for(int index{0}; index < num; index++){
			
			if(players[index].getStatus() != true)
				cout << "\t " << players[index].getName() << " total points: [ " <<players[index].getPoints() << " ]\n"; 
		}	
	
	cout<< "\t------------------------------\n";
};


void displayCurrentPlayers(CoinTossingGame *players, int num){
	for(int index{0}; index < num; index++){
			if(players[index].getPoints() <= 0){
				players[index].eliminate();
				cout << "***** " << players[index].getName() << " - eliminated" << endl;
			}
		}
}

void assignPoints(CoinTossingGame *players, int heads, int tails, map<int, int> &res, int p){
	
			//***** Cases ******
										
										
		//---------- Heads > Tails
			
//If the number of heads is greater than the number of tails, 
//then the players who tossed heads each adds a positive integer P to their points and the players who tossed tails each subtracts 
//the same positive integer P from their points. 

			if(heads > tails){
				cout << "***** Heads > Tails ****" << endl;
				cout << "***** P = " << p << " ****" << endl;
				for( auto it: res){
					if(it.second == 1)
					players[it.first].inc_point(p); //increase the number of point by P  
					else
					players[it.first].dec_point(p);//decrease the number of point by P 
				}
			}
			
		//---------- Heads < Tails
			
//The players perform the opposite actions when the number tails are greater than the number of heads. 
//Meaning that If the number of heads is less than the number of tails, 
//then the players who tossed heads each subtracts a positive integer P from their points
// and the players who tossed tails add P to their points


			else if ( heads < tails){
				cout << "***** Heads < Tails ****" << endl;
				cout << "***** P = " << p << " ****" << endl;
				
				for( auto it: res){
					if(it.second == 1)
					players[it.first].dec_point(p);
					else
					players[it.first].inc_point(p);
				}
			}else{
				
//If the number of heads equals the number of tails no player gains any points and no player loses any points.

				cout << "***** Heads = Tails ****" << endl;
				cout << "***** P = " << p << " ****" << endl;
			}
	
	
}

void getTheWinner(CoinTossingGame *players, int num, vector<int> participants){
		cout << "\t***************************\n";
		cout << "\t******* Game Over *********\n";
	
	int winner_index;//holds the winner's index
	bool greater;
	
	if(players[participants[0]].getPoints() == players[participants[1]].getPoints()){
		cout << "The Winners of The Game: \n";
		for(int index{0}; index < num; index++){
		if(players[index].getStatus() == false)
			cout << "\n\t" << players[index].getName()  << ", points - " << players[index].getPoints() ;
		}
	
	}else
	{
	for(int outer {0}; outer < num; outer++){
		greater = true;
		for(int inner{0}; inner < num; inner++){
			if(players[outer].getPoints() >= players[inner].getPoints() && greater == true){
				winner_index = outer;
			}else{
				greater = false;
			}
			}
			if(greater == true)
				break;
		}
	
	cout << "The Winner of The Game is " << players[winner_index].getName() << " : " 
	<< players[winner_index].getPoints() << " points "<< endl;
	
	//display the remaining winners
	
	
	cout << "\n\n\t Other Winners: " ;
	
	for(int index{0}; index < num; index++){
		if(players[index].getStatus() == false && index != winner_index)
			cout << "\n\t" << players[index].getName()  << ", points - " << players[index].getPoints() ;
		}
		
	}
	cout << endl;
}


void tossTheCoin(CoinTossingGame *players,int num, int &heads, int &tails,  map<int, int> &res){
	
	int tossed;

	cout<< "\t------------------------------\n";
	//
		for(int index{0}; index < num; index++){
			
			if(players[index].getStatus() == false){			
			cout << "\t " << players[index].getName() << " Tosses The Coin ... : "; 
			tossed = genNum();//tossing the coin
			
			if(tossed == 0)
				cout << "Tail" << endl;
			else
				cout << "Head" << endl;
			
			
			res[index] = tossed; //store the result for each index that represents a player
			
			//below the program counts the number of heads and tails for each round, 
			//where 0 is the tail and 1 is the head
				if(tossed == 0)
					tails++;
				else
					heads++;
			}	
		}	
		cout<< "\t------------------------------\n";
}
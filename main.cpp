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
//nd the number of tails that appear when the coins fall to the ground. 

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

	bool _eliminated {false};

	int _points{0};
	int _heads{0};
	int _tails{0};
	
		
public: 

//CoinTossingGame(int num_points)
//:_points(num_points){}

//getters
	int getPoints(){
		return _points;
	}
	
	int getHeads(){
		return _heads;
	}
	
		int getTails(){
		return _tails;
	}
	
	bool getStatus(){
		return _eliminated;
	}
	
	//setters
	
	void eliminate(){
		_eliminated = true;
	}
	void setPoints(int p){
		 _points = p;
	}
	
	void setHeads(int h){
		 _heads = h;
	}
	
	void setTails(int t){
		_tails = t;
	}
	
	
	void inc_point(int num){
		_points+= num;
	}
	void inc_heads(){
		_heads++;
	}
	void inc_tails(){
		_tails++;
	}
	

	
	
	void dec_point(int num){
		_points-=num;
	}
	void dec_heads(){
		_heads--;
	}
	void dec_tails(){
		_tails--;
	}
	
	
	
};

 random_device rdevice{};


 unsigned int tossCoin();
// void setInPoints(CoinTossingGame p[], int num, int points);




int main()
{
	
	
	cout << "\tWelcome to The Tossing Game\n";
	cout << "\t***************************\n";
	
	int players_num{0};
	int points_num{0};
	int p{1};
	int tossed;
	int numOfHead{0};
	int numOfTails{0};
	
	vector<int> participants;
	map<int, int> results;
	
	bool gameOver{false};
	cout << "Number of players: ";
	cin >> players_num;
	cout << "Number of points: ";
	cin >> points_num;
	
	CoinTossingGame players[players_num];
	
	for(int index{0}; index < players_num; index++){
			if(players[index].getStatus() != true)
			 participants.push_back(index);
	
		}
		

   
		
	for(int index{0}; index < players_num; index++){
			 players[index].setPoints(points_num);
			 results.insert({index, 0});
	
		}
		
	for(int index{0}; index < players_num; index++){
			
			if(players[index].getStatus() != true)
				cout << "\tPlayer " << index + 1 << " total points: [ " <<players[index].getPoints() << " ]\n"; 
		}	
	
	while(gameOver != true){
		cout << "\n\tRound " << p << endl;
		cout << "\n\t------ " << endl;
	
		
		
		for(int index{0}; index < players_num; index++){
			
			if(players[index].getStatus() == false){
//				cout << "\tPlayer " << index + 1 << " is Eliminated \n"; 
//			}else{
//				
			cout << "\tPlayer " << index + 1 << " Tosses The Coin ... : "; 
			tossed = tossCoin();
			cout << tossed << endl;
			results[index] = tossed;
				if(tossed == 0)
					numOfTails++;
				else
					numOfHead++;
			
			}	
		}	
			
		//---------- Heads > Tails
			
			if(numOfHead > numOfTails){
				cout << "***** Heads > Tails ****" << endl;
				cout << "***** P = " << p << " ****" << endl;
				for( auto it: results){
					if(it.second == 1)
					players[it.first].inc_point(p);
					else
					players[it.first].dec_point(p);
				}
			}
			
		//---------- Heads < Tails
			
			else if ( numOfHead < numOfTails){
				cout << "***** Heads < Tails ****" << endl;
				cout << "***** P = " << p << " ****" << endl;
				
				for( auto it: results){
					if(it.second == 1)
					players[it.first].dec_point(p);
					else
					players[it.first].inc_point(p);
				}
			}else{
				cout << "***** Heads = Tails ****" << endl;
				cout << "***** P = " << p << " ****" << endl;
			}
			
		
		
		for(int index{0}; index < players_num; index++){
			
			if(players[index].getStatus() != true)
				cout << "\tPlayer " << index + 1 << " total points: [ " <<players[index].getPoints() << " ]\n"; 
		
		}	
		
		
		for(int index{0}; index < players_num; index++){
			if(players[index].getPoints() <= 0){
				players[index].eliminate();
				cout << "***** Player # " << index+1 << " - eliminated" << endl;
			}
		}
		
		results.clear();
		p++;
		numOfHead = 0;
		numOfTails = 0;
		participants.clear();
		
		for(int index{0}; index < players_num; index++){
			if(players[index].getStatus() != true)
			 participants.push_back(index);
	
		}
		
		if(participants.size() <= 2)
			gameOver = true;
	};
	
	cout << "\t***************************\n";
	cout << "\t******* Game Over *********\n";
	
	
	cout << "\n\n\tWinners: " ;
	
	for(int index{0}; index < players_num; index++){
		if(players[index].getStatus() == false)
			cout << "Player #" << index +1 << ", ";
		}
		
		cout << endl;
		
	system("pause");
	return 0;
}


  unsigned int tossCoin(){
	 default_random_engine num{rdevice()};
	uniform_int_distribution< unsigned int> randomNum{0,1};
	
	
	return randomNum(num);
	
}

// void setInPoints(CoinTossingGame& p[num], int num, int points){
//	 for(int count {0}; count < num; count++)
//		 p[count].setPoints(points);
// }
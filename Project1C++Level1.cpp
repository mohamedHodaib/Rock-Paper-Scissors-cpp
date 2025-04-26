
#include <iostream>
using namespace std;
enum enGameChoice { stone = 1, paper = 2, scissors = 3 };
enum enWinner { Player = 1, Computer = 2, NoWinner = 3 };
struct stRoundInfo {
    short RoundNumber;
        enGameChoice PlayerChoice;
        enGameChoice ComputerChoice;
        enWinner RoundWinner;
        string WinnerName;
};
struct stGameResults {
    short NumberOfRounds;
    short PlayerWonTimes;
    short ComputerWonTimes;
    short DrawTimes;
    enWinner GameWinner;
    string WinnerName;
};
void ResetGame() {
    system("cls");
    system("color 0F");
}
short HowManyRounds() {
    short HowManyRounds;
    do {
        cout <<"How many rounds from 1 to 10?";
        cin >> HowManyRounds;
    } while (HowManyRounds < 1|| HowManyRounds > 10);
    return HowManyRounds;
}
enGameChoice ReadPlayerChoice() {
    short PlayerChoice;
    do {
        cout << "Your Choice: [1]:stone,[2]:paper,[3]:scissors?";
        cin >> PlayerChoice;
    } while (PlayerChoice < 1 || PlayerChoice > 3);
    return enGameChoice(PlayerChoice);
}
short GenerateRandomNumber(short From, short To) {
    short random = rand() % (To - From + 1) + From;
    return random;
}
enGameChoice GetComputerChoice() {
    return enGameChoice(GenerateRandomNumber(1, 3));
}
void SetWinnerScreenColor(enWinner Winner) {
    switch (Winner) {
    case Player:
        system("color 2F");
        break;
    case Computer:
        system("color 4F");
        cout << "\a";
        break;
    default:
        system("color 6F");
    }
}
enWinner WhoWonTheRound(stRoundInfo RoundInfo) {
    if (RoundInfo.PlayerChoice == RoundInfo.ComputerChoice)return NoWinner;
    switch (RoundInfo.PlayerChoice) {
    case stone:
        if (RoundInfo.ComputerChoice == paper)return Computer;
        break;
    case paper:
        if (RoundInfo.ComputerChoice == scissors)return Computer;
        break;
    case scissors:
        if (RoundInfo.ComputerChoice == stone)return Computer;
        break;
    }
    return Player;
}
string WinnerName(enWinner Winner) {
    string arrWinner[3] = {"Player","Computer","No Winner"};
    return arrWinner[Winner - 1];
}
string ChoiceName(enGameChoice Choice) {
    string arrChoice[3] = { "stone","paper","scissors" };
    return arrChoice[Choice - 1];
}
void PrintRoundResults(stRoundInfo RoundInfo) {
    cout << "\n__________________________Round[" << RoundInfo.RoundNumber << "]__________________________\n\n";
    cout << "Player Choice:" <<ChoiceName(RoundInfo.PlayerChoice)<<endl;
    cout << "Computer Choice: " <<ChoiceName(RoundInfo.ComputerChoice)<<endl;
    cout << "Round winner: " <<RoundInfo.WinnerName<< endl;
    cout << "____________________________________________________________________________________________\n\n";
    SetWinnerScreenColor(RoundInfo.RoundWinner);
}
enWinner WhoWonTheGame(stGameResults GameResults) {
    if (GameResults.PlayerWonTimes > GameResults.ComputerWonTimes)return Player;
    else if (GameResults.PlayerWonTimes < GameResults.ComputerWonTimes)return Computer;
    else return NoWinner;
}
stGameResults fillGameResults(short PlayerWons, short ComputerWons, short Draw, short Rounds) {
    stGameResults GameResults;
    GameResults.PlayerWonTimes = PlayerWons;
    GameResults.ComputerWonTimes = ComputerWons;
    GameResults.NumberOfRounds = Rounds;
    GameResults.DrawTimes = Draw;
    GameResults.GameWinner = WhoWonTheGame(GameResults);
    GameResults.WinnerName = WinnerName(GameResults.GameWinner);
    return GameResults;
}
stGameResults Playgame(short HowManyRounds) {
    stRoundInfo RoundInfo;
    short PlayerWonTimes = 0, ComputerWonTimes=0, DrawTimes=0;
    for (short GameRound = 1;GameRound <= HowManyRounds;GameRound++) {
        RoundInfo.RoundNumber = GameRound;
        RoundInfo.PlayerChoice = ReadPlayerChoice();
        RoundInfo.ComputerChoice = GetComputerChoice();
        RoundInfo.RoundWinner = WhoWonTheRound(RoundInfo);
        RoundInfo.WinnerName = WinnerName(RoundInfo.RoundWinner);
        if (RoundInfo.RoundWinner == Player)PlayerWonTimes++;
        else if (RoundInfo.RoundWinner == Computer)ComputerWonTimes++;
        else DrawTimes++;
        PrintRoundResults(RoundInfo);
    }
    return fillGameResults(PlayerWonTimes, ComputerWonTimes, DrawTimes, HowManyRounds);
}
string Tabs(short NumOftabs) {
    string Tabs = "";
    for (short i = 0;i < NumOftabs;i++)Tabs += "\t";
    return Tabs;
}
void ShowGameOverScreen() {
    cout<<Tabs(3)<< "_____________________________________________________________________________\n\n" ;
    cout<<Tabs(3)<< "                           +++GAME OVER+++\n\n" ;
    cout<<Tabs(3)<< "______________________________________________________________________________\n\n";
}
void ShowFinalGameResults(stGameResults GameResults) {
    cout << Tabs(3) << "___________________________Game Results________________________________________\n\n";
    cout <<Tabs(3)<< "Game Rounds: " << GameResults.NumberOfRounds << endl;
    cout <<Tabs(3)<< "Player Wons: " << GameResults.PlayerWonTimes<<endl;
    cout <<Tabs(3)<< "Computer Wons: " << GameResults.ComputerWonTimes << endl;
    cout <<Tabs(3)<< "Draw Times: " << GameResults.DrawTimes << endl;
    cout <<Tabs(3)<< "Final Winner: " << GameResults.WinnerName << endl;
    cout << Tabs(3) << "_______________________________________________________________________________\n\n";
    SetWinnerScreenColor(GameResults.GameWinner);

}
void StartGame() {
    char PlayAgain;
    do {
        ResetGame();
        stGameResults GameResults = Playgame(HowManyRounds());
        ShowGameOverScreen();
        ShowFinalGameResults(GameResults);
        cout <<Tabs(3)<< "Do you want to play again?Y/N?";
        cin >> PlayAgain;
    } while (PlayAgain == 'y' || PlayAgain == 'Y');
}
int main()
{
    srand((unsigned)time(NULL));
    StartGame();
}





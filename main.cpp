#include<iostream>
// #include<cstdlib.h>
#include<fstream>
#include<string>
#include<unistd.h>
#include<sstream>

#if (defined(__APPLE__) || defined(__OSX__) || defined(__MACOS__)) && defined(__MACH__)//To ensure that we are running on a mondern version of macOS
  #define OS_MAC

  #define COLOR_RED "\033[31m"
  #define COLOR_GREEN "\033[32m" 
  #define COLOR_BLUE "\033[34m"
  #define COLOR_RESET "\033[0m"

#endif

using namespace std;

const int gridSize = 25;
void printGrid(bool gridOne[gridSize + 1][gridSize + 1]);
void determineState(bool gridOne[gridSize + 1][gridSize + 1]);
void clearScreen(void);

int main(){
    cout << COLOR_GREEN;
    clearScreen();
    bool gridOne[gridSize + 1][gridSize + 1] = {};
    int x, y, n;
    string nc;
    string start;
    string filename;
    cout << "                         THE GAME OF life - Implementation in C++" << endl;
    cout << endl;
    cout << "Enter the number of cells, or 'r' to read cells from files";
    cin >> nc;
    cout << endl;

    if(nc=="r"){
        while(true){
            cout << "Enter the name of the file read from" << endl;
            cin >> filename;

            ifstream readfile(filename);
            if(readfile.is_open()){
                string fileline, xx, yy;

                while(getline(readfile,fileline)){
                    stringstream ss(fileline);

                    getline(ss, xx, ' ');
                    getline(ss, yy, ' ');

                    x = stoi(xx);
                    y = stoi(yy);

                    gridOne[x][y] = true;
                }
                break;
            }else{
                cout << "No Such file" << endl;
            }
        }
    }else{
        for (int i = 0; i < stoi(nc);i++){
            cout << stoi(nc) << "Enter the coordinates  " << i + 1 << " ; ";
            cin >> x >> y;
            gridOne[x][y] = true;
            printGrid(gridOne);
        }
    }

    cout << "Start the game ? (y/n)" << endl;
    printGrid(gridOne);
    cin >> start;
    if(start=="y"||start=="Y"){
        while(true){
            printGrid(gridOne);
            determineState(gridOne);
            usleep(200000);
            clearScreen();
        }
    }else{
        cout << COLOR_RESET;
        clearScreen();
        return 0;
    }
}


void clearScreen(void){
    cout << "\033[2J;" << "\033[1;1H";
}

void printGrid(bool gridOne[gridSize+1][gridSize+1]){
    for (int a = 1; a < gridSize;a++){
        for (int b = 1; b < gridSize;b++){
            if(gridOne[a][b]==true){
                cout << " 0 ";
            }else{
                cout << " . ";
            }

            if(b==gridSize-1){
                cout << endl;
            }
        }
    }
}

void compareGrid(bool gridOne[gridSize+1][gridSize+1], bool gridTwo[gridSize+1][gridSize+1]){
    for (int a = 0; a < gridSize;a++){
        for (int b = 0; b < gridSize;b++){
            gridTwo[a][b] = gridOne[a][b];
        }
    }
}

void determineState(bool gridOne[gridSize+1][gridSize+1]){

    bool gridTwo[gridSize + 1][gridSize + 1] = {};
    compareGrid(gridOne, gridTwo);

    for (int a = 1; a < gridSize;a++){
        for (int b = 1; b < gridSize;b++){
            int alive = 0;
            for (int c = -1; c < 2;c++){
                for (int d = -1; d < 2;d++){
                    if(!(c==0 && d==0)){
                        if(gridTwo[a+c][b+d]){
                            ++alive;
                        }
                    }
                }
            }
            if(alive<2){
                gridOne[a][b] = false;
            }else if(alive==3){
                gridOne[a][b] = true;
            }else if(alive>3){
                gridOne[a][b] = false;
            }
        }
    }
}
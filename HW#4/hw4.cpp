#include <iostream>
#include <fstream>
#include <string>
#include <ctime>

using namespace std;

/************************************
  Note that in general using global
  variables is a bad habit.
  I use globals here because I don't 
  want to scare you with "double***"
*************************************/

int m;
int n;
double **v;  // n*(m+1) 2D-array
double **h;  // (n+1)*m 2D-array

// For internal use only. Do not really use them directly
double *real_v;
double *real_h;

void shortest_path(int, int, double, double &,string, string &);
void readParameters()
{
    ifstream ifs("input1", ifstream::binary);

    ifs.read((char*)&m, sizeof(int));
    ifs.read((char*)&n, sizeof(int));

    real_v = new double[n*(m+1)];
    real_h = new double[(n+1)*m];

    ifs.read((char*)real_v, sizeof(double)*n*(m+1));
    ifs.read((char*)real_h, sizeof(double)*(n+1)*m);

    v = new double*[n];
    for (int i=0; i<n; ++i)
        v[i] = &(real_v[i*(m+1)]);

    h = new double*[n+1];
    for (int i=0; i<n+1; ++i)
        h[i] = &(real_h[i*m]);

    ifs.close();
}

void release()
{

    delete []v;
    delete []h;

    delete []real_v;
    delete []real_h;
}

int main()
{
    readParameters();
    /*for(int i = 0; i < n; i++)
    {
        for(int j = 0; j < m + 1; j++)
            cout << v[i][j] << " ";
        cout << endl;
    }
    for(int i = 0; i < n + 1; i++)
    {
        for(int j = 0; j < m; j++)
            cout << h[i][j] << " ";
        cout << endl;
    }*/
    string movement;
    string MAX_MOVEMENT;
    int x = 0, y = 0;
    double total = 0;
    double MAX_TOTAL = 99999;
    shortest_path(x, y, total, MAX_TOTAL, movement, MAX_MOVEMENT);
    cout << MAX_TOTAL << endl;
    cout << MAX_MOVEMENT << endl;

    release();
    return 0;
}
void shortest_path(int x, int y, double total, double& MAX_TOTAL , string str, string& MAX_MOVEMENT)
{
    if(x == m && y == n)
    {
        if(total < MAX_TOTAL)
        {
            cout << total << endl;
            MAX_MOVEMENT = str;
            MAX_TOTAL = total;
        }
        return;
    }
    if(x == m)
    {
        str += "v";
        shortest_path(x, y + 1, total + v[ y ][ x ], MAX_TOTAL, str, MAX_MOVEMENT);
    }
    else if(y == n)
    {
        str += "h";
        shortest_path(x + 1, y, total + h[ y ][ x ], MAX_TOTAL, str, MAX_MOVEMENT);
    }
    else
    { 
        str += "v";
        shortest_path(x, y + 1, total + v[ y ][ x ], MAX_TOTAL, str, MAX_MOVEMENT);
        str.pop_back();

        str += "h";
        shortest_path(x + 1, y, total + h[ y ][ x ], MAX_TOTAL, str, MAX_MOVEMENT);
        str.pop_back();
    }
}

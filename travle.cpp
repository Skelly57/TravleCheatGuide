#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <cmath>

using namespace std;

vector<vector<string>> import(vector<string> &countries);
void initialize(vector<vector<int>> &dist, vector<vector<int>> &prev, vector<string> countries, vector<vector<string>> countries_graph);
void floyd_warshall(vector<vector<int>> &dist, vector<vector<int>> &prev);
void shortest_path(string start_country, string end_country, vector<vector<int>> prev, vector<string> countries);
int sp_recursion(int i, int j, vector<vector<int>> prev, vector<string> countries);
void country_lookup(char letter, vector<string> countries);

int main()
{
    vector<string> countries;
    vector<vector<string>> countries_graph;
    vector<vector<int>> dist;
    vector<vector<int>> prev;
    countries_graph = import(countries);
    initialize(dist, prev, countries, countries_graph);
    floyd_warshall(dist, prev);
    int x, loop = 1;
    string start_country, end_country;
    char letter;
    cout << "Welcome to the Travle Cheat Guide! Here you can find the shortest distance between two countries for all your travle.earth needs!\n"
         << "To continue, enter one of the numbers below, depending on what you need :D"
         << "Also, for the country lookup, enter your letter as a capital please :)" << endl;
    while (loop == 1)
    {
        cout << "1. Find the Shortest Path between 2 Countries\n"
             << "2. Search for a country\n"
             << "3. Exit the program" << endl;
        cin >> x;
        switch (x)
        {
            case 1:
                cout << "Enter the Start Country:" << endl;
                getline(cin, start_country);
                getline(cin, start_country); // it just works
                cout << "Enter the End Country:" << endl;
                getline(cin, end_country);
                shortest_path(start_country, end_country, prev, countries);
                break;
            case 2:
                cout << "Enter the starting letter of the country you wish to find: ";
                cin >> letter;
                country_lookup(letter, countries);
                break;
            default:
                cout << "Thank you for using the Travle Cheat Guide, have an above average day :)" << endl;
                loop = 0;
                break;
        }
    }
    return 0;
}

vector<vector<string>> import(vector<string> & countries)
{
    string path = "country_borders.txt";
    vector<vector<string>> countries_graph;
    fstream countries_file;
    countries_file.open(path, ios::in);

    if (!countries_file.is_open())
    {
        cout << "Could not find/open input file!" << endl;
    }
    else
    {
        string line;
        while (getline(countries_file, line))
        {
            stringstream ss(line);
            string token;
            vector<string> tokens;
            vector<string> temp_vec;
            char delimiter = ',';
            while (getline(ss, token, delimiter))
            {
                tokens.push_back(token);
            }
            countries.push_back(tokens[0]);
            int len = tokens.size();
            for (int i = 0; i < len; i++)
            {
                string entry = tokens[i];
                temp_vec.push_back(tokens[i]);
            }
            countries_graph.push_back(temp_vec);
        }
    }
    return countries_graph;
}

void initialize(vector<vector<int>> & dist, vector<vector<int>> & prev, vector<string> countries, vector<vector<string>> countries_graph)
{
    vector<int> temp_dist_vec, temp_prev_vec;
    for (int i = 0; i < 197; i++)
    {
        temp_dist_vec.push_back(999999);
        temp_prev_vec.push_back(-1);
    }
    for (int i = 0; i < 197; i++)
    {
        dist.push_back(temp_dist_vec);
        prev.push_back(temp_prev_vec);
    }
    for (int i = 0; i < dist.size(); i++)
    {
        vector<int> country_nums;
        for (int j = 1; j < countries_graph[i].size(); j++)
        {
            string country = countries_graph[i][j];
            int x = 0;
            while (countries[x] != country)
            {
                x++;
            }
            dist[i][x] = 1;
            prev[i][x] = i;
        }
    }
}

void floyd_warshall(vector<vector<int>> &dist, vector<vector<int>> &prev)
{
    int n = dist.size();
    for (int k = 0; k < n; ++k)
    {
        for (int i = 0; i < n; ++i)
        {
            for (int j = 0; j < n; ++j)
            {
                if (dist[i][k] + dist[k][j] < dist[i][j])
                {
                    dist[i][j] = dist[i][k] + dist[k][j];
                    prev[i][j] = prev[k][j];
                }
            }
        }
    }
}

void shortest_path(string end_country, string start_country, vector<vector<int>> prev, vector<string> countries)
{
    int i = 0, j = 0;
    while (countries[i] != start_country)
    {
        i++;
    }
    while (countries[j] != end_country)
    {
        j++;
    }
    if (prev[i][j] == -1)
    {
        cout << "There is no path from " << end_country << " -> " << start_country << endl;
    }
    else
    {
        cout << "Shortest Path from " << end_country << " -> " << start_country << ":" << endl;
        cout << end_country << " -> ";
        sp_recursion(i, j, prev, countries);
    }
    
}

int sp_recursion(int i, int j, vector<vector<int>> prev, vector<string> countries)
{
    if (prev[i][j] == i)
    {
        cout << countries[prev[i][j]] << endl;
        return 0;
    }
    else
    {
        cout << countries[prev[i][j]] << " -> ";
        sp_recursion(i, prev[i][j], prev, countries);
    }
}

void country_lookup(char letter, vector<string> countries)
{
    vector<int> c;
    cout << "Countries starting with " << letter << endl;
    for (int i = 0; i < 196; i++)
    {
        if (countries[i][0] == letter)
        {
            c.push_back(i);
        }
    }
    if (countries[196][0] == letter)
    {
        c.push_back(196);
    }
    for (int j = 0; j < c.size()-1; j++)
    {
        cout << countries[c[j]] << ", ";
    }
    cout << countries[c[c.size()-1]] << endl;
}
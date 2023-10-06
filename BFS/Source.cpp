#include <iostream>
#include <vector>
#include <fstream>
#include <stack>
using namespace std;

#define inputFile "input.inp"
#define outputFile "output.out"

const int MAX = 1000;
int rows, cols;

vector<string> forest;
pair<int, int> start, finish; // similar to python's tuple
vector<pair<int, int>> steps;
vector<vector<int>> trace; // mang y nghia danh dau

void input()
{
	ifstream f;
	f.open(inputFile);

	f >> rows >> cols;

	string x;
	for (int r = 0; r < rows; ++r)
	{
		f >> x;
		forest.push_back(x);
	}
	f.close();
}

void Init()
{
	for (int r = 0; r < rows; ++r)
	{
		int c = forest[r].find('E');

		//
		if (c != string::npos) //npos = end position cant find E then c is at npos
		{
			start.first = r;
			start.second = c;
			break;
		}
	}

	steps.push_back({ -1, 0 }); // up
	steps.push_back({ 1, 0 }); // down
	steps.push_back({ 0, -1 }); // left
	steps.push_back({ 0, 1 }); //right

	trace.resize(rows);
	for (int r = 0; r < rows; ++r)
	{
		trace[r].resize(cols, -1); //resize and asign value (-1)
	}
}

void Process(pair<int, int> current)
{
	if (current.first == 0 || current.first == rows - 1 || current.second == 0 || current.second == cols - 1)//if current equal top row or bottom row
	{
		finish.first = current.first;
		finish.second = current.second;

		return;
	}
	pair<int, int> next;

	for (int s = 0; s < steps.size(); ++s)
	{
		next.first = current.first + steps[s].first;
		next.second = current.second + steps[s].second;

		if (next.first >= 0 && next.first < rows &&     //condition sentences have the same type go together
			next.second >= 0 && next.second < cols)
			if (forest[next.first][next.second] == 'O')
				if (trace[next.first][next.second] == -1)
				{
					trace[next.first][next.second] = (MAX + current.second) * MAX + current.first;

					current.first = next.first;
					current.second = next.second;

					Process(current);
				}
	}
}

void Output()
{
	stack<pair<int, int>> path;

	path.push(finish);

	while (trace[finish.first][finish.second] != -1)
	{
		int r = trace[finish.first][finish.second] % MAX;
		int c = trace[finish.first][finish.second] / MAX - MAX;
		
		path.push({r, c});

		finish.first = r;
		finish.second = c;
	}

	ofstream f;
	f.open(outputFile);

	while (!path.empty())
	{
		f << path.top().first << " " << path.top().second;
		
		if (path.size() != 1)
		{
			f << endl;
		}

		path.pop();
	}

	f.close();
}

int main()
{
	input();
	Init();
	Process(start);
	Output();
	
	return 0;
}

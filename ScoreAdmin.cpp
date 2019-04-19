#include "DXUT.h"
#include "ScoreAdmin.h"

#include <fstream>

ScoreAdmin::ScoreAdmin()
{
}


ScoreAdmin::~ScoreAdmin()
{
}

list<int> ScoreAdmin::GetList()
{
	return listScore;
}

void ScoreAdmin::Insert(int newScore)
{
	listScore.push_back(newScore);
}

void ScoreAdmin::FileInput(RsKey path)
{
	ifstream file;
	file.open(path, ios::in | ios::binary);

	int temp;

	while (!file.eof())
	{
		file >> temp;
		listScore.push_back(temp);
	}

	file.close();
}

void ScoreAdmin::FileOutput(RsKey path, int count)
{
	ofstream file;
	file.open(path, ios::trunc);

	for (auto iter : listScore)
	{
		file << iter << endl;

		if (count-- <= 1)
		{
			file.close();
			return;
		}
	}

	file.close();
}

void ScoreAdmin::sort()
{
	listScore.sort(sorting);
}

bool ScoreAdmin::sorting(int i, int j)
{
	return i > j;
}

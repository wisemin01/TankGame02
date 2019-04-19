#pragma once

class ScoreAdmin
{
public:
	list<int> listScore;
public:
	ScoreAdmin();
	virtual ~ScoreAdmin();

	list<int> GetList();
	void Insert(int newScore);
	void FileInput(RsKey path);
	void FileOutput(RsKey path, int count = 3);

	void sort();

public:
	static bool sorting(int i, int j);
};


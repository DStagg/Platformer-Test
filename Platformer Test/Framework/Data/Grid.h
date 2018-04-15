#ifndef GRID_H
#define GRID_H

#include <vector>

template <class T>
class Grid
{
public:

	Grid(int w = 1, int h = 1, T default_value = T())
	{
		Create(w, h, default_value);
	}
	~Grid()
	{

	};

	void Create(int w, int h, T default_value)
	{
		Resize(w, h);

		for (int x = 0; x < GetWidth(); x++)
			for (int y = 0; y < GetHeight(); y++)
				SetCell(x, y, default_value);
	};

	T GetCell(int x, int y)
	{
		if (x < 0) x = 0;
		if (x >= GetWidth()) x = GetWidth() - 1;
		if (y < 0) y = 0;
		if (y >= GetHeight()) y = GetHeight() - 1;

		return _Cells[x][y];
	};

	void SetCell(int x, int y, T value)
	{
		if (x < 0) x = 0;
		if (x >= GetWidth()) x = GetWidth() - 1;
		if (y < 0) y = 0;
		if (y >= GetHeight()) y = GetHeight() - 1;

		_Cells[x][y] = value;
	};

	int GetWidth()
	{
		return (int)_Cells.size();
	};

	int GetHeight()
	{
		if (GetWidth() == 0) return 0;
		return (int)_Cells[0].size();
	};

	void Resize(int w, int h)
	{
		if (w < 1) w = 1;
		if (h < 1) h = 1;

		//	Add/Remove Columns to new Width
		if (GetWidth() < w)
		{
			std::vector<T> newCol;
			for (int y = 0; y < h; y++)
				newCol.push_back(T());
			while (GetWidth() < w)
				_Cells.push_back(newCol);
		}
		else
		{
			while (GetWidth() > w)
				_Cells.pop_back();
		}

		//	Resize Existing Columns to new Height
		while (GetHeight() > h)
		{
			for (int x = 0; x < GetWidth(); x++)
				_Cells[x].pop_back();
		}
		while (GetHeight() < h)
		{
			for (int x = 0; x < GetWidth(); x++)
				_Cells[x].push_back(T());
		}

	};

private:

	std::vector<std::vector<T>> _Cells;
	
};

#endif

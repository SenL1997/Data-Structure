template <class T>
class matrixEntry
{
	friend int getKey(const matrixEntry<T> &entry)
	{
		return entry.row * 100 + entry.colum;
	}
	friend bool operator==(const matrixEntry &a, const matrixEntry &b)
	{
		if (a.row == b.row&&a.column == b.column)
			return true;
		else
			return false;
	}

public:
	matrixEntry(int r, int c, T value) :row(r), column(c), data(value) {};
	matrixEntry(){}

private:
	int row, column;
	T data;
};

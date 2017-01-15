#ifndef PRIORITYQUEUE_H_INCLUDED
#define PRIORITYQUEUE_H_INCLUDED

template <typename Type>
class priorityQueue
{
public:
	priorityQueue(int capacity = 100)
	{
		array = new Type[capacity];
		maxSize = capacity;
		currentSize = 0;
	}
	priorityQueue(const Type data[], int size);
	~priorityQueue() { delete[] array; }

	bool isEmpty()const { return currentSize == 0; }
	void enQueue(const Type &x);
	Type deQueue();
	Type getHead()const { return array[1]; }

	int findMin(Type x)						//找出大于或等于x的最小元素
	{
		Type min;
		int ID = -1;

		for (int i = 1;i <= currentSize;++i)
		{
			if (array[i] >= x && (ID == -1 || array[i]<min))
			{
				min = array[i];
				ID = i;
			}
		}

		return ID;
	}

	void decreaseKey(int i, Type value)				//将堆中第i个结点的值减小value
	{
		Type x;
		int hole;

		array[hole = i] -= value;					//将第i个元素减少value
		for (x = array[i];hole>1 && x<array[hole / 2];hole /= 2)	//过滤
			array[hole] = array[hole / 2];
		array[hole] = x;
	}

private:
	int currentSize;				//队列长度
	Type * array;
	int maxSize;

	void doubleSpace();
	void buildHeap();
	void percolateDown(int hole);
};

template <typename Type>
void priorityQueue<Type>::enQueue(const Type &x)
{
	if (currentSize == maxSize - 1)
		doubleSpace();
	//向上过滤
	int hole = ++currentSize;
	for (;hole>1 && x<array[hole / 2];hole /= 2)
		array[hole] = array[hole / 2];
	array[hole] = x;
}

template <typename Type>
Type priorityQueue<Type>::deQueue()
{
	Type minItem;
	minItem = array[1];
	array[1] = array[currentSize--];
	percolateDown(1);
	return minItem;
}

template <typename Type>
void priorityQueue<Type>::percolateDown(int hole)
{
	int child;
	Type tmp = array[hole];

	for (;hole * 2 <= currentSize;hole = child)
	{
		child = hole * 2;
		if (child != currentSize && array[child + 1]<array[child])
			child++;
		if (array[child] < tmp)
			array[hole] = array[child];
		else
			break;
	}
	array[hole] = tmp;
}

template <typename Type>
void priorityQueue<Type>::buildHeap()
{
	for (int i = currentSize / 2;i>0;i--)
		percolateDown(i);
}

template <typename Type>
priorityQueue<Type>::priorityQueue(const Type *items, int size) :maxSize(size + 10), currentSize(size)
{
	array = new Type[maxSize];
	for (int i = 0;i<size;i++)
		array[i + 1] = items[i];
	buildHeap();
}

template <typename Type>
void priorityQueue<Type>::doubleSpace()
{
	Type *tmp = array;
	maxSize *= 2;
	array = new Type[maxSize];

	for (int i = 0;i <= currentSize;++i)
		array[i] = tmp[i];

	delete[]tmp;
}

#endif // PRIORITYQUEUE_H_INCLUDED

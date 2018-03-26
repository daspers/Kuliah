
template <class T>
class Stack{
public:
	Stack(int sz = 10)
	{
		size = sz;
		data = new T[size];
		topIndex = -1;
	}
	Stack(const Stack<T>& t);
	Stack<T>& operator =(const Stack<T>& t);
	~Stack();
	bool isFull() const;
	bool isEmpty() const;
	int getSize() const;
	void push(T x);
	T pop();
private:
	T *data;
	int size;
	int topIndex;
};

template <class T>
Stack<T>::Stack(const Stack<T>& t)
{
	size = t.size;
	topIndex = t.topIndex;
	data = new T[size];
	for(int i = 0;i<=topIndex;i++){
		data[i] = t.data[i];
	}
}
template <class T>
Stack<T>& Stack<T>::operator =(const Stack<T>& t)
{
	delete[] data;
	size = t.size;
	topIndex = t.topIndex;
	data = new T[size];
	for(int i = 0;i<=topIndex;i++){
		data[i] = t.data[i];
	}
}
template <class T>
Stack<T>::~Stack()
{
	delete[] data;
}
template <class T>
bool Stack<T>::isFull() const
{
	return topIndex+1 == size;
}
template <class T>
bool Stack<T>::isEmpty() const
{
	return topIndex ==-1;
}
template <class T>
int Stack<T>::getSize() const
{
	return size;
}
template <class T>
void Stack<T>::push(T x)
{
	if(!isFull()){
		topIndex++;
		data[topIndex] = x;
	}
}
template <class T>
T Stack<T>::pop()
{
	return data[topIndex--];
}

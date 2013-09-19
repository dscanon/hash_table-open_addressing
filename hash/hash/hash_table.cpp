#include<iostream>
using namespace std;

template<class T>
class Hash
{
	T *data;
	bool *deleted;
	int size;
public :
	Hash();
	~Hash();
	void print();
	void insert(T value);
	int hf(T value);
	int search(T value);
	bool isFull();
	void rehash();
	void deletehash(T value);
};
bool isPrime(int number)
{
	for(int i = 2 ;i<number; i++)
	{
		if(number%i==0)
		{
			return false;
		}
	}
	return true;
}
template<class T>
Hash<T> :: Hash()
{
	size = 4;
	data = new T[size];
	for(int i = 0 ; i<size ; i++)
	{
		data[i] = -1;
	}
	deleted = new bool[size];
	for(int i=0;i<size;i++)
	{
		deleted[i] = false;
	}
}

template<class T>
Hash<T> :: ~Hash()
{
	delete[] data;
}

template<class T>
int Hash<T> :: hf(T value)
{
	return value%size;
}

template<class T>
int Hash<T> :: search(T value)
{
	int index = hf(value);
	if(data[index]==value)
	{
		return index;
	}
	else
	{
		while(deleted[index] || data[index] != -1)
		{
			index++;
			if(data[index]==value)
			{
				return index;
			}
		}
	}
	cout << "Cann't found " << value << endl;
	return 0;
}

template<class T>
void Hash<T> :: insert(T value)
{
	cout << "======  Insert  ----->   " << value <<endl;
	int index = hf(value);
	if(!isFull())
	{
		if(data[index] == -1)
		{
			data[index] = value;
		}
		else
		{
			cout << "========  Collision " << value << endl;
			while(data[index] != -1)
			{
				index++;
				if(index==size)
				{
					index = 0;
				}
			}
			data[index] = value;
		}
		print();
	}
	else
	{
		rehash();
		insert(value);
	}
	
}

template<class T>
void Hash<T> :: print()
{
	for(int i=0;i<size;i++)
	{
		cout << i << " ";
		if(data[i] != -1)
		{
			cout << data[i] << " ";
		}
		cout << endl;
	}
}

template<class T>
bool Hash<T> :: isFull()
{
	for(int i=0; i<size; i++)
	{
		if(data[i]==-1)
		{
			return false;
		}
	}
	return true;
}

template<class T>
void Hash<T> :: rehash()
{
	cout << "----------Rehash-----------"<<endl;
	int oldsize = size;
	size = size*2;
	while(!isPrime(size))
	{
		size++;
	}
	
	T *temp2 = new T[size];
	for(int i=0;i<size;i++)
	{
		temp2[i] = -1;
	}
	for(int i=0;i<oldsize;i++)
	{
		int index;
		if(data[i]!= -1)
		{
			if(temp2[i]==-1)
			{
				index = hf(data[i]);
				temp2[index] = data[i];
			}
			else
			{
				while(temp2[index] != -1)
				{
					index++;
					if(index==size)
					{
						index = 0;
					}
				}
				temp2[index] = data[i];
			}
		}
	}
	delete[] data;
	data = temp2;
}

template<class T>
void Hash<T> :: deletehash(T value)
{
	int index = hf(value);
		if(data[index] == value)
		{
			data[index] = -1;
			deleted[index] = true;
		}
}

int main()
{
	const int size = 13;
	int a[size] = {706,707,711,753,776,877,895,904,906,911};
	Hash<int> t1;
	t1.insert(706);
	t1.insert(707);
	t1.insert(711);
	t1.insert(753);
	t1.insert(776);
	t1.insert(877);
	t1.insert(895);
	t1.insert(904);
	t1.insert(906);
	t1.insert(911);
	cout << "=================" << endl;
	cout << "delete " << " 877  " << endl;
	t1.deletehash(877);
	t1.print();
	int search = 904;
	cout << "search data " << search << endl;
	cout << "Index at ... " << t1.search(search) << endl;
	return 0;
}
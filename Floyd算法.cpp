#include <iostream>
#include <cstdlib>
using namespace std;
#define N 6

class Floyd
{
public:
	Floyd(int *arr)
	{
		for (int i = 0; i <	N * N; i++)
		{
			this->arr[i / N][i % N] = arr[i];
		}
	}

	void min_dist_by_Floyd()
	{
		for (int i = 0; i < N; i++)
		{
			for (int j = 0; j < N; j++)
			{
				for (int k = 0; k < N; k++)
				{
					//jk是起始和目标节点的距离
					if (arr[j][k] > arr[j][i] + arr[i][k])
					{
						arr[j][k] = arr[j][i] + arr[i][k];
					}
				}
			}
		}
	}

	int arr[N][N] = {0};
};

void output(int arr[N][N])
{
	cout << "[";
	for (int i = 0; i < N; i++)
	{
		cout << "[";
		for (int j = 0; j < N; j++)
		{
			cout << arr[i][j] << " ";
		}
		if(i==N-1) cout << "]";
		else cout << "]\n";
	}
	cout << "]\n";
}

int main()
{
	int* arr = (int*)malloc(sizeof(int) * N * N);
	if (arr == NULL)
	{
		return 0;
	}
	for (int i = 0; i < N * N; i++)
	{
		cin >> arr[i];
	}
	Floyd F(arr);
	free(arr);
	output(F.arr);
	F.min_dist_by_Floyd();
	output(F.arr);
	return 0;
}
#include <cstdio>
#include <string>
#include <iostream>
#define MAX_ROW_COUNT 100
#define MAX_COL_COUNT 100

using namespace std;

int kadane(int* arr, int* start, int* finish, int n)
{
	// initialize sum, maxSum and
	int sum = 0, maxSum = INT_MIN, i;

	// Just some initial value to check for all negative values case
	*finish = -1;

	// local variable
	int local_start = 0;

	for (i = 0; i < n; ++i)
	{
		sum += arr[i];
		if (sum < 0)
		{
			sum = 0;
			local_start = i + 1;
		}
		else if (sum > maxSum)
		{
			maxSum = sum;
			*start = local_start;
			*finish = i;
		}
	}

	// There is at-least one non-negative number
	if (*finish != -1)
		return maxSum;

	// Special Case: When all numbers in arr[] are negative
	maxSum = arr[0];
	*start = *finish = 0;

	// Find the maximum element in array
	for (i = 1; i < n; i++)
	{
		if (arr[i] > maxSum)
		{
			maxSum = arr[i];
			*start = *finish = i;
		}
	}
	return maxSum;
}

// The main function that finds maximum sum rectangle in M[][]
void findMaxSum(int** mat, int row_count, int col_count)
{
	// Variables to store the final output
	int maxSum = INT_MIN, finalLeft = 0, finalRight = col_count, finalTop = 0, finalBottom = row_count;

	int left, right, i;
	int sum, start, finish;
	int* temp = new int[MAX_ROW_COUNT];

	// Set the left column
	for (left = 0; left < col_count; ++left)
	{
		// Initialize all elements of temp as 0
		memset(temp, 0, MAX_ROW_COUNT*sizeof(int));

		// Set the right column for the left column set by outer loop
		for (right = left; right < col_count; ++right)
		{
			// Calculate sum between current left and right for every row 'i'
			for (i = 0; i < row_count; ++i)
				temp[i] += mat[i][right];

			// Find the maximum sum subarray in temp[]. The kadane() function
			// also sets values of start and finish.  So 'sum' is sum of
			// rectangle between (start, left) and (finish, right) which is the
			//  maximum sum with boundary columns strictly as left and right.
			sum = kadane(temp, &start, &finish, row_count);

			// Compare sum with maximum sum so far. If sum is more, then update
			// maxSum and other output values
			if (sum > maxSum)
			{
				maxSum = sum;
				finalLeft = left;
				finalRight = right;
				finalTop = start;
				finalBottom = finish;
			}
		}
	}

	delete[] temp;

	for (int row_i = finalTop; row_i <= finalBottom; ++ row_i)
	{
		for (int col_i = finalLeft; col_i <= finalRight; ++col_i)
		{
			cout << mat[row_i][col_i];
			if (col_i + 1 <= finalRight)
				cout << ",";
		}
		if (row_i + 1 <= finalBottom)
			cout << ";";
	}
}

// Driver program to test above functions
int main()
{
	string raw_input_string;
	getline(cin, raw_input_string);
	if (raw_input_string.empty())
	{
		cerr << "ERROR: input data is missing" << endl;
		return -1;
	}

	int** mat = new int*[MAX_ROW_COUNT];
	int mat_row_index = 0;
	int mat_col_index = 0;

	size_t l_off = 0, r_off = 0;
	while (l_off != string::npos)
	{
		r_off = raw_input_string.find_first_of(';', l_off);

		string raw_sub_string = raw_input_string.substr(l_off, r_off == string::npos ? string::npos : r_off - l_off);
		if (raw_sub_string.empty())
			break;

		mat_col_index = 0;
		int* mat_row = mat[mat_row_index] = new int[MAX_COL_COUNT];

		size_t l_l_off = 0, l_r_off = 0;
		while (l_l_off != string::npos)
		{
			l_r_off = raw_sub_string.find_first_of(',', l_l_off);

			string node_string = raw_sub_string.substr(l_l_off, l_r_off == string::npos ? string::npos : l_r_off - l_l_off);

			mat_row[mat_col_index] = stoi(node_string);

			l_l_off = l_r_off == string::npos ? string::npos : l_r_off + 1;
			
			mat_col_index++;
			if (mat_col_index >= MAX_COL_COUNT)
			{
				cerr << "ERROR: input count limit exceeded" << endl;
				return -1;
			}
		}
		
		l_off = r_off == string::npos ? string::npos : r_off + 1;
		mat_row_index++;
		if (mat_row_index >= MAX_ROW_COUNT)
		{
			cerr << "ERROR: input count limit exceeded" << endl;
			return -1;
		}
	}

	findMaxSum(mat, mat_row_index, mat_col_index);

	for (int i = 0; i < mat_row_index; ++i)
		delete[] mat[i];
	delete[] mat;

	return 0;
}
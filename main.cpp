#include <cstdio>
#include <iostream>
#include <string>
#include <vector>
using namespace std;

#define MAX_INPUT_COUNT 100

struct Node
{
	bool is_null;
	int key;
	Node *next;
};

// A utility function to print a linked list
void printList(Node *head)
{
	Node* node = head;
	while (true)
	{
		if (node->is_null)
			cout << "Null";
		else
			cout << node->key;
		cout << ",";
		if (node->next == NULL)
			cout << "Null";
		else
			cout << node->next - head;
		node = node->next;
		if (node == NULL)
			break;
		cout << ";";
	}
	cout << endl;
}

void detectAndRemoveLoop(Node *head)
{
	Node *slow = head;
	Node *fast = head->next;

	// Search for loop using slow and fast pointers
	while (fast && fast->next)
	{
		if (slow == fast)
			break;
		slow = slow->next;
		fast = fast->next->next;
	}

	/* If loop exists */
	if (slow == fast)
	{
		slow = head;
		while (slow != fast->next)
		{
			slow = slow->next;
			fast = fast->next;
		}

		/* since fast->next is the looping point */
		fast->next = NULL; /* remove loop */
	}
}

/* Drier program to test above function*/
int main()
{
	string raw_input_string;
	getline(cin, raw_input_string);
	if (raw_input_string.empty())
	{
		cerr << "ERROR: input data is missing" << endl;
		return -1;
	}

	Node* nodes = new Node[MAX_INPUT_COUNT];
	int nodes_index = 0;

	size_t l_off = 0, r_off = 0;
	while (l_off != string::npos)
	{
		r_off = raw_input_string.find_first_of(';', l_off);

		string node_string = raw_input_string.substr(l_off, r_off == string::npos ? string::npos : r_off - l_off);
		size_t delimiter_off = node_string.find_first_of(',');

		string key_string = node_string.substr(0, delimiter_off);
		string next_string = node_string.substr(delimiter_off + 1, string::npos);

		Node* node = nodes + nodes_index;
		try
		{
			node->key = stoi(key_string);
			node->is_null = false;
		}
		catch(...)
		{
			node->key = 0;
			node->is_null = true;
		}

		try
		{
			int next = stoi(next_string);
			node->next = nodes + next;
		}
		catch (...)
		{
			node->next = NULL;
		}

		l_off = r_off == string::npos ? string::npos : r_off + 1;
		nodes_index++;
		if (nodes_index >= MAX_INPUT_COUNT)
		{
			cerr << "ERROR: input count limit exceeded" << endl;
			return -1;
		}
	}

	detectAndRemoveLoop(nodes);
	printList(nodes);

	delete[] nodes;

	return 0;
}
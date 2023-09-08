#include <bits/stdc++.h>
#include<fstream>
using namespace std;

// CREATION OF NODE
class Node
{
public:
	int data;
	Node *left;
	Node *right;

	Node(int d)
	{
		data = d;
		left = NULL;
		right = NULL;
	}
};
// CUSTOM COMPARATOR FOR PRIORITY QUEUE
class cmp
{
public:
	bool operator()(Node *a, Node *b)
	{
		return a->data > b->data;
	}
};

class Solution
{
public:
	void traverse(Node *root, vector<pair<char, string>> &ans, string temp1, vector<pair<int, char>> &pairs, vector<bool> &visited)
	{
		// base case
		if (root->left == NULL && root->right == NULL)
		{
			char c;
			for (int i = 0; i < pairs.size(); i++)
			{
				if (pairs[i].first == root->data && !visited[i])
				{
					c = pairs[i].second;
					visited[i] = true;
					break;
				}
			}
			ans.push_back({c, temp1});
			return;
		}
		traverse(root->left, ans, temp1 + '1', pairs, visited);
		traverse(root->right, ans, temp1 + '0', pairs, visited);
	};
	vector<pair<char, string>> huffmanCodes(string S, vector<int> f, int N, vector<pair<int, char>> pairs)
	{
		// Code here
		int n = pairs.size();
		vector<bool> visited(n, false);

		// Priority Queue to store frequencies and extracting minimum each time

		priority_queue<Node *, vector<Node *>, cmp> pq;
		for (int i = 0; i < N; i++)
		{
			Node *temp = new Node(f[i]);
			pq.push(temp);
		}
		while (pq.size() > 1)
		{
			Node *left = pq.top();
			pq.pop();

			Node *right = pq.top();
			pq.pop();

			Node *newNode = new Node(left->data + right->data);
			newNode->left = left;
			newNode->right = right;
			pq.push(newNode);
		}
		Node *root = pq.top();
		vector<pair<char, string>> ans;
		string temp1 = "";
		traverse(root, ans, temp1, pairs, visited);
		return ans;
	}
};

int main()
{
	//entering the file name from where sentence is taken
	ifstream inputFile("input.txt");
	string s;
	getline(inputFile,s);

	inputFile.close();//closing that file

	cout<<s<<endl;
	//getline(cin, s);
	int N = s.length(); // length of sentence that is taken as input

	vector<int> frequencytable(256, 0);
	for (int i = 0; i < N; i++)
	{
		frequencytable[s[i]]++; // mapping characters to their frequency table
	}

	vector<int> f; // vector to store frequencies
	string chars = "";
	for (int i = 0; i < 256; i++)
	{
		if (frequencytable[i] != 0)
		{
			// extracting frequency and character from the frequencytable
			f.push_back(frequencytable[i]);
			chars += i;
		}
	}

	vector<pair<int, char>> pairs;
	// pairing characters with their frequencies
	for (int i = 0; i < chars.length(); i++)
	{
		pairs.push_back({f[i], chars[i]});
	}
	cout<<endl;
	cout << "EXTRACTED CHARACTERS AND THEIR FREQUENCIES " << endl;
	cout << endl;

	for (int i = 0; i < chars.length(); i++)
	{
		cout << "Frequency of the character " << pairs[i].second << " is " << pairs[i].first << " " << endl;
	}

	Solution ob; // creatinf an object solution
	vector<pair<char, string>> ans = ob.huffmanCodes(chars, f, chars.length(), pairs);
	cout<<endl;
	cout << "HOFFMAN CODES ARE AS FOLLOWS " << endl;
	cout << endl;
	for (auto i : ans)
	{
		cout << "Charcter is " << i.first << "->>>>"
			 << " " << i.second << endl;
	}

	cout << endl;

	// Probability of occurence
	int sumoffrequencies = accumulate(f.begin(), f.end(), 0);
	cout << sumoffrequencies << endl;
	// ENTROPY
	int ent = 0.0;
	for (int i = 0; i < f.size(); i++)
	{
		ent += f[i] * log2(f[i]);
	}
	float entropy;
	entropy = (float)ent / sumoffrequencies;
	cout << "Entropy is " << entropy << endl;

	// AVERAGE CODE WORD
	int avg = 0;
	for (int i = 0; i < ans.size(); i++)
	{
		for (int j = 0; j < pairs.size(); j++)
		{
			if (pairs[j].second == ans[i].first)
			{
				avg += ans[i].second.length() * pairs[j].first;
			}
		}
	}
	float avgCodeword;
	avgCodeword = (float)avg / sumoffrequencies;
	cout << "Average codeword is " << avgCodeword << endl;

	// EFFICIENCY
	float efficiency = entropy / avgCodeword;
	cout << "Efficiency is " << efficiency * 100 << "%" << endl;

	// VARIANCE
	float variance = 0;
	for (int i = 0; i < ans.size(); i++)
	{
		for (int j = 0; j < pairs.size(); j++)
		{
			if (pairs[j].second == ans[i].first)
			{
				variance += pow(abs(ans[i].second.length() - avgCodeword), 2) * pairs[j].first;
			}
		}
	}
	cout << "Variance is " << variance << endl;

	return 0;
}
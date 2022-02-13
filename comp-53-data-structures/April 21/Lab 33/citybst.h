#ifndef CITYBST_H
#define CITYBST_H

#include <string>
#include "citynode.h"
#include <algorithm>

using namespace std;

class CityBST {
public:
	CityNode* root;
	CityBST() {
		root = nullptr;
	}
	void insert(CityNode* cityNode) {
		CityNode* cur;
		if (root == nullptr)
		{
			root = cityNode;
			root->left = nullptr;
			root->right = nullptr;
		}
		else {
			cur = root;
			while (cur != nullptr)
			{
				if (cityNode->data.getPopulation() < cur->data.getPopulation())
				{
					if (cur->left == nullptr)
					{
						cur->left = cityNode;
						cur = nullptr;
					}
					else
					{
						cur = cur->left;
					}
				}
				else
				{
					if (cur->right == nullptr)
					{
						cur->right = cityNode;
						cur = nullptr;
					}
					else
					{
						cur = cur->right;
					}
				}
			}
			cityNode->left = nullptr;
			cityNode->right = nullptr;
		}
	}
	void remove(unsigned int pop) {
		CityNode* par = nullptr;
		CityNode* cur = root;
		CityNode* suc = root;
		City successorData;
		while (cur != nullptr) {
			if (cur->data.getPopulation() == pop)
			{
				if (!cur->left && !cur->right)
				{
					if (!par)
					{
						root = nullptr;
					}
					else if (par->left == cur)
					{
						par->left = nullptr;
					}
					else
					{
						par->right = nullptr;
					}
				}
				else if (cur->left && !cur->right)
				{
					if (!par)
					{
						root = cur->left;
					}
					else if (par->left == cur)
					{
						par->left = cur->left;
					}
					else
					{
						par->right = cur->left;
					}
				}
				else if (!cur->left && cur->right)
				{
					if (!par)
					{
						root = cur->right;
					}
					else if (par->left == cur)
					{
						par->left = cur->right;
					}
					else
					{
						par->right = cur->right;
					}
				}
				else
				{
					suc = cur->right;
					while (suc->left != nullptr)
					{
						suc = suc->left;
					}
					successorData = suc->data;
					remove(suc->data.getPopulation());
					cur->data = successorData;
				}
				return;
			}
			else if (cur->data.getPopulation() < pop)
			{
				par = cur;
				cur = cur->right;
			}
			else
			{
				par = cur;
				cur = cur->left;
			}
		}
		return;
	}
	CityNode* search(unsigned int pop) {
		return searchRecursive(root, pop);
	}
	void printCityBST() {
		printCityBSTRecursive(root, 0);
	}
	void printCityBST_InOrder() {
		printCityBST_InOrderRecursive(root);
	}
	int getHeight() {
		return getHeightRecursive(root);
	}
private:
	void printCityBSTRecursive(CityNode* cityNode, int n) {
		if (cityNode == nullptr)
		{
			return;
		}
		for (int i = 0; i < n; i++)
		{
			cout << " ";
		}
		cityNode->data.printInfo();
		printCityBSTRecursive(cityNode->left, n + 1);
		printCityBSTRecursive(cityNode->right, n + 1);
	}
	CityNode* searchRecursive(CityNode* cityNode, unsigned int pop) {
		if (cityNode != nullptr)
		{
			if (cityNode->data.getPopulation() == pop)
			{
				return cityNode;
			}
			else if (pop < cityNode->data.getPopulation())
			{
				return searchRecursive(cityNode->left, pop);
			}
			else
			{
				return searchRecursive(cityNode->right, pop);
			}
		}
		return nullptr;
	}
	void printCityBST_InOrderRecursive(CityNode* cityNode) {
		if (cityNode == nullptr)
		{
			return;
		}
		printCityBST_InOrderRecursive(cityNode->left);
		cityNode->data.printInfo();
		printCityBST_InOrderRecursive(cityNode->right);
	}
	int getHeightRecursive(CityNode* cityNode) {
		if (cityNode == nullptr)
		{
			return -1;
		}

		int leftHeight = getHeightRecursive(cityNode->left);
		int rightHeight = getHeightRecursive(cityNode->right);
		return 1 + max(leftHeight, rightHeight);
	}
};

#endif

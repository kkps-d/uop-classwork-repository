#ifndef CITYBST_H
#define CITYBST_H

#include <string>
#include "citynode.h"

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
	CityNode* search(unsigned int pop) {
		CityNode* cur;
		cur = root;
		while (cur != nullptr) {
			if (pop == cur->data.getPopulation())
			{
				return cur;
			}
			else if (pop < cur->data.getPopulation())
			{
				cur = cur->left;
			}
			else
			{
				cur = cur->right;
			}
		}
		return nullptr;
	}
	void printCityBST() {
		printCityBSTRecursive(root, 0);
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
};

#endif

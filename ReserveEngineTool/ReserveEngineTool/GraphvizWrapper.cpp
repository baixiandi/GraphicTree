#include "GraphvizWrapper.h"
#include <assert.h>
#include <fstream>
#include <iostream>

namespace GraphvizWrapper_space {
	GraphvizWrapper* GraphvizWrapper::hInstance = nullptr;
	std::mutex GraphvizWrapper::m_Mutex;

	GraphvizWrapper* GraphvizWrapper::gethInstance() {
		std::unique_lock<std::mutex> lock(m_Mutex);
		if (hInstance == nullptr) {
			hInstance = new GraphvizWrapper();
		}
		assert(hInstance != nullptr);
		return hInstance;
	}

	Node *GraphvizWrapper::ge_root_node() {
		return this->root_node;
	}

	void GraphvizWrapper::set_root_node(Node *node) {
		this->root_node = node;
	}
	Node* GraphvizWrapper::produce_node()
	{
		Node* node = (Node *)malloc(sizeof(Node)); 
		assert(node != nullptr);
		memset(node, 0, sizeof(Node));
		this->nodes.push_back(node);
		return node;
	}
	void GraphvizWrapper::clear_all_node()
	{
		for (int index = 0; index < this->nodes.size(); index++) {
			if (nullptr != nodes.at(index)) {
				free( nodes.at(index) );
			}
		}
		this->nodes.clear();
	}
	std::vector<Node*> GraphvizWrapper::get_all_nodes()
	{
		return this->nodes;
	}
	void node_set_left(_Node* node, _Node* left)
	{
		node->left = left;
	}
	void node_set_right(_Node* node, _Node* right)
	{
		node->right = right;
	}
	void nodes2file(_Node* root, std::string filename)
	{
	    //std::cout<< __FUNCTION__ << std::endl;
		std::string result;
		result.append("digraph G{\n");

		//这里先对所有节点做拓展
		std::vector<Node*> nodes = GraphvizWrapper::gethInstance()->get_all_nodes();
		for (int index = 0; index < nodes.size(); index++) {
			std::string node_name = nodes.at(index)->node_name;
			std::vector<std::string> context = nodes.at(index)->context ;
			if ((!node_name.empty()) && (!context.empty())) {
				result.append("\t" + node_name + " [" +"\n");
				result.append("\t\t");
				result.append("label = ");

				result.append("\"");
				for (int j = 0; j < context.size(); j++) {
					result.append(context.at(j));
					result.append(";\n");
				}
				result.append("\"");
				result.append("\n");
				result.append("\t");
				result.append("]");
			}
			result.append("\n");
		}

		Node* node = root ;
		std::stack<Node*> stk;
		while (node != nullptr || !stk.empty()) {
			while (node != nullptr) 
			{
				if (node->left != nullptr) {
					result.append("\t" + node->node_name + "->" + node->left->node_name + ";\n");
				}
				if (node->right != nullptr) {
					result.append("\t" + node->node_name + "->" + node->right->node_name + ";\n");
				}
				stk.push(node);
				node = node->left;
			}
			while (!stk.empty())
			{
				node = stk.top();
				stk.pop();
				node = node->right;

			}
		}

		result.append("}");

		std::ofstream of(filename);
		std::string temp;
		of << result;
		of.close();
		std::cout << result << std::endl;
	}
	void PreOrderTraverse(Node* node)
	{
		if (node != nullptr) {
			std::cout << node->node_name << std::endl;
			PreOrderTraverse(node->left);
			PreOrderTraverse(node->right);
		}
	}
	void InOrderTraverse(Node* node)
	{
		if (node != nullptr) {
			PreOrderTraverse(node->left);
			std::cout << node->node_name << std::endl;
			PreOrderTraverse(node->right);
		}
	}
	void PostOrderTraverse(Node* node)
	{
		if (node != nullptr) {
			PreOrderTraverse(node->left);
			PreOrderTraverse(node->right);
			std::cout << node->node_name << std::endl;
		}
	}
}


#pragma once

#include <mutex>
#include <iostream>
#include <string>
#include <vector>
#include <stack>


namespace GraphvizWrapper_space {

	typedef struct _Node {
		std::string node_name;
		std::vector<std::string> context;
		_Node *left = nullptr;
		_Node* right = nullptr;
		unsigned int ref_count = 0;
	}Node;

	void node_set_left(_Node* node, _Node* left);
	void node_set_right(_Node* node, _Node* right);
	void nodes2file(_Node* root, std::string filename);
	void PreOrderTraverse(Node *node);
	void InOrderTraverse(Node* node);
	void PostOrderTraverse(Node* node);

	class GraphvizWrapper
	{
	private:
		static GraphvizWrapper* hInstance;
		static std::mutex m_Mutex;
		Node *root_node;
		std::vector<Node*> nodes;
	public:
		static GraphvizWrapper* gethInstance();
		Node *ge_root_node();
		void set_root_node(Node *node);
		Node* produce_node();
		void clear_all_node();
		std::vector<Node*> get_all_nodes();
	};
}




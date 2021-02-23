// ReserveEngineTool.cpp : 此文件包含 "main" 函数。程序执行将在此处开始并结束。
//

#include <iostream>
#include <string>
#include <vector>
#include "GraphvizWrapper.h"

int main()
{
    //std::cout << "Hello World!\n";

    using namespace GraphvizWrapper_space;

    Node *root = GraphvizWrapper_space::GraphvizWrapper::gethInstance()->produce_node();
    
    Node *left = GraphvizWrapper_space::GraphvizWrapper::gethInstance()->produce_node();

    Node* right = GraphvizWrapper_space::GraphvizWrapper::gethInstance()->produce_node();

    root->left = left;
    
    root->right = right;

    //初始化节点内部的内容,这里暂时存放std::string
    std::vector<std::string > root_context;
    std::vector<std::string > left_context;
    std::vector<std::string > right_context;

    //初始化根节点
    root_context.push_back(std::string("r_node"));
    root_context.push_back(std::string("em,are you a man?"));

    //初始化左节点
    left_context.push_back(std::string("yes i am a man"));

    //初始化右节点
    right_context.push_back(std::string("no i am a woman"));

    //节点设定
    root->context = root_context;
    root->node_name = std::string("root");
    left->context = left_context;
    left->node_name = std::string("left");
    right->context = right_context;
    right->node_name = std::string("right");

    GraphvizWrapper_space::GraphvizWrapper::gethInstance()->set_root_node(root);

    nodes2file(root,std::string("D:/Graphviz/bin/test.dot"));
    

    GraphvizWrapper_space::GraphvizWrapper::gethInstance()->clear_all_node();

    
}

// 运行程序: Ctrl + F5 或调试 >“开始执行(不调试)”菜单
// 调试程序: F5 或调试 >“开始调试”菜单

// 入门使用技巧: 
//   1. 使用解决方案资源管理器窗口添加/管理文件
//   2. 使用团队资源管理器窗口连接到源代码管理
//   3. 使用输出窗口查看生成输出和其他消息
//   4. 使用错误列表窗口查看错误
//   5. 转到“项目”>“添加新项”以创建新的代码文件，或转到“项目”>“添加现有项”以将现有代码文件添加到项目
//   6. 将来，若要再次打开此项目，请转到“文件”>“打开”>“项目”并选择 .sln 文件

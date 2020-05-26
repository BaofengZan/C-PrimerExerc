/*
 * @Author: your name
 * @Date: 2020-05-26 16:40:09
 * @LastEditTime: 2020-05-26 17:44:43
 * @LastEditors: Please set LastEditors
 * @Description: 类模板的声明和实现要放在一起,否则编译报错,找不到实现
 *               以及spdlog库的简单使用
 * @FilePath: \vscodeCMakeTmplate\Project\CircularQueueTemplate\CircularQueue.cpp
 */ 

#include <iostream>
#include "MyQueue.h"
#include "spdlog/spdlog.h"
#include "spdlog/sinks/basic_file_sink.h"
int main()
{
    spdlog::set_level(spdlog::level::debug);
    // 设置等级后,大于设置的等级 相关log信息才会被输出
    // debug info warning error critical
    spdlog::debug("debug log!!");
    spdlog::info("Welcome to spdlog!");
    spdlog::warn("warning log!!");
    spdlog::error("error log!!");
    spdlog::critical("critical log!!");
    
    auto file_logger = spdlog::basic_logger_mt("basic_logger", "log/basic.log");  // log文件夹在最上层的CMakeLists.txt同级目录
    spdlog::set_default_logger(file_logger);

    spdlog::debug("debug log!!");
    spdlog::info("Welcome to spdlog! writing");
    spdlog::warn("warning log!!");
    spdlog::error("error log!!");
    spdlog::critical("critical log!!");
    // 写入形式:[2020-05-26 17:30:04.514] [basic_logger] [info] Welcome to spdlog! writing
    // 程序结束后才会写入文件

    MyQueue<int> Q(4);
    Q.EnQueue(1);
    Q.EnQueue(2);
    Q.EnQueue(3);
    Q.EnQueue(4);
    Q.QueueTraverse();
    std::cout << "=============" << std::endl;
    Q.EnQueue(5);
    Q.QueueTraverse();
    std::cout << "=============" << std::endl;
    //////
    int p = Q.DeQueue();
    std::cout << p << std::endl;

    std::cout << "=============" << std::endl;
    Q.EnQueue(5);
    Q.QueueTraverse();
    
    return 0;
}
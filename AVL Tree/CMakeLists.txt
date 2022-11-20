cmake_minimum_required(VERSION 3.23)
project(avl_tree_reimplemented C)

set(CMAKE_C_STANDARD 23)

add_executable(avl_tree_reimplemented avl_tree.c BST.c)

#ifndef __ARGPARSE_H__
#define __ARGPARSE_H__

#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct CommandArg {
  /* 参数名
   * 1. 使用--或者-作为前缀的参数
   * 2. 位置参数
   */
  char *flag;
  //   ArgAction arg_action;
  //   ArgNargs arg_nargs;
  /* 参数是否为必须参数 */
  int required;
  /* 参数的初始值 */
  void *init;
  /* 用于存放参数的真值 */
  void *value;
  /* 对参数的说明 */
  char *help;
} CommandArg;

typedef struct Command {
  /* 子命令的命令名，为空时即为通用命令 */
  char *name;
  /* 子命令的描述 */
  char *description;
  /* 子命令的使用方法 */
  char *usage;
  /* 解析器的回调函数 */
  void* (*callback)(int nargs, CommandArg *args);
  /* 解析器的参数个数 */
  int nargs;
  /* 必须要传递的参数个数 */
  int required_nargs;
  /* 存放的参数个数 */
  struct CommandArg *args;
} Command;

typedef struct ArgumentParser {
  /* 解析器的名字 */
  char *prog;
  /* 描述 */
  char *description;
  /* 使用方法 */
  char *usage;
  /* 含有的子命令个数 */
  int ncmd;
  /* 目前解析器还可以放置几个子命令 */
  int fcmd;
  /* 通用的命令参数 */
  Command *generic_cmd;
  /* 子命令 */
  Command **cmd;
} ArgumentParser;

/* 全局只使用一个解析器 */
extern struct ArgumentParser *__parser;

typedef void *(*callback_t)(int nargs, CommandArg *args);
void *argparse_add_command(char *command_name, char *description, char *usage,
                           callback_t callback, CommandArg *args);
void argparse_init_parser(char *prog, char *description, char *usage);
void argparse_parse_args(int argc, char *argv[]);
void argparse_print_parser();
void argparse_print_command();
#endif

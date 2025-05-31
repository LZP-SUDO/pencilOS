#include "terminal.hpp"
#include "io.hpp"

// 内核主函数
extern "C" void kernel_main() {
    // 初始化终端
    Terminal terminal;
    terminal.initialize();
    
    terminal.write_string("MyOS v0.1 - Simple Operating System\n");
    terminal.write_string("Type 'help' for available commands\n");
    
    // 简单命令行界面
    char input[100];
    while (true) {
        terminal.write_string("> ");
        terminal.read_string(input, sizeof(input));
        
        // 处理命令
        if (strcmp(input, "help") == 0) {
            terminal.write_string("Available commands:\n");
            terminal.write_string("help - Show this help\n");
            terminal.write_string("clear - Clear screen\n");
            terminal.write_string("echo - Print text\n");
        } 
        else if (strcmp(input, "clear") == 0) {
            terminal.clear();
        }
        else if (strncmp(input, "echo ", 5) == 0) {
            terminal.write_string(input + 5);
            terminal.write_string("\n");
        }
        else {
            terminal.write_string("Unknown command: ");
            terminal.write_string(input);
            terminal.write_string("\n");
        }
    }
}
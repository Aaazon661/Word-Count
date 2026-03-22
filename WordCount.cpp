#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

// 函数声明
void print_usage();
int count_characters(FILE *file);
int count_words(FILE *file);

int main(int argc, char *argv[]) {
    // 检查参数数量
    if (argc != 3) {
        print_usage();
        return 1;
    }
    
    char *parameter = argv[1];  // 参数：-c 或 -w
    char *filename = argv[2];   // 文件名
    
    // 检查参数是否合法
    if (strcmp(parameter, "-c") != 0 && strcmp(parameter, "-w") != 0) {
        printf("错误：参数必须是 -c 或 -w\n");
        print_usage();
        return 1;
    }
    
    // 打开文件
    FILE *file = fopen(filename, "r");
    if (file == NULL) {
        printf("错误：无法打开文件 '%s'\n", filename);
        return 1;
    }
    
    int result = 0;
    
    // 根据参数选择统计模式
    if (strcmp(parameter, "-c") == 0) {
        result = count_characters(file);
        printf("字符数：%d\n", result);
    } else if (strcmp(parameter, "-w") == 0) {
        result = count_words(file);
        printf("单词数：%d\n", result);
    }
    
    // 关闭文件
    fclose(file);
    
    return 0;
}

// 打印使用说明
void print_usage() {
    printf("使用方法：\n");
    printf("  wordCount.exe -c filename  统计文件字符数\n");
    printf("  wordCount.exe -w filename  统计文件单词数\n");
    printf("\n示例：\n");
    printf("  wordCount.exe -c input.txt\n");
    printf("  wordCount.exe -w input.txt\n");
}

// 统计字符数
int count_characters(FILE *file) {
    int count = 0;
    int ch;
    
    // 重置文件指针到开头
    rewind(file);
    
    // 读取每个字符（包括空格、制表符、换行符）
    while ((ch = fgetc(file)) != EOF) {
        count++;
    }
    
    return count;
}

// 统计单词数
int count_words(FILE *file) {
    int count = 0;
    int ch;
    int in_word = 0;  // 标记是否在单词中
    
    // 重置文件指针到开头
    rewind(file);
    
    while ((ch = fgetc(file)) != EOF) {
        // 如果是空格或逗号，表示单词结束
        if (ch == ' ' || ch == ',' || ch == '\n' || ch == '\t' || ch == '\r') {
            if (in_word) {
                count++;
                in_word = 0;
            }
        } else {
            // 不是分隔符，说明在单词中
            in_word = 1;
        }
    }
    
    // 处理文件以单词结尾的情况
    if (in_word) {
        count++;
    }
    
    return count;
}

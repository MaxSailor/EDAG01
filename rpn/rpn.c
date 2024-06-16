#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <stdbool.h>
#define N		(10)

void error(int line, const char* errMsg){
  printf("line %d: error at %s\n", line, errMsg);
}

int main(void)
{
  int stack[N];
  volatile int top = 0;
  int c;
  int line = 1;
  int num;
  while((c = getchar()) != EOF){
    if(isdigit(c)){
      if(top < N + 1){
        num = c -'0';
        while(isdigit(c = getchar())){
          num = (num * 10) + (c - '0');
        }
        ungetc(c, stdin);
        stack[top] = num;
        top++;
      }else{
        char str[1];
        str[0] = c;
        error(line, str);
        while ((c = getchar()) != '\n' && c != EOF);
        line++;
        top = 0;
      }
    }else if(c == '+' || c == '-' || c == '*' || c == '/'){
      if(top >= 2){
        switch(c){
          case '+': stack[top -2] = stack[top-2] + stack[top-1]; break;
          case '-': stack[top -2] = stack[top-2] - stack[top-1]; break;
          case '*': stack[top -2] = stack[top-2] * stack[top-1]; break;
          case '/':
            if(stack[top-1] != 0){
              stack[top -2] = stack[top-2] / stack[top-1];
             }else{
               //char str[1];
               //str[0] = c;
               error(line, "/");
               while ((c = getchar()) != '\n' && c != EOF);
               line++;
               top = 0;
             }
            break;
        }
        top--;
      }else{
        char str[1];
        str[0] = c;
        error(line, str);
        while ((c = getchar()) != '\n' && c != EOF);
        line++;
        top = 0;
      }
    }else if(c == ' '){

    }else if(c == '\n'){
      if(top == 1){
        printf("line %d: %d\n", line, stack[top-1]);
       }else{
         error(line, "\\n");
       }
      top = 0;
      line++;
    }else{
      char str[1];
      str[0] = c;
      error(line, str);
      while ((c = getchar()) != '\n' && c != EOF);
      top = 0;
      line++;
    }

  }
  return 0;
}
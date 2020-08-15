#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

void mrr_rr_hook(const char * file, const int32_t line){
  printf("foo");
}

int main(int argc, char const *argv){
  printf("dummy\n");
  mrr_rr_hook("foo.rb", 3);
  return 0;
}

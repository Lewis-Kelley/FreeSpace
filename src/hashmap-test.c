#include <stdio.h>
#include <string.h>
#include "hashmap.h"

int main(int argc, char **argv) {
  Hashmap map = {(Node *)malloc(100 * sizeof(Node)), 100};
  for(int i = 0; i < 100; i++)
    map.data[i] = (Node){NULL, NULL, 0, NULL};

  char *str = (char *)malloc(256 * sizeof(char));
  int *item = (int *)malloc(sizeof(int));

  for(int i = 0; i < 10; i++) {
    printf("Enter a number and string to store:\n");
    scanf("%d %s", item, str);

    printf("Read values %d and %s.\n", *item, str);

    hashmap_put(&map, str, item, sizeof(int));
  }

  printf("Enter a string to lookup or quit to quit:\n");
  scanf("%s", str);

  *item = 0;

  while(strcmp(str, "quit") != 0) {
    if(map.data[0].data != NULL)
      printf("In output loop with stack = {%s, %d, %p}\n", map.data[0].key,
             *(int *)map.data[0].data, map.data[0].next);

    item = (int *)hashmap_find(map, str);

    if(item != NULL) {
      printf("Found item %d at %s!\n", *item, str);
    } else {
      printf("Could not find %s.\n", str);
    }

    printf("Enter a string to lookup or quit to quit:\n");
    scanf("%s", str);
  }

  return 0;
}

#include <ctype.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int findValue(int x, int y, int **array, int size);
int actualSizeOf(int arr[], int size);
int *intdup(int const *src, size_t len);
int factorial(int n);
int actualSizeOf2D(int **arr, int rows);
int **createPairArray(int count);

int main(void) {
  srand(time(0));
  int x[] = {3, 4, 9, 5, 1, 2, 6, 7, 8, 10, 11};
  int n = sizeof(x) / sizeof(x[0]);
  int target = 10;

  bool gettingPairs = true;
  int index = 0;
  int maxSize = factorial(n) / (factorial(2) * factorial(n - 2));
  int **pairs =
      createPairArray(maxSize); // move outside the loop so it persists
  while (gettingPairs) {
    int pairsCheckpoint = n - index - 1;

    int numberOfPairs = actualSizeOf2D(pairs, maxSize);
    if (numberOfPairs == maxSize) {
      printf("found all values: %d\n", numberOfPairs);
      break;
    }

    int countOfPairs = 0;
    int *tempArray = intdup(x, n);
    printf("values: size:%d pairs:%d\n", maxSize, numberOfPairs);

    while (countOfPairs < pairsCheckpoint) {
      numberOfPairs = actualSizeOf2D(pairs, maxSize);

      int randIndex = index + 1 + rand() % (n - index - 1);

      if (tempArray[randIndex] == -1) {
        continue;
      }

      int foundValue =
          findValue(tempArray[index], tempArray[randIndex], pairs, maxSize);

      if (foundValue == 0) {
        int insertAt = actualSizeOf2D(pairs, maxSize);
        pairs[insertAt][0] = tempArray[index];
        pairs[insertAt][1] = tempArray[randIndex];
        tempArray[randIndex] = -1;
        countOfPairs++;

        printf("Found pair: (%d, %d)\n", tempArray[index], pairs[insertAt][1]);
      }
    }

    free(tempArray);

    if (index >= n - 2) {
      gettingPairs = false;
    }
    index++;
  }
  int countTarget = 0;
  // Cleanup
  for (int i = 0; i < maxSize; i++) {
    if (pairs[i][0] + pairs[i][1] == target) {
      countTarget++;
    }
    free(pairs[i]);
  }
  free(pairs);
  printf("final pairs equal 10: %d", countTarget);
}

int **createPairArray(int count) {
  int **array = malloc(count * sizeof(int *));
  for (int i = 0; i < count; i++) {
    array[i] = malloc(2 * sizeof(int));
    array[i][0] = -1;
    array[i][1] = -1;
  }
  return array;
}

int factorial(int n) {
  int result = 1;
  for (int i = 2; i <= n; i++) {
    result *= i;
  }
  return result;
}

int findValue(int x, int y, int **array, int size) {
  for (int i = 0; i < size; i++) {
    if ((array[i][0] == x && array[i][1] == y) ||
        (array[i][0] == y && array[i][1] == x)) {
      return 1;
    }
  }
  return 0;
}

int actualSizeOf(int arr[], int size) {
  int count = 0;
  for (int i = 0; i < size; i++) {
    if (arr[i] != -1) {
      count++;
    }
  }
  return count;
}

int actualSizeOf2D(int **arr, int rows) {
  int count = 0;
  for (int i = 0; i < rows; i++) {
    if (arr[i][0] != -1) {
      count++;
    }
  }
  return count;
}

int *intdup(int const *src, size_t len) {
  int *p = malloc(len * sizeof(int));
  memcpy(p, src, len * sizeof(int));
  return p;
}

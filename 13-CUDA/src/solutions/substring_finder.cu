// Parallel substring finder
// returns the index of the first occurrence of the substring in the string (per
// thread) or -1 if not found

#include <random>
#include <string>

#include <stdio.h>
#include <stdlib.h>

char *random_string(int length) {
  // Create a random number generator
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_int_distribution<> dis(0, 25);
  char *str = (char *)malloc(length + 1);
  for (int i = 0; i < length; i++) {
    str[i] = 'a' + dis(gen);
  }
  str[length] = '\0';
  return str;
}

void __global__ find_substring(char *string, char *substring, int *result,
                               int string_length, int substring_length,
                               int num_threads) {
  int i = blockIdx.x * blockDim.x + threadIdx.x;
  int start_index = i * num_threads;
  int end_index = start_index + num_threads;
  int found = 0;
  int index = -1;

  printf("Thread %d: start_index = %d, end_index = %d, string_len = %d\n", i,
         start_index, end_index, string_length);

  if (end_index > string_length) {
    end_index = string_length;
  }

  for (int j = start_index; j < end_index; j++) {
    if (string[j] == substring[0]) {
      found = 1;
      for (int k = 1; k < substring_length; k++) {
        if (string[j + k] != substring[k]) {
          found = 0;
          break;
        }
      }
      if (found) {
        index = j;
        break;
      }
    }
  }

  result[i] = index;
}

int main(int argc, char *argv[]) {
  int string_length = 10000000;
  int substring_length = 5;
  int num_threads = 4;
  char *string = random_string(string_length);
  char *substring = (char *)"pizza";

  int *result = (int *)malloc(sizeof(int) * num_threads);
  int *d_result;
  cudaMalloc((void **)&d_result, sizeof(int) * num_threads);

  char *d_string;
  cudaMalloc((void **)&d_string, sizeof(char) * string_length);
  cudaMemcpy(d_string, string, sizeof(char) * string_length,
             cudaMemcpyHostToDevice);

  char *d_substring;
  cudaMalloc((void **)&d_substring, sizeof(char) * substring_length);
  cudaMemcpy(d_substring, substring, sizeof(char) * substring_length,
             cudaMemcpyHostToDevice);

  find_substring<<<1, num_threads>>>(d_string, d_substring, d_result,
                                     string_length, substring_length,
                                     string_length / num_threads);

  cudaMemcpy(result, d_result, sizeof(int) * num_threads,
             cudaMemcpyDeviceToHost);

  int i;
  int min_index = -1;
  for (i = 0; i < num_threads; i++) {
    if (result[i] != -1) {
      min_index = result[i];
      break;
    }
  }

  if (min_index != -1) {
    printf("Found substring at index %d\n", min_index);
    char *found = (char *)malloc(sizeof(char) * (substring_length + 1));
    for (int j = 0; j < substring_length; j++) {
      found[j] = string[min_index + j];
    }
    found[substring_length] = '\0';

    printf("Result: %s\n", found);
  } else {
    printf("Substring not found\n");
  }

  // get a null-terminated string at the index
  cudaFree(d_string);
  cudaFree(d_substring);
  cudaFree(d_result);
  free(string);
  free(result);

  return 0;
}

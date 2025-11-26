int rolling(int dice[], int size) {
  int roll = random_int (0, size -1);
  int roll2 = random_int (0, size-1);
  int sum = dice[roll] + dice[roll2];
  return sum;
}

void count_product (int log[], int size11, int sums[], int size) {
    for (int i = 0; i < size; i++)
    {
      if (sums[i] == 2)
      {
        log [1] ++;
      } else if (sums[i] == 3)
      {
        log [2] ++;
      } else if (sums[i] == 4)
      {
        log [3] ++;
      } else if (sums[i] == 5)
      {
        log [4] ++;
      } else if (sums[i] == 6)
      {
        log [5] ++;
      } else if (sums[i] == 7)
      {
        log [6] ++;
      } else if (sums[i] == 8)
      {
        log [7] ++;
      } else if (sums[i] == 9)
      {
        log [8] ++;
      } else if (sums[i] == 10)
      {
        log [9] ++;
      } else if (sums[i] == 11)
      {
        log [10] ++;
      } else if (sums[i] == 12)
      {
        log [11] ++;
      } 
    }
}
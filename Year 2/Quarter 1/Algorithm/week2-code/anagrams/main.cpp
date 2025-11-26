#include <iostream>
#include <string>
#include <array>

int main() {
  /* TODO:
      Write a program that reads two lines of input: the first line contains a word,
      and the second line contains a sentence that may contain an anagram of the word (ignoring spaces).
      The program should find the first anagram of the word in the sentence and print it.
      If no anagram is found, the program should print "<not found>".

      Example input:
        conversation
        our voices rant on forever
      Example output: voices rant on
  */
  std::string target, text;
  std::getline (std::cin, target);
  std::getline(std::cin, text);

  //prepare target frequency
  std::array<int, 26> target_freq{};
  int target_len = 0;
  for(char c : target){
    if(isalpha(c)){
      target_freq[c - 'a']++;
      target_len++;
    }
  }

  //sliding window
  std::array<int, 26> window_freq{};
  int left = 0, count = 0;  //count is the num of ch in window

  for (int right = 0; right < (int)text.size(); right++){
    char rc = text[right];
    if(isalpha(rc)){
      window_freq[rc - 'a']++;
      count ++;
    }

    //if window too big -> shrink from left
    while(count > target_len){  //only for shrinking the window and updating the frequency array. 
      char lc = text[left++];   //does not prevent non-alphabetic characters from being part of the window
      if(isalpha(lc)){
        window_freq[lc - 'a']--;
        count --;
      }
    }
    
    //if window size matches target length -> anagram
    if(count == target_len && window_freq == target_freq){
      //skip non-alphabetic at the start (quotes, punctuation) 
      while(left < (int)text.size() && !isalpha(text[left])){
        left++;
      }
      std::cout << text.substr(left, right - left + 1) << std::endl;  //std::string substr (size_t pos = 0, size_t len = npos) const;
      return 0;       //right - left + 1 = len of substr
    }
  }
  
  
  //no match
  std::cout << "[]" << std::endl;
  return 0;
}

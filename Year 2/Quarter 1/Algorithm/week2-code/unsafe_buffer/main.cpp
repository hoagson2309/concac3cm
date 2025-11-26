#include <iostream>
#include <string>

// int main() {
//     /* TODO:
//         Write a program that reads an integer that specifies the size of a buffer,
//         followed by a string to process.
//         Each character (unless it is '*') should be enqueued into the buffer, and if the buffer is full,
//         the oldest character should be dequeued to make space for the new character.
        
//         In case a '*' character is encountered, the program should dequeue a character from the buffer
//         and print it to standard output.
        
//         All characters must appear on a single line, without spaces.
//     */
//     size_t size;
//     std::cin >> size;
//     std::cin.ignore();   //discard newline after size input
    
//     char* buffer = new char[size]{};

//     size_t head = 0; 
//     size_t tail = 0;
//     size_t count = 0;//num of elements currently in the buffer

//     char ch;
//         while(std::cin.get(ch)){
//             if(ch == '*'){
//                 if(count > 0){
//                 //dequeue 
//                 std::cout << buffer[head];
//                 head = (head + 1) % size;   
//                 count--;
//                 }
//             } else if(ch != '\n' && ch != '\r') {  
//                 //enqueue
//                 buffer[tail] = ch;
//                 tail = (tail + 1) % size;

//                 if(count < size){          
//                     count++;     
//                 } else {
//                     //full -> drop oldest element
//                     head = (head + 1) % size;
//                 }                                                                                                      
//             }
//         }

//     //clean space
//     delete[] buffer;
//     return 0;
// }


#include <iostream>
#include <string>
#include <memory>

class Buffer{

    public:
        
        Buffer(int size) :_size(size),  _buffer(std::make_unique<char[]>(_size)) {}

        void queue(char ch) {
            _buffer[_tail] = ch;   
            _tail = (_tail + 1) % _size;   //abc*def*gh 
        }

        char dequeue() {
            char ch = _buffer[_head];
            _head = (_head + 1) % _size;
            return ch;
        }

    private:
        const int _size;
        int _tail = 0;
        int _head = 0;
        std::unique_ptr<char[]> _buffer;
};


int main() {    
    /* TODO:
        Write a program that reads an integer that specifies the size of a buffer,
        followed by a string to process.
        Each character (unless it is '*') should be enqueued into the buffer, and if the buffer is full,
        the oldest character should be dequeued to make space for the new character.
        
        In case a '*' character is encountered, the program should dequeue a character from the buffer
        and print it to standard output.
        
        All characters must appear on a single line, without spaces.
    */
    
    int buffer_size;
    std::string sentence;

    std::cin >> buffer_size >> sentence;
    Buffer buffer(buffer_size);

    for (char c : sentence){

    if (c == '*') {
            
            std::cout << buffer.dequeue();
        }

        else buffer.queue(c);

    }
    return 0;
}
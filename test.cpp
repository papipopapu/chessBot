#include <iostream>
#include <sstream>
#include <string>

using namespace std;

string fen = "rnbqkbnr/ppppp1pp/8/3PPp2/5P2/5BP1/PPP4P/RNBQK1NR w KQkq f6 0 2";

int main() {
    std::string flags = fen.substr(fen.find(' ')), token_str;
	int size = flags.size(), idx = 1;
	unsigned char token = flags[idx++];
	int epsq = 79;

	idx++; // skip space
	while (idx < size && flags[idx] != ' ') {
		token = flags[idx++];
        std::cout << token << std::endl;
	}
	int epsq0 = 0;
	idx++; // skip space
	token = flags[idx]; 
    std::cout << "1:"<<token << std::endl;
	switch (token) {
	case 'a':
		epsq0 += 0;
		break;
	case 'b':
		epsq0 += 1;
		break;
	case 'c':
		epsq0 += 2;
		break;
	case 'd':
		epsq0 += 3;
		break;
	case 'e':
		epsq0 += 4;
		break;
	case 'f':
		epsq0 += 5;
		break;
	case 'g':
		epsq0 += 6;
		break;
	case 'h':
		epsq0 += 7;
		break;
	}  
    idx++;
	token = flags[idx];
	if (token != ' ') {
	switch (token) {
	case '1':
		epsq = epsq0;
		break;
	case '2':
		epsq = epsq0 + 8;
		break;
	case '3':
		epsq = epsq0 + 16;
		break;
	case '4':
		epsq = epsq0 + 24;
		break;
	case '5':
		epsq = epsq0 + 32;
		break;
	case '6':
		epsq = epsq0 + 40;
		break;
	case '7':
		epsq =epsq0 + 48;
		break;
	case '8':
		epsq = epsq0 + 56;
		break;
	}
	idx++; // skip space
	}
    idx++;
    std::cout << "1.5:"<<flags[idx] << std::endl;
	while (idx < size && flags[idx] != ' ') {
        std::cout << "2:"<<flags[idx] << std::endl;
		token_str += flags[idx++];
	}

    std::cout << epsq << std::endl;
    std::cout << token_str << std::endl;
   
   
   
   
	
    return 0;
}
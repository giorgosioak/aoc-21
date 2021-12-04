#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>
#include <bitset>

#define SIZE 12 // change to 5 for example

int main () {

	if ( !std::filesystem::exists("input") ){
		std::cout << "input file does not exist" << std::endl;
		return 1;
	}

	std::ifstream input("input");


	/* --- Part 1 --- */
	
	int count_zeros[SIZE];
	std::vector<std::bitset<SIZE>> data;

	std::string line;
	
	while ( std::getline(input, line) ) {
		std::bitset<SIZE> b(line);
		data.push_back(b);

		for (int i = 0; i < SIZE; i++) {
			count_zeros[i] += b[i] ^ 1; // if zero : counter++
		}

	}

	std::bitset<SIZE> gamma;
	int size = data.size();
	for (int i = 0; i < SIZE; i++) {
		gamma[i] = ( count_zeros[i] > size/2 ) ? 0 : 1;
	}


	std::bitset<SIZE> epsilon = gamma;
	epsilon.flip();

	std::cout << "Part1: " << gamma.to_ulong()  * epsilon.to_ulong() << std::endl;

	/* --- Part 2 --- */

	/* oxygen generator rating */

	std::vector<std::bitset<SIZE>> oxygen = data;
	
	for (int i = SIZE-1; i >= 0; i--) {

		int count_zeros = 0;
		for ( auto b : oxygen ) {
			count_zeros += b[i] ^ 1;
		}
		int oxygen_rate = ( count_zeros > oxygen.size()/2 ) ? 0 : 1;

		if ( oxygen.size() > 1 ){
			auto end = std::remove_if(oxygen.begin(), oxygen.end(), [&oxygen_rate,&i](std::bitset<SIZE> &bs) { return bs[i] != oxygen_rate; });
			oxygen.erase(end, oxygen.end());	
		} else {
			break;
		}
	}

	/* CO2 scrubber rating */


	std::vector<std::bitset<SIZE>> co2_scrubber = data;
	
	for (int i = SIZE-1; i >= 0; i--) {

		int count_zeros = 0;
		for ( auto b : co2_scrubber ) {
			count_zeros += b[i] ^ 1;
		}
		int co2_scrubber_rate = ( count_zeros <= co2_scrubber.size()/2 ) ? 0 : 1;

		if ( co2_scrubber.size() > 1 ){
			auto end = std::remove_if(co2_scrubber.begin(), co2_scrubber.end(), [&co2_scrubber_rate,&i](std::bitset<SIZE> &bs) { return bs[i] != co2_scrubber_rate; });
			co2_scrubber.erase(end, co2_scrubber.end());	
		} else {
			break;
		}
	}
	
	std::cout << "Part2: " << oxygen[0].to_ulong() * co2_scrubber[0].to_ulong() << std::endl;


	return 0;


}
	




// 	for (int i = 0; i <1000; i++) {
// 		input >> x;
// 		for (int j = 0; j < 12; j++){
// 			digit = x % 10;
// 			data[i][11-j] = digit;
// 			common[11-j][digit]++;
// 			x = x / 10;
// 		}
// 	}

// 	for (int j = 0; j < 12; j++){
// 		std::cout << j << ": " << common[j][0] << " " << common[j][1] << std::endl;
// 	}

// 	for (int j = 0; j < 12; j++){
// 		if ( common[j][0] > common[j][1] ) {
// 			gamma_rate = gamma_rate*10;
// 			epsilon_rate = epsilon_rate*10 + 1;
// 		} else {
// 			gamma_rate = gamma_rate*10 + 1;
// 			epsilon_rate = epsilon_rate*10;
// 		}
// 	}
	
// 	std::cout << "Part1: " << convert(gamma_rate) * convert(epsilon_rate) << std::endl;

// 	// /* --- Part 2 --- */

// 	long oxygen_generator_rating = 0, CO2_scrubber_rating = 0;

// 	int oxygen_generator_rating_match[12], CO2_scrubber_rating_match[12];
// 	int count_oxygen, last_pos_oxygen;
// 	int count_co2, last_pos_co2;
// 	int result_oxygen = -1, result_co2 = -1;

// 	for (int j = 0; j < 12; j++) {
// 		oxygen_generator_rating_match[j] = (common[j][0] > common[j][1]) ? 0 : 1;
// 		CO2_scrubber_rating_match[j] = (common[j][0] <= common[j][1]) ? 0 : 1;
// 	}

// 	for (int j = 0; j < 12; j++) {
		
// 		if ( result_oxygen == -1 ) {
// 			for (int i = 0; i < 1000; i++) {
// 				count_oxygen = 0;
// 				for (int k = 0; k < j; k++){
// 					if ( data[i][k] == oxygen_generator_rating_match[k] ){
// 						count_oxygen++;
// 						last_pos_oxygen = i;
// 					}
// 				}
// 			}

// 			if ( count_oxygen == 1 ){
// 				result_oxygen = last_pos_oxygen;
// 				break;
// 			}

// 		}
// 	}

// 	for (int j = 0; j < 12; j++) {

// 		if ( result_co2 == -1 ) {
// 			for (int i = 0; i < 1000; i++) {
// 				count_co2 = 0;
// 				for (int k = 0; k < j; k++){
// 					if ( data[i][k] == CO2_scrubber_rating_match[k] ){
// 						count_co2++;
// 						last_pos_co2 = i;
// 					}
// 				}
// 			}

// 			if ( count_co2 == 1 ){
// 				result_co2 = last_pos_co2;
// 				break;
// 			}
// 		}
// 	}

// 	for (int j = 0; j < 12; j++){

// 		oxygen_generator_rating = oxygen_generator_rating * 10;
// 		oxygen_generator_rating += data[result_oxygen][11-j];

// 		CO2_scrubber_rating = CO2_scrubber_rating * 10;
// 		CO2_scrubber_rating += data[result_co2][11-j];
	
// 	}

// 	std::cout << "Part2: " << convert(oxygen_generator_rating) * convert(CO2_scrubber_rating) << std::endl;

// 	return 0;
// }
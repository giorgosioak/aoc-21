#include <iostream>
#include <fstream>
#include <vector>
#include <algorithm>
#include <filesystem>
#include <string>
#include <numeric>
#include "entry.hpp"

Entry::Entry() {
    value = 0;
}

/* Check all inputs and match segments */
void Entry::check() {

    set_unique_segments();
    set_five_six_segs();

    /* 1 is contained in 3 */
    for ( int f = 0; f < five_seg.size(); f++ ) {
        if ( is_contained_in(number[1],five_seg[f]) ) {
            number[3] = five_seg[f];
            five_seg.erase(five_seg.begin()+f);
            break;
        }
    }

    /* 5 is only contained in 6 and 9 , you can find 5 and 2 */
    for ( int f = 0; f < five_seg.size(); f++ ) {
        for ( int s = 0; s < six_seg.size(); s++ ) {
            if ( is_contained_in(five_seg[f],six_seg[s]) ) {

                number[5] = five_seg[f];
                five_seg.erase(five_seg.begin()+f);

                number[2] = five_seg[0];
                five_seg.erase(five_seg.begin());

                break;
            }
        }
    }

    /* 5 is contained in 6 and 9 and not in 0 */
    for ( int s = 0; s < six_seg.size(); s++ ) {
        if ( !is_contained_in(number[5],six_seg[s]) ) {

            number[0] = six_seg[s];
            six_seg.erase(six_seg.begin()+s);

            break;
        }
    }

    /* 1 is contained in 9 and not in 6 */
    for ( int s = 0; s < six_seg.size(); s++ ) {
        if ( is_contained_in(number[1],six_seg[s]) ) {

            // std::cout << " 9 " << six_seg[s] << std::endl;

            number[9] = six_seg[s];
            six_seg.erase(six_seg.begin()+s);

            number[6] = six_seg[0];
            six_seg.erase(six_seg.begin());

            break;
        }
    }

    set_value();
}

void Entry::set_five_six_segs() {
    for ( auto display : input ) {

        if ( five_seg.size() == 3 && six_seg.size() == 3 )
            return;

        if ( display.size() == 5 && five_seg.size() < 3 ) {
            if( std::find(five_seg.begin(), five_seg.end(), display) == five_seg.end() ) {
                five_seg.push_back(display);
            }
        }

        if ( display.size() == 6 && six_seg.size() < 3 ) {
            if( std::find(six_seg.begin(), six_seg.end(), display) == six_seg.end() ) {
                six_seg.push_back(display);
            }
        }
    }
}

void Entry::set_unique_segments() {

    bool found1 = false;
    bool found4 = false;
    bool found7 = false;
    bool found8 = false;

    for ( auto display : input ) {

        if ( found1 && found4 && found7 && found8 )
            return;

        switch (display.size()) {
        
            case 2: /* Digit 1 uses 2 segments */
                number[1] = display;
                found1 = true;
                break;

            case 3: /* Digit 7 uses 3 segments */
                number[7] = display;
                found4 = true;
                break;

            case 4: /* Digit 4 uses 4 segments */
                number[4] = display;
                found7 = true;
                break;

            case 7: /* Digit 8 uses all 7 segments */
                number[8] = display;
                found8 = true;
                break;

            default: /* Digit 8 uses all 7 segments */
                break;
        }
    }

    for ( auto display : output ) {

        if ( found1 && found4 && found7 && found8 )
            return;
        
        switch (display.size()) {
        
            case 2: /* Digit 1 uses 2 segments */
                std::cout << "Digit 1 " << display << std::endl;
                number[1] = display;
                found1 = true;
                break;

            case 3: /* Digit 7 uses 3 segments */
                std::cout << "Digit 7 " << display << std::endl;
                number[7] = display;
                found4 = true;
                break;

            case 4: /* Digit 4 uses 4 segments */
                std::cout << "Digit 4 " << display << std::endl;
                number[4] = display;
                found7 = true;
                break;

            case 7: /* Digit 8 uses all 7 segments */
                std::cout << "Digit 8 " << display << std::endl;
                number[8] = display;
                found8 = true;
                break;

            default:
                break;
        }
    }
}

/* if x is contained in y */
bool Entry::is_contained_in(std::string x, std::string y) {
    if ( x.size() > y.size() ) return false;

    for( char c : y ) {
        x.erase(std::remove(x.begin(), x.end(), c), x.end());
    }

    return x.empty();
}

void Entry::set_value() {
    for ( auto str : output ) {

        for ( int i = 0; i < 10; i++ ) {
            if ( str == number[i] ) {
                value *= 10;
                value += i;
            }
        }
        
    }
}

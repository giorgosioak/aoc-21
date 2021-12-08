#ifndef ENTRY_H__
#define ENTRY_H__

class Entry {
    public:

        std::vector<std::string> input = { };
        std::vector<std::string> output = { };
        std::vector<std::string> five_seg = { };
        std::vector<std::string> six_seg = { };
        std::string number[10];

        int value;

        Entry();

        void check();        
        void set_five_six_segs();
        void set_unique_segments();
        bool is_contained_in(std::string, std::string);
        void set_value();

};

#endif
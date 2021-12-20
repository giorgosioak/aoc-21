#/bin/bash 

AOC_SESSION="<your session cookie>"

args=("$@")
argc=${#args[@]}

if [ $argc != 1 ]; then
    echo "Usage: ./setup.sh <day number>"
    exit 1
fi

DAY=${args[0]}
echo "DAY" $DAY

# Create directory
mkdir $DAY
cd $DAY

# Create makefile
echo "all:" > makefile
echo -e "\tg++ -std=c++17 code.cpp" >> makefile

# Create code.cpp file to edit
touch code.cpp

# Create example file to edit
touch example

# Download input
curl --silent --cookie "session=$AOC_SESSION" https://adventofcode.com/2021/day/$DAY/input -o input

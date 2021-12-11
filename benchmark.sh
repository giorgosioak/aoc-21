for day in */ ; do
    cd $day
    make > /dev/null 2>&1
    elapsed=$( { time ./a.out >/dev/null; } 2>&1 | grep real | sed 's/real//' )
    echo "Day" "${day%/}:" $elapsed
    cd ..
done
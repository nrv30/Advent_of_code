BEGIN {
    
}

NR == 1 {
    len_times = split(substr($0, index($0, ":")+1, length($0)), times, " ")
    for (i = 1; i <= len_times; i++) {
        #print times[i]
    }
}

{
    size = split(substr($0, index($0, ":")+1, length($0)), distances, " ")
    for (i = 1; i <= size; i++) {
        map[times[i]] = distances[i]
    }
}

END {
    margin = 1
    for (time in map) {
        count = 0
        print "time: ", time
        for (i = 1; i <= time+0; i++) {
            #print i
            remaining_time = time - i;
            #print "remaining time:", remaining_time
            #print "distance", i * remaining_time
            if (i*remaining_time > map[time]) {
                count++
            }
        }
    print count
    margin *= count
    }
    print margin
}


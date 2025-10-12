BEGIN{
	scratch_card_total = 0
}

{
	colon_index = index($0, ":")
	pipe_index = index($0, "|")
	print "PIPE INDEX: "
	print  pipe_index
	winning_nums = substr($0, colon_index+1, pipe_index-1-colon_index-1)
	elf_nums = substr($0, pipe_index+2, length($0))

	winning_size = split(winning_nums, winning_nums_arr, " ")
	elf_size = split(elf_nums, elf_nums_arr, " ")

	#print "----Winning nums----"
	#print winning_nums
	#print "----elf_nums----"
	#print elf_nums

	#print winning_nums_arr[1]
	#print winning_nums_arr[2]

		#print elf_nums_arr[1]

	matches = 0

	for (i = 1; i <= winning_size; i++) {
		num = winning_nums_arr[i]
		#print num
		for (j = 1; j <= elf_size; j++) {
			if (elf_nums_arr[j] == num) {
				#print  elf_nums_arr[j]
				if (matches == 0){
					matches++
				}
				else matches *= 2
				break
			}
		}
	}
	#print matches
	scratch_card_total += matches

}

END {
	print scratch_card_total
}

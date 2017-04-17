Project 2 with time complexity of O(n + w + m^2)

	To get the index of hint within the main string I used a trie and added every possible suffix of the main string to it. Assuming the main string has length w then this has a run time of O(w). Then I searched the trie for the hint of length n. This has a runtime complexity of O(n). Therefore, to get the indexes of the hint within the main string the time complexity is O(n + w).

	To get the longest palidromic subsequence of the combination sequence I used dynamic programming. By storing overlapping subproblems in a 2d array I was able to run the lps in O(m^2) where m is the length of the combination sequence. Although, I only needed to use the top diagonal of the 2d array so the average time complexity is closer to (m^2)/2.



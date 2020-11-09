int countNumBits1(int mask) {	// O(bits Length)
	int ret = 0;	//1101001 -> 110100 -> 11010 -> 1101 -> 110 -> 11 -> 1 -> 0
	while (mask) {
		if(mask&1)
			ret++;
		mask >>= 1;
	}
	return ret;
}
// Get bit
int getBit(int num, int idx) {
  return ((num >> idx) & 1) == 1;		// 110100, idx = 4  -->  110 & 1 = 0
}

int setBit1(int num, int idx) {
	return num | (1<<idx);
}

int setBit0(int num, int idx) {
	return num & ~(1<<idx);				// 110100, idx = 3  -->  110100 & ~000100 = 110100 & 111011
}

int flipBit(int num, int idx) {
	return num ^ (1<<idx);
}

/*
X-1 is very important!
X 	= 840 	= 01101001000
X-1 = 839 	= 01101000111		What happened? First bit 16=(2^4) is removed, and 15=2^4-1 is added.
X & (X-1) 	= 01101000000		first bit from right removed
X & ~(X-1) 	= 01101001000 & 10010111000 = 0000000100 		value of 1<<SmaintestBitIdx
*/

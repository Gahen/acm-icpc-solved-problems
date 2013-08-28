#include <algorithm>    // std::copy
#include <vector>       // std::vector
#include <iostream>
#include <stdio.h>
#include <string>
#include <map>
#include <set>
#include <math.h>
#include <string.h>

using namespace std;

int calc(int nums[131074], int s, bool isOr) {
	if (isOr) {
		for (int i=1; i <= s; i+=2) {	
			nums[i/2+1] = nums[i] | nums[i+1];
		}
	} else {
		for (int i=1; i <= s; i+=2) {	
			nums[i/2+1] = nums[i] ^ nums[i+1];
		}
	}
	s = s/2;

	if (s > 1) {
		return calc(nums, s, !isOr);
	} else {
		return nums[1];
	}
}

int main() {
	int s, n, m;
	scanf("%d %d", &n, &m);
	int nums[131074], nums2[131074];

	int i = 1;
	s = pow(2, n);
	n = s;
	while (n--) {
		int k;
		scanf("%d", &k);
		nums[i++] = k;
		// cout << " nums[" << i-1 << "] = " << k << endl;
	}

	while (m--) {
		int i, k;
		scanf("%d %d", &i, &k);
		nums[i] = k;
		memcpy(&nums2, nums, sizeof(nums2));
		printf("%d\n", calc(nums2, s, true));
	}
}

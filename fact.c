
int Fact(int p) {
	if (p == 1) return 1;
	return p * Fact(p-1);
}

int main() {
	int x;
	x = ReadInt();//not available for now
	LogMsg("Factorial of %d is %d.", x, Fact(x));
	return 0;
}

int main () {
	int x,cond;
	x = 100;
	while (x > 1) {
		x--;
		cond = x == 1;
		LogMsg("%d bottle%sof beer on the wall,", x, cond ? " " : "s ");
		LogMsg("%d bottle%sof beer.", x, cond ? " " : "s ");
		LogMsg("Take one down,");
		LogMsg("pass it around,");
		cond = x == 2; // (x-1) == 1
		LogMsg("%d bottle%sof beer on the wall!\n", x-1, cond ? " " : "s ");
	}
	return 0;
}
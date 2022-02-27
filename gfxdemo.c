///////////////////////////////////////////////////////
//// GRAPHICS DEMO FOR NANOSHELL OPERATING SYSTEM  ////
///////////////////////////////////////////////////////

int red, green, blue;
int background;
int ballpos, balldir, balldelta;

int main(){
	int k,x1,x2;

	red = 16711680; green = 65280; blue = 255;
	background = 32639;
	FillScreen(background); // Black

	DrawString (red+green+blue, 10, 10, "Text Demo");

	FillRectangle(100,400,400,700,green);
	DrawRectangle(100,400,400,700,red);
	DrawRectangle(101,401,399,699,red);

	DrawString (red+green+blue, 10, 20, "Press any key to do a scroll thing");
	ReadChar();
	DrawString (background, 10, 20, "Press any key to do a scroll thing");
	k = 40;
	while (k > 0) {
		ShiftScreenY(4);
		k--;
	}
	DrawString(10,400,"Shifted! Press any key to get the Ball thing.");
	ReadChar();//wait for a keypress

	// ball bounce - ctrl+c
	ballpos = 100;
	balldir = 0;//0 - ballpos increments, 1 - ballpos decrements
	balldelta = +10;
	
	while (1) {
		//if (balldelta != 0) {
		//	DrawString(red+green+blue,10,10,"LOOOOOOOOOOOL");
		//	if (balldelta < 0)
		//	{ x2 = ballpos + 40; x1 = ballpos + 40 + balldelta; }
		//	else
		//	{ x2 = ballpos + balldelta; x1 = ballpos + 40; }
		//	FillRectangle(x1,100,x2,140,background);
		//}
		FillRectangle(ballpos,100,ballpos+40,140,background);

		if (balldir == 1)
			balldelta = -10;
		else
			balldelta = +10;
		ballpos = ballpos + balldelta;
		if (ballpos < 100) {
			ballpos = 100;	
			balldir = balldir ^ 1;
		}
		if (ballpos > 900) {
			ballpos = 900;	
			balldir = balldir ^ 1;
		}
		FillRectangle(ballpos,100,ballpos+40,140,green);
		//ReadChar();
	}

	return 0;
}



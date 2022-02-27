// Brainfuck interpreter (C) 2021 iProgramInCpp

char* g_pBrainfuckExample;

int* g_pAllocatedBuffer;//nothing in here!
int  g_memorySize, g_pointer;

char g_debug, g_verbose, g_example;

void RunBrainfuckCode(const char* pCode) {
	char* pHead;
	char opc;
	int loopCount, cond;//how many loops we need to go back

	pHead = pCode;
	g_pAllocatedBuffer = malloc (sizeof(int)*g_memorySize);
	memset(g_pAllocatedBuffer, 0, sizeof(int)*g_memorySize);
	g_pointer = g_memorySize >> 1;

	while (*pHead != '/') {
		opc = *pHead;
		if (g_verbose) LogMsg("[H:%d] Read in '%c'. Pointer is %d and value in it is %d (%c)", pHead - pCode, opc, g_pointer, g_pAllocatedBuffer[g_pointer], g_pAllocatedBuffer[g_pointer]);
		if (opc == '>') g_pointer++; // move pointer to right
		if (opc == '<') g_pointer--; // move pointer to left
		if (opc == '+') g_pAllocatedBuffer[g_pointer]++;
		if (opc == '-') g_pAllocatedBuffer[g_pointer]--;
		if (opc == '.') LogMsgNoCr("%c", g_pAllocatedBuffer[g_pointer] & 0xFF);//!NOTE: we don't support character output like that yet
		if (opc == ',') g_pAllocatedBuffer[g_pointer] = ReadChar();
		// oh boy, loops
		if (opc == '[') {
			if (g_verbose) LogMsg("Loop start at index %d", pHead - pCode);
			if (g_pAllocatedBuffer[g_pointer] == 0) {
				if (g_verbose) LogMsg("Current cell is equal to zero, skipping a chunk of code");
				// skip to after the matching ']' cell
				loopCount = 0;
				cond = 1;
				while (*pHead != '/' && cond) {
					if (g_verbose) LogMsg("[H:%d] pHead should increment right about now", pHead - pCode);
					pHead++;//skip all that code
					if (g_verbose) LogMsg("[H:%d] there it is", pHead - pCode);
					if (*pHead == '[') {
						loopCount++;
						if (g_verbose) LogMsg("[H:%d] Start of loop, loopCount is %d", pHead - pCode, loopCount);
					}
					if (*pHead == ']') {
						if (loopCount == 0) cond = 0;
						else loopCount--;
						if (g_verbose) LogMsg("[H:%d] End of loop, cond is %d and loopCount is %d", pHead - pCode, cond, loopCount);
					}
				}
			}
		}
		if (opc == ']') {
			if (g_pAllocatedBuffer[g_pointer] != 0) {
				// skip to after the matching ']' cell
				loopCount = 0;
				cond = 1;
				while (*pHead != '/' && cond) {
					pHead--;//go back through all that code
					if (*pHead == ']') {
						loopCount++;
						if (g_verbose) LogMsg("[H:%d] Endd of loop, loopCount is %d", pHead - pCode, loopCount);
					}
					if (*pHead == '[') {
						if (loopCount == 0) cond = 0;
						else loopCount--;
						if (g_verbose) LogMsg("[H:%d] Startt of loop, cond is %d and loopCount is %d", pHead - pCode, cond, loopCount);
					}
				}
			}
		}

		pHead++;
	}

	free(g_pAllocatedBuffer); g_pAllocatedBuffer = 0;
}

void PrintHelp() {
	LogMsg("Brainfuck interpreter (C) 2021 iProgramInCpp");
	LogMsg("Programs end with /.");
}

void OnRunOwnProgram()
{
	char* code1, *code2;
	char input, check;
	code1 = malloc(16384);
	code2 = code1;
	check = 1;
	LogMsg("Type out your BF program here.  Finish it with /. Max sizeof program: 16384");

	while (check)
	{
		input = ReadChar();
		if (input == 8)
		{
			//remove one char:
			code2--;
			*code2=0;
		}
		else if (input == '/')
		{
			LogMsg("Program write ended.  Now executing...");
			check = 0;//no break!
		}
		else if (input != 0x2b && input != 0x2d && input != 0x5b && input != 0x5d &&
				 input != 0x2e && input != 0x2c && input != 0x3c && input != 0x3e)
		{
			//ignore non bf characters :)
		}
		else
		{
			if (input == 13) input = 10;
			LogMsg("%c %d",input,input);
			*code2++ = input;
		}
	}
	RunBrainfuckCode(code1);
	free(code1);
}

int main () {
	g_memorySize = 30000;
	LogMsg("Debug (d) or no-debug (n)?");
	g_debug = ReadChar();
	if (g_debug == 'd') g_debug = 1;
	else                g_debug = 0;
	LogMsg("\n\nVerbose (v) or not verbose? (n)");
	g_verbose = ReadChar();
	if (g_verbose == 'v') g_verbose = 1;
	else                  g_verbose = 0;

	while (1) {
		LogMsg("Exit (e), run hello world (h), run c-test (c), or type in your own program (t)?");
		g_example = ReadChar();
		if (g_example == 'e') {
			exit(0);
		}
		else if (g_example == 't') {
			OnRunOwnProgram();
		} 
		else if (g_example == 'h')
		{
			g_pBrainfuckExample = "++++++++[>++++[>++>+++>+++>+<<<<-]>+>+>->>+[<]<-]>>.>---.+++++++..+++.>>.<-.<.+++.------.--------.>>+.>++.////";
			LogMsg("Print program before running? (press p to accept printing)");
			g_example = ReadChar();
			if (g_example == 'p')
			{
				LogMsg("Program: %s", g_pBrainfuckExample);
			}
//			OnRunExampleProgram();
			RunBrainfuckCode(g_pBrainfuckExample);
		}
		else if (g_example == 'c')
		{
			g_pBrainfuckExample = "+++[>+++++<-]>>+<[>>++++>++>+++++>+++++>+>>+<++[++<]>---]>++++.>>>.+++++.>------.<--.+++++++++.>+.+.<<<<---.[>]<<.<<<.-------.>++++.<+++++.+.>-----.>+.<++++.>>++.>-----.<<<-----.+++++.-------.<--.<<<.>>>.<<+.>------.-..--.+++.-----<++.<--[>+<-]>>>>>--.--.<++++.>>-.<<<.>>>--.>.<<<<-----.>----.++++++++.----<+.+++++++++>>--.+.++<<<<.[>]<.>>,[>>+++[<+++++++>-]<[<[-[-<]]>>[>]<-]<[<+++++>-[<+++>-[<-->-[<+++>-[<++++[>[->>]<[>>]<<-]>[<+++>-[<--->-[<++++>-[<+++[>[-[-[-[->>]]]]<[>>]<<-]>[<+>-[<->-[<++>-[<[-]>-]]]]]]]]]]]]]<[-[-[>+<-]>]<[<<<<.>+++.+.+++.-------.>---.++.<.>-.++<<<<.[>]>>>>>>>>>]<[[<]>++.--[>]>>>>>>>>]<[<<++..-->>>>>>]<[<<..>>>>>]<[<<..-.+>>>>]<[<<++..---.+>>>]<[<<<.>>.>>>>>]<[<<<<-----.+++++>.----.+++.+>---.<<<-.[>]>]<[<<<<.-----.>++++.<++.+++>----.>---.<<<.-[>]]<[<<<<<----.>>.<<.+++++.>>>+.++>.>>]<.>]>,]<<<<<.<+.>++++.<----.>>---.<<<-.>>>+.>.>.[<]>++.[>]<.////";
			LogMsg("Print program before running? (press p to accept printing)");
			g_example = ReadChar();
			if (g_example == 'p')
			{
				LogMsg("Program: %s", g_pBrainfuckExample);
			}
//			OnRunExampleProgram();
			RunBrainfuckCode(g_pBrainfuckExample);
		}
	}
}
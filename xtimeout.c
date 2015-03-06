/*
 * Runs until dpms timesout. Useful for running a command when the screen
 * turns off.
 *
 * -------------------------------------------------------------------------
 *
 * MIT/X Consortium License
 * 
 * (C) 2014-2015 Mytchel Hammond <mytchel at openmailbox dot org>
 * 
 * Permission is hereby granted, free of charge, to any person obtaining a
 * copy of this software and associated documentation files (the "Software"),
 * to deal in the Software without restriction, including without limitation
 * the rights to use, copy, modify, merge, publish, distribute, sublicense,
 * and/or sell copies of the Software, and to permit persons to whom the
 * Software is furnished to do so, subject to the following conditions:
 * 
 * The above copyright notice and this permission notice shall be included in
 * all copies or substantial portions of the Software.
 * 
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
 * IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
 * FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL
 * THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
 * LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING
 * FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER
 * DEALINGS IN THE SOFTWARE.
 */

#include <stdio.h>
#include <X11/Xlib.h>
#include <X11/extensions/dpms.h>

/*
 * Returns -1 if not capable, 0 if not on else one of 
 * DPMSModeStandby, DPMSModeSuspend, DPMSModeOff, DPMSModeOn:
 */
int dpmsinfo(Display *dis) {
	int dummy;
	CARD16 state;
	BOOL onoff;
	if (DPMSQueryExtension(dis, &dummy, &dummy)) {
		if (DPMSCapable(dis)) {
			DPMSInfo(dis, &state, &onoff);
			if (onoff) 
				return state;
			else 
				return 0;
		} else {
			return -1;
		}
	} else {
		return -1;
	}
}

int main(int argc, char *argv[]) {
	Display *dis;
	CARD16 state;
	int delay = 1;

	if (argc != 1) {	
		printf("Usage: %s\n", argv[0]);
		printf("Checks the DPMS status each second then exits when the screen turns off\n");
		printf("Return status 2 if DPMS not avaliable\n");
		return 0;
	}

	dis = XOpenDisplay(NULL);
	if (!dis) {
		fprintf(stderr, "Failed to open display\n");
		return 1;
	}

	do {
		sleep(delay);
		state = dpmsinfo(dis);
		if (state < 0) return 2;
	} while (state == DPMSModeOn);

	return 0;
}


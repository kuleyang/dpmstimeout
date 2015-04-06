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
#include <stdlib.h>
#include <X11/Xlib.h>
#include <X11/extensions/dpms.h>

void usage() {
	printf("Usage: dpmstimeout [on|standby|suspend|off]\n");
	printf("Checks the DPMS status each second then exits when the state changes to one of the states specified (yes, that means you can specify more than one state). Defaults to standby, suspend and off.\n");
	printf("Return status 1 if DPMS not avaliable\n");
	exit(0);
}

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
	int i, delay = 1;
	int checking[4] = {0, 1, 1, 1};

	for (i = 1; i < argc; i++) {
		if (strcmp(argv[i], "on") == 0) checking[DPMSModeOn] = 1;
		if (strcmp(argv[i], "standby") == 0) checking[DPMSModeStandby] = 1;
		if (strcmp(argv[i], "suspend") == 0) checking[DPMSModeSuspend] = 1;
		if (strcmp(argv[i], "off") == 0) checking[DPMSModeOff] = 1;
		if (strcmp(argv[i], "-h") == 0) usage();
	}

	dis = XOpenDisplay(NULL);
	if (!dis) {
		fprintf(stderr, "Failed to open display\n");
		return 1;
	}

	while (1) {
		state = dpmsinfo(dis);
		if (state < 0) return 1;
		if (checking[state]) return 0;
		sleep(delay);
	}
}


xtimeout
========
xtimeout is a simple program that checks the dpms status each second and exists when DPMS timeout occurs.

For example if you wanted to have slock called when your at DPMS timeout put something like this in your .xinitrc

	$ (while true; do xtimeout && slock; done) &

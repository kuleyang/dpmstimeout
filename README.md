dpmstimeout
===========
checks the dpms status each second and exists when the DPMS state is equal to one of the states specified.

Takes arguments 'on', 'standby', 'suspend', 'off'. You can give multiple options. It will exit when the state changes to one of those. Defaults to standby, suspend and off.

For example if you wanted to have slock called when state changes to standby, suspend or off, put something like this in your .xinitrc

	$ (while true; do dpmstimeout && slock; done) &

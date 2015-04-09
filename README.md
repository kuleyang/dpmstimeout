dpmstimeout
===========
checks the dpms status each second and exists when the DPMS state is equal to one of the states specified.

Takes arguments 'on', 'standby', 'suspend', 'off'. You can give multiple options. It will exit when the state changes to one of those. Defaults to standby, suspend and off.

Look at dmpslock for an example.

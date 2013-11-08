# SDoS Test Client #

-------

Thank you a lot for using the Sauerbraten Day of Sobriety Test Client!

Please help with testing by sending your feedback.

# What is this? #

This is test client is the foundation of what the anti-cheat client is
built on. It doesn't include any of the anti-cheat functions. The
reason it needs testing is that it uses SDL version 2 rather than
version 1, which the regular Sauerbraten client is built on. This
newer version of SDL brings many improvements that help with both the
normal game and the anti-cheat protections, but it is a major
change. Things could break. We need some help with testing.

You can play with this client on any normal server. It's meant to work
just like the normal sauer client, with some improvements.

# Installation #

The installation is the same as the acc client or the swlacc
builds. If you can't remember the procedure, you can refresh your
memory with the appropriate README in the archive.

# Testing #

The following is some sparse info of what you should consider while
testing. Reports of oddities or bad functioning are important, but
"everything works fine" is helpful too.

- General stability and performance
- Mouse input
  - sensitivity might change. __Do not change your sensitivity with
    the normal variables__. Please tune the variable
    `sdl2_sensitivity_adjust` (default value 1.0), **and report your
    findings**. Was sensitivity different from the standard
    Sauerbraten client, and what value of `sdl2_sensitivity_adjust`
    made it seem the same? This is very important!
  - are all your mouse buttons recognized? If you have a mouse with
    many buttons (more than 3), please test them thoroughfully. If a
    button doesn't seem to be recognized, go in the `binds` options
    panel, and try to bind the button to some action, and note the
    button name, if it shows up
  - the new `relativemouse 0|1` variable is related to the new SDL2
    mouse handling. Default is 1, and 0 seems to never work, but if it
    does for you, please report
- Compatibility with vanilla config and data files
  - new configuration variables should go to `sdos.cfg`, to avoid
    interfering with `config.cfg`
  - are there error messages (undefined variables and such) on
    startup?
  - are there error on startup shown by the vanilla client after the
    test client has been run once, or unwanted modification to
    configuration values?
- Minimization, general window/fullscreen handling
  - can you switch from the test client window/fullscreen to your
    desktop? Try <kbd>alt-tab</kbd>, or <kbd>windows-R</kbd>, or
    <kbd>ctrl+alt+d</kbd> too
- Vertical synch
  - variable `vsync` now is only 0 or 1 (-1 does not exist anymore)
  - there is a new variable `vsynctear`, effective if vsync is on,
    which should provide better vsync performance
- <kbd>Ctrl+v</kbd> should finally work on linux, report if this is
  not the case
- Linux users with old OSes (specifically with an old glibc installed,
  found on Debian wheezy) should now be able to run the normal binary,
  not needing anymore an .oldglibc version, report if this is not the
  case
- Bonus pro setting `multipoll 0|1|2`: low latency input
  - test `multipoll 1` this with `vsync 0` and maxfps set to something
    appropriate (tipycally a multiple of your monitor refresh, 60):
    the fps will be limited by `maxfps`, but contrary to vanilla the
    input will be polled at least once per millisecond, not once for
    each drawn frame. Please report your impressions, together with
    the numbers you get with `showfps 1`
  - if you really want to push it to the extreme, use `multipoll 2`:
    input will be polled continuously. Warning: this is likely to be
    useless, and will make the test client use one CPU core completely
- `showfps 1` now uses a different internal logic: fps counting should
  be more precise and responsive, but the downside is that the refresh
  rate is now fixed to one second.

# Giving Feedback #

Send feedback

- via email to pisto, blaffablaffa at gmail
- via irc in #sdos on Gamesurge

When giving a feedback, please include:

- some way to contact you back
- version of the test client you use (only 1.0 as of now)
- build type (OS and 32/64 bit if applicable)
- graphic card model and driver, if related to the issue
- mouse model, if related to the issue

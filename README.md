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
    desktop? Try <kbd>Alt</kbd>+<kbd>Tab</kbd>, or <kbd>⌘ Win</kbd>+<kbd>R</kbd>, or
    <kbd>Ctrl</kbd>+<kbd>Alt</kbd>+<kbd>D</kbd> too
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
- `showfps 1` now uses a different internal logic: fps counting should
  be more precise and responsive, but the downside is that the refresh
  rate is now fixed to one second. Also, `showfpsrange 1` has no effect.
- Bonus pro setting `multipoll -1|0|1`: low latency input.
  Before explaining the meaning of /multipoll, it's better to have a look
  at the info printed by `/showfps 1`:
  - "fps"  : the frames drawn on screen per second
  - "ifps" : the engine refreshes per second (input polling, networking,
    physics..., what you really want to be responsive)
  - "draw" : the milliseconds that drawing a frame takes
  Competitive players usually set /vsync 0 and a high /maxfps, because in
  most games, Sauerbraten included, there is a single engine refresh
  per frame drawn ("fps" == "ifps"). This minimizes input lag, but you get:
  - screen tearing, because display update happens with a steady pace
    (usually 60 Hz), and with /vsync 0 you don't sinchronize to that pace
    (you draw more, less, or starting at different times)
  - waste of CPU/GPU resources
  - you usually don't get more than 200-300 fps
  `/multipoll` tries to fix this problem by breaking the equality of fps
  and ifps, e.g. the engine is refreshed more often than frames are drawn.
  Since the world state cannot be modified while the frame is drawn, and
  refreshing the engine is a very cheap operation, basically the maximum
  input lag that you can encounter equals the "draw" value shown in the
  fps statistics, and how often that delay happens is exactly "fps" times
  in a second.

  - `/multipoll  0`: one frame drawn for each engine update, as in vanilla.
  - `/multipoll -1`: engine is refreshed continuously, but every 1000/`maxfps`
    milliseconds a frame is drawn. Pros: known to work (it was shipped with
    SDoS test client 1.1). Cons: `vsync` has to be disabled (because it would
    block the same thread that runs engine updates) so you do get tearing,
    and a good value of /maxfps must be sought by trial and error (but
    generally it is either very high or a multiple of your screen refresh rate)
  - `/multipoll +1`: a separate thread handles flushing the graphic card
    commands and waiting for `vsync`, the main thread refreshes the engines
    continuously and when the other thread signals availability a frame is
    drawn. Pros: doesn't need `maxfps` (set it to 0), works very well with and
    without `vsync`. With it, you get the advantages of multipoll  and no
    tearing at all, and you minimize the number of frames drawn (cfr maximum
    input lag and draw millis), without you may get a smaller value of draw
    millis (cfr draw millis again). Cons: it simply crashes or freezes on
    some setups. After a lot of experimenting I believe that it comes down
    to the video card driver to either support multithreading in OpenGL or not.

  Ultimately, it's up to you to choose the values that best suit you. I personally
  think that `vsync` makes everything a whole lot smoother, and `/multipoll 1`
  works for me, so that is my choice. If you think that `vsync` is not for you
  first try `/multipoll 1` and `/vsync 0`, and only if it doesn't work try
  `/multipoll -1`.

# Giving Feedback #

Send feedback

- via email to pisto, blaffablaffa at gmail
- via irc in #sdos on Gamesurge

When giving a feedback, please include:

- some way to contact you back
- version of the test client you use
- build type (OS and 32/64 bit if applicable)
- graphic card model and driver, if related to the issue
- mouse model, if related to the issue

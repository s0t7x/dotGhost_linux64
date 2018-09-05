# dotGhost_linux64
linux64 port of dotGhost CSGO hook

# DOTGHOST VERSION CHANGELOG
25.02.2016 version 1.5
	- Debug_Aimlock now draws vecPunchAngle
	- Triggerbot now can use Aimlock (cfg_triggerbot_iAimlock)
	- "Hide" Draw Mode introduced	
	- Aimlock works a little bit better

19.01.2016 version 1.4
	- new code signature
	- edited some bugs with new player struct

08.01.2016 version 1.3
	- added 400 lines of junk code
	- added new configuration to either ask for dump or not
	- fixed a bug where m_vecVelocity[0] wasnt read correctly
	- new code signature

20.12.2015 version 1.2:
	- added icon
	- aimlock does not longer lock onto enemy while in recoil
	- fixed a bug where some settings in the "config.cfg" didnt work
	- several runtime optimizations
	- new code signature

20.12.2015 version 1.1:
	- new function to read settings out of "config.cfg"
	- fixed a bug where the Aimlock locked the view on false coordinates
	- fixed "GetEnginePointerAddr()" as it was updated by the game
	- fixed "draw_DebugAimlock()" to really draw most important debug information instead of things we dont even use
	- fixed entity array
	- several runtime optimizations
	- new code signature

18.12.2015 version 1.0:
	- initial working release
  
  # Commentary
Our goal was to implement our own code into the game during the lifetime of Cs-Go in order to gain advantages over other players.
This approach is also known as a so-called hook. The realization of the project was mainly favored by the fact that the source code of the game is freely available.

The implementation of our functions started with a so-called wallhack. Our first goal was therefore to make visible opponents behind objects and walls. For this we now had two options. On the one hand, we could have had a box drawn around each character, but that was quite a lot Effort. On the other hand, there was the possibility, thanks to the freely visible source code, to take over a function from the viewer mode which draws the individual characters in these modes through walls. So we have just made use of this feature by the hookand fake that we are in spectator mode.

Next up was the Triggerbot and the Aimlock on our list. For the trigger we have (trigger) the ID's of the object located in the crosshair saved. So if an opponent is in the crosshairs, our program simulates a left-click to trigger a shot. Alone this is not very useful, which is why we added an Aimlock. This also recognizes whether the ID in the crosshair is in Team of the player or in the opposite one and then changes the viewpoint so that the crosshair aims directly at the head.
Together with the trigger, for the direct demise of the virtual opposite leads.

Thus, we had our "all around sorglospacket" to annoy other players done.
Unfortunately, during development we often had problems with patches, ie updates of the game that had caused the memory addresses to change like Player coordinates and others that are external to our program. Unfortunately we had to sacrifice a lot of time for the addresses to recover. Also, another problem has persisted, namely that the program is taking up the memory and Prozerssor, which led to, at least on our test laptop, some power drops, which reflected in a low refresh rate.

# simple esp32 synth

*Hey! You found my github! Good job! But what's next?*

Well, this project is still very much under development. I haven't released any schematics for any hardware or anything. But if you want to hack around with what I have so far, here's the general idea:

## The "development environment" (how to set up the jank)
1. Get an esp32, a breadboard, some resistors, capacitors and an npn transistor, a computer, and a USB cable.
2. Get setup with the [esp-idf](https://docs.espressif.com/projects/esp-idf/en/latest/esp32/) environment. If you're a cool leet dude then you can just download it and use their python scripts to do things. If you prefer something actually remotely practical like me, they have a vscode extension! Lower down I'll give some tips for getting that set up. They have an eclipse extension but please don't use eclipse.
3. Make a new project with esp-idf. This is really really bad but the way you have to do it is copy an example project over. Then, save [synth.h](https://github.com/audiodog301/esp32-synth/blob/master/main/synth.h) in your main folder and copy the code from [synth.c](https://github.com/audiodog301/esp32-synth/blob/master/main/synth.c) into your main.c file.
4. Optionally, you can futz with some files (CMakeCache.txt is the not-obvious one you have to mess with) to make your project a little bit more aesthetically pleasing (change the project name, name of the file with your code, etc.) There are also probably some files that come with the example you can delete. Trial and error with educated guesses is your best bet for finding these.
5. Put your esp32 on the breadboard. Using a 0.1uF ceramic capacitor and an ~80ohm resistor, make an R/C low pass filter. Plug the output of the second DAC (whatever that pin is on your esp32) into the input of the low pass.
6. Next you'll need some kind of transistor buffer so you're not pulling a ton of current from the DAC. I haven't worked this out at all so just do some googling with terms like "Class A amp" and "NPN transistor headphone amp" and you should get a result. A 2n4401 or 2n3904 transistor should work. The esp32 might not like you drawing ~300 mA so you may need to get dirty with wiring to pull it straight from USB, or use a separate power supply and tie grounds.
7. Finally, you'll need a blocking capacitor on the output. Just try different ceramic values until your headphones don't break when you plug them in to the output.
8. Oh and you'll need a jack socket on the output to plug in headphones. Tip goes to the output of your buffer and sleeve goes to ground.
9. AT LONG LAST you can flash my bad code onto your esp32 and hear a less-than-impressive 8-bit sawtooth wave.

## The "development environment" 2.0 - vscode!
Here are some tips for defeating some truly AWFUL UX and getting the esp-idf vscode plugin set up:

- It will automatically unzip the zip it downloads to the same place it downloads the zip. You have to find the folder with the same name as the zip and run the install script. THEN you will have access to the folder with all of the paths the setup wizard wants (most of which are difficult to find)
- Once you've hit the button at the end to save your preferences, it doesn't look like it has saved them because closing and re-opening vscode will show the onboarding screen again. It actually does save them. You can safely hit whatever button to stop the onboarding process from happening WHENEVER you open vscode.

## Final thoughts (hopeless ambitions)
When this project gets a little more mature, I hope to write some actually decent instructions on setting everything up so that you don't have to go through the same pain I did.

The code should be fairly well-commented so you can see how it works, even though it is pretty awful. If you have a suggestion on how to improve the code, a feature idea, or a comment, don't hesitate to open an issue.

Happy hacking!

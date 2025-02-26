# Part 2 : Compute Something.

**ComputeSomething.ino** is a big leap forward. The code converts 8 bit binary input to ASCII ouput. However, the code's main focus is to provide a clean, consistent style borrowed from the [Arduino Style Guide](https://docs.arduino.cc/learn/contributions/arduino-writing-style-guide/). I'll try to stick to this convention in Part 2 and beyond. The button code is refactored into a class and the prev "screenOut" function is removed in favor of smaller, more focused functions. I can now easily add more buttons if needed. 

I also try out the **arduino-cli**.

### Set up arduino-cli

- I used Homebrew to install it on mac.
- The .ino program file needs to be in a directory with the same name
- To find the arduino port:

```bash
ls /dev/tty.*
```

Or try:

```bash
arduino-cli board list
```

It might look like: ***/dev/tty.usbserial-XXXXX**

Example of compile and load commands:
```bash

# build
arduino-cli compile --fqbn arduino:avr:uno --output-dir ./ComputeSomething/build ./ComputeSomething

cd Part2/ComputeSomthing

# load
arduino-cli upload --fqbn arduino:avr:uno -p /dev/tty.usbmodem14301
```

I'm not sure if using the CLI tool is worth it yet and at this point I need to define what "computer" means for my project. [A Reddit Debate](https://www.reddit.com/r/computers/comments/1bi3ose/what_is_a_computer/)

That's a wrap for Part 2!


![More Buttons!](https://github.com/cjvillar/MicroCompute/blob/main/SimpleProgam_Part_2/FourButtons.png)

# Exercise Session 1

Work through the exercises in order. Write your answers directly in this file, in the
`_Answer:_` blocks under each question, and commit it together with any `.cpp` files
you are asked to attach, to your own copy of the repository.

---

## Exercise 1: Verify your setup

Confirm that the [`SETUP.md`](../SETUP.md)
instructions have been followed and your Pico development environment is in place.

**Anything that did not work, and how you solved it:**

> _Answer:_
>

---

## Exercise 2: Build and run the blinker

Create, build and flash the example **Blink** project to confirm that your development
environment works from source code all the way to running firmware on the Pico W.

### Instructions

1. Open **Visual Studio Code**.
2. Open the **Raspberry Pi Pico** extension from the sidebar.
3. Create a new project and select the **Blink** example.
   - Select **Pico W** as the target board.
   - Choose a folder for the project.
   - Create/open the project in VS Code.
4. Add a `printf("Test");` statement inside the while loop in main().
5. Build the project.
   - Use the **Compile / Build** command from the Raspberry Pi Pico extension.
   - Watch the terminal output and make sure the build finishes without errors.
6. Connect the Pico W to your computer using USB.
7. Flash the program to the Pico W using the **Run / Flash** command in the
   Raspberry Pi Pico extension or by manually uploading the .uf2 file.
8. Check the board. The LED should now blink continuously.
9. Connect the **Debug Probe** (hardware) and open the **Serial Monitor**, then look for the output.

### Checklist
- [ ] Blink project created and opened
- [ ] Project builds without errors
- [ ] Program flashed to the Pico W
- [ ] The LED is blinking
- [ ] Serial Monitor output is visible

**If the build or flash failed, what was the error and what fixed it?**

> _Answer:_
I had to install driver, but now it works
>

---

## Exercise 3: Explore PicoBricks

For each hardware module on the PicoBricks board, answer the following
questions:

1. What is the name of this module?
2. What does this module do?
3. Is it an input or output?

### Module 1

| # | Question | Answer |
|---|----------|--------|
| 1 | Name |OLED (SDA: GP4, SCL: GP5)|   
| 2 | Purpose |Displays information |
| 3 | Input or output |output|

| # | Question | Answer |
|---|----------|--------|
| 1 | Name |RGB LED (GP6)|   
| 2 | Purpose |Show information through colours|
| 3 | Input or output |output|

| # | Question | Answer |
|---|----------|--------|
| 1 | Name |LED-BUTTON (L: GP7, B: GP10)|   
| 2 | Purpose |B: Sending a signal to the pico, L: Showing an output from the pico|
| 3 | Input or output |L: output, B: input|

| # | Question | Answer |
|---|----------|--------|
| 1 | Name |TEMP.&HUM. (SDA: GP4, SCL: GP5)|   
| 2 | Purpose |To measure air temperature and humidity|
| 3 | Input or output |input|

| # | Question | Answer |
|---|----------|--------|
| 1 | Name |RELAY(GP12)|   
| 2 | Purpose |A switch that can be electronically controlled by Pico|
| 3 | Input or output |output|

| # | Question | Answer |
|---|----------|--------|
| 1 | Name |MOTOR DRIVER (SDA: GP4, SCL: GP5)|   
| 2 | Purpose |A device that allows Pico to safely control a motor.|
| 3 | Input or output |output|

| # | Question | Answer |
|---|----------|--------|
| 1 | Name |WIRELESS(TX: GP0, RX: GP1)|   
| 2 | Purpose |Wi-Fi allows the Pico to communicate wirelessly with other devices and networks.|
| 3 | Input or output |input, output|

| # | Question | Answer |
|---|----------|--------|
| 1 | Name |BUZZER(GP20)|   
| 2 | Purpose |Can produce sound if Pico sends a signal.|
| 3 | Input or output |output|\

| # | Question | Answer |
|---|----------|--------|
| 1 | Name |LDR(GP27)|   
| 2 | Purpose |A light sensor that measure how much light is around.|
| 3 | Input or output |input|

| # | Question | Answer |
|---|----------|--------|
| 1 | Name |POTENTIOMETER(GP26)|   
| 2 | Purpose |Lets you adjust a variable value, such as brightness or motor speed, by turning a knob.|
| 3 | Input or output |input|

_Add more blocks as you write._

---

## Exercise 4: Morse Code

Make a program that blinks `help!` as Morse
code using the LED abstractions in the blink project (`pico_set_led`). How you represent
and translate Morse code is up to you.

Rules:

- dot = 1 time unit (200ms)
- dash = 3 time units 600ms
- gap between dot/dash elements within one letter = 1 unit
- gap between letters = 3 units
- gap between words = 7 units

Use the Morse-code reference below and the C++ book/documentation, Google as needed.

Reference: <https://en.wikipedia.org/wiki/Morse_code>

Simply copy the modified .c file(s) containing your solution to the exercise folder.

**Attached file(s):**

> _Filename:_
blink.c
>

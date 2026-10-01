# Exercise Session 5

Work through the exercises in order. Write answers in the `_Answer:_` blocks. Commit this
file and your `.cpp` files.

Exercises 1-3 are for the session. Exercises 4 and 5 are homework.
See [`homework.md`](homework.md).

Create projects like in Session 4. Use **New Pico Project** → **C/C++**. Pick board
**Pico W**. Tick **Generate C++ code** and **Console over UART**.

---

## Exercise 1: Reading the potentiometer

**Goal:** Read the potentiometer with the ADC. Turn the raw number into volts and ohms.

So far every pin was digital. Digital pins are only 0 or 1. The ADC measures the voltages
in between.

The Pico's ADC has 12 bits. That gives 4096 steps, 0 to 4095. 4095 means 3.3 V.

The potentiometer ("pot") is a knob on a 10 kΩ resistor. One end of the resistor is at
3.3 V, the other at GND. A contact, the wiper, slides along it as you turn the knob and
connects to GP26. Halfway along, it picks up half of 3.3 V. The ohms from the wiper to GND
change the same way.

### Instructions

1. Create a project `pot_adc`. Copy in [`code/pot_adc.cpp`](code/pot_adc.cpp). In
   `CMakeLists.txt`, add `hardware_adc` to `target_link_libraries`.
2. Fill in TODO 1 in `raw_to_volts()`. It gets `raw` and returns volts.
3. Fill in TODO 2 in `raw_to_ohms()`. Set `POT_OHMS` to the value on your pot. `B10K`
   means 10 kΩ.
4. Open the Serial Monitor, build and run. Turn the knob fully both ways. Fill in the
   table.
5. Now leave the knob still. Watch `raw` for a few seconds. Note how much it jumps.
6. Add `<< "  9-bit " << (raw >> 3)` to the print. `>> 3` drops the 3 lowest bits. A
   9-bit ADC would see this.

| Knob | `raw` | volts | ohms |
|---|---|---|---|
| fully left |4095 |3.3 |B10K |
| middle |2150 |1.73 |5220 |
| fully right |30 |0.022 |70 |

`raw` jumps by about 10 steps with the knob still. The 9-bit value jumps by 3.

### Checklist

- [x] TODO 1 and 2 filled in
- [x] Table filled in
- [x] Jumps noted, 12-bit and 9-bit

**How many millivolts is one 12-bit step?**

> _Answer:_
>Approximately  3300/4096=0.806

**The knob was still. Why did `raw` move?**

> _Answer:_
> Small electrical noise from the potentiometer, power supply, reference voltage, wiring, or the ADC itself can make raw fluctuate by a few counts.

**Did the 9-bit value jump less? Why?**

> _Answer:_
>The 9-bit value appeared to jump less because it has lower resolution A 12-bit reading has 4096 possible values, while a 9-bit reading has only 512. Converting from 12-bit to 9-bit usually combines about 8 raw counts into one value. Small changes in raw may therefore be discarded, so the displayed 9-bit value stays still more often. The voltage noise did not necessarily decrease; it is simply less visible..

**Attached file(s):**

> _Filename:_
>

*Read more (optional): Programming Embedded Systems, Sect. 13.1.4.1 ("Analog circuits"):
analog vs. digital, a knob on a variable resistor, and why analog signals are noisy.
Real-Time C++, Sect. 6.13 ("Consider Advantageous Hardware Dimensioning"): a voltage
divider in front of an ADC. Its `raw2mv()` function does the same job as `raw_to_volts()`.*

---

## Exercise 2: Disco in Darkness

**Goal:** Light the LED when it gets dark.

The light sensor works like the pot. It puts a voltage on GP27. Less light gives a higher
number.

### Instructions

1. Create a project `light_led`. Copy in [`code/light_led.cpp`](code/light_led.cpp). In
   `CMakeLists.txt`:
   - Add `hardware_adc` and `pico_status_led` to `target_link_libraries`.
     `pico_status_led` drives the RGB LED on GP6, used from step 6.
   - Below `add_executable(...)`, add this line. It tells the SDK which pin the RGB LED
     is on: `target_compile_definitions(light_led PRIVATE PICO_DEFAULT_WS2812_PIN=6)`
2. Fill in TODO 1. Dark turns the LED on.
3. Build and run. Note `raw` in normal light. Cover the sensor, and note it again.
   A dim room can read higher than a covered sensor in bright light.
4. Set `DARK_THRESHOLD` halfway between your two numbers. Rebuild and test.
5. Half cover the sensor, so `raw` sits near `DARK_THRESHOLD`. Watch the LED.
6. **Disco:** fill in TODO 2. The RGB LED now glows blue in the dark, together with the
   red LED.
7. **Disco:** fill in TODO 3. Keep the position in `COLORS` in a variable declared before
   the loop. `% COLORS.size()` brings it back to 0 after the last colour.

| Normal light | Covered | Your threshold |
|---|---|---|
|91 |3630 |1860 |

### Checklist

- [x] TODO 1 filled in; the LED turns on in the dark
- [x] Threshold set from your own numbers
- [x] LED checked with `raw` near the threshold
- [x] TODO 2 filled in; the RGB LED glows blue when dark
- [x] TODO 3 filled in; the colours change when dark

**Why two thresholds? What would `is_dark = raw > DARK_THRESHOLD;` do in step 5?**

> _Answer:_
>Any small sensor noise around 700 could repeatedly switch the LED on and off. raw > 700: dark, LED on
raw <= 700: light, LED off

**Between the two thresholds, what does the LED do?**

> _Answer:_
>Between 650 and 750, is_dark keeps its previous value.

**The ADC has several inputs. Which line picks the sensor's?**

> _Answer:_
>adc_select_input(LIGHT_ADC_INPUT);

**Attached file(s):**

> _Filename:_
>

---

## Exercise 3: Macros vs. `constexpr`

**Goal:** See what the preprocessor does. Then use it only where it helps.

The preprocessor runs before the compiler. It only swaps text. `#define LED_PIN 7` swaps
every `LED_PIN` for `7`.

Beginning C++17 says: no `#define` constants. They have no type and no scope.
Use `constexpr` for constants instead.

`#if` is different. It picks which lines get compiled. The other lines are deleted first.

### Instructions

1. Create a project `macros`. Copy in [`code/macros.cpp`](code/macros.cpp). Add
   `hardware_adc` and `pico_cyw43_arch_none` to `target_link_libraries`.
2. Read the three switches at the top. They pick which code gets compiled.
3. Build and run. Turn the pot past halfway. The Pico W's own LED lights up.
4. Fill in TODO 1. Write the constants like earlier sessions: `constexpr uint LED_PIN {7};`
   Rebuild. Nothing should change.
5. Look at what `DOUBLE(3 + 4)` printed. It is printed once, above the `[DEBUG]` lines, so
   scroll up. Is it 14?
6. Fill in TODO 2. Define the following constexpr function:
   `constexpr int double_value(int x)`. Delete `DOUBLE` and print `double_value(3 + 4)`.
7. Set `USE_BUILTIN_LED` to `0`. Fill in both TODO 3s. Now the red LED on GP7 reacts.
8. In `led_set()`, turn `#if USE_BUILTIN_LED`, `#else` and `#endif` into a normal
   `if (USE_BUILTIN_LED)` and `else`, with the same two lines inside. Build with
   `USE_BUILTIN_LED` still `0`. Read the error, then undo.
9. Set `EXERCISE` to `2`. Set the `THRESHOLD` to the value from Exercise 2. Cover the
   sensor: the LED lights.
10. Set `EXERCISE` to `3`. Build and read the **first** error. The errors after it follow
    from it.
11. Delete the `#define EXERCISE` line. Build and read the first error again. Then put it
    back.
12. Put `//` in front of `#define DEBUG_MODE`. Rebuild. The `[DEBUG]` lines are gone.

### Checklist

- [x] TODO 1 and 2 filled in; `double_value(3 + 4)` prints 14
- [x] TODO 3 filled in; the GP7 LED works
- [x] Plain `if` error read (step 8)
- [x] `EXERCISE` set to 2, 3 and deleted
- [x] `DEBUG_MODE` turned off

**What did `DOUBLE(3 + 4)` print? Write the text the preprocessor made.**

> _Answer:_
>11, because in DOUBLE(3+4), double got substituted by *2, so it became 3+4*2, which is 11. 

**Why does `double_value(3 + 4)` give 14?**

> _Answer:_
> Because double_value is a function, not a macro, C evaluates the argument first. 

**Say you had kept `#define LED_PIN 7`. What would `int LED_PIN {5};` inside a function
turn into? Why is that a problem?**

> _Answer:_
>During compile time the preprocessor would get all Macros replaced in the code, so int LED_PIN {5}; would turn into int 7 {5}; and this is invalid sintax.

**What was the error in step 8? Why does `#if` avoid it?**

> _Answer:_
>That cyw43_arch_gpio_put(CYW43_WL_GPIO_LED_PIN, on); is not initialized. The function and CYW43_WL_GPIO_LED_PIN were only available inside: #if USE_BUILTIN_LED
#include "pico/cyw43_arch.h"
#endif. Using #if avoids the error by excluding the built-in LED code entirely when the feature is disabled.   

**You deleted `#define EXERCISE`. Which error came first? Why?**

> _Answer:_
> That exercise should be 1 or 2. Because an undefined macro is treated as 0, so the condition becomes true: #if 0 != 1 && 0 != 2. 

**`DEBUG_MODE` is off. Where did the printing code go?**

> _Answer:_
>When DEBUG_MODE is off, it is treated as 0. Any printing code inside: #if DEBUG_MODE
    std::cout << "debug information" << std::endl;
#endif. is removed by the preprocessor before compilation. So there is no printing code.  

**Attached file(s):**

> _Filename:_
>

*Read more (optional): Beginning C++17, Chapter 10 ("Defining Preprocessor Macros",
"Logical Preprocessing Directives"). Real-Time C++, Sect. 1.11 ("Compile-Time Constant")
and 3.8 ("Generalized Constant Expressions with constexpr").*

Exercises 4 and 5 continue in [`homework.md`](homework.md).

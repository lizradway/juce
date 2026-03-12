
# JUCE Gain & Pitch Shift Audio Plugin

A simple audio plugin built with the **JUCE framework** that applies **gain control** and **real-time pitch shifting** to incoming audio.
The plugin includes a minimal graphical interface with sliders for adjusting volume and pitch.

This project demonstrates the basic structure of a JUCE plugin, including:

* Audio processing (`AudioProcessor`)
* Graphical user interface (`AudioProcessorEditor`)
* Real-time DSP inside `processBlock`

---

# Features

### 🎚 Gain Control

Adjust the output volume of the audio signal using a vertical slider.

Range:

```
0.0 → 1.0
```

The gain is applied directly to the incoming audio buffer.

---

### 🎵 Pitch Shifting

The plugin can shift the pitch of incoming audio up or down.

Range:

```
-12 semitones → +12 semitones
```

Examples:

| Pitch | Effect           |
| ----- | ---------------- |
| +12   | One octave up    |
| +7    | Perfect fifth up |
| -12   | One octave down  |

The pitch shifting is implemented using a **simple resampling method with linear interpolation**.

---

# How It Works

The plugin processes audio in blocks using JUCE’s `processBlock()` function.

Processing steps:

```
Incoming Audio
      ↓
Apply Gain
      ↓
Resample Audio (Pitch Shift)
      ↓
Output Audio
```

Pitch shifting is achieved by computing a **pitch ratio**:

```
pitchRatio = 2^(semitones / 12)
```

For example:

```
+12 semitones → pitchRatio = 2
```

The algorithm then reads samples from earlier positions in the audio buffer and interpolates between them to generate the shifted pitch.

---

# Graphical Interface

The plugin editor contains two vertical sliders:

| Slider | Function                  |
| ------ | ------------------------- |
| Gain   | Controls output volume    |
| Pitch  | Shifts pitch in semitones |

When a slider is moved, the GUI sends the updated value to the audio processor.

Example:

```
slider → audioProcessor.mGain
slider → audioProcessor.mPitch
```

These parameters are then used inside the audio processing function.

---

# Project Structure

```
JUCE-PitchShift-Plugin
│
├── PluginProcessor.h
├── PluginProcessor.cpp
│     Core audio processing code
│
├── PluginEditor.h
├── PluginEditor.cpp
│     Graphical interface (sliders)
│
└── README.md
```

### PluginProcessor

Handles:

* audio input/output
* DSP processing
* gain and pitch calculations

### PluginEditor

Handles:

* GUI layout
* slider controls
* user interaction

---

# Building the Plugin

This project requires the **JUCE framework**.

Steps:

1. Install JUCE.
2. Open the project in **Projucer** or your IDE.
3. Build the project for your target format (VST3, AU, etc.).

Supported plugin formats depend on your JUCE configuration.

---

# Running the Plugin

1. Build the plugin.
2. Load it into a Digital Audio Workstation (DAW), such as:

* Ableton Live
* Logic Pro
* Reaper
* FL Studio

3. Insert the plugin on an audio track.
4. Adjust the sliders to change the gain and pitch of the audio signal.


# License

This project is intended for **educational and experimental use**.
Feel free to modify and extend it.

# ESP32-ESP-IDF-start

Starting point for ESP32 projects based on ESP-IDF (FreeRTOS), WiFi, NTP and MQTT.

## Motivation

Provide a foundation for future projects that run on an ESP32 using the ESP-IDF platform (which includes Espressif's version of FreeRTOS), WiFi access, NTP time keeping and an MQTT client. Many of my projects start with this combination. 

This combination is proving to be a bit more difficult to get going than some of the Arduino examples but should prove more useful in the long run. Or not.

## Process

Development will be using PlatformIO driven by VS Code. There are ready made examples that share a lot of code in `connect.c` (and perhaps other files) and it will be my task to extract what is needed for this specific project. General steps will include

1. Copy the files from `.../examples/get-started/sample_project` to this repo and build (except the `README.md)`. (`blink` and `hello_world` projects in the same directory may be useful references as well.)
1. Open with PlatformIO. No Joy. Wants a `platformio.ini`.
1. Create with PlatformIO. Still not so good. Created the inside the git directory. I guess I can merge my `README.md` into the PlatformIO project, destroy the Guitrhub project and then create a bare gitbub project and import Platform IO project.
1. Abandon this and start from scratch.

1. Create bare Github project.
1. Create PlatformIO project with same name.
1. Follow instructions from Github bare project redirect to import the project into Github.
1. project builds, ready to roll!

Given a buildable project...

1. Add a (FreeRTOS) task to blink an LED. Always fun to blink an LED and can be used as an indicator later.
1. Associate with a WiFi AP and identify by host name.
1. Add MQTT client to publish messages.
1. Add NTP client so we know time. (Does anyboey really know what time it is? - CTA)

## Errata

The sample project was pretty much abandoned. I should read the link below from "How to use example"

### From the sample project README

(See the README.md file in the upper level 'examples' directory for more information about examples.)

This is the simplest buildable example. The example is used by command `idf.py create-project`
that copies the project to user specified path and set it's name. For more information follow the [docs page](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project)



## How to use example

We encourage the users to use the example as a template for the new projects.
A recommended way is to follow the instructions on a [docs page](https://docs.espressif.com/projects/esp-idf/en/latest/api-guides/build-system.html#start-a-new-project).

## Example folder contents

The project **sample_project** contains one source file in C language [main.c](main/main.c). The file is located in folder [main](main).

ESP-IDF projects are built using CMake. The project build configuration is contained in `CMakeLists.txt`
files that provide set of directives and instructions describing the project's source files and targets
(executable, library, or both). 

Below is short explanation of remaining files in the project folder.

```
├── CMakeLists.txt
├── main
│   ├── CMakeLists.txt
│   └── main.c
└── README.md                  This is the file you are currently reading
```
Additionally, the sample project contains Makefile and component.mk files, used for the legacy Make based build system. 
They are not used or needed when building with CMake and idf.py.

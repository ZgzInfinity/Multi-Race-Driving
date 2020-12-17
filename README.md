&nbsp;

<p align="center">
    <img src="https://i.ibb.co/bbHSK8h/logo.png" alt="Logo" width=200 height=200>
  </a>
</p>

![State](https://img.shields.io/badge/Context-Up%20to%20date-%20%2329f305)
[![License: GPL v3](https://img.shields.io/badge/License-GPLv3-blue.svg)](https://www.gnu.org/licenses/gpl-3.0) 
[![windows](https://img.shields.io/badge/Windows%20-compatible-f305b2.svg)](https://www.microsoft.com/es-es/windows) 
[![Version](https://img.shields.io/badge/Version%20-1.0-0fd5f9.svg)](https://github.com/ZgzInfinity/Multi-Race-Driving/releases)
![made-with-C++](https://img.shields.io/badge/Made%20with-C++-600ff9.svg)
[![SFML](https://img.shields.io/badge/Requeriment%20-SFML-f9720f.svg)](https://www.sfml-dev.org/)

![GitHub All Releases](https://img.shields.io/github/downloads/ZgzInfinity/Multi-Race-Driving/total?color=%20%23f34605&label=Release%20downloads&logoColor=%20)
[![Github Stars](https://img.shields.io/github/stars/ZgzInfinity/Multi-Race-Driving?logo=github)](https://github.com/ZgzInfinity/Multi-Race-Driving/stargazers)
[![Github forks](https://img.shields.io/github/forks/ZgzInfinity/Multi-Race-Driving?logo=github)](https://github.com/ZgzInfinity/Multi-Race-Driving/network/members)

&nbsp;

# General description

_**Multi Race Driving**_ is a general and customized platform for racing games with 2.5D graphics. This platform has been designed using **C++** as a high-level programming language, and **SFML**, a simple interface for various components of your PC, to ease the development of games and multimedia applications. 

&nbsp;

<p align="center">
  <img src="https://i.ibb.co/p21Ch8N/portada.png">
</p>

&nbsp;

## 1. Getting started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. See deployment for notes on how to deploy the project on a live system.

### Prerequisites

To run successfully _**Multi Race Driving**_, you must comply the following requeriments:

* A version of **Windows** with 64-bit architecture.
* If you want to run it in **MAC** or **Linux**, currently you have to have installed **WineHq 5**.
* Download **SFML** and **RapidXML** from the links provided previously.
* Install **MinGW** in your computer to compile and run the code.

&nbsp;

### Compilation

In order to compile the code you have to do the following instructions:

* Clone or download this repository with all its content.
* Open Codeblocks and create a C++ project in the same folder of the repository. 
* Add all the the source (.cc and .cpp) and interface (.h) files provided in the repository.
* Configure SFML in Codeblocks like it is indicated in the following [tutorial](https://www.sfml-dev.org/tutorials/2.1/start-cb.php).
* Add all the _.dll_ files with option _-d_ of SFML in the Debug folder for run the project in Debug mode. If you want to run the code project in Release mode you have to add the _.dll_ files without _-d_ option to the Release folder of the project. This step must be done only if you choose dinamic compilation of the libraries. If you choose static compilation, which is explained in the tutorial too, please omit this step.

&nbsp;

### Execution

In order to execute _**Multi Race Driving**_, you can do any of the following options:

* Execute the .exe file generated when you compile the project in your computer.
* Download the executable file provided in the Release section of the repository. This executable has been linked statically with both **MinGW** and **SFML** dependencies, so you don´t have to install anything.

&nbsp;

## 2. Software used

To carry out the development of _**Multi Race Driving**_ the following software has been used:

* The IDE for C++ programming [Codeblocks](http://www.codeblocks.org/), version 17.12.
* The API of [SFML](https://www.sfml-dev.org/download.php), version 2.5.1.
* The XML parser library [RapidXML](http://rapidxml.sourceforge.net/).
* [Boreas](https://github.com/aeri/Boreas), a C++ implementation of the Linda framework under **GPL-3.0 License**.

&nbsp;

## 3. Outstanding features

This new the following features with respect to the original versions:

* Multiple game modes for one player.
* Multiplayer online mode.
* Different types of vehicles available, customizabled and with many colors.
* Realistic and spectacular graphics in 2.5D.
* Realistic physics (speed, braking, collision, inertia).
* Customizable menus (fonts, colors, images, texts).
* Compatible with many screen resolutions.
* Graphics available in HD and in pixel art. quality.
* Fantastic soundtracks and SFX fully customizable.
* Various difficulty levels.
* Numerous types of artificial intelligence integrated.
* Configuration of the controllers customizable.
* Completely new scenarios available and customizable.

&nbsp;

## 4. Controllers

These are the default controllers of the simulator, but you can change them whenever you want:

* Acceleration: Left Control.
* Braking: Left Alt.
* Turning left: Left arrow of the cursor.
* Turning right: Right arrow of the cursor.
* Select an option: Enter.
* Change the soundtrack which is been sounding during the game: Z.
* Exit the game during the navigation in the interface, pause the game while the player is driving: Esc.

&nbsp;

## 4. Author

* [ZgzInfinity](https://github.com/ZgzInfinity)

&nbsp;

## 5. License

Code is released under the GNU General Public License v3.0.

&nbsp;

## 6. Supporting the project

This is the first version of the video game. I have tested it as best as I could but I'm absolutely aware that some fault may have due to its
complexity, especially in multiplayer mode. The fact that the project is open source is the real way for the community to solve all the possible 
problems together, feel free to open an issue or do a pull request. See the open issues for a list of known issues (and proposed features).

&nbsp;


## 7. Documentation

Please, go to the [Wiki](https://github.com/ZgzInfinity/Multi-Race-Driving/wiki/World-Tour) in order to be able to see the more details about what _**Multi Race Driving**_ can offer to you.

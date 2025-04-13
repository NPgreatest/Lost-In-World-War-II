# Lost In World War II

A C++ and Qt-based remake and expansion of the classic “Tank Battle” game. This project adds new features such as **rich storytelling**, **multiple skill systems**, and even **LAN multiplayer** functionality, all powered by **Qt** and **OpenGL**. Inspired by childhood memories of tank-battle games on older consoles, the goal of this project is to showcase robust C++/Qt programming skills while preserving the retro charm of the original.

> This README is based on design documentation found in the original project specification. 

## ![image-20250413034340253](picture/image-20250413034340253.png)Table of Contents

- [Project Overview](#project-overview)
- [Core Features](#core-features)
- [Game Modes](#game-modes)
- [Technology Stack](#technology-stack)
- [Installation](#installation)
- [Basic Usage](#basic-usage)
- [Demonstration Images](#demonstration-images)
- [Roadmap](#roadmap)
- [Contribution](#contribution)
- [License](#license)
- [Chinese Version](#chinese-version)

---

## Project Overview

**Lost In World War II** is a passion project designed to reimagine the classic Tank Battle game with expanded gameplay mechanics and higher-quality visuals. In addition to the nostalgic top-down tank combat, the game introduces:

- **Story Mode**: Featuring short cutscenes to explain the backstory.
- **Skills and Power-Ups**: Several new weapons and abilities for more strategic battles.
- **Local Network (LAN) Multiplayer**: Team up or battle each other on the same local network.
- **Level Editor**: Easily create and edit your own maps.

Developed primarily in C++ using Qt and OpenGL, the game offers a window into deeper, lower-level programming concepts—such as collision detection, AI movement, and networked data synchronization—while still retaining a simple and accessible retro feel.

---

## Core Features

1. **Story and Battle Modes**  
   - **Story Mode**: Follow a sequence of maps and short narrative cutscenes.  
   - **Battle Mode**: Survive or destroy waves of enemies in a more traditional tank-battle setting.

2. **Three Primary Weapons**  
   - **Main Cannon**: Standard tank shells.  
   - **Shotgun / Scatter Shot**: Fires several projectiles in an arc.  
   - **Flamethrower**: A short-range but high-damage, continuous attack.

3. **Power-Ups and Items**  
   - **Medkits** of varying strength.  
   - **Weapon Boxes** that expand ammo or upgrade certain attacks.  
   - **Environmental Hazards** such as ice, traps, and debris.

4. **AI-Driven Enemies**  
   - Enemies come in various tiers with different movement and firing patterns.  
   - Some enemies feature **rudimentary AI** to seek out or avoid the player.

5. **Local Network Multiplayer**  
   - Based on Qt’s `QUdpSocket` broadcast functionality.  
   - Multiple PCs can connect to a single game session on the same LAN.  
   - Cooperative or adversarial modes are possible.

6. **Level Editor**  
   - Create and customize your own maps.  
   - Save your designs to text files and share with friends.

---

## Game Modes

1. **Story Mode**  
   - Includes pre-level dialogue and cutscenes.  
   - Progressively more difficult maps culminating in a boss fight.

2. **Battle / Arcade Mode**  
   - Inspired by classic Tank Battle gameplay.  
   - Unlimited or wave-based system with no story interruptions.

3. **LAN Multiplayer Mode**  
   - Host or join a local server.  
   - Synchronize enemy positions, bullets, and item spawns over the network.

---

## Technology Stack

- **Language**: C++ (Object-Oriented Programming, data structures)
- **Framework**: [Qt 5.14.2](https://www.qt.io/) for GUI and network capabilities
- **Graphics**: OpenGL for optimized rendering within the Qt environment
- **Development Environment**:
  - **qmake** for build configuration
  - **Visual Studio** / **Qt Creator** for coding and debugging
- **Art and Audio Tools**:
  - Adobe Photoshop CC 2019 (sprite design)
  - Format Factory (audio formatting)
  - Additional free assets from [kenney.nl](https://kenney.nl/assets), [game-icons.net](https://game-icons.net/), and [craftpix.net](https://craftpix.net/)

---

## Installation

1. **Download the Executable**  
   You can download the latest release from the [GitHub Releases](https://github.com/NPgreatest/Lost-In-World-War-II/releases) section. Look for the file named `Lost-In-World-War-II.exe` (or the corresponding installer).

2. **Run the Installer**  
   - Double-click the installer.  
   - Choose your preferred language (e.g., English).  
   - Follow the on-screen instructions and click “Install.”

3. **Launch the Game**  
   - Check the box to “Launch Lost-In-World-War-II” at the end of the installation.  
   - A desktop shortcut icon should be created.  
   - Click **Finish** to start playing right away.

---

## Basic Usage

1. **Single Player**  
   - Launch the game and select your preferred mode (Story or Battle).  
   - Use keyboard arrows or **WASD** (configurable in Settings) to move.  
   - Mouse clicks or keyboard keys trigger special attacks like the flamethrower and shotgun.

2. **LAN Multiplayer**  
   - One player hosts the game (server).  
   - Other players select “Join Game” and input the host’s IP or auto-discover on the local network.  
   - Once connected, all players can move, attack, and explore the map simultaneously.

3. **Creating/Editing Maps**  
   - From the main menu, choose **Map Editor** to build or modify your maps.  
   - Place various terrain types (ice, traps, walls) and items (power-ups).  
   - Save your new map for use in the main game or to share with friends.

---

## Demonstration Images

Below are some representative screenshots of **Lost In World War II**. (These are sample placeholders—replace with your actual images or GIFs.)

1. **Main Menu**  
   ![Main Menu Screenshot](docs/images/demo_main_menu.png)

2. **Battle Scene**  
   ![Battle Scene Screenshot](docs/images/demo_battle.png)

3. **Map Editor**  
   ![Map Editor Screenshot](docs/images/demo_editor.png)

---

## Roadmap

- **Short Term**  
  - Fix any remaining bugs in the LAN multiplayer feature.  
  - Improve AI pathfinding for larger, more complex maps.

- **Long Term**  
  - Potential migration to a dedicated game engine like Unreal Engine or Unity for advanced features.  
  - Online (non-LAN) multiplayer support.  
  - Additional story elements and extended cutscenes.  
  - Polishing visuals with custom shaders for modern GPU effects.

---

## Contribution

Contributions are always welcome! Feel free to:

- Fork the repository on [GitHub](https://github.com/NPgreatest/Lost-In-World-War-II)
- Submit pull requests for new features, bug fixes, or performance improvements
- Raise issues for discussion or to report bugs

If you have ideas for new maps, you can share your custom `.txt` files for others to enjoy.

---

## License

This project is intended for **educational and personal use**. Please check the repository for any specific license details or third-party asset attributions.

---

## Chinese Version

For the **Chinese** version of this README, please visit:
[**README_zh.md**](./README_zh.md)

---

Thanks for checking out **Lost In World War II**! We hope you enjoy the blend of old-school nostalgia and modern C++/Qt development. If you have any questions or suggestions, please open an issue on GitHub or reach out to the maintainers.

---

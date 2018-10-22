# Network-audio
Tizen IoT Application, Network-audio

## Overview
This project is consisted of as follows:
- SmartThings application: this is based on network audio sample built-in tizen studio
- SmartThinsgs device plugin: this is based on network audio device plugin sample in the github below.
    + merged with networkaudio sample https://github.com/Samsung/SmartThings.git
    + commit id: e1d5a114564d1c68db3d1b059d1042f655b504ac
- This project does not contain project related files.

## Project Folder Structure

- SmartThings application: this is for tizen studio
  + inc (header files)
  + lib (sdk libraries that is created by tizen studio)
  + res (resource files: mp3 or wav)
  + shared
  + src (capabilities and smartThings)
- SmartThinsgs device plugin: this is for atom smartThings sdk packages
  + plugin
    + plugin
      + js (javascripts for capabilities)
      + res (resource files: images)
      + css (style sheets)

## How to build

- SmartThings appliation
  1. create tizen project using tizen studio
  2. merge this project with newly created tizen project
  3. build
  4. run

- SmartThings device plugin
  1. create smartThings project using ATOM smartThings packages
  2. merge this project with newly created ATOM smartThings project
  3. install target or virtual device

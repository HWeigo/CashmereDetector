# CashmereDetector
This is a software for fiber classification. The classification process uses a combination of image pre-processor and ResNet-101 module. 
Our algorithm reaches 91.8% accuracy on test sets over 7 different fibers, which far exceeds the accuracy of using ResNet(70.6%) or YOLOv5(77.2%) models directly. 

<img src="https://github.com/HWeigo/CashmereDetector/blob/main/img/process.png"/>

---
## GUI
<img width="600" height="420" src="https://github.com/HWeigo/CashmereDetector/blob/main/img/gui.png"/>

## Dependencies
* VS2017 (or higher version)
* Qt5.9.9 (or any other version)
* LibTorch 1.11.0 - CPU 
* OpenCV 4.1.1
* OpenMP (already builted in VS)
* Halcon (Note: pre-processor without Halcon is also provided)

## Changelog
### 2022-04-03
* upgrade to VS2017 platform (compile error when LibTorch on VS2015)

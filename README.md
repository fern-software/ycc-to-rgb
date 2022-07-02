# ycc-to-rgb

## Usage
Since reading JPG files in C is quite involved and is out of scope for this project, simpler input
files are expected by the program. The program ycc2rgb expects a binary file as a command line
argument where each group of nth group of 3 bytes represents the Y, Cb and Cr values for the nth
pixel. The values are listed from left to right and top to bottom. Sample binary files and their
corresponding jpgs can be found in /testimages. 

## Creating Test Data
YCC values can be extracted from a JPG using
[ImageMagick](https://imagemagick.org/) using the commands below.

```convert image.jpg YCbCr:image.bin```

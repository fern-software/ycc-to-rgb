# ycc-to-rgb
SENG 440 Final project by Owen Jaques and Finn Morin. This project aims to explore the world of
embedded programming through an implementation of a colour space conversion algorithm.
Specifically, a YCbCr to RGB algorithm will be implemented, then optimized.

## Building
To compile ensure that cmake is installed on your system then run `cmake <path to root directory>`.
This will generate all the build files required for the project. Then run `cmake --build .` to
build the program. This will generate an executable called `ycc2rgb` and one called `rgb2ycc`.

## Usage
All interaction with this project is done using the executables `ycc2rgb` and `rgb2ycc`. 

### ycc2rgb
Running the program will generate an RGB image from the given YCbCr file. It expects the name of a
YCbCr input file followed by the desired name of the RGB output file as command line parameters.

### rgb2ycc
This program in un-optimized and was created solely to generate test files for `ycc2rgb`. Running
it will generate a YCbCr image from the given RGB file. It expects the name of an RGB input file
followed by the desired name of the YCbCr output file as command line parameters.

## File formats
The RGB and YCbCr file formats expected by both programs is described below.

### YCbCr file format
Since reading JPG files in C is quite involved and is out of scope for this project, simpler YCbCr
files are used by the programs. They are always represented as having four Y values per Cb and Cr
value (4:2:0 format).

#### Header
The header of every YCbCr file used by these programs must always follow this format. The files are
written in binary so reading them must be done with a hex editor.

```
YCbCr
<image width> <image height>
```

#### Data
After the header there is exactly one newline followed by the data for the image. The pixels are
stored in chunks of four Y values grouped with one pair of Cb and Cr values. These chunks are then
stored in row-major order. The data for the chunks is stored as consecutive bytes in the following
order.

1. Top left Y value
2. Top right Y value
3. Bottom left Y value
4. Bottom right Y value
5. Cb value
6. Cr value

### RGB File Format
All RGB files used by the program must be given in binary PPM format. This format was chosen as it
allows the program to easily read/write RGB values from/to a file.

# ycc-to-rgb
SENG 440 Final project by Owen Jaques and Finn Morin. This project aims to explore the world of
embedded programming through an implementation of a colour space conversion algorithm. Specifically,
a YCC to RGB algorithm will be implemented, then optimized.

## Building
To compile ensure that cmake is installed on your system then run `cmake <path to root directory>`.
This will generate all the build files required for the project. Then run `cmake --build .` to
build the program. This will generate an executable called `ycc2rgb`.

## Usage
All interaction with the program is done using the executable `ycc2rgb`. It expects the name of a
YCC input file in the format specified below followed by the desired name of the output file which
will be given in the format specified below.

### Input Files
Since reading JPG files in C is quite involved and is out of scope for this project, simpler input
files are expected by the program. The program ycc2rgb expects a binary file as a command line
argument where each group of nth group of 3 bytes represents the Y, Cb and Cr values for the nth
pixel. The values are listed from left to right and top to bottom. Sample binary files and their
corresponding jpgs can be found in [/testimages](/testimages). 

#### Creating Input Files
YCC values can be extracted from a JPG using [ImageMagick](https://imagemagick.org/)
with the following command `convert image.jpg YCbCr:image.bin`.

### Output Files
All output files of the program will be given in PPM format. This format was chosen as it allows
the program to easily write RGB values to a file.

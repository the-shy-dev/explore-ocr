# explore-ocr

Prerequisites
```bash
# Reference: https://tesseract-ocr.github.io/tessdoc/Compiling.html#linux
sudo apt install tesseract-ocr
sudo apt install libtesseract-dev

sudo apt-get install g++ # or clang++ (presumably)
sudo apt-get install autoconf automake libtool
sudo apt-get install pkg-config
sudo apt-get install libpng-dev
sudo apt-get install libjpeg8-dev
sudo apt-get install libtiff5-dev
sudo apt-get install zlib1g-dev
sudo apt-get install libwebpdemux2 libwebp-dev
sudo apt-get install libopenjp2-7-dev
sudo apt-get install libgif-dev
sudo apt-get install libarchive-dev libcurl4-openssl-dev

sudo apt-get install libleptonica-dev
```

```bash
# Create a build directory and navigate into it
mkdir build
cd build

# Generate the build system files
cmake ..

# Build the project
cmake --build ..

# Run the executable with an image file as an argument
./BasicDemo path/to/your/image.png
```
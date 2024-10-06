/**
 * @file rtw_stb_image.hpp
 * @author Bogdan Ciurea (ciureabogdanalexandru@gmail.com)
 * @brief Declaration of the stb_image class
 * Copied from
 * https://raytracing.github.io/books/RayTracingTheNextWeek.html#texturemapping/accessingtextureimagedata
 * @version 0.1
 * @date 2024-10-06
 *
 * @copyright Copyright (c) 2024
 *
 */

#ifndef RTW_STB_IMAGE_H
#define RTW_STB_IMAGE_H

// Disable strict warnings for this header from the Microsoft Visual C++
// compiler.
#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#define STB_IMAGE_IMPLEMENTATION
#define STBI_FAILURE_USERMSG
#include <cstdlib>
#include <iostream>

#include "utils.hpp"

class rtw_image {
 public:
  rtw_image() {}

  rtw_image(const char *image_filename) {
    // Loads image data from the specified file. If the RTW_IMAGES environment
    // variable is defined, looks only in that directory for the image file. If
    // the image was not found, searches for the specified image file first from
    // the current directory, then in the images/ subdirectory, then the
    // _parent's_ images/ subdirectory, and then _that_ parent, on so on, for
    // six levels up. If the image was not loaded successfully, width() and
    // height() will return 0.

    auto filename = std::string(image_filename);
    auto imagedir = getenv("RTW_IMAGES");

    TraceLog(LOG_DEBUG, "Attempting to load image: %s", image_filename);

    if (imagedir) {
      std::string path = std::string(imagedir) + "/" + image_filename;
      TraceLog(LOG_ALL, "Trying path from RTW_IMAGES: %s", path.c_str());
      if (load(path)) return;
    }

    TraceLog(LOG_ALL, "Trying current directory: %s", filename.c_str());
    if (load(filename)) return;

    const char *dirs[] = {"images/",
                          "../images/",
                          "../../images/",
                          "../../../images/",
                          "../../../../images/",
                          "../../../../../images/",
                          "../../../../../../images/"};

    for (const auto &dir : dirs) {
      std::string path = dir + filename;
      if (load(path)) return;
    }

    TraceLog(LOG_ERROR, "Could not load image file '%s' from any location",
             image_filename);
  }

  ~rtw_image() {
    delete[] bdata;
    free(fdata);
  }

  bool load(const std::string &filename) {
    // Loads the linear (gamma=1) image data from the given file name. Returns
    // true if the load succeeded. The resulting data buffer contains the three
    // [0.0, 1.0] floating-point values for the first pixel (red, then green,
    // then blue). Pixels are contiguous, going left to right for the width of
    // the image, followed by the next row below, for the full height of the
    // image.

    TraceLog(LOG_DEBUG, "Attempting to load file: %s", filename.c_str());

    // Check if file exists and log its size
    FILE *file = fopen(filename.c_str(), "rb");
    if (!file) {
      TraceLog(LOG_ERROR, "File not found: %s", filename.c_str());
      return false;
    }

    fseek(file, 0, SEEK_END);
    long fileSize = ftell(file);
    fseek(file, 0, SEEK_SET);

    TraceLog(LOG_ALL, "File size: %ld bytes", fileSize);

    // Read and log the first few bytes of the file
    unsigned char header[8];
    size_t bytesRead = fread(header, 1, sizeof(header), file);
    fclose(file);

    TraceLog(LOG_ALL,
             "First %zu bytes: %02X %02X %02X %02X %02X %02X %02X %02X",
             bytesRead, header[0], header[1], header[2], header[3], header[4],
             header[5], header[6], header[7]);

    auto n = bytes_per_pixel;
    fdata = stbi_loadf(filename.c_str(), &image_width, &image_height, &n,
                       bytes_per_pixel);

    if (fdata == nullptr) {
      TraceLog(LOG_ERROR, "Failed to load image: %s. Reason: %s",
               filename.c_str(), stbi_failure_reason());
      return false;
    }

    TraceLog(LOG_INFO,
             "Successfully loaded image file '%s' (%d x %d, %d components)",
             filename.c_str(), image_width, image_height, n);

    bytes_per_scanline = image_width * bytes_per_pixel;
    convert_to_bytes();
    return true;
  }

  int width() const { return (fdata == nullptr) ? 0 : image_width; }
  int height() const { return (fdata == nullptr) ? 0 : image_height; }

  const unsigned char *pixel_data(int x, int y) const {
    // Return the address of the three RGB bytes of the pixel at x,y. If there
    // is no image data, returns magenta.
    static unsigned char magenta[] = {255, 0, 255};
    if (bdata == nullptr) return magenta;

    x = clamp(x, 0, image_width);
    y = clamp(y, 0, image_height);

    return bdata + y * bytes_per_scanline + x * bytes_per_pixel;
  }

 private:
  const int bytes_per_pixel = 3;
  float *fdata = nullptr;          // Linear floating point pixel data
  unsigned char *bdata = nullptr;  // Linear 8-bit pixel data
  int image_width = 0;             // Loaded image width
  int image_height = 0;            // Loaded image height
  int bytes_per_scanline = 0;

  static int clamp(int x, int low, int high) {
    // Return the value clamped to the range [low, high).
    if (x < low) return low;
    if (x < high) return x;
    return high - 1;
  }

  static unsigned char float_to_byte(float value) {
    if (value <= 0.0) return 0;
    if (1.0 <= value) return 255;
    return static_cast<unsigned char>(256.0 * value);
  }

  void convert_to_bytes() {
    // Convert the linear floating point pixel data to bytes, storing the
    // resulting byte data in the `bdata` member.

    int total_bytes = image_width * image_height * bytes_per_pixel;
    bdata = new unsigned char[total_bytes];

    // Iterate through all pixel components, converting from [0.0, 1.0] float
    // values to unsigned [0, 255] byte values.

    auto *bptr = bdata;
    auto *fptr = fdata;
    for (auto i = 0; i < total_bytes; i++, fptr++, bptr++)
      *bptr = float_to_byte(*fptr);
  }
};

// Restore MSVC compiler warnings
#ifdef _MSC_VER
#pragma warning(pop)
#endif

#endif

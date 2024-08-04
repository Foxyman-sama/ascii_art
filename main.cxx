#include <SFML/Graphics.hpp>
#include <array>
#include <fstream>
#include <iostream>
#include <vector>

constexpr std::array<char, 10> ascii { '.', ',', ':', '+', '*', '?', '%', 'S', '#', '@' };

void convert_to_grayscale(sf::Image &image);
std::vector<std::vector<char>> convert(sf::Image &image);

double map(double value_to_map, double start1, double stop1, double start2, double stop2) {
  return (value_to_map - start1) / (stop1 - start1) * (stop2 - start2) + start2;
}

int main() {
  std::string image_path;
  std::cin >> image_path;

  sf::Image image;
  if (!image.loadFromFile(image_path)) {
    std::terminate();
  }

  convert_to_grayscale(image);

  const auto converted { convert(image) };

  std::ofstream fout { "result.txt" };
  for (auto row : converted) {
    for (auto ch : row) {
      fout.put(ch);
    }

    fout.put('\n');
  }
}

void convert_to_grayscale(sf::Image &image) {
  for (auto y { 0 }; y < image.getSize().y; ++y) {
    for (auto x { 0 }; x < image.getSize().x; ++x) {
      auto pixel { image.getPixel(x, y) };
      sf::Uint8 avg { (pixel.r + pixel.g + pixel.b) / 3 };
      image.setPixel(x, y, { avg, avg, avg, pixel.a });
    }
  }
}

std::vector<std::vector<char>> convert(sf::Image &image) {
  const auto width { image.getSize().x };
  const auto height { image.getSize().y };

  std::vector<std::vector<char>> result;
  result.resize(height);

  for (auto y { 0 }; y < height; ++y) {
    result[y].resize(width);
    for (auto x { 0 }; x < width; ++x) {
      auto r { image.getPixel(x, y).r };
      auto map_index { map(r, 0, 255, 0, ascii.size() - 1) };
      result[y][x] = ascii[map_index];
    }
  }

  return result;
}
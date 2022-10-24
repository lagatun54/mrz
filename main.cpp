#include <fstream>
#include <iostream>
#include <string>
#include "Cimg/Cimg.h"
#include "ImageCompressor.h"

int main() {
    int n;
    std::cout<< "выберите метод\n 2 - работа с результатом \n 1 - работа с нейронкой\n";
    std::cin >> n ;
    switch (n) {
        case 1: {
            std::string path;
            std::cout << "название файла\n";
            std::cin >> path;
            cimg_library::CImg<double> image(path.c_str());
            ImageCompressor imageCompressor(image);
            imageCompressor.setNetworkConfiguration();
            imageCompressor.imageToMatrix();
            imageCompressor.initializeWeights();
            imageCompressor.study();

            imageCompressor.putInResultCompressedImageMatrix();

            imageCompressor.matrixToImage();
            imageCompressor.showCompressedImage();
            imageCompressor.printCompressionRatio();
            break;
        }
        case 2:{
            std::string pathing;
            std::cout << "название файла\n";
            std::cin >> pathing;
            cimg_library::CImg<double> images(pathing.c_str());
            int W = images.width();
            int H = images.height();
            int m, n;
            std::cin >> m;
            std::cin >> n;
            double p[W][H];
            std::ifstream fout;
            std::string resulting = "result.txt";
            fout.open(resulting, std::ios::in | std::ios::out);
            std::vector<Matrix> result;
            for (int i = 0, q = 0; i < W; i += m) {
                for (int j = 0; j < H; j += n, q++) {
                    for (auto k = j, w = 0; k < j + n; k++) {
                        for (auto o = i; o < i + m; o++) {
                            for (auto t = 0; t < 3; t++, w++) {
                                fout >> p[i][j];
                                images(o, k, 0, t) = p[i][j];
                            }
                        }
                    }
                }
            }
            images.save("result.bmp");
    }
        case 3:{
            std::string pathDelta;
            std::cout << "название файла\n";
            std::cin >> pathDelta;
            cimg_library::CImg<double> imagesDelta(pathDelta.c_str());
            int Width = imagesDelta.width();
            int Height = imagesDelta.height();
            int m1,n1;
            std::cin >> m1;
            std::cin >> n1;
            double p1 [Width][Height];
            std::ifstream fouting;
            std::string resultDelta = "resultDeltaY.txt";
            fouting.open(resultDelta,std::ios::in | std::ios::out);
            std::vector<Matrix> resultDel;
            for (int i = 0, q = 0; i < Width; i += m1) {
                for (int j = 0; j < Height; j += n1, q++) {
                    for (auto k = j, w = 0; k < j + n1; k++) {
                        for (auto o = i; o < i + m1; o++) {
                            for (auto t = 0; t < 3; t++, w++) {
                                fouting >> p1[i][j];
                                imagesDelta(o, k, 0, t) = p1[i][j];
                            }
                        }
                    }
                }
            }
            imagesDelta.save("resultDeltaY.bmp");}


    }
}
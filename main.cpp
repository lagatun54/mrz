#include <fstream>
#include <iostream>
#include <string>
#include "Cimg/Cimg.h"
#include "ImageCompressor.h"

int main() {
    int n;
    std::cin >> n ;
    switch (n) {
        case 1:
        {
            std::string path = "image/test8.bmp";

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
        case 2:
            std::string pathing = "image/test8.bmp";

            cimg_library::CImg<double> images(pathing.c_str());
            int W = images.width();
            int H = images.height();
            int m,n;
            std::cin >> m;
            std::cin >> n;
            double p [W][H];
            std::ifstream fout;
            std::string resulting = "result.txt";
            fout.open(resulting,std::ios::in | std::ios::out);
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

	system("pause");
}
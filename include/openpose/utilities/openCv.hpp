#ifndef OPENPOSE_UTILITIES_OPEN_CV_HPP
#define OPENPOSE_UTILITIES_OPEN_CV_HPP

#include <opencv2/core/core.hpp> // cv::Mat
#include <opencv2/imgproc/imgproc.hpp> // cv::warpAffine, cv::BORDER_CONSTANT
#include <openpose/core/array.hpp>
#include <openpose/core/macros.hpp>
#include <openpose/core/point.hpp>

namespace op
{
    OP_API void putTextOnCvMat(cv::Mat& cvMat, const std::string& textToDisplay, const Point<int>& position, const cv::Scalar& color, const bool normalizeWidth);

    OP_API void floatPtrToUCharCvMat(cv::Mat& cvMat, const float* const floatImage, const Point<int>& resolutionSize, const int resolutionChannels);

    OP_API void unrollArrayToUCharCvMat(cv::Mat& cvMatResult, const Array<float>& array);

    OP_API void uCharCvMatToFloatPtr(float* floatImage, const cv::Mat& cvImage, const bool normalize);

    OP_API double resizeGetScaleFactor(const Point<int>& initialSize, const Point<int>& targetSize);

    OP_API cv::Mat resizeFixedAspectRatio(const cv::Mat& cvMat, const double scaleFactor, const Point<int>& targetSize, const int borderMode = cv::BORDER_CONSTANT,
                                          const cv::Scalar& borderValue = cv::Scalar{0,0,0});
}

#endif // OPENPOSE_UTILITIES_OPEN_CV_HPP

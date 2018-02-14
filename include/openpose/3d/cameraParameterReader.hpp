﻿#ifndef OPENPOSE_EXPERIMENTAL_3D_CAMERA_PARAMETER_READER_HPP
#define OPENPOSE_EXPERIMENTAL_3D_CAMERA_PARAMETER_READER_HPP

#include <opencv2/core/core.hpp>
#include <openpose/core/common.hpp>

namespace op
{
	OP_API const cv::Mat getIntrinsics(const int cameraIndex);

	OP_API const cv::Mat getDistorsion(const int cameraIndex);

	OP_API cv::Mat getM(const int cameraIndex);

	OP_API unsigned long long getNumberCameras();
}

#endif // OPENPOSE_EXPERIMENTAL_3D_CAMERA_PARAMETER_READER_HPP

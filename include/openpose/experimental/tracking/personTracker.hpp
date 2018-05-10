#ifndef OPENPOSE_TRACKING_PERSON_TRACKER_HPP
#define OPENPOSE_TRACKING_PERSON_TRACKER_HPP

#include <atomic>
#include <openpose/core/common.hpp>
#include <openpose/experimental/tracking/personTracker.hpp>

namespace op
{
    class OP_API PersonTracker
    {

    public:
        PersonTracker(const bool mergeResults);

        virtual ~PersonTracker();

        void track(Array<float>& poseKeypoints, Array<long long>& poseIds, const cv::Mat& cvMatInput);

        void trackLockThread(Array<float>& poseKeypoints, Array<long long>& poseIds, const cv::Mat& cvMatInput,
                             const long long frameId);

        bool getMergeResults() const;

    private:
        const bool mMergeResults;

        // Thread-safe variables
        std::atomic<long long> mLastFrameId;

        DELETE_COPY(PersonTracker);
    };
}

#endif // OPENPOSE_TRACKING_PERSON_TRACKER_HPP

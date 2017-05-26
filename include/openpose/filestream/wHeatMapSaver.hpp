#ifndef OPENPOSE__FILESTREAM__W_HEAT_MAP_SAVER_HPP
#define OPENPOSE__FILESTREAM__W_HEAT_MAP_SAVER_HPP

#include <memory> // std::shared_ptr
#include <string>
#include <openpose/thread/workerConsumer.hpp>
#include "heatMapSaver.hpp"

namespace op
{
    template<typename TDatums>
    class WHeatMapSaver : public WorkerConsumer<TDatums>
    {
    public:
        explicit WHeatMapSaver(const std::shared_ptr<HeatMapSaver>& heatMapSaver);

        void initializationOnThread();

        void workConsumer(const TDatums& tDatums);

    private:
        const std::shared_ptr<HeatMapSaver> spHeatMapSaver;

        DELETE_COPY(WHeatMapSaver);
    };
}





// Implementation
#include <vector>
#include <opencv2/core/core.hpp>
#include <openpose/utilities/errorAndLog.hpp>
#include <openpose/utilities/macros.hpp>
#include <openpose/utilities/pointerContainer.hpp>
#include <openpose/utilities/profiler.hpp>
namespace op
{
    template<typename TDatums>
    WHeatMapSaver<TDatums>::WHeatMapSaver(const std::shared_ptr<HeatMapSaver>& heatMapSaver) :
        spHeatMapSaver{heatMapSaver}
    {
    }

    template<typename TDatums>
    void WHeatMapSaver<TDatums>::initializationOnThread()
    {
    }

    template<typename TDatums>
    void WHeatMapSaver<TDatums>::workConsumer(const TDatums& tDatums)
    {
        try
        {
            if (checkNoNullNorEmpty(tDatums))
            {
                // Debugging log
                dLog("", Priority::Low, __LINE__, __FUNCTION__, __FILE__);
                // Profiling speed
                const auto profilerKey = Profiler::timerInit(__LINE__, __FUNCTION__, __FILE__);
                // T* to T
                auto& tDatumsNoPtr = *tDatums;
                // Record image(s) on disk
                std::vector<Array<float>> poseHeatMaps(tDatumsNoPtr.size());
                for (auto i = 0; i < tDatumsNoPtr.size(); i++)
                    poseHeatMaps[i] = tDatumsNoPtr[i].poseHeatMaps;
                const auto fileName = (!tDatumsNoPtr[0].name.empty() ? tDatumsNoPtr[0].name : std::to_string(tDatumsNoPtr[0].id));
                spHeatMapSaver->saveHeatMaps(poseHeatMaps, fileName);
                // Profiling speed
                Profiler::timerEnd(profilerKey);
                Profiler::printAveragedTimeMsOnIterationX(profilerKey, __LINE__, __FUNCTION__, __FILE__, Profiler::DEFAULT_X);
                // Debugging log
                dLog("", Priority::Low, __LINE__, __FUNCTION__, __FILE__);
            }
        }
        catch (const std::exception& e)
        {
            this->stop();
            error(e.what(), __LINE__, __FUNCTION__, __FILE__);
        }
    }

    COMPILE_TEMPLATE_DATUM(WHeatMapSaver);
}

#endif // OPENPOSE__FILESTREAM__W_HEAT_MAP_SAVER_HPP

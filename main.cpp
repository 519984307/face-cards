#include "donde/feature_extract/face_pipeline.h"
#include "donde/feature_extract/processor_factory.h"
#include "donde/video_process/ffmpeg_processor.h"
#include "mainwindow.h"
#include "picture_generator.h"
#include "play_controller.h"

#include <QApplication>

using json = nlohmann::json;
using donde_toolkits::feature_extract::FacePipeline;
using donde_toolkits::video_process::FFmpegVideoFrameProcessor;
using donde_toolkits::video_process::FFmpegVideoProcessor;

int main(int argc, char* argv[]) {
    QApplication a(argc, argv);

    json conf = R"(
    {
        "detector": {
          "concurrent": 1,
          "device_id": "CPU",
          "model": "./contrib/models/face-detection-adas-0001.xml",
          "warmup": false
        }
    }
)"_json;

    // init face pipeline, with detector only.
    FacePipeline pipeline{conf};
    auto detector = donde_toolkits::feature_extract::ProcessorFactory::createDetector();
    pipeline.Init(detector, nullptr, nullptr, nullptr);

    FFmpegVideoProcessor p{};
    PictureGenerator factory{p};
    PlayController controller{p};

    MainWindow w{factory, controller, pipeline};
    w.show();

    return a.exec();
}

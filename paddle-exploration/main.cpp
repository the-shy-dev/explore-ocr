#include <opencv2/opencv.hpp>
#include <paddle_inference_api.h>
#include <iostream>
#include <vector>

using namespace paddle_infer;

// Function to load a Paddle model
std::shared_ptr<Predictor> loadModel(const std::string &modelDir) {
    AnalysisConfig config;
    config.SetModel(modelDir + "/inference.pdmodel", modelDir + "/inference.pdiparams");
    config.DisableGpu();
    config.EnableMKLDNN();
    return CreatePredictor(config);
}

// Function to run the detection model
std::vector<std::vector<int>> runDetectionModel(std::shared_ptr<Predictor> &detector, const cv::Mat &img) {
    // Prepare input tensor
    auto input_names = detector->GetInputNames();
    auto input_tensor = detector->GetInputHandle(input_names[0]);
    input_tensor->Reshape({1, 3, img.rows, img.cols});
    input_tensor->CopyFromCpu(img.data);

    // Run the prediction
    detector->Run();

    // Get output tensor
    auto output_names = detector->GetOutputNames();
    auto output_tensor = detector->GetOutputHandle(output_names[0]);

    // Process output data
    std::vector<float> output_data(output_tensor->shape()[0]);
    output_tensor->CopyToCpu(output_data.data());

    // Dummy implementation: Replace with actual detection logic
    std::vector<std::vector<int>> detectedBoxes;
    detectedBoxes.push_back({50, 50, 200, 200});  // Example box, replace with real data
    return detectedBoxes;
}

// Function to run the classification model
std::string runClassificationModel(std::shared_ptr<Predictor> &classifier, const cv::Mat &img) {
    // Prepare input tensor
    auto input_names = classifier->GetInputNames();
    auto input_tensor = classifier->GetInputHandle(input_names[0]);
    input_tensor->Reshape({1, 3, img.rows, img.cols});
    input_tensor->CopyFromCpu(img.data);

    // Run the prediction
    classifier->Run();

    // Get output tensor
    auto output_names = classifier->GetOutputNames();
    auto output_tensor = classifier->GetOutputHandle(output_names[0]);

    // Get output data
    std::vector<float> output_data(output_tensor->shape()[0]);
    output_tensor->CopyToCpu(output_data.data());

    // Dummy implementation: Replace with actual classification logic
    return "Horizontal";  // Example classification result
}

// Function to run the recognition model
std::string runRecognitionModel(std::shared_ptr<Predictor> &recognizer, const cv::Mat &img) {
    // Prepare input tensor
    auto input_names = recognizer->GetInputNames();
    auto input_tensor = recognizer->GetInputHandle(input_names[0]);
    input_tensor->Reshape({1, 3, img.rows, img.cols});
    input_tensor->CopyFromCpu(img.data);

    // Run the prediction
    recognizer->Run();

    // Get output tensor
    auto output_names = recognizer->GetOutputNames();
    auto output_tensor = recognizer->GetOutputHandle(output_names[0]);

    // Get output data
    std::vector<float> output_data(output_tensor->shape()[0]);
    output_tensor->CopyToCpu(output_data.data());

    // Dummy implementation: Replace with actual recognition logic
    return "Recognized Text";  // Example recognition result
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "Usage: " << argv[0] << " <image_path>\n";
        return 1;
    }

    std::string imagePath = argv[1];

    // Read the image using OpenCV
    cv::Mat img = cv::imread(imagePath, cv::IMREAD_COLOR);
    if (img.empty()) {
        std::cerr << "Could not open or find the image: " << imagePath << "\n";
        return 1;
    }

    // Load models
    auto detector = loadModel("models/detection");
    auto classifier = loadModel("models/classification");
    auto recognizer = loadModel("models/recognition");

    // Run detection model
    auto detectedBoxes = runDetectionModel(detector, img);
    for (const auto &box : detectedBoxes) {
        cv::Rect rect(box[0], box[1], box[2] - box[0], box[3] - box[1]);
        cv::Mat roi = img(rect);

        // Run classification model on each detected text box
        std::string orientation = runClassificationModel(classifier, roi);
        std::cout << "Orientation: " << orientation << std::endl;

        // Run recognition model on each detected text box
        std::string text = runRecognitionModel(recognizer, roi);
        std::cout << "Recognized Text: " << text << std::endl;
    }

    return 0;
}

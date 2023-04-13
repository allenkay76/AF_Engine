#pragma once

struct ImageData {
    int width;
    int height;
    int channels;
    unsigned char* data;

    // Constructor
    ImageData()
        : width(0)
        , height(0)
        , channels(0)
        , data(nullptr)
    {
        // Additional constructor code here, if needed
    }
};


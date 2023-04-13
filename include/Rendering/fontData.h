#pragma once

struct FontData {
    int width;
    int height;
    int channels;
    unsigned char* data;

    // Constructor
    FontData()
        : width(0)
        , height(0)
        , channels(0)
        , data(nullptr)
    {
        // Additional constructor code here, if needed
    }
};


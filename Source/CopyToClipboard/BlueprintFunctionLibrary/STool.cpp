// Fill out your copyright notice in the Description page of Project Settings.


#include "./STool.h"
#include "HAL/PlatformApplicationMisc.h"
#include "Windows/AllowWindowsPlatformTypes.h"
#include "Windows/PreWindowsApi.h"
#include <windows.h>
#include "Windows/PostWindowsApi.h"
#include "Windows/HideWindowsPlatformTypes.h"

bool USTool::CopyImageToClipboard(const int32 width, const int32 height, const TArray<FColor>& imageData)
{

    bool bSuccess = true;
    // define dib header
    BITMAPINFOHEADER bitmapInfoHeader;
    ZeroMemory(&bitmapInfoHeader, sizeof(BITMAPINFOHEADER));
    bitmapInfoHeader.biSize = sizeof(BITMAPINFOHEADER);
    bitmapInfoHeader.biWidth = width;
    bitmapInfoHeader.biHeight = height; // Positive for bottom-up DIB
    bitmapInfoHeader.biPlanes = 1;
    bitmapInfoHeader.biBitCount = 32;
    bitmapInfoHeader.biCompression = BI_RGB;
    bitmapInfoHeader.biSizeImage = width * height * 4;
    bitmapInfoHeader.biXPelsPerMeter = 0;
    bitmapInfoHeader.biYPelsPerMeter = 0;
    bitmapInfoHeader.biClrUsed = 0;
    bitmapInfoHeader.biClrImportant = 0;


    // Calculate total size needed for DIB
    DWORD dibSize = sizeof(BITMAPINFOHEADER) + bitmapInfoHeader.biSizeImage;

    // Allocate global memory for the DIB
    HANDLE hDIB = GlobalAlloc(GMEM_MOVEABLE | GMEM_ZEROINIT, dibSize);
    if (hDIB == NULL) {
        CloseClipboard();
        return bSuccess = false;
    }

    LPVOID pDIB = GlobalLock(hDIB);
    if (pDIB == NULL) {
        GlobalFree(hDIB);
        CloseClipboard();
        return bSuccess = false;
    }

    // Copy the BITMAPINFOHEADER
    memcpy(pDIB, &bitmapInfoHeader, sizeof(BITMAPINFOHEADER));

    // Get pointer to the bitmap bits
    uint8* pBits = (uint8*)pDIB + sizeof(BITMAPINFOHEADER);

    // Copy pixel data with padding
    for (int32 y = 0; y < height; ++y) {
        uint8* rowDest = pBits + ((height-1-y) * width*4); // in reverse order to prevent flipping
        const FColor* rowSrc = &imageData[y * width];
        for (int32 x = 0; x < width; ++x) {
            rowDest[x * 4 + 0] = rowSrc[x].B;
            rowDest[x * 4 + 1] = rowSrc[x].G;
            rowDest[x * 4 + 2] = rowSrc[x].R;
            rowDest[x * 4 + 3] = rowSrc[x].A;
        }
    }

    GlobalUnlock(hDIB);

    if (!OpenClipboard(NULL) && EmptyClipboard()) {
        UE_LOG(LogTemp, Warning, TEXT("unable to open clipboard and clear clipboard"), width, height);
        return bSuccess=false;
    }

    // Set clipboard data and pass the ownership to system
    SetClipboardData(CF_DIB, hDIB);

    // Clean up
    CloseClipboard();

    return bSuccess;
}

bool USTool::CopyImageToClipboard(UTexture2D* texture2d)
{   
    //convert texture2d to TArray<FColor>
    int16 width = texture2d->GetPlatformData()->Mips[0].SizeX;
    int16 height = texture2d->GetPlatformData()->Mips[0].SizeY;
    if (width == 0 || height == 0) {
        UE_LOG(LogTemp, Warning, TEXT(" width or height can not be Zero"));
        return false;
    };
    FColor* pixels = static_cast<FColor*>(texture2d->GetPlatformData()->Mips[0].BulkData.Lock(LOCK_READ_WRITE));

    TArray<FColor> data;
    data.SetNum(width * height);

    for (int16 y = 0; y < height;++y) {
        for (int16 x = 0; x < width; ++x) {
            FColor pixel = pixels[y * width + x];
            data[y * width + x] = pixel;
        }
    }
    texture2d->GetPlatformData()->Mips[0].BulkData.Unlock();

    return CopyImageToClipboard(width, height, data);
}

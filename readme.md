# CopyClipboardImage

## Sample
https://github.com/Glanceman/Unreal-CopyToClipboard/releases/tag/Sample

## Environment
1. UE5.3.2
2. Windows 11 24h2

## Dev
1. generate .sln by right the .uproject or generate through unreal editor

## Functions 
### Press Z to copy red image to clipboard
https://www.youtube.com/watch?v=3FEePfON-Ko

https://github.com/user-attachments/assets/0cfab64f-0f18-4d27-a314-81d1ab6ad672


### Press X to copy texture to clipboard
https://www.youtube.com/watch?v=02HJQW1Au3w

https://github.com/user-attachments/assets/d5517998-f604-45ca-b1b8-bcdf354630ce


## Principle
Use windows api for handling image data to clipboard since `FPlatformMisc:ClipboardCopy(TChar* str)` is only for the UTF8 data

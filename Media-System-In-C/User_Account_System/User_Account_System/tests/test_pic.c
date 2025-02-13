#include <stdio.h>
#include <string.h>
#define STB_IMAGE_IMPLEMENTATION
#include "C:\Users\SHnav\OneDrive\Pictures\Documents\Media-System-In-C\User_Account_System\includes\stb_image.h"

int main() {
    char imagePath[256] = "C:\\Users\\SHnav\\Downloads\\GetImage.jpeg";

    char Chars[] = "@#MW&8%B$XQO0GUCJYXLZxuvncrjtf/|\\!?[]{}1-_+~<>.";
    int CharsLen = strlen(Chars);

    int Width, Height, PixelSize;
    unsigned char *ImageData = stbi_load(imagePath, &Width, &Height, &PixelSize, 0);

    if (ImageData) {
        unsigned char *Pixels = ImageData;
        for (int RowIndex = 0; RowIndex < Height; RowIndex++) {  // Keep all rows
            for (int ColumnIndex = 0; ColumnIndex < Width; ColumnIndex++) {
                unsigned char R = *Pixels++;
                unsigned char G = *Pixels++;
                unsigned char B = *Pixels++;
                if (PixelSize == 4) {
                    unsigned char A = *Pixels++;
                }
                float Avg = (R + G + B) / 3.0f;
                int CharIndex = (int)(CharsLen * (Avg / 255.0f));
                putchar(Chars[CharIndex]);
                putchar(Chars[CharIndex]);  // Duplicate character to make it wider
            }
            putchar('\n');
        }
        stbi_image_free(ImageData);
    } else {
        printf("Failed to load image %s\n", imagePath);
    }
    return 0;
}

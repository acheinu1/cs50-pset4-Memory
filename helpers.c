#include "helpers.h"
#include <math.h>

// Convert image to grayscale
void grayscale(int height, int width, RGBTRIPLE image[height][width])
{
    for(int row=0; row<height; row++)
    {
        for(int col=0; col<width; col++)
        {
            float average = (image[row][col].rgbtBlue + image[row][col].rgbtGreen + image[row][col].rgbtRed)/3.00;
            int avg = round(average);

            image[row][col].rgbtBlue = avg;
            image[row][col].rgbtGreen = avg;
            image[row][col].rgbtRed = avg;
        }
    }
    return;
}

int cap(int value)
{
    return value > 255 ? 255 : value;
}

// Convert image to sepia
void sepia(int height, int width, RGBTRIPLE image[height][width])
{
    for(int row=0; row<height; row++)
    {
        for(int col=0; col<width; col++)
        {
            int sepiaRed = cap(round(0.393 * image[row][col].rgbtRed + 0.769 * image[row][col].rgbtGreen + 0.189 * image[row][col].rgbtBlue));
            int sepiaGreen = cap(round(.349 * image[row][col].rgbtRed + .686 * image[row][col].rgbtGreen + .168 * image[row][col].rgbtBlue));
            int sepiaBlue = cap(round(.272 * image[row][col].rgbtRed + .534 * image[row][col].rgbtGreen + .131 * image[row][col].rgbtBlue));

            image[row][col].rgbtBlue = sepiaBlue;
            image[row][col].rgbtGreen = sepiaGreen;
            image[row][col].rgbtRed = sepiaRed;
        }
    }
    return;
}

// Reflect image horizontally
void reflect(int height, int width, RGBTRIPLE image[height][width])
{
   for(int i = 0; i < height; i++)
    {
      for(int j = 0; j < (width/2); j++)
        {
            int red = image[i][j].rgbtRed;
            int blue = image[i][j].rgbtBlue;
            int green = image[i][j].rgbtGreen;

            image[i][j].rgbtRed = image[i][width - j - 1].rgbtRed;
            image[i][j].rgbtBlue = image[i][width - j - 1].rgbtBlue;
            image[i][j].rgbtGreen = image[i][width - j - 1].rgbtGreen;

            image[i][width - j - 1].rgbtRed = red;
            image[i][width - j - 1].rgbtBlue = blue;
            image[i][width - j - 1].rgbtGreen = green;
        }
    }
    return;
}

// Blur image
void blur(int height, int width, RGBTRIPLE image[height][width])
{
    RGBTRIPLE temp[height][width];


  for(int i = 0; i < height; i++)
    {
      for(int j = 0; j < width; j++)
        {
            int sumRed = 0;
            int sumGreen = 0;
            int sumBlue = 0;
            float counter = 0.00;


        for (int k=-1; k<2; k++)
        {
            for (int h=-1; h<2; h++)
            {
                if (i + k < 0 || i + k > height - 1 ||  j + h < 0 || j + h > width - 1)
                {
                    continue;
                }

                sumBlue += image [i+k][j+h].rgbtBlue;
                sumGreen += image [i+k][j+h].rgbtGreen;
                sumRed += image [i+k][j+h].rgbtRed;

                counter++;
            }
        }

           temp[i][j].rgbtBlue = round(sumBlue/counter);
           temp[i][j].rgbtRed = round(sumRed/counter);
           temp[i][j].rgbtGreen = round(sumGreen/counter);
        }
    }

    for(int i = 0; i < height; i++)
    {
        for(int j = 0; j < width; j++)
        {
           image[i][j].rgbtBlue = temp[i][j].rgbtBlue;
           image[i][j].rgbtRed = temp[i][j].rgbtRed;
           image[i][j].rgbtGreen = temp[i][j].rgbtGreen;
        }
    }
    return;
}

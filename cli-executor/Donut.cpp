#include "Donut.hpp"

#include <math.h>
#include <stdint.h>
#include <string.h>
#include <unistd.h>

void donut(cli::OutputStream& output) 
{
    float A = 0, B = 0;
    float i, j;
    int k;
    float z[1760];
    char b[1760];

    output << ("\x1b[2J"); // clear screen
    for(;;) {
        memset(b,32,1760);
        memset(z,0,7040);
        for(j=0; j < 6.28; j += 0.07) {
            for(i=0; i < 6.28; i += 0.02) {
                float c = sin(i);
                float d = cos(j);
                float e = sin(A);
                float f = sin(j);
                float g = cos(A);
                float h = d + 2;
                float D = 1 / (c * h * e + f * g + 5);
                float l = cos(i);
                float m = cos(B);
                float n = sin(B);
                float t = c * h * g - f * e;
                int x = 40 + 30 * D * (l * h * m - t * n);
                int y= 12 + 15 * D * (l * h * n + t * m);
                int o = x + 80 * y;
                int N = 8 * ((f * e - c * d * g) * m - c * d * e - f * g - l * d * n);
                if(22 > y && y > 0 && x > 0 && 80 > x && D > z[o]) {
                    z[o] = D;
                    b[o] = ".,-~:;=!*#$@"[N > 0 ? N : 0];
                }
            }
        }
        output <<("\x1b[H"); //move home
        for(k = 0; k < 1761; k++) {

            if(k % 80) {
                output << b[k];
            } else {
                output << "\r\n";
            }
            A += 0.00004;
            B += 0.00002;
        }
        usleep(30000);
    }
}
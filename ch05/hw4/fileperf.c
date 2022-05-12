#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <wchar.h>
#include <uchar.h>
#include <locale.h>

void CheckOverflow(int *buflen, int *pos, int *tab, FILE *file, wchar_t *wordbuf)
{
    if(*buflen + *pos + *tab > 80)     // check if word buffer can be outputed
    {
        fprintf(file, "\n");  
        *buflen = *pos + *tab;
    } 
    else
        *buflen += *pos + *tab;

    wordbuf[*pos] = '\0';

    fprintf(file, "%ls", wordbuf);
    *pos = 0;
    *tab = 0;
    wordbuf[*pos] = '\0';
}

int main(int argc, char **argv)
{
    if(argc < 4)
        fprintf(stderr, "Invalid format: <executable file> <inputfile> <outputfile> <buffer length>\n");
    else
    {
        FILE *inputfile = fopen(argv[1], "r");
        FILE *outputfile = fopen(argv[2], "w+");

        if(inputfile == NULL || outputfile == NULL)
            fprintf(stderr, "%s\n", strerror(errno));
        else
        {
            int bufsize = atoi(argv[3]);
            if(bufsize < -1)
                fprintf(stderr, "Invalid input: buffer size need to be larger than or equal to -1\n");
            else
            {
                if(bufsize == 0)    // no buffer
                {
                    setvbuf(inputfile, NULL, _IONBF, 0);
                    setvbuf(outputfile, NULL, _IONBF, 0);
                }
                else if(bufsize == -1)  // line buffer
                {
                    bufsize = 1024;
                    setvbuf(inputfile, NULL, _IOLBF, bufsize);
                    setvbuf(outputfile, NULL, _IOLBF, bufsize);
                }
                else if(bufsize > 0)    // full buffer
                {
                    setvbuf(inputfile, NULL, _IOFBF, bufsize);
                    setvbuf(outputfile, NULL, _IOFBF, bufsize);
                }

                setlocale(LC_CTYPE,"C.UTF-8");
                wint_t ch = 0, buflen = 0, pos = 0, tab = 0;
                wchar_t wordbuf[150];
                wchar_t inputch;
                

                while(1)
                {
                    ch = getwc(inputfile);
                    inputch = (wchar_t) ch;


                    if(inputch == '\t')
                        tab += 7;
                        
                    if(ch == WEOF)   // output remain word in buffer
                    {

                        if(pos != 0)
                        {
                            wordbuf[pos] = '\0';
                            CheckOverflow(&buflen, &pos, &tab, outputfile, wordbuf);
                            buflen = 0;
                        }
                        break;
                    }

                    if(inputch == '\n')     // output word buffer with newline
                    {
                        wordbuf[pos++] = inputch;
                        CheckOverflow(&buflen, &pos, &tab, outputfile, wordbuf);
                        buflen = 0;
                    }
                    else if(inputch == ' ')     
                    {
                        if(pos == 0 && buflen == 0)
                            continue;
                        else
                        {
                            wordbuf[pos++] = inputch;
                            CheckOverflow(&buflen, &pos, &tab, outputfile, wordbuf);
                        }
                    }
                    else
                        wordbuf[pos++] = inputch;
                }
            }
            fclose(inputfile);
            fclose(outputfile);
        }
    }

    return 0;
}
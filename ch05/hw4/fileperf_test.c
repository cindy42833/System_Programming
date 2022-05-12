#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>

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
                // char *inputbuf = NULL;
                // char *outputbuf = NULL;
                // if(bufsize == 0)    // no buffer
                // {
                //     setvbuf(inputfile, NULL, _IONBF, 0);
                //     setvbuf(outputfile, NULL, _IONBF, 0);
                // }
                // else if(bufsize == -1)  // line buffer
                // {
                //     bufsize = 1024;
                //     inputbuf = (char *) malloc(sizeof(char) * bufsize);
                //     outputbuf = (char *) malloc(sizeof(char) * bufsize);
                //     setvbuf(inputfile, inputbuf, _IOLBF, sizeof(inputbuf));
                //     setvbuf(outputfile, outputbuf, _IOLBF, sizeof(outputbuf));
                // }
                // else if(bufsize > 0)    // full buffer
                // {
                //     inputbuf = (char *) malloc(sizeof(char) * bufsize);
                //     outputbuf = (char *) malloc(sizeof(char) * bufsize);
                //     setvbuf(inputfile, inputbuf, _IOFBF, sizeof(inputbuf));
                //     setvbuf(outputfile, outputbuf, _IOFBF, sizeof(outputbuf));
                // }

                int ch = 0, buflen = 0;
                char wordbuf[120];
                unsigned char inputch;
                

                while(1)
                {
                    ch = getc(inputfile);
                    inputch = (unsigned char) ch;

                    if(ch == EOF)   // output remain word in buffer
                    {
                        if(buflen != 0)
                        {
                            wordbuf[buflen] = '\0';
                            fprintf(outputfile, "%s", wordbuf);
                            buflen = 0;
                            wordbuf[buflen] = '\0';
                        }
                        
                        break;
                    }

                    if(inputch == '\n')     // output word buffer with newline
                    {
                        wordbuf[buflen++] = inputch;
                        wordbuf[buflen] = '\0';
                        fprintf(outputfile, "%s", wordbuf);
                        buflen = 0;
                        wordbuf[buflen] = '\0';
                    }
                    else if(inputch == ' ')     
                    {
                        if(buflen == 0)
                            continue;
                        else
                        {
                            wordbuf[buflen++] = inputch;
                            if(buflen > 80)     // check if word buffer can be outputed
                            {   
                                wordbuf[buflen++] = '\n';
                                wordbuf[buflen] = '\0';
                                fprintf(outputfile, "%s", wordbuf);
                                buflen = 0;
                                wordbuf[buflen] = '\0';
                            }
                        }
                    }
                    else
                        wordbuf[buflen++] = inputch;
                }
            }
            fclose(inputfile);
            fclose(outputfile);
        }
    }

    



    return 0;
}
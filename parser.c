#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"


/*======== void parse_file () ==========
Inputs:   char * filename
struct matrix * transform,
struct matrix * pm,
screen s
Returns:

Goes through the file named filename and performs all of the actions listed in that file.
The file follows the following format:
Every command is a single character that takes up a line
Any command that requires arguments must have those arguments in the second line.
The commands are as follows:
line: add a line to the edge matrix -
takes 6 arguemnts (x0, y0, z0, x1, y1, z1)
ident: set the transform matrix to the identity matrix -
scale: create a scale matrix,
then multiply the transform matrix by the scale matrix -
takes 3 arguments (sx, sy, sz)
translate: create a translation matrix,
then multiply the transform matrix by the translation matrix -
takes 3 arguments (tx, ty, tz)
rotate: create an rotation matrix,
then multiply the transform matrix by the rotation matrix -
takes 2 arguments (axis, theta) axis should be x y or z
apply: apply the current transformation matrix to the
edge matrix
display: draw the lines of the edge matrix to the screen
display the screen
save: draw the lines of the edge matrix to the screen
save the screen to a file -
takes 1 argument (file name)
quit: end parsing

See the file script for an example of the file format


IMPORTANT MATH NOTE:
the trig functions int math.h use radian mesure, but us normal
humans use degrees, so the file will contain degrees for rotations,
be sure to conver those degrees to radians (M_PI is the constant
for PI)
====================*/
void parse_file ( char * filename,
    struct matrix * transform,
    struct matrix * edges,
    screen s) {

        FILE *f;
        char line[256];
        char params[256];
        clear_screen(s);

        /*if ( strcmp(filename, "stdin") == 0 )
        f = stdin;
        else
        f = fopen(filename, "r");*/
        f = fopen(filename,"rw");

        while ( fgets(line, 255, f) != NULL ) {
            line[strlen(line)-1]='\0';

            //printf("%s\n",line);


            //line
            if( strcmp(line,"line") ){
                fgets(params,255,f);
                printf("params: %s\n",params);

                int l[6];
                int i;
                char * s = strtok(params," ");
                for (i = 0; i < 6; i++){
                    //printf("%s\n",s);
                    l[i] = s;
                    s = strtok(NULL, " ");
                }

                for (i = 0; i < 6; i++){
                    printf("%s",l[i]);
                }
                printf("\n");

                add_edge(edges,l[0],l[1],l[2],l[3],l[4],l[5]);
            }
            //ident
            else if ( strcmp(line, "ident") ){
                ident(transform);
            }

            //scale
            else if ( strcmp(line, "scale") ){
                fgets(params,255,f);
                int l[3];
                int i;
                char * s = strtok(params," ");
                for (i = 0; i < 3; i++){
                    params[i] = s;
                    s = strtok(NULL, " ");
                }

                matrix_mult(make_scale(l[0],l[1],l[2]),transform);
            }

            //move
            else if ( strcmp(line, "move") ){
                fgets(params,255,f);
                int l[3];
                int i;
                char * s = strtok(params," ");
                for (i = 0; i < 3; i++){
                    params[i] = s;
                    s = strtok(NULL, " ");
                }

                matrix_mult(make_translate(l[0],l[1],l[2]),transform);
            }

            //rotate
            else if ( strcmp(line, "rotate") ){
                fgets(params,255,f);
                int l[2];
                int i;
                char * s = strtok(params," ");
                for (i = 0; i < 2; i++){
                    params[i] = s;
                    s = strtok(NULL, " ");
                }

                if(strcmp(l[0],'x') == 0){
                    matrix_mult(make_rotX(l[1]),transform);
                }

                else if (strcmp(l[1],'y')==0){
                    matrix_mult(make_rotY(l[1]),transform);
                }
                else{
                    matrix_mult(make_rotZ(l[1]),transform);
                }

            }

            //apply
            else if ( strcmp(line, "apply") ){
                matrix_mult(transform,edges);
                color c;
                c.red=255;
                c.blue=0;
                c.green=0;
                draw_lines(edges,s,c);
            }

            //display
            else if ( strcmp(line,"display") ){
                display(s);
            }

            //save
            else if ( strcmp(line,"save") ){
                fgets(params,255,f);
                save_extension(s,params);
            }

            else{
                printf("error\n");
            }
        }


    }
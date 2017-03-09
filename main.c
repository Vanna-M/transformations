#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "ml6.h"
#include "display.h"
#include "draw.h"
#include "matrix.h"
#include "parser.h"

int main(int argc, char **argv) {

    struct matrix * edges;
    struct matrix * transform;

    edges = new_matrix(4, 4);
    transform = new_matrix(4, 4);
    int i,j;

    //add_edge(edges,0,0,0,500,500,500);

    screen s;
    color c;
    c.red = 255;
    c.green = 0;
    c.blue = 0;

    clear_screen(s);



    /*if ( argc == 2 )
    parse_file( argv[1], transform, edges, s );
    else
        //parse_file( "stdin", transform, edges, s );*/
    parse_file("script",transform,edges,s);


    //display(s);
    free_matrix( edges );
    free_matrix( transform );
}

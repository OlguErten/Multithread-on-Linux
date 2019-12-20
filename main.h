/**
 * file main.h
 *
 * Author: Erten
 * brief Function prototypes and look up tables for main runnable
 **/

#ifndef MAIN_H_
#define MAIN_H_

char *Listed_Songs[20][2] = /* Look-up table for the Song names and genres */
{
    {"One",
     "Rock"
    },
    {"Vogue",
     "Pop"
    },
    {"Jeremy",
     "Rock"
    },
    {"Sabotage",
     "Pop"
    },
    {"Loser",
     "Rock"
    },
    {"Gasolina",
     "Rap",
    },
    {"Weezer",
     "Rock",
    },
    {"Ignition",
     "Pop"
    },
    {"Clocks",
     "Rock",
    },
    {"Runaway",
     "Jazz"
    },
    {"Surrender",
     "Rock"
    },
    {"Rain",
     "Rock"
    },
    {"Kiss",
     "Rock"
    },
    {"Cupid",
     "Jazz"
    },
    {"Heroin",
     "Rock"
    },
    {"Juicy",
     "Rap"
    },
    {"Thirteen",
     "Rock"
    },
    {"Roxanne",
     "Pop"
    },
    {"Maps",
     "Rock"
    },
    {"Alison",
     "Rock"
    }
};

int *Song_Years[20] = { 1991, 1990, 1991, 1991, 2004, 1994, 2002, 2002, 1961, 1978, 1966, 1986, 1961, 1961, 1967, 1994, 1972, 1979, 2004, 1977}; /* Look-up table for song release years */

void* threadFunction_1(void* args);    /*Prototype for thread Type A */
void* threadFunction_2(void* args);    /*Prototype for thread Type B */
void* threadFunction_3(void* args);    /*Prototype for thread Type C */

#endif /* MAIN_H_ */

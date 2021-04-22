
/*
    Lookup Table for ASCII characters.
    This class could have been implemented as a single texture that
    can be read in at runtime.
*/

const int ASCII_WIDTH = 5;
const int ASCII_HEIGHT = 7;
const int ASCII_LENGTH = ASCII_WIDTH*ASCII_HEIGHT;
const int ASCII_TABLE_LENGTH = 13;

const bool ASCII_SPACE[ASCII_LENGTH] = {};

const bool ASCII_DOT[ASCII_LENGTH] = 
                           {0,0,0,0,0,
                            0,0,0,0,0,
                            0,0,0,0,0,
                            0,0,0,0,0,
                            0,0,0,0,0,
                            0,0,0,0,0,
                            0,0,1,0,0};

const bool ASCII_COLON[ASCII_LENGTH] =
                           {0,0,0,0,0,
                            0,0,0,0,0,
                            0,0,1,0,0,
                            0,0,0,0,0,
                            0,0,1,0,0,
                            0,0,0,0,0,
                            0,0,0,0,0};

const bool ASCII_MINUS[ASCII_LENGTH] =
                           {0,0,0,0,0,
                            0,0,0,0,0,
                            0,0,0,0,0,
                            1,1,1,1,1,
                            0,0,0,0,0,
                            0,0,0,0,0,
                            0,0,0,0,0};

const bool ASCII_EQUAL[ASCII_LENGTH] =
                           {0,0,0,0,0,
                            0,0,0,0,0,
                            1,1,1,1,1,
                            0,0,0,0,0,
                            1,1,1,1,1,
                            0,0,0,0,0,
                            0,0,0,0,0};

const bool ASCII_PLUS[ASCII_LENGTH] =
                           {0,0,0,0,0,
                            0,0,1,0,0,
                            0,0,1,0,0,
                            1,1,1,1,1,
                            0,0,1,0,0,
                            0,0,1,0,0,
                            0,0,0,0,0};                            

const bool ASCII_HASH[ASCII_LENGTH] =
                           {0,1,0,1,0,
                            0,1,0,1,0,
                            1,1,1,1,1,
                            0,1,0,1,0,
                            1,1,1,1,1,
                            0,1,0,1,0,
                            0,1,0,1,0};

const bool ASCII_ASTERISK[ASCII_LENGTH] = 
                           {0,0,1,0,0,
                            1,0,1,0,1,
                            0,1,1,1,0,
                            0,0,1,0,0,
                            0,1,1,1,0,
                            1,0,1,0,1,
                            0,0,1,0,0};

const bool ASCII_PERCENT[ASCII_LENGTH] =
                           {1,1,0,0,0,
                            1,1,0,0,1,
                            0,0,0,1,0,
                            0,0,1,0,0,
                            0,1,0,0,0,
                            1,0,0,1,1,
                            0,0,0,1,1};

const bool ASCII_AT[ASCII_LENGTH] =
                           {0,1,1,1,0,
                            1,0,0,0,1,
                            1,0,1,0,1,
                            1,0,1,1,1,
                            1,0,1,1,0,
                            1,0,0,0,0,
                            0,1,1,1,1};

const bool ASCII_DOLLAR[ASCII_LENGTH] =
                           {0,0,1,0,0,
                            0,1,1,1,1,
                            1,0,1,0,0,
                            0,1,1,1,0,
                            0,0,1,0,1,
                            1,1,1,1,0,
                            0,0,1,0,0};

const bool ASCII_B[ASCII_LENGTH] =
                           {1,1,1,1,0,
                            1,0,0,0,1,
                            1,0,0,0,1,
                            1,1,1,1,0,
                            1,0,0,0,1,
                            1,0,0,0,1,
                            1,1,1,1,0};

const bool ASCII_8[ASCII_LENGTH] =
                           {0,1,1,1,0,
                            1,0,0,0,1,
                            1,0,0,0,1,
                            0,1,1,1,0,
                            1,0,0,0,1,
                            1,0,0,0,1,
                            0,1,1,1,0};

// Example ASCII brightness string " .:-=+*#%@"
const bool *ASCII_TABLE[ASCII_TABLE_LENGTH] = {ASCII_SPACE, ASCII_DOT, ASCII_COLON, ASCII_MINUS, ASCII_EQUAL, ASCII_PLUS, ASCII_ASTERISK, ASCII_HASH, ASCII_8, ASCII_PERCENT, ASCII_B, ASCII_AT, ASCII_DOLLAR}; 

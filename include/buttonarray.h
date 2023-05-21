#include <Arduino.h>

#ifndef BUTTONARRAY_H
#define BUTTONARRAY_H

/*

        0   1   2   3           Cols


0       0   1   2   3

1       4   5   6   7

2       8   9   10  11

3       12  13  14  15



Rows


Cols are Outputs
Rows are Inputs

*/

class buttonArray {
    private:
        int* button_rows;
        int* button_cols;
        int row_num;
        int col_num;

        int int_results_len;
        uint8_t* results;

        bool executor_exist = false;
        void (*press) (int);
    public:
        buttonArray(int col_num, int row_num, int* button_cols, int* button_rows);
        void setup();
        uint8_t* getResultArray();
        void setExecuter(void (*new_press)(int));
        void update();
};

#endif
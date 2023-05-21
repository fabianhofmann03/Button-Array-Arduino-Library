#include <buttonarray.h>

buttonArray::buttonArray(int col_num, int row_num, int *button_cols, int *button_rows)
{
    this->col_num = col_num;
    this->row_num = row_num;
    this->button_cols = button_cols;
    this->button_rows = button_rows;
}

void buttonArray::setup()
{
    for (int x = 0; x < this->col_num; x++)
    {
        pinMode(*(this->button_cols + x), INPUT); // Set to input first as default
                                                  // Switched between Input (Z) and Low (0)
    }
    for (int x = 0; x < this->row_num; x++)
    {
        pinMode(*(this->button_rows + x), INPUT_PULLUP); // Rows are input
    }
}

void buttonArray::setExecuter(void (*new_press)(int)) {
    this->press = new_press;
}

void buttonArray::update()
{
    for (int x = 0; x < this->col_num; x++) 
    {
        pinMode(*(this->button_cols + x), OUTPUT);
        digitalWrite(*(this->button_cols + x), LOW);
        for (int y = 0; y < this->row_num; y++)
        {
            if (!digitalRead(*(this->button_rows + y)))
            {
                this->press(x + y * this->col_num);
            }
        }
        pinMode(*(this->button_cols + x), INPUT_PULLUP);
    }
}
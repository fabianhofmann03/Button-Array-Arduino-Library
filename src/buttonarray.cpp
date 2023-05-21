#include <buttonarray.h>

buttonArray::buttonArray(int col_num, int row_num, int *button_cols, int *button_rows)
{
    this->col_num = col_num;
    this->row_num = row_num;
    this->button_cols = button_cols;
    this->button_rows = button_rows;

    this->int_results_len = (col_num * row_num) / 8 + ((col_num * row_num) % 8 != 0);
    this->results = new uint8_t[this->int_results_len];
    for(int x = 0; x < this->int_results_len; x++) {
        *(this->results + x) = 0;
    } 
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

uint8_t* buttonArray::getResultArray() {
    return this->results;
}

void buttonArray::setExecuter(void (*new_press)(int)) {
    this->executor_exist = true;
    this->press = new_press;
}

void buttonArray::update()
{
    for(int x = 0; x < this->int_results_len; x++) {
        *(this->results + x) = 0;
    }
    for (int x = 0; x < this->col_num; x++) 
    {
        pinMode(*(this->button_cols + x), OUTPUT);
        digitalWrite(*(this->button_cols + x), LOW);
        for (int y = 0; y < this->row_num; y++)
        {
            bool reading = !digitalRead(*(this->button_rows + y));

            int position = x + y * this->col_num;
            *(this->results + (position / 8)) = *(this->results + (position / 8)) | (reading << (position % 8));
            
            if (reading && this->executor_exist)
            {
                this->press(position);
            }
        }
        pinMode(*(this->button_cols + x), INPUT_PULLUP);
    }
}
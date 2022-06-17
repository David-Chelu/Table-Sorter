The format is going to be primitive, using ' ' character as a separator between values.
Any column name and value can have letters, digits, special characters etc.
Each entry will follow the same format, and the format will exist in a file separate from the data itself.
By default, the format file will be called "format.txt", and the data file will be called "data.txt".
Within the program, though, names can be entered for custom files.
The default format will look something like this:

name weight column1 column2 column3 ...

Instead of "column1", "column2", "column3", and so on, there will be text that names the current column.
So for instance, when assessing project complexity, one may include the columns "total_complexity", "estimated_code", "structural_complexity", "mathematical_complexity", and so on.
By default, sorting will be string sorting.
By default, each entry will have an ID variable, the value representing the line on which the entry is found in the file.

In the data file, entries will be one per line.
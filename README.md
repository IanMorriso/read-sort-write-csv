# read-sort-write-csv
Reads, sorts, updates, and writes data from .csv files

This program was created with **C** to read video game sales data from **gamesales.csv** file, calculate and update missing values, then sorts by *Global_Sales*.

To process and update missing values, run **./processing**. Once the program has finished running, you can then sort the data by any of the header row names (Publisher, Genre, NA_Sales, etc).
To do this, run **./sorting "header name here"**. Your sorted values will now be output to the file **gamesales_"header_name".csv**!
